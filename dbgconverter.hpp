// Generic debugging information converter
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

#ifndef ECS_DEBUGGING_CONVERTER_HEADER_INCLUDED
#define ECS_DEBUGGING_CONVERTER_HEADER_INCLUDED

#include <list>
#include <string>

namespace ECS
{
	class Charset;
	class Diagnostics;

	using Message = std::string;
	using Source = std::string;

    namespace Object
    {
        struct Binary;

        using Binaries = std::list<Binary>;
    }

    namespace Debugging
    {
        struct Information;
        class Converter
        {
        public:
            Converter (Diagnostics&, Charset&);
            virtual ~Converter () = default;

            void Convert (const Information&, const Source&, Object::Binaries&);

        protected:
            class Context;

            Diagnostics& diagnostics;
            Charset& charset;

            virtual void Process (const Information&, const Source&, Object::Binaries&) const = 0;
        };
    }

}

#endif // ECS_DEBUGGING_CONVERTER_HEADER_INCLUDED
