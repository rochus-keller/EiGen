// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Set.2b688abfab.h"
#include "som.IdentitySet.2b688abfab.h"

void som$Set$2b688abfab$Set$contains$TestInterface$init$(struct som$Set$2b688abfab$Set$contains$TestInterface* inst){
    inst->class$ = &som$Set$2b688abfab$Set$contains$TestInterface$class$;
}
void som$Set$2b688abfab$Set$init$(struct som$Set$2b688abfab$Set* inst){
    inst->class$ = &som$Set$2b688abfab$Set$class$;
}
struct som$Set$2b688abfab$Set * som$Set$2b688abfab$createWithSize(int32_t siz) {
    struct som$Set$2b688abfab$Set * s;
    struct som$Set$2b688abfab$Set * $t0;
    s = 0;
    $t0 = OBX$Alloc(sizeof(struct som$Set$2b688abfab$Set));
    memset($t0,0,sizeof(struct som$Set$2b688abfab$Set));
    s = $t0;
    som$Set$2b688abfab$Set$init$($t0);
    (*s).items = som$Vector$2b688abfab$createWithSize(siz);
    return s;
}

struct som$Set$2b688abfab$Set * som$Set$2b688abfab$create() {
    return som$Set$2b688abfab$createWithSize(10);
}

int32_t som$Set$2b688abfab$Set$getSize(void* this) {
    struct som$Set$2b688abfab$Set* this$ = this;
    void* $t0;
    int32_t (* $t1)(void*);
    return ($t1 = ((struct som$Vector$2b688abfab$Vector *)($t0 = &(*(*this$).items)))->class$->getSize, $t1($t0));
}

void som$Set$2b688abfab$Set$forEach(void* this, struct som$Interfaces$2b688abfab$ForEachInterface * fn) {
    struct som$Set$2b688abfab$Set* this$ = this;
    void* $t0;
    void (* $t1)(void*, struct som$Interfaces$2b688abfab$ForEachInterface *);
    ($t1 = ((struct som$Vector$2b688abfab$Vector *)($t0 = &(*(*this$).items)))->class$->forEach, $t1($t0, &(*fn)));
}

uint8_t som$Set$2b688abfab$Set$hasSome(void* this, struct som$Interfaces$2b688abfab$TestInterface * fn) {
    struct som$Set$2b688abfab$Set* this$ = this;
    void* $t0;
    uint8_t (* $t1)(void*, struct som$Interfaces$2b688abfab$TestInterface *);
    return ($t1 = ((struct som$Vector$2b688abfab$Vector *)($t0 = &(*(*this$).items)))->class$->hasSome, $t1($t0, &(*fn)));
}

uint8_t som$Set$2b688abfab$Set$getOne(void* this, struct som$Interfaces$2b688abfab$TestInterface * fn, struct Havlak$SimpleLoop * * out) {
    struct som$Set$2b688abfab$Set* this$ = this;
    void* $t0;
    uint8_t (* $t1)(void*, struct som$Interfaces$2b688abfab$TestInterface *, struct Havlak$SimpleLoop * *);
    return ($t1 = ((struct som$Vector$2b688abfab$Vector *)($t0 = &(*(*this$).items)))->class$->getOne, $t1($t0, &(*fn), &(*out)));
}

void som$Set$2b688abfab$Set$removeAll(void* this) {
    struct som$Set$2b688abfab$Set* this$ = this;
    void* $t0;
    void (* $t1)(void*);
    ($t1 = ((struct som$Vector$2b688abfab$Vector *)($t0 = &(*(*this$).items)))->class$->removeAll, $t1($t0));
}

void som$Set$2b688abfab$Set$add(void* this, struct Havlak$SimpleLoop * * obj) {
    struct som$Set$2b688abfab$Set* this$ = this;
    void* $t0;
    uint8_t (* $t1)(void*, struct Havlak$SimpleLoop * *);
    void* $t2;
    void (* $t3)(void*, struct Havlak$SimpleLoop * *);
    if( (!($t1 = ((struct som$Set$2b688abfab$Set *)($t0 = &(*this$)))->class$->contains, $t1($t0, &(*obj)))) ) {
        ($t3 = ((struct som$Vector$2b688abfab$Vector *)($t2 = &(*(*this$).items)))->class$->append, $t3($t2, &(*obj)));
    } 
}

uint8_t som$Set$2b688abfab$Set$contains(void* this, struct Havlak$SimpleLoop * * obj) {
    struct som$Set$2b688abfab$Set* this$ = this;
    struct som$Set$2b688abfab$Set$contains$TestInterface t;
    void* $t0;
    uint8_t (* $t1)(void*, struct som$Interfaces$2b688abfab$TestInterface *);
    memset(&t,0,sizeof(t));
    som$Set$2b688abfab$Set$contains$TestInterface$init$(&t);
    t.obj = (*obj);
    return ($t1 = ((struct som$Set$2b688abfab$Set *)($t0 = &(*this$)))->class$->hasSome, $t1($t0, ((struct som$Interfaces$2b688abfab$TestInterface *)&t)));
}

uint8_t som$Set$2b688abfab$Set$contains$TestInterface$test(void* this, struct Havlak$SimpleLoop * * elem) {
    struct som$Set$2b688abfab$Set$contains$TestInterface* this$ = this;
    return ((void*)(*elem) == (void*)(*this$).obj);
}

struct som$Set$2b688abfab$Set$contains$TestInterface$Class$ som$Set$2b688abfab$Set$contains$TestInterface$class$ = { 
    &som$Interfaces$2b688abfab$TestInterface$class$,
    som$Set$2b688abfab$Set$contains$TestInterface$test,
};

struct som$Set$2b688abfab$Set$Class$ som$Set$2b688abfab$Set$class$ = { 
    0,
    som$Set$2b688abfab$Set$getSize,
    som$Set$2b688abfab$Set$forEach,
    som$Set$2b688abfab$Set$hasSome,
    som$Set$2b688abfab$Set$getOne,
    som$Set$2b688abfab$Set$removeAll,
    som$Set$2b688abfab$Set$add,
    som$Set$2b688abfab$Set$contains,
};

static int initDone$ = 0;
void som$Set$2b688abfab$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    som$Vector$2b688abfab$init$();
    som$Interfaces$2b688abfab$init$();
}
OBX$Cmd som$Set$2b688abfab$cmd$(const char* name) {
    if( name == 0 ) return som$Set$2b688abfab$init$;
    return 0;
}
