// Generated by Oberon+ IDE (Mono) 0.9.107 on 2024-08-10T01:27:54

#include "Bubble.h"

int32_t Bubble$sortlist[5001];
int32_t Bubble$biggest = 0;
int32_t Bubble$littlest = 0;
int32_t Bubble$top = 0;
void Bubble$bInitarr() {
    int32_t i;
    int32_t temp;
    struct OBX$Array$1* $t0;
    struct OBX$Array$1* $t1;
    i = 0;
    temp = 0;
    Util$Initrand();
    Bubble$biggest = 0;
    Bubble$littlest = 0;
    i = 1;
    while(1) {
        if( (i <= 500) ) {
            temp = Util$Rand();
            (((int32_t *)((struct OBX$Array$1){5001,1,Bubble$sortlist}).$a)[i]) = ((temp - (OBX$Div32(temp,100000) * 100000)) - 50000);
            if( ((((int32_t *)((struct OBX$Array$1){5001,1,Bubble$sortlist}).$a)[i]) > Bubble$biggest) ) {
                Bubble$biggest = (((int32_t *)((struct OBX$Array$1){5001,1,Bubble$sortlist}).$a)[i]);
            } else if( ((((int32_t *)((struct OBX$Array$1){5001,1,Bubble$sortlist}).$a)[i]) < Bubble$littlest) ) {
                Bubble$littlest = (((int32_t *)((struct OBX$Array$1){5001,1,Bubble$sortlist}).$a)[i]);
            } 
            i++;
        } else {
            break;
        }
    }
}

void Bubble$Run() {
    int32_t i;
    int32_t j;
    struct OBX$Array$1* $t0;
    struct OBX$Array$1* $t1;
    struct OBX$Array$1* $t2;
    i = 0;
    j = 0;
    Bubble$bInitarr();
    Bubble$top = 500;
    while(1) {
        if( (Bubble$top > 1) ) {
            i = 1;
            while(1) {
                if( (i < Bubble$top) ) {
                    if( ((((int32_t *)((struct OBX$Array$1){5001,1,Bubble$sortlist}).$a)[i]) > (((int32_t *)((struct OBX$Array$1){5001,1,Bubble$sortlist}).$a)[(i + 1)])) ) {
                        j = (((int32_t *)((struct OBX$Array$1){5001,1,Bubble$sortlist}).$a)[i]);
                        (((int32_t *)((struct OBX$Array$1){5001,1,Bubble$sortlist}).$a)[i]) = (((int32_t *)((struct OBX$Array$1){5001,1,Bubble$sortlist}).$a)[(i + 1)]);
                        (((int32_t *)((struct OBX$Array$1){5001,1,Bubble$sortlist}).$a)[(i + 1)]) = j;
                    } 
                    i = (i + 1);
                } else {
                    break;
                }
            }
            Bubble$top = (Bubble$top - 1);
        } else {
            break;
        }
    }
    if( (((((int32_t *)((struct OBX$Array$1){5001,1,Bubble$sortlist}).$a)[1]) != Bubble$littlest) || ((((int32_t *)((struct OBX$Array$1){5001,1,Bubble$sortlist}).$a)[500]) != Bubble$biggest)) ) {
        Util$Str((const struct OBX$Array$1){19,0,OBX$FromUtf("Error3 in Bubble.$",19,0)});
    } 
}

static int initDone$ = 0;
void Bubble$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    Util$init$();
    memset(&Bubble$sortlist,0,sizeof(Bubble$sortlist));
}
OBX$Cmd Bubble$cmd$(const char* name) {
    if( name == 0 ) return Bubble$init$;
    if( strcmp(name,"bInitarr") == 0 ) return Bubble$bInitarr;
    if( strcmp(name,"Run") == 0 ) return Bubble$Run;
    return 0;
}
