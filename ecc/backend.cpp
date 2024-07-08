extern "C" {
#include "chibicc.h"
}

#include "debugging.hpp"
#include "driver.hpp"
#include "stdcharset.hpp"
#include "stringpool.hpp"
#include "cdgenerator.hpp"
#include "amd64.hpp"
#include "amd64generator.hpp"
#include "arma64generator.hpp"
#include "armt32generator.hpp"
#include "arma32generator.hpp"
#include "asmparser.hpp"
#include "assembly.hpp"
#include "cdchecker.hpp"
#include "objlinker.hpp"
#include "dbgdwarfconverter.hpp"
#include <deque>

using namespace ECS;

static ASCIICharset charset;
static StringPool stringPool;
static StreamDiagnostics diagnostics {std::cerr};

static std::string extensionOf(const std::string& path)
{
    const size_t pos = path.find_last_of(".");
    std::string extension;
    if( pos != std::string::npos )
        extension = path.substr(pos);
    return extension;
}

static void generate(const Assembly::Program& program, Assembly::Generator& generator, const char* output)
{
    Code::Sections sections;
    Code::Checker checker {diagnostics, charset, generator.platform};
    checker.Check (program, sections);

    Object::Binaries binaries;
    Debugging::Information information;
    std::ostream listing {nullptr};
    generator.Generate (sections, program.source, binaries, information, listing);

    std::string path(output);

    if( debug_info )
    {
        Debugging::DWARFConverter converter(diagnostics, charset);
        Object::Binaries dbfobj;
        converter.Convert (information, program.source, dbfobj);
        ECS::File dbf_file {path, ".dbf"};
        dbf_file << dbfobj;
        register_for_cleanup(dbf_file.getPath().c_str(),1);
    }

    ECS::File object( path, extensionOf(path) ); // File constructor wants to replace the extension of path in any case, even if empty
    object << binaries;
}

static void generate_amd16(const Assembly::Program& program, const char* output)
{
    AMD64::Generator generator {diagnostics, stringPool, charset, AMD64::RealMode, false, true};
    generate(program, generator, output);
}

static void generate_amd32(const Assembly::Program& program, const char* output)
{
    AMD64::Generator generator {diagnostics, stringPool, charset, AMD64::ProtectedMode, true, true}; // RK: was false, true
    // use media instead of legacy float instructions, see https://software.openbrace.org/boards/3/topics/44?r=60#message-60
    // speed-up is factor 10
    generate(program, generator, output);
}

static void generate_amd64(const Assembly::Program& program, const char* output)
{
    AMD64::Generator generator {diagnostics, stringPool, charset, AMD64::LongMode, true, true};
    generate(program, generator, output);
}

static void generate_arma32(const Assembly::Program& program, const char* output)
{
    ARM::A32::Generator generator {diagnostics, stringPool, charset, true};
    generate(program, generator, output);
}

static void generate_arma64(const Assembly::Program& program, const char* output)
{
    ARM::A64::Generator generator {diagnostics, stringPool, charset, false};
    generate(program, generator, output);
}

static void generate_armt32(const Assembly::Program& program, const char* output)
{
    ARM::T32::Generator generator {diagnostics, stringPool, charset, false};
    generate(program, generator, output);
}

static void generate_armt32fpe(const Assembly::Program& program, const char* output)
{
    ARM::T32::Generator generator {diagnostics, stringPool, charset, true};
    generate(program, generator, output);
}

extern "C" {

void run_codegen(const char *input, const char *output)
{
    try
    {
    Assembly::Program program{input};
    Assembly::Parser parser {diagnostics, stringPool, true};
    std::ifstream file;
    file.open (input, file.binary);
    if (!file.is_open ())
        error("failed to open input file '%s'", input);
    parser.Parse (file, GetLine (Position(file, input, 1, 1)), program);

    const char* backend = targets[target].backend;
    if( strcmp(backend,"amd16") == 0 )
        generate_amd16(program,output);
    else if( strcmp(backend,"amd32") == 0 )
        generate_amd32(program,output);
    else if( strcmp(backend,"amd64") == 0 )
        generate_amd64(program,output);
    else if( strcmp(backend,"arma32") == 0 )
        generate_arma32(program,output);
    else if( strcmp(backend,"arma64") == 0 )
        generate_arma64(program,output);
    else if( strcmp(backend,"armt32") == 0 )
        generate_armt32(program,output);
    else if( strcmp(backend,"armt32fpe") == 0 )
        generate_armt32fpe(program,output);
    else
        error("no generator available for '%s'", backend);
    }catch(...)
    {
        // already reported
        error("error generating code for %s",base_file);
    }
}

#include "hostdetect.h"

#if defined Q_OS_LINUX || defined Q_OS_UNIX
#include <sys/stat.h>
#endif

void run_linker(StringArray *inputs, StringArray *extra_args, const char *output)
{
    try
    {
    Object::Linker linker(diagnostics);
    Object::Binaries binaries;

    std::deque<std::string> paths;
    std::deque<std::string> libs;
    bool linkLib = false;
    for (int i = 0; i < extra_args->len; i++)
    {
        const std::string path = extra_args->data[i];
        if( path == "-lib" )
        {
            linkLib = true;
            continue;
        }
        if( path.size() < 2 || path[0] != '-' || ( path[1] != 'L' && path[1] != 'l' ) )
            continue;
        i++;
        if( i >= extra_args->len )
            break;
        if( path[1] == 'L' )
            paths.push_back(extra_args->data[i]);
        else
            libs.push_back(extra_args->data[i]);
    }

    // add internal libs
    if( !linkLib && target > NoTarget && target <= Win64 )
    {
        std::string lib = targets[target].name;
        lib += "run.obf";
        libs.push_back(lib);
#if 0
        // apparently not required, but includes things like floor, sqrt, putchar etc.
        lib = targets[target].backend;
        lib += "run.obf";
        libs.push_back(lib);
#endif
    }

    for (int i = 0; i < inputs->len; i++)
    {
      std::ifstream file;
      file.open (inputs->data[i], file.binary);
      if (!file.is_open ())
          error("failed to open input file '%s'", inputs->data[i]);
      file >> binaries;
      if (!file)
          error("invalid object file: %s", inputs->data[i]);
    }

    if( debug_info )
    {
        for (int i = 0; i < inputs->len; i++)
        {
          std::ifstream dbfin;
          const std::string dbf = ECS::File::replace_extension(inputs->data[i],".dbf");
          dbfin.open (dbf, dbfin.binary);
          if (!dbfin.is_open ())
              error("failed to open input file '%s'", dbf.c_str());
          dbfin >> binaries;
          const int s = binaries.size();
          if (!dbfin)
              error("invalid object file: %s", dbf.c_str());
        }
    }

    for( int i = 0; i < libs.size(); i++ )
    {
        bool found = false;
        for( int j = 0; j < paths.size(); j++ )
        {
            std::string path = paths[j];
            if( path.empty() )
                continue;
            const char last = path[path.size()-1];
            if( last != '/' && last != '\\' )
                path += '/';
            path += libs[i];
            std::ifstream file;
            file.open(path, file.binary);
            if (!file.is_open ())
                continue;
            file >> binaries;
            if (!file)
                error("invalid object file: %s", path.c_str());
            else
                found = true;
            break;
        }
        if( !found )
            error("could not find library: %s", libs[i].c_str());
    }

    std::string path = output;
    if( target >= BareAmd16 && target <= BareArmA64)
    {
        Object::MappedByteArrangement ram, rom;
        linker.Link (binaries, rom, ram, rom);
        ECS::File ramfile {path, ".ram", ramfile.binary};
        Object::WriteBinary (ramfile, ram.bytes);
        ECS::File romfile {path, ".rom", romfile.binary};
        Object::WriteBinary (romfile, rom.bytes);
        ECS::File map {path, ".map"};
        map << ram.map << rom.map;
    }else if( linkLib )
    {
        linker.Combine (binaries);
        ECS::File library {path, ".lib"};
        library << binaries;
    }else
    {
        Object::MappedByteArrangement arrangement;
        linker.Link (binaries, arrangement);
        std::string ext = GetContents ("_extension", binaries, charset, ".bin");
        if( ext.empty() )
            ext = extensionOf(path);
        ECS::File file(path, ext, ECS::File::binary);
        Object::WriteBinary (file, arrangement.bytes);
#if defined Q_OS_LINUX || defined Q_OS_UNIX
        chmod(file.getPath().c_str (), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
#endif
#if 0
        // TODO: why do we need this?
        ECS::File map(output, ".map");
        map << arrangement.map;
#endif
    }
    }catch(...)
    {
        // already reported
    }
}

}
