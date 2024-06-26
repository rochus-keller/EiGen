// Output stream diagnostics
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

#ifndef ECS_STREAMDIAGNOSTICS_HEADER_INCLUDED
#define ECS_STREAMDIAGNOSTICS_HEADER_INCLUDED

#include "diagnostics.hpp"
#include "position.hpp"

namespace ECS
{
	class StreamDiagnostics;

	struct ErrorLimit final {std::size_t messages;};

	std::ostream& EmitMessage (std::ostream&, Diagnostics::Type, const Source&, const Position&);

    class StreamDiagnostics : public Diagnostics
    {
    public:
        explicit StreamDiagnostics (std::ostream& s) : stream (s) {}

        void Emit (Type, const Source&, const Position&, const Message&) override;

    private:
        std::size_t errors = 0;
        std::ostream& stream;
    };

    inline void StreamDiagnostics::Emit (const Type type, const Source& source, const Position& position, const Message& message)
    {
        position.Indicate (EmitMessage (stream, type, source, position) << message << '\n').flush ();
        static const int err_limit = 100; // was 10
        if (type >= Error && type <= FatalError && ++errors >= err_limit)
            throw ErrorLimit {errors};
    }

    inline std::ostream& EmitMessage (std::ostream& stream, const Diagnostics::Type type, const Source& source, const Position& position)
    {
        stream << source;
        if (const auto line = GetLine (position)) stream << ':' << line;
        if (const auto column = GetColumn (position)) stream << ':' << column;
        static const char*const types[] {"error", "fatal error", "warning", "note"};
        return stream << ": " << types[type] << ": ";
    }
}


#endif // ECS_STREAMDIAGNOSTICS_HEADER_INCLUDED
