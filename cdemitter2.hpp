// Generic intermediate code emitter
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

#ifndef ECS_CODE_EMITTER2_HEADER_INCLUDED
#define ECS_CODE_EMITTER2_HEADER_INCLUDED

#include "asmparser.hpp"
#include "cdchecker.hpp"
#include "code.hpp"

namespace ECS
{
	class Position;

    namespace Code
    {
        class Emitter2
        {
        public:
            Emitter2 (Diagnostics&, StringPool&, Charset&, Platform&, Sections &s);

            class Label;
            class RestoreRegisterState;
            class RestoreState;
            class SmartOperand;

            struct RegisterShortage final {};

            using Hint = Register;

            Section& BeginAssembly ();
            Section& Begin (Section::Type, const Section::Name&, Section::Alignment = 0, Section::Required = false,
                            Section::Duplicable = false, Section::Replaceable = false);

            void Alias (const Section::Name&);
            void Require (const Section::Name&);
            void Define (const Operand&);
            void Reserve (Size);

            void Move (const Operand&, const Operand&);
            SmartOperand Move (const Operand&, Hint = RVoid);
            void Convert (const Operand&, const Operand&);
            SmartOperand Convert (const Type&, const Operand&, Hint = RVoid);
            void Copy (const Operand&, const Operand&, const Operand&);
            void Fill (const Operand&, const Operand&, const Operand&);

            void Negate (const Operand&, const Operand&);
            SmartOperand Negate (const Operand&, Hint = RVoid);
            void Add (const Operand&, const Operand&, const Operand&);
            SmartOperand Add (const Operand&, const Operand&, Hint = RVoid);
            void Subtract (const Operand&, const Operand&, const Operand&);
            SmartOperand Subtract (const Operand&, const Operand&, Hint = RVoid);
            void Multiply (const Operand&, const Operand&, const Operand&);
            SmartOperand Multiply (const Operand&, const Operand&, Hint = RVoid);
            void Divide (const Operand&, const Operand&, const Operand&);
            SmartOperand Divide (const Operand&, const Operand&, Hint = RVoid);
            void Modulo (const Operand&, const Operand&, const Operand&);
            SmartOperand Modulo (const Operand&, const Operand&, Hint = RVoid);

            void Complement (const Operand&, const Operand&);
            SmartOperand Complement (const Operand&, Hint = RVoid);
            void And (const Operand&, const Operand&, const Operand&);
            SmartOperand And (const Operand&, const Operand&, Hint = RVoid);
            void Or (const Operand&, const Operand&, const Operand&);
            SmartOperand Or (const Operand&, const Operand&, Hint = RVoid);
            void ExclusiveOr (const Operand&, const Operand&, const Operand&);
            SmartOperand ExclusiveOr (const Operand&, const Operand&, Hint = RVoid);
            void ShiftLeft (const Operand&, const Operand&, const Operand&);
            SmartOperand ShiftLeft (const Operand&, const Operand&, Hint = RVoid);
            void ShiftRight (const Operand&, const Operand&, const Operand&);
            SmartOperand ShiftRight (const Operand&, const Operand&, Hint = RVoid);

            void SaveRegister (SmartOperand&);
            void RestoreRegister (SmartOperand&);

            void SaveRegisters (SmartOperand&, SmartOperand&);
            void RestoreRegisters (SmartOperand&, SmartOperand&);

            Size Push (Size);
            Size Push (const Operand&);
            void Pop (const Operand&);
            void Call (const Operand&, Size);
            SmartOperand Pop (const Type&, Hint = RVoid);
            SmartOperand Call (const Type&, const Operand&, Size);
            void Return ();
            void Enter (Size);
            void Leave ();

            Label CreateLabel ();
            void Branch (const Label&);
            void BranchEqual (const Label&, const Operand&, const Operand&);
            void BranchNotEqual (const Label&, const Operand&, const Operand&);
            void BranchLessThan (const Label&, const Operand&, const Operand&);
            void BranchGreaterEqual (const Label&, const Operand&, const Operand&);
            void Jump (const Operand&);

            void Assemble (const String&, Size, const String&);

            void Fix (const Operand&);
            void Unfix (const Operand&);

            SmartOperand Set (Label&, const Operand&, const Operand&, Hint = RVoid);
            SmartOperand Minimize (const Operand&, const Operand&, Hint = RVoid);

            void Locate (const Source&, const Position&);
            void Break (const Source&, const Position&);
            void Trap (Size);

            void DeclareSymbol (const Label&, const String&, const Operand&);
            void DeclareField (const String&, Size, const Operand&);
            void DeclareEnumerator (const String&, const Operand&);

            void DeclareVoid ();
            void DeclareType (const Operand&);
            void DeclareArray (Size, Size);
            void DeclareRecord (const Label&, Size);
            void DeclarePointer ();
            void DeclareReference ();
            void DeclareFunction (const Label&);
            void DeclareEnumeration (const Label&);

            void Increment (const Operand&, Pointer::Value);
            void Decrement (const Operand&, Pointer::Value);

            void Displace (SmartOperand&, Displacement);
            SmartOperand Displace (const Operand&, Displacement);
            SmartOperand Add (const Operand&, Displacement);
            SmartOperand Subtract (const Operand&, Displacement);

            SmartOperand Protect (const Operand&);
            SmartOperand Deprotect (const Operand&);

            SmartOperand MakeRegister (const Operand&, Hint = RVoid);
            SmartOperand AcquireRegister (const Type&, Hint = RVoid);
            SmartOperand MakeMemory (const Type&, const Operand&, Displacement = 0, Operand::Strict = false);

            void Comment (const char*);
            template <typename... Values> void Comment (const Position&, const Values&...);
            template <typename... Values> void Comment (const Source&, const Position&, const Values&...);

            template <typename String> void Define (const String&, const Type&);

            static Hint Reuse (const Operand&);
            static Hint Reuse (Hint, const Operand&);

        private:
            struct State
            {
                using Counters = Size[UserRegisters];

                String comment;
                Section* section = nullptr;
                std::vector<SmartOperand*> savedRegisters;
                Counters uses {}, fixes {}, protections {};
            };

            template <typename> struct LeftShift;
            template <typename> struct RightShift;

            State* current = &state;
            State state;

            void Save (SmartOperand&);

            SmartOperand ReuseRegister (const Operand&, const Type&, Hint);
            SmartOperand ReuseRegister (const Operand&, const Operand&, Hint);

            void Emit (const Instruction&);
            void Emit (Instruction::Mnemonic, Operand (*) (const Operand&), const Operand&, const Operand&);
            void Emit (Instruction::Mnemonic, Operand (*) (const Operand&, const Operand&), const Operand&,
                       const Operand&, const Operand&);

            SmartOperand Apply (Instruction::Mnemonic, Operand (*) (const Operand&), const Operand&, Hint);
            SmartOperand Apply (Instruction::Mnemonic, Operand (*) (const Operand&, const Operand&), const Operand&,
                                const Operand&, Hint);
            void Branch (Instruction::Mnemonic, bool (*) (const Operand&, const Operand&), const Label&, const Operand& = {},
                         const Operand& = {});

            void Patch (Instruction::Mnemonic, const Label&, const Operand& = {}, const Operand& = {});

            static constexpr Offset Indeterminate = 0;

            static Operand Evaluate (const Operand&, const Type&);
            template <typename, typename> static Operand Evaluate (const Operand&, const Type&);
            template <template <typename> class> static Operand Evaluate (const Operand&);
            template <template <typename> class> static Operand EvaluateIntegral (const Operand&);
            template <template <typename> class> static Operand Evaluate (const Operand&, const Operand&);
            template <template <typename> class> static Operand EvaluateIntegral (const Operand&, const Operand&);
            template <template <typename> class> static bool Compare (const Operand&, const Operand&);

            static bool IsSymbolDeclaration (const Instruction&);
            static bool HaveSameUserRegister (const Operand&, const Operand&);

            friend class SmartOperand;
        protected:
            Sections& sections;
            Diagnostics& diagnostics;
            Charset& charset;
            Platform& platform;
            const Reg stackPointer, framePointer, linkRegister;

        };

        class Emitter2::Label
        {
        public:
            Label () = default;
            Label (Label&&) noexcept;
            Label& operator = (Label&&) noexcept;
            ~Label ();

            void swap (Label&);

            void operator () ();

        private:
            using Offset = Instructions::size_type;

            explicit Label (Section&);

            Offset offset = Unknown;
            Section* section = nullptr;
            mutable std::vector<Offset> fixups;

            void Patch (Offset) const;

            static constexpr Offset Unknown = Offset (-1);

            friend class Emitter2;
        };
    }
}



#endif // ECS_CODE_EMITTER2_HEADER_INCLUDED
