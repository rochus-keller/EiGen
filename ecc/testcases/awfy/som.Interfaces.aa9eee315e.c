// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Interfaces.aa9eee315e.h"
#include "som.Vector.aa9eee315e.h"

void som$Interfaces$aa9eee315e$TestInterface$init$(struct som$Interfaces$aa9eee315e$TestInterface* inst){
    inst->class$ = &som$Interfaces$aa9eee315e$TestInterface$class$;
}
void som$Interfaces$aa9eee315e$ForEachInterface$init$(struct som$Interfaces$aa9eee315e$ForEachInterface* inst){
    inst->class$ = &som$Interfaces$aa9eee315e$ForEachInterface$class$;
}
void som$Interfaces$aa9eee315e$ForEachInterfaceRW$init$(struct som$Interfaces$aa9eee315e$ForEachInterfaceRW* inst){
    inst->class$ = &som$Interfaces$aa9eee315e$ForEachInterfaceRW$class$;
}
void som$Interfaces$aa9eee315e$Comparator$init$(struct som$Interfaces$aa9eee315e$Comparator* inst){
    inst->class$ = &som$Interfaces$aa9eee315e$Comparator$class$;
}
void som$Interfaces$aa9eee315e$ForEachInterface$apply(void* this, struct som$Set$04445da84e$Set * * elem) {
    struct som$Interfaces$aa9eee315e$ForEachInterface* this$ = this;
}

void som$Interfaces$aa9eee315e$ForEachInterfaceRW$apply(void* this, struct som$Set$04445da84e$Set * * elem) {
    struct som$Interfaces$aa9eee315e$ForEachInterfaceRW* this$ = this;
}

uint8_t som$Interfaces$aa9eee315e$TestInterface$test(void* this, struct som$Set$04445da84e$Set * * elem) {
    struct som$Interfaces$aa9eee315e$TestInterface* this$ = this;
    return 0;
}

int32_t som$Interfaces$aa9eee315e$Comparator$compare(void* this, struct som$Set$04445da84e$Set * * i, struct som$Set$04445da84e$Set * * j) {
    struct som$Interfaces$aa9eee315e$Comparator* this$ = this;
    return 0;
}

struct som$Interfaces$aa9eee315e$TestInterface$Class$ som$Interfaces$aa9eee315e$TestInterface$class$ = { 
    0,
    som$Interfaces$aa9eee315e$TestInterface$test,
};

struct som$Interfaces$aa9eee315e$ForEachInterface$Class$ som$Interfaces$aa9eee315e$ForEachInterface$class$ = { 
    0,
    som$Interfaces$aa9eee315e$ForEachInterface$apply,
};

struct som$Interfaces$aa9eee315e$ForEachInterfaceRW$Class$ som$Interfaces$aa9eee315e$ForEachInterfaceRW$class$ = { 
    0,
    som$Interfaces$aa9eee315e$ForEachInterfaceRW$apply,
};

struct som$Interfaces$aa9eee315e$Comparator$Class$ som$Interfaces$aa9eee315e$Comparator$class$ = { 
    0,
    som$Interfaces$aa9eee315e$Comparator$compare,
};

static int initDone$ = 0;
void som$Interfaces$aa9eee315e$init$(void) {
    if(initDone$) return; else initDone$ = 1;
}
OBX$Cmd som$Interfaces$aa9eee315e$cmd$(const char* name) {
    if( name == 0 ) return som$Interfaces$aa9eee315e$init$;
    return 0;
}
