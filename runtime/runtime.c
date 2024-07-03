// Common basic runtime support
// Copyright (C) Florian Negele

// This file is part of the Eigen Compiler Suite.

// The ECS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// The ECS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of the GNU General Public License version 3,
// the copyright holder grants you additional permissions to use
// this file as described in the ECS Runtime Support Exception.

// You should have received a copy of the GNU General Public License
// and a copy of the ECS Runtime Support Exception along with
// the ECS.  If not, see <https://www.gnu.org/licenses/>.

#include <stdbool.h>

typedef float f4 ;
typedef long double f8 ;
typedef signed char s1 ;
typedef signed short s2 ;
typedef signed long s4 ;
typedef signed long long s8 ;
typedef unsigned char u1 ;
typedef unsigned short u2 ;
typedef unsigned long u4 ;
typedef unsigned long long u8 ;

typedef struct {u4 s; u4 m; s4 e;} fp4;
typedef struct {u8 s; u8 m; s8 e;} fp8;
typedef struct {s4 l; s4 h;} ss8;
typedef struct {u4 l; s4 h;} us8;
typedef struct {u4 l; u4 h;} uu8;


#define PACK4(x, px) (px).c = (x).m ? (x).s << 31 | (x).e << 23 | (x).m & 0x007fffff : 0
#define PACK8(x, px) (px).c = (x).m ? (x).s << 63 | (x).e << 52 | (x).m & 0x000fffffffffffff : 0
#define UNPACK4(px, x) (x).s = (px).c >> 31, (x).m = (px).c ? (px).c & 0x007fffff | 0x00800000 : 0, (x).e = (px).c >> 23 & 0xff
#define UNPACK8(px, x) (x).s = (px).c >> 63, (x).m = (px).c ? (px).c & 0x000fffffffffffff | 0x0010000000000000 : 0, (x).e = (px).c >> 52 & 0x7ff

// floating-point unit initialization

#if defined __amd16__

	asm target (R"(
		.initdata _init_fpu
			fninit
			push	word 0x0f7f
			mov	si, sp
			fldcw	[si]
			pop	ax
	)");

#elif defined __amd32__

	asm target (R"(
		.initdata _init_fpu
			fninit
			push	word 0x0f7f
			fldcw	[esp]
			pop	ax
	)");

#endif

// global register definitions

// intermediate conv instruction

s1 _conv_s1_f4 (const f4 x) 
{
    union {f4 v; u4 c;} a; a.v = x; const s4 e = (a.c << 1 >> 24) - 127; s4 r;
	if (e <= 0) r = !e; else if (e < 32) r = 1 << e | a.c << 9 >> 32 - e; else r = -1;
	if (a.c >> 31) r = -r; return (s1)r;
}

s1 _conv_s1_f8 (const f8 x) 
{
    union {f8 v; uu8 c;} a; a.v = x; const s4 e = (a.c.h << 1 >> 21) - 1023; s4 r;
	if (e <= 0) r = !e; else if (e < 20) r = 1 << e | a.c.h << 12 >> 32 - e;
	else if (e < 32) r = 1 << e | a.c.h << 12 >> 32 - e | a.c.l >> 52 - e; else r = -1;
	if (a.c.h >> 31) r = -r; return (s1)r;
}

s2 _conv_s2_f4 (const f4 x) 
{
    union {f4 v; u4 c;} a; a.v = x; const s4 e = (a.c << 1 >> 24) - 127; s4 r;
	if (e <= 0) r = !e; else if (e < 32) r = 1 << e | a.c << 9 >> 32 - e; else r = -1;
	if (a.c >> 31) r = -r; return (s2)r;
}

s2 _conv_s2_f8 (const f8 x) 
{
    union {f8 v; uu8 c;} a; a.v = x; const s4 e = (a.c.h << 1 >> 21) - 1023; s4 r;
	if (e <= 0) r = !e; else if (e < 20) r = 1 << e | a.c.h << 12 >> 32 - e;
	else if (e < 32) r = 1 << e | a.c.h << 12 >> 32 - e | a.c.l >> 52 - e; else r = -1;
	if (a.c.h >> 31) r = -r; return (s2)r;
}

s4 _conv_s4_f4 (const f4 x) 
{
    union {f4 v; u4 c;} a; a.v = x; const s4 e = (a.c << 1 >> 24) - 127; s4 r;
	if (e <= 0) r = !e; else if (e < 32) r = 1 << e | a.c << 9 >> 32 - e; else r = -1;
	if (a.c >> 31) r = -r; return r;
}

s4 _conv_s4_f8 (const f8 x) 
{
    union {f8 v; uu8 c;} a; a.v = x; const s4 e = (a.c.h << 1 >> 21) - 1023; s4 r;
	if (e <= 0) r = !e; else if (e < 20) r = 1 << e | a.c.h << 12 >> 32 - e;
	else if (e < 32) r = 1 << e | a.c.h << 12 >> 32 - e | a.c.l >> 52 - e; else r = -1;
	if (a.c.h >> 31) r = -r; return r;
}

s8 _conv_s8_f4 (const f4 x) 
{
    union {f4 v; u4 c;} a; a.v = x; const s4 e = (a.c << 1 >> 24) - 127; union {s8 v; uu8 c;} r;
	if (e <= 0) r.c.l = !e, r.c.h = 0; else if (e < 32) r.c.l = 1 << e | a.c << 9 >> 32 - e, r.c.h = 0;
	else if (e < 64) r.c.l = a.c << 9 >> 64 - e, r.c.h = 1 << e - 32 | a.c << 9 >> 64 - e; else r.c.l = -1, r.c.h = -1;
	if (a.c >> 31) r.v = -r.v; return r.v;
}

s8 _conv_s8_f8 (const f8 x) 
{
    union {f8 v; uu8 c;} a; a.v = x; const s4 e = (a.c.h << 1 >> 21) - 1023; union {s8 v; uu8 c;} r;
	if (e <= 0) r.c.l = !e, r.c.h = 0; else if (e < 20) r.c.l = 1 << e | a.c.h << 12 >> 32 - e, r.c.h = 0;
	else if (e < 32) r.c.l = 1 << e | a.c.h << 12 >> 32 - e | a.c.l >> 52 - e, r.c.h = 0;
	else if (e < 52) r.c.l = a.c.l >> 52 - e | a.c.h << e - 20, r.c.h = 1 << e - 32 | a.c.h << 12 >> 64 - e;
	else if (e < 64) r.c.l = a.c.l << e - 52, r.c.h = 1 << e - 64 | a.c.h << 12 >> 64 - e | a.c.l >> 84 - e; else r.c.l = -1, r.c.h = -1;
	if (a.c.h >> 31) r.v = -r.v; return r.v;
}

u1 _conv_u1_f4 (const f4 x) 
{
    union {f4 v; u4 c;} a; a.v = x; const s4 e = (a.c >> 23) - 127; u4 r;
	if (e <= 0) r = !e; else if (e < 32) r = 1 << e | a.c << 9 >> 32 - e; else r = -1;
	return (u1)r;
}

u1 _conv_u1_f8 (const f8 x) 
{
    union {f8 v; uu8 c;} a; a.v = x; const s4 e = (a.c.h >> 20) - 1023; u4 r;
	if (e <= 0) r = !e; else if (e < 20) r = 1 << e | a.c.h << 12 >> 32 - e;
	else if (e < 32) r = 1 << e | a.c.h << 12 >> 32 - e | a.c.l >> 52 - e; else r = -1;
	return (u1)r;
}

u2 _conv_u2_f4 (const f4 x) 
{
    union {f4 v; u4 c;} a; a.v = x; const s4 e = (a.c >> 23) - 127; u4 r;
	if (e <= 0) r = !e; else if (e < 32) r = 1 << e | a.c << 9 >> 32 - e; else r = -1;
	return (u2)r;
}

u2 _conv_u2_f8 (const f8 x) 
{
    union {f8 v; uu8 c;} a; a.v = x; const s4 e = (a.c.h >> 20) - 1023; u4 r;
	if (e <= 0) r = !e; else if (e < 20) r = 1 << e | a.c.h << 12 >> 32 - e;
	else if (e < 32) r = 1 << e | a.c.h << 12 >> 32 - e | a.c.l >> 52 - e; else r = -1;
	return (u2)r;
}

u4 _conv_u4_f4 (const f4 x) 
{
    union {f4 v; u4 c;} a; a.v = x; const s4 e = (a.c >> 23) - 127; u4 r;
	if (e <= 0) r = !e; else if (e < 32) r = 1 << e | a.c << 9 >> 32 - e; else r = -1;
	return r;
}

u4 _conv_u4_f8 (const f8 x) 
{
    union {f8 v; uu8 c;} a; a.v = x; const s4 e = (a.c.h >> 20) - 1023; u4 r;
	if (e <= 0) r = !e; else if (e < 20) r = 1 << e | a.c.h << 12 >> 32 - e;
	else if (e < 32) r = 1 << e | a.c.h << 12 >> 32 - e | a.c.l >> 52 - e; else r = -1;
	return r;
}

u8 _conv_u8_f4 (const f4 x) 
{
    union {f4 v; u4 c;} a; a.v = x; const s4 e = (a.c >> 23) - 127; union {u8 v; uu8 c;} r;
	if (e <= 0) r.c.l = !e, r.c.h = 0; else if (e < 32) r.c.l = 1 << e | a.c << 9 >> 32 - e, r.c.h = 0;
	else if (e < 64) r.c.l = a.c << 9 >> 64 - e, r.c.h = 1 << e - 32 | a.c << 9 >> 64 - e; else r.c.l = -1, r.c.h = -1;
	return r.v;
}

u8 _conv_u8_f8 (const f8 x) 
{
    union {f8 v; uu8 c;} a; a.v = x; const s4 e = (a.c.h >> 20) - 1023; union {u8 v; uu8 c;} r;
	if (e <= 0) r.c.l = !e, r.c.h = 0; else if (e < 20) r.c.l = 1 << e | a.c.h << 12 >> 32 - e, r.c.h = 0;
	else if (e < 32) r.c.l = 1 << e | a.c.h << 12 >> 32 - e | a.c.l >> 52 - e, r.c.h = 0;
	else if (e < 52) r.c.l = a.c.l >> 52 - e | a.c.h << e - 20, r.c.h = 1 << e - 32 | a.c.h << 12 >> 64 - e;
	else if (e < 64) r.c.l = a.c.l << e - 52, r.c.h = 1 << e - 64 | a.c.h << 12 >> 64 - e | a.c.l >> 84 - e; else r.c.l = -1, r.c.h = -1;
	return r.v;
}

f4 _conv_f4_s1 (s1 x) 
{
	const bool s = x < 0; if (s) x = -x;
	u4 a = x, b = x; union {u4 c; f4 v;} r;
	u4 p = 0; while (a) a >>= 1, ++p;
	if (p > 0) b = b << 32 - p << 1;
	if (p) r.c = p + 126 << 23 | b >> 9; else r.c = 0;
	if (s) r.v = -r.v; return r.v;
}

f4 _conv_f4_s2 (s2 x) 
{
	const bool s = x < 0; if (s) x = -x;
	u4 a = x, b = x; union {u4 c; f4 v;} r;
	u4 p = 0; while (a) a >>= 1, ++p;
	if (p > 0) b = b << 32 - p << 1;
	if (p) r.c = p + 126 << 23 | b >> 9; else r.c = 0;
	if (s) r.v = -r.v; return r.v;
}

f4 _conv_f4_s4 (s4 x) 
{
	const bool s = x < 0; if (s) x = -x;
	u4 a = x, b = x; union {u4 c; f4 v;} r;
	u4 p = 0; while (a) a >>= 1, ++p;
	if (p > 0) b = b << 32 - p << 1;
	if (p) r.c = p + 126 << 23 | b >> 9; else r.c = 0;
	if (s) r.v = -r.v; return r.v;
}

f4 _conv_f4_s8 (s8 x) 
{
	const bool s = x < 0; if (s) x = -x;
	union {u8 a; uu8 c;} a, b; a.a = x; b.a = x; union {u4 c; f4 v;} r;
	u4 p = 0; if (a.c.h) {p += 32; do a.c.h >>= 1, ++p; while (a.c.h);} else while (a.c.l) a.c.l >>= 1, ++p;
	if (p > 32) b.c.h = b.c.h << 64 - p << 1 | b.c.l >> p - 33; else if (p > 0) b.c.h = b.c.l << 32 - p << 1;
	if (p) r.c = p + 126 << 23 | b.c.h >> 9; else r.c = 0;
	if (s) r.v = -r.v; return r.v;
}

f8 _conv_f8_s1 (s1 x) 
{
	const bool s = x < 0; if (s) x = -x;
	u4 a = x, b = x; union {uu8 c; f8 v;} r;
	u4 p = 0; while (a) a >>= 1, ++p;
	if (p > 0) b = b << 32 - p << 1;
	if (p) r.c.l = b << 20, r.c.h = p + 1022 << 20 | b >> 12; else r.c.l = 0, r.c.h = 0;
	if (s) r.v = -r.v; return r.v;
}

f8 _conv_f8_s2 (s2 x) 
{
	const bool s = x < 0; if (s) x = -x;
	u4 a = x, b = x; union {uu8 c; f8 v;} r;
	u4 p = 0; while (a) a >>= 1, ++p;
	if (p > 0) b = b << 32 - p << 1;
	if (p) r.c.l = b << 20, r.c.h = p + 1022 << 20 | b >> 12; else r.c.l = 0, r.c.h = 0;
	if (s) r.v = -r.v; return r.v;
}

f8 _conv_f8_s4 (s4 x) 
{
	const bool s = x < 0; if (s) x = -x;
	u4 a = x, b = x; union {uu8 c; f8 v;} r;
	u4 p = 0; while (a) a >>= 1, ++p;
	if (p > 0) b = b << 32 - p << 1;
	if (p) r.c.l = b << 20, r.c.h = p + 1022 << 20 | b >> 12; else r.c.l = 0, r.c.h = 0;
	if (s) r.v = -r.v; return r.v;
}

f8 _conv_f8_s8 (s8 x) 
{
	const bool s = x < 0; if (s) x = -x;
	union {u8 a; uu8 c;} a, b; a.a = x; b.a = x; union {uu8 c; f8 v;} r;
	u4 p = 0; if (a.c.h) {p += 32; do a.c.h >>= 1, ++p; while (a.c.h);} else while (a.c.l) a.c.l >>= 1, ++p;
	if (p > 32) b.c.h = b.c.h << 64 - p << 1 | b.c.l >> p - 33, b.c.l = b.c.l << 64 - p << 1; else if (p > 0) b.c.h = b.c.l << 32 - p << 1, b.c.l = 0;
	if (p) r.c.l = b.c.l >> 12 | b.c.h << 20, r.c.h = p + 1022 << 20 | b.c.h >> 12; else r.c.l = 0, r.c.h = 0;
	if (s) r.v = -r.v; return r.v;
}

f4 _conv_f4_u1 (const u1 x) 
{
	u4 a = x, b = x; union {u4 c; f4 v;} r;
	u4 p = 0; while (a) a >>= 1, ++p;
	if (p > 0) b = b << 32 - p << 1;
	if (p) r.c = p + 126 << 23 | b >> 9; else r.c = 0;
	return r.v;
}

f4 _conv_f4_u2 (const u2 x) 
{
	u4 a = x, b = x; union {u4 c; f4 v;} r;
	u4 p = 0; while (a) a >>= 1, ++p;
	if (p > 0) b = b << 32 - p << 1;
	if (p) r.c = p + 126 << 23 | b >> 9; else r.c = 0;
	return r.v;
}

f4 _conv_f4_u4 (const u4 x) 
{
	u4 a = x, b = x; union {u4 c; f4 v;} r;
	u4 p = 0; while (a) a >>= 1, ++p;
	if (p > 0) b = b << 32 - p << 1;
	if (p) r.c = p + 126 << 23 | b >> 9; else r.c = 0;
	return r.v;
}

f4 _conv_f4_u8 (const u8 x) 
{
	union {u8 a; uu8 c;} a, b; a.a = x; b.a = x; union {u4 c; f4 v;} r;
	u4 p = 0; if (a.c.h) {p += 32; do a.c.h >>= 1, ++p; while (a.c.h);} else while (a.c.l) a.c.l >>= 1, ++p;
	if (p > 32) b.c.h = b.c.h << 64 - p << 1 | b.c.l >> p - 33; else if (p > 0) b.c.h = b.c.l << 32 - p << 1;
	if (p) r.c = p + 126 << 23 | b.c.h >> 9; else r.c = 0;
	return r.v;
}

f8 _conv_f8_u1 (const u1 x) 
{
	u4 a = x, b = x; union {uu8 c; f8 v;} r;
	u4 p = 0; while (a) a >>= 1, ++p;
	if (p > 0) b = b << 32 - p << 1;
	if (p) r.c.l = b << 20, r.c.h = p + 1022 << 20 | b >> 12; else r.c.l = 0, r.c.h = 0;
	return r.v;
}

f8 _conv_f8_u2 (const u2 x) 
{
	u4 a = x, b = x; union {uu8 c; f8 v;} r;
	u4 p = 0; while (a) a >>= 1, ++p;
	if (p > 0) b = b << 32 - p << 1;
	if (p) r.c.l = b << 20, r.c.h = p + 1022 << 20 | b >> 12; else r.c.l = 0, r.c.h = 0;
	return r.v;
}

f8 _conv_f8_u4 (const u4 x) 
{
	u4 a = x, b = x; union {uu8 c; f8 v;} r;
	u4 p = 0; while (a) a >>= 1, ++p;
	if (p > 0) b = b << 32 - p << 1;
	if (p) r.c.l = b << 20, r.c.h = p + 1022 << 20 | b >> 12; else r.c.l = 0, r.c.h = 0;
	return r.v;
}

f8 _conv_f8_u8 (const u8 x) 
{
	union {u8 a; uu8 c;} a, b; a.a = x; b.a = x; union {uu8 c; f8 v;} r;
	u4 p = 0; if (a.c.h) {p += 32; do a.c.h >>= 1, ++p; while (a.c.h);} else while (a.c.l) a.c.l >>= 1, ++p;
	if (p > 32) b.c.h = b.c.h << 64 - p << 1 | b.c.l >> p - 33, b.c.l = b.c.l << 64 - p << 1; else if (p > 0) b.c.h = b.c.l << 32 - p << 1, b.c.l = 0;
	if (p) r.c.l = b.c.l >> 12 | b.c.h << 20, r.c.h = p + 1022 << 20 | b.c.h >> 12; else r.c.l = 0, r.c.h = 0;
	return r.v;
}

f4 _conv_f4_f8 (const f8 x) 
{
	union {f8 v; u8 c;} pa; pa.v = x; fp8 a; UNPACK8 (pa, a); union {f4 v; u4 c;} pr; fp4 r;
	r.s = (u4) a.s;
	r.e = (s4) a.e - 1023 + 127;
	r.m = (u4) (a.m >> 29);
	PACK4 (r, pr); return pr.v;
}

f8 _conv_f8_f4 (const f4 x) 
{
	union {f4 v; u4 c;} pa; pa.v = x; fp4 a; UNPACK4 (pa, a); union {f8 v; u8 c;} pr; fp8 r;
	r.s = a.s;
	r.e = a.e - 127 + 1023;
	r.m = (u8) a.m << 29;
	PACK8 (r, pr); return pr.v;
}

// intermediate fill instruction

#if defined __amd16__

	asm target (R"(
		.code _fill_ptr_s8
			.alias	_fill_ptr_u8
			.alias	_fill_ptr_f8
			mov	si, sp
			mov	cx, [si + 4]
			cmp	cx, 0
			je	done
			mov	di, [si + 2]
			mov	eax, [si + 6]
			mov	ebx, [si + 10]
		loop:	mov	[di], eax
			mov	[di + 4], ebx
			add	di, 8
			dec	cx
			jne	loop
		done:	ret
	)");

#elif defined __amd32__

	asm target (R"(
		.code _fill_ptr_s8
			.alias	_fill_ptr_u8
			.alias	_fill_ptr_f8
			mov	ecx, [esp + 8]
			cmp	ecx, 0
			je	done
			mov	edx, [esp + 4]
			mov	eax, [esp + 12]
			mov	ebx, [esp + 16]
		loop:	mov	[edx], eax
			mov	[edx + 4], ebx
			add	edx, 8
			dec	ecx
			jne	loop
		done:	ret
	)");

#endif

// intermediate neg instruction

s8 _neg_s8 (const s8 x) 
{
	union {s8 v; ss8 c;} r; r.v = x;
	r.c.l = -r.c.l; r.c.h = -r.c.h; if (r.c.l) --r.c.h;
	return r.v;
}

f4 _neg_f4 (const f4 x) 
{
	union {f4 v; u4 c;} r; r.v = x;
	r.c ^= 0x80000000;
	return r.v;
}

f8 _neg_f8 (const f8 x) 
{
	union {f8 v; uu8 c;} r; r.v = x;
	r.c.h ^= 0x80000000;
	return r.v;
}

// intermediate add instruction

s8 _add_s8 (const s8 x, const s8 y) 
{
	union {s8 v; uu8 c;} a, b, r; a.v = x; b.v = y;
	r.c.l = a.c.l + b.c.l; r.c.h = a.c.h + b.c.h; if (r.c.l < a.c.l) ++r.c.h;
	return r.v;
}

u8 _add_u8(const s8 x, const s8 y) { return _add_s8(x,y); }

f4 _add_f4 (const f4 x, const f4 y) 
{
	union {f4 v; u4 c;} pa, pb, pr; pa.v = x; pb.v = y; fp4 a, b, r; UNPACK4 (pa, a); UNPACK4 (pb, b);
	if (a.e < b.e) a.m = a.m >> (b.e - a.e < 24 ? b.e - a.e : 24), a.e = b.e;
	if (b.e < a.e) b.m = b.m >> (a.e - b.e < 24 ? a.e - b.e : 24), b.e = a.e;
	if (a.s) a.m = -a.m;
	if (b.s) b.m = -b.m;
	r.m = a.m + b.m;
	r.s = r.m >> 31;
	if (r.s) r.m = -r.m;
	r.e = a.e;
	if (r.m & 0x01000000) r.m >>= 1, r.e += 1;
	else while (r.m && ~r.m & 0x00800000) r.m <<= 1, r.e -= 1;
	PACK4 (r, pr); return pr.v;
}

f8 _add_f8 (const f8 x, const f8 y) 
{
	union {f8 v; u8 c;} pa, pb, pr; pa.v = x; pb.v = y; fp8 a, b, r; UNPACK8 (pa, a); UNPACK8 (pb, b);
	if (a.e < b.e) a.m = a.m >> (b.e - a.e < 53 ? b.e - a.e : 53), a.e = b.e;
	if (b.e < a.e) b.m = b.m >> (a.e - b.e < 53 ? a.e - b.e : 53), b.e = a.e;
	if (a.s) a.m = -a.m;
	if (b.s) b.m = -b.m;
	r.m = a.m + b.m;
	r.s = r.m >> 63;
	if (r.s) r.m = -r.m;
	r.e = a.e;
	if (r.m & 0x0020000000000000) r.m >>= 1, r.e += 1;
	else while (r.m && ~r.m & 0x0010000000000000) r.m <<= 1, r.e -= 1;
	PACK8 (r, pr); return pr.v;
}

// intermediate sub instruction

f4 _sub_f4 (const f4 x, const f4 y) 
{
	union {f4 v; u4 c;} pa, pb, pr; pa.v = x; pb.v = y; fp4 a, b, r; UNPACK4 (pa, a); UNPACK4 (pb, b);
	if (a.e < b.e) a.m = a.m >> (b.e - a.e < 24 ? b.e - a.e : 24), a.e = b.e;
	if (b.e < a.e) b.m = b.m >> (a.e - b.e < 24 ? a.e - b.e : 24), b.e = a.e;
	if (a.s) a.m = -a.m;
	if (b.s) b.m = -b.m;
	r.m = a.m - b.m;
	r.s = r.m >> 31;
	if (r.s) r.m = -r.m;
	r.e = a.e;
	if (r.m & 0x01000000) r.m >>= 1, r.e += 1;
	else while (r.m && ~r.m & 0x00800000) r.m <<= 1, r.e -= 1;
	PACK4 (r, pr); return pr.v;
}

f8 _sub_f8 (const f8 x, const f8 y) 
{
	union {f8 v; u8 c;} pa, pb, pr; pa.v = x; pb.v = y; fp8 a, b, r; UNPACK8 (pa, a); UNPACK8 (pb, b);
	if (a.e < b.e) a.m = a.m >> (b.e - a.e < 53 ? b.e - a.e : 53), a.e = b.e;
	if (b.e < a.e) b.m = b.m >> (a.e - b.e < 53 ? a.e - b.e : 53), b.e = a.e;
	if (a.s) a.m = -a.m;
	if (b.s) b.m = -b.m;
	r.m = a.m - b.m;
	r.s = r.m >> 63;
	if (r.s) r.m = -r.m;
	r.e = a.e;
	if (r.m & 0x0020000000000000) r.m >>= 1, r.e += 1;
	else while (r.m && ~r.m & 0x0010000000000000) r.m <<= 1, r.e -= 1;
	PACK8 (r, pr); return pr.v;
}

// intermediate mul instruction


u4 _mul_u4 (const u4 x, const u4 y) 
{
	u4 a = x, b = y, r;
	if (a > b) r = a, a = b, b = r;
	for (r = 0; a; a >>= 1, b <<= 1) if (a & 1) r += b;
	return r;
}

#if defined __amd16__

	asm target (R"(
		.code _mul_s8
			.alias	_mul_u8
			mov	di, sp
			mov	edx, [di + 6]
			mov	ecx, [di + 14]
			or	edx, ecx
			mov	edx, [di + 10]
			mov	eax, [di + 2]
			jnz	twomul
			mul	edx
			ret
		twomul:
			imul	edx, [di + 6]
			imul	ecx, eax
			add	ecx, edx
			mul	dword [di + 10]
			add	edx, ecx
			ret
	)");

#elif defined __amd32__

	asm target (R"(
		.code _mul_s8
			.alias	_mul_u8
			mov	edx, [esp + 8]
			mov	ecx, [esp + 16]
			or	edx, ecx
			mov	edx, [esp + 12]
			mov	eax, [esp + 4]
			jnz	twomul
			mul	edx
			ret
		twomul:
			imul	edx, [esp + 8]
			imul	ecx, eax
			add	ecx, edx
			mul	dword [esp + 12]
			add	edx, ecx
			ret
	)");

#else

	u8 _mul_s8 (const u8 x, const u8 y) 
	{
		u8 a = x, b = y, r;
		if (a > b) r = a, a = b, b = r;
		for (r = 0; a; a >>= 1, b <<= 1) if (a & 1) r += b;
		return r;
	}
	
	u8 _mul_u8(const u8 x, const u8 y) { return _mul_s8(x,y); }

#endif

f4 _mul_f4 (const f4 x, const f4 y) 
{
	union {f4 v; u4 c;} pa, pb, pr; pa.v = x; pb.v = y; fp4 a, b, r; UNPACK4 (pa, a); UNPACK4 (pb, b);
	r.s = a.s ^ b.s;
	r.m = (a.m >> 8) * (b.m >> 8) >> 8;
	r.e = a.e + b.e - 127;
	if (r.m & 0x00800000) r.e += 1; else r.m <<= 1;
	PACK4 (r, pr); return pr.v;
}

f8 _mul_f8 (const f8 x, const f8 y) 
{
	union {f8 v; u8 c;} pa, pb, pr; pa.v = x; pb.v = y; fp8 a, b, r; UNPACK8 (pa, a); UNPACK8 (pb, b);
	r.s = a.s ^ b.s;
	r.m = (a.m >> 21) * (b.m >> 21) >> 11;
	r.e = a.e + b.e - 1023;
	if (r.m & 0x0010000000000000) r.e += 1; else r.m <<= 1;
	PACK8 (r, pr); return pr.v;
}

// intermediate div instruction

s1 _div_s1 (s1 x, s1 y) 
{
	u1 q = 0, r = 0; bool s = x < 0; if (s) x = -x; if (y < 0) s ^= true, y = -y;
	for (int i = 7; i >= 0; --i)
		if (r <<= 1, r |= (u1) (x >> i & 1), r >= y) r -= y, q |= (u1) (1 << i);
	return s ? -q : q;
}

u1 _div_u1 (const u1 x, const u1 y) 
{
	u1 q = 0, r = 0;
	for (int i = 7; i >= 0; --i) if (r <<= 1, r |= (u1) (x >> i & 1), r >= y) r -= y, q |= (u1) (1 << i);
	return q;
}

s2 _div_s2 (s2 x, s2 y) 
{
	u2 q = 0, r = 0; bool s = x < 0; if (s) x = -x; if (y < 0) s ^= true, y = -y;
	for (int i = 15; i >= 0; --i) if (r <<= 1, r |= (u2) (x >> i & 1), r >= y) r -= y, q |= (u2) (1 << i);
	return s ? -q : q;
}

u2 _div_u2 (const u2 x, const u2 y) 
{
	u2 q = 0, r = 0;
	for (int i = 15; i >= 0; --i) if (r <<= 1, r |= (u2) (x >> i & 1), r >= y) r -= y, q |= (u2) (1 << i);
	return q;
}

#if defined __arma32__

	asm target (R"(
		.code _div_s4
			ldr	r2, [sp, 0]
			ldr	r3, [sp, 4]
			mov	r0, r2, asr 31
			add	r2, r2, r0
			eor	r2, r2, r0
			mov	r1, r3, asr 31
			add	r3, r3, r1
			eor	r3, r3, r1
			eor	r1, r0, r1
			clz	r4, r2
			clz	r5, r3
			sub	r4, r5, r4
			add	r4, r4, 1
			mov	r5, 0
			b	check
		loop:	cmp	r2, r3, lsl r4
			adc	r5, r5, r5
			subcs	r2, r2, r3, lsl r4
		check:	subs	r4, r4, 1
			bpl	loop
			add	r0, r5, r1
			eor	r0, r0, r1
			bx	lr

		.code _div_u4
			ldr	r2, [sp, 0]
			ldr	r3, [sp, 4]
			clz	r4, r2
			clz	r5, r3
			sub	r4, r5, r4
			add	r4, r4, 1
			mov	r5, 0
			b	check
		loop:	cmp	r2, r3, lsl r4
			adc	r5, r5, r5
			subcs	r2, r2, r3, lsl r4
		check:	subs	r4, r4, 1
			bpl	loop
			mov	r0, r5
			bx	lr
	)");

#else

	s4 _div_s4 (s4 x, s4 y) 
	{
		u4 q = 0, r = 0; bool s = x < 0; if (s) x = -x; if (y < 0) s ^= true, y = -y;
		for (int i = 31; i >= 0; --i) if (r <<= 1, r |= (u4) (x >> i & 1), r >= y) r -= y, q |= (u4) (1) << i;
		return s ? -q : q;
	}

	u4 _div_u4 (const u4 x, const u4 y) 
	{
		u4 q = 0, r = 0;
		for (int i = 31; i >= 0; --i) if (r <<= 1, r |= (u4) (x >> i & 1), r >= y) r -= y, q |= (u4) (1) << i;
		return q;
	}

#endif

#if defined __amd16__

	asm target (R"(
		.code _div_s8
			mov	si, sp
			mov	ecx, [si + 14]
			mov	ebx, [si + 10]
			mov	edx, [si + 6]
			mov	eax, [si + 2]
			mov	esi, ecx
			xor	esi, edx
			sar	esi, 31
			mov	edi, edx
			sar	edi, 31
			xor	eax, edi
			xor	edx, edi
			sub	eax, edi
			sbb	edx, edi
			mov	edi, ecx
			sar	edi, 31
			xor	ebx, edi
			xor	ecx, edi
			sub	ebx, edi
			sbb	ecx, edi
			jnz	big_divisor
			cmp	edx, ebx
			jae	two_divs
			div	ebx
			mov	edx, ecx
			xor	eax, esi
			xor	edx, esi
			sub	eax, esi
			sbb	edx, esi
			ret
		two_divs:
			mov	ecx, eax
			mov	eax, edx
			xor	edx, edx
			div	ebx
			xchg	eax, ecx
			div	ebx
			mov	edx, ecx
			jmp	make_sign
		big_divisor:
			push	esi
			sub	sp, 0xc
			mov	si, sp
			mov	[si], eax
			mov	[si + 4], ebx
			mov	[si + 8], edx
			mov	edi, ecx
			shr	edx, 1
			rcr	eax, 1
			ror	edi, 1
			rcr	ebx, 1
			bsr	ecx, ecx
			shrd	ebx, edi, cl
			shrd	eax, edx, cl
			shr	edx, cl
			rol	edi, 1
			div	ebx
			mov	ebx, [si]
			mov	ecx, eax
			imul	edi, eax
			mul	dword [si + 4]
			add	edx, edi
			sub	ebx, eax
			mov	eax, ecx
			mov	ecx, [si + 8]
			sbb	ecx, edx
			sbb	eax, 0
			xor	edx, edx
			add	sp, 0xc
			pop	esi
		make_sign:
			xor	eax, esi
			xor	edx, esi
			sub	eax, esi
			sbb	edx, esi
			ret

		.code _div_u8
			mov	si, sp
			mov	ecx, [si + 14]
			mov	ebx, [si + 10]
			mov	edx, [si + 6]
			mov	eax, [si + 2]
			test	ecx, ecx
			jnz	big_divisor
			cmp	edx, ebx
			jae	two_divs
			div	ebx
			mov	edx, ecx
			ret
		two_divs:
			mov	ecx, eax
			mov	eax, edx
			xor	edx, edx
			div	ebx
			xchg	eax, ecx
			div	ebx
			mov	edx, ecx
			ret
		big_divisor:
			mov	edi, ecx
			shr	edx, 1
			rcr	eax, 1
			ror	edi, 1
			rcr	ebx, 1
			bsr	ecx, ecx
			shrd	ebx, edi, cl
			shrd	eax, edx, cl
			shr	edx, cl
			rol	edi, 1
			div	ebx
			mov	ebx, [si + 2]
			mov	ecx, eax
			imul	edi, eax
			mul	dword [si + 10]
			add	edx, edi
			sub	ebx, eax
			mov	eax, ecx
			mov	ecx, [si + 6]
			sbb	ecx, edx
			sbb	eax, 0
			xor	edx, edx
			ret
	)");

#elif defined __amd32__

	asm target (R"(
		.code _div_s8
			mov	ecx, [esp + 16]
			mov	ebx, [esp + 12]
			mov	edx, [esp + 8]
			mov	eax, [esp + 4]
			mov	esi, ecx
			xor	esi, edx
			sar	esi, 31
			mov	edi, edx
			sar	edi, 31
			xor	eax, edi
			xor	edx, edi
			sub	eax, edi
			sbb	edx, edi
			mov	edi, ecx
			sar	edi, 31
			xor	ebx, edi
			xor	ecx, edi
			sub	ebx, edi
			sbb	ecx, edi
			jnz	big_divisor
			cmp	edx, ebx
			jae	two_divs
			div	ebx
			mov	edx, ecx
			xor	eax, esi
			xor	edx, esi
			sub	eax, esi
			sbb	edx, esi
			ret
		two_divs:
			mov	ecx, eax
			mov	eax, edx
			xor	edx, edx
			div	ebx
			xchg	eax, ecx
			div	ebx
			mov	edx, ecx
			jmp	make_sign
		big_divisor:
			sub	esp, 0xc
			mov	[esp], eax
			mov	[esp + 4], ebx
			mov	[esp + 8], edx
			mov	edi, ecx
			shr	edx, 1
			rcr	eax, 1
			ror	edi, 1
			rcr	ebx, 1
			bsr	ecx, ecx
			shrd	ebx, edi, cl
			shrd	eax, edx, cl
			shr	edx, cl
			rol	edi, 1
			div	ebx
			mov	ebx, [esp]
			mov	ecx, eax
			imul	edi, eax
			mul	dword [esp + 4]
			add	edx, edi
			sub	ebx, eax
			mov	eax, ecx
			mov	ecx, [esp + 8]
			sbb	ecx, edx
			sbb	eax, 0
			xor	edx, edx
			add	esp, 0xc
		make_sign:
			xor	eax, esi
			xor	edx, esi
			sub	eax, esi
			sbb	edx, esi
			ret

		.code _div_u8
			mov	ecx, [esp + 16]
			mov	ebx, [esp + 12]
			mov	edx, [esp + 8]
			mov	eax, [esp + 4]
			test	ecx, ecx
			jnz	big_divisor
			cmp	edx, ebx
			jae	two_divs
			div	ebx
			mov	edx, ecx
			ret
		two_divs:
			mov	ecx, eax
			mov	eax, edx
			xor	edx, edx
			div	ebx
			xchg	eax, ecx
			div	ebx
			mov	edx, ecx
			ret
		big_divisor:
			mov	edi, ecx
			shr	edx, 1
			rcr	eax, 1
			ror	edi, 1
			rcr	ebx, 1
			bsr	ecx, ecx
			shrd	ebx, edi, cl
			shrd	eax, edx, cl
			shr	edx, cl
			rol	edi, 1
			div	ebx
			mov	ebx, [esp + 4]
			mov	ecx, eax
			imul	edi, eax
			mul	dword [esp + 12]
			add	edx, edi
			sub	ebx, eax
			mov	eax, ecx
			mov	ecx, [esp + 8]
			sbb	ecx, edx
			sbb	eax, 0
			xor	edx, edx
			ret
	)");

#else

	s8 _div_s8 (s8 x, s8 y) 
	{
		u8 q = 0, r = 0; bool s = x < 0; if (s) x = -x; if (y < 0) s ^= true, y = -y;
		for (int i = 63; i >= 0; --i) if (r <<= 1, r |= (u8) (x >> i & 1), r >= y) r -= y, q |= (u8) (1) << i;
		return s ? -q : q;
	}

	u8 _div_u8 (const u8 x, const u8 y) 
	{
		u8 q = 0, r = 0;
		for (int i = 63; i >= 0; --i) if (r <<= 1, r |= (u8) (x >> i & 1), r >= y) r -= y, q |= (u8) (1) << i;
		return q;
	}

#endif

f4 _div_f4 (const f4 x, const f4 y) 
{
	union {f4 v; u4 c;} pa, pb, pr; pa.v = x; pb.v = y; fp4 a, b, r; UNPACK4 (pa, a); UNPACK4 (pb, b);
	r.s = a.s ^ b.s;
	r.m = (a.m << 8) / (b.m >> 15);
	r.e = a.e - b.e + 127;
	if (~r.m & 0x00800000) r.m <<= 1, r.e -= 1;
	PACK4 (r, pr); return pr.v;
}

f8 _div_f8 (const f8 x, const f8 y) 
{
	union {f8 v; u8 c;} pa, pb, pr; pa.v = x; pb.v = y; fp8 a, b, r; UNPACK8 (pa, a); UNPACK8 (pb, b);
	r.s = a.s ^ b.s;
	r.m = (a.m << 11) / (b.m >> 41);
	r.e = a.e - b.e + 1023;
	if (~r.m & 0x0010000000000000) r.m <<= 1, r.e -= 1;
	PACK8 (r, pr); return pr.v;
}

// intermediate mod instruction

s1 _mod_s1 (s1 x, s1 y) 
{
	u1 r = 0; bool s = x < 0; if (s) x = -x; if (y < 0) s ^= true, y = -y;
	for (int i = 7; i >= 0; --i) if (r <<= 1, r |= (u1) (x >> i & 1), r >= y) r -= y;
	return s ? -r : r;
}

u1 _mod_u1 (const u1 x, const u1 y) 
{
	u1 r = 0;
	for (int i = 7; i >= 0; --i) if (r <<= 1, r |= (u1) (x >> i & 1), r >= y) r -= y;
	return r;
}

s2 _mod_s2 (s2 x, s2 y) 
{
	u2 r = 0; bool s = x < 0; if (s) x = -x; if (y < 0) s ^= true, y = -y;
	for (int i = 15; i >= 0; --i) if (r <<= 1, r |= (u2) (x >> i & 1), r >= y) r -= y;
	return s ? -r : r;
}

u2 _mod_u2 (const u2 x, const u2 y) 
{
	u2 r = 0;
	for (int i = 15; i >= 0; --i) if (r <<= 1, r |= (u2) (x >> i & 1), r >= y) r -= y;
	return r;
}

#if defined __arma32__

	asm target (R"(
		.code _mod_s4
			ldr	r2, [sp, 0]
			ldr	r3, [sp, 4]
			mov	r0, r2, asr 31
			add	r2, r2, r0
			eor	r2, r2, r0
			mov	r1, r3, asr 31
			add	r3, r3, r1
			eor	r3, r3, r1
			eor	r1, r0, r1
			clz	r4, r2
			clz	r5, r3
			sub	r4, r5, r4
			add	r4, r4, 1
			mov	r5, 0
			b	check
		loop:	cmp	r2, r3, lsl r4
			adc	r5, r5, r5
			subcs	r2, r2, r3, lsl r4
		check:	subs	r4, r4, 1
			bpl	loop
			add	r0, r2, r1
			eor	r0, r0, r1
			bx	lr

		.code _mod_u4
			ldr	r2, [sp, 0]
			ldr	r3, [sp, 4]
			clz	r4, r2
			clz	r5, r3
			sub	r4, r5, r4
			add	r4, r4, 1
			mov	r5, 0
			b	check
		loop:	cmp	r2, r3, lsl r4
			adc	r5, r5, r5
			subcs	r2, r2, r3, lsl r4
		check:	subs	r4, r4, 1
			bpl	loop
			mov	r0, r2
			bx	lr
	)");

#else

	s4 _mod_s4 (s4 x, s4 y) 
	{
		u4 r = 0; bool s = x < 0; if (s) x = -x; if (y < 0) s ^= true, y = -y;
		for (int i = 31; i >= 0; --i) if (r <<= 1, r |= (u4) (x >> i & 1), r >= y) r -= y;
		return s ? -r : r;
	}

	u4 _mod_u4 (const u4 x, const u4 y) 
	{
		u4 r = 0;
		for (int i = 31; i >= 0; --i) if (r <<= 1, r |= (u4) (x >> i & 1), r >= y) r -= y;
		return r;
	}

#endif

#if defined __amd16__

	asm target (R"(
		.code _mod_s8
			mov	si, sp
			mov	ecx, [si + 14]
			mov	ebx, [si + 10]
			mov	edx, [si + 6]
			mov	eax, [si + 2]
			mov	esi, edx
			sar	esi, 31
			mov	edi, edx
			sar	edi, 31
			xor	eax, edi
			xor	edx, edi
			sub	eax, edi
			sbb	edx, edi
			mov	edi, ecx
			sar	edi, 31
			xor	ebx, edi
			xor	ecx, edi
			sub	ebx, edi
			sbb	ecx, edi
			jnz	sr_big_divisor
			cmp	edx, ebx
			jae	sr_two_divs
			div	ebx
			mov	eax, edx
			mov	edx, ecx
			xor	eax, esi
			xor	edx, esi
			sub	eax, esi
			sbb	edx, esi
			ret
		sr_two_divs:
			mov	ecx, eax
			mov	eax, edx
			xor	edx, edx
			div	ebx
			mov	eax, ecx
			div	ebx
			mov	eax, edx
			xor	edx, edx
			jmp	sr_makesign
		sr_big_divisor:
			push	esi
			sub	sp, 16
			mov	si, sp
			mov	[si], eax
			mov	[si + 4], ebx
			mov	[si + 8], edx
			mov	[si + 12], ecx
			mov	edi, ecx
			shr	edx, 1
			rcr	eax, 1
			ror	edi, 1
			rcr	ebx, 1
			bsr	ecx, ecx
			shrd	ebx, edi, cl
			shrd	eax, edx, cl
			shr	edx, cl
			rol	edi, 1
			div	ebx
			mov	ebx, [si]
			mov	ecx, eax
			imul	edi, eax
			mul	dword [si + 4]
			add	edx, edi
			sub	ebx, eax
			mov	ecx, [si + 8]
			sbb	ecx, edx
			sbb	eax, eax
			mov	edx, [si + 12]
			and	edx, eax
			and	eax, [si + 4]
			add	eax, ebx
			add	edx, ecx
			add	sp, 16
			pop	esi
		sr_makesign:
			xor	eax, esi
			xor	edx, esi
			sub	eax, esi
			sbb	edx, esi
			ret

		.code _mod_u8
			mov	si, sp
			mov	ecx, [si + 14]
			mov	ebx, [si + 10]
			mov	edx, [si + 6]
			mov	eax, [si + 2]
			test	ecx, ecx
			jnz	r_big_divisor
			cmp	edx, ebx
			jae	r_two_divs
			div	ebx
			mov	eax, edx
			mov	edx, ecx
			ret
		r_two_divs:
			mov	ecx, eax
			mov	eax, edx
			xor	edx, edx
			div	ebx
			mov	eax, ecx
			div	ebx
			mov	eax, edx
			xor	edx, edx
			ret
		r_big_divisor:
			mov	edi, ecx
			shr	edx, 1
			rcr	eax, 1
			ror	edi, 1
			rcr	ebx, 1
			bsr	ecx, ecx
			shrd	ebx, edi, cl
			shrd	eax, edx, cl
			shr	edx, cl
			rol	edi, 1
			div	ebx
			mov	ebx, [si + 2]
			mov	ecx, eax
			imul	edi, eax
			mul	dword [si + 10]
			add	edx, edi
			sub	ebx, eax
			mov	ecx, [si + 6]
			mov	eax, [si + 10]
			sbb	ecx, edx
			sbb	edx, edx
			and	eax, edx
			and	edx, [si + 14]
			add	eax, ebx
			ret
	)");

#elif defined __amd32__

	asm target (R"(
		.code _mod_s8
			mov	ecx, [esp + 16]
			mov	ebx, [esp + 12]
			mov	edx, [esp + 8]
			mov	eax, [esp + 4]
			mov	esi, edx
			sar	esi, 31
			mov	edi, edx
			sar	edi, 31
			xor	eax, edi
			xor	edx, edi
			sub	eax, edi
			sbb	edx, edi
			mov	edi, ecx
			sar	edi, 31
			xor	ebx, edi
			xor	ecx, edi
			sub	ebx, edi
			sbb	ecx, edi
			jnz	sr_big_divisor
			cmp	edx, ebx
			jae	sr_two_divs
			div	ebx
			mov	eax, edx
			mov	edx, ecx
			xor	eax, esi
			xor	edx, esi
			sub	eax, esi
			sbb	edx, esi
			ret
		sr_two_divs:
			mov	ecx, eax
			mov	eax, edx
			xor	edx, edx
			div	ebx
			mov	eax, ecx
			div	ebx
			mov	eax, edx
			xor	edx, edx
			jmp	sr_makesign
		sr_big_divisor:
			sub	esp, 16
			mov	[esp], eax
			mov	[esp + 4], ebx
			mov	[esp + 8], edx
			mov	[esp + 12], ecx
			mov	edi, ecx
			shr	edx, 1
			rcr	eax, 1
			ror	edi, 1
			rcr	ebx, 1
			bsr	ecx, ecx
			shrd	ebx, edi, cl
			shrd	eax, edx, cl
			shr	edx, cl
			rol	edi, 1
			div	ebx
			mov	ebx, [esp]
			mov	ecx, eax
			imul	edi, eax
			mul	dword [esp + 4]
			add	edx, edi
			sub	ebx, eax
			mov	ecx, [esp + 8]
			sbb	ecx, edx
			sbb	eax, eax
			mov	edx, [esp + 12]
			and	edx, eax
			and	eax, [esp + 4]
			add	eax, ebx
			add	edx, ecx
			add	esp, 16
		sr_makesign:
			xor	eax, esi
			xor	edx, esi
			sub	eax, esi
			sbb	edx, esi
			ret

		.code _mod_u8
			mov	ecx, [esp + 16]
			mov	ebx, [esp + 12]
			mov	edx, [esp + 8]
			mov	eax, [esp + 4]
			test	ecx, ecx
			jnz	r_big_divisor
			cmp	edx, ebx
			jae	r_two_divs
			div	ebx
			mov	eax, edx
			mov	edx, ecx
			ret
		r_two_divs:
			mov	ecx, eax
			mov	eax, edx
			xor	edx, edx
			div	ebx
			mov	eax, ecx
			div	ebx
			mov	eax, edx
			xor	edx, edx
			ret
		r_big_divisor:
			mov	edi, ecx
			shr	edx, 1
			rcr	eax, 1
			ror	edi, 1
			rcr	ebx, 1
			bsr	ecx, ecx
			shrd	ebx, edi, cl
			shrd	eax, edx, cl
			shr	edx, cl
			rol	edi, 1
			div	ebx
			mov	ebx, [esp + 4]
			mov	ecx, eax
			imul	edi, eax
			mul	dword [esp + 12]
			add	edx, edi
			sub	ebx, eax
			mov	ecx, [esp + 8]
			mov	eax, [esp + 12]
			sbb	ecx, edx
			sbb	edx, edx
			and	eax, edx
			and	edx, [esp + 16]
			add	eax, ebx
			ret
	)");

#else

	s8 _mod_s8 (s8 x, s8 y) 
	{
		u8 r = 0; bool s = x < 0; if (s) x = -x; if (y < 0) s ^= true, y = -y;
		for (int i = 63; i >= 0; --i) if (r <<= 1, r |= (u8) (x >> i & 1), r >= y) r -= y;
		return s ? -r : r;
	}

	u8 _mod_u8 (const u8 x, const u8 y) 
	{
		u8 r = 0;
		for (int i = 63; i >= 0; --i) if (r <<= 1, r |= (u8) (x >> i & 1), r >= y) r -= y;
		return r;
	}

#endif

// intermediate lsh instruction

#if defined __amd16__

	asm target (R"(
		.code _lsh_s8
			.alias	_lsh_u8
			mov	si, sp
			mov	eax, [si + 2]
			mov	edx, [si + 6]
			mov	ecx, [si + 10]
			shld	edx, eax, cl
			shl	eax, cl
			test	ecx, 32
			jz	done
			mov	edx, eax
			xor	eax, eax
		done:	ret
	)");

#elif defined __amd32__

	asm target (R"(
		.code _lsh_s8
			.alias	_lsh_u8
			mov	eax, [esp + 4]
			mov	edx, [esp + 8]
			mov	ecx, [esp + 12]
			shld	edx, eax, cl
			shl	eax, cl
			test	ecx, 32
			jz	done
			mov	edx, eax
			xor	eax, eax
		done:	ret
	)");

#elif defined __arma32__

	asm target (R"(
		.code _lsh_s8
			.alias	_lsh_u8
			ldr	r2, [sp, 0]
			ldr	r3, [sp, 4]
			ldr	r4, [sp, 8]
			ldr	r5, [sp, 12]
			cmp	r5, 0
			movne	r4, 64
			rsbs	r5, r4, 32
			submi	r5, r4, 32
			movmi	r1, r2, lsl r5
			movpl	r1, r3, lsl r4
			orrpl	r1, r1, r2, lsr r5
			mov	r0, r2, lsl r4
			bx	lr
	)");

#else

	s8 _lsh_s8 (const s8 x, const s8 y) 
	{
		union {s8 v; us8 c;} a, b, r; a.v = x; b.v = y;
		if (b.c.l == 0) r.c.l = a.c.l, r.c.h = a.c.h;
		else if (b.c.l >= 32) r.c.l = 0, r.c.h = a.c.l << b.c.l - 32;
		else r.c.l = a.c.l << b.c.l, r.c.h = a.c.h << b.c.l | a.c.l >> 32 - b.c.l;
		return r.v;
	}
	
	s8 _lsh_u8(const s8 x, const s8 y) { return _lsh_s8(x,y); }

#endif

// intermediate rsh instruction

#if defined __amd16__

	asm target (R"(
		.code _rsh_s8
			mov	si, sp
			mov	eax, [si + 2]
			mov	edx, [si + 6]
			mov	ecx, [si + 10]
			shrd	eax, edx, cl
			sar	edx, cl
			test	ecx, 32
			jz	done
			mov	eax, edx
			cdq
		done:	ret

		.code _rsh_u8
			mov	si, sp
			mov	eax, [si + 2]
			mov	edx, [si + 6]
			mov	ecx, [si + 10]
			shrd	eax, edx, cl
			shr	edx, cl
			test	ecx, 32
			jz	done
			mov	eax, edx
			xor	edx, edx
		done:	ret
	)");

#elif defined __amd32__

	asm target (R"(
		.code _rsh_s8
			mov	eax, [esp + 4]
			mov	edx, [esp + 8]
			mov	ecx, [esp + 12]
			shrd	eax, edx, cl
			sar	edx, cl
			test	ecx, 32
			jz	done
			mov	eax, edx
			cdq
		done:	ret

		.code _rsh_u8
			mov	eax, [esp + 4]
			mov	edx, [esp + 8]
			mov	ecx, [esp + 12]
			shrd	eax, edx, cl
			shr	edx, cl
			test	ecx, 32
			jz	done
			mov	eax, edx
			xor	edx, edx
		done:	ret
	)");

#elif defined __arma32__

	asm target (R"(
		.code _rsh_s8
			ldr	r2, [sp, 0]
			ldr	r3, [sp, 4]
			ldr	r4, [sp, 8]
			ldr	r5, [sp, 12]
			cmp	r5, 0
			movne	r4, 64
			rsbs	r5, r4, 32
			submi	r5, r4, 32
			movmi	r0, r3, asr r5
			movpl	r0, r2, lsr r4
			orrpl	r0, r0, r3, lsl r5
			mov	r1, r3, asr r4
			bx	lr

		.code _rsh_u8
			ldr	r2, [sp, 0]
			ldr	r3, [sp, 4]
			ldr	r4, [sp, 8]
			ldr	r5, [sp, 12]
			cmp	r5, 0
			movne	r4, 64
			rsbs	r5, r4, 32
			submi	r5, r4, 32
			movmi	r0, r3, lsr r5
			movpl	r0, r2, lsr r4
			orrpl	r0, r0, r3, lsl r5
			mov	r1, r3, lsr r4
			bx	lr
	)");

#else

	s8 _rsh_s8 (const s8 x, const s8 y) 
	{
		union {s8 v; us8 c;} a, b, r; a.v = x; b.v = y;
		if (b.c.l == 0) r.c.l = a.c.l, r.c.h = a.c.h;
		else if (b.c.l >= 32) r.c.l = a.c.h >> (s4) (b.c.l) - 32, r.c.h = a.c.h >> 31;
		else r.c.l = a.c.l >> b.c.l | a.c.h << 32 - b.c.l, r.c.h = a.c.h >> (s4) (b.c.l);
		return r.v;
	}

	u8 _rsh_u8 (const u8 x, const u8 y) 
	{
		union {u8 v; uu8 c;} a, b, r; a.v = x; b.v = y;
		if (b.c.l == 0) r.c.l = a.c.l, r.c.h = a.c.h;
		else if (b.c.l >= 32) r.c.l = a.c.h >> b.c.l - 32, r.c.h = 0;
		else r.c.l = a.c.l >> b.c.l | a.c.h << 32 - b.c.l, r.c.h = a.c.h >> b.c.l;
		return r.v;
	}

#endif

// intermediate breq instruction

bool _breq_f4 (const f4 x, const f4 y) 
{
	union {f4 v; u4 c;} a, b; a.v = x; b.v = y;
	return a.c == b.c;
}

bool _breq_f8 (const f8 x, const f8 y) 
{
	union {f8 v; u8 c;} a, b; a.v = x; b.v = y;
	return a.c == b.c;
}

// intermediate brne instruction

bool _brne_f4 (const f4 x, const f4 y) 
{
	union {f4 v; u4 c;} a, b; a.v = x; b.v = y;
	return a.c != b.c;
}

bool _brne_f8 (const f8 x, const f8 y) 
{
	union {f8 v; u8 c;} a, b; a.v = x; b.v = y;
	return a.c != b.c;
}

// intermediate brlt instruction

bool _brlt_f4 (const f4 x, const f4 y) 
{
	union {f4 v; u4 c;} pa, pb; pa.v = x; pb.v = y; fp4 a, b; UNPACK4 (pa, a); UNPACK4 (pb, b);
	return a.s > b.s || a.s == b.s && (a.s ? a.e > b.e || a.e == b.e && a.m > b.m : a.e < b.e || a.e == b.e && a.m < b.m);
}

bool _brlt_f8 (const f8 x, const f8 y) 
{
	union {f8 v; u8 c;} pa, pb; pa.v = x; pb.v = y; fp8 a, b; UNPACK8 (pa, a); UNPACK8 (pb, b);
	return a.s > b.s || a.s == b.s && (a.s ? a.e > b.e || a.e == b.e && a.m > b.m : a.e < b.e || a.e == b.e && a.m < b.m);
}

// intermediate brge instruction

bool _brge_f4 (const f4 x, const f4 y) 
{
	union {f4 v; u4 c;} pa, pb; pa.v = x; pb.v = y; fp4 a, b; UNPACK4 (pa, a); UNPACK4 (pb, b);
	return a.s < b.s || a.s == b.s && (a.s ? a.e < b.e || a.e == b.e && a.m <= b.m : a.e > b.e || a.e == b.e && a.m >= b.m);
}

bool _brge_f8 (const f8 x, const f8 y) 
{
	union {f8 v; u8 c;} pa, pb; pa.v = x; pb.v = y; fp8 a, b; UNPACK8 (pa, a); UNPACK8 (pb, b);
	return a.s < b.s || a.s == b.s && (a.s ? a.e < b.e || a.e == b.e && a.m <= b.m : a.e > b.e || a.e == b.e && a.m >= b.m);
}


