// Generic assembly language representation
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

#ifndef ECS_ASSEMBLY_HEADER_INCLUDED
#define ECS_ASSEMBLY_HEADER_INCLUDED

#include "asmlexer.hpp"

namespace ECS {
namespace Assembly {

	struct Expression;
	struct Instruction;
	struct Program;
	struct Section;

	using Directive = Lexer::Symbol;
	using Expressions = std::list<Expression>;
	using Instructions = std::vector<Instruction>;
	using Sections = std::list<Section>;

	bool IsConditional (Directive);
	bool IsGroup (const Expression&);
	bool IsIdentifier (const Expression&);
	bool IsIdentity (const Expression&);
	bool IsLabel (const Expression&);
	bool IsNumber (const Expression&);
	bool IsParenthesized (const Expression&);
	bool IsString (const Expression&);

	std::ostream& operator << (std::ostream&, const Expression&);
	std::ostream& operator << (std::ostream&, const Expressions&);

    struct Expression
    {
        enum Model {Label, Number, Character, String, Address, Identity, Identifier,
                    NullaryOperation, UnaryOperation, BinaryOperation, PostfixOperation,
                    FunctionalOperation, Parenthesized, Unreachable = 0};

        using Operation = Lexer::Symbol;
        using Value = std::uint64_t;

        Model model;

        union
        {
            Value value;
            Operation operation;
            Lexer::Symbol parenthesis;
        };

        Assembly::String string;
        Expressions operands;
        bool separated = false;

        Expression () = default;
        Expression (Model, Value);
        Expression (Model, const Assembly::String&);
    };

    struct Instruction
    {
        Location location;
        Directive directive;
        Identifier label, mnemonic;
        Expressions operands;

        explicit Instruction (const Location&);
    };

    struct Section : Object::Section
    {
        Instructions instructions;

        using Object::Section::Section;
    };

    struct Program
    {
        Source source;
        Sections sections;

        explicit Program (const Source&);
    };

} // Assembly
} // ECS



#endif // ECS_ASSEMBLY_HEADER_INCLUDED
