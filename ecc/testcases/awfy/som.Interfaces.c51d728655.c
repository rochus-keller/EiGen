// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Interfaces.c51d728655.h"
#include "som.Vector.c51d728655.h"

void som$Interfaces$c51d728655$ForEachInterface$init$(struct som$Interfaces$c51d728655$ForEachInterface* inst){
    inst->class$ = &som$Interfaces$c51d728655$ForEachInterface$class$;
}
void som$Interfaces$c51d728655$ForEachInterfaceRW$init$(struct som$Interfaces$c51d728655$ForEachInterfaceRW* inst){
    inst->class$ = &som$Interfaces$c51d728655$ForEachInterfaceRW$class$;
}
void som$Interfaces$c51d728655$Comparator$init$(struct som$Interfaces$c51d728655$Comparator* inst){
    inst->class$ = &som$Interfaces$c51d728655$Comparator$class$;
}
void som$Interfaces$c51d728655$TestInterface$init$(struct som$Interfaces$c51d728655$TestInterface* inst){
    inst->class$ = &som$Interfaces$c51d728655$TestInterface$class$;
}
void som$Interfaces$c51d728655$ForEachInterface$apply(void* this, struct DeltaBlue$Strength * * elem) {
    struct som$Interfaces$c51d728655$ForEachInterface* this$ = this;
}

void som$Interfaces$c51d728655$ForEachInterfaceRW$apply(void* this, struct DeltaBlue$Strength * * elem) {
    struct som$Interfaces$c51d728655$ForEachInterfaceRW* this$ = this;
}

uint8_t som$Interfaces$c51d728655$TestInterface$test(void* this, struct DeltaBlue$Strength * * elem) {
    struct som$Interfaces$c51d728655$TestInterface* this$ = this;
    return 0;
}

int32_t som$Interfaces$c51d728655$Comparator$compare(void* this, struct DeltaBlue$Strength * * i, struct DeltaBlue$Strength * * j) {
    struct som$Interfaces$c51d728655$Comparator* this$ = this;
    return 0;
}

struct som$Interfaces$c51d728655$ForEachInterface$Class$ som$Interfaces$c51d728655$ForEachInterface$class$ = { 
    0,
    som$Interfaces$c51d728655$ForEachInterface$apply,
};

struct som$Interfaces$c51d728655$ForEachInterfaceRW$Class$ som$Interfaces$c51d728655$ForEachInterfaceRW$class$ = { 
    0,
    som$Interfaces$c51d728655$ForEachInterfaceRW$apply,
};

struct som$Interfaces$c51d728655$Comparator$Class$ som$Interfaces$c51d728655$Comparator$class$ = { 
    0,
    som$Interfaces$c51d728655$Comparator$compare,
};

struct som$Interfaces$c51d728655$TestInterface$Class$ som$Interfaces$c51d728655$TestInterface$class$ = { 
    0,
    som$Interfaces$c51d728655$TestInterface$test,
};

static int initDone$ = 0;
void som$Interfaces$c51d728655$init$(void) {
    if(initDone$) return; else initDone$ = 1;
}
OBX$Cmd som$Interfaces$c51d728655$cmd$(const char* name) {
    if( name == 0 ) return som$Interfaces$c51d728655$init$;
    return 0;
}