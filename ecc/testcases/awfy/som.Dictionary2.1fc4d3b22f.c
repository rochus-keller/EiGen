// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Dictionary2.1fc4d3b22f.h"
#include "som.IdentityDictionary2.ec88893d1b.h"

void som$Dictionary2$1fc4d3b22f$Entry$init$(struct som$Dictionary2$1fc4d3b22f$Entry* inst){
    inst->class$ = &som$Dictionary2$1fc4d3b22f$Entry$class$;
}
void som$Dictionary2$1fc4d3b22f$Dictionary$init$(struct som$Dictionary2$1fc4d3b22f$Dictionary* inst){
    inst->class$ = &som$Dictionary2$1fc4d3b22f$Dictionary$class$;
}
struct som$Dictionary2$1fc4d3b22f$Entry * som$Dictionary2$1fc4d3b22f$createEntry(int32_t hash, struct DeltaBlue$Sym * key, struct DeltaBlue$Strength * value, struct som$Dictionary2$1fc4d3b22f$Entry * next) {
    struct som$Dictionary2$1fc4d3b22f$Entry * e;
    struct som$Dictionary2$1fc4d3b22f$Entry * $t0;
    e = 0;
    $t0 = OBX$Alloc(sizeof(struct som$Dictionary2$1fc4d3b22f$Entry));
    memset($t0,0,sizeof(struct som$Dictionary2$1fc4d3b22f$Entry));
    e = $t0;
    som$Dictionary2$1fc4d3b22f$Entry$init$($t0);
    (*e).hash = hash;
    (*e).key = key;
    (*e).value = value;
    (*e).next = next;
    return e;
}

uint8_t som$Dictionary2$1fc4d3b22f$Entry$match(void* this, int32_t hash, struct DeltaBlue$Sym * key) {
    struct som$Dictionary2$1fc4d3b22f$Entry* this$ = this;
    return ((hash == (*this$).hash) && ((void*)key == (void*)(*this$).key));
}

struct som$Dictionary2$1fc4d3b22f$Dictionary * som$Dictionary2$1fc4d3b22f$create() {
    return som$Dictionary2$1fc4d3b22f$createWithSize(16);
}

struct som$Dictionary2$1fc4d3b22f$Dictionary * som$Dictionary2$1fc4d3b22f$createWithSize(int32_t size) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary * d;
    struct som$Dictionary2$1fc4d3b22f$Dictionary * $t0;
    struct som$Dictionary2$1fc4d3b22f$Entry * * $t1;
    d = 0;
    $t0 = OBX$Alloc(sizeof(struct som$Dictionary2$1fc4d3b22f$Dictionary));
    memset($t0,0,sizeof(struct som$Dictionary2$1fc4d3b22f$Dictionary));
    d = $t0;
    som$Dictionary2$1fc4d3b22f$Dictionary$init$($t0);
    {int $0 = size, $n = $0, $s=sizeof(struct som$Dictionary2$1fc4d3b22f$Entry *); $t1 = OBX$Alloc($s*$n); memset($t1,0,$s*$n); (*d).buckets = (struct OBX$Array$1){$0, 1, $t1};};
    (*d).size = 0;
    return d;
}

int32_t som$Dictionary2$1fc4d3b22f$Dictionary$hash(void* this, struct DeltaBlue$Sym * * key) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    int32_t h;
    h = 0;
    h = DeltaBlue$symHash(&(*key));
    return (h ^ OBX$Ror32(h,16));
}

int32_t som$Dictionary2$1fc4d3b22f$Dictionary$getSize(void* this) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    return (*this$).size;
}

uint8_t som$Dictionary2$1fc4d3b22f$Dictionary$isEmpty(void* this) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    return ((*this$).size == 0);
}

int32_t som$Dictionary2$1fc4d3b22f$Dictionary$getBucketIdx(void* this, int32_t hash) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    return ((((*this$).buckets).$1 - 1) & hash);
}

struct som$Dictionary2$1fc4d3b22f$Entry * som$Dictionary2$1fc4d3b22f$Dictionary$getBucket(void* this, int32_t hash) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    struct OBX$Array$1* $t0;
    void* $t1;
    int32_t (* $t2)(void*, int32_t);
    return (*($t0 = (&(*this$).buckets),&((struct som$Dictionary2$1fc4d3b22f$Entry * *)$t0->$a)[($t2 = ((struct som$Dictionary2$1fc4d3b22f$Dictionary *)($t1 = &(*this$)))->class$->getBucketIdx, $t2($t1, hash))]));
}

struct DeltaBlue$Strength * som$Dictionary2$1fc4d3b22f$Dictionary$at(void* this, struct DeltaBlue$Sym * * key) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    int32_t h;
    struct som$Dictionary2$1fc4d3b22f$Entry * e;
    void* $t0;
    int32_t (* $t1)(void*, struct DeltaBlue$Sym * *);
    struct som$Dictionary2$1fc4d3b22f$Entry * (* $t2)(void*, int32_t);
    uint8_t (* $t3)(void*, int32_t, struct DeltaBlue$Sym *);
    h = 0;
    e = 0;
    h = ($t1 = ((struct som$Dictionary2$1fc4d3b22f$Dictionary *)($t0 = &(*this$)))->class$->hash, $t1($t0, &(*key)));
    e = ($t2 = ((struct som$Dictionary2$1fc4d3b22f$Dictionary *)($t0 = &(*this$)))->class$->getBucket, $t2($t0, h));
    while(1) {
        if( ((void*)e != (void*)0) ) {
            if( ($t3 = ((struct som$Dictionary2$1fc4d3b22f$Entry *)($t0 = &(*e)))->class$->match, $t3($t0, h, (*key))) ) {
                return (*e).value;
            } 
            e = (*e).next;
        } else {
            break;
        }
    }
    return 0;
}

uint8_t som$Dictionary2$1fc4d3b22f$Dictionary$containsKey(void* this, struct DeltaBlue$Sym * * key) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    int32_t h;
    struct som$Dictionary2$1fc4d3b22f$Entry * e;
    void* $t0;
    int32_t (* $t1)(void*, struct DeltaBlue$Sym * *);
    struct som$Dictionary2$1fc4d3b22f$Entry * (* $t2)(void*, int32_t);
    uint8_t (* $t3)(void*, int32_t, struct DeltaBlue$Sym *);
    h = 0;
    e = 0;
    h = ($t1 = ((struct som$Dictionary2$1fc4d3b22f$Dictionary *)($t0 = &(*this$)))->class$->hash, $t1($t0, &(*key)));
    e = ($t2 = ((struct som$Dictionary2$1fc4d3b22f$Dictionary *)($t0 = &(*this$)))->class$->getBucket, $t2($t0, h));
    while(1) {
        if( ((void*)e != (void*)0) ) {
            if( ($t3 = ((struct som$Dictionary2$1fc4d3b22f$Entry *)($t0 = &(*e)))->class$->match, $t3($t0, h, (*key))) ) {
                return 1;
            } 
            e = (*e).next;
        } else {
            break;
        }
    }
    return 0;
}

void som$Dictionary2$1fc4d3b22f$Dictionary$atPut(void* this, struct DeltaBlue$Sym * * key, struct DeltaBlue$Strength * * value) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    int32_t h;
    int32_t i;
    struct som$Dictionary2$1fc4d3b22f$Entry * current;
    void* $t0;
    int32_t (* $t1)(void*, struct DeltaBlue$Sym * *);
    int32_t (* $t2)(void*, int32_t);
    struct OBX$Array$1* $t3;
    struct som$Dictionary2$1fc4d3b22f$Entry * (* $t4)(void*, struct DeltaBlue$Sym * *, struct DeltaBlue$Strength * *, int32_t);
    void (* $t5)(void*, struct DeltaBlue$Sym * *, struct DeltaBlue$Strength * *, int32_t, struct som$Dictionary2$1fc4d3b22f$Entry *);
    void (* $t6)(void*);
    h = 0;
    i = 0;
    current = 0;
    h = ($t1 = ((struct som$Dictionary2$1fc4d3b22f$Dictionary *)($t0 = &(*this$)))->class$->hash, $t1($t0, &(*key)));
    i = ($t2 = ((struct som$Dictionary2$1fc4d3b22f$Dictionary *)($t0 = &(*this$)))->class$->getBucketIdx, $t2($t0, h));
    current = (*($t3 = (&(*this$).buckets),&((struct som$Dictionary2$1fc4d3b22f$Entry * *)$t3->$a)[i]));
    if( ((void*)current == (void*)0) ) {
        (*($t3 = (&(*this$).buckets),&((struct som$Dictionary2$1fc4d3b22f$Entry * *)$t3->$a)[i])) = ($t4 = ((struct som$Dictionary2$1fc4d3b22f$Dictionary *)($t0 = &(*this$)))->class$->newEntry, $t4($t0, &(*key), &(*value), h));
        (*this$).size++;
    } else {
        ($t5 = ((struct som$Dictionary2$1fc4d3b22f$Dictionary *)($t0 = &(*this$)))->class$->insertBucketEntry, $t5($t0, &(*key), &(*value), h, current));
    }
    if( ((*this$).size > ((*this$).buckets).$1) ) {
        ($t6 = ((struct som$Dictionary2$1fc4d3b22f$Dictionary *)($t0 = &(*this$)))->class$->resize, $t6($t0));
    } 
}

struct som$Dictionary2$1fc4d3b22f$Entry * som$Dictionary2$1fc4d3b22f$Dictionary$newEntry(void* this, struct DeltaBlue$Sym * * key, struct DeltaBlue$Strength * * value, int32_t hash) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    return som$Dictionary2$1fc4d3b22f$createEntry(hash, (*key), (*value), 0);
}

void som$Dictionary2$1fc4d3b22f$Dictionary$insertBucketEntry(void* this, struct DeltaBlue$Sym * * key, struct DeltaBlue$Strength * * value, int32_t hash, struct som$Dictionary2$1fc4d3b22f$Entry * head) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    struct som$Dictionary2$1fc4d3b22f$Entry * current;
    void* $t0;
    uint8_t (* $t1)(void*, int32_t, struct DeltaBlue$Sym *);
    struct som$Dictionary2$1fc4d3b22f$Entry * (* $t2)(void*, struct DeltaBlue$Sym * *, struct DeltaBlue$Strength * *, int32_t);
    current = 0;
    current = head;
    while(1) {
        if( 1 ) {
            if( ($t1 = ((struct som$Dictionary2$1fc4d3b22f$Entry *)($t0 = &(*current)))->class$->match, $t1($t0, hash, (*key))) ) {
                (*current).value = (*value);
                return ;
            } 
            if( ((void*)(*current).next == (void*)0) ) {
                (*this$).size++;
                (*current).next = ($t2 = ((struct som$Dictionary2$1fc4d3b22f$Dictionary *)($t0 = &(*this$)))->class$->newEntry, $t2($t0, &(*key), &(*value), hash));
                return ;
            } 
            current = (*current).next;
        } else {
            break;
        }
    }
}

void som$Dictionary2$1fc4d3b22f$Dictionary$resize(void* this) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    struct OBX$Array$1 oldStorage;
    struct OBX$Array$1 newStorage;
    struct som$Dictionary2$1fc4d3b22f$Entry * * $t0;
    void* $t1;
    void (* $t2)(void*, struct OBX$Array$1);
    memset(&oldStorage,0,sizeof(oldStorage));
    memset(&newStorage,0,sizeof(newStorage));
    oldStorage = (*this$).buckets;
    {int $0 = ((oldStorage).$1 * 2), $n = $0, $s=sizeof(struct som$Dictionary2$1fc4d3b22f$Entry *); $t0 = OBX$Alloc($s*$n); memset($t0,0,$s*$n); newStorage = (struct OBX$Array$1){$0, 1, $t0};};
    (*this$).buckets = newStorage;
    ($t2 = ((struct som$Dictionary2$1fc4d3b22f$Dictionary *)($t1 = &(*this$)))->class$->transferEntries, $t2($t1, oldStorage));
}

void som$Dictionary2$1fc4d3b22f$Dictionary$transferEntries(void* this, struct OBX$Array$1 oldStorage) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    int32_t i;
    struct som$Dictionary2$1fc4d3b22f$Entry * current;
    struct OBX$Array$1* $t0;
    void* $t1;
    void (* $t2)(void*, struct OBX$Array$1, int32_t, struct som$Dictionary2$1fc4d3b22f$Entry *);
    i = 0;
    current = 0;
    i = 0;
    while(1) {
        if( (i <= ((oldStorage).$1 - 1)) ) {
            current = (*($t0 = (&oldStorage),&((struct som$Dictionary2$1fc4d3b22f$Entry * *)$t0->$a)[i]));
            if( ((void*)current != (void*)0) ) {
                (*($t0 = (&oldStorage),&((struct som$Dictionary2$1fc4d3b22f$Entry * *)$t0->$a)[i])) = 0;
                if( ((void*)(*current).next == (void*)0) ) {
                    (*($t0 = (&(*this$).buckets),&((struct som$Dictionary2$1fc4d3b22f$Entry * *)$t0->$a)[((*current).hash & (((*this$).buckets).$1 - 1))])) = current;
                } else {
                    ($t2 = ((struct som$Dictionary2$1fc4d3b22f$Dictionary *)($t1 = &(*this$)))->class$->splitBucket, $t2($t1, oldStorage, i, current));
                }
            } 
            i = (i + 1);
        } else {
            break;
        }
    }
}

void som$Dictionary2$1fc4d3b22f$Dictionary$splitBucket(void* this, struct OBX$Array$1 oldStorage, int32_t i, struct som$Dictionary2$1fc4d3b22f$Entry * head) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    struct som$Dictionary2$1fc4d3b22f$Entry * loHead;
    struct som$Dictionary2$1fc4d3b22f$Entry * loTail;
    struct som$Dictionary2$1fc4d3b22f$Entry * hiHead;
    struct som$Dictionary2$1fc4d3b22f$Entry * hiTail;
    struct som$Dictionary2$1fc4d3b22f$Entry * current;
    struct OBX$Array$1* $t0;
    loHead = 0;
    loTail = 0;
    hiHead = 0;
    hiTail = 0;
    current = 0;
    current = head;
    while(1) {
        if( ((void*)current != (void*)0) ) {
            if( (((*current).hash & (oldStorage).$1) == 0) ) {
                if( ((void*)loTail == (void*)0) ) {
                    loHead = current;
                } else {
                    (*loTail).next = current;
                }
                loTail = current;
            } else {
                if( ((void*)hiTail == (void*)0) ) {
                    hiHead = current;
                } else {
                    (*hiTail).next = current;
                }
                hiTail = current;
            }
            current = (*current).next;
        } else {
            break;
        }
    }
    if( ((void*)loTail != (void*)0) ) {
        (*loTail).next = 0;
        (*($t0 = (&(*this$).buckets),&((struct som$Dictionary2$1fc4d3b22f$Entry * *)$t0->$a)[i])) = loHead;
    } 
    if( ((void*)hiTail != (void*)0) ) {
        (*hiTail).next = 0;
        (*($t0 = (&(*this$).buckets),&((struct som$Dictionary2$1fc4d3b22f$Entry * *)$t0->$a)[(i + (oldStorage).$1)])) = hiHead;
    } 
}

void som$Dictionary2$1fc4d3b22f$Dictionary$removeAll(void* this) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    struct som$Dictionary2$1fc4d3b22f$Entry * * $t0;
    {int $0 = ((*this$).buckets).$1, $n = $0, $s=sizeof(struct som$Dictionary2$1fc4d3b22f$Entry *); $t0 = OBX$Alloc($s*$n); memset($t0,0,$s*$n); (*this$).buckets = (struct OBX$Array$1){$0, 1, $t0};};
    (*this$).size = 0;
}

struct som$Vector$1f9e73b9b7$Vector * som$Dictionary2$1fc4d3b22f$Dictionary$getKeys(void* this) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    struct som$Vector$1f9e73b9b7$Vector * keys;
    int32_t i;
    struct som$Dictionary2$1fc4d3b22f$Entry * current;
    struct OBX$Array$1* $t0;
    void* $t1;
    void (* $t2)(void*, struct DeltaBlue$Sym * *);
    keys = 0;
    i = 0;
    current = 0;
    keys = som$Vector$1f9e73b9b7$createWithSize((*this$).size);
    i = 0;
    while(1) {
        if( (i <= (((*this$).buckets).$1 - 1)) ) {
            current = (*($t0 = (&(*this$).buckets),&((struct som$Dictionary2$1fc4d3b22f$Entry * *)$t0->$a)[i]));
            while(1) {
                if( ((void*)current != (void*)0) ) {
                    ($t2 = ((struct som$Vector$1f9e73b9b7$Vector *)($t1 = &(*keys)))->class$->append, $t2($t1, &(*current).key));
                    current = (*current).next;
                } else {
                    break;
                }
            }
            i = (i + 1);
        } else {
            break;
        }
    }
    return keys;
}

struct som$Vector$c51d728655$Vector * som$Dictionary2$1fc4d3b22f$Dictionary$getValues(void* this) {
    struct som$Dictionary2$1fc4d3b22f$Dictionary* this$ = this;
    struct som$Vector$c51d728655$Vector * values;
    int32_t i;
    struct som$Dictionary2$1fc4d3b22f$Entry * current;
    struct OBX$Array$1* $t0;
    void* $t1;
    void (* $t2)(void*, struct DeltaBlue$Strength * *);
    values = 0;
    i = 0;
    current = 0;
    values = som$Vector$c51d728655$createWithSize((*this$).size);
    i = 0;
    while(1) {
        if( (i <= (((*this$).buckets).$1 - 1)) ) {
            current = (*($t0 = (&(*this$).buckets),&((struct som$Dictionary2$1fc4d3b22f$Entry * *)$t0->$a)[i]));
            while(1) {
                if( ((void*)current != (void*)0) ) {
                    ($t2 = ((struct som$Vector$c51d728655$Vector *)($t1 = &(*values)))->class$->append, $t2($t1, &(*current).value));
                    current = (*current).next;
                } else {
                    break;
                }
            }
            i = (i + 1);
        } else {
            break;
        }
    }
    return values;
}

struct som$Dictionary2$1fc4d3b22f$Entry$Class$ som$Dictionary2$1fc4d3b22f$Entry$class$ = { 
    0,
    som$Dictionary2$1fc4d3b22f$Entry$match,
};

struct som$Dictionary2$1fc4d3b22f$Dictionary$Class$ som$Dictionary2$1fc4d3b22f$Dictionary$class$ = { 
    0,
    som$Dictionary2$1fc4d3b22f$Dictionary$hash,
    som$Dictionary2$1fc4d3b22f$Dictionary$getSize,
    som$Dictionary2$1fc4d3b22f$Dictionary$isEmpty,
    som$Dictionary2$1fc4d3b22f$Dictionary$getBucketIdx,
    som$Dictionary2$1fc4d3b22f$Dictionary$getBucket,
    som$Dictionary2$1fc4d3b22f$Dictionary$at,
    som$Dictionary2$1fc4d3b22f$Dictionary$containsKey,
    som$Dictionary2$1fc4d3b22f$Dictionary$atPut,
    som$Dictionary2$1fc4d3b22f$Dictionary$newEntry,
    som$Dictionary2$1fc4d3b22f$Dictionary$insertBucketEntry,
    som$Dictionary2$1fc4d3b22f$Dictionary$resize,
    som$Dictionary2$1fc4d3b22f$Dictionary$transferEntries,
    som$Dictionary2$1fc4d3b22f$Dictionary$splitBucket,
    som$Dictionary2$1fc4d3b22f$Dictionary$removeAll,
    som$Dictionary2$1fc4d3b22f$Dictionary$getKeys,
    som$Dictionary2$1fc4d3b22f$Dictionary$getValues,
};

static int initDone$ = 0;
void som$Dictionary2$1fc4d3b22f$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    som$Vector$1f9e73b9b7$init$();
    som$Vector$c51d728655$init$();
}
OBX$Cmd som$Dictionary2$1fc4d3b22f$cmd$(const char* name) {
    if( name == 0 ) return som$Dictionary2$1fc4d3b22f$init$;
    return 0;
}
