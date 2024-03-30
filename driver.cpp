// Generic driver
// Copyright (C) Florian Negele

// This file is part of the Eigen Compiler Suite.

// The ECS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// The ECS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with the ECS.  If not, see <https://www.gnu.org/licenses/>.

#include "driver.hpp"
#include <stdio.h>
#if defined(_WIN32) && !defined(__GNUC__)
  #include <direct.h>
#else
  #include <sys/stat.h>
#endif
using namespace ECS;

static inline std::string replace_extension(const std::string &source, const std::string &extension)
{
    const size_t pos = source.find_last_of(".");
    std::string res;
    if( pos < 0 )
        res = source;
    else
        res = source.substr(0, pos);

    if( !extension.empty() )
        res += extension;
    return res;
}

bool File::is_directory( const std::string& path )
{
    struct stat path_stat;
    stat(path.c_str(), &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

ECS::File::File (const std::string &source, const std::string &extension, const std::ios_base::openmode mode) :
    path {replace_extension(source,extension)}, file {path, mode}
{
    if (!file.is_open ())
        throw ProcessAborted {Format ("failed to open output file '%0'", path)};
}

ECS::File::~File () noexcept (false)
{
    file.close ();
    if (!file ) // || std::uncaught_exceptions ())
        ::remove (path.c_str());
    //if (!file && !std::uncaught_exceptions ())
    //    throw ProcessAborted {Format ("failed to write output file '%0'", path)};
}

int ECS::Drive (void (*const process) (std::istream&, const Source&, const Position&),
                const char*const name, const int argc, const char*const argv[],
                StreamDiagnostics& diagnostics, void (*const complete) (const Source&)) noexcept
{
try
{
    std::ios_base::sync_with_stdio (false);

    auto first = argv[argc];
    for (auto argument = argv + 1; argument < argv + argc; ++argument)
    {
        if (!*argument)
            continue;
        if (!first)
            first = *argument;
        const Source source {*argument};
        std::ifstream file;
        if (!File::is_directory (source))
            file.open (source, file.binary);
        if (!file.is_open ())
            throw ProcessAborted {Format ("failed to open input file '%0'", source)};
        process (file, source, {file, source, 1, 1});
    }

    if (!first)
    {
        std::cout << name << " Version 0.0.40 Build " __DATE__ " Copyright (C) Florian Negele\n"
        "This is free software; see the source for copying conditions. There is NO\n"
        "WARRANTY; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";
        process (std::cin, first = "stdin", {1, 1}); std::cin.clear ();
    }

    if (complete) complete (first);

    return EXIT_SUCCESS;
}
catch (const ErrorLimit& error)
{
    return diagnostics.Emit (Diagnostics::Note, name, {}, Format ("exiting after %0 errors", error.messages)), EXIT_FAILURE;
}
catch (const InvalidInput& error)
{
    return diagnostics.Emit (Diagnostics::Error, error.source, {}, error.message), EXIT_FAILURE;
}
catch (const ProcessFailed& error)
{
    return diagnostics.Emit (Diagnostics::Error, name, {}, error.message), EXIT_FAILURE;
}
catch (const ProcessAborted& error)
{
    return diagnostics.Emit (Diagnostics::FatalError, name, {}, error.message), EXIT_FAILURE;
}
catch (const std::system_error&)
{
    return diagnostics.Emit (Diagnostics::FatalError, name, {}, "system error"), EXIT_FAILURE;
}
catch (const std::length_error&)
{
    return diagnostics.Emit (Diagnostics::FatalError, name, {}, "out of memory"), EXIT_FAILURE;
}
catch (const std::bad_alloc&)
{
    return diagnostics.Emit (Diagnostics::FatalError, name, {}, "out of memory"), EXIT_FAILURE;
}
catch (const Error&)
{
    return EXIT_FAILURE;
}
}
