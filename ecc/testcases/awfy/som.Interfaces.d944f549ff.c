// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Interfaces.d944f549ff.h"
#include "som.Vector.d944f549ff.h"

void som$Interfaces$d944f549ff$TestInterface$init$(struct som$Interfaces$d944f549ff$TestInterface* inst){
    inst->class$ = &som$Interfaces$d944f549ff$TestInterface$class$;
}
void som$Interfaces$d944f549ff$ForEachInterface$init$(struct som$Interfaces$d944f549ff$ForEachInterface* inst){
    inst->class$ = &som$Interfaces$d944f549ff$ForEachInterface$class$;
}
void som$Interfaces$d944f549ff$ForEachInterfaceRW$init$(struct som$Interfaces$d944f549ff$ForEachInterfaceRW* inst){
    inst->class$ = &som$Interfaces$d944f549ff$ForEachInterfaceRW$class$;
}
void som$Interfaces$d944f549ff$Comparator$init$(struct som$Interfaces$d944f549ff$Comparator* inst){
    inst->class$ = &som$Interfaces$d944f549ff$Comparator$class$;
}
void som$Interfaces$d944f549ff$ForEachInterface$apply(void* this, struct Havlak$UnionFindNode * * elem) {
    struct som$Interfaces$d944f549ff$ForEachInterface* this$ = this;
}

void som$Interfaces$d944f549ff$ForEachInterfaceRW$apply(void* this, struct Havlak$UnionFindNode * * elem) {
    struct som$Interfaces$d944f549ff$ForEachInterfaceRW* this$ = this;
}

uint8_t som$Interfaces$d944f549ff$TestInterface$test(void* this, struct Havlak$UnionFindNode * * elem) {
    struct som$Interfaces$d944f549ff$TestInterface* this$ = this;
    return 0;
}

int32_t som$Interfaces$d944f549ff$Comparator$compare(void* this, struct Havlak$UnionFindNode * * i, struct Havlak$UnionFindNode * * j) {
    struct som$Interfaces$d944f549ff$Comparator* this$ = this;
    return 0;
}

struct som$Interfaces$d944f549ff$TestInterface$Class$ som$Interfaces$d944f549ff$TestInterface$class$ = { 
    0,
    som$Interfaces$d944f549ff$TestInterface$test,
};

struct som$Interfaces$d944f549ff$ForEachInterface$Class$ som$Interfaces$d944f549ff$ForEachInterface$class$ = { 
    0,
    som$Interfaces$d944f549ff$ForEachInterface$apply,
};

struct som$Interfaces$d944f549ff$ForEachInterfaceRW$Class$ som$Interfaces$d944f549ff$ForEachInterfaceRW$class$ = { 
    0,
    som$Interfaces$d944f549ff$ForEachInterfaceRW$apply,
};

struct som$Interfaces$d944f549ff$Comparator$Class$ som$Interfaces$d944f549ff$Comparator$class$ = { 
    0,
    som$Interfaces$d944f549ff$Comparator$compare,
};

static int initDone$ = 0;
void som$Interfaces$d944f549ff$init$(void) {
    if(initDone$) return; else initDone$ = 1;
}
OBX$Cmd som$Interfaces$d944f549ff$cmd$(const char* name) {
    if( name == 0 ) return som$Interfaces$d944f549ff$init$;
    return 0;
}
