// Generated by Oberon+ IDE (Mono) 0.9.107 on 2024-08-10T01:27:54

#include "Towers.h"

void Towers$element$init$(struct Towers$element* inst){
    inst->class$ = &Towers$element$class$;
}
int32_t Towers$stack[4];
struct Towers$element Towers$cellspace[19];
int32_t Towers$freelist = 0;
int32_t Towers$movesdone = 0;
void Towers$Makenull(int32_t s) {
    struct OBX$Array$1* $t0;
    (((int32_t *)((struct OBX$Array$1){4,1,Towers$stack}).$a)[s]) = 0;
}

int32_t Towers$Getelement() {
    int32_t temp;
    struct OBX$Array$1* $t0;
    temp = 0;
    if( (Towers$freelist > 0) ) {
        temp = Towers$freelist;
        Towers$freelist = (((struct Towers$element *)((struct OBX$Array$1){19,1,Towers$cellspace}).$a)[Towers$freelist]).next;
    } else {
        Util$Str((const struct OBX$Array$1){17,0,OBX$FromUtf("out of space   $",17,0)});
    }
    return temp;
}

void Towers$Push(int32_t i, int32_t s) {
    int32_t localel;
    uint8_t errorfound;
    struct OBX$Array$1* $t0;
    struct OBX$Array$1* $t1;
    struct OBX$Array$1* $t2;
    localel = 0;
    errorfound = 0;
    errorfound = 0;
    if( ((((int32_t *)((struct OBX$Array$1){4,1,Towers$stack}).$a)[s]) > 0) ) {
        if( ((((struct Towers$element *)((struct OBX$Array$1){19,1,Towers$cellspace}).$a)[(((int32_t *)((struct OBX$Array$1){4,1,Towers$stack}).$a)[s])]).discsize <= i) ) {
            errorfound = 1;
            Util$Str((const struct OBX$Array$1){17,0,OBX$FromUtf("disc size error$",17,0)});
        } 
    } 
    if( (!errorfound) ) {
        localel = Towers$Getelement();
        (((struct Towers$element *)((struct OBX$Array$1){19,1,Towers$cellspace}).$a)[localel]).next = (((int32_t *)((struct OBX$Array$1){4,1,Towers$stack}).$a)[s]);
        (((int32_t *)((struct OBX$Array$1){4,1,Towers$stack}).$a)[s]) = localel;
        (((struct Towers$element *)((struct OBX$Array$1){19,1,Towers$cellspace}).$a)[localel]).discsize = i;
    } 
}

void Towers$Init(int32_t s, int32_t n) {
    int32_t discctr;
    discctr = 0;
    Towers$Makenull(s);
    discctr = n;
    while(1) {
        if( (discctr >= 1) ) {
            Towers$Push(discctr, s);
            discctr--;
        } else {
            break;
        }
    }
}

int32_t Towers$Pop(int32_t s) {
    int32_t temp;
    int32_t temp1;
    struct OBX$Array$1* $t0;
    struct OBX$Array$1* $t1;
    struct OBX$Array$1* $t2;
    temp = 0;
    temp1 = 0;
    if( ((((int32_t *)((struct OBX$Array$1){4,1,Towers$stack}).$a)[s]) > 0) ) {
        temp1 = (((struct Towers$element *)((struct OBX$Array$1){19,1,Towers$cellspace}).$a)[(((int32_t *)((struct OBX$Array$1){4,1,Towers$stack}).$a)[s])]).discsize;
        temp = (((struct Towers$element *)((struct OBX$Array$1){19,1,Towers$cellspace}).$a)[(((int32_t *)((struct OBX$Array$1){4,1,Towers$stack}).$a)[s])]).next;
        (((struct Towers$element *)((struct OBX$Array$1){19,1,Towers$cellspace}).$a)[(((int32_t *)((struct OBX$Array$1){4,1,Towers$stack}).$a)[s])]).next = Towers$freelist;
        Towers$freelist = (((int32_t *)((struct OBX$Array$1){4,1,Towers$stack}).$a)[s]);
        (((int32_t *)((struct OBX$Array$1){4,1,Towers$stack}).$a)[s]) = temp;
    } else {
        Util$Str((const struct OBX$Array$1){17,0,OBX$FromUtf("nothing to pop $",17,0)});
        temp1 = 0;
    }
    return temp1;
}

void Towers$Move(int32_t s1, int32_t s2) {
    Towers$Push(Towers$Pop(s1), s2);
    Towers$movesdone = (Towers$movesdone + 1);
}

void Towers$tower(int32_t i, int32_t j, int32_t k) {
    int32_t other;
    other = 0;
    if( (k == 1) ) {
        Towers$Move(i, j);
    } else {
        other = ((6 - i) - j);
        Towers$tower(i, other, (k - 1));
        Towers$Move(i, j);
        Towers$tower(other, j, (k - 1));
    }
}

void Towers$Run() {
    int32_t i;
    struct OBX$Array$1* $t0;
    i = 0;
    i = 1;
    while(1) {
        if( (i <= 18) ) {
            (((struct Towers$element *)((struct OBX$Array$1){19,1,Towers$cellspace}).$a)[i]).next = (i - 1);
            i++;
        } else {
            break;
        }
    }
    Towers$freelist = 18;
    Towers$Init(1, 14);
    Towers$Makenull(2);
    Towers$Makenull(3);
    Towers$movesdone = 0;
    Towers$tower(1, 2, 14);
    if( (Towers$movesdone != 16383) ) {
        Util$Str((const struct OBX$Array$1){19,0,OBX$FromUtf(" Error in Towers.$",19,0)});
    } 
}

struct Towers$element$Class$ Towers$element$class$ = { 
    0,
};

static int initDone$ = 0;
void Towers$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    Util$init$();
    memset(&Towers$stack,0,sizeof(Towers$stack));
    memset(&Towers$cellspace,0,sizeof(Towers$cellspace));
    for(int $i = 0; $i < (19); $i++) Towers$element$init$(&((struct Towers$element *)Towers$cellspace)[$i]);
}
OBX$Cmd Towers$cmd$(const char* name) {
    if( name == 0 ) return Towers$init$;
    if( strcmp(name,"Run") == 0 ) return Towers$Run;
    return 0;
}