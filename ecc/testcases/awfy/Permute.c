// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "Permute.h"

void Permute$Permute$init$(struct Permute$Permute* inst){
    inst->class$ = &Permute$Permute$class$;
}
struct Permute$Permute * Permute$create() {
    struct Permute$Permute * p;
    struct Permute$Permute * $t0;
    p = 0;
    $t0 = OBX$Alloc(sizeof(struct Permute$Permute));
    memset($t0,0,sizeof(struct Permute$Permute));
    p = $t0;
    Permute$Permute$init$($t0);
    return p;
}

struct Benchmark$Result * Permute$Permute$benchmark(void* this) {
    struct Permute$Permute* this$ = this;
    struct Benchmark$IntResult * res;
    int32_t * $t0;
    void* $t1;
    void (* $t2)(void*, int32_t);
    struct Benchmark$IntResult * $t3;
    res = 0;
    (*this$).count = 0;
    {int $0 = 6, $n = $0, $s=sizeof(int32_t); $t0 = OBX$Alloc($s*$n); memset($t0,0,$s*$n); (*this$).v = (struct OBX$Array$1){$0, 1, $t0};};
    ($t2 = ((struct Permute$Permute *)($t1 = &(*this$)))->class$->permute, $t2($t1, 6));
    $t3 = OBX$Alloc(sizeof(struct Benchmark$IntResult));
    memset($t3,0,sizeof(struct Benchmark$IntResult));
    res = $t3;
    Benchmark$IntResult$init$($t3);
    (*res).res = (*this$).count;
    return ((struct Benchmark$Result *)res);
}

void Permute$Permute$permute(void* this, int32_t n) {
    struct Permute$Permute* this$ = this;
    int32_t n1;
    int32_t i;
    void* $t0;
    void (* $t1)(void*, int32_t);
    void (* $t2)(void*, int32_t, int32_t);
    n1 = 0;
    i = 0;
    (*this$).count++;
    if( (n != 0) ) {
        n1 = (n - 1);
        ($t1 = ((struct Permute$Permute *)($t0 = &(*this$)))->class$->permute, $t1($t0, n1));
        i = n1;
        while(1) {
            if( (i >= 0) ) {
                ($t2 = ((struct Permute$Permute *)($t0 = &(*this$)))->class$->swap, $t2($t0, n1, i));
                ($t1 = ((struct Permute$Permute *)($t0 = &(*this$)))->class$->permute, $t1($t0, n1));
                ($t2 = ((struct Permute$Permute *)($t0 = &(*this$)))->class$->swap, $t2($t0, n1, i));
                i--;
            } else {
                break;
            }
        }
    } 
}

void Permute$Permute$swap(void* this, int32_t i, int32_t j) {
    struct Permute$Permute* this$ = this;
    int32_t tmp;
    struct OBX$Array$1* $t0;
    struct OBX$Array$1* $t1;
    tmp = 0;
    tmp = (*($t0 = (&(*this$).v),&((int32_t *)$t0->$a)[i]));
    (*($t0 = (&(*this$).v),&((int32_t *)$t0->$a)[i])) = (*($t1 = (&(*this$).v),&((int32_t *)$t1->$a)[j]));
    (*($t0 = (&(*this$).v),&((int32_t *)$t0->$a)[j])) = tmp;
}

void Permute$swap(int32_t * i, int32_t * j) {
    int32_t tmp;
    tmp = 0;
    tmp = (*i);
    (*i) = (*j);
    (*j) = tmp;
}

uint8_t Permute$Permute$verifyResult(void* this, struct Benchmark$Result * result) {
    struct Permute$Permute* this$ = this;
    return ((*((struct Benchmark$IntResult*)result)).res == 8660);
}

struct Permute$Permute$Class$ Permute$Permute$class$ = { 
    &Benchmark$Benchmark$class$,
    Permute$Permute$benchmark,
    Permute$Permute$verifyResult,
    Benchmark$Benchmark$innerBenchmarkLoop,
    Permute$Permute$permute,
    Permute$Permute$swap,
};

static int initDone$ = 0;
void Permute$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    Benchmark$init$();
}
OBX$Cmd Permute$cmd$(const char* name) {
    if( name == 0 ) return Permute$init$;
    return 0;
}
