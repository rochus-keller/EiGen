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

using namespace ECS;

static ASCIICharset charset;
static StringPool stringPool;
static StreamDiagnostics diagnostics {std::cerr};

static void generate(const Assembly::Program& program, Assembly::Generator& generator, const char* output)
{
    Code::Sections sections;
    Code::Checker checker {diagnostics, charset, generator.platform};
    checker.Check (program, sections);

    Object::Binaries binaries;
    Debugging::Information information;
    std::ostream listing {nullptr};
    generator.Generate (sections, program.source, binaries, information, listing);
    ECS::File object( output, "" );
    object << binaries;
}

static void generate_amd16(const Assembly::Program& program, const char* output)
{
    AMD64::Generator generator {diagnostics, stringPool, charset, AMD64::RealMode, false, true};
    generate(program, generator, output);
}

static void generate_amd32(const Assembly::Program& program, const char* output)
{
    AMD64::Generator generator {diagnostics, stringPool, charset, AMD64::ProtectedMode, true, true};
    // RK: was false, true
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
    Assembly::Program program{input};
    Assembly::Parser parser {diagnostics, stringPool, true};
    std::ifstream file;
    file.open (input, file.binary);
    if (!file.is_open ())
        error("failed to open input file '%s'", input);
    parser.Parse (file, GetLine (Position(file, input, 1, 1)), program);

    // TODO: catch exceptions
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
}

void run_linker(StringArray *inputs, StringArray *extra_args, const char *output)
{
    // TODO
}

}
