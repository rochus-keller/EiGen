// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Set.04445da84e.h"

void som$Set$04445da84e$Set$init$(struct som$Set$04445da84e$Set* inst){
    inst->class$ = &som$Set$04445da84e$Set$class$;
}
void som$Set$04445da84e$Set$contains$TestInterface$init$(struct som$Set$04445da84e$Set$contains$TestInterface* inst){
    inst->class$ = &som$Set$04445da84e$Set$contains$TestInterface$class$;
}
struct som$Set$04445da84e$Set * som$Set$04445da84e$createWithSize(int32_t siz) {
    struct som$Set$04445da84e$Set * s;
    struct som$Set$04445da84e$Set * $t0;
    s = 0;
    $t0 = OBX$Alloc(sizeof(struct som$Set$04445da84e$Set));
    memset($t0,0,sizeof(struct som$Set$04445da84e$Set));
    s = $t0;
    som$Set$04445da84e$Set$init$($t0);
    (*s).items = som$Vector$04445da84e$createWithSize(siz);
    return s;
}

struct som$Set$04445da84e$Set * som$Set$04445da84e$create() {
    return som$Set$04445da84e$createWithSize(10);
}

int32_t som$Set$04445da84e$Set$getSize(void* this) {
    struct som$Set$04445da84e$Set* this$ = this;
    void* $t0;
    int32_t (* $t1)(void*);
    return ($t1 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*(*this$).items)))->class$->getSize, $t1($t0));
}

void som$Set$04445da84e$Set$forEach(void* this, struct som$Interfaces$04445da84e$ForEachInterface * fn) {
    struct som$Set$04445da84e$Set* this$ = this;
    void* $t0;
    void (* $t1)(void*, struct som$Interfaces$04445da84e$ForEachInterface *);
    ($t1 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*(*this$).items)))->class$->forEach, $t1($t0, &(*fn)));
}

uint8_t som$Set$04445da84e$Set$hasSome(void* this, struct som$Interfaces$04445da84e$TestInterface * fn) {
    struct som$Set$04445da84e$Set* this$ = this;
    void* $t0;
    uint8_t (* $t1)(void*, struct som$Interfaces$04445da84e$TestInterface *);
    return ($t1 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*(*this$).items)))->class$->hasSome, $t1($t0, &(*fn)));
}

uint8_t som$Set$04445da84e$Set$getOne(void* this, struct som$Interfaces$04445da84e$TestInterface * fn, int32_t * out) {
    struct som$Set$04445da84e$Set* this$ = this;
    void* $t0;
    uint8_t (* $t1)(void*, struct som$Interfaces$04445da84e$TestInterface *, int32_t *);
    return ($t1 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*(*this$).items)))->class$->getOne, $t1($t0, &(*fn), &(*out)));
}

void som$Set$04445da84e$Set$removeAll(void* this) {
    struct som$Set$04445da84e$Set* this$ = this;
    void* $t0;
    void (* $t1)(void*);
    ($t1 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*(*this$).items)))->class$->removeAll, $t1($t0));
}

void som$Set$04445da84e$Set$add(void* this, int32_t * obj) {
    struct som$Set$04445da84e$Set* this$ = this;
    void* $t0;
    uint8_t (* $t1)(void*, int32_t *);
    void* $t2;
    void (* $t3)(void*, int32_t *);
    if( (!($t1 = ((struct som$Set$04445da84e$Set *)($t0 = &(*this$)))->class$->contains, $t1($t0, &(*obj)))) ) {
        ($t3 = ((struct som$Vector$04445da84e$Vector *)($t2 = &(*(*this$).items)))->class$->append, $t3($t2, &(*obj)));
    } 
}

uint8_t som$Set$04445da84e$Set$contains(void* this, int32_t * obj) {
    struct som$Set$04445da84e$Set* this$ = this;
    struct som$Set$04445da84e$Set$contains$TestInterface t;
    void* $t0;
    uint8_t (* $t1)(void*, struct som$Interfaces$04445da84e$TestInterface *);
    memset(&t,0,sizeof(t));
    som$Set$04445da84e$Set$contains$TestInterface$init$(&t);
    t.obj = (*obj);
    return ($t1 = ((struct som$Set$04445da84e$Set *)($t0 = &(*this$)))->class$->hasSome, $t1($t0, ((struct som$Interfaces$04445da84e$TestInterface *)&t)));
}

uint8_t som$Set$04445da84e$Set$contains$TestInterface$test(void* this, int32_t * elem) {
    struct som$Set$04445da84e$Set$contains$TestInterface* this$ = this;
    return ((*elem) == (*this$).obj);
}

struct som$Set$04445da84e$Set$Class$ som$Set$04445da84e$Set$class$ = { 
    0,
    som$Set$04445da84e$Set$getSize,
    som$Set$04445da84e$Set$forEach,
    som$Set$04445da84e$Set$hasSome,
    som$Set$04445da84e$Set$getOne,
    som$Set$04445da84e$Set$removeAll,
    som$Set$04445da84e$Set$add,
    som$Set$04445da84e$Set$contains,
};

struct som$Set$04445da84e$Set$contains$TestInterface$Class$ som$Set$04445da84e$Set$contains$TestInterface$class$ = { 
    &som$Interfaces$04445da84e$TestInterface$class$,
    som$Set$04445da84e$Set$contains$TestInterface$test,
};

static int initDone$ = 0;
void som$Set$04445da84e$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    som$Vector$04445da84e$init$();
    som$Interfaces$04445da84e$init$();
}
OBX$Cmd som$Set$04445da84e$cmd$(const char* name) {
    if( name == 0 ) return som$Set$04445da84e$init$;
    return 0;
}