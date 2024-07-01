// Generic debugging information converter context
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
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#ifndef ECS_DEBUGGING_CONVERTER_CONTEXT_HEADER_INCLUDED
#define ECS_DEBUGGING_CONVERTER_CONTEXT_HEADER_INCLUDED

#include "dbgconverter.hpp"
#include "debugging.hpp"
#include "object.hpp"

namespace ECS { namespace Debugging {

class Converter::Context
{
public:
	Context (const Converter&, const Information&, const Source&, Object::Binaries&);

protected:
	enum Size {Byte = 1, DByte = 2, TByte = 3, QByte = 4, OByte = 8};

    struct Block
    {
        Lifetime lifetime;
        std::vector<const Symbol*> symbols;
        std::list<Block> blocks;

        explicit Block (const Entry&);
        explicit Block (const Symbol&);

        void Insert (const Symbol&);
    };

	using Binary = Object::Binary;
	using Patch = Object::Patch;

	const Information& information;

	Binary* current = nullptr;

    void EmitError /*[[noreturn]]*/ (const Message&) const;

	void Begin (const Binary::Name&, Binary::Required = false, Binary::Replaceable = false);

	void Alias (const Binary::Name&);
	void Group (const Binary::Name&);
	void Require (const Binary::Name&);

	Object::Offset Emit (Size);
	void Fixup (Object::Offset, Size);

	void Emit (Value::Unsigned, Size);
	void Emit (const std::string&, Size);
	void Emit (const Binary::Name&, Patch::Mode, Patch::Displacement, Size);

	bool IsDefined (const Binary::Name&) const;

private:
	const Converter& converter;
	const Source& source;
	Object::Binaries& binaries;
};
}}

#endif // ECS_DEBUGGING_CONVERTER_CONTEXT_HEADER_INCLUDED
