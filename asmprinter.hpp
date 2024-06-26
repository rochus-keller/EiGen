// Generic assembly language pretty printer
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

#ifndef ECS_ASSEMBLY_PRINTER_HEADER_INCLUDED
#define ECS_ASSEMBLY_PRINTER_HEADER_INCLUDED

#include <iosfwd>
#include <vector>

namespace ECS {
    namespace Assembly {
        class Printer;

        struct Instruction;
        struct Program;

        using Instructions = std::vector<Instruction>;

        class Printer
        {
        public:
            void Print (const Program&, std::ostream&) const;
            void Print (const Instructions&, std::ostream&) const;

        private:
            class Context;
        };

    } // Assembly
} // ECS


#endif // ECS_ASSEMBLY_PRINTER_HEADER_INCLUDED
