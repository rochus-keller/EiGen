// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Interfaces.e0832c0c14.h"
#include "som.Vector.e0832c0c14.h"

void som$Interfaces$e0832c0c14$Comparator$init$(struct som$Interfaces$e0832c0c14$Comparator* inst){
    inst->class$ = &som$Interfaces$e0832c0c14$Comparator$class$;
}
void som$Interfaces$e0832c0c14$ForEachInterfaceRW$init$(struct som$Interfaces$e0832c0c14$ForEachInterfaceRW* inst){
    inst->class$ = &som$Interfaces$e0832c0c14$ForEachInterfaceRW$class$;
}
void som$Interfaces$e0832c0c14$TestInterface$init$(struct som$Interfaces$e0832c0c14$TestInterface* inst){
    inst->class$ = &som$Interfaces$e0832c0c14$TestInterface$class$;
}
void som$Interfaces$e0832c0c14$ForEachInterface$init$(struct som$Interfaces$e0832c0c14$ForEachInterface* inst){
    inst->class$ = &som$Interfaces$e0832c0c14$ForEachInterface$class$;
}
void som$Interfaces$e0832c0c14$ForEachInterface$apply(void* this, struct CD$Motion * * elem) {
    struct som$Interfaces$e0832c0c14$ForEachInterface* this$ = this;
}

void som$Interfaces$e0832c0c14$ForEachInterfaceRW$apply(void* this, struct CD$Motion * * elem) {
    struct som$Interfaces$e0832c0c14$ForEachInterfaceRW* this$ = this;
}

uint8_t som$Interfaces$e0832c0c14$TestInterface$test(void* this, struct CD$Motion * * elem) {
    struct som$Interfaces$e0832c0c14$TestInterface* this$ = this;
    return 0;
}

int32_t som$Interfaces$e0832c0c14$Comparator$compare(void* this, struct CD$Motion * * i, struct CD$Motion * * j) {
    struct som$Interfaces$e0832c0c14$Comparator* this$ = this;
    return 0;
}

struct som$Interfaces$e0832c0c14$Comparator$Class$ som$Interfaces$e0832c0c14$Comparator$class$ = { 
    0,
    som$Interfaces$e0832c0c14$Comparator$compare,
};

struct som$Interfaces$e0832c0c14$ForEachInterfaceRW$Class$ som$Interfaces$e0832c0c14$ForEachInterfaceRW$class$ = { 
    0,
    som$Interfaces$e0832c0c14$ForEachInterfaceRW$apply,
};

struct som$Interfaces$e0832c0c14$TestInterface$Class$ som$Interfaces$e0832c0c14$TestInterface$class$ = { 
    0,
    som$Interfaces$e0832c0c14$TestInterface$test,
};

struct som$Interfaces$e0832c0c14$ForEachInterface$Class$ som$Interfaces$e0832c0c14$ForEachInterface$class$ = { 
    0,
    som$Interfaces$e0832c0c14$ForEachInterface$apply,
};

static int initDone$ = 0;
void som$Interfaces$e0832c0c14$init$(void) {
    if(initDone$) return; else initDone$ = 1;
}
OBX$Cmd som$Interfaces$e0832c0c14$cmd$(const char* name) {
    if( name == 0 ) return som$Interfaces$e0832c0c14$init$;
    return 0;
}
