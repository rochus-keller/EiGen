// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Interfaces.d1517c3aa3.h"
#include "som.RedBlackTree.14446907c4.h"

void som$Interfaces$d1517c3aa3$ForEachInterface$init$(struct som$Interfaces$d1517c3aa3$ForEachInterface* inst){
    inst->class$ = &som$Interfaces$d1517c3aa3$ForEachInterface$class$;
}
void som$Interfaces$d1517c3aa3$ForEachInterfaceRW$init$(struct som$Interfaces$d1517c3aa3$ForEachInterfaceRW* inst){
    inst->class$ = &som$Interfaces$d1517c3aa3$ForEachInterfaceRW$class$;
}
void som$Interfaces$d1517c3aa3$TestInterface$init$(struct som$Interfaces$d1517c3aa3$TestInterface* inst){
    inst->class$ = &som$Interfaces$d1517c3aa3$TestInterface$class$;
}
void som$Interfaces$d1517c3aa3$Comparator$init$(struct som$Interfaces$d1517c3aa3$Comparator* inst){
    inst->class$ = &som$Interfaces$d1517c3aa3$Comparator$class$;
}
void som$Interfaces$d1517c3aa3$ForEachInterface$apply(void* this, struct som$RedBlackTree$14446907c4$Entry * elem) {
    struct som$Interfaces$d1517c3aa3$ForEachInterface* this$ = this;
}

void som$Interfaces$d1517c3aa3$ForEachInterfaceRW$apply(void* this, struct som$RedBlackTree$14446907c4$Entry * elem) {
    struct som$Interfaces$d1517c3aa3$ForEachInterfaceRW* this$ = this;
}

uint8_t som$Interfaces$d1517c3aa3$TestInterface$test(void* this, struct som$RedBlackTree$14446907c4$Entry * elem) {
    struct som$Interfaces$d1517c3aa3$TestInterface* this$ = this;
    return 0;
}

int32_t som$Interfaces$d1517c3aa3$Comparator$compare(void* this, struct som$RedBlackTree$14446907c4$Entry * i, struct som$RedBlackTree$14446907c4$Entry * j) {
    struct som$Interfaces$d1517c3aa3$Comparator* this$ = this;
    return 0;
}

struct som$Interfaces$d1517c3aa3$ForEachInterface$Class$ som$Interfaces$d1517c3aa3$ForEachInterface$class$ = { 
    0,
    som$Interfaces$d1517c3aa3$ForEachInterface$apply,
};

struct som$Interfaces$d1517c3aa3$ForEachInterfaceRW$Class$ som$Interfaces$d1517c3aa3$ForEachInterfaceRW$class$ = { 
    0,
    som$Interfaces$d1517c3aa3$ForEachInterfaceRW$apply,
};

struct som$Interfaces$d1517c3aa3$TestInterface$Class$ som$Interfaces$d1517c3aa3$TestInterface$class$ = { 
    0,
    som$Interfaces$d1517c3aa3$TestInterface$test,
};

struct som$Interfaces$d1517c3aa3$Comparator$Class$ som$Interfaces$d1517c3aa3$Comparator$class$ = { 
    0,
    som$Interfaces$d1517c3aa3$Comparator$compare,
};

static int initDone$ = 0;
void som$Interfaces$d1517c3aa3$init$(void) {
    if(initDone$) return; else initDone$ = 1;
}
OBX$Cmd som$Interfaces$d1517c3aa3$cmd$(const char* name) {
    if( name == 0 ) return som$Interfaces$d1517c3aa3$init$;
    return 0;
}
