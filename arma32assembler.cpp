// ARM A32 assembler
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

#include "arma32.hpp"
#include "arma32assembler.hpp"
#include "utilities.hpp"

using namespace ECS;
using namespace ARM;
using namespace A32;

Assembler::Assembler (Diagnostics& d, Charset& c) :
    Assembly::Assembler(d, c, 4, 4, 1, Endianness::Little, 32)
{
}

Assembler::Size Assembler::GetDisplacement (const Size, const BitMode) const
{
	return 8;
}

Assembler::Size Assembler::ParseInstruction (std::istream& stream, const BitMode, State&) const
{
	Instruction instruction;
	return stream >> instruction && IsValid (instruction) ? 4 : 0;
}

Assembler::Size Assembler::EmitInstruction (std::istream& stream, const BitMode, const Endianness, const Span<Byte> bytes, Object::Patch& patch, State&) const
{
	Instruction instruction;
	const Size size = stream >> instruction && IsValid (instruction) ? 4 : 0;
	if (size && size <= bytes.size ()) instruction.Emit (bytes), instruction.Adjust (patch);
	return size;
}
