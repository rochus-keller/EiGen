#ifndef _INTMM_
#define _INTMM_

// Generated by Oberon+ IDE (Mono) 0.9.107 on 2024-08-10T01:27:54

#include "OBX.Runtime.h"
#include "Util.h"

// Declaration of module Intmm

extern int32_t Intmm$ima[41][41];
extern int32_t Intmm$imb[41][41];
extern int32_t Intmm$imr[41][41];
void Intmm$Initmatrix(struct OBX$Array$2 m);
void Intmm$Innerproduct(int32_t * result, struct OBX$Array$2 a, struct OBX$Array$2 b, int32_t row, int32_t column);
void Intmm$Run();
extern void Intmm$init$(void);
extern OBX$Cmd Intmm$cmd$(const char* name);
#endif
