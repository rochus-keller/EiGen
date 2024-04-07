// Intermediate code semantic checker
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

#ifndef ECS_CODE_CHECKER_HEADER_INCLUDED
#define ECS_CODE_CHECKER_HEADER_INCLUDED

#include "asmchecker.hpp"

#include <list>
#include <vector>

namespace ECS {

    namespace Assembly
    {
        struct Instruction;
        struct Program;
        struct Section;

        using Instructions = std::vector<Instruction>;
    }

    namespace Code
    {
        class Platform;

        struct Section;
        struct Type;

        using Sections = std::list<Section>;

        class Checker : Assembly::Checker
        {
        public:
            Checker (Diagnostics&, Charset&, Platform&);

            void Check (const Assembly::Program&, Sections&) const;
            void Check (const Assembly::Instructions&, Section&) const;

        private:
            class Context;

            Platform& platform;

            void Check (const Assembly::Section&, Sections&) const;
        };
    }

} // ECS



#endif // ECS_CODE_CHECKER_HEADER_INCLUDED
