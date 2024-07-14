#ifndef _QUEENS_
#define _QUEENS_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "Benchmark.h"

// Declaration of module Queens

struct Queens$Queens$Class$;
struct Queens$Queens;
struct Queens$Queens {
    struct Queens$Queens$Class$* class$;
    uint8_t freeRows[8];
    uint8_t freeMaxs[16];
    uint8_t freeMins[16];
    int32_t queenRows[8];
};

extern void Queens$Queens$init$(struct Queens$Queens*);
struct Queens$Queens * Queens$create();
struct Benchmark$Result * Queens$Queens$benchmark(void* this);
uint8_t Queens$Queens$queens(void* this);
uint8_t Queens$Queens$placeQueen(void* this, int32_t c);
uint8_t Queens$Queens$getRowColumn(void* this, int32_t r, int32_t c);
void Queens$Queens$setRowColumn(void* this, int32_t r, int32_t c, uint8_t v);
uint8_t Queens$Queens$verifyResult(void* this, struct Benchmark$Result * result);
struct Queens$Queens$Class$ {
    struct Benchmark$Benchmark$Class$* super$;
    struct Benchmark$Result * (*benchmark)(void* this);
    uint8_t (*verifyResult)(void* this, struct Benchmark$Result * result);
    uint8_t (*innerBenchmarkLoop)(void* this, int32_t innerIterations);
    uint8_t (*queens)(void* this);
    uint8_t (*placeQueen)(void* this, int32_t c);
    uint8_t (*getRowColumn)(void* this, int32_t r, int32_t c);
    void (*setRowColumn)(void* this, int32_t r, int32_t c, uint8_t v);
};
extern struct Queens$Queens$Class$ Queens$Queens$class$;

extern void Queens$init$(void);
extern OBX$Cmd Queens$cmd$(const char* name);
#endif