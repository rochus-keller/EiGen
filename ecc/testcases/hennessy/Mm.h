#ifndef _MM_
#define _MM_

// Generated by Oberon+ IDE (Mono) 0.9.107 on 2024-08-10T01:27:54

#include "OBX.Runtime.h"
#include "Util.h"

// Declaration of module Mm

extern double Mm$rma[41][41];
extern double Mm$rmb[41][41];
extern double Mm$rmr[41][41];
void Mm$rInitmatrix(struct OBX$Array$2 m);
void Mm$rInnerproduct(double * result, struct OBX$Array$2 a, struct OBX$Array$2 b, int32_t row, int32_t column);
void Mm$Run();
extern void Mm$init$(void);
extern OBX$Cmd Mm$cmd$(const char* name);
#endif