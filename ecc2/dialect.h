/*
 * This file is part of cparser.
 * Copyright (C) 2012 Matthias Braun <matze@braunis.de>
 */
#ifndef DIALECT_H
#define DIALECT_H

#include <stdbool.h>

#define BITS_PER_BYTE    8

typedef enum lang_features_t {
	_C89  = 1U << 0,
	_C99  = 1U << 1,
	_C11  = 1U << 2,
	_CXX  = 1U << 3,
	_GNUC = 1U << 4,
	_MS   = 1U << 5,
	_ALL  = 0xFF
} lang_features_t;

typedef struct c_dialect_t {
	bool freestanding              : 1;
	bool no_builtins               : 1;
	bool strict                    : 1;
	bool c89                       : 1;
	bool c99                       : 1;
	bool c11                       : 1;
	bool cpp                       : 1;
	bool gnu                       : 1;
	bool ms                        : 1;
	/** enable hack to add call to __main into the main function (mingw) */
	bool enable_main_collect2_hack : 1;
	bool support_fastcall_stdcall  : 1;
	lang_features_t features;
} c_dialect_t;

extern c_dialect_t dialect;

#endif
