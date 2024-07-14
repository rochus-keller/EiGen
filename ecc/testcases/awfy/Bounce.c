// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "Bounce.h"

void Bounce$Bounce$init$(struct Bounce$Bounce* inst){
    inst->class$ = &Bounce$Bounce$class$;
}
void Bounce$Ball$init$(struct Bounce$Ball* inst){
    inst->class$ = &Bounce$Ball$class$;
}
struct Bounce$Ball * Bounce$createBall() {
    struct Bounce$Ball * b;
    struct Bounce$Ball * $t0;
    b = 0;
    $t0 = OBX$Alloc(sizeof(struct Bounce$Ball));
    memset($t0,0,sizeof(struct Bounce$Ball));
    b = $t0;
    Bounce$Ball$init$($t0);
    (*b).x = OBX$Mod32(som$Random$next(),500);
    (*b).y = OBX$Mod32(som$Random$next(),500);
    (*b).xVel = (OBX$Mod32(som$Random$next(),300) - 150);
    (*b).yVel = (OBX$Mod32(som$Random$next(),300) - 150);
    return b;
}

uint8_t Bounce$Ball$bounce(void* this) {
    struct Bounce$Ball* this$ = this;
    int32_t xLimit;
    int32_t yLimit;
    uint8_t bounced;
    xLimit = 0;
    yLimit = 0;
    bounced = 0;
    xLimit = 500;
    yLimit = 500;
    bounced = 0;
    (*this$).x = ((*this$).x + (*this$).xVel);
    (*this$).y = ((*this$).y + (*this$).yVel);
    if( ((*this$).x > xLimit) ) {
        (*this$).x = xLimit;
        (*this$).xVel = (-abs((*this$).xVel));
        bounced = 1;
    } 
    if( ((*this$).x < 0) ) {
        (*this$).x = 0;
        (*this$).xVel = abs((*this$).xVel);
        bounced = 1;
    } 
    if( ((*this$).y > yLimit) ) {
        (*this$).y = yLimit;
        (*this$).yVel = (-abs((*this$).yVel));
        bounced = 1;
    } 
    if( ((*this$).y < 0) ) {
        (*this$).y = 0;
        (*this$).yVel = abs((*this$).yVel);
        bounced = 1;
    } 
    return bounced;
}

struct Bounce$Bounce * Bounce$create() {
    struct Bounce$Bounce * b;
    struct Bounce$Bounce * $t0;
    b = 0;
    $t0 = OBX$Alloc(sizeof(struct Bounce$Bounce));
    memset($t0,0,sizeof(struct Bounce$Bounce));
    b = $t0;
    Bounce$Bounce$init$($t0);
    return b;
}

struct Benchmark$Result * Bounce$Bounce$benchmark(void* this) {
    struct Bounce$Bounce* this$ = this;
    struct Benchmark$IntResult * res;
    int32_t bounces;
    int32_t i;
    int32_t j;
    struct Bounce$Ball * balls[100];
    struct OBX$Array$1* $t0;
    void* $t1;
    uint8_t (* $t2)(void*);
    struct Benchmark$IntResult * $t3;
    res = 0;
    bounces = 0;
    i = 0;
    j = 0;
    memset(&balls,0,sizeof(balls));
    som$Random$reset();
    bounces = 0;
    i = 0;
    while(1) {
        if( (i <= (100 - 1)) ) {
            (((struct Bounce$Ball * *)((struct OBX$Array$1){100,1,balls}).$a)[i]) = Bounce$createBall();
            i = (i + 1);
        } else {
            break;
        }
    }
    i = 0;
    while(1) {
        if( (i <= (50 - 1)) ) {
            j = 0;
            while(1) {
                if( (j <= (100 - 1)) ) {
                    if( ($t2 = ((struct Bounce$Ball *)($t1 = &(*(((struct Bounce$Ball * *)((struct OBX$Array$1){100,1,balls}).$a)[j]))))->class$->bounce, $t2($t1)) ) {
                        bounces++;
                    } 
                    j = (j + 1);
                } else {
                    break;
                }
            }
            i = (i + 1);
        } else {
            break;
        }
    }
    $t3 = OBX$Alloc(sizeof(struct Benchmark$IntResult));
    memset($t3,0,sizeof(struct Benchmark$IntResult));
    res = $t3;
    Benchmark$IntResult$init$($t3);
    (*res).res = bounces;
    return ((struct Benchmark$Result *)res);
}

uint8_t Bounce$Bounce$verifyResult(void* this, struct Benchmark$Result * result) {
    struct Bounce$Bounce* this$ = this;
    return ((*((struct Benchmark$IntResult*)result)).res == 1331);
}

struct Bounce$Bounce$Class$ Bounce$Bounce$class$ = { 
    &Benchmark$Benchmark$class$,
    Bounce$Bounce$benchmark,
    Bounce$Bounce$verifyResult,
    Benchmark$Benchmark$innerBenchmarkLoop,
};

struct Bounce$Ball$Class$ Bounce$Ball$class$ = { 
    0,
    Bounce$Ball$bounce,
};

static int initDone$ = 0;
void Bounce$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    som$Random$init$();
    Benchmark$init$();
}
OBX$Cmd Bounce$cmd$(const char* name) {
    if( name == 0 ) return Bounce$init$;
    return 0;
}