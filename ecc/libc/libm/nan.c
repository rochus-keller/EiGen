/*
 * Copyright (C) 2002 by Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

/***********************************************************************
    nan, nanf, nanl - return quiet NaN

	These functions shall return a quiet NaN, if available, with content
	indicated through tagp.

	If the implementation does not support quiet NaNs, these functions
	shall return zero.

   Calls:  strlen(), sprintf(), strtod()

***********************************************************************/
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

# if __BYTE_ORDER == __BIG_ENDIAN
#  define __nan_bytes		{ 0x7f, 0xc0, 0, 0 }
# elif __BYTE_ORDER == __LITTLE_ENDIAN
#  define __nan_bytes		{ 0, 0, 0xc0, 0x7f }
# endif

static const union { unsigned char __c[4]; float __d; } __nan_union = { __nan_bytes };
float __nan_value() { return __nan_union.__d; }

double nan (const char *tagp)
{
	if (tagp[0] != '\0') {
		char* buf = malloc(6 + strlen (tagp));
		sprintf (buf, "NAN(%s)", tagp);
		const double res = strtod (buf, NULL);
		free(buf);
		return res;
	}
	return NAN;
}

float nanf (const char *tagp)
{
	if (tagp[0] != '\0') {
		char* buf = malloc(6 + strlen (tagp));
		sprintf (buf, "NAN(%s)", tagp);
		const float res = strtof (buf, NULL);
		free(buf);
		return res;
	}
	return NAN;
}


