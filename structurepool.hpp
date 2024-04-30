// Generic structure pool
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

#ifndef ECS_STRUCTUREPOOL_HEADER_INCLUDED
#define ECS_STRUCTUREPOOL_HEADER_INCLUDED

#include <utility>

namespace ECS
{
class StructurePool
{
public:
    StructurePool () = default;
    StructurePool (StructurePool&&) noexcept;
    StructurePool& operator = (StructurePool&&) noexcept;
    ~StructurePool ();

    template <typename Structure, typename... Arguments> Structure& Create (Arguments&&...);
    template <typename Structure, typename... Arguments> void Create (Structure*&, Arguments&&...);

private:
    struct BasicNode;
    template <typename> struct Node;

    BasicNode* first = nullptr;
};

struct StructurePool::BasicNode
{
    BasicNode*const next;

    explicit BasicNode (BasicNode*);
    virtual ~BasicNode () = default;
};

template <typename Structure>
struct StructurePool::Node : BasicNode
{
    Structure structure;

    template <typename... Arguments> explicit Node (BasicNode*, Arguments&&...);
};

inline StructurePool::StructurePool (StructurePool&& pool) noexcept :
    first {pool.first}
{
    pool.first = nullptr;
}

inline StructurePool& StructurePool::operator = (StructurePool&& pool) noexcept
{
    std::swap (first, pool.first); return *this;
}

inline StructurePool::~StructurePool ()
{
    while (const auto node = first) first = node->next, delete node;
}

template <typename Structure, typename... Arguments>
inline Structure& StructurePool::Create (Arguments&&... arguments)
{
    const auto node = new Node<Structure> (first, std::forward<Arguments> (arguments)...); first = node; return node->structure;
}

template <typename Structure, typename... Arguments>
inline void StructurePool::Create (Structure*& structure, Arguments&&... arguments)
{
    structure = &Create<Structure> (std::forward<Arguments> (arguments)...);
}

inline StructurePool::BasicNode::BasicNode (BasicNode*const n) :
    next {n}
{
}

template <typename Structure> template <typename... Arguments>
inline StructurePool::Node<Structure>::Node (BasicNode*const next, Arguments&&... arguments) :
    BasicNode(next), structure(std::forward<Arguments> (arguments)...)
{
}
}



#endif // ECS_STRUCTUREPOOL_HEADER_INCLUDED
