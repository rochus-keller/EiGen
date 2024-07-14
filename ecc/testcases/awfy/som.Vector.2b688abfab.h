#ifndef _SOM$VECTOR$2B688ABFAB_
#define _SOM$VECTOR$2B688ABFAB_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "som.Interfaces.2b688abfab.h"

// Declaration of module som.Vector(Havlak.SimpleLoop)

struct Havlak$SimpleLoop; // meta actual
struct som$Vector$2b688abfab$Vector$Class$;
struct som$Vector$2b688abfab$Vector;
struct som$Vector$2b688abfab$Vector {
    struct som$Vector$2b688abfab$Vector$Class$* class$;
    struct OBX$Array$1 storage;
    int32_t firstIdx;
    int32_t lastIdx;
};

extern void som$Vector$2b688abfab$Vector$init$(struct som$Vector$2b688abfab$Vector*);
struct som$Vector$2b688abfab$Vector * som$Vector$2b688abfab$createWithSize(int32_t siz);
struct som$Vector$2b688abfab$Vector * som$Vector$2b688abfab$create();
struct som$Vector$2b688abfab$Vector * som$Vector$2b688abfab$createWithElement(struct Havlak$SimpleLoop * * elem);
struct Havlak$SimpleLoop * som$Vector$2b688abfab$Vector$at(void* this, int32_t idx);
void som$Vector$2b688abfab$Vector$resize(void* this, int32_t newLength);
void som$Vector$2b688abfab$Vector$atPut(void* this, int32_t idx, struct Havlak$SimpleLoop * * elem);
void som$Vector$2b688abfab$Vector$append(void* this, struct Havlak$SimpleLoop * * elem);
uint8_t som$Vector$2b688abfab$Vector$isEmpty(void* this);
struct Havlak$SimpleLoop * som$Vector$2b688abfab$Vector$first(void* this);
struct Havlak$SimpleLoop * som$Vector$2b688abfab$Vector$removeFirst(void* this);
void som$Vector$2b688abfab$Vector$removeAll(void* this);
int32_t som$Vector$2b688abfab$Vector$getSize(void* this);
int32_t som$Vector$2b688abfab$Vector$capacity(void* this);
void som$Vector$2b688abfab$Vector$forEach(void* this, struct som$Interfaces$2b688abfab$ForEachInterface * fn);
uint8_t som$Vector$2b688abfab$Vector$hasSome(void* this, struct som$Interfaces$2b688abfab$TestInterface * fn);
uint8_t som$Vector$2b688abfab$Vector$getOne(void* this, struct som$Interfaces$2b688abfab$TestInterface * fn, struct Havlak$SimpleLoop * * out);
uint8_t som$Vector$2b688abfab$Vector$remove(void* this, struct Havlak$SimpleLoop * * obj, uint8_t (*eq)(struct Havlak$SimpleLoop * *, struct Havlak$SimpleLoop * *));
void som$Vector$2b688abfab$Vector$sort(void* this, struct som$Interfaces$2b688abfab$Comparator * c);
void som$Vector$2b688abfab$Vector$sortImp(void* this, int32_t i, int32_t j, struct som$Interfaces$2b688abfab$Comparator * c);
void som$Vector$2b688abfab$swap(struct OBX$Array$1 storage2, int32_t i, int32_t j);
struct som$Vector$2b688abfab$Vector$Class$ {
    struct som$Vector$2b688abfab$Vector$Class$* super$;
    struct Havlak$SimpleLoop * (*at)(void* this, int32_t idx);
    void (*resize)(void* this, int32_t newLength);
    void (*atPut)(void* this, int32_t idx, struct Havlak$SimpleLoop * * elem);
    void (*append)(void* this, struct Havlak$SimpleLoop * * elem);
    uint8_t (*isEmpty)(void* this);
    struct Havlak$SimpleLoop * (*first)(void* this);
    struct Havlak$SimpleLoop * (*removeFirst)(void* this);
    void (*removeAll)(void* this);
    int32_t (*getSize)(void* this);
    int32_t (*capacity)(void* this);
    void (*forEach)(void* this, struct som$Interfaces$2b688abfab$ForEachInterface * fn);
    uint8_t (*hasSome)(void* this, struct som$Interfaces$2b688abfab$TestInterface * fn);
    uint8_t (*getOne)(void* this, struct som$Interfaces$2b688abfab$TestInterface * fn, struct Havlak$SimpleLoop * * out);
    uint8_t (*remove)(void* this, struct Havlak$SimpleLoop * * obj, uint8_t (*eq)(struct Havlak$SimpleLoop * *, struct Havlak$SimpleLoop * *));
    void (*sort)(void* this, struct som$Interfaces$2b688abfab$Comparator * c);
    void (*sortImp)(void* this, int32_t i, int32_t j, struct som$Interfaces$2b688abfab$Comparator * c);
};
extern struct som$Vector$2b688abfab$Vector$Class$ som$Vector$2b688abfab$Vector$class$;

extern void som$Vector$2b688abfab$init$(void);
extern OBX$Cmd som$Vector$2b688abfab$cmd$(const char* name);
#endif