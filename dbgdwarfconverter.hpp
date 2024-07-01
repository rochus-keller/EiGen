// DWARF debugging information converter
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

#ifndef ECS_DEBUGGING_DWARF_CONVERTER_HEADER_INCLUDED
#define ECS_DEBUGGING_DWARF_CONVERTER_HEADER_INCLUDED

#include "dbgconverter.hpp"

namespace ECS { namespace Debugging
{
    class DWARFConverter : public Converter
    {
    public:
        using Converter::Converter;

    private:
        class Context;

        void Process (const Information&, const Source&, Object::Binaries&) const override;
    };
}}


#endif // ECS_DEBUGGING_DWARF_CONVERTER_HEADER_INCLUDED
