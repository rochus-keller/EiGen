#ifndef _SOM$VECTOR$71499F4DFF_
#define _SOM$VECTOR$71499F4DFF_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "som.Interfaces.71499f4dff.h"

// Declaration of module som.Vector(Json.String)

struct som$Vector$71499f4dff$Vector$Class$;
struct som$Vector$71499f4dff$Vector;
struct som$Vector$71499f4dff$Vector {
    struct som$Vector$71499f4dff$Vector$Class$* class$;
    struct OBX$Array$1 storage;
    int32_t firstIdx;
    int32_t lastIdx;
};

extern void som$Vector$71499f4dff$Vector$init$(struct som$Vector$71499f4dff$Vector*);
struct som$Vector$71499f4dff$Vector * som$Vector$71499f4dff$createWithSize(int32_t siz);
struct som$Vector$71499f4dff$Vector * som$Vector$71499f4dff$create();
struct som$Vector$71499f4dff$Vector * som$Vector$71499f4dff$createWithElement(struct OBX$Array$1 * elem);
struct OBX$Array$1 som$Vector$71499f4dff$Vector$at(void* this, int32_t idx);
void som$Vector$71499f4dff$Vector$resize(void* this, int32_t newLength);
void som$Vector$71499f4dff$Vector$atPut(void* this, int32_t idx, struct OBX$Array$1 * elem);
void som$Vector$71499f4dff$Vector$append(void* this, struct OBX$Array$1 * elem);
uint8_t som$Vector$71499f4dff$Vector$isEmpty(void* this);
struct OBX$Array$1 som$Vector$71499f4dff$Vector$first(void* this);
struct OBX$Array$1 som$Vector$71499f4dff$Vector$removeFirst(void* this);
void som$Vector$71499f4dff$Vector$removeAll(void* this);
int32_t som$Vector$71499f4dff$Vector$getSize(void* this);
int32_t som$Vector$71499f4dff$Vector$capacity(void* this);
void som$Vector$71499f4dff$Vector$forEach(void* this, struct som$Interfaces$71499f4dff$ForEachInterface * fn);
uint8_t som$Vector$71499f4dff$Vector$hasSome(void* this, struct som$Interfaces$71499f4dff$TestInterface * fn);
uint8_t som$Vector$71499f4dff$Vector$getOne(void* this, struct som$Interfaces$71499f4dff$TestInterface * fn, struct OBX$Array$1 * out);
uint8_t som$Vector$71499f4dff$Vector$remove(void* this, struct OBX$Array$1 * obj, uint8_t (*eq)(struct OBX$Array$1 *, struct OBX$Array$1 *));
void som$Vector$71499f4dff$Vector$sort(void* this, struct som$Interfaces$71499f4dff$Comparator * c);
void som$Vector$71499f4dff$Vector$sortImp(void* this, int32_t i, int32_t j, struct som$Interfaces$71499f4dff$Comparator * c);
void som$Vector$71499f4dff$swap(struct OBX$Array$1 storage2, int32_t i, int32_t j);
struct som$Vector$71499f4dff$Vector$Class$ {
    struct som$Vector$71499f4dff$Vector$Class$* super$;
    struct OBX$Array$1 (*at)(void* this, int32_t idx);
    void (*resize)(void* this, int32_t newLength);
    void (*atPut)(void* this, int32_t idx, struct OBX$Array$1 * elem);
    void (*append)(void* this, struct OBX$Array$1 * elem);
    uint8_t (*isEmpty)(void* this);
    struct OBX$Array$1 (*first)(void* this);
    struct OBX$Array$1 (*removeFirst)(void* this);
    void (*removeAll)(void* this);
    int32_t (*getSize)(void* this);
    int32_t (*capacity)(void* this);
    void (*forEach)(void* this, struct som$Interfaces$71499f4dff$ForEachInterface * fn);
    uint8_t (*hasSome)(void* this, struct som$Interfaces$71499f4dff$TestInterface * fn);
    uint8_t (*getOne)(void* this, struct som$Interfaces$71499f4dff$TestInterface * fn, struct OBX$Array$1 * out);
    uint8_t (*remove)(void* this, struct OBX$Array$1 * obj, uint8_t (*eq)(struct OBX$Array$1 *, struct OBX$Array$1 *));
    void (*sort)(void* this, struct som$Interfaces$71499f4dff$Comparator * c);
    void (*sortImp)(void* this, int32_t i, int32_t j, struct som$Interfaces$71499f4dff$Comparator * c);
};
extern struct som$Vector$71499f4dff$Vector$Class$ som$Vector$71499f4dff$Vector$class$;

extern void som$Vector$71499f4dff$init$(void);
extern OBX$Cmd som$Vector$71499f4dff$cmd$(const char* name);
#endif
