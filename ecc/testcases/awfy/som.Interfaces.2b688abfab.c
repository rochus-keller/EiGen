// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Interfaces.2b688abfab.h"
#include "som.Set.2b688abfab.h"

void som$Interfaces$2b688abfab$Comparator$init$(struct som$Interfaces$2b688abfab$Comparator* inst){
    inst->class$ = &som$Interfaces$2b688abfab$Comparator$class$;
}
void som$Interfaces$2b688abfab$ForEachInterfaceRW$init$(struct som$Interfaces$2b688abfab$ForEachInterfaceRW* inst){
    inst->class$ = &som$Interfaces$2b688abfab$ForEachInterfaceRW$class$;
}
void som$Interfaces$2b688abfab$TestInterface$init$(struct som$Interfaces$2b688abfab$TestInterface* inst){
    inst->class$ = &som$Interfaces$2b688abfab$TestInterface$class$;
}
void som$Interfaces$2b688abfab$ForEachInterface$init$(struct som$Interfaces$2b688abfab$ForEachInterface* inst){
    inst->class$ = &som$Interfaces$2b688abfab$ForEachInterface$class$;
}
void som$Interfaces$2b688abfab$ForEachInterface$apply(void* this, struct Havlak$SimpleLoop * * elem) {
    struct som$Interfaces$2b688abfab$ForEachInterface* this$ = this;
}

void som$Interfaces$2b688abfab$ForEachInterfaceRW$apply(void* this, struct Havlak$SimpleLoop * * elem) {
    struct som$Interfaces$2b688abfab$ForEachInterfaceRW* this$ = this;
}

uint8_t som$Interfaces$2b688abfab$TestInterface$test(void* this, struct Havlak$SimpleLoop * * elem) {
    struct som$Interfaces$2b688abfab$TestInterface* this$ = this;
    return 0;
}

int32_t som$Interfaces$2b688abfab$Comparator$compare(void* this, struct Havlak$SimpleLoop * * i, struct Havlak$SimpleLoop * * j) {
    struct som$Interfaces$2b688abfab$Comparator* this$ = this;
    return 0;
}

struct som$Interfaces$2b688abfab$Comparator$Class$ som$Interfaces$2b688abfab$Comparator$class$ = { 
    0,
    som$Interfaces$2b688abfab$Comparator$compare,
};

struct som$Interfaces$2b688abfab$ForEachInterfaceRW$Class$ som$Interfaces$2b688abfab$ForEachInterfaceRW$class$ = { 
    0,
    som$Interfaces$2b688abfab$ForEachInterfaceRW$apply,
};

struct som$Interfaces$2b688abfab$TestInterface$Class$ som$Interfaces$2b688abfab$TestInterface$class$ = { 
    0,
    som$Interfaces$2b688abfab$TestInterface$test,
};

struct som$Interfaces$2b688abfab$ForEachInterface$Class$ som$Interfaces$2b688abfab$ForEachInterface$class$ = { 
    0,
    som$Interfaces$2b688abfab$ForEachInterface$apply,
};

static int initDone$ = 0;
void som$Interfaces$2b688abfab$init$(void) {
    if(initDone$) return; else initDone$ = 1;
}
OBX$Cmd som$Interfaces$2b688abfab$cmd$(const char* name) {
    if( name == 0 ) return som$Interfaces$2b688abfab$init$;
    return 0;
}
