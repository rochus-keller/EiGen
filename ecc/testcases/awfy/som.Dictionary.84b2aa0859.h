#ifndef _SOM$DICTIONARY$84B2AA0859_
#define _SOM$DICTIONARY$84B2AA0859_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "som.Vector.6226d61315.h"
#include "som.Vector.04445da84e.h"

// Declaration of module som.Dictionary(Havlak.BasicBlock,INT32)

struct Havlak$BasicBlock; // meta actual
struct som$Dictionary$84b2aa0859$Dictionary$Class$;
struct som$Dictionary$84b2aa0859$Dictionary;
struct som$Dictionary$84b2aa0859$Entry$Class$;
struct som$Dictionary$84b2aa0859$Entry;
struct som$Dictionary$84b2aa0859$Dictionary {
    struct som$Dictionary$84b2aa0859$Dictionary$Class$* class$;
    struct OBX$Array$1 buckets;
    int32_t size;
    int32_t (*hf)(struct Havlak$BasicBlock * *);
};

extern void som$Dictionary$84b2aa0859$Dictionary$init$(struct som$Dictionary$84b2aa0859$Dictionary*);
struct som$Dictionary$84b2aa0859$Entry {
    struct som$Dictionary$84b2aa0859$Entry$Class$* class$;
    int32_t hash;
    struct Havlak$BasicBlock * key;
    int32_t value;
    struct som$Dictionary$84b2aa0859$Entry * next;
};

extern void som$Dictionary$84b2aa0859$Entry$init$(struct som$Dictionary$84b2aa0859$Entry*);
struct som$Dictionary$84b2aa0859$Entry * som$Dictionary$84b2aa0859$createEntry(int32_t hash, struct Havlak$BasicBlock * key, int32_t value, struct som$Dictionary$84b2aa0859$Entry * next);
uint8_t som$Dictionary$84b2aa0859$Entry$match(void* this, int32_t hash, struct Havlak$BasicBlock * key);
struct som$Dictionary$84b2aa0859$Dictionary * som$Dictionary$84b2aa0859$create(int32_t (*hf)(struct Havlak$BasicBlock * *));
struct som$Dictionary$84b2aa0859$Dictionary * som$Dictionary$84b2aa0859$createWithSize(int32_t size, int32_t (*hf)(struct Havlak$BasicBlock * *));
int32_t som$Dictionary$84b2aa0859$Dictionary$hash(void* this, struct Havlak$BasicBlock * * key);
int32_t som$Dictionary$84b2aa0859$Dictionary$getSize(void* this);
uint8_t som$Dictionary$84b2aa0859$Dictionary$isEmpty(void* this);
int32_t som$Dictionary$84b2aa0859$Dictionary$getBucketIdx(void* this, int32_t hash);
struct som$Dictionary$84b2aa0859$Entry * som$Dictionary$84b2aa0859$Dictionary$getBucket(void* this, int32_t hash);
int32_t som$Dictionary$84b2aa0859$Dictionary$at(void* this, struct Havlak$BasicBlock * * key);
uint8_t som$Dictionary$84b2aa0859$Dictionary$containsKey(void* this, struct Havlak$BasicBlock * * key);
void som$Dictionary$84b2aa0859$Dictionary$atPut(void* this, struct Havlak$BasicBlock * * key, int32_t * value);
struct som$Dictionary$84b2aa0859$Entry * som$Dictionary$84b2aa0859$Dictionary$newEntry(void* this, struct Havlak$BasicBlock * * key, int32_t * value, int32_t hash);
void som$Dictionary$84b2aa0859$Dictionary$insertBucketEntry(void* this, struct Havlak$BasicBlock * * key, int32_t * value, int32_t hash, struct som$Dictionary$84b2aa0859$Entry * head);
void som$Dictionary$84b2aa0859$Dictionary$resize(void* this);
void som$Dictionary$84b2aa0859$Dictionary$transferEntries(void* this, struct OBX$Array$1 oldStorage);
void som$Dictionary$84b2aa0859$Dictionary$splitBucket(void* this, struct OBX$Array$1 oldStorage, int32_t i, struct som$Dictionary$84b2aa0859$Entry * head);
void som$Dictionary$84b2aa0859$Dictionary$removeAll(void* this);
struct som$Vector$6226d61315$Vector * som$Dictionary$84b2aa0859$Dictionary$getKeys(void* this);
struct som$Vector$04445da84e$Vector * som$Dictionary$84b2aa0859$Dictionary$getValues(void* this);
struct som$Dictionary$84b2aa0859$Dictionary$Class$ {
    struct som$Dictionary$84b2aa0859$Dictionary$Class$* super$;
    int32_t (*hash)(void* this, struct Havlak$BasicBlock * * key);
    int32_t (*getSize)(void* this);
    uint8_t (*isEmpty)(void* this);
    int32_t (*getBucketIdx)(void* this, int32_t hash);
    struct som$Dictionary$84b2aa0859$Entry * (*getBucket)(void* this, int32_t hash);
    int32_t (*at)(void* this, struct Havlak$BasicBlock * * key);
    uint8_t (*containsKey)(void* this, struct Havlak$BasicBlock * * key);
    void (*atPut)(void* this, struct Havlak$BasicBlock * * key, int32_t * value);
    struct som$Dictionary$84b2aa0859$Entry * (*newEntry)(void* this, struct Havlak$BasicBlock * * key, int32_t * value, int32_t hash);
    void (*insertBucketEntry)(void* this, struct Havlak$BasicBlock * * key, int32_t * value, int32_t hash, struct som$Dictionary$84b2aa0859$Entry * head);
    void (*resize)(void* this);
    void (*transferEntries)(void* this, struct OBX$Array$1 oldStorage);
    void (*splitBucket)(void* this, struct OBX$Array$1 oldStorage, int32_t i, struct som$Dictionary$84b2aa0859$Entry * head);
    void (*removeAll)(void* this);
    struct som$Vector$6226d61315$Vector * (*getKeys)(void* this);
    struct som$Vector$04445da84e$Vector * (*getValues)(void* this);
};
extern struct som$Dictionary$84b2aa0859$Dictionary$Class$ som$Dictionary$84b2aa0859$Dictionary$class$;

struct som$Dictionary$84b2aa0859$Entry$Class$ {
    struct som$Dictionary$84b2aa0859$Entry$Class$* super$;
    uint8_t (*match)(void* this, int32_t hash, struct Havlak$BasicBlock * key);
};
extern struct som$Dictionary$84b2aa0859$Entry$Class$ som$Dictionary$84b2aa0859$Entry$class$;

extern void som$Dictionary$84b2aa0859$init$(void);
extern OBX$Cmd som$Dictionary$84b2aa0859$cmd$(const char* name);
#endif
