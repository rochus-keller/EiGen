// Generic compiler driver
// Copyright (C) Florian Negele (original author)

// This file is derivative work of the Eigen Compiler Suite.
// See https://github.com/rochus-keller/EiGen for more information.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#include "debugging.hpp"
#include "driver.hpp"
#include "stdcharset.hpp"
#include "stringpool.hpp"
#include "cdgenerator.hpp"

using namespace ECS;

static ASCIICharset charset;
static StringPool stringPool;
static StreamDiagnostics diagnostics {std::cerr};

#if defined CODEBACKEND
    // CODEBACKEND can optionally be declared together with one of AMD32BACKEND, AMD64BACKEND
    // ARMA32BACKEND or ARMA64BACKEND to generate IR compatible with the corresponding cdamd32,
    // cdamd64, cdarma32 or cdarma64 code generator; by default the standard layout of the
    // machine, where this code is compiled, is used.

	#define NAMESUFFIX "code"
#if defined AMD32BACKEND
    static Layout l { {4, 1, 4}, {8, 4, 4}, 4, 4, {0, 4, 4}, true };
    static Code::Platform p {l, false};
    static Code::Generator generator(l, p);
#elif defined AMD64BACKEND
    static Layout l { {4, 1, 8}, {8, 4, 8}, 8, 8, {0, 4, 8}, true };
    static Code::Platform p {l, false};
    static Code::Generator generator(l, p);
#elif defined ARMA32BACKEND
    static const bool floatingPointExtension = true;
    static Layout l { {4, 1, 8}, {floatingPointExtension ? 8u : 4u, 4, 4}, 4, 4, {0, 4, 4}, true };
    static Code::Platform p {l, true};
    static Code::Generator generator(l, p);
#elif defined ARMA64BACKEND
    static Layout l { {4, 1, 8}, {8, 4, 8}, 8, 8, {0, 16, 16}, true };
    static Code::Platform p {l, true};
    static Code::Generator generator(l, p);
#else
    static Code::Generator generator; // using StandardLayout
#endif

#elif defined AMD16BACKEND

	#include "amd64.hpp"
	#include "amd64generator.hpp"

	#define NAMESUFFIX "amd16"
	static AMD64::Generator generator {diagnostics, stringPool, charset, AMD64::RealMode, false, true};

#elif defined AMD32BACKEND

	#include "amd64.hpp"
	#include "amd64generator.hpp"

	#define NAMESUFFIX "amd32"
    static AMD64::Generator generator {diagnostics, stringPool, charset, AMD64::ProtectedMode, true, true};
    // RK: was false, true
    // use media instead of legacy float instructions, see https://software.openbrace.org/boards/3/topics/44?r=60#message-60
    // speed-up is factor 10

#elif defined AMD64BACKEND

	#include "amd64.hpp"
	#include "amd64generator.hpp"

	#define NAMESUFFIX "amd64"
	static AMD64::Generator generator {diagnostics, stringPool, charset, AMD64::LongMode, true, true};

#elif defined ARMA32BACKEND

	#include "arma32generator.hpp"

	#define NAMESUFFIX "arma32"
	static ARM::A32::Generator generator {diagnostics, stringPool, charset, true};

#elif defined ARMA64BACKEND

	#include "arma64generator.hpp"

	#define NAMESUFFIX "arma64"
	static ARM::A64::Generator generator {diagnostics, stringPool, charset, false};

#elif defined ARMT32BACKEND

	#include "armt32generator.hpp"

	#define NAMESUFFIX "armt32"
	static ARM::T32::Generator generator {diagnostics, stringPool, charset, false};

#elif defined ARMT32FPEBACKEND

	#include "armt32generator.hpp"

	#define NAMESUFFIX "armt32fpe"
	static ARM::T32::Generator generator {diagnostics, stringPool, charset, true};

#elif defined AVRBACKEND

	#include "avrgenerator.hpp"

	#define NAMESUFFIX "avr"
	static AVR::Generator generator {diagnostics, stringPool, charset, 32 * 1024};

#elif defined AVR32BACKEND

	#include "avr32generator.hpp"

	#define NAMESUFFIX "avr32"
	static AVR32::Generator generator {diagnostics, stringPool, charset};

#elif defined M68KBACKEND

	#include "m68kgenerator.hpp"

	#define NAMESUFFIX "m68k"
	static M68K::Generator generator {diagnostics, stringPool, charset};

#elif defined MICROBLAZEBACKEND

	#include "miblgenerator.hpp"

	#define NAMESUFFIX "mibl"
	static MicroBlaze::Generator generator {diagnostics, stringPool, charset};

#elif defined MIPS32BACKEND

	#include "mips.hpp"
	#include "mipsgenerator.hpp"
	#include "utilities.hpp"

	#define NAMESUFFIX "mips32"
	static MIPS::Generator generator {diagnostics, stringPool, charset, MIPS::MIPS32, Endianness::Little, true, false};

#elif defined MIPS64BACKEND

	#include "mips.hpp"
	#include "mipsgenerator.hpp"
	#include "utilities.hpp"

	#define NAMESUFFIX "mips64"
	static MIPS::Generator generator {diagnostics, stringPool, charset, MIPS::MIPS64, Endianness::Little, true, true};

#elif defined MMIXBACKEND

	#include "mmixgenerator.hpp"

	#define NAMESUFFIX "mmix"
	static MMIX::Generator generator {diagnostics, stringPool, charset, false};

#elif defined OR1KBACKEND

	#include "or1kgenerator.hpp"

	#define NAMESUFFIX "or1k"
	static OR1K::Generator generator {diagnostics, stringPool, charset};

#elif defined POWERPC32BACKEND

	#include "ppc.hpp"
	#include "ppcgenerator.hpp"

	#define NAMESUFFIX "ppc32"
	static PowerPC::Generator generator {diagnostics, stringPool, charset, PowerPC::PPC32, false};

#elif defined POWERPC64BACKEND

	#include "ppc.hpp"
	#include "ppcgenerator.hpp"

	#define NAMESUFFIX "ppc64"
	static PowerPC::Generator generator {diagnostics, stringPool, charset, PowerPC::PPC64, false};

#elif defined RISCBACKEND

	#include "riscgenerator.hpp"

	#define NAMESUFFIX "risc"
	static RISC::Generator generator {diagnostics, stringPool, charset};

#elif defined WEBASSEMBLYBACKEND

	#include "wasmgenerator.hpp"

	#define NAMESUFFIX "wasm"
	static WebAssembly::Generator generator {diagnostics, stringPool, charset};

#else

	#error unknown back-end

#endif

static void Generate (const Code::Sections& sections, const Source& source)
{
	#if defined CODEBACKEND
		File file {source, ".cod"};
		generator.Generate (sections, source, file);
	#else
		Object::Binaries binaries;
		Debugging::Information information;

		#if defined ASSEMBLYLISTING
			File listing {source, ".lst"};
		#else
			std::ostream listing {nullptr};
		#endif

#if defined CODELISTING
        File cod {source, ".cod"};
        Code::Generator g { generator.layout, Code::Platform(generator.layout,generator.platform.link.size != 0) };
        g.Generate (sections, source, cod);
#endif

		generator.Generate (sections, source, binaries, information, listing);
		File object {source, ".obf"};
		object << binaries;

		#if defined DEBUGGINGINFORMATION
			File debugging {source, ".dbg"};
			debugging << information;
		#endif
	#endif
}

#if defined CODEFRONTEND

	#include "asmparser.hpp"
	#include "assembly.hpp"
	#include "cdchecker.hpp"

	#define NAMEPREFIX "cd"
	static Assembly::Parser parser {diagnostics, stringPool, true};
	static Code::Checker checker {diagnostics, charset, generator.platform};

	static void Emit (std::istream& stream, const Source& source, const Position& position, Code::Sections& sections)
	{
		Assembly::Program program {source};
		parser.Parse (stream, GetLine (position), program);
		checker.Check (program, sections);
	}

#elif defined CPPFRONTEND

	#include "cppemitter.hpp"
	#include "cppparser.hpp"
	#include "stringpool.hpp"

	#define NAMEPREFIX "cpp"
	static CPP::Platform platform {generator.layout};
	static CPP::Parser parser {diagnostics, stringPool, charset, platform, false};
	static CPP::Emitter emitter {diagnostics, stringPool, charset, generator.platform, platform};

	static void Emit (std::istream& stream, const Source& source, const Position& position, Code::Sections& sections)
	{
		CPP::TranslationUnit translationUnit {source};
		parser.Parse (stream, position, translationUnit);
		emitter.Emit (translationUnit, sections);
	}

#elif defined FALSEFRONTEND

	#include "falemitter.hpp"
	#include "falparser.hpp"
	#include "false.hpp"

	#define NAMEPREFIX "fal"
	static FALSE::Parser parser {diagnostics};
	static FALSE::Emitter emitter {diagnostics, stringPool, charset, generator.platform};

	static void Emit (std::istream& stream, const Source& source, const Position& position, Code::Sections& sections)
	{
		FALSE::Program program {source};
		parser.Parse (stream, position, program);
		emitter.Emit (program, sections);
	}

#elif defined OBERONFRONTEND

	#include "obchecker.hpp"
	#include "obemitter.hpp"
	#include "oberon.hpp"

	#define NAMEPREFIX "ob"
	static Oberon::Parser parser {diagnostics, false};
	static Oberon::Platform platform {generator.layout};
	static Oberon::Checker checker {diagnostics, charset, platform, true};
	static Oberon::Emitter emitter {diagnostics, stringPool, charset, generator.platform, platform};

	static void Emit (std::istream& stream, const Source& source, const Position& position, Code::Sections& sections)
	{
		Oberon::Module module {source};
		parser.Parse (stream, position, module);
		checker.Check (module);
		emitter.Emit (module, sections);
	}

#else

	#error unknown front-end

#endif

#if defined CODEOPTIMIZER

	#include "cdoptimizer.hpp"

	static Code::Optimizer optimizer {generator.platform};

#endif

static void Compile (std::istream& stream, const Source& source, const Position& position)
{
	Code::Sections sections;
	Emit (stream, source, position, sections);

	#if defined CODEOPTIMIZER
		optimizer.Optimize (sections);
	#endif

	Generate (sections, source);
}

int main (int argc, char* argv[])
{
	#if defined CPPFRONTEND
		parser.IncludeEnvironmentDirectories ();
		parser.Predefine (stringPool.Insert ("__" NAMESUFFIX "__"));
	#endif

	return Drive (Compile, NAMEPREFIX NAMESUFFIX, argc, argv, diagnostics);
}
