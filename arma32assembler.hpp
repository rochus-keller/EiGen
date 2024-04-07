// ARM A32 assembler
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

#ifndef ECS_ARM_A32_ASSEMBLER_HEADER_INCLUDED
#define ECS_ARM_A32_ASSEMBLER_HEADER_INCLUDED

#include "asmassembler.hpp"

namespace ECS { namespace ARM { namespace A32
{
    class Assembler : public Assembly::Assembler
    {
    public:
        Assembler (Diagnostics&, Charset&);

    protected:
        using Assembly::Assembler::Assembler;

        Size GetDisplacement (Size, BitMode) const override;
        Size ParseInstruction (std::istream&, BitMode, State&) const override;
        Size EmitInstruction (std::istream&, BitMode, Endianness, Span<Byte>, Object::Patch&, State&) const override;
    };
}}}


#endif // ECS_ARM_A32_ASSEMBLER_HEADER_INCLUDED
