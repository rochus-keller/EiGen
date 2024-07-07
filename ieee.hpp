// Standard IEEE 754 floating-point conversions
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

#ifndef ECS_IEEE_HEADER_INCLUDED
#define ECS_IEEE_HEADER_INCLUDED

#include <cstdint>
#include <cmath>

namespace ECS
{
	using Bits = unsigned;

    namespace IEEE
    {
        template <Bits, Bits, typename, typename> struct Precision;

        using DoublePrecision = Precision<11, 52, std::uint64_t, double>;
        using SinglePrecision = Precision<8, 23, std::uint32_t, float>;

        template <Bits Exponent, Bits Significant, typename Unsigned, typename Float>
        struct Precision
        {
            static constexpr ECS::Bits Bias = (1 << (Exponent - 1)) - 1;

            static Float Decode (Unsigned) noexcept;
            static Unsigned Encode (Float) noexcept;

            //static_assert (sizeof (Float) * 8 == Exponent + Significant + 1);
            //static_assert (sizeof (Unsigned) * 8 == Exponent + Significant + 1);
        };


        template <Bits Exponent, Bits Significant, typename Unsigned, typename Float>
        Float Precision<Exponent, Significant, Unsigned, Float>::Decode (Unsigned value) noexcept
        {
            auto mantissa = value & (Unsigned {1} << Significant) - 1; value >>= Significant;
            signed exponent = value & (signed {1} << Exponent) - 1; value >>= Exponent;
            if (exponent == Bias * 2 + 1) if (mantissa) return value ? -NAN : NAN; else return value ? -INFINITY : INFINITY;
            if (exponent != 0) mantissa |= Unsigned {1} << Significant, exponent += Significant - Bias;
            else if (mantissa) exponent = Significant - Bias + 1; else return 0;
            Float result = exponent < 0 ? Float {1} / (1 << -exponent) : 1 << exponent;
            for (Bits i = 0; i != Significant; ++i) result /= 2, result += mantissa & 1, mantissa >>= 1;
            if (value) result = -result; return result;
        }

        template <Bits Exponent, Bits Significant, typename Unsigned, typename Float>
        Unsigned Precision<Exponent, Significant, Unsigned, Float>::Encode (Float value) noexcept
        {
            if (std::isinf (value)) return ~(Unsigned (!std::signbit (value)) << Exponent) << Significant;
            if (std::isnan (value)) return ~(Unsigned (!std::signbit (value)) << Exponent + 1) << Significant - 1;
            if (value == 0) return 0; Unsigned result = 0; signed exponent = 0;
            if (value < 0) value = -value, result = 1 << Exponent;
            while (value < 1) value *= 2, --exponent; while (value >= 2) value /= 2, ++exponent;
            result |= exponent + Bias; value -= 1;
            for (Bits i = 0; i != Significant; ++i) if (result <<= 1, (value *= 2) >= 1) value -= 1, result |= 1;
            return result;
        }
    }
}




#endif // ECS_IEEE_HEADER_INCLUDED
