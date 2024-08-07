#ifndef _SOM$VECTOR$E0832C0C14_
#define _SOM$VECTOR$E0832C0C14_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "som.Interfaces.e0832c0c14.h"

// Declaration of module som.Vector(CD.Motion)

struct CD$Motion; // meta actual
struct som$Vector$e0832c0c14$Vector$Class$;
struct som$Vector$e0832c0c14$Vector;
struct som$Vector$e0832c0c14$Vector {
    struct som$Vector$e0832c0c14$Vector$Class$* class$;
    struct OBX$Array$1 storage;
    int32_t firstIdx;
    int32_t lastIdx;
};

extern void som$Vector$e0832c0c14$Vector$init$(struct som$Vector$e0832c0c14$Vector*);
struct som$Vector$e0832c0c14$Vector * som$Vector$e0832c0c14$createWithSize(int32_t siz);
struct som$Vector$e0832c0c14$Vector * som$Vector$e0832c0c14$create();
struct som$Vector$e0832c0c14$Vector * som$Vector$e0832c0c14$createWithElement(struct CD$Motion * * elem);
struct CD$Motion * som$Vector$e0832c0c14$Vector$at(void* this, int32_t idx);
void som$Vector$e0832c0c14$Vector$resize(void* this, int32_t newLength);
void som$Vector$e0832c0c14$Vector$atPut(void* this, int32_t idx, struct CD$Motion * * elem);
void som$Vector$e0832c0c14$Vector$append(void* this, struct CD$Motion * * elem);
uint8_t som$Vector$e0832c0c14$Vector$isEmpty(void* this);
struct CD$Motion * som$Vector$e0832c0c14$Vector$first(void* this);
struct CD$Motion * som$Vector$e0832c0c14$Vector$removeFirst(void* this);
void som$Vector$e0832c0c14$Vector$removeAll(void* this);
int32_t som$Vector$e0832c0c14$Vector$getSize(void* this);
int32_t som$Vector$e0832c0c14$Vector$capacity(void* this);
void som$Vector$e0832c0c14$Vector$forEach(void* this, struct som$Interfaces$e0832c0c14$ForEachInterface * fn);
uint8_t som$Vector$e0832c0c14$Vector$hasSome(void* this, struct som$Interfaces$e0832c0c14$TestInterface * fn);
uint8_t som$Vector$e0832c0c14$Vector$getOne(void* this, struct som$Interfaces$e0832c0c14$TestInterface * fn, struct CD$Motion * * out);
uint8_t som$Vector$e0832c0c14$Vector$remove(void* this, struct CD$Motion * * obj, uint8_t (*eq)(struct CD$Motion * *, struct CD$Motion * *));
void som$Vector$e0832c0c14$Vector$sort(void* this, struct som$Interfaces$e0832c0c14$Comparator * c);
void som$Vector$e0832c0c14$Vector$sortImp(void* this, int32_t i, int32_t j, struct som$Interfaces$e0832c0c14$Comparator * c);
void som$Vector$e0832c0c14$swap(struct OBX$Array$1 storage2, int32_t i, int32_t j);
struct som$Vector$e0832c0c14$Vector$Class$ {
    struct som$Vector$e0832c0c14$Vector$Class$* super$;
    struct CD$Motion * (*at)(void* this, int32_t idx);
    void (*resize)(void* this, int32_t newLength);
    void (*atPut)(void* this, int32_t idx, struct CD$Motion * * elem);
    void (*append)(void* this, struct CD$Motion * * elem);
    uint8_t (*isEmpty)(void* this);
    struct CD$Motion * (*first)(void* this);
    struct CD$Motion * (*removeFirst)(void* this);
    void (*removeAll)(void* this);
    int32_t (*getSize)(void* this);
    int32_t (*capacity)(void* this);
    void (*forEach)(void* this, struct som$Interfaces$e0832c0c14$ForEachInterface * fn);
    uint8_t (*hasSome)(void* this, struct som$Interfaces$e0832c0c14$TestInterface * fn);
    uint8_t (*getOne)(void* this, struct som$Interfaces$e0832c0c14$TestInterface * fn, struct CD$Motion * * out);
    uint8_t (*remove)(void* this, struct CD$Motion * * obj, uint8_t (*eq)(struct CD$Motion * *, struct CD$Motion * *));
    void (*sort)(void* this, struct som$Interfaces$e0832c0c14$Comparator * c);
    void (*sortImp)(void* this, int32_t i, int32_t j, struct som$Interfaces$e0832c0c14$Comparator * c);
};
extern struct som$Vector$e0832c0c14$Vector$Class$ som$Vector$e0832c0c14$Vector$class$;

extern void som$Vector$e0832c0c14$init$(void);
extern OBX$Cmd som$Vector$e0832c0c14$cmd$(const char* name);
#endif
