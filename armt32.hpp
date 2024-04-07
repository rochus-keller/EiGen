// ARM T32 instruction set representation
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

#ifndef ECS_ARM_T32_HEADER_INCLUDED
#define ECS_ARM_T32_HEADER_INCLUDED

#include "arm.hpp"

#include <array>

namespace ECS { namespace ARM { namespace T32
{
	class Instruction;
	class Operand;

	bool IsValid (const Instruction&);
	bool IsValid (Immediate);

	auto GetSize (const Instruction&) -> std::size_t;
	auto GetConditionCode (const Instruction&) -> ConditionCode;

	std::istream& operator >> (std::istream&, Instruction&);
	std::ostream& operator << (std::ostream&, const Instruction&);

    class Operand : public ARM::Operand
    {
    public:
        using ARM::Operand::Operand;

    private:
        enum Type {Void,
            #define TYPE(type) type,
            #include "armt32.def"
        };

        Opcode Encode (Type) const;
        bool Decode (Opcode, Type);
        bool IsCompatibleWith (Type) const;

        static Opcode Encode (ARM::Immediate);
        static ARM::Immediate Decode (Opcode);

        friend class Instruction;
        friend bool IsValid (ARM::Immediate);
        friend ARM::ConditionCode GetConditionCode (const Instruction&);
    };

    class Instruction : public ARM::Instruction
    {
    public:
        explicit Instruction (ConditionCode);
        Instruction (Span<const Byte>, ConditionCode);
        Instruction (Mnemonic, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {});
        Instruction (Mnemonic, ConditionCode, Qualifier, Suffix, ConditionCode, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {});

        void Emit (Span<Byte>) const;
        void Adjust (Object::Patch&) const;

    private:
        struct Entry;

        const Entry* entry = nullptr;
        std::array<Operand, 6> operands;
        ConditionCode code;

        static const Entry table[];
        static const Lookup<Entry, Mnemonic> first, last;

        friend bool IsValid (const Instruction&);
        friend std::size_t GetSize (const Instruction&);
        friend ConditionCode GetConditionCode (const Instruction&);
        friend std::istream& operator >> (std::istream&, Instruction&);
        friend std::ostream& operator << (std::ostream&, const Instruction&);
    };

    template <Instruction::Mnemonic> struct InstructionMnemonic;

    #define MNEM(name, mnem, ...) using mnem = InstructionMnemonic<Instruction::mnem>;
    #include "arm.def"

    template <Instruction::Mnemonic>
    struct InstructionMnemonic : Instruction
    {
        explicit InstructionMnemonic (const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {});
        explicit InstructionMnemonic (ConditionCode, Qualifier, Suffix, ConditionCode, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {});
    };

    inline bool IsValid (const Instruction& instruction)
    {
        return instruction.entry;
    }

    template <Instruction::Mnemonic m>
    inline InstructionMnemonic<m>::InstructionMnemonic (const Operand& op0, const Operand& op1, const Operand& op2, const Operand& op3, const Operand& op4, const Operand& op5) :
        Instruction {m, No, Default, None, No, op0, op1, op2, op3, op4, op5}
    {
    }

    template <Instruction::Mnemonic m>
    inline InstructionMnemonic<m>::InstructionMnemonic (const ConditionCode c, const Qualifier q, const Suffix s, const ConditionCode p, const Operand& op0, const Operand& op1, const Operand& op2, const Operand& op3, const Operand& op4, const Operand& op5) :
        Instruction {m, c, q, s, p, op0, op1, op2, op3, op4, op5}
    {
    }
}}} // ECS:ARM:T32



#endif // ECS_ARM_T32_HEADER_INCLUDED
