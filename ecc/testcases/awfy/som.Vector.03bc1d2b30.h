#ifndef _SOM$VECTOR$03BC1D2B30_
#define _SOM$VECTOR$03BC1D2B30_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "som.Interfaces.03bc1d2b30.h"

// Declaration of module som.Vector(CD2.CallSign)

struct CD2$CallSign; // meta actual
struct som$Vector$03bc1d2b30$Vector$Class$;
struct som$Vector$03bc1d2b30$Vector;
struct som$Vector$03bc1d2b30$Vector {
    struct som$Vector$03bc1d2b30$Vector$Class$* class$;
    struct OBX$Array$1 storage;
    int32_t firstIdx;
    int32_t lastIdx;
};

extern void som$Vector$03bc1d2b30$Vector$init$(struct som$Vector$03bc1d2b30$Vector*);
struct som$Vector$03bc1d2b30$Vector * som$Vector$03bc1d2b30$createWithSize(int32_t siz);
struct som$Vector$03bc1d2b30$Vector * som$Vector$03bc1d2b30$create();
struct som$Vector$03bc1d2b30$Vector * som$Vector$03bc1d2b30$createWithElement(struct CD2$CallSign * * elem);
struct CD2$CallSign * som$Vector$03bc1d2b30$Vector$at(void* this, int32_t idx);
void som$Vector$03bc1d2b30$Vector$resize(void* this, int32_t newLength);
void som$Vector$03bc1d2b30$Vector$atPut(void* this, int32_t idx, struct CD2$CallSign * * elem);
void som$Vector$03bc1d2b30$Vector$append(void* this, struct CD2$CallSign * * elem);
uint8_t som$Vector$03bc1d2b30$Vector$isEmpty(void* this);
struct CD2$CallSign * som$Vector$03bc1d2b30$Vector$first(void* this);
struct CD2$CallSign * som$Vector$03bc1d2b30$Vector$removeFirst(void* this);
void som$Vector$03bc1d2b30$Vector$removeAll(void* this);
int32_t som$Vector$03bc1d2b30$Vector$getSize(void* this);
int32_t som$Vector$03bc1d2b30$Vector$capacity(void* this);
void som$Vector$03bc1d2b30$Vector$forEach(void* this, struct som$Interfaces$03bc1d2b30$ForEachInterface * fn);
uint8_t som$Vector$03bc1d2b30$Vector$hasSome(void* this, struct som$Interfaces$03bc1d2b30$TestInterface * fn);
uint8_t som$Vector$03bc1d2b30$Vector$getOne(void* this, struct som$Interfaces$03bc1d2b30$TestInterface * fn, struct CD2$CallSign * * out);
uint8_t som$Vector$03bc1d2b30$Vector$remove(void* this, struct CD2$CallSign * * obj, uint8_t (*eq)(struct CD2$CallSign * *, struct CD2$CallSign * *));
void som$Vector$03bc1d2b30$Vector$sort(void* this, struct som$Interfaces$03bc1d2b30$Comparator * c);
void som$Vector$03bc1d2b30$Vector$sortImp(void* this, int32_t i, int32_t j, struct som$Interfaces$03bc1d2b30$Comparator * c);
void som$Vector$03bc1d2b30$swap(struct OBX$Array$1 storage2, int32_t i, int32_t j);
struct som$Vector$03bc1d2b30$Vector$Class$ {
    struct som$Vector$03bc1d2b30$Vector$Class$* super$;
    struct CD2$CallSign * (*at)(void* this, int32_t idx);
    void (*resize)(void* this, int32_t newLength);
    void (*atPut)(void* this, int32_t idx, struct CD2$CallSign * * elem);
    void (*append)(void* this, struct CD2$CallSign * * elem);
    uint8_t (*isEmpty)(void* this);
    struct CD2$CallSign * (*first)(void* this);
    struct CD2$CallSign * (*removeFirst)(void* this);
    void (*removeAll)(void* this);
    int32_t (*getSize)(void* this);
    int32_t (*capacity)(void* this);
    void (*forEach)(void* this, struct som$Interfaces$03bc1d2b30$ForEachInterface * fn);
    uint8_t (*hasSome)(void* this, struct som$Interfaces$03bc1d2b30$TestInterface * fn);
    uint8_t (*getOne)(void* this, struct som$Interfaces$03bc1d2b30$TestInterface * fn, struct CD2$CallSign * * out);
    uint8_t (*remove)(void* this, struct CD2$CallSign * * obj, uint8_t (*eq)(struct CD2$CallSign * *, struct CD2$CallSign * *));
    void (*sort)(void* this, struct som$Interfaces$03bc1d2b30$Comparator * c);
    void (*sortImp)(void* this, int32_t i, int32_t j, struct som$Interfaces$03bc1d2b30$Comparator * c);
};
extern struct som$Vector$03bc1d2b30$Vector$Class$ som$Vector$03bc1d2b30$Vector$class$;

extern void som$Vector$03bc1d2b30$init$(void);
extern OBX$Cmd som$Vector$03bc1d2b30$cmd$(const char* name);
#endif
