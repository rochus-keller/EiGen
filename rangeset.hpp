// Range set utility
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

#ifndef ECS_RANGESET_HEADER_INCLUDED
#define ECS_RANGESET_HEADER_INCLUDED

#include <set>

namespace ECS
{
	template <typename> struct Range;

    template <typename Value> bool operator < (const Range<Value>&, const Range<Value>&);

    template <typename Value>
    struct Range
    {
        Value lower, upper;

        Range () = default;
        Range (const Value&);
        Range (const Value&, const Value&);

        bool operator [] (const Value&) const;
    };

#if 0
    // GCC 4.8: rangeset.hpp:47:12: internal compiler error: in gen_type_die_with_usage, at dwarf2out.c:19486 class ECS::RangeSet
    template <typename Value>
    class RangeSet
    {
    public:
        void insert (const Range<Value>&);
        bool operator [] (const Range<Value>&) const;

        auto begin () const {return set.begin ();}
        auto end () const {return set.end ();}
        auto empty () const {return set.empty ();}

    private:
        std::set<Range<Value>> set;

        static Value increment (Value value) {return ++value;}
    };
#else
    template<typename T>
    using RangeSet = std::set<Range<T>>;
#endif

    template <typename Value>
    Range<Value>::Range (const Value& v) :
        lower (v), upper (v)
    {
    }

    template <typename Value>
    Range<Value>::Range (const Value& l, const Value& u) :
        lower (l), upper (u)
    {
    }

    template <typename Value>
    bool Range<Value>::operator [] (const Value& value) const
    {
        return value >= lower && value <= upper;
    }

    template <typename Value>
    bool operator < (const Range<Value>& a, const Range<Value>& b)
    {
        return a.lower < b.lower;
    }

#if 0
    template <typename Value>
    void RangeSet<Value>::insert (const Range<Value>& range)
    {
        if (range.lower > range.upper) return;
        auto iterator = set.upper_bound (range.lower);
        auto lower = range.lower, upper = range.upper;

        if (iterator != set.begin ()) if (lower <= increment ((--iterator)->upper))
            lower = iterator->lower, iterator = set.erase (iterator); else ++iterator;

        while (iterator != set.end () && iterator->upper <= upper)
            iterator = set.erase (iterator);

        if (iterator != set.end () && iterator->lower <= increment (upper))
            upper = iterator->upper, iterator = set.erase (iterator);

        set.emplace_hint (iterator, lower, upper);
    }

    template <typename Value>
    bool RangeSet<Value>::operator [] (const Range<Value>& range) const
    {
        auto iterator = set.upper_bound (range.lower);
        return iterator != set.end () && iterator->lower <= range.upper || iterator != set.begin () && (--iterator)->upper >= range.lower;
    }
#else
    template<typename T>
    T increment (T value) {return ++value;}

    template<typename T>
    void insert(RangeSet<T>& set, const Range<T>& range)
    {
        if (range.lower > range.upper) return;
        auto iterator = set.upper_bound (range.lower);
        auto lower = range.lower, upper = range.upper;

        if (iterator != set.begin ()) if (lower <= increment ((--iterator)->upper))
            lower = iterator->lower, iterator = set.erase (iterator); else ++iterator;

        while (iterator != set.end () && iterator->upper <= upper)
            iterator = set.erase (iterator);

        if (iterator != set.end () && iterator->lower <= increment (upper))
            upper = iterator->upper, iterator = set.erase (iterator);

        set.emplace_hint (iterator, lower, upper);
    }

    template<typename T>
    bool contains( const RangeSet<T>& set, const Range<T>& range)
    {
        auto iterator = set.upper_bound (range.lower);
        return iterator != set.end () && iterator->lower <= range.upper ||
                iterator != set.begin () && (--iterator)->upper >= range.lower;
    }

#endif

}


#endif // ECS_RANGESET_HEADER_INCLUDED
