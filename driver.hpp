// Generic driver
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

#ifndef ECS_DRIVER_HEADER_INCLUDED
#define ECS_DRIVER_HEADER_INCLUDED

#include "strdiagnostics.hpp"
#include "error.hpp"
#include "format.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <system_error>

namespace ECS
{
	struct InvalidInput final {Source source; Message message;};
	struct ProcessAborted final {Message message;};
	struct ProcessFailed final {Message message;};

    int Drive (void (*) (std::istream&, const Source&, const Position&), const char*, int,
               const char*const [], StreamDiagnostics&, void (*) (const Source&) = nullptr) noexcept;

    class File
    {
    public:
        File (const std::string&, const std::string&, std::ios_base::openmode = std::ios_base::out);
        ~File () noexcept (false);

        operator std::ostream& () {return file;}

        static constexpr auto cur = std::ios_base::cur;
        static constexpr auto binary = std::ios_base::binary;

        static bool is_directory(const std::string&);
        const std::string& getPath() const { return path; }
        static std::string replace_extension(const std::string &source, const std::string &extension);
    private:
        const std::string path;
        std::ofstream file;
    };
}

#endif // ECS_DRIVER_HEADER_INCLUDED
