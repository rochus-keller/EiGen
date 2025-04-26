// M68000 machine code generator
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

#ifndef ECS_M68K_GENERATOR_HEADER_INCLUDED
#define ECS_M68K_GENERATOR_HEADER_INCLUDED

#include "asmgenerator.hpp"
#include "m68kassembler.hpp"

namespace ECS
{
namespace M68K
{
	class Generator;

class Generator : public Assembly::Generator
{
public:
	Generator (Diagnostics&, StringPool&, Charset&);

private:
	class Context;

	Assembler assembler;

	void Process (const Code::Sections&, Object::Binaries&, Debugging::Information&, std::ostream&) const override;
};

} // M68K
} // ECS

#endif // ECS_M68K_GENERATOR_HEADER_INCLUDED
