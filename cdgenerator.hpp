// Intermediate code generator
// Copyright (C) Florian Negele

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
// along with the ECS.  If not, see <https://www.gnu.org/licenses/>.

#ifndef ECS_CODE_GENERATOR_HEADER_INCLUDED
#define ECS_CODE_GENERATOR_HEADER_INCLUDED

#include "code.hpp"
#include "stdlayout.hpp"

namespace ECS
{
	using Source = std::string;

namespace Code
{
    class Generator
    {
    public:
    #if 1
        StandardLayout layout;
    #else
        Layout layout {{4, 1, 4}, {8, 4, 4}, 4, 4, {0, 4, 8}, true};
    #endif
        Platform platform {layout};

        void Generate (const Sections&, const Source&, std::ostream&) const;

    private:
        void Generate (const Section&, std::ostream&) const;
        void Generate (const Instruction&, Size, std::ostream&) const;
    };
}
}


#endif // ECS_CODE_GENERATOR_HEADER_INCLUDED
