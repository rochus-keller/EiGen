#ifndef _SOM$VECTOR$AA9EEE315E_
#define _SOM$VECTOR$AA9EEE315E_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "som.Interfaces.aa9eee315e.h"

// Declaration of module som.Vector(som.Set(INT32).Set)

struct som$Set$04445da84e$Set; // meta actual
struct som$Vector$aa9eee315e$Vector$Class$;
struct som$Vector$aa9eee315e$Vector;
struct som$Vector$aa9eee315e$Vector {
    struct som$Vector$aa9eee315e$Vector$Class$* class$;
    struct OBX$Array$1 storage;
    int32_t firstIdx;
    int32_t lastIdx;
};

extern void som$Vector$aa9eee315e$Vector$init$(struct som$Vector$aa9eee315e$Vector*);
struct som$Vector$aa9eee315e$Vector * som$Vector$aa9eee315e$createWithSize(int32_t siz);
struct som$Vector$aa9eee315e$Vector * som$Vector$aa9eee315e$create();
struct som$Vector$aa9eee315e$Vector * som$Vector$aa9eee315e$createWithElement(struct som$Set$04445da84e$Set * * elem);
struct som$Set$04445da84e$Set * som$Vector$aa9eee315e$Vector$at(void* this, int32_t idx);
void som$Vector$aa9eee315e$Vector$resize(void* this, int32_t newLength);
void som$Vector$aa9eee315e$Vector$atPut(void* this, int32_t idx, struct som$Set$04445da84e$Set * * elem);
void som$Vector$aa9eee315e$Vector$append(void* this, struct som$Set$04445da84e$Set * * elem);
uint8_t som$Vector$aa9eee315e$Vector$isEmpty(void* this);
struct som$Set$04445da84e$Set * som$Vector$aa9eee315e$Vector$first(void* this);
struct som$Set$04445da84e$Set * som$Vector$aa9eee315e$Vector$removeFirst(void* this);
void som$Vector$aa9eee315e$Vector$removeAll(void* this);
int32_t som$Vector$aa9eee315e$Vector$getSize(void* this);
int32_t som$Vector$aa9eee315e$Vector$capacity(void* this);
void som$Vector$aa9eee315e$Vector$forEach(void* this, struct som$Interfaces$aa9eee315e$ForEachInterface * fn);
uint8_t som$Vector$aa9eee315e$Vector$hasSome(void* this, struct som$Interfaces$aa9eee315e$TestInterface * fn);
uint8_t som$Vector$aa9eee315e$Vector$getOne(void* this, struct som$Interfaces$aa9eee315e$TestInterface * fn, struct som$Set$04445da84e$Set * * out);
uint8_t som$Vector$aa9eee315e$Vector$remove(void* this, struct som$Set$04445da84e$Set * * obj, uint8_t (*eq)(struct som$Set$04445da84e$Set * *, struct som$Set$04445da84e$Set * *));
void som$Vector$aa9eee315e$Vector$sort(void* this, struct som$Interfaces$aa9eee315e$Comparator * c);
void som$Vector$aa9eee315e$Vector$sortImp(void* this, int32_t i, int32_t j, struct som$Interfaces$aa9eee315e$Comparator * c);
void som$Vector$aa9eee315e$swap(struct OBX$Array$1 storage2, int32_t i, int32_t j);
struct som$Vector$aa9eee315e$Vector$Class$ {
    struct som$Vector$aa9eee315e$Vector$Class$* super$;
    struct som$Set$04445da84e$Set * (*at)(void* this, int32_t idx);
    void (*resize)(void* this, int32_t newLength);
    void (*atPut)(void* this, int32_t idx, struct som$Set$04445da84e$Set * * elem);
    void (*append)(void* this, struct som$Set$04445da84e$Set * * elem);
    uint8_t (*isEmpty)(void* this);
    struct som$Set$04445da84e$Set * (*first)(void* this);
    struct som$Set$04445da84e$Set * (*removeFirst)(void* this);
    void (*removeAll)(void* this);
    int32_t (*getSize)(void* this);
    int32_t (*capacity)(void* this);
    void (*forEach)(void* this, struct som$Interfaces$aa9eee315e$ForEachInterface * fn);
    uint8_t (*hasSome)(void* this, struct som$Interfaces$aa9eee315e$TestInterface * fn);
    uint8_t (*getOne)(void* this, struct som$Interfaces$aa9eee315e$TestInterface * fn, struct som$Set$04445da84e$Set * * out);
    uint8_t (*remove)(void* this, struct som$Set$04445da84e$Set * * obj, uint8_t (*eq)(struct som$Set$04445da84e$Set * *, struct som$Set$04445da84e$Set * *));
    void (*sort)(void* this, struct som$Interfaces$aa9eee315e$Comparator * c);
    void (*sortImp)(void* this, int32_t i, int32_t j, struct som$Interfaces$aa9eee315e$Comparator * c);
};
extern struct som$Vector$aa9eee315e$Vector$Class$ som$Vector$aa9eee315e$Vector$class$;

extern void som$Vector$aa9eee315e$init$(void);
extern OBX$Cmd som$Vector$aa9eee315e$cmd$(const char* name);
#endif
