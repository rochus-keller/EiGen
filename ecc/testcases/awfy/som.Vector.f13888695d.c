// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Vector.f13888695d.h"
#include "CD2.h"

void som$Vector$f13888695d$Vector$init$(struct som$Vector$f13888695d$Vector* inst){
    inst->class$ = &som$Vector$f13888695d$Vector$class$;
}
struct som$Vector$f13888695d$Vector * som$Vector$f13888695d$createWithSize(int32_t siz) {
    struct som$Vector$f13888695d$Vector * v;
    struct som$Vector$f13888695d$Vector * $t0;
    struct CD2$Aircraft * * $t1;
    v = 0;
    $t0 = OBX$Alloc(sizeof(struct som$Vector$f13888695d$Vector));
    memset($t0,0,sizeof(struct som$Vector$f13888695d$Vector));
    v = $t0;
    som$Vector$f13888695d$Vector$init$($t0);
    {int $0 = siz, $n = $0, $s=sizeof(struct CD2$Aircraft *); $t1 = OBX$Alloc($s*$n); memset($t1,0,$s*$n); (*v).storage = (struct OBX$Array$1){$0, 1, $t1};};
    (*v).firstIdx = 0;
    (*v).lastIdx = 0;
    return v;
}

struct som$Vector$f13888695d$Vector * som$Vector$f13888695d$create() {
    return som$Vector$f13888695d$createWithSize(50);
}

struct som$Vector$f13888695d$Vector * som$Vector$f13888695d$createWithElement(struct CD2$Aircraft * * elem) {
    struct som$Vector$f13888695d$Vector * v;
    void* $t0;
    void (* $t1)(void*, struct CD2$Aircraft * *);
    v = 0;
    v = som$Vector$f13888695d$createWithSize(1);
    ($t1 = ((struct som$Vector$f13888695d$Vector *)($t0 = &(*v)))->class$->append, $t1($t0, &(*elem)));
    return v;
}

struct CD2$Aircraft * som$Vector$f13888695d$Vector$at(void* this, int32_t idx) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    struct OBX$Array$1* $t0;
    if( (idx >= ((*this$).storage).$1) ) {
        return 0;
    } 
    return (*($t0 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t0->$a)[idx]));
}

void som$Vector$f13888695d$Vector$resize(void* this, int32_t newLength) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    struct OBX$Array$1 storage;
    int32_t oldLength;
    int32_t i;
    struct CD2$Aircraft * * $t0;
    struct OBX$Array$1* $t1;
    struct OBX$Array$1* $t2;
    memset(&storage,0,sizeof(storage));
    oldLength = 0;
    i = 0;
    {int $0 = newLength, $n = $0, $s=sizeof(struct CD2$Aircraft *); $t0 = OBX$Alloc($s*$n); memset($t0,0,$s*$n); storage = (struct OBX$Array$1){$0, 1, $t0};};
    i = 0;
    while(1) {
        if( (i <= (((*this$).storage).$1 - 1)) ) {
            (*($t1 = (&storage),&((struct CD2$Aircraft * *)$t1->$a)[i])) = (*($t2 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t2->$a)[i]));
            i = (i + 1);
        } else {
            break;
        }
    }
    (*this$).storage = storage;
}

void som$Vector$f13888695d$Vector$atPut(void* this, int32_t idx, struct CD2$Aircraft * * elem) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    int32_t length;
    void* $t0;
    void (* $t1)(void*, int32_t);
    struct OBX$Array$1* $t2;
    length = 0;
    length = ((*this$).storage).$1;
    if( (idx >= length) ) {
        while(1) {
            if( (length <= idx) ) {
                length = (length * 2);
            } else {
                break;
            }
        }
        ($t1 = ((struct som$Vector$f13888695d$Vector *)($t0 = &(*this$)))->class$->resize, $t1($t0, length));
    } 
    (*($t2 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t2->$a)[idx])) = (*elem);
    if( ((*this$).lastIdx < (idx + 1)) ) {
        (*this$).lastIdx = (idx + 1);
    } 
}

void som$Vector$f13888695d$Vector$append(void* this, struct CD2$Aircraft * * elem) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    int32_t lenght;
    void* $t0;
    void (* $t1)(void*, int32_t);
    struct OBX$Array$1* $t2;
    lenght = 0;
    lenght = ((*this$).storage).$1;
    if( ((*this$).lastIdx >= lenght) ) {
        lenght = (lenght * 2);
        ($t1 = ((struct som$Vector$f13888695d$Vector *)($t0 = &(*this$)))->class$->resize, $t1($t0, lenght));
    } 
    (*($t2 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t2->$a)[(*this$).lastIdx])) = (*elem);
    (*this$).lastIdx = ((*this$).lastIdx + 1);
}

uint8_t som$Vector$f13888695d$Vector$isEmpty(void* this) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    return ((*this$).lastIdx == (*this$).firstIdx);
}

struct CD2$Aircraft * som$Vector$f13888695d$Vector$first(void* this) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    void* $t0;
    uint8_t (* $t1)(void*);
    struct OBX$Array$1* $t2;
    if( ($t1 = ((struct som$Vector$f13888695d$Vector *)($t0 = &(*this$)))->class$->isEmpty, $t1($t0)) ) {
        return 0;
    } 
    return (*($t2 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t2->$a)[(*this$).firstIdx]));
}

struct CD2$Aircraft * som$Vector$f13888695d$Vector$removeFirst(void* this) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    void* $t0;
    uint8_t (* $t1)(void*);
    struct OBX$Array$1* $t2;
    if( ($t1 = ((struct som$Vector$f13888695d$Vector *)($t0 = &(*this$)))->class$->isEmpty, $t1($t0)) ) {
        return 0;
    } 
    (*this$).firstIdx = ((*this$).firstIdx + 1);
    return (*($t2 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t2->$a)[((*this$).firstIdx - 1)]));
}

void som$Vector$f13888695d$Vector$removeAll(void* this) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    (*this$).firstIdx = 0;
    (*this$).lastIdx = 0;
}

int32_t som$Vector$f13888695d$Vector$getSize(void* this) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    return ((*this$).lastIdx - (*this$).firstIdx);
}

int32_t som$Vector$f13888695d$Vector$capacity(void* this) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    return ((*this$).storage).$1;
}

void som$Vector$f13888695d$Vector$forEach(void* this, struct som$Interfaces$f13888695d$ForEachInterface * fn) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    int32_t i;
    void* $t0;
    void (* $t1)(void*, struct CD2$Aircraft * *);
    struct OBX$Array$1* $t2;
    i = 0;
    i = (*this$).firstIdx;
    while(1) {
        if( (i <= ((*this$).lastIdx - 1)) ) {
            ($t1 = ((struct som$Interfaces$f13888695d$ForEachInterface *)($t0 = &(*fn)))->class$->apply, $t1($t0, &(*($t2 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t2->$a)[i]))));
            i = (i + 1);
        } else {
            break;
        }
    }
}

uint8_t som$Vector$f13888695d$Vector$hasSome(void* this, struct som$Interfaces$f13888695d$TestInterface * fn) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    int32_t i;
    void* $t0;
    uint8_t (* $t1)(void*, struct CD2$Aircraft * *);
    struct OBX$Array$1* $t2;
    i = 0;
    i = (*this$).firstIdx;
    while(1) {
        if( (i <= ((*this$).lastIdx - 1)) ) {
            if( ($t1 = ((struct som$Interfaces$f13888695d$TestInterface *)($t0 = &(*fn)))->class$->test, $t1($t0, &(*($t2 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t2->$a)[i])))) ) {
                return 1;
            } 
            i = (i + 1);
        } else {
            break;
        }
    }
    return 0;
}

uint8_t som$Vector$f13888695d$Vector$getOne(void* this, struct som$Interfaces$f13888695d$TestInterface * fn, struct CD2$Aircraft * * out) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    int32_t i;
    void* $t0;
    uint8_t (* $t1)(void*, struct CD2$Aircraft * *);
    struct OBX$Array$1* $t2;
    struct OBX$Array$1* $t3;
    i = 0;
    i = (*this$).firstIdx;
    while(1) {
        if( (i <= ((*this$).lastIdx - 1)) ) {
            if( ($t1 = ((struct som$Interfaces$f13888695d$TestInterface *)($t0 = &(*fn)))->class$->test, $t1($t0, &(*($t2 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t2->$a)[i])))) ) {
                (*out) = (*($t3 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t3->$a)[i]));
                return 1;
            } 
            i = (i + 1);
        } else {
            break;
        }
    }
    return 0;
}

uint8_t som$Vector$f13888695d$Vector$remove(void* this, struct CD2$Aircraft * * obj, uint8_t (*eq)(struct CD2$Aircraft * *, struct CD2$Aircraft * *)) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    struct OBX$Array$1 newArray;
    int32_t i;
    int32_t newLast;
    uint8_t found;
    void* $t0;
    int32_t (* $t1)(void*);
    struct CD2$Aircraft * * $t2;
    struct OBX$Array$1* $t3;
    struct OBX$Array$1* $t4;
    memset(&newArray,0,sizeof(newArray));
    i = 0;
    newLast = 0;
    found = 0;
    {int $0 = ($t1 = ((struct som$Vector$f13888695d$Vector *)($t0 = &(*this$)))->class$->capacity, $t1($t0)), $n = $0, $s=sizeof(struct CD2$Aircraft *); $t2 = OBX$Alloc($s*$n); memset($t2,0,$s*$n); newArray = (struct OBX$Array$1){$0, 1, $t2};};
    newLast = 0;
    found = 0;
    i = (*this$).firstIdx;
    while(1) {
        if( (i <= ((*this$).lastIdx - 1)) ) {
            if( eq(&(*($t3 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t3->$a)[i])), &(*obj)) ) {
                found = 1;
            } else {
                (*($t3 = (&newArray),&((struct CD2$Aircraft * *)$t3->$a)[newLast])) = (*($t4 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t4->$a)[i]));
                newLast++;
            }
            i = (i + 1);
        } else {
            break;
        }
    }
    (*this$).storage = newArray;
    (*this$).lastIdx = newLast;
    (*this$).firstIdx = 0;
    return found;
}

void som$Vector$f13888695d$Vector$sort(void* this, struct som$Interfaces$f13888695d$Comparator * c) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    void* $t0;
    int32_t (* $t1)(void*);
    void* $t2;
    void (* $t3)(void*, int32_t, int32_t, struct som$Interfaces$f13888695d$Comparator *);
    if( (($t1 = ((struct som$Vector$f13888695d$Vector *)($t0 = &(*this$)))->class$->getSize, $t1($t0)) > 0) ) {
        ($t3 = ((struct som$Vector$f13888695d$Vector *)($t2 = &(*this$)))->class$->sortImp, $t3($t2, (*this$).firstIdx, ((*this$).lastIdx - 1), &(*c)));
    } 
}

void som$Vector$f13888695d$Vector$sortImp(void* this, int32_t i, int32_t j, struct som$Interfaces$f13888695d$Comparator * c) {
    struct som$Vector$f13888695d$Vector* this$ = this;
    int32_t n;
    int32_t ij;
    int32_t k;
    int32_t l;
    struct CD2$Aircraft * di;
    struct CD2$Aircraft * dj;
    struct CD2$Aircraft * tt;
    struct CD2$Aircraft * dij;
    struct OBX$Array$1* $t0;
    void* $t1;
    int32_t (* $t2)(void*, struct CD2$Aircraft * *, struct CD2$Aircraft * *);
    void* $t3;
    int32_t (* $t4)(void*, struct CD2$Aircraft * *, struct CD2$Aircraft * *);
    void (* $t5)(void*, int32_t, int32_t, struct som$Interfaces$f13888695d$Comparator *);
    n = 0;
    ij = 0;
    k = 0;
    l = 0;
    di = 0;
    dj = 0;
    tt = 0;
    dij = 0;
    n = ((j + 1) - i);
    if( (n <= 1) ) {
        return ;
    } 
    di = (*($t0 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t0->$a)[i]));
    dj = (*($t0 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t0->$a)[j]));
    if( (($t2 = ((struct som$Interfaces$f13888695d$Comparator *)($t1 = &(*c)))->class$->compare, $t2($t1, &di, &dj)) > 0) ) {
        som$Vector$f13888695d$swap((*this$).storage, i, j);
        tt = di;
        di = dj;
        dj = tt;
    } 
    if( (n > 2) ) {
        ij = OBX$Div32((i + j),2);
        dij = (*($t0 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t0->$a)[ij]));
        if( (($t2 = ((struct som$Interfaces$f13888695d$Comparator *)($t1 = &(*c)))->class$->compare, $t2($t1, &di, &dij)) <= 0) ) {
            if( (($t4 = ((struct som$Interfaces$f13888695d$Comparator *)($t3 = &(*c)))->class$->compare, $t4($t3, &dij, &dj)) > 0) ) {
                som$Vector$f13888695d$swap((*this$).storage, j, ij);
                dij = dj;
            } 
        } else {
            som$Vector$f13888695d$swap((*this$).storage, i, ij);
            dij = di;
        }
        if( (n > 3) ) {
            k = i;
            l = (j - 1);
            while(1) {
                while(1) {
                    if( ((k <= l) && (($t2 = ((struct som$Interfaces$f13888695d$Comparator *)($t1 = &(*c)))->class$->compare, $t2($t1, &dij, &(*($t0 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t0->$a)[l])))) <= 0)) ) {
                        l = (l - 1);
                    } else {
                        break;
                    }
                }
                k = (k + 1);
                while(1) {
                    if( ((k <= l) && (($t2 = ((struct som$Interfaces$f13888695d$Comparator *)($t1 = &(*c)))->class$->compare, $t2($t1, &(*($t0 = (&(*this$).storage),&((struct CD2$Aircraft * *)$t0->$a)[k])), &dij)) <= 0)) ) {
                        k = (k + 1);
                    } else {
                        break;
                    }
                }
                if( (k > l) ) {
                    break;
                } 
                som$Vector$f13888695d$swap((*this$).storage, k, l);
            }
            ($t5 = ((struct som$Vector$f13888695d$Vector *)($t1 = &(*this$)))->class$->sortImp, $t5($t1, i, l, &(*c)));
            ($t5 = ((struct som$Vector$f13888695d$Vector *)($t1 = &(*this$)))->class$->sortImp, $t5($t1, k, j, &(*c)));
        } 
    } 
}

void som$Vector$f13888695d$swap(struct OBX$Array$1 storage2, int32_t i, int32_t j) {
    struct CD2$Aircraft * temp;
    struct OBX$Array$1* $t0;
    struct OBX$Array$1* $t1;
    temp = 0;
    temp = (*($t0 = (&storage2),&((struct CD2$Aircraft * *)$t0->$a)[i]));
    (*($t0 = (&storage2),&((struct CD2$Aircraft * *)$t0->$a)[i])) = (*($t1 = (&storage2),&((struct CD2$Aircraft * *)$t1->$a)[j]));
    (*($t0 = (&storage2),&((struct CD2$Aircraft * *)$t0->$a)[j])) = temp;
}

struct som$Vector$f13888695d$Vector$Class$ som$Vector$f13888695d$Vector$class$ = { 
    0,
    som$Vector$f13888695d$Vector$at,
    som$Vector$f13888695d$Vector$resize,
    som$Vector$f13888695d$Vector$atPut,
    som$Vector$f13888695d$Vector$append,
    som$Vector$f13888695d$Vector$isEmpty,
    som$Vector$f13888695d$Vector$first,
    som$Vector$f13888695d$Vector$removeFirst,
    som$Vector$f13888695d$Vector$removeAll,
    som$Vector$f13888695d$Vector$getSize,
    som$Vector$f13888695d$Vector$capacity,
    som$Vector$f13888695d$Vector$forEach,
    som$Vector$f13888695d$Vector$hasSome,
    som$Vector$f13888695d$Vector$getOne,
    som$Vector$f13888695d$Vector$remove,
    som$Vector$f13888695d$Vector$sort,
    som$Vector$f13888695d$Vector$sortImp,
};

static int initDone$ = 0;
void som$Vector$f13888695d$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    som$Interfaces$f13888695d$init$();
}
OBX$Cmd som$Vector$f13888695d$cmd$(const char* name) {
    if( name == 0 ) return som$Vector$f13888695d$init$;
    return 0;
}
