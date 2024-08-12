// Generated by Oberon+ IDE (Mono) 0.9.107 on 2024-08-10T01:27:54

#include "Intmm.h"

int32_t Intmm$ima[41][41];
int32_t Intmm$imb[41][41];
int32_t Intmm$imr[41][41];
void Intmm$Initmatrix(struct OBX$Array$2 m) {
    int32_t temp;
    int32_t i;
    int32_t j;
    struct OBX$Array$2* $t0;
    temp = 0;
    i = 0;
    j = 0;
    i = 1;
    while(1) {
        if( (i <= 40) ) {
            j = 1;
            while(1) {
                if( (j <= 40) ) {
                    temp = Util$Rand();
                    (((int32_t *)(m).$a)[i*41+j]) = ((temp - (OBX$Div32(temp,120) * 120)) - 60);
                    j++;
                } else {
                    break;
                }
            }
            i++;
        } else {
            break;
        }
    }
}

void Intmm$Innerproduct(int32_t * result, struct OBX$Array$2 a, struct OBX$Array$2 b, int32_t row, int32_t column) {
    int32_t i;
    struct OBX$Array$2* $t0;
    struct OBX$Array$2* $t1;
    i = 0;
    (*result) = 0;
    i = 1;
    while(1) {
        if( (i <= 40) ) {
            (*result) = ((*result) + ((((int32_t *)(a).$a)[row*41+i]) * (((int32_t *)(b).$a)[i*41+column])));
            i++;
        } else {
            break;
        }
    }
}

void Intmm$Run() {
    int32_t i;
    int32_t j;
    struct OBX$Array$2* $t0;
    i = 0;
    j = 0;
    Util$Initrand();
    Intmm$Initmatrix((struct OBX$Array$2){41,41,1,Intmm$ima});
    Intmm$Initmatrix((struct OBX$Array$2){41,41,1,Intmm$imb});
    i = 1;
    while(1) {
        if( (i <= 40) ) {
            j = 1;
            while(1) {
                if( (j <= 40) ) {
                    Intmm$Innerproduct(&(((int32_t *)((struct OBX$Array$2){41,41,1,Intmm$imr}).$a)[i*41+j]), (struct OBX$Array$2){41,41,1,Intmm$ima}, (struct OBX$Array$2){41,41,1,Intmm$imb}, i, j);
                    j++;
                } else {
                    break;
                }
            }
            i++;
        } else {
            break;
        }
    }
}

static int initDone$ = 0;
void Intmm$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    Util$init$();
    memset(&Intmm$ima,0,sizeof(Intmm$ima));
    memset(&Intmm$imb,0,sizeof(Intmm$imb));
    memset(&Intmm$imr,0,sizeof(Intmm$imr));
}
OBX$Cmd Intmm$cmd$(const char* name) {
    if( name == 0 ) return Intmm$init$;
    if( strcmp(name,"Run") == 0 ) return Intmm$Run;
    return 0;
}