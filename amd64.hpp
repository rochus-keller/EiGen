// AMD64 instruction set representation
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

#ifndef ECS_AMD64_HEADER_INCLUDED
#define ECS_AMD64_HEADER_INCLUDED

#include <cstddef>
#include <cstdint>
#include <iosfwd>

namespace ECS {

    template <typename> class Span;

    using Byte = std::uint8_t;

    namespace Object
    {
        struct Patch;
    }

namespace AMD64 {

	enum OperatingMode : unsigned {RealMode = 16, ProtectedMode = 32, LongMode = 64};

	enum Register {RVoid,
		#define REG(reg, name) reg,
		#include "amd64.def"
	};

	class Instruction;
	class Mem;
	class Operand;

	using Immediate = std::int64_t;

	bool IsEmpty (const Operand&);
	bool IsValid (const Instruction&);

	auto GetSize (const Instruction&) -> std::size_t;

	std::istream& operator >> (std::istream&, Instruction&);
	std::istream& operator >> (std::istream&, Operand&);
	std::istream& operator >> (std::istream&, Register&);
	std::ostream& operator << (std::ostream&, const Instruction&);
	std::ostream& operator << (std::ostream&, const Operand&);
	std::ostream& operator << (std::ostream&, Register);

    class Operand
    {
    public:
        enum Size {Default = 0, Byte = 1, Word = 2, DWord = 4, QWord = 8, OWord = 16, HWord = 32};

        using Index = AMD64::Register;
        using Scale = unsigned;
        using Segment = AMD64::Register;

        Operand () = default;
        Operand (AMD64::Register);
        Operand (AMD64::Immediate, Size = Default);

        enum Model {Empty, Immediate, Register, Memory};
        const Size& getSize() const { return size; }
        const Model& getModel() const { return model; }
        const AMD64::Register& getRegister() const { return register_; }
    protected:

        Model model = Empty;
        Size size = Default;
        AMD64::Register segment = RVoid, register_ = RVoid, index = RVoid;
        Scale scale = 0;
        AMD64::Immediate immediate = 0;

        Operand (Size, Segment, AMD64::Register, Index, Scale, AMD64::Immediate);

    private:
        class Format;

        static const char*const sizes[];
        static const char*const registers[];

        friend class Instruction;
        friend bool IsEmpty (const Operand&);
        friend std::istream& operator >> (std::istream&, Operand&);
        friend std::istream& operator >> (std::istream&, AMD64::Register&);
        friend std::ostream& operator << (std::ostream&, Size);
        friend std::ostream& operator << (std::ostream&, AMD64::Register);
        friend std::ostream& operator << (std::ostream&, const Operand&);
    };

    class Mem : public Operand
    {
    public:
        explicit Mem (AMD64::Immediate, Size = Default, Segment = RVoid);
        explicit Mem (AMD64::Register, AMD64::Immediate = 0, Size = Default, Segment = RVoid);
        Mem (AMD64::Register, Index, Scale = 1, AMD64::Immediate = 0, Size = Default, Segment = RVoid);
    };

    class Instruction
    {
    public:
        enum Mnemonic : std::uint16_t {
            #define MNEM(name, mnem, ...) mnem,
            #include "amd64.def"
            Count,
        };

        enum Prefix {NoPrefix, Locked, Rep, Repne};

        explicit Instruction (OperatingMode);
        Instruction (OperatingMode, Span<const Byte>);
        Instruction (OperatingMode, Mnemonic, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {});
        Instruction (OperatingMode, Prefix, Mnemonic, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {});

        void Emit (Span<Byte>) const;
        void Adjust (Object::Patch&) const;

    private:
        struct Fixup {std::size_t offset, size; bool relative;};

        OperatingMode mode;
        Prefix prefix;
        Mnemonic mnemonic;
        Operand operand1, operand2, operand3, operand4;
        std::size_t size = 0;
        Byte code[16];
        Fixup fixup;

        static const char*const prefixes[];
        static const char*const mnemonics[];

        friend class Operand::Format;
        friend bool IsValid (const Instruction&);
        friend std::size_t GetSize (const Instruction&);
        friend std::istream& operator >> (std::istream&, Instruction&);
        friend std::ostream& operator << (std::ostream&, Prefix);
        friend std::ostream& operator << (std::ostream&, Mnemonic);
        friend std::ostream& operator << (std::ostream&, const Instruction&);
    };

    template <Instruction::Mnemonic> struct InstructionMnemonic;

    #define MNEM(name, mnem, ...) using mnem = InstructionMnemonic<Instruction::mnem>;
    #include "amd64.def"

    std::ostream& operator << (std::ostream&, Instruction::Mnemonic);
    std::ostream& operator << (std::ostream&, Instruction::Prefix);
    std::ostream& operator << (std::ostream&, Operand::Size);


    template <Instruction::Mnemonic>
    struct InstructionMnemonic : Instruction
    {
        explicit InstructionMnemonic (OperatingMode, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {});

        template <Instruction::Prefix> struct Prefixed;

        using LOCK = Prefixed<Locked>;
        using REP = Prefixed<Rep>;
        using REPNE = Prefixed<Repne>;
    };

    template <Instruction::Mnemonic m> template <Instruction::Prefix>
    struct InstructionMnemonic<m>::Prefixed : Instruction
    {
        explicit Prefixed (OperatingMode, const Operand& = {}, const Operand& = {}, const Operand& = {}, const Operand& = {});
    };

    inline bool IsEmpty (const Operand& operand)
    {
        return operand.model == Operand::Empty;
    }

    inline bool IsValid (const Instruction& instruction)
    {
        return instruction.size != 0;
    }

    inline Instruction::Instruction (const OperatingMode om, const Mnemonic m, const Operand& o1, const Operand& o2, const Operand& o3, const Operand& o4) :
        Instruction {om, NoPrefix, m, o1, o2, o3, o4}
    {
    }

    template <Instruction::Mnemonic m>
    inline InstructionMnemonic<m>::InstructionMnemonic (const OperatingMode om, const Operand& o1, const Operand& o2, const Operand& o3, const Operand& o4) :
        Instruction {om, NoPrefix, m, o1, o2, o3, o4}
    {
    }

    template <Instruction::Mnemonic m> template <Instruction::Prefix p>
    inline InstructionMnemonic<m>::Prefixed<p>::Prefixed (const OperatingMode om, const Operand& o1, const Operand& o2, const Operand& o4, const Operand& o3) :
        Instruction {om, p, m, o1, o2, o3, o4}
    {
    }


} // AMD64
} // ECS


#endif // ECS_AMD64_HEADER_INCLUDED
