// Generated by Oberon+ IDE (Mono) 0.9.107 on 2024-08-10T01:27:54

#include "Mm.h"

double Mm$rma[41][41];
double Mm$rmb[41][41];
double Mm$rmr[41][41];
void Mm$rInitmatrix(struct OBX$Array$2 m) {
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
                    (((double *)(m).$a)[i*41+j]) = (double)OBX$Div32(((temp - (OBX$Div32(temp,120) * 120)) - 60),3);
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

void Mm$rInnerproduct(double * result, struct OBX$Array$2 a, struct OBX$Array$2 b, int32_t row, int32_t column) {
    int32_t i;
    struct OBX$Array$2* $t0;
    struct OBX$Array$2* $t1;
    i = 0;
    (*result) = 0.0000000e+00;
    i = 1;
    while(1) {
        if( (i <= 40) ) {
            (*result) = ((*result) + ((((double *)(a).$a)[row*41+i]) * (((double *)(b).$a)[i*41+column])));
            i++;
        } else {
            break;
        }
    }
}

void Mm$Run() {
    int32_t i;
    int32_t j;
    struct OBX$Array$2* $t0;
    i = 0;
    j = 0;
    Util$Initrand();
    Mm$rInitmatrix((struct OBX$Array$2){41,41,1,Mm$rma});
    Mm$rInitmatrix((struct OBX$Array$2){41,41,1,Mm$rmb});
    i = 1;
    while(1) {
        if( (i <= 40) ) {
            j = 1;
            while(1) {
                if( (j <= 40) ) {
                    Mm$rInnerproduct(&(((double *)((struct OBX$Array$2){41,41,1,Mm$rmr}).$a)[i*41+j]), (struct OBX$Array$2){41,41,1,Mm$rma}, (struct OBX$Array$2){41,41,1,Mm$rmb}, i, j);
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
void Mm$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    Util$init$();
    memset(&Mm$rma,0,sizeof(Mm$rma));
    memset(&Mm$rmb,0,sizeof(Mm$rmb));
    memset(&Mm$rmr,0,sizeof(Mm$rmr));
}
OBX$Cmd Mm$cmd$(const char* name) {
    if( name == 0 ) return Mm$init$;
    if( strcmp(name,"Run") == 0 ) return Mm$Run;
    return 0;
}