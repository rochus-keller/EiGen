// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Interfaces.f13888695d.h"
#include "som.Vector.f13888695d.h"

void som$Interfaces$f13888695d$TestInterface$init$(struct som$Interfaces$f13888695d$TestInterface* inst){
    inst->class$ = &som$Interfaces$f13888695d$TestInterface$class$;
}
void som$Interfaces$f13888695d$ForEachInterface$init$(struct som$Interfaces$f13888695d$ForEachInterface* inst){
    inst->class$ = &som$Interfaces$f13888695d$ForEachInterface$class$;
}
void som$Interfaces$f13888695d$Comparator$init$(struct som$Interfaces$f13888695d$Comparator* inst){
    inst->class$ = &som$Interfaces$f13888695d$Comparator$class$;
}
void som$Interfaces$f13888695d$ForEachInterfaceRW$init$(struct som$Interfaces$f13888695d$ForEachInterfaceRW* inst){
    inst->class$ = &som$Interfaces$f13888695d$ForEachInterfaceRW$class$;
}
void som$Interfaces$f13888695d$ForEachInterface$apply(void* this, struct CD2$Aircraft * * elem) {
    struct som$Interfaces$f13888695d$ForEachInterface* this$ = this;
}

void som$Interfaces$f13888695d$ForEachInterfaceRW$apply(void* this, struct CD2$Aircraft * * elem) {
    struct som$Interfaces$f13888695d$ForEachInterfaceRW* this$ = this;
}

uint8_t som$Interfaces$f13888695d$TestInterface$test(void* this, struct CD2$Aircraft * * elem) {
    struct som$Interfaces$f13888695d$TestInterface* this$ = this;
    return 0;
}

int32_t som$Interfaces$f13888695d$Comparator$compare(void* this, struct CD2$Aircraft * * i, struct CD2$Aircraft * * j) {
    struct som$Interfaces$f13888695d$Comparator* this$ = this;
    return 0;
}

struct som$Interfaces$f13888695d$TestInterface$Class$ som$Interfaces$f13888695d$TestInterface$class$ = { 
    0,
    som$Interfaces$f13888695d$TestInterface$test,
};

struct som$Interfaces$f13888695d$ForEachInterface$Class$ som$Interfaces$f13888695d$ForEachInterface$class$ = { 
    0,
    som$Interfaces$f13888695d$ForEachInterface$apply,
};

struct som$Interfaces$f13888695d$Comparator$Class$ som$Interfaces$f13888695d$Comparator$class$ = { 
    0,
    som$Interfaces$f13888695d$Comparator$compare,
};

struct som$Interfaces$f13888695d$ForEachInterfaceRW$Class$ som$Interfaces$f13888695d$ForEachInterfaceRW$class$ = { 
    0,
    som$Interfaces$f13888695d$ForEachInterfaceRW$apply,
};

static int initDone$ = 0;
void som$Interfaces$f13888695d$init$(void) {
    if(initDone$) return; else initDone$ = 1;
}
OBX$Cmd som$Interfaces$f13888695d$cmd$(const char* name) {
    if( name == 0 ) return som$Interfaces$f13888695d$init$;
    return 0;
}