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
#include <string.h>

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

#if 0
    // TODO
    if( target.debug_info )
    {
        Debugging::DWARFConverter converter(diagnostics, charset);
        Object::Binaries dbfobj;
        converter.Convert (information, program.source, dbfobj);
        ECS::File dbf_file {path, ".dbf"};
        dbf_file << dbfobj;
        // TODO register_for_cleanup(dbf_file.getPath().c_str(),1);
    }
#endif

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
#include "target.h"
#include "panic.h"
#include "driver_t.h"
#include "hostdetect.h"

void run_codegen(const char *input, const char *output)
{
    try
    {
    Assembly::Program program{input};
    Assembly::Parser parser {diagnostics, stringPool, true};
    std::ifstream file;
    file.open (input, file.binary);
    if (!file.is_open ())
        std::cerr << "failed to open input file " << input << std::endl, throw "";
    parser.Parse (file, GetLine (Position(file, input, 1, 1)), program);

    const char* backend = target_data[target.target].backend;
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
        std::cerr << "no generator available for " << backend << std::endl;
    }catch(...)
    {
        // already reported
        std::cerr << "error generating code for " << input << std::endl;
    }
}

#if defined Q_OS_LINUX || defined Q_OS_UNIX
#include <sys/stat.h>
#endif

void run_linker(compilation_unit_t* inputs, const char *output)
{
    try
    {
    Object::Linker linker(diagnostics);
    Object::Binaries binaries;

    std::deque<std::string> paths;
    std::deque<std::string> libs;
    bool linkLib = false;

    for( struct _obstack_chunk* c = ldflags_obst.chunk; c; c = c->prev )
    {
        const std::string data(c->contents + 1);
        if( data == "-lib" )
        {
            linkLib = true;
            continue;
        }
        if( data.size() < 2 || data[0] != '-' || ( data[1] != 'L' && data[1] != 'l' ) )
            continue;
        if( data[1] == 'L' )
            paths.push_back(&data[2]);
        else
            libs.push_back(&data[2]);
    }

    // add internal libs
    if( !linkLib && target.target > NoTarget && target.target <= Win64 )
    {
        std::string lib = target_data[target.target].name;
        lib += "run.obf";
        libs.push_back(lib);
#if 1
        // apparently not required, but includes things like floor, sqrt, putchar etc.
        lib = target_data[target.target].backend;
        lib += "run.obf";
        libs.push_back(lib);
#endif
    }

    for (compilation_unit_t *unit = units; unit != NULL; unit = unit->next) {
        if (unit->type != COMPILATION_UNIT_OBJECT)
            continue;

        std::ifstream file;
        file.open (unit->name, file.binary);
        if (!file.is_open ())
            panic("failed to open input file '%s'", unit->name);
        file >> binaries;
        if (!file)
            panic("invalid object file: %s", unit->name);
    }

#if 0
    // TODO
    if( target.debug_info )
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
#endif

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
                panic("invalid object file: %s", path.c_str());
            else
                found = true;
            break;
        }
        if( !found )
            panic("could not find library: %s", libs[i].c_str());
    }

    std::string path = output;
    if( target.target >= BareAmd16 && target.target <= BareArmA64)
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
