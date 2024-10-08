// Generated by Oberon+ IDE (Mono) 0.9.107 on 2024-08-10T01:27:54

#include "Quick.h"

int32_t Quick$sortlist[5001];
int32_t Quick$biggest = 0;
int32_t Quick$littlest = 0;
int32_t Quick$top = 0;
void Quick$Initarr() {
    int32_t i;
    int32_t temp;
    struct OBX$Array$1* $t0;
    struct OBX$Array$1* $t1;
    i = 0;
    temp = 0;
    Util$Initrand();
    Quick$biggest = 0;
    Quick$littlest = 0;
    i = 1;
    while(1) {
        if( (i <= 5000) ) {
            temp = Util$Rand();
            (((int32_t *)((struct OBX$Array$1){5001,1,Quick$sortlist}).$a)[i]) = ((temp - (OBX$Div32(temp,100000) * 100000)) - 50000);
            if( ((((int32_t *)((struct OBX$Array$1){5001,1,Quick$sortlist}).$a)[i]) > Quick$biggest) ) {
                Quick$biggest = (((int32_t *)((struct OBX$Array$1){5001,1,Quick$sortlist}).$a)[i]);
            } else if( ((((int32_t *)((struct OBX$Array$1){5001,1,Quick$sortlist}).$a)[i]) < Quick$littlest) ) {
                Quick$littlest = (((int32_t *)((struct OBX$Array$1){5001,1,Quick$sortlist}).$a)[i]);
            } 
            i++;
        } else {
            break;
        }
    }
}

void Quick$Quicksort(struct OBX$Array$1 a, int32_t l, int32_t r) {
    int32_t i;
    int32_t j;
    int32_t x;
    int32_t w;
    struct OBX$Array$1* $t0;
    struct OBX$Array$1* $t1;
    i = 0;
    j = 0;
    x = 0;
    w = 0;
    i = l;
    j = r;
    //x = ((int32_t *)a.$a)[OBX$Div32((l + r),2)]; // ok
    x = (*($t0 = (&a),&((int32_t *)$t0->$a)[OBX$Div32((l + r),2)])); // orig, crash
    //$t0 = (&a); x = ((int32_t *)$t0->$a)[OBX$Div32((l + r),2)]; // crash
    //$t0 = (&a); int32_t idx = OBX$Div32((l + r),2); x = ((int32_t *)$t0->$a)[idx]; // ok
    do {
        while(1) {
            if( ((*($t0 = (&a),&((int32_t *)$t0->$a)[i])) < x) ) {
                i = (i + 1);
            } else {
                break;
            }
        }
        while(1) {
            if( (x < (*($t0 = (&a),&((int32_t *)$t0->$a)[j]))) ) {
                j = (j - 1);
            } else {
                break;
            }
        }
        if( (i <= j) ) {
            w = (*($t0 = (&a),&((int32_t *)$t0->$a)[i]));
            (*($t0 = (&a),&((int32_t *)$t0->$a)[i])) = (*($t1 = (&a),&((int32_t *)$t1->$a)[j]));
            (*($t0 = (&a),&((int32_t *)$t0->$a)[j])) = w;
            i = (i + 1);
            j = (j - 1);
        } 
    }while(!((i > j)));
    if( (l < j) ) {
        Quick$Quicksort(a, l, j);
    } 
    if( (i < r) ) {
        Quick$Quicksort(a, i, r);
    } 
}

void Quick$Run() {
    struct OBX$Array$1* $t0;
    struct OBX$Array$1* $t1;
    Quick$Initarr();
    Quick$Quicksort((struct OBX$Array$1){5001,1,Quick$sortlist}, 1, 5000);
    if( (((((int32_t *)((struct OBX$Array$1){5001,1,Quick$sortlist}).$a)[1]) != Quick$littlest) || ((((int32_t *)((struct OBX$Array$1){5001,1,Quick$sortlist}).$a)[5000]) != Quick$biggest)) ) {
        Util$Str((const struct OBX$Array$1){18,0,OBX$FromUtf(" Error in Quick.$",18,0)});
    } 
}

static int initDone$ = 0;
void Quick$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    Util$init$();
    memset(&Quick$sortlist,0,sizeof(Quick$sortlist));
}
OBX$Cmd Quick$cmd$(const char* name) {
    if( name == 0 ) return Quick$init$;
    if( strcmp(name,"Initarr") == 0 ) return Quick$Initarr;
    if( strcmp(name,"Run") == 0 ) return Quick$Run;
    return 0;
}
