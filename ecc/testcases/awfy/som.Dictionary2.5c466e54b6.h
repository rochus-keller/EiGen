#ifndef _SOM$DICTIONARY2$5C466E54B6_
#define _SOM$DICTIONARY2$5C466E54B6_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "som.Vector.1f9e73b9b7.h"
#include "som.Vector.04445da84e.h"

// Declaration of module som.Dictionary2(DeltaBlue.Sym,INT32,som.IdentityDictionary2(DeltaBlue.Sym,INT32,DeltaBlue.symHash).hf)

struct DeltaBlue$Sym; // meta actual
struct som$Dictionary2$5c466e54b6$Entry$Class$;
struct som$Dictionary2$5c466e54b6$Entry;
struct som$Dictionary2$5c466e54b6$Dictionary$Class$;
struct som$Dictionary2$5c466e54b6$Dictionary;
struct som$Dictionary2$5c466e54b6$Entry {
    struct som$Dictionary2$5c466e54b6$Entry$Class$* class$;
    int32_t hash;
    struct DeltaBlue$Sym * key;
    int32_t value;
    struct som$Dictionary2$5c466e54b6$Entry * next;
};

extern void som$Dictionary2$5c466e54b6$Entry$init$(struct som$Dictionary2$5c466e54b6$Entry*);
struct som$Dictionary2$5c466e54b6$Dictionary {
    struct som$Dictionary2$5c466e54b6$Dictionary$Class$* class$;
    struct OBX$Array$1 buckets;
    int32_t size;
};

extern void som$Dictionary2$5c466e54b6$Dictionary$init$(struct som$Dictionary2$5c466e54b6$Dictionary*);
struct som$Dictionary2$5c466e54b6$Entry * som$Dictionary2$5c466e54b6$createEntry(int32_t hash, struct DeltaBlue$Sym * key, int32_t value, struct som$Dictionary2$5c466e54b6$Entry * next);
uint8_t som$Dictionary2$5c466e54b6$Entry$match(void* this, int32_t hash, struct DeltaBlue$Sym * key);
struct som$Dictionary2$5c466e54b6$Dictionary * som$Dictionary2$5c466e54b6$create();
struct som$Dictionary2$5c466e54b6$Dictionary * som$Dictionary2$5c466e54b6$createWithSize(int32_t size);
int32_t som$Dictionary2$5c466e54b6$Dictionary$hash(void* this, struct DeltaBlue$Sym * * key);
int32_t som$Dictionary2$5c466e54b6$Dictionary$getSize(void* this);
uint8_t som$Dictionary2$5c466e54b6$Dictionary$isEmpty(void* this);
int32_t som$Dictionary2$5c466e54b6$Dictionary$getBucketIdx(void* this, int32_t hash);
struct som$Dictionary2$5c466e54b6$Entry * som$Dictionary2$5c466e54b6$Dictionary$getBucket(void* this, int32_t hash);
int32_t som$Dictionary2$5c466e54b6$Dictionary$at(void* this, struct DeltaBlue$Sym * * key);
uint8_t som$Dictionary2$5c466e54b6$Dictionary$containsKey(void* this, struct DeltaBlue$Sym * * key);
void som$Dictionary2$5c466e54b6$Dictionary$atPut(void* this, struct DeltaBlue$Sym * * key, int32_t * value);
struct som$Dictionary2$5c466e54b6$Entry * som$Dictionary2$5c466e54b6$Dictionary$newEntry(void* this, struct DeltaBlue$Sym * * key, int32_t * value, int32_t hash);
void som$Dictionary2$5c466e54b6$Dictionary$insertBucketEntry(void* this, struct DeltaBlue$Sym * * key, int32_t * value, int32_t hash, struct som$Dictionary2$5c466e54b6$Entry * head);
void som$Dictionary2$5c466e54b6$Dictionary$resize(void* this);
void som$Dictionary2$5c466e54b6$Dictionary$transferEntries(void* this, struct OBX$Array$1 oldStorage);
void som$Dictionary2$5c466e54b6$Dictionary$splitBucket(void* this, struct OBX$Array$1 oldStorage, int32_t i, struct som$Dictionary2$5c466e54b6$Entry * head);
void som$Dictionary2$5c466e54b6$Dictionary$removeAll(void* this);
struct som$Vector$1f9e73b9b7$Vector * som$Dictionary2$5c466e54b6$Dictionary$getKeys(void* this);
struct som$Vector$04445da84e$Vector * som$Dictionary2$5c466e54b6$Dictionary$getValues(void* this);
struct som$Dictionary2$5c466e54b6$Entry$Class$ {
    struct som$Dictionary2$5c466e54b6$Entry$Class$* super$;
    uint8_t (*match)(void* this, int32_t hash, struct DeltaBlue$Sym * key);
};
extern struct som$Dictionary2$5c466e54b6$Entry$Class$ som$Dictionary2$5c466e54b6$Entry$class$;

struct som$Dictionary2$5c466e54b6$Dictionary$Class$ {
    struct som$Dictionary2$5c466e54b6$Dictionary$Class$* super$;
    int32_t (*hash)(void* this, struct DeltaBlue$Sym * * key);
    int32_t (*getSize)(void* this);
    uint8_t (*isEmpty)(void* this);
    int32_t (*getBucketIdx)(void* this, int32_t hash);
    struct som$Dictionary2$5c466e54b6$Entry * (*getBucket)(void* this, int32_t hash);
    int32_t (*at)(void* this, struct DeltaBlue$Sym * * key);
    uint8_t (*containsKey)(void* this, struct DeltaBlue$Sym * * key);
    void (*atPut)(void* this, struct DeltaBlue$Sym * * key, int32_t * value);
    struct som$Dictionary2$5c466e54b6$Entry * (*newEntry)(void* this, struct DeltaBlue$Sym * * key, int32_t * value, int32_t hash);
    void (*insertBucketEntry)(void* this, struct DeltaBlue$Sym * * key, int32_t * value, int32_t hash, struct som$Dictionary2$5c466e54b6$Entry * head);
    void (*resize)(void* this);
    void (*transferEntries)(void* this, struct OBX$Array$1 oldStorage);
    void (*splitBucket)(void* this, struct OBX$Array$1 oldStorage, int32_t i, struct som$Dictionary2$5c466e54b6$Entry * head);
    void (*removeAll)(void* this);
    struct som$Vector$1f9e73b9b7$Vector * (*getKeys)(void* this);
    struct som$Vector$04445da84e$Vector * (*getValues)(void* this);
};
extern struct som$Dictionary2$5c466e54b6$Dictionary$Class$ som$Dictionary2$5c466e54b6$Dictionary$class$;

extern void som$Dictionary2$5c466e54b6$init$(void);
extern OBX$Cmd som$Dictionary2$5c466e54b6$cmd$(const char* name);
#endif
