// Object file linker
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

#include "charset.hpp"
#include "diagnostics.hpp"
#include "error.hpp"
#include "format.hpp"
#include "objlinker.hpp"
#include "position.hpp"
#include "utilities.hpp"

#include <map>

namespace ECS {
namespace Object {

struct Linker::Block
{
	enum Placement {Fixed, Header, InitData, InitCode, EntryPoint, Code, Const, Data, Trailer};

	using Entry = std::pair<const Binary::Name, Reference>;

	const Binary& binary;
	const Placement placement;
	Entry*const group;

	Offset address = 0, index = 0;
	bool replaced = false, used = false, referenced = false;

	Block (const Binary&, Entry*);

	bool operator < (const Block&) const;

	Placement GetPlacement (const Binary&);
};

struct Linker::Reference
{
	bool isGroup = false;
	Block* block = nullptr;

	union
	{
		Offset offset;
		struct {Size size; Offset count;} group;
	};

	Reference ();
	Reference (Block*, Offset);
};

class Linker::Context
{
public:
	Context (const Linker&, Arrangement&, Arrangement&, Arrangement&);

	void Process (const Binaries&);

private:
	const Linker& linker;

	Block* currentBlock;
	std::list<Block> blocks;
	std::set<Binary::Name> unresolved;
	const Block* previousCode = nullptr;
    Offset values[Patch::Count + 1];
	Arrangement* arrangements[Section::Trailer + 1];
	std::map<Binary::Name, Linker::Reference> directory;

	bool IsRequired (const Binary::Name&) const;
    void EmitError /*[[noreturn]]*/ (const Binary::Name&, const Message&) const;

	void Use (Block&);
	void Link (Block&);
	void Arrange (Block&);
	void Reference (Block&);
	void Add (const Binary&);
	void Enter (const Alias&);
    void patch (const struct Link&);
	void Touch (const struct Link&);
	void Apply (const struct Patch&);
	void Reset (const struct Patch&);
	void Resolve (const struct Link&);
    void patch (Offset, const Pattern&, Offset);
	void Replace (Block&, const Linker::Reference&);
};

Linker::Linker (Diagnostics& d) :
    diagnostics (d)
{
}

void Linker::Combine (Binaries& binaries) const
{
	for (auto binary = binaries.begin (); binary != binaries.end (); ++binary)
		if (binary->duplicable) for (auto duplicate = std::next (binary); duplicate != binaries.end ();)
			if (*duplicate == *binary) duplicate = binaries.erase (duplicate); else ++duplicate;
}

void Linker::Link (const Binaries& binaries, Arrangement& arrangement) const
{
    Context ctx(*this, arrangement, arrangement, arrangement);
    ctx.Process (binaries);
}

void Linker::Link (const Binaries& binaries, Arrangement& code, Arrangement& data) const
{
    Context ctx(*this, code, data, data);
    ctx.Process (binaries);
}

void Linker::Link (const Binaries& binaries, Arrangement& code, Arrangement& data, Arrangement& const_) const
{
    Context ctx(*this, code, data, const_);
    ctx.Process (binaries);
}

Offset ByteArrangement::Allocate (const Binary& binary, const Size size)
{
	if (layout.empty () && binary.fixed && binary.origin) layout.insert ({0, (placement = origin = binary.origin) - 1});
	const auto begin = binary.fixed ? binary.origin : size ? NextFit (size, binary.alignment) : Align (origin + bytes.size (), binary.alignment), end = begin + binary.bytes.size ();
    if (end > begin) {
        const Range<Offset> range(begin, end - 1);
#if 0
        if (layout[range])
            return !binary.origin;
        layout.insert (range);
#else
        if( contains(layout,range) )
            return !binary.origin;
        insert(layout,range);
#endif
    }
	if (end - origin > bytes.size ()) bytes.resize (end - origin); if (!binary.fixed) placement = end; return begin;
}

Offset ByteArrangement::NextFit (const Size size, const Binary::Alignment alignment) const
{
	assert (size); auto address = Align (placement, alignment);
	for (auto& range: layout) if (address <= range.upper) if (address + size <= range.lower) break; else address = Align (range.upper + 1, alignment);
	return address;
}

Span<Byte> ByteArrangement::Designate (const Offset offset, const Size size)
{
	assert (offset >= origin); assert (offset - origin + size <= bytes.size ());
	return {&bytes[offset - origin], size};
}

Offset MappedByteArrangement::Allocate (const Binary& binary, const Size size)
{
	return map.emplace (ByteArrangement::Allocate (binary, size), binary)->offset;
}

Linker::Context::Context (const Linker& l, Arrangement& code, Arrangement& data, Arrangement& const_) :
    linker(l), arrangements{&code, &code, &code, &data, &const_, &const_, &const_}
{
}

void Linker::Context::EmitError (const Binary::Name& name, const Message& message) const
{
    linker.diagnostics.Emit (Diagnostics::Error, name, Position(), message); throw Error {};
}

bool Linker::Context::IsRequired (const Binary::Name& name) const
{
	Binary::Name::size_type begin = 0;
    for (auto next = name.find ('?'); next != name.npos; begin = next + 1, next = name.find ('?', begin)) {
        const auto entry = directory.find (name.substr (begin, next - begin));
        if (entry != directory.end () && entry->second.block->used) return true;
    }
    return begin == 0;
}

void Linker::Context::Process (const Binaries& binaries)
{
	Batch (binaries, [this] (const Binary& binary) {Add (binary);}); const auto entryPoint = directory.find (Section::EntryPoint);
	if (entryPoint == directory.end () || entryPoint->second.block->replaced) EmitError (Section::EntryPoint, "missing entry point");
	else if (entryPoint->second.offset || !IsEntryPoint (entryPoint->second.block->binary)) EmitError (entryPoint->first, "invalid entry point");
	Use (*entryPoint->second.block); for (auto& block: blocks) if (!block.replaced && block.binary.required) Use (block);
	Batch (blocks, [this] (Block& block) {if (block.used) Reference (block);});
	for (auto& block: blocks) if (block.used) Arrange (block);
	for (auto& block: blocks) if (block.used) Link (block);
}

void Linker::Context::Add (const Binary& binary)
{
    Block block(binary, binary.group.empty () ? nullptr : &*directory.insert ({binary.group, {}}).first);
	currentBlock = &*blocks.insert (std::upper_bound (blocks.begin (), blocks.end (), block), block);
    Enter ({binary.name, 0});
    for (auto& alias: binary.aliases)
      if (!currentBlock->replaced)
         Enter (alias);
	if (!block.group) return; if (!block.group->second.isGroup) EmitError (binary.group, "reserved group name");
	if (binary.fixed || block.group->second.block && block.placement != block.group->second.block->placement) EmitError (binary.name, "invalid group member");
	if (block.group->second.block && binary.alignment != block.group->second.block->binary.alignment) EmitError (binary.name, "invalid group member alignment");
	if (!currentBlock->replaced) block.group->second.block = currentBlock;
}

void Linker::Context::Enter (const Alias& alias)
{
	const auto result = directory.insert ({alias.name, {currentBlock, alias.offset}});
	if (result.second) return; auto& reference = result.first->second; if (reference.isGroup) EmitError (alias.name, "reserved group name");
	if (currentBlock->binary.replaceable && !reference.block->binary.replaceable)
		Replace (*currentBlock, reference);
	else if (reference.block->binary.replaceable && !currentBlock->binary.replaceable)
		Replace (*reference.block, reference), reference.block = currentBlock, reference.offset = alias.offset;
	else if (currentBlock->binary.duplicable || reference.block->binary.duplicable)
		if (currentBlock->binary == reference.block->binary && reference.block != currentBlock) Replace (*currentBlock, reference);
		else EmitError (alias.name, "unequal duplicate");
	else EmitError (alias.name, "duplicated section");
}

void Linker::Context::Replace (Block& block, const Linker::Reference& reference)
{
	assert (!block.replaced); block.replaced = true;
    const auto iterator = directory.find (block.binary.name);
    if (iterator != directory.end () && &iterator->second != &reference) directory.erase (iterator);
    for (auto& alias: block.binary.aliases) {
        const auto iterator = directory.find (alias.name);
        if (iterator != directory.end () && &iterator->second != &reference) directory.erase (iterator);
    }
}

void Linker::Context::Use (Block& block)
{
	if (block.used) return; block.used = true;
	for (auto& link: block.binary.links) Touch (link);
}

void Linker::Context::Touch (const struct Link& link)
{
	if (HasConditionals (link.name)) return;
    const auto entry = directory.find (link.name);
    if (entry != directory.end () && !entry->second.isGroup) Use (*entry->second.block);
}

void Linker::Context::Reference (Block& block)
{
	if (block.referenced) return; block.used = block.referenced = true;
	if (block.group) block.group->second.block = &block, block.group->second.group.size += block.binary.bytes.size ();
    const Restore<Block*> restoreBlock {currentBlock, &block}; Batch (block.binary.links, [this] (const struct Link& link) {Resolve (link);});
}

void Linker::Context::Resolve (const struct Link& link)
{
	const auto strippedName = StripConditionals (link.name, IsRequired (link.name));
	if (strippedName.empty ()) return; const auto entry = directory.find (strippedName);
	if (entry == directory.end ()) if (unresolved.insert (strippedName).second) EmitError (currentBlock->binary.name, Format ("unresolved symbol '%0'", strippedName)); else throw Error {};
	else if (!entry->second.isGroup) Reference (*entry->second.block);
}

void Linker::Context::Arrange (Block& block)
{
	block.address = arrangements[block.binary.type]->Allocate (block.binary, block.group ? block.group->second.group.size : block.binary.bytes.size ());
	if (block.binary.fixed && block.address != block.binary.origin) EmitError (block.binary.name, "invalid origin");
	if (block.address + block.binary.bytes.size () < block.address) EmitError (block.binary.name, "address space exhausted");
	if (previousCode && previousCode->binary.bytes.empty ()) EmitError (previousCode->binary.name, Format ("empty %0 section", previousCode->binary.type));
	if (previousCode && block.placement < Block::Code && !block.binary.fixed && (previousCode->address + previousCode->binary.bytes.size ()) % block.binary.alignment)
		EmitError (previousCode->binary.name, Format ("padding code for aligned section '%0'", block.binary.name));
	if (block.group) if (block.index = block.group->second.group.count++, !block.group->second.block->address) block.group->second.block = &block;
	if (IsCode (block.binary.type)) previousCode = &block;
}

void Linker::Context::Link (Block& block)
{
	if (!block.binary.bytes.empty ()) std::copy (block.binary.bytes.begin (), block.binary.bytes.end (), arrangements[block.binary.type]->Designate (block.address, block.binary.bytes.size ()).begin ());
    currentBlock = &block; for (auto& link: block.binary.links) patch (link);
}

void Linker::Context::patch (const struct Link& link)
{
	const auto strippedName = StripConditionals (link.name, IsRequired (link.name));
	if (strippedName.empty ()) {for (auto& patch: link.patches) Reset (patch); return;}
	const auto entry = directory.find (strippedName); assert (entry != directory.end ());
	if (!entry->second.isGroup) values[Patch::Absolute] = entry->second.block->address + entry->second.offset, values[Patch::Size] = entry->second.block->binary.bytes.size () - entry->second.offset;
	else if (entry->second.block->used) values[Patch::Absolute] = entry->second.block->address, values[Patch::Size] = entry->second.group.size; else EmitError (entry->first, "empty group");
	values[Patch::Position] = entry->second.block->group ? entry->second.block->address + entry->second.offset - entry->second.block->group->second.block->address : 0;
	values[Patch::Index] = entry->second.block->index; values[Patch::Count] = entry->second.isGroup ? entry->second.group.count : 0;
	values[Patch::Extent] = values[Patch::Absolute] + values[Patch::Size];
	for (auto& patch: link.patches) Apply (patch);
}

void Linker::Context::Apply (const struct Patch& patch_)
{
    if (patch_.mode != Patch::Relative) patch (Scale (values[patch_.mode] + patch_.displacement, patch_.scale), patch_.pattern, patch_.offset);
    else patch (Scale (Patch::Displacement (values[Patch::Absolute] - currentBlock->address - patch_.offset) + patch_.displacement, patch_.scale), patch_.pattern, patch_.offset);
}

void Linker::Context::Reset (const struct Patch& patch_)
{
    patch (Scale (patch_.displacement, patch_.scale), patch_.pattern, patch_.offset);
}

void Linker::Context::patch (const Offset value, const Pattern& pattern, const Offset offset)
{
	assert (offset < currentBlock->binary.bytes.size ());
	pattern.Patch (value, arrangements[currentBlock->binary.type]->Designate (currentBlock->address + offset, currentBlock->binary.bytes.size () - offset));
}

Linker::Block::Block (const Binary& b, Entry*const g) :
    binary(b), placement(GetPlacement (binary)), group(g)
{
}

bool Linker::Block::operator < (const Block& other) const
{
	if (placement != other.placement) return placement < other.placement;
	if (placement == Fixed) return binary.origin < other.binary.origin;
	if (!group != !other.group) return group;
	if (group && group->first != other.group->first) return group->first < other.group->first;
	return binary.bytes.empty () && !other.binary.bytes.empty ();
}

Linker::Block::Placement Linker::Block::GetPlacement (const Binary& binary)
{
	if (binary.fixed) return Fixed;
	if (IsEntryPoint (binary)) return EntryPoint;
	if (binary.type == Binary::Header) return Header;
	if (binary.type == Binary::Trailer) return Trailer;
	if (binary.type == Binary::InitData) return InitData;
	if (binary.type == Binary::InitCode) return InitCode;
	if (binary.type == Binary::Code) return Code;
	if (binary.type == Binary::Const) return Const;
	return Data;
}

Linker::Reference::Reference () :
    isGroup(true), group{0, 0}
{
}

Linker::Reference::Reference (Block*const b, const Offset o) :
    block(b), offset(o)
{
	assert (block);
}

std::ostream& WriteBinary (std::ostream& stream, const Bytes& bytes)
{
	return stream.write (reinterpret_cast<const char*> (bytes.data ()), std::streamsize (bytes.size ()));
}

std::string GetContents (const Binary::Name& name, const Binaries& binaries, Charset& charset, const char*const defaultValue)
{
	for (auto& binary: binaries) if (binary.type == Binary::Const && binary.name == name && !binary.replaceable && binary.links.empty ())
		{std::string value; for (char character: binary.bytes) value.push_back (charset.Decode (character)); return value;}
	return defaultValue;
}

} // Object
} // ECS
