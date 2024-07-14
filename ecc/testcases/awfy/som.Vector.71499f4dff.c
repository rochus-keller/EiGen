// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.Vector.71499f4dff.h"
#include "Json.h"

void som$Vector$71499f4dff$Vector$init$(struct som$Vector$71499f4dff$Vector* inst){
    inst->class$ = &som$Vector$71499f4dff$Vector$class$;
}
struct som$Vector$71499f4dff$Vector * som$Vector$71499f4dff$createWithSize(int32_t siz) {
    struct som$Vector$71499f4dff$Vector * v;
    struct som$Vector$71499f4dff$Vector * $t0;
    struct OBX$Array$1 * $t1;
    v = 0;
    $t0 = OBX$Alloc(sizeof(struct som$Vector$71499f4dff$Vector));
    memset($t0,0,sizeof(struct som$Vector$71499f4dff$Vector));
    v = $t0;
    som$Vector$71499f4dff$Vector$init$($t0);
    {int $0 = siz, $n = $0, $s=sizeof(struct OBX$Array$1); $t1 = OBX$Alloc($s*$n); memset($t1,0,$s*$n); (*v).storage = (struct OBX$Array$1){$0, 1, $t1};};
    (*v).firstIdx = 0;
    (*v).lastIdx = 0;
    return v;
}

struct som$Vector$71499f4dff$Vector * som$Vector$71499f4dff$create() {
    return som$Vector$71499f4dff$createWithSize(50);
}

struct som$Vector$71499f4dff$Vector * som$Vector$71499f4dff$createWithElement(struct OBX$Array$1 * elem) {
    struct som$Vector$71499f4dff$Vector * v;
    void* $t0;
    void (* $t1)(void*, struct OBX$Array$1 *);
    v = 0;
    v = som$Vector$71499f4dff$createWithSize(1);
    ($t1 = ((struct som$Vector$71499f4dff$Vector *)($t0 = &(*v)))->class$->append, $t1($t0, &(*elem)));
    return v;
}

struct OBX$Array$1 som$Vector$71499f4dff$Vector$at(void* this, int32_t idx) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    struct OBX$Array$1* $t0;
    if( (idx >= ((*this$).storage).$1) ) {
        return (struct OBX$Array$1){0};
    } 
    return (*($t0 = (&(*this$).storage),&((struct OBX$Array$1 *)$t0->$a)[idx]));
}

void som$Vector$71499f4dff$Vector$resize(void* this, int32_t newLength) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    struct OBX$Array$1 storage;
    int32_t oldLength;
    int32_t i;
    struct OBX$Array$1 * $t0;
    struct OBX$Array$1* $t1;
    struct OBX$Array$1* $t2;
    memset(&storage,0,sizeof(storage));
    oldLength = 0;
    i = 0;
    {int $0 = newLength, $n = $0, $s=sizeof(struct OBX$Array$1); $t0 = OBX$Alloc($s*$n); memset($t0,0,$s*$n); storage = (struct OBX$Array$1){$0, 1, $t0};};
    i = 0;
    while(1) {
        if( (i <= (((*this$).storage).$1 - 1)) ) {
            (*($t1 = (&storage),&((struct OBX$Array$1 *)$t1->$a)[i])) = (*($t2 = (&(*this$).storage),&((struct OBX$Array$1 *)$t2->$a)[i]));
            i = (i + 1);
        } else {
            break;
        }
    }
    (*this$).storage = storage;
}

void som$Vector$71499f4dff$Vector$atPut(void* this, int32_t idx, struct OBX$Array$1 * elem) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
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
        ($t1 = ((struct som$Vector$71499f4dff$Vector *)($t0 = &(*this$)))->class$->resize, $t1($t0, length));
    } 
    (*($t2 = (&(*this$).storage),&((struct OBX$Array$1 *)$t2->$a)[idx])) = (*elem);
    if( ((*this$).lastIdx < (idx + 1)) ) {
        (*this$).lastIdx = (idx + 1);
    } 
}

void som$Vector$71499f4dff$Vector$append(void* this, struct OBX$Array$1 * elem) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    int32_t lenght;
    void* $t0;
    void (* $t1)(void*, int32_t);
    struct OBX$Array$1* $t2;
    lenght = 0;
    lenght = ((*this$).storage).$1;
    if( ((*this$).lastIdx >= lenght) ) {
        lenght = (lenght * 2);
        ($t1 = ((struct som$Vector$71499f4dff$Vector *)($t0 = &(*this$)))->class$->resize, $t1($t0, lenght));
    } 
    (*($t2 = (&(*this$).storage),&((struct OBX$Array$1 *)$t2->$a)[(*this$).lastIdx])) = (*elem);
    (*this$).lastIdx = ((*this$).lastIdx + 1);
}

uint8_t som$Vector$71499f4dff$Vector$isEmpty(void* this) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    return ((*this$).lastIdx == (*this$).firstIdx);
}

struct OBX$Array$1 som$Vector$71499f4dff$Vector$first(void* this) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    void* $t0;
    uint8_t (* $t1)(void*);
    struct OBX$Array$1* $t2;
    if( ($t1 = ((struct som$Vector$71499f4dff$Vector *)($t0 = &(*this$)))->class$->isEmpty, $t1($t0)) ) {
        return (struct OBX$Array$1){0};
    } 
    return (*($t2 = (&(*this$).storage),&((struct OBX$Array$1 *)$t2->$a)[(*this$).firstIdx]));
}

struct OBX$Array$1 som$Vector$71499f4dff$Vector$removeFirst(void* this) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    void* $t0;
    uint8_t (* $t1)(void*);
    struct OBX$Array$1* $t2;
    if( ($t1 = ((struct som$Vector$71499f4dff$Vector *)($t0 = &(*this$)))->class$->isEmpty, $t1($t0)) ) {
        return (struct OBX$Array$1){0};
    } 
    (*this$).firstIdx = ((*this$).firstIdx + 1);
    return (*($t2 = (&(*this$).storage),&((struct OBX$Array$1 *)$t2->$a)[((*this$).firstIdx - 1)]));
}

void som$Vector$71499f4dff$Vector$removeAll(void* this) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    (*this$).firstIdx = 0;
    (*this$).lastIdx = 0;
}

int32_t som$Vector$71499f4dff$Vector$getSize(void* this) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    return ((*this$).lastIdx - (*this$).firstIdx);
}

int32_t som$Vector$71499f4dff$Vector$capacity(void* this) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    return ((*this$).storage).$1;
}

void som$Vector$71499f4dff$Vector$forEach(void* this, struct som$Interfaces$71499f4dff$ForEachInterface * fn) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    int32_t i;
    void* $t0;
    void (* $t1)(void*, struct OBX$Array$1 *);
    struct OBX$Array$1* $t2;
    i = 0;
    i = (*this$).firstIdx;
    while(1) {
        if( (i <= ((*this$).lastIdx - 1)) ) {
            ($t1 = ((struct som$Interfaces$71499f4dff$ForEachInterface *)($t0 = &(*fn)))->class$->apply, $t1($t0, &(*($t2 = (&(*this$).storage),&((struct OBX$Array$1 *)$t2->$a)[i]))));
            i = (i + 1);
        } else {
            break;
        }
    }
}

uint8_t som$Vector$71499f4dff$Vector$hasSome(void* this, struct som$Interfaces$71499f4dff$TestInterface * fn) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    int32_t i;
    void* $t0;
    uint8_t (* $t1)(void*, struct OBX$Array$1 *);
    struct OBX$Array$1* $t2;
    i = 0;
    i = (*this$).firstIdx;
    while(1) {
        if( (i <= ((*this$).lastIdx - 1)) ) {
            if( ($t1 = ((struct som$Interfaces$71499f4dff$TestInterface *)($t0 = &(*fn)))->class$->test, $t1($t0, &(*($t2 = (&(*this$).storage),&((struct OBX$Array$1 *)$t2->$a)[i])))) ) {
                return 1;
            } 
            i = (i + 1);
        } else {
            break;
        }
    }
    return 0;
}

uint8_t som$Vector$71499f4dff$Vector$getOne(void* this, struct som$Interfaces$71499f4dff$TestInterface * fn, struct OBX$Array$1 * out) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    int32_t i;
    void* $t0;
    uint8_t (* $t1)(void*, struct OBX$Array$1 *);
    struct OBX$Array$1* $t2;
    struct OBX$Array$1* $t3;
    i = 0;
    i = (*this$).firstIdx;
    while(1) {
        if( (i <= ((*this$).lastIdx - 1)) ) {
            if( ($t1 = ((struct som$Interfaces$71499f4dff$TestInterface *)($t0 = &(*fn)))->class$->test, $t1($t0, &(*($t2 = (&(*this$).storage),&((struct OBX$Array$1 *)$t2->$a)[i])))) ) {
                (*out) = (*($t3 = (&(*this$).storage),&((struct OBX$Array$1 *)$t3->$a)[i]));
                return 1;
            } 
            i = (i + 1);
        } else {
            break;
        }
    }
    return 0;
}

uint8_t som$Vector$71499f4dff$Vector$remove(void* this, struct OBX$Array$1 * obj, uint8_t (*eq)(struct OBX$Array$1 *, struct OBX$Array$1 *)) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    struct OBX$Array$1 newArray;
    int32_t i;
    int32_t newLast;
    uint8_t found;
    void* $t0;
    int32_t (* $t1)(void*);
    struct OBX$Array$1 * $t2;
    struct OBX$Array$1* $t3;
    struct OBX$Array$1* $t4;
    memset(&newArray,0,sizeof(newArray));
    i = 0;
    newLast = 0;
    found = 0;
    {int $0 = ($t1 = ((struct som$Vector$71499f4dff$Vector *)($t0 = &(*this$)))->class$->capacity, $t1($t0)), $n = $0, $s=sizeof(struct OBX$Array$1); $t2 = OBX$Alloc($s*$n); memset($t2,0,$s*$n); newArray = (struct OBX$Array$1){$0, 1, $t2};};
    newLast = 0;
    found = 0;
    i = (*this$).firstIdx;
    while(1) {
        if( (i <= ((*this$).lastIdx - 1)) ) {
            if( eq(&(*($t3 = (&(*this$).storage),&((struct OBX$Array$1 *)$t3->$a)[i])), &(*obj)) ) {
                found = 1;
            } else {
                (*($t3 = (&newArray),&((struct OBX$Array$1 *)$t3->$a)[newLast])) = (*($t4 = (&(*this$).storage),&((struct OBX$Array$1 *)$t4->$a)[i]));
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

void som$Vector$71499f4dff$Vector$sort(void* this, struct som$Interfaces$71499f4dff$Comparator * c) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    void* $t0;
    int32_t (* $t1)(void*);
    void* $t2;
    void (* $t3)(void*, int32_t, int32_t, struct som$Interfaces$71499f4dff$Comparator *);
    if( (($t1 = ((struct som$Vector$71499f4dff$Vector *)($t0 = &(*this$)))->class$->getSize, $t1($t0)) > 0) ) {
        ($t3 = ((struct som$Vector$71499f4dff$Vector *)($t2 = &(*this$)))->class$->sortImp, $t3($t2, (*this$).firstIdx, ((*this$).lastIdx - 1), &(*c)));
    } 
}

void som$Vector$71499f4dff$Vector$sortImp(void* this, int32_t i, int32_t j, struct som$Interfaces$71499f4dff$Comparator * c) {
    struct som$Vector$71499f4dff$Vector* this$ = this;
    int32_t n;
    int32_t ij;
    int32_t k;
    int32_t l;
    struct OBX$Array$1 di;
    struct OBX$Array$1 dj;
    struct OBX$Array$1 tt;
    struct OBX$Array$1 dij;
    struct OBX$Array$1* $t0;
    void* $t1;
    int32_t (* $t2)(void*, struct OBX$Array$1 *, struct OBX$Array$1 *);
    void* $t3;
    int32_t (* $t4)(void*, struct OBX$Array$1 *, struct OBX$Array$1 *);
    void (* $t5)(void*, int32_t, int32_t, struct som$Interfaces$71499f4dff$Comparator *);
    n = 0;
    ij = 0;
    k = 0;
    l = 0;
    memset(&di,0,sizeof(di));
    memset(&dj,0,sizeof(dj));
    memset(&tt,0,sizeof(tt));
    memset(&dij,0,sizeof(dij));
    n = ((j + 1) - i);
    if( (n <= 1) ) {
        return ;
    } 
    di = (*($t0 = (&(*this$).storage),&((struct OBX$Array$1 *)$t0->$a)[i]));
    dj = (*($t0 = (&(*this$).storage),&((struct OBX$Array$1 *)$t0->$a)[j]));
    if( (($t2 = ((struct som$Interfaces$71499f4dff$Comparator *)($t1 = &(*c)))->class$->compare, $t2($t1, &di, &dj)) > 0) ) {
        som$Vector$71499f4dff$swap((*this$).storage, i, j);
        tt = di;
        di = dj;
        dj = tt;
    } 
    if( (n > 2) ) {
        ij = OBX$Div32((i + j),2);
        dij = (*($t0 = (&(*this$).storage),&((struct OBX$Array$1 *)$t0->$a)[ij]));
        if( (($t2 = ((struct som$Interfaces$71499f4dff$Comparator *)($t1 = &(*c)))->class$->compare, $t2($t1, &di, &dij)) <= 0) ) {
            if( (($t4 = ((struct som$Interfaces$71499f4dff$Comparator *)($t3 = &(*c)))->class$->compare, $t4($t3, &dij, &dj)) > 0) ) {
                som$Vector$71499f4dff$swap((*this$).storage, j, ij);
                dij = dj;
            } 
        } else {
            som$Vector$71499f4dff$swap((*this$).storage, i, ij);
            dij = di;
        }
        if( (n > 3) ) {
            k = i;
            l = (j - 1);
            while(1) {
                while(1) {
                    if( ((k <= l) && (($t2 = ((struct som$Interfaces$71499f4dff$Comparator *)($t1 = &(*c)))->class$->compare, $t2($t1, &dij, &(*($t0 = (&(*this$).storage),&((struct OBX$Array$1 *)$t0->$a)[l])))) <= 0)) ) {
                        l = (l - 1);
                    } else {
                        break;
                    }
                }
                k = (k + 1);
                while(1) {
                    if( ((k <= l) && (($t2 = ((struct som$Interfaces$71499f4dff$Comparator *)($t1 = &(*c)))->class$->compare, $t2($t1, &(*($t0 = (&(*this$).storage),&((struct OBX$Array$1 *)$t0->$a)[k])), &dij)) <= 0)) ) {
                        k = (k + 1);
                    } else {
                        break;
                    }
                }
                if( (k > l) ) {
                    break;
                } 
                som$Vector$71499f4dff$swap((*this$).storage, k, l);
            }
            ($t5 = ((struct som$Vector$71499f4dff$Vector *)($t1 = &(*this$)))->class$->sortImp, $t5($t1, i, l, &(*c)));
            ($t5 = ((struct som$Vector$71499f4dff$Vector *)($t1 = &(*this$)))->class$->sortImp, $t5($t1, k, j, &(*c)));
        } 
    } 
}

void som$Vector$71499f4dff$swap(struct OBX$Array$1 storage2, int32_t i, int32_t j) {
    struct OBX$Array$1 temp;
    struct OBX$Array$1* $t0;
    struct OBX$Array$1* $t1;
    memset(&temp,0,sizeof(temp));
    temp = (*($t0 = (&storage2),&((struct OBX$Array$1 *)$t0->$a)[i]));
    (*($t0 = (&storage2),&((struct OBX$Array$1 *)$t0->$a)[i])) = (*($t1 = (&storage2),&((struct OBX$Array$1 *)$t1->$a)[j]));
    (*($t0 = (&storage2),&((struct OBX$Array$1 *)$t0->$a)[j])) = temp;
}

struct som$Vector$71499f4dff$Vector$Class$ som$Vector$71499f4dff$Vector$class$ = { 
    0,
    som$Vector$71499f4dff$Vector$at,
    som$Vector$71499f4dff$Vector$resize,
    som$Vector$71499f4dff$Vector$atPut,
    som$Vector$71499f4dff$Vector$append,
    som$Vector$71499f4dff$Vector$isEmpty,
    som$Vector$71499f4dff$Vector$first,
    som$Vector$71499f4dff$Vector$removeFirst,
    som$Vector$71499f4dff$Vector$removeAll,
    som$Vector$71499f4dff$Vector$getSize,
    som$Vector$71499f4dff$Vector$capacity,
    som$Vector$71499f4dff$Vector$forEach,
    som$Vector$71499f4dff$Vector$hasSome,
    som$Vector$71499f4dff$Vector$getOne,
    som$Vector$71499f4dff$Vector$remove,
    som$Vector$71499f4dff$Vector$sort,
    som$Vector$71499f4dff$Vector$sortImp,
};

static int initDone$ = 0;
void som$Vector$71499f4dff$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    som$Interfaces$71499f4dff$init$();
}
OBX$Cmd som$Vector$71499f4dff$cmd$(const char* name) {
    if( name == 0 ) return som$Vector$71499f4dff$init$;
    return 0;
}