// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Interfaces.ad6c2c594a.h"
#include "som.Vector.ad6c2c594a.h"

void som$Interfaces$ad6c2c594a$ForEachInterfaceRW$init$(struct som$Interfaces$ad6c2c594a$ForEachInterfaceRW* inst){
    inst->class$ = &som$Interfaces$ad6c2c594a$ForEachInterfaceRW$class$;
}
void som$Interfaces$ad6c2c594a$TestInterface$init$(struct som$Interfaces$ad6c2c594a$TestInterface* inst){
    inst->class$ = &som$Interfaces$ad6c2c594a$TestInterface$class$;
}
void som$Interfaces$ad6c2c594a$ForEachInterface$init$(struct som$Interfaces$ad6c2c594a$ForEachInterface* inst){
    inst->class$ = &som$Interfaces$ad6c2c594a$ForEachInterface$class$;
}
void som$Interfaces$ad6c2c594a$Comparator$init$(struct som$Interfaces$ad6c2c594a$Comparator* inst){
    inst->class$ = &som$Interfaces$ad6c2c594a$Comparator$class$;
}
void som$Interfaces$ad6c2c594a$ForEachInterface$apply(void* this, struct DeltaBlue$AbstractConstraint * * elem) {
    struct som$Interfaces$ad6c2c594a$ForEachInterface* this$ = this;
}

void som$Interfaces$ad6c2c594a$ForEachInterfaceRW$apply(void* this, struct DeltaBlue$AbstractConstraint * * elem) {
    struct som$Interfaces$ad6c2c594a$ForEachInterfaceRW* this$ = this;
}

uint8_t som$Interfaces$ad6c2c594a$TestInterface$test(void* this, struct DeltaBlue$AbstractConstraint * * elem) {
    struct som$Interfaces$ad6c2c594a$TestInterface* this$ = this;
    return 0;
}

int32_t som$Interfaces$ad6c2c594a$Comparator$compare(void* this, struct DeltaBlue$AbstractConstraint * * i, struct DeltaBlue$AbstractConstraint * * j) {
    struct som$Interfaces$ad6c2c594a$Comparator* this$ = this;
    return 0;
}

struct som$Interfaces$ad6c2c594a$ForEachInterfaceRW$Class$ som$Interfaces$ad6c2c594a$ForEachInterfaceRW$class$ = { 
    0,
    som$Interfaces$ad6c2c594a$ForEachInterfaceRW$apply,
};

struct som$Interfaces$ad6c2c594a$TestInterface$Class$ som$Interfaces$ad6c2c594a$TestInterface$class$ = { 
    0,
    som$Interfaces$ad6c2c594a$TestInterface$test,
};

struct som$Interfaces$ad6c2c594a$ForEachInterface$Class$ som$Interfaces$ad6c2c594a$ForEachInterface$class$ = { 
    0,
    som$Interfaces$ad6c2c594a$ForEachInterface$apply,
};

struct som$Interfaces$ad6c2c594a$Comparator$Class$ som$Interfaces$ad6c2c594a$Comparator$class$ = { 
    0,
    som$Interfaces$ad6c2c594a$Comparator$compare,
};

static int initDone$ = 0;
void som$Interfaces$ad6c2c594a$init$(void) {
    if(initDone$) return; else initDone$ = 1;
}
OBX$Cmd som$Interfaces$ad6c2c594a$cmd$(const char* name) {
    if( name == 0 ) return som$Interfaces$ad6c2c594a$init$;
    return 0;
}