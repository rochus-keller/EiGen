// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Set.6226d61315.h"
#include "som.IdentitySet.6226d61315.h"

void som$Set$6226d61315$Set$init$(struct som$Set$6226d61315$Set* inst){
    inst->class$ = &som$Set$6226d61315$Set$class$;
}
void som$Set$6226d61315$Set$contains$TestInterface$init$(struct som$Set$6226d61315$Set$contains$TestInterface* inst){
    inst->class$ = &som$Set$6226d61315$Set$contains$TestInterface$class$;
}
struct som$Set$6226d61315$Set * som$Set$6226d61315$createWithSize(int32_t siz) {
    struct som$Set$6226d61315$Set * s;
    struct som$Set$6226d61315$Set * $t0;
    s = 0;
    $t0 = OBX$Alloc(sizeof(struct som$Set$6226d61315$Set));
    memset($t0,0,sizeof(struct som$Set$6226d61315$Set));
    s = $t0;
    som$Set$6226d61315$Set$init$($t0);
    (*s).items = som$Vector$6226d61315$createWithSize(siz);
    return s;
}

struct som$Set$6226d61315$Set * som$Set$6226d61315$create() {
    return som$Set$6226d61315$createWithSize(10);
}

int32_t som$Set$6226d61315$Set$getSize(void* this) {
    struct som$Set$6226d61315$Set* this$ = this;
    void* $t0;
    int32_t (* $t1)(void*);
    return ($t1 = ((struct som$Vector$6226d61315$Vector *)($t0 = &(*(*this$).items)))->class$->getSize, $t1($t0));
}

void som$Set$6226d61315$Set$forEach(void* this, struct som$Interfaces$6226d61315$ForEachInterface * fn) {
    struct som$Set$6226d61315$Set* this$ = this;
    void* $t0;
    void (* $t1)(void*, struct som$Interfaces$6226d61315$ForEachInterface *);
    ($t1 = ((struct som$Vector$6226d61315$Vector *)($t0 = &(*(*this$).items)))->class$->forEach, $t1($t0, &(*fn)));
}

uint8_t som$Set$6226d61315$Set$hasSome(void* this, struct som$Interfaces$6226d61315$TestInterface * fn) {
    struct som$Set$6226d61315$Set* this$ = this;
    void* $t0;
    uint8_t (* $t1)(void*, struct som$Interfaces$6226d61315$TestInterface *);
    return ($t1 = ((struct som$Vector$6226d61315$Vector *)($t0 = &(*(*this$).items)))->class$->hasSome, $t1($t0, &(*fn)));
}

uint8_t som$Set$6226d61315$Set$getOne(void* this, struct som$Interfaces$6226d61315$TestInterface * fn, struct Havlak$BasicBlock * * out) {
    struct som$Set$6226d61315$Set* this$ = this;
    void* $t0;
    uint8_t (* $t1)(void*, struct som$Interfaces$6226d61315$TestInterface *, struct Havlak$BasicBlock * *);
    return ($t1 = ((struct som$Vector$6226d61315$Vector *)($t0 = &(*(*this$).items)))->class$->getOne, $t1($t0, &(*fn), &(*out)));
}

void som$Set$6226d61315$Set$removeAll(void* this) {
    struct som$Set$6226d61315$Set* this$ = this;
    void* $t0;
    void (* $t1)(void*);
    ($t1 = ((struct som$Vector$6226d61315$Vector *)($t0 = &(*(*this$).items)))->class$->removeAll, $t1($t0));
}

void som$Set$6226d61315$Set$add(void* this, struct Havlak$BasicBlock * * obj) {
    struct som$Set$6226d61315$Set* this$ = this;
    void* $t0;
    uint8_t (* $t1)(void*, struct Havlak$BasicBlock * *);
    void* $t2;
    void (* $t3)(void*, struct Havlak$BasicBlock * *);
    if( (!($t1 = ((struct som$Set$6226d61315$Set *)($t0 = &(*this$)))->class$->contains, $t1($t0, &(*obj)))) ) {
        ($t3 = ((struct som$Vector$6226d61315$Vector *)($t2 = &(*(*this$).items)))->class$->append, $t3($t2, &(*obj)));
    } 
}

uint8_t som$Set$6226d61315$Set$contains(void* this, struct Havlak$BasicBlock * * obj) {
    struct som$Set$6226d61315$Set* this$ = this;
    struct som$Set$6226d61315$Set$contains$TestInterface t;
    void* $t0;
    uint8_t (* $t1)(void*, struct som$Interfaces$6226d61315$TestInterface *);
    memset(&t,0,sizeof(t));
    som$Set$6226d61315$Set$contains$TestInterface$init$(&t);
    t.obj = (*obj);
    return ($t1 = ((struct som$Set$6226d61315$Set *)($t0 = &(*this$)))->class$->hasSome, $t1($t0, ((struct som$Interfaces$6226d61315$TestInterface *)&t)));
}

uint8_t som$Set$6226d61315$Set$contains$TestInterface$test(void* this, struct Havlak$BasicBlock * * elem) {
    struct som$Set$6226d61315$Set$contains$TestInterface* this$ = this;
    return ((void*)(*elem) == (void*)(*this$).obj);
}

struct som$Set$6226d61315$Set$Class$ som$Set$6226d61315$Set$class$ = { 
    0,
    som$Set$6226d61315$Set$getSize,
    som$Set$6226d61315$Set$forEach,
    som$Set$6226d61315$Set$hasSome,
    som$Set$6226d61315$Set$getOne,
    som$Set$6226d61315$Set$removeAll,
    som$Set$6226d61315$Set$add,
    som$Set$6226d61315$Set$contains,
};

struct som$Set$6226d61315$Set$contains$TestInterface$Class$ som$Set$6226d61315$Set$contains$TestInterface$class$ = { 
    &som$Interfaces$6226d61315$TestInterface$class$,
    som$Set$6226d61315$Set$contains$TestInterface$test,
};

static int initDone$ = 0;
void som$Set$6226d61315$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    som$Vector$6226d61315$init$();
    som$Interfaces$6226d61315$init$();
}
OBX$Cmd som$Set$6226d61315$cmd$(const char* name) {
    if( name == 0 ) return som$Set$6226d61315$init$;
    return 0;
}
