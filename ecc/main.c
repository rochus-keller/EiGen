#include "chibicc.h"
#include <time.h>

typedef enum {
  FILE_NONE, FILE_C, FILE_ASM, FILE_OBJ, FILE_AR, FILE_DSO,
} FileType;

StringArray include_paths;
bool opt_fcommon = true;
bool opt_fpic;

static FileType opt_x;
static StringArray opt_include;
static bool opt_E;
static bool opt_M;
static bool opt_MD;
static bool opt_MMD;
static bool opt_MP;
static bool opt_S;
static bool opt_c;
static bool opt_cc1;
static bool opt_hash_hash_hash;
static bool opt_static;
static bool opt_shared;
static bool opt_lib = 0;
static char *opt_MF;
static char *opt_MT;
static char *opt_o;

static StringArray ld_extra_args;
static StringArray std_include_paths;

char *base_file;
static char *output_file;
uint8_t debug_info = 0;

static StringArray input_paths;
static StringArray tmpfiles;

static void usage(int status) {
  fprintf (stderr,
           "Usage: ecc options <source files>; where options are:\n");
  fprintf (stderr, "\n");
  fprintf (stderr, "  -E -- output C preprocessed code into stdout\n");
  fprintf (stderr, "  -Dname[=value], -Uname -- predefine or unpredefine macros\n");
  fprintf (stderr, "  -Idir, -Ldir -- add directories to search include headers or lbraries\n");
  fprintf (stderr, "  -w -- do not print any warnings\n");
  fprintf (stderr, "  -S, -c -- generate corresponding cod or obf files\n");
  fprintf (stderr, "  -o file -- put output code into given file\n");
  fprintf (stderr, "  -M, -MD   -- write a list of input files to stdout\n");
  fprintf (stderr, "  -lib   -- combine files to a library instead of an executable\n");

  fprintf(stderr,  "  -t  target\tselect one of the following targets (default: as host):\n\n");
  for( int i = 1; i < MaxTarget; i++ )
      fprintf(stderr, "      %s\t%s\n", targets[i].name, targets[i].description);
  exit(status);
}

static bool take_arg(char *arg) {
  char *x[] = {
    "-o", "-I", "-idirafter", "-include", "-x", "-MF", "-MT", "-Xlinker",
  };

  for (int i = 0; i < sizeof(x) / sizeof(*x); i++)
    if (!strcmp(arg, x[i]))
      return true;
  return false;
}

static void define(char *str) {
  char *eq = strchr(str, '=');
  if (eq)
    define_macro(mystrndup(str, eq - str), eq + 1);
  else
    define_macro(str, "1");
}

static int set_target(char *str) {
    for( int i = 1; i < MaxTarget; i++ )
    {
        if( strcmp(str,targets[i].name) == 0 )
        {
            target = i;
            Type* int_type = basic_type(TY_INT);
            Type* uint_type = basic_utype(TY_INT);
            Type* long_type = basic_type(TY_LONG);
            Type* ulong_type = basic_utype(TY_LONG);
            switch(targets[i].architecture)
            {
            case Amd16:
                target_pointer_width = 2;
                target_has_linkregister = 0;
                target_stack_align = 2;
                int_type->size = int_type->align = uint_type->size = uint_type->align = 2;
                long_type->size = long_type->align = ulong_type->size = ulong_type->align = 2;
               break;
            case Amd32:
                target_pointer_width = 4;
                target_has_linkregister = 0;
                target_stack_align = 4;
                int_type->size = int_type->align = uint_type->size = uint_type->align = 4;
                long_type->size = long_type->align = ulong_type->size = ulong_type->align = 4;
                break;
            case Amd64:
                target_pointer_width = 8;
                target_has_linkregister = 0;
                target_stack_align = 8;
                int_type->size = int_type->align = uint_type->size = uint_type->align = 4;
                long_type->size = long_type->align = ulong_type->size = ulong_type->align = 8;
               break;
            case Arma32:
                target_pointer_width = 4;
                target_has_linkregister = 1;
                target_stack_align = 4;
                int_type->size = int_type->align = uint_type->size = uint_type->align = 4;
                long_type->size = long_type->align = ulong_type->size = ulong_type->align = 4;
                break;
            case Armt32:
                target_pointer_width = 4;
                target_has_linkregister = 1;
                target_stack_align = 4;
                int_type->size = int_type->align = uint_type->size = uint_type->align = 4;
                long_type->size = long_type->align = ulong_type->size = ulong_type->align = 4;
                break;
            case Arma64:
                target_pointer_width = 8;
                target_has_linkregister = 1;
                target_stack_align = 16;
                int_type->size = int_type->align = uint_type->size = uint_type->align = 4;
                long_type->size = long_type->align = ulong_type->size = ulong_type->align = 8;
                break;
            }
            return 1;
        }
    }
    return 0;
}

static FileType parse_opt_x(char *s) {
  if (!strcmp(s, "c"))
    return FILE_C;
  if (!strcmp(s, "assembler"))
    return FILE_ASM;
  if (!strcmp(s, "none"))
    return FILE_NONE;
  error("<command line>: unknown argument for -x: %s", s);
}

static char *quote_makefile(char *s) {
  char *buf = calloc(1, strlen(s) * 2 + 1);

  for (int i = 0, j = 0; s[i]; i++) {
    switch (s[i]) {
    case '$':
      buf[j++] = '$';
      buf[j++] = '$';
      break;
    case '#':
      buf[j++] = '\\';
      buf[j++] = '#';
      break;
    case ' ':
    case '\t':
      for (int k = i - 1; k >= 0 && s[k] == '\\'; k--)
        buf[j++] = '\\';
      buf[j++] = '\\';
      buf[j++] = s[i];
      break;
    default:
      buf[j++] = s[i];
      break;
    }
  }
  return buf;
}

static void parse_args(int argc, char **argv) {
  // Make sure that all command line options that take an argument
  // have an argument.
  for (int i = 1; i < argc; i++)
    if (take_arg(argv[i]))
      if (!argv[++i])
        usage(1);

  StringArray idirafter = {};

  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-###")) {
      opt_hash_hash_hash = true;
      continue;
    }

    if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h"))
      usage(0);

    if (!strcmp(argv[i], "-o")) {
      opt_o = argv[++i];
      continue;
    }

    if (!strncmp(argv[i], "-o", 2)) {
      opt_o = argv[i] + 2;
      continue;
    }

    if (!strcmp(argv[i], "-S")) {
      opt_S = true;
      continue;
    }

#if 0
    if (!strcmp(argv[i], "-fcommon")) {
      opt_fcommon = true;
      continue;
    }

    if (!strcmp(argv[i], "-fno-common")) {
      opt_fcommon = false;
      continue;
    }
#endif

    if (!strcmp(argv[i], "-c")) {
      opt_c = true;
      continue;
    }

    if (!strcmp(argv[i], "-E")) {
      opt_E = true;
      continue;
    }

    if (!strncmp(argv[i], "-I", 2)) {
      strarray_push(&include_paths, argv[i] + 2);
      continue;
    }

    if (!strncmp(argv[i], "-lib", 4)) {
      opt_lib = 1;
      strarray_push(&ld_extra_args, "-lib");
      continue;
    }

    if (!strcmp(argv[i], "-D")) {
      define(argv[++i]);
      continue;
    }

    if (!strncmp(argv[i], "-D", 2)) {
      define(argv[i] + 2);
      continue;
    }

    if (!strcmp(argv[i], "-t")) {
      if( !set_target(argv[++i]) )
          error("unknown target: %s", argv[i]);
      continue;
    }

    if (!strcmp(argv[i], "-U")) {
      undef_macro(argv[++i]);
      continue;
    }

    if (!strncmp(argv[i], "-U", 2)) {
      undef_macro(argv[i] + 2);
      continue;
    }

    if (!strcmp(argv[i], "-include")) {
      strarray_push(&opt_include, argv[++i]);
      continue;
    }

    if (!strcmp(argv[i], "-x")) {
      opt_x = parse_opt_x(argv[++i]);
      continue;
    }

    if (!strncmp(argv[i], "-x", 2)) {
      opt_x = parse_opt_x(argv[i] + 2);
      continue;
    }

    if (!strncmp(argv[i], "-l", 2) || !strncmp(argv[i], "-Wl,", 4)) {
      strarray_push(&input_paths, argv[i]);
      continue;
    }

#if 0
    if (!strcmp(argv[i], "-Xlinker")) {
      strarray_push(&ld_extra_args, argv[++i]);
      continue;
    }
#endif

    if (!strcmp(argv[i], "-s")) {
      strarray_push(&ld_extra_args, "-s");
      continue;
    }

    if (!strcmp(argv[i], "-M")) {
      opt_M = true;
      continue;
    }

    if (!strcmp(argv[i], "-MF")) {
      opt_MF = argv[++i];
      continue;
    }

    if (!strcmp(argv[i], "-MP")) {
      opt_MP = true;
      continue;
    }

    if (!strcmp(argv[i], "-MT")) {
      if (opt_MT == NULL)
        opt_MT = argv[++i];
      else
        opt_MT = format("%s %s", opt_MT, argv[++i]);
      continue;
    }

    if (!strcmp(argv[i], "-MD")) {
      opt_MD = true;
      continue;
    }

    if (!strcmp(argv[i], "-MQ")) {
      if (opt_MT == NULL)
        opt_MT = quote_makefile(argv[++i]);
      else
        opt_MT = format("%s %s", opt_MT, quote_makefile(argv[++i]));
      continue;
    }

    if (!strcmp(argv[i], "-MMD")) {
      opt_MD = opt_MMD = true;
      continue;
    }

#if 0
    if (!strcmp(argv[i], "-fpic") || !strcmp(argv[i], "-fPIC")) {
      opt_fpic = true;
      continue;
    }

    if (!strcmp(argv[i], "-idirafter")) {
      strarray_push(&idirafter, argv[i++]);
      continue;
    }

    if (!strcmp(argv[i], "-static")) {
      opt_static = true;
      strarray_push(&ld_extra_args, "-static");
      continue;
    }

    if (!strcmp(argv[i], "-shared")) {
      opt_shared = true;
      strarray_push(&ld_extra_args, "-shared");
      continue;
    }
#endif

    if (!strcmp(argv[i], "-L")) {
      strarray_push(&ld_extra_args, "-L");
      strarray_push(&ld_extra_args, argv[++i]);
      continue;
    }

    if (!strncmp(argv[i], "-L", 2)) {
      strarray_push(&ld_extra_args, "-L");
      strarray_push(&ld_extra_args, argv[i] + 2);
      continue;
    }

    if (!strncmp(argv[i], "-g", 2)) {
        debug_info = 1;
        continue;
    }

#if 0
    if (!strcmp(argv[i], "-hashmap-test")) {
      hashmap_test();
      exit(0);
    }

    // These options are ignored for now.
    if (!strncmp(argv[i], "-O", 2) ||
        !strncmp(argv[i], "-W", 2) ||
        !strncmp(argv[i], "-g", 2) ||
        !strncmp(argv[i], "-std=", 5) ||
        !strcmp(argv[i], "-ffreestanding") ||
        !strcmp(argv[i], "-fno-builtin") ||
        !strcmp(argv[i], "-fno-omit-frame-pointer") ||
        !strcmp(argv[i], "-fno-stack-protector") ||
        !strcmp(argv[i], "-fno-strict-aliasing") ||
        !strcmp(argv[i], "-m64") ||
        !strcmp(argv[i], "-mno-red-zone") ||
        !strcmp(argv[i], "-w"))
      continue;
#endif

    if (argv[i][0] == '-' && argv[i][1] != '\0')
      error("unknown argument: %s", argv[i]);

    strarray_push(&input_paths, argv[i]);
  }

  for (int i = 0; i < idirafter.len; i++)
    strarray_push(&include_paths, idirafter.data[i]);

  if (input_paths.len == 0)
    error("no input files");

  // -E implies that the input is the C macro language.
  if (opt_E)
    opt_x = FILE_C;
}

static FILE *open_file(char *path) {
  if (!path || strcmp(path, "-") == 0)
    return stdout;

  FILE *out = fopen(path, "w");
  if (!out)
    error("cannot open output file: %s: %s", path, strerror(errno));
  return out;
}

static bool endswith(char *p, char *q) {
  int len1 = strlen(p);
  int len2 = strlen(q);
  return (len1 >= len2) && !strcmp(p + len1 - len2, q);
}

// Replace file extension
static char *replace_extn(char *tmpl, char *extn) {
  char *dot = strrchr(tmpl, '.');
  const int len2 = strlen(extn);
  int len1;
  if (dot)
    len1 = dot - tmpl;
  else
    len1 = strlen(tmpl);
  const int len3 = len1 + len2 + 1;
  char* res = (char*)malloc(len3);
  memcpy(res, tmpl, len1);
  memcpy(res + len1, extn, len2 );
  res[len3-1] = 0;
  return res;
}

static void cleanup(void) {
  for (int i = 0; i < tmpfiles.len; i++)
  {
    remove(tmpfiles.data[i]);
    free(tmpfiles.data[i]);
  }
  cleanup_base_types();
}

static char *create_tmpfile(void) {
  char* path = (char*)malloc(TMP_MAX);
  tmpnam(path);
  strarray_push(&tmpfiles, path);
  return path;
}

static void cc1(void);
static void run_cc1(int argc, char **argv, char *input, char *output) {
  if (input) { // -cc1-input
    base_file = input;
  }

  if (output) { // -cc1-output
    output_file = output;
  }

  cc1();
}

// Print tokens to stdout. Used for -E.
static void print_tokens(Token *tok) {
  FILE *out = open_file(opt_o ? opt_o : "-");

  int line = 1;
  for (; tok->kind != TK_EOF; tok = tok->next) {
    if (line > 1 && tok->at_bol)
      fprintf(out, "\n");
    if (tok->has_space && !tok->at_bol)
      fprintf(out, " ");
    fprintf(out, "%.*s", tok->len, tok->loc);
    line++;
  }
  fprintf(out, "\n");
}

static bool in_std_include_path(char *path) {
  for (int i = 0; i < std_include_paths.len; i++) {
    char *dir = std_include_paths.data[i];
    int len = strlen(dir);
    if (strncmp(dir, path, len) == 0 && path[len] == '/')
      return true;
  }
  return false;
}

// If -M options is given, the compiler write a list of input files to
// stdout in a format that "make" command can read. This feature is
// used to automate file dependency management.
static void print_dependencies(void) {
  char *path;
  if (opt_MF)
    path = opt_MF;
  else if (opt_MD)
    path = replace_extn(opt_o ? opt_o : base_file, ".d");
  else if (opt_o)
    path = opt_o;
  else
    path = "-";

  FILE *out = open_file(path);
  if (opt_MT)
    fprintf(out, "%s:", opt_MT);
  else
    fprintf(out, "%s:", quote_makefile(replace_extn(base_file, ".obf")));

  File **files = get_input_files();

  for (int i = 0; files[i]; i++) {
    if (opt_MMD && in_std_include_path(files[i]->name))
      continue;
    fprintf(out, " \\\n  %s", files[i]->name);
  }

  fprintf(out, "\n\n");

  if (opt_MP) {
    for (int i = 1; files[i]; i++) {
      if (opt_MMD && in_std_include_path(files[i]->name))
        continue;
      fprintf(out, "%s:\n\n", quote_makefile(files[i]->name));
    }
  }
}

static Token *must_tokenize_file(char *path) {
  Token *tok = tokenize_file(path);
  if (!tok)
    error("%s: %s", path, strerror(errno));
  return tok;
}

static Token *append_tokens(Token *tok1, Token *tok2) {
  if (!tok1 || tok1->kind == TK_EOF)
    return tok2;

  Token *t = tok1;
  while (t->next->kind != TK_EOF)
    t = t->next;
  t->next = tok2;
  return tok1;
}

static void cc1(void) {
  Token *tok = NULL;

  // Process -include option
  for (int i = 0; i < opt_include.len; i++) {
    char *incl = opt_include.data[i];

    char *path;
    if (file_exists(incl)) {
      path = incl;
    } else {
      path = search_include_paths(incl);
      if (!path)
        error("-include: %s: %s", incl, strerror(errno));
    }

    Token *tok2 = must_tokenize_file(path);
    tok = append_tokens(tok, tok2);
  }

  printf("compiling '%s'\n", base_file);
  fflush(stdout);
  // Tokenize and parse.
  Token *tok2 = must_tokenize_file(base_file);
  tok = append_tokens(tok, tok2);
  tok = preprocess(tok);

  // If -M or -MD are given, print file dependencies.
  if (opt_M || opt_MD) {
    print_dependencies();
    if (opt_M)
      return;
  }

  // If -E is given, print out preprocessed C code as a result.
  if (opt_E) {
    print_tokens(tok);
    return;
  }

  Obj *prog = parse(tok);

  // Open a temporary output buffer.
  FILE *output_buf = tmpfile();

  // Traverse the AST to emit assembly.
  codegen(prog, output_buf);
  fseek(output_buf,0,SEEK_SET);

  // Write the asembly text to a file.
  FILE *out = open_file(output_file);
  char a;
  while ( (a = fgetc(output_buf)) != EOF )
  {
     fputc(a, out);
  }
  fclose(out);
  fclose(output_buf);
}

static void assemble(char *input, char *output) {
#ifdef ECC_HAVE_BACKEND
  run_codegen(input,output);
#else
  error("this version of ecc has no integrated backend; call 'ecsd -t %s <cod-file>' instead",
        targets[target].name);
#endif
}

static void link(StringArray *inputs, char *output) {
  // TODO if (opt_static) {
  // TODO if (opt_shared)
#ifdef ECC_HAVE_BACKEND
  run_linker(inputs, &ld_extra_args, output);
#endif
}

static FileType get_file_type(char *filename) {
  if (opt_x != FILE_NONE)
    return opt_x;

  if (endswith(filename, ".lib"))
    return FILE_AR;
  if (endswith(filename, ".obf"))
    return FILE_OBJ;
  if (endswith(filename, ".c"))
    return FILE_C;
  if (endswith(filename, ".cod"))
    return FILE_ASM;

  error("<command line>: unknown file extension: %s", filename);
}

int main(int argc, char **argv) {
  clock_t start, end;
  start = clock();

  atexit(cleanup);
  parse_args(argc, argv);

  if( target == NoTarget )
      error("please specify a valid target using the -t option");

  init_macros();

  if (input_paths.len > 1 && opt_o && (opt_c || opt_S | opt_E))
    error("cannot specify '-o' with '-c,' '-S' or '-E' with multiple files");

  StringArray ld_args = {};

  for (int i = 0; i < input_paths.len; i++) {
    char *input = input_paths.data[i];

    if (!strncmp(input, "-l", 2)) {
      strarray_push(&ld_args, input);
      continue;
    }

    if (!strncmp(input, "-Wl,", 4)) {
      char *s = mystrdup(input + 4);
      char *arg = strtok(s, ",");
      while (arg) {
        strarray_push(&ld_args, arg);
        arg = strtok(NULL, ",");
      }
      continue;
    }

    char *output;
    if (opt_o)
      output = opt_o;
    else if (opt_S)
      output = replace_extn(input, ".cod");
    else
      output = replace_extn(input, ".obf");

    FileType type = get_file_type(input);

    // Handle .o or .a
    if (type == FILE_OBJ || type == FILE_AR || type == FILE_DSO) {
      strarray_push(&ld_args, input);
      continue;
    }

    // Handle .s
    if (type == FILE_ASM) {
      if (!opt_S)
        assemble(input, output);
      continue;
    }

    assert(type == FILE_C);

    // Just preprocess
    if (opt_E || opt_M) {
      run_cc1(argc, argv, input, NULL);
      continue;
    }

    // Compile
    if (opt_S) {
      run_cc1(argc, argv, input, output);
      continue;
    }

    // Compile and assemble
    if (opt_c) {
      char *tmp = create_tmpfile();
      run_cc1(argc, argv, input, tmp);
      assemble(tmp, output);
      continue;
    }

    // Compile, assemble and link
    char *tmp1 = create_tmpfile();
    char *tmp2 = create_tmpfile();
    run_cc1(argc, argv, input, tmp1);
    assemble(tmp1, tmp2);
    strarray_push(&ld_args, tmp2);
    continue;
  }

  if (ld_args.len > 0)
    link(&ld_args, opt_o ? opt_o : opt_lib ? "a.lib" : "a.out");

  end = clock();
  printf("run for %.1f seconds\n", ((float) (end - start)) / CLOCKS_PER_SEC);
  return 0;
}

#include "hostdetect.h"

uint8_t target_pointer_width = sizeof(void*);
uint8_t target_stack_align = sizeof(void*);

#ifdef Q_PROCESSOR_ARM
uint8_t target_has_linkregister = 1;
#else
uint8_t target_has_linkregister = 0;
#endif

#ifdef Q_PROCESSOR_ARM
#ifdef Q_OS_LINUX
uint8_t target = sizeof(void*) == 8 ? ARMA64Linux : ARMA32Linux;
#elif defined Q_OS_MACOS
uint8_t target = NoTarget; // TODO
#else
uint8_t target = NoTarget;
#endif
#elif defined Q_PROCESSOR_X86
#ifdef Q_OS_LINUX
uint8_t target = sizeof(void*) == 8 ? AMD64Linux : AMD32Linux;
#elif defined Q_OS_WIN32
uint8_t target = sizeof(void*) == 8 ? Win64 : Win32;
#elif defined Q_OS_MACOS
uint8_t target = sizeof(void*) == 8 ? OSX64 : OSX32;
#else
uint8_t target = NoTarget;
#endif
#else
uint8_t target = NoTarget;
#endif

struct TargetData targets[] = {
    // all linkbin or linklib
    {"", "none", NoProcessor, true, "undefined", "none"},
    {"amd32linux", "amd32", Amd32, true, "Linux-based 32-bit systems", "dbgdwarf"}, // amd32run.obf amd32linuxrun.obf
    {"amd64linux", "amd64", Amd64, true, "Linux-based 64-bit systems", "dbgdwarf"}, // amd64run.obf amd64linuxrun.obf
    {"arma32linux", "arma32", Arma32, true, "Linux-based systems", "dbgdwarf"}, // arma32run.obf arma32linuxrun.obf
    {"arma64linux", "arma64", Arma64, true, "Linux-based systems", "dbgdwarf"},
    {"armt32linux", "armt32", Armt32, true, "Linux-based systems", "dbgdwarf"},
    {"armt32fpelinux", "armt32fpe", Armt32, true, "Linux-based systems", "dbgdwarf"}, // armt32fperun.obf armt32fpelinuxrun.obf
    {"bios16", "amd16", Amd16, false, "BIOS-based 16-bit systems"}, // amd16run.obf bios16run.obf
    {"bios32", "amd32", Amd32, false, "BIOS-based 32-bit systems"},
    {"bios64", "amd64", Amd64, false, "BIOS-based 64-bit systems"},
    {"dos", "amd16", Amd16, false, "DOS systems"},
    {"efi32", "amd32", Amd32, false, "EFI-based 32-bit systems"},
    {"efi64", "amd64", Amd64, false, "EFI-based 64-bit systems"},
    {"osx32", "amd32", Amd32, true, "32-bit OS X systems", "dbgdwarf"},
    {"osx64", "amd64", Amd64, true, "64-bit OS X systems", "dbgdwarf"},
    {"rpi2b", "arma32", Arma32, false, "Raspberry Pi 2 Model B"},
    {"win32", "amd32", Amd32, false, "32-bit Windows systems"},
    {"win64", "amd64", Amd64, false, "64-bit Windows systems"},
    {"amd16", "amd16", Amd16, false, "barebone x86 real mode"},
    {"amd32", "amd32", Amd32, false, "barebone x86 protected mode"},
    {"amd64", "amd64", Amd64, false, "barebone x86 long mode"},
    {"arma32", "arma32", Arma32, false, "barebone ARMv7"},
    {"armt32", "armt32", Armt32, false, "barebone ARMv7 thumb"},
    {"arma64", "arma64", Arma64, false, "barebone ARMv8"},
};

