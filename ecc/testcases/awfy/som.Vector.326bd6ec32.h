#ifndef _SOM$VECTOR$326BD6EC32_
#define _SOM$VECTOR$326BD6EC32_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "som.Interfaces.326bd6ec32.h"

// Declaration of module som.Vector(CD.Collision)

struct CD$Collision;
struct CD$Collision; // meta actual
struct som$Vector$326bd6ec32$Vector$Class$;
struct som$Vector$326bd6ec32$Vector;
struct som$Vector$326bd6ec32$Vector {
    struct som$Vector$326bd6ec32$Vector$Class$* class$;
    struct OBX$Array$1 storage;
    int32_t firstIdx;
    int32_t lastIdx;
};

extern void som$Vector$326bd6ec32$Vector$init$(struct som$Vector$326bd6ec32$Vector*);
struct som$Vector$326bd6ec32$Vector * som$Vector$326bd6ec32$createWithSize(int32_t siz);
struct som$Vector$326bd6ec32$Vector * som$Vector$326bd6ec32$create();
struct som$Vector$326bd6ec32$Vector * som$Vector$326bd6ec32$createWithElement(struct CD$Collision * elem);
struct CD$Collision som$Vector$326bd6ec32$Vector$at(void* this, int32_t idx);
void som$Vector$326bd6ec32$Vector$resize(void* this, int32_t newLength);
void som$Vector$326bd6ec32$Vector$atPut(void* this, int32_t idx, struct CD$Collision * elem);
void som$Vector$326bd6ec32$Vector$append(void* this, struct CD$Collision * elem);
uint8_t som$Vector$326bd6ec32$Vector$isEmpty(void* this);
struct CD$Collision som$Vector$326bd6ec32$Vector$first(void* this);
struct CD$Collision som$Vector$326bd6ec32$Vector$removeFirst(void* this);
void som$Vector$326bd6ec32$Vector$removeAll(void* this);
int32_t som$Vector$326bd6ec32$Vector$getSize(void* this);
int32_t som$Vector$326bd6ec32$Vector$capacity(void* this);
void som$Vector$326bd6ec32$Vector$forEach(void* this, struct som$Interfaces$326bd6ec32$ForEachInterface * fn);
uint8_t som$Vector$326bd6ec32$Vector$hasSome(void* this, struct som$Interfaces$326bd6ec32$TestInterface * fn);
uint8_t som$Vector$326bd6ec32$Vector$getOne(void* this, struct som$Interfaces$326bd6ec32$TestInterface * fn, struct CD$Collision * out);
uint8_t som$Vector$326bd6ec32$Vector$remove(void* this, struct CD$Collision * obj, uint8_t (*eq)(struct CD$Collision *, struct CD$Collision *));
void som$Vector$326bd6ec32$Vector$sort(void* this, struct som$Interfaces$326bd6ec32$Comparator * c);
void som$Vector$326bd6ec32$Vector$sortImp(void* this, int32_t i, int32_t j, struct som$Interfaces$326bd6ec32$Comparator * c);
void som$Vector$326bd6ec32$swap(struct OBX$Array$1 storage2, int32_t i, int32_t j);
struct som$Vector$326bd6ec32$Vector$Class$ {
    struct som$Vector$326bd6ec32$Vector$Class$* super$;
    struct CD$Collision (*at)(void* this, int32_t idx);
    void (*resize)(void* this, int32_t newLength);
    void (*atPut)(void* this, int32_t idx, struct CD$Collision * elem);
    void (*append)(void* this, struct CD$Collision * elem);
    uint8_t (*isEmpty)(void* this);
    struct CD$Collision (*first)(void* this);
    struct CD$Collision (*removeFirst)(void* this);
    void (*removeAll)(void* this);
    int32_t (*getSize)(void* this);
    int32_t (*capacity)(void* this);
    void (*forEach)(void* this, struct som$Interfaces$326bd6ec32$ForEachInterface * fn);
    uint8_t (*hasSome)(void* this, struct som$Interfaces$326bd6ec32$TestInterface * fn);
    uint8_t (*getOne)(void* this, struct som$Interfaces$326bd6ec32$TestInterface * fn, struct CD$Collision * out);
    uint8_t (*remove)(void* this, struct CD$Collision * obj, uint8_t (*eq)(struct CD$Collision *, struct CD$Collision *));
    void (*sort)(void* this, struct som$Interfaces$326bd6ec32$Comparator * c);
    void (*sortImp)(void* this, int32_t i, int32_t j, struct som$Interfaces$326bd6ec32$Comparator * c);
};
extern struct som$Vector$326bd6ec32$Vector$Class$ som$Vector$326bd6ec32$Vector$class$;

extern void som$Vector$326bd6ec32$init$(void);
extern OBX$Cmd som$Vector$326bd6ec32$cmd$(const char* name);
#endif
