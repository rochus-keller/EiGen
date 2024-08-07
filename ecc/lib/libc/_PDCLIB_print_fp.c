/* _PDCLIB_print_float

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#if 0
// using the implementation from https://github.com/mpaland/printf:
// this code has issues, therefore another version below was added
///////////////////////////////////////////////////////////////////////////////
// \author (c) Marco Paland (info@paland.com)
//             2014-2019, PALANDesign Hannover, Germany
//
// \license The MIT License (MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// \brief Tiny printf, sprintf and (v)snprintf implementation, optimized for speed on
//        embedded systems with a very limited resources. These routines are thread
//        safe and reentrant!
//        Use this instead of the bloated standard/newlib printf cause these use
//        malloc for printf (and may not be thread safe).
//
///////////////////////////////////////////////////////////////////////////////

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <inttypes.h>
#include <math.h>

#include "pdclib/_PDCLIB_print.h"


#ifndef PRINTF_FTOA_BUFFER_SIZE
#define PRINTF_FTOA_BUFFER_SIZE    32U
#endif
#ifndef PRINTF_MAX_FLOAT
#define PRINTF_MAX_FLOAT  1e9
#endif
#ifndef PRINTF_DEFAULT_FLOAT_PRECISION
#define PRINTF_DEFAULT_FLOAT_PRECISION  6U
#endif
#define FLAGS_PLUS E_plus
#define FLAGS_ZEROPAD E_zero
#define FLAGS_SPACE E_space
#define FLAGS_LEFT E_minus
#define FLAGS_ADAPT_EXP E_generic
#define FLAGS_PRECISION (1 << 30)

// output the specified string in reverse, taking care of any zero-padding
static size_t _out_rev(struct _PDCLIB_status_t * status, const char* buf, size_t len, unsigned int width, unsigned int flags)
{
  size_t idx = 0;

  // pad spaces up to given width
  if (!(flags & FLAGS_LEFT) && !(flags & FLAGS_ZEROPAD)) {
    for (size_t i = len; i < width; i++) {
      PUT(' '); idx++;
    }
  }

  // reverse string
  while (len) {
    PUT(buf[--len]); idx++;
  }

  // append pad spaces up to given width
  if (flags & FLAGS_LEFT) {
    while (idx < width) {
      PUT(' '); idx++;
    }
  }

  return idx;
}

static size_t _etoa(struct _PDCLIB_status_t * status, double value, unsigned int prec, unsigned int width, unsigned int flags);

// internal ftoa for fixed decimal floating point
static size_t _ftoa(struct _PDCLIB_status_t * status, double value, unsigned int prec, unsigned int width, unsigned int flags)
{
  char buf[PRINTF_FTOA_BUFFER_SIZE];
  size_t len  = 0U;
  double diff = 0.0;

  // powers of 10
  static const double pow10[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };

  // test for special values
  if (value != value)
    return _out_rev(status, "nan", 3, width, flags);
  if (value < -DBL_MAX)
    return _out_rev(status, "fni-", 4, width, flags);
  if (value > DBL_MAX)
    return _out_rev(status, (flags & FLAGS_PLUS) ? "fni+" : "fni", (flags & FLAGS_PLUS) ? 4U : 3U, width, flags);

  // test for very large values
  // standard printf behavior is to print EVERY whole number digit -- which could be 100s of characters overflowing your buffers == bad
  if ((value > PRINTF_MAX_FLOAT) || (value < -PRINTF_MAX_FLOAT)) {
    return _etoa(status, value, prec, width, flags);
  }

  // test for negative
  bool negative = false;
  if (value < 0) {
    negative = true;
    value = 0 - value;
  }

  // set default precision, if not set explicitly
  if (!(flags & FLAGS_PRECISION)) {
    prec = PRINTF_DEFAULT_FLOAT_PRECISION;
  }
  // limit precision to 9, cause a prec >= 10 can lead to overflow errors
  while ((len < PRINTF_FTOA_BUFFER_SIZE) && (prec > 9U)) {
    buf[len++] = '0';
    prec--;
  }

  int whole = floor(value);
  double tmp = (value - (double)whole) * pow10[prec];
  unsigned long frac = (unsigned long)floor(tmp);
  diff = tmp - frac;

  if (diff > 0.5) {
    ++frac;
    // handle rollover, e.g. case 0.99 with prec 1 is 1.0
    if (frac >= pow10[prec]) {
      frac = 0;
      ++whole;
    }
  }
  else if (diff < 0.5) {
  }
  else if ((frac == 0U) || (frac & 1U)) {
    // if halfway, round up if odd OR if last digit is 0
    ++frac;
  }

  if (prec == 0U) {
    diff = value - (double)whole;
    if ((!(diff < 0.5) || (diff > 0.5)) && (whole & 1)) {
      // exactly 0.5 and ODD, then round up
      // 1.5 -> 2, but 2.5 -> 2
      ++whole;
    }
  }
  else {
    unsigned int count = prec;
    // now do fractional part, as an unsigned number
    while (len < PRINTF_FTOA_BUFFER_SIZE && count > 0) {
      --count;
      buf[len++] = (char)(48U + (frac % 10U));
      if (!(frac /= 10U)) {
        break;
      }
    }
    // add extra 0s
    while ((len < PRINTF_FTOA_BUFFER_SIZE) && (count > 0U)) {
      buf[len++] = '0';
      count--;
    }
    if (len < PRINTF_FTOA_BUFFER_SIZE) {
      // add decimal
      buf[len++] = '.';
    }
  }

  // do whole part, number is reversed
  while (len < PRINTF_FTOA_BUFFER_SIZE) {
    buf[len++] = (char)(48 + (whole % 10));
    if (!(whole /= 10)) {
      break;
    }
  }

  // pad leading zeros
  if (!(flags & FLAGS_LEFT) && (flags & FLAGS_ZEROPAD)) {
    if (width && (negative || (flags & (FLAGS_PLUS | FLAGS_SPACE)))) {
      width--;
    }
    while ((len < width) && (len < PRINTF_FTOA_BUFFER_SIZE)) {
      buf[len++] = '0';
    }
  }

  if (len < PRINTF_FTOA_BUFFER_SIZE) {
    if (negative) {
      buf[len++] = '-';
    }
    else if (flags & FLAGS_PLUS) {
      buf[len++] = '+';  // ignore the space if the '+' exists
    }
    else if (flags & FLAGS_SPACE) {
      buf[len++] = ' ';
    }
  }

  return _out_rev(status, buf, len, width, flags);
}

// internal ftoa variant for exponential floating-point type, contributed by Martijn Jasperse <m.jasperse@gmail.com>
static size_t _etoa(struct _PDCLIB_status_t * status, double value, unsigned int prec, unsigned int width, unsigned int flags)
{
  // check for NaN and special values
  if ((value != value) || (value > DBL_MAX) || (value < -DBL_MAX)) {
    return _ftoa(status, value, prec, width, flags);
  }

  // determine the sign
  const bool negative = value < 0;
  if (negative) {
    value = -value;
  }

  // default precision
  if (!(flags & FLAGS_PRECISION)) {
    prec = PRINTF_DEFAULT_FLOAT_PRECISION;
  }

  // determine the decimal exponent
  // based on the algorithm by David Gay (https://www.ampl.com/netlib/fp/dtoa.c)
  union {
    uint64_t U;
    double   F;
  } conv;

  conv.F = value;
  int exp2 = (int)((conv.U >> 52U) & 0x07FFU) - 1023;           // effectively log2
  conv.U = (conv.U & ((1ULL << 52U) - 1U)) | (1023ULL << 52U);  // drop the exponent so conv.F is now in [1,2)
  // now approximate log10 from the log2 integer part and an expansion of ln around 1.5
  int expval = (int)(0.1760912590558 + exp2 * 0.301029995663981 + (conv.F - 1.5) * 0.289529654602168);
  // now we want to compute 10^expval but we want to be sure it won't overflow
  exp2 = (int)(expval * 3.321928094887362 + 0.5);
  const double z  = expval * 2.302585092994046 - exp2 * 0.6931471805599453;
  const double z2 = z * z;
  conv.U = (uint64_t)(exp2 + 1023) << 52U;
  // compute exp(z) using continued fractions, see https://en.wikipedia.org/wiki/Exponential_function#Continued_fractions_for_ex
  conv.F *= 1 + 2 * z / (2 - z + (z2 / (6 + (z2 / (10 + z2 / 14)))));
  // correct for rounding errors
  if (value < conv.F) {
    expval--;
    conv.F /= 10;
  }

  // the exponent format is "%+03d" and largest value is "307", so set aside 4-5 characters
  unsigned int minwidth = ((expval < 100) && (expval > -100)) ? 4U : 5U;

  // in "%g" mode, "prec" is the number of *significant figures* not decimals
  if (flags & FLAGS_ADAPT_EXP) {
    // do we want to fall-back to "%f" mode?
    if ((value >= 1e-4) && (value < 1e6)) {
      if ((int)prec > expval) {
        prec = (unsigned)((int)prec - expval - 1);
      }
      else {
        prec = 0;
      }
      flags |= FLAGS_PRECISION;   // make sure _ftoa respects precision
      // no characters in exponent
      minwidth = 0U;
      expval   = 0;
    }
    else {
      // we use one sigfig for the whole part
      if ((prec > 0) && (flags & FLAGS_PRECISION)) {
        --prec;
      }
    }
  }

  // will everything fit?
  unsigned int fwidth = width;
  if (width > minwidth) {
    // we didn't fall-back so subtract the characters required for the exponent
    fwidth -= minwidth;
  } else {
    // not enough characters, so go back to default sizing
    fwidth = 0U;
  }
  if ((flags & FLAGS_LEFT) && minwidth) {
    // if we're padding on the right, DON'T pad the floating part
    fwidth = 0U;
  }

  // rescale the float value
  if (expval) {
    value /= conv.F;
  }

  // output the floating part
  size_t idx = _ftoa(status, negative ? -value : value, prec, fwidth, flags & ~FLAGS_ADAPT_EXP);

  // output the exponent part
  if (minwidth) {
    // output the exponential symbol
    PUT((flags & E_lower) ? 'e' : 'E'); idx++;
    // output the exponent value
    _PDCLIB_int_fast32_t old_flags = status->flags;
    status->flags = FLAGS_ZEROPAD | FLAGS_PLUS;
    _PDCLIB_size_t   old_width = status->width;
    status->width = minwidth-1;
    int old_prec = status->prec;
    status->prec = 0;
    int old_base = status->base;
    status->base = 10;
    _PDCLIB_size_t   old_i = status->i;
    _PDCLIB_print_integer(imaxdiv( (expval < 0) ? -expval : expval, status->base ), status );
    idx += status->i - old_i;
    status->flags = old_flags;
    status->width = old_width;
    status->prec = old_prec;
    status->base = old_base;
    // might need to right-pad spaces
    if (flags & FLAGS_LEFT) {
      while (idx < width) { PUT(' '); idx++; }
    }
  }
  return idx;
}

void _PDCLIB_print_double( double value, struct _PDCLIB_status_t * status )
{
    _ftoa(status, value, status->prec != EOF ? status->prec : 0, status->width,
          status->flags | (status->prec != EOF ? FLAGS_PRECISION : 0 ));
}
#else

#include "pdclib/_PDCLIB_print.h"
#include <string.h>

/**
 *  stm32tpl --  STM32 C++ Template Peripheral Library
 *  Visit https://github.com/antongus/stm32tpl for new versions
 *
 *  Copyright (c) 2011-2020 Anton B. Gusev aka AHTOXA
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 *
 *
 *  file         : ftoa.c
 *  description  : convert double to string
 *
 */

#define MAX_PRECISION	(10)
static const double rounders[MAX_PRECISION + 1] =
{
    0.5,				// 0
    0.05,				// 1
    0.005,				// 2
    0.0005,				// 3
    0.00005,			// 4
    0.000005,			// 5
    0.0000005,			// 6
    0.00000005,			// 7
    0.000000005,		// 8
    0.0000000005,		// 9
    0.00000000005		// 10
};

static char * _ftoa(double f, char * buf, int precision)
{
    char * ptr = buf;
    char * p = ptr;
    char * p1;
    char c;
    long intPart;

    // check precision bounds
    if (precision > MAX_PRECISION)
        precision = MAX_PRECISION;

    // sign stuff
    if (f < 0)
    {
        f = -f;
        *ptr++ = '-';
    }

    if (precision < 0)  // negative precision == automatic precision guess
    {
        if (f < 1.0) precision = 6;
        else if (f < 10.0) precision = 5;
        else if (f < 100.0) precision = 4;
        else if (f < 1000.0) precision = 3;
        else if (f < 10000.0) precision = 2;
        else if (f < 100000.0) precision = 1;
        else precision = 0;
    }

    // round value according the precision
    if (precision)
        f += rounders[precision];

    // integer part...
    intPart = f;
    f -= intPart;

    if (!intPart)
        *ptr++ = '0';
    else
    {
        // save start pointer
        p = ptr;

        // convert (reverse order)
        while (intPart)
        {
            *p++ = '0' + intPart % 10;
            intPart /= 10;
        }

        // save end pos
        p1 = p;

        // reverse result
        while (p > ptr)
        {
            c = *--p;
            *p = *ptr;
            *ptr++ = c;
        }

        // restore end pos
        ptr = p1;
    }

    // decimal part
    if (precision)
    {
        // place decimal point
        *ptr++ = '.';

        // convert
        while (precision--)
        {
            f *= 10.0;
            c = f;
            *ptr++ = '0' + c;
            f -= c;
        }
    }

    // terminating zero
    *ptr = 0;

    return buf;
}

void _PDCLIB_print_double( double value, struct _PDCLIB_status_t * status )
{
    char buf[32];
    _ftoa(value, buf, status->prec );

    if( value >= 0.0 ) {
        if( status->flags & E_plus )
            PUT('+');
        else if( status->flags & E_space )
            PUT(' ');
    }else
        PUT('-');
    const char* dot = strchr(buf,'.');
    int curwidth = strlen(buf);
    if( dot )
        curwidth = dot - buf;
    if( buf[0] == '-' )
        curwidth--;

    const int target_width = status->width - curwidth;
    // TODO E_minus : left-aligned output
    // TODO E_exponent and E_generic
    for( int i = 0; i < target_width; i++ )
    {
        if( status->flags & E_zero )
            PUT('0');
        else
            PUT(' ');
    }

    for( int i = 0; i < strlen(buf); i++ )
    {
        if( i == 0 && buf[i] == '-')
            continue;
        PUT(buf[i]);
    }
}

#endif


void _PDCLIB_print_ldouble( long double value, struct _PDCLIB_status_t * status )
{
    _PDCLIB_print_double(value,status);
}


