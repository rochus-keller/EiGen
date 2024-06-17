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

#include "assembly.hpp"
#include "cdemitter2.hpp"
#include "charset.hpp"
#include "position.hpp"
#include "utilities.hpp"

#include <sstream>


#include <functional>

namespace ECS {
namespace Code {

class Emitter2::RestoreState
{
public:
    explicit RestoreState (Emitter2&);
    ~RestoreState ();

private:
    Emitter2& context;
    State*const previous;
    State state;
};

class Emitter2::RestoreRegisterState
{
public:
    explicit RestoreRegisterState (Emitter2&);
    ~RestoreRegisterState ();

private:
    Emitter2& context;
    std::vector<SmartOperand*> savedRegisters;
};


template <typename String>
Section::Name GetName (const String& string)
{
    std::ostringstream stream; WriteEscaped (stream << '$', string, '?'); return stream.str ();
}

inline void Emitter2::Comment (const char*const text)
{
    current->comment = text;
}

inline void send(std::ostringstream& out) {}

template <typename Value, typename ...Values>
void send(std::ostringstream& out, const Value& val, const Values&... values)
{
    out << val;
    send(out, values...);
}

template <typename... Values>
void Emitter2::Comment (const Position& position, const Values&... values)
{
    std::ostringstream stream;
    stream << "line " << GetLine (position) << ": ";
    using unused = int[];
    (void)unused { 0, (send(stream,values), 0)... };
    current->comment = stream.str ();
}

template <typename... Values>
void Emitter2::Comment (const Source& source, const Position& position, const Values&... values)
{
    std::ostringstream stream;
    stream << "file '" << source << "' line " << GetLine (position) << ": ";
    using unused = int[];
    (void)unused { 0, (send(stream,values), 0)... };
    current->comment = stream.str ();
}

template <typename String>
void Emitter2::Define (const String& string, const Type& type)
{
    for (auto character: string) Define (UImm {type, charset.Encode (character)});
    Define (UImm {type, charset.Encode (0)});
}

template <typename Value>
struct Emitter2::LeftShift
{
	Value operator () (const Value value1, const Value value2) {return ECS::ShiftLeft (value1, value2);}
};

template <typename Value>
struct Emitter2::RightShift
{
	Value operator () (const Value value1, const Value value2) {return ECS::ShiftRight (value1, value2);}
};

Emitter2::Emitter2 (Diagnostics& d, StringPool& sp, Charset& c, Platform& p, Sections& s) :
    diagnostics(d), charset(c), platform(p), stackPointer(p.pointer, RSP), framePointer(p.pointer, RFP),
    linkRegister(p.link, RLink), sections(s)
{
}

Section& Emitter2::Begin (const Section::Type type, const Section::Name& name, const Section::Alignment alignment,
                                  const Section::Required required, const Section::Duplicable duplicable,
                                  const Section::Replaceable replaceable)
{
    sections.emplace_back (type, name, alignment, required, duplicable, replaceable);
    current->section = &sections.back();
    if (!current->comment.empty ()) current->comment.swap (current->section->comment); return *current->section;
}

Section& Emitter2::BeginAssembly ()
{
	if (current->section && IsAssembly (*current->section)) return *current->section;
    sections.emplace_back ();
    current->section = &sections.back();
	if (!current->comment.empty ()) current->comment.swap (current->section->comment); return *current->section;
}

void Emitter2::Alias (const Section::Name& name)
{
	Emit (ALIAS {name});
}

void Emitter2::Require (const Section::Name& name)
{
	Emit (REQ {name});
}

void Emitter2::Define (const Operand& value)
{
	Emit (DEF {value});
}

void Emitter2::Reserve (const Size size)
{
	if (!size) return; auto& instructions = current->section->instructions;
    if (!instructions.empty () && instructions.back ().mnemonic == Instruction::RES)
        instructions.back ().operand1.size += size;
    else
        Emit (RES {size});
}

void Emitter2::Move (const Operand& target, const Operand& source)
{
    if (target == source)
        return;
    if (IsRegister (target) && HasRegister (source) && target.register_ == source.register_ &&
            !IsAddress (source) && !IsMemory (source))
        if (source.displacement < 0)
            return Decrement (target, -source.displacement);
        else
            return Increment (target, source.displacement);
	Emit (MOV {target, source});
}

Emitter2::SmartOperand Emitter2::Move (const Operand& value, const Hint hint)
{
    auto result = AcquireRegister (value.type, hint);
    Move (result, value);
    return result;
}

void Emitter2::Convert (const Operand& target, const Operand& source)
{
    if (target.type == source.type)
        return Move (target, source);
    if (IsImmediate (source))
        return Move (target, Evaluate (source, target.type));
	Emit (CONV {target, source});
}

Emitter2::SmartOperand Emitter2::Convert (const Type& type, const Operand& value, const Hint hint)
{
    if (IsImmediate (value))
        return Evaluate (value, type);
    auto result = ReuseRegister (value, type, hint);
    Convert (result, value);
    return result;
}

void Emitter2::Copy (const Operand& target, const Operand& source, const Operand& size)
{
    if (target == source || IsZero (size))
        return;
	Emit (COPY {target, source, size});
}

void Emitter2::Fill (const Operand& target, const Operand& size, const Operand& value)
{
    if (!IsImmediate (size) || size.ptrimm > 2)
        return Emit (FILL {target, size, value});
    auto destination = MakeRegister (target);
    for (PtrImm::Value index = 0; index != size.ptrimm; ++index)
        Move (MakeMemory (value.type, destination, index * value.type.size), value);
}

void Emitter2::Negate (const Operand& target, const Operand& value)
{
	Emit (Instruction::NEG, Evaluate<std::negate>, target, value);
}

Emitter2::SmartOperand Emitter2::Negate (const Operand& value, const Hint hint)
{
	return Apply (Instruction::NEG, Evaluate<std::negate>, value, hint);
}

void Emitter2::Add (const Operand& target, const Operand& value1, const Operand& value2)
{
    if (IsZero (value1) || IsZero (value2))
        return Move (target, Add (value1, value2));
    if (IsNegative (value1) && !IsNegative (Negate (value1)))
        return Subtract (target, value2, Negate (value1));
    if (IsNegative (value2) && !IsNegative (Negate (value2)))
        return Subtract (target, value1, Negate (value2));
	Emit (Instruction::ADD, Evaluate<std::plus>, target, value1, value2);
}

Emitter2::SmartOperand Emitter2::Add (const Operand& value1, const Operand& value2, const Hint hint)
{
    if (IsZero (value1))
        return {current->uses, value2};
    if (IsZero (value2))
        return {current->uses, value1};
    if (IsImmediate (value1) && IsPointer (value1.type))
        return Add (value2, value1.ptrimm);
    if (IsImmediate (value2) && IsPointer (value2.type))
        return Add (value1, value2.ptrimm);
    if (IsNegative (value1) && !IsNegative (Negate (value1)))
        return Subtract (value2, Negate (value1));
    if (IsNegative (value2) && !IsNegative (Negate (value2)))
        return Subtract (value1, Negate (value2));
    if (IsAddress (value1) && IsRegister (value2))
        return {current->uses, Adr {value1.type, value1.address, value2.register_, value1.displacement}};
    if (IsAddress (value2) && IsRegister (value1))
        return {current->uses, Adr {value2.type, value2.address, value1.register_, value2.displacement}};
	return Apply (Instruction::ADD, Evaluate<std::plus>, value1, value2, hint);
}

void Emitter2::Subtract (const Operand& target, const Operand& value1, const Operand& value2)
{
    if (IsZero (value1))
        return Negate (target, value2);
    if (IsZero (value2) || value1 == value2)
        return Move (target, Subtract (value1, value2));
    if (IsNegative (value2) && !IsNegative (Negate (value2)))
        return Add (target, value1, Negate (value2));
	Emit (Instruction::SUB, Evaluate<std::minus>, target, value1, value2);
}

Emitter2::SmartOperand Emitter2::Subtract (const Operand& value1, const Operand& value2, const Hint hint)
{
    if (IsZero (value1))
        return Negate (value2);
    if (IsZero (value2))
        return {current->uses, value1};
    if (value1 == value2)
        return Imm {value1.type, 0};
    if (IsImmediate (value2) && IsPointer (value2.type))
        return Subtract (value1, value2.ptrimm);
    if (IsNegative (value2) && !IsNegative (Negate (value2)))
        return Add (value1, Negate (value2));
	return Apply (Instruction::SUB, Evaluate<std::minus>, value1, value2, hint);
}

void Emitter2::Multiply (const Operand& target, const Operand& value1, const Operand& value2)
{
    if (IsZero (value1) || IsOne (value1) || IsZero (value2) || IsOne (value2))
        return Move (target, Multiply (value1, value2));
    if (IsMinusOne (value1))
        return Negate (target, value2);
    if (IsMinusOne (value2))
        return Negate (target, value1);
	Emit (Instruction::MUL, Evaluate<std::multiplies>, target, value1, value2);
}

Emitter2::SmartOperand Emitter2::Multiply (const Operand& value1, const Operand& value2, const Hint hint)
{
    if (IsZero (value1))
        return {current->uses, value1};
    if (IsOne (value1))
        return {current->uses, value2};
    if (IsMinusOne (value1))
        return Negate (value2);
    if (IsZero (value2))
        return {current->uses, value2};
    if (IsOne (value2))
        return {current->uses, value1};
    if (IsMinusOne (value2))
        return Negate (value1);
	return Apply (Instruction::MUL, Evaluate<std::multiplies>, value1, value2, hint);
}

void Emitter2::Divide (const Operand& target, const Operand& value1, const Operand& value2)
{
    if (IsZero (value1) || IsOne (value2) || value1 == value2)
        return Move (target, Divide (value1, value2));
    if (IsMinusOne (value2))
        return Negate (target, value1);
	Emit (Instruction::DIV, Evaluate<std::divides>, target, value1, value2);
}

Emitter2::SmartOperand Emitter2::Divide (const Operand& value1, const Operand& value2, const Hint hint)
{
    if (IsZero (value1))
        return {current->uses, value1};
    if (IsOne (value2))
        return {current->uses, value1};
    if (IsMinusOne (value2))
        return Negate (value1);
    if (value1 == value2)
        return Imm {value1.type, 1};
	return Apply (Instruction::DIV, Evaluate<std::divides>, value1, value2, hint);
}

void Emitter2::Modulo (const Operand& target, const Operand& value1, const Operand& value2)
{
    if (IsZero (value1) || IsOne (value2) || value1 == value2)
        return Move (target, Modulo (value1, value2));
	Emit (Instruction::MOD, EvaluateIntegral<std::modulus>, target, value1, value2);
}

Emitter2::SmartOperand Emitter2::Modulo (const Operand& value1, const Operand& value2, const Hint hint)
{
    if (IsZero (value1))
        return {current->uses, value1};
    if (IsOne (value2))
        return Imm {value1.type, 0};
    if (value1 == value2)
        return {current->uses, value1};
	return Apply (Instruction::MOD, EvaluateIntegral<std::modulus>, value1, value2, hint);
}

template<typename T>
struct bit_not {
    constexpr T operator()(const T& arg) const
    {
        return ~arg;
    }
};

void Emitter2::Complement (const Operand& target, const Operand& value)
{
    Emit (Instruction::NOT, EvaluateIntegral<bit_not>, target, value);
}

Emitter2::SmartOperand Emitter2::Complement (const Operand& value, const Hint hint)
{
    return Apply (Instruction::NOT, EvaluateIntegral<bit_not>, value, hint);
}

void Emitter2::And (const Operand& target, const Operand& value1, const Operand& value2)
{
    if (IsZero (value1) || IsFull (value1) || IsZero (value2) || IsFull (value2) || value1 == value2)
        return Move (target, And (value1, value2));
	Emit (Instruction::AND, EvaluateIntegral<std::bit_and>, target, value1, value2);
}

Emitter2::SmartOperand Emitter2::And (const Operand& value1, const Operand& value2, const Hint hint)
{
    if (IsZero (value1) || IsFull (value2))
        return {current->uses, value1};
    if (IsZero (value2) || IsFull (value1))
        return {current->uses, value2};
    if (value1 == value2)
        return {current->uses, value1};
	return Apply (Instruction::AND, EvaluateIntegral<std::bit_and>, value1, value2, hint);
}

void Emitter2::Or (const Operand& target, const Operand& value1, const Operand& value2)
{
    if (IsZero (value1) || IsFull (value1) || IsZero (value2) || IsFull (value2) || value1 == value2)
        return Move (target, Or (value1, value2));
	Emit (Instruction::OR, EvaluateIntegral<std::bit_or>, target, value1, value2);
}

Emitter2::SmartOperand Emitter2::Or (const Operand& value1, const Operand& value2, const Hint hint)
{
    if (IsZero (value1) || IsFull (value2))
        return {current->uses, value2};
    if (IsZero (value2) || IsFull (value1))
        return {current->uses, value1};
    if (value1 == value2)
        return {current->uses, value1};
	return Apply (Instruction::OR, EvaluateIntegral<std::bit_or>, value1, value2, hint);
}

void Emitter2::ExclusiveOr (const Operand& target, const Operand& value1, const Operand& value2)
{
    if (IsZero (value1) || IsZero (value2) || value1 == value2)
        return Move (target, ExclusiveOr (value1, value2));
	Emit (Instruction::XOR, EvaluateIntegral<std::bit_xor>, target, value1, value2);
}

Emitter2::SmartOperand Emitter2::ExclusiveOr (const Operand& value1, const Operand& value2, const Hint hint)
{
    if (IsZero (value1))
        return {current->uses, value2};
    if (IsZero (value2))
        return {current->uses, value1};
    if (value1 == value2)
        return Imm {value1.type, 0};
	return Apply (Instruction::XOR, EvaluateIntegral<std::bit_xor>, value1, value2, hint);
}

void Emitter2::ShiftLeft (const Operand& target, const Operand& value1, const Operand& value2)
{
    if (IsZero (value2))
        return Move (target, ShiftLeft (value1, value2));
	Emit (Instruction::LSH, EvaluateIntegral<LeftShift>, target, value1, value2);
}

Emitter2::SmartOperand Emitter2::ShiftLeft (const Operand& value1, const Operand& value2, const Hint hint)
{
    if (IsZero (value2))
        return {current->uses, value1};
	return Apply (Instruction::LSH, EvaluateIntegral<LeftShift>, value1, value2, hint);
}

void Emitter2::ShiftRight (const Operand& target, const Operand& value1, const Operand& value2)
{
    if (IsZero (value2))
        return Move (target, ShiftRight (value1, value2));
	Emit (Instruction::RSH, EvaluateIntegral<RightShift>, target, value1, value2);
}

Emitter2::SmartOperand Emitter2::ShiftRight (const Operand& value1, const Operand& value2, const Hint hint)
{
    if (IsZero (value2))
        return {current->uses, value1};
	return Apply (Instruction::RSH, EvaluateIntegral<RightShift>, value1, value2, hint);
}

void Emitter2::SaveRegister (SmartOperand& operand)
{
    if (HasRegister (operand) && IsUser (operand.register_))
        current->savedRegisters.push_back (&operand);
}

void Emitter2::Save (SmartOperand& operand)
{
    assert (HasRegister (operand));
    assert (IsUser (operand.register_));
    if (operand.saved)
        return;
    Push (IsMemory (operand) ?
              Reg {platform.pointer, operand.register_} :
              Reg {operand.type, operand.register_});
    operand.saved = true;
}

void Emitter2::RestoreRegister (SmartOperand& operand)
{
    if (!HasRegister (operand) || !IsUser (operand.register_))
        return; assert (!current->savedRegisters.empty ());
    assert (current->savedRegisters.back () == &operand);
    current->savedRegisters.pop_back ();
    if (!operand.saved)
        return;
    operand.ReplaceRegister (IsMemory (operand) ? Pop (platform.pointer) : Pop (operand.type));
    operand.saved = false;
}

void Emitter2::SaveRegisters (SmartOperand& first, SmartOperand& second)
{
    SaveRegister (first);
    if (!HaveSameUserRegister (first, second))
        SaveRegister (second);
}

void Emitter2::RestoreRegisters (SmartOperand& first, SmartOperand& second)
{
    if (HaveSameUserRegister (first, second))
        RestoreRegister (first), second.ReplaceRegister (first);
    else
        RestoreRegister (second), RestoreRegister (first);
}

Size Emitter2::Push (const Size size)
{
    assert (platform.IsStackAligned (size));
    Decrement (stackPointer, size);
    return size;
}

Size Emitter2::Push (const Operand& operand)
{
    Emit (PUSH(operand));
    return platform.GetStackSize (operand.type);
}

void Emitter2::Pop (const Operand& target)
{
    Emit (POP(target));
}

Emitter2::SmartOperand Emitter2::Pop (const Type& type, const Hint hint)
{
    auto result = AcquireRegister (type, hint);
    Pop (result);
    return result;
}

void Emitter2::Call (const Operand& target, const Size size)
{
	Emit (CALL {target, size});
}

Emitter2::SmartOperand Emitter2::Call (const Type& type, const Operand& target, const Size size)
{
    Call (target, size);
    return {current->uses, Reg {type, RRes}};
}

void Emitter2::Return ()
{
	Emit (RET {});
}

void Emitter2::Enter (const Size size)
{
	Emit (ENTER {size});
}

void Emitter2::Leave ()
{
	Emit (LEAVE {});
}

Emitter2::Label Emitter2::CreateLabel ()
{
    assert (current->section);
    return Label {*current->section};
}

void Emitter2::Branch (const Label& label)
{
	Branch (Instruction::BR, nullptr, label);
}

void Emitter2::BranchEqual (const Label& label, const Operand& value1, const Operand& value2)
{
    if (value1 == value2)
        return Branch (label);
	Branch (Instruction::BREQ, Compare<std::equal_to>, label, value1, value2);
}

void Emitter2::BranchNotEqual (const Label& label, const Operand& value1, const Operand& value2)
{
    if (value1 == value2)
        return;
	Branch (Instruction::BRNE, Compare<std::not_equal_to>, label, value1, value2);
}

void Emitter2::BranchLessThan (const Label& label, const Operand& value1, const Operand& value2)
{
	Branch (Instruction::BRLT, Compare<std::less>, label, value1, value2);
}

void Emitter2::BranchGreaterEqual (const Label& label, const Operand& value1, const Operand& value2)
{
	Branch (Instruction::BRGE, Compare<std::greater_equal>, label, value1, value2);
}

void Emitter2::Jump (const Operand& target)
{
	Emit (JUMP {target});
}

void Emitter2::Locate (const Source& source, const Position& position)
{
	Emit (LOC {source, Size (GetLine (position)), Size (GetColumn (position))});
}

void Emitter2::Break (const Source& source, const Position& position)
{
    Emit (BREAK {});
    Locate (source, position);
}

void Emitter2::Trap (const Size code)
{
	Emit (TRAP {code});
}

void Emitter2::DeclareSymbol (const Label& lifetime, const String& name, const Operand& value)
{
	Patch (Instruction::SYM, lifetime, name, value);
}

void Emitter2::DeclareField (const String& name, const Size offset, const Operand& mask)
{
	Emit (FIELD {name, offset, mask});
}

void Emitter2::DeclareEnumerator (const String& name, const Operand& value)
{
	Emit (VALUE {name, value});
}

void Emitter2::DeclareVoid ()
{
	Emit (VOID {});
}

void Emitter2::DeclareType (const Operand& operand)
{
	Emit (TYPE {operand});
}

void Emitter2::DeclareArray (const Size index, const Size size)
{
	Emit (ARRAY {index, size});
}

void Emitter2::DeclareRecord (const Label& extent, const Size size)
{
	Patch (Instruction::REC, extent, size);
}

void Emitter2::DeclarePointer ()
{
	Emit (PTR {});
}

void Emitter2::DeclareReference ()
{
	Emit (REF {});
}

void Emitter2::DeclareFunction (const Label& extent)
{
	Patch (Instruction::FUNC, extent);
}

void Emitter2::DeclareEnumeration (const Label& extent)
{
	Patch (Instruction::ENUM, extent);
}

void Emitter2::Assemble (const String& source, const Size line, const String& code)
{
	Emit (ASM {source, line, code});
}

void Emitter2::Fix (const Operand& operand)
{
    assert (IsRegister (operand));
    if (!IsUser (operand.register_))
        return;
    if (!current->fixes[operand.register_]++)
        Emit (FIX {operand});
}

void Emitter2::Unfix (const Operand& operand)
{
    assert (IsRegister (operand));
    if (!IsUser (operand.register_))
        return; assert (current->fixes[operand.register_]);
    if (!--current->fixes[operand.register_])
        Emit (UNFIX {operand});
}

Emitter2::SmartOperand Emitter2::Protect (const Operand& operand)
{
	return {current->protections, operand};
}

Emitter2::SmartOperand Emitter2::Deprotect (const Operand& operand)
{
	return {current->uses, operand};
}

Emitter2::SmartOperand Emitter2::MakeRegister (const Operand& operand, const Hint hint)
{
    if (IsRegister (operand))
        return {current->uses, operand};
    auto register_ = ReuseRegister (operand, operand.type, hint);
    Move (register_, operand);
    return register_;
}

Emitter2::SmartOperand Emitter2::MakeMemory (const Type& type, const Operand& operand,
                                                         const Displacement displacement, const Operand::Strict strict)
{
    return {current->uses, Mem {type, IsMemory (operand) ?
                        MakeRegister (operand) : operand,
                    displacement, strict}};
}

Emitter2::SmartOperand Emitter2::AcquireRegister (const Type& type, const Hint hint)
{
    if (hint != RVoid)
        return {current->uses, Reg {type, hint}};
    auto register_ = R0;
    while (register_ <= RMax && (current->uses[register_] || current->protections[register_]))
        register_ = Register (register_ + 1);
    if (register_ > RMax)
        throw RegisterShortage {};
    return {current->uses, Reg {type, register_}};
}

Emitter2::SmartOperand Emitter2::ReuseRegister (const Operand& operand, const Type& type, const Hint hint)
{
    if (hint != RVoid)
        return {current->uses, Reg {type, hint}};
    if (HasRegister (operand) && IsUser (operand.register_) && !current->protections[operand.register_])
        return {current->uses, Reg {type, operand.register_}};
	return AcquireRegister (type);
}

Emitter2::SmartOperand Emitter2::ReuseRegister (const Operand& operand1, const Operand& operand2,
                                                                const Hint hint)
{
	assert (operand1.type == operand2.type);
    if (hint != RVoid)
        return {current->uses, Reg {operand1.type, hint}};
    if (HasRegister (operand1) && IsUser (operand1.register_) && !current->protections[operand1.register_])
        return {current->uses, Reg {operand1.type, operand1.register_}};
    if (HasRegister (operand2) && IsUser (operand2.register_) && !current->protections[operand2.register_])
        return {current->uses, Reg {operand1.type, operand2.register_}};
	return AcquireRegister (operand1.type);
}

Emitter2::Hint Emitter2::Reuse (const Operand& operand)
{
	return HasRegister (operand) ? operand.register_ : RVoid;
}

Emitter2::Hint Emitter2::Reuse (const Hint hint, const Operand& operand)
{
	return Reuse (operand) != hint ? hint : RVoid;
}

void Emitter2::Increment (const Operand& target, const Pointer::Value value)
{
	Add (target, target, PtrImm {platform.pointer, value});
}

void Emitter2::Decrement (const Operand& target, const Pointer::Value value)
{
	Subtract (target, target, PtrImm {platform.pointer, value});
}

void Emitter2::Displace (SmartOperand& operand, const Displacement displacement)
{
	assert (IsMemory (operand) || IsPointer (operand.type));
    if (IsImmediate (operand))
        operand.ptrimm = Truncate (operand.ptrimm + displacement, operand.type.size * 8);
    else
        operand.displacement = Truncate (operand.displacement + displacement, platform.pointer.size * 8);
}

Emitter2::SmartOperand Emitter2::Displace (const Operand& operand, const Displacement displacement)
{
    SmartOperand result {current->uses, operand}; Displace (result, displacement);
    return result;
}

Emitter2::SmartOperand Emitter2::Add (const Operand& operand, const Displacement displacement)
{
	return Displace (IsMemory (operand) && displacement ? MakeRegister (operand) : operand, displacement);
}

Emitter2::SmartOperand Emitter2::Subtract (const Operand& operand, const Displacement displacement)
{
	return Displace (IsMemory (operand) && displacement ? MakeRegister (operand) : operand, -displacement);
}

Emitter2::SmartOperand Emitter2::Set (Label& skip, const Operand& value1, const Operand& value2,
                                                      const Hint hint)
{
    assert (value1.type == value2.type);
    auto end = CreateLabel ();
    auto result = MakeRegister (value1, hint);
    Fix (result);
    Branch (end);
    skip ();
    Move (result, value2);
    Unfix (result);
    end ();
    return result;
}

Emitter2::SmartOperand Emitter2::Minimize (const Operand& value1, const Operand& value2, const Hint hint)
{
    if (IsImmediate (value1) && IsImmediate (value2))
        return Compare<std::less> (value1, value2) ? value1 : value2;
    auto skip = CreateLabel ();
    auto result = Move (value1, hint), value = Move (value2, hint);
    Fix (result);
    BranchLessThan (skip, result, value);
    Move (result, value);
    Unfix (result);
    skip ();
    return result;
}

void Emitter2::EmitImp (const Instruction& instruction)
{
    assert (IsValid (instruction));
    assert (current->section);
	current->section->instructions.push_back (instruction);
    if (!current->comment.empty ())
        current->comment.swap (current->section->instructions.back ().comment);
}

void Emitter2::Emit (const Instruction& instruction)
{
    // default implementation; override to filter and compact
    EmitImp(instruction);
}

void Emitter2::Emit (const Instruction::Mnemonic mnemonic,
                             Operand (*const evaluate) (const Operand&), const Operand& target, const Operand& value)
{
    if (IsImmediate (value))
        return Move (target, evaluate (value));
	Emit ({mnemonic, target, value});
}

void Emitter2::Emit (const Instruction::Mnemonic mnemonic,
                             Operand (*const evaluate) (const Operand&, const Operand&),
                             const Operand& target, const Operand& value1, const Operand& value2)
{
	assert (value1.type == value2.type);
    if (IsImmediate (value1) && IsImmediate (value2))
        return Move (target, evaluate (value1, value2));
	Emit ({mnemonic, target, value1, value2});
}

Emitter2::SmartOperand Emitter2::Apply (const Instruction::Mnemonic mnemonic,
                            Operand (*const evaluate) (const Operand&), const Operand& value, const Hint hint)
{
    if (IsImmediate (value))
        return evaluate (value);
    auto result = ReuseRegister (value, value.type, hint);
    Emit (mnemonic, evaluate, result, value);
    return result;
}

Emitter2::SmartOperand Emitter2::Apply (const Instruction::Mnemonic mnemonic,
                                        Operand (*const evaluate) (const Operand&, const Operand&),
                                                        const Operand& value1, const Operand& value2, const Hint hint)
{
	assert (value1.type == value2.type);
    if (IsImmediate (value1) && IsImmediate (value2))
        return evaluate (value1, value2);
    auto result = ReuseRegister (value1, value2, hint);
    Emit (mnemonic, evaluate, result, value1, value2);
    return result;
}

void Emitter2::Branch (const Instruction::Mnemonic mnemonic,
                               bool (*const compare) (const Operand&, const Operand&),
                               const Label& label, const Operand& value1, const Operand& value2)
{
    assert (value1.type == value2.type);
    assert (label.section == current->section);
    if (IsImmediate (value1) && IsImmediate (value2))
        if (compare (value1, value2))
            return Branch (label);
        else
            return;
	Patch (mnemonic, label, value1, value2);
}

void Emitter2::Patch (const Instruction::Mnemonic mnemonic, const Label& label,
                              const Operand& value1, const Operand& value2)
{
    const Offset offset = label.offset == Label::Unknown ?
                label.fixups.push_back (current->section->instructions.size ()), Indeterminate :
                label.offset - current->section->instructions.size () - 1;
	Emit ({mnemonic, offset, value1, value2});
}

Operand Emitter2::Evaluate (const Operand& value, const Type& type)
{
	switch (type.model)
	{
    case Type::Signed:
        return Evaluate<SImm, Signed::Value> (value, type);
    case Type::Unsigned:
        return Evaluate<UImm, Signed::Value> (value, type);
    case Type::Float:
        return Evaluate<FImm, Float::Value> (value, type);
    case Type::Pointer:
        return Evaluate<PtrImm, Signed::Value> (value, type);
    case Type::Function:
        return Evaluate<FunImm, Signed::Value> (value, type);
    default:
        assert (Type::Unreachable);
	}
}

template <typename Immediate, typename FloatConversion>
Operand Emitter2::Evaluate (const Operand& value, const Type& type)
{
	switch (value.type.model)
	{
    case Type::Signed:
        return Immediate {type, Truncate<typename Immediate::Value> (value.simm, type.size * 8)};
    case Type::Unsigned:
        return Immediate {type, Truncate<typename Immediate::Value> (value.uimm, type.size * 8)};
    case Type::Float:
        return Immediate {type, Truncate<typename Immediate::Value> (FloatConversion (value.fimm), type.size * 8)};
    case Type::Pointer:
        return Immediate {type, Truncate<typename Immediate::Value> (value.ptrimm, type.size * 8)};
    case Type::Function:
        return Immediate {type, Truncate<typename Immediate::Value> (value.funimm, type.size * 8)};
    default:
        assert (Type::Unreachable);
	}
}

template <template <typename> class Unary>
Operand Emitter2::Evaluate (const Operand& value)
{
	if (value.type.model != Type::Float) return EvaluateIntegral<Unary> (value);
	return FImm {value.type, Truncate (Unary<Float::Value> {} (value.fimm), value.type.size * 8)};
}

template <template <typename> class Unary>
Operand Emitter2::EvaluateIntegral (const Operand& value)
{
	switch (value.type.model)
	{
	case Type::Signed: return SImm {value.type, Truncate (Unary<Signed::Value> {} (value.simm), value.type.size * 8)};
	case Type::Unsigned: return UImm {value.type, Truncate (Unary<Unsigned::Value> {} (value.uimm), value.type.size * 8)};
	default: assert (Type::Unreachable);
	}
}

template <template <typename> class Binary>
Operand Emitter2::Evaluate (const Operand& value1, const Operand& value2)
{
	if (value1.type.model != Type::Float) return EvaluateIntegral<Binary> (value1, value2);
	return FImm {value1.type, Truncate (Binary<Float::Value> {} (value1.fimm, value2.fimm), value1.type.size * 8)};
}

template <template <typename> class Binary>
Operand Emitter2::EvaluateIntegral (const Operand& value1, const Operand& value2)
{
	switch (value1.type.model)
	{
	case Type::Signed: return SImm {value1.type, Truncate (Binary<Signed::Value> {} (value1.simm, value2.simm), value1.type.size * 8)};
	case Type::Unsigned: return UImm {value1.type, Truncate (Binary<Unsigned::Value> {} (value1.uimm, value2.uimm), value1.type.size * 8)};
	case Type::Pointer: return PtrImm {value1.type, Truncate (Binary<Pointer::Value> {} (value1.ptrimm, value2.ptrimm), value1.type.size * 8)};
	default: assert (Type::Unreachable);
	}
}

template <template <typename> class Binary>
bool Emitter2::Compare (const Operand& value1, const Operand& value2)
{
	switch (value1.type.model)
	{
	case Type::Signed: return Binary<Signed::Value> {} (value1.simm, value2.simm);
	case Type::Unsigned: return Binary<Unsigned::Value> {} (value1.uimm, value2.uimm);
	case Type::Float: return Binary<Float::Value> {} (value1.fimm, value2.fimm);
	case Type::Pointer: return Binary<Pointer::Value> {} (value1.ptrimm, value2.ptrimm);
	case Type::Function: return Binary<Function::Value> {} (value1.funimm, value2.funimm);
	default: assert (Type::Unreachable);
	}
}

bool Emitter2::IsSymbolDeclaration (const Instruction& instruction)
{
	return instruction.mnemonic == Instruction::SYM && instruction.operand1.offset == Indeterminate;
}

bool Emitter2::HaveSameUserRegister (const Operand& first, const Operand& second)
{
	return HasRegister (first) && HasRegister (second) && first.register_ == second.register_ && IsUser (first.register_);
}

Emitter2::SmartOperand::SmartOperand (const Operand& operand) :
    Operand(operand)
{
	assert (!HasRegister (operand) || !IsUser (operand.register_));
}

Emitter2::SmartOperand::SmartOperand (State::Counters& c, const Operand& operand) :
    Operand(operand)
{
	if (HasRegister (operand) && IsUser (operand.register_)) counters = &c, ++(*counters)[register_];
}

Emitter2::SmartOperand::SmartOperand (const SmartOperand& operand) :
    Operand(operand), counters(operand.counters)
{
	if (counters) ++(*counters)[register_];
}

Emitter2::SmartOperand::SmartOperand (SmartOperand&& operand) noexcept :
    Operand(std::move (operand)), counters(operand.counters)
{
	operand.counters = nullptr;
}

Emitter2::SmartOperand::~SmartOperand ()
{
	if (counters) --(*counters)[register_];
}

Emitter2::SmartOperand& Emitter2::SmartOperand::operator = (const SmartOperand& operand)
{
	auto copy = operand; swap (copy); return *this;
}

Emitter2::SmartOperand& Emitter2::SmartOperand::operator = (SmartOperand&& operand) noexcept
{
	swap (operand); return *this;
}

void Emitter2::SmartOperand::ReplaceRegister (const SmartOperand& other)
{
	assert (HasRegister (*this)); assert (HasRegister (other));
	if (counters) --(*counters)[register_]; register_ = other.register_; if (counters) ++(*counters)[register_];
}

void Emitter2::SmartOperand::swap (SmartOperand& other)
{
	std::swap<Operand> (*this, other); std::swap (counters, other.counters);
}

Emitter2::Label::Label (Section& s) :
    section(&s)
{
}

Emitter2::Label::Label (Label&& label) noexcept :
    offset(label.offset), section(label.section), fixups(std::move (label.fixups))
{
	label.section = nullptr;
}

Emitter2::Label::~Label ()
{
    if (section /*&& !std::uncaught_exceptions ()*/)
        assert (offset != Unknown), assert (fixups.empty ());
}

Emitter2::Label& Emitter2::Label::operator = (Label&& label) noexcept
{
	swap (label); return *this;
}

void Emitter2::Label::swap (Label& other)
{
	std::swap (offset, other.offset);
	std::swap (section, other.section);
	fixups.swap (other.fixups);
}

void Emitter2::Label::operator () ()
{
	assert (section); assert (offset == Unknown);
	offset = section->instructions.size ();
	for (auto& fixup: fixups) Patch (fixup); fixups.clear ();
}

void Emitter2::Label::Patch (const Offset offset) const
{
	assert (offset < section->instructions.size ());
	auto& instruction = section->instructions[offset];
	assert (IsOffset (instruction.operand1));
	instruction.operand1.offset = this->offset - offset - 1;
	if (!IsBranching (instruction.mnemonic) || instruction.operand1.offset) return; instruction = NOP {};
	if (offset && section->instructions[offset - 1].mnemonic == Instruction::BREAK) section->instructions[offset - 1] = NOP {};
}

Emitter2::RestoreState::RestoreState (Emitter2& c) :
    context(c), previous(c.current)
{
	context.current = &state;
}

Emitter2::RestoreState::~RestoreState ()
{
	context.current = previous;
}

Emitter2::RestoreRegisterState::RestoreRegisterState (Emitter2& c) :
    context(c)
{
	savedRegisters.swap (context.current->savedRegisters);
	for (auto operand: savedRegisters) context.Save (*operand);
}

Emitter2::RestoreRegisterState::~RestoreRegisterState ()
{
	savedRegisters.swap (context.current->savedRegisters);
}

} // Code
} // ECS
