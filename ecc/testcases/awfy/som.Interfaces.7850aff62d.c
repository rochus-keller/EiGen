// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Interfaces.7850aff62d.h"
#include "DeltaBlue.h"

void som$Interfaces$7850aff62d$ForEachInterfaceRW$init$(struct som$Interfaces$7850aff62d$ForEachInterfaceRW* inst){
    inst->class$ = &som$Interfaces$7850aff62d$ForEachInterfaceRW$class$;
}
void som$Interfaces$7850aff62d$Comparator$init$(struct som$Interfaces$7850aff62d$Comparator* inst){
    inst->class$ = &som$Interfaces$7850aff62d$Comparator$class$;
}
void som$Interfaces$7850aff62d$TestInterface$init$(struct som$Interfaces$7850aff62d$TestInterface* inst){
    inst->class$ = &som$Interfaces$7850aff62d$TestInterface$class$;
}
void som$Interfaces$7850aff62d$ForEachInterface$init$(struct som$Interfaces$7850aff62d$ForEachInterface* inst){
    inst->class$ = &som$Interfaces$7850aff62d$ForEachInterface$class$;
}
void som$Interfaces$7850aff62d$ForEachInterface$apply(void* this, struct DeltaBlue$Variable * * elem) {
    struct som$Interfaces$7850aff62d$ForEachInterface* this$ = this;
}

void som$Interfaces$7850aff62d$ForEachInterfaceRW$apply(void* this, struct DeltaBlue$Variable * * elem) {
    struct som$Interfaces$7850aff62d$ForEachInterfaceRW* this$ = this;
}

uint8_t som$Interfaces$7850aff62d$TestInterface$test(void* this, struct DeltaBlue$Variable * * elem) {
    struct som$Interfaces$7850aff62d$TestInterface* this$ = this;
    return 0;
}

int32_t som$Interfaces$7850aff62d$Comparator$compare(void* this, struct DeltaBlue$Variable * * i, struct DeltaBlue$Variable * * j) {
    struct som$Interfaces$7850aff62d$Comparator* this$ = this;
    return 0;
}

struct som$Interfaces$7850aff62d$ForEachInterfaceRW$Class$ som$Interfaces$7850aff62d$ForEachInterfaceRW$class$ = { 
    0,
    som$Interfaces$7850aff62d$ForEachInterfaceRW$apply,
};

struct som$Interfaces$7850aff62d$Comparator$Class$ som$Interfaces$7850aff62d$Comparator$class$ = { 
    0,
    som$Interfaces$7850aff62d$Comparator$compare,
};

struct som$Interfaces$7850aff62d$TestInterface$Class$ som$Interfaces$7850aff62d$TestInterface$class$ = { 
    0,
    som$Interfaces$7850aff62d$TestInterface$test,
};

struct som$Interfaces$7850aff62d$ForEachInterface$Class$ som$Interfaces$7850aff62d$ForEachInterface$class$ = { 
    0,
    som$Interfaces$7850aff62d$ForEachInterface$apply,
};

static int initDone$ = 0;
void som$Interfaces$7850aff62d$init$(void) {
    if(initDone$) return; else initDone$ = 1;
}
OBX$Cmd som$Interfaces$7850aff62d$cmd$(const char* name) {
    if( name == 0 ) return som$Interfaces$7850aff62d$init$;
    return 0;
}