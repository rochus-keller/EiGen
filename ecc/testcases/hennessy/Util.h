#ifndef _UTIL_
#define _UTIL_

// Generated by Oberon+ IDE (Mono) 0.9.107 on 2024-08-10T01:27:54

#include "OBX.Runtime.h"
#include "Input.h"
#include "Out.h"

// Declaration of module Util

extern int32_t Util$seed;
void Util$Str(struct OBX$Array$1 s);
int32_t Util$Getclock();
void Util$Initrand();
int32_t Util$Rand();
extern void Util$init$(void);
extern OBX$Cmd Util$cmd$(const char* name);
#endif