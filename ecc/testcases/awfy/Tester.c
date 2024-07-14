// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "Tester.h"

void Tester$TestVector$Comparator$init$(struct Tester$TestVector$Comparator* inst){
    inst->class$ = &Tester$TestVector$Comparator$class$;
}
void Tester$Test4$FI$init$(struct Tester$Test4$FI* inst){
    inst->class$ = &Tester$Test4$FI$class$;
}
void Tester$TestVector$Printer$init$(struct Tester$TestVector$Printer* inst){
    inst->class$ = &Tester$TestVector$Printer$class$;
}
void Tester$Test5$FI$init$(struct Tester$Test5$FI* inst){
    inst->class$ = &Tester$Test5$FI$class$;
}
struct OBX$Array$1 Tester$str;
int32_t Tester$Hash(struct OBX$Array$1 k) {
    return 0;
}

void Tester$TestVector() {
    struct som$Vector$04445da84e$Vector * l;
    struct Tester$TestVector$Printer p;
    struct Tester$TestVector$Comparator c;
    void* $t0;
    int32_t (* $t1)(void*);
    void (* $t2)(void*, int32_t *);
    void (* $t3)(void*, struct som$Interfaces$04445da84e$ForEachInterface *);
    void (* $t4)(void*, int32_t, int32_t *);
    void (* $t5)(void*, struct som$Interfaces$04445da84e$Comparator *);
    l = 0;
    memset(&p,0,sizeof(p));
    Tester$TestVector$Printer$init$(&p);
    memset(&c,0,sizeof(c));
    Tester$TestVector$Comparator$init$(&c);
    l = som$Vector$04445da84e$createWithElement(&(int32_t){33});
    OBX$PrintA(1,(const char*)((const struct OBX$Array$1){14,0,OBX$FromUtf("initial size:",14,0)}).$a);
    printf("%d\n",($t1 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*l)))->class$->getSize, $t1($t0)));
    ($t2 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*l)))->class$->append, $t2($t0, &(int32_t){44}));
    ($t2 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*l)))->class$->append, $t2($t0, &(int32_t){55}));
    ($t2 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*l)))->class$->append, $t2($t0, &(int32_t){66}));
    ($t2 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*l)))->class$->append, $t2($t0, &(int32_t){99}));
    ($t2 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*l)))->class$->append, $t2($t0, &(int32_t){88}));
    ($t2 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*l)))->class$->append, $t2($t0, &(int32_t){77}));
    OBX$PrintA(1,(const char*)((const struct OBX$Array$1){20,0,OBX$FromUtf("print each element:",20,0)}).$a);
    ($t3 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*l)))->class$->forEach, $t3($t0, ((struct som$Interfaces$04445da84e$ForEachInterface *)&p)));
    printf("%d\n",($t1 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*l)))->class$->removeFirst, $t1($t0)));
    ($t4 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*l)))->class$->atPut, $t4($t0, 2, &(int32_t){22}));
    OBX$PrintA(1,(const char*)((const struct OBX$Array$1){39,0,OBX$FromUtf("print each element after remove first:",39,0)}).$a);
    ($t3 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*l)))->class$->forEach, $t3($t0, ((struct som$Interfaces$04445da84e$ForEachInterface *)&p)));
    ($t5 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*l)))->class$->sort, $t5($t0, ((struct som$Interfaces$04445da84e$Comparator *)&c)));
    OBX$PrintA(1,(const char*)((const struct OBX$Array$1){31,0,OBX$FromUtf("print each element after sort:",31,0)}).$a);
    ($t3 = ((struct som$Vector$04445da84e$Vector *)($t0 = &(*l)))->class$->forEach, $t3($t0, ((struct som$Interfaces$04445da84e$ForEachInterface *)&p)));
}

void Tester$TestVector$Printer$apply(void* this, int32_t * elem) {
    struct Tester$TestVector$Printer* this$ = this;
    printf("%d\n",(*elem));
}

int32_t Tester$TestVector$Comparator$compare(void* this, int32_t * i, int32_t * j) {
    struct Tester$TestVector$Comparator* this$ = this;
    if( ((*i) < (*j)) ) {
        return (-1);
    } else if( ((*i) == (*j)) ) {
        return 0;
    } else {
        return 1;
    }
    return 0;
}

void Tester$Test2() {
    struct OBX$Array$2 args;
    char * $t0;
    struct OBX$Array$2* $t1;
    memset(&args,0,sizeof(args));
    {int $0 = 1, $1 = 32, $n = $0 * $1, $s=sizeof(char); $t0 = OBX$Alloc($s*$n); memset($t0,0,$s*$n); args = (struct OBX$Array$2){$0, $1, 1, $t0};};
    OBX$StrCopy(($t1 = (&args),&(struct OBX$Array$1){$t1->$2,1,&((char *)$t1->$a)[0*$t1->$2]}),0,&(const struct OBX$Array$1){8,0,OBX$FromUtf("Permute",8,0)},0);
    Harness$main(args);
}

void Tester$Test3() {
    som$Random$reset();
    assert((som$Random$next() == 22896));
    assert((som$Random$next() == 34761));
    assert((som$Random$next() == 34014));
    assert((som$Random$next() == 39231));
    assert((som$Random$next() == 52540));
    assert((som$Random$next() == 41445));
    assert((som$Random$next() == 1546));
    assert((som$Random$next() == 5947));
    assert((som$Random$next() == 65224));
    OBX$PrintA(1,(const char*)((const struct OBX$Array$1){11,0,OBX$FromUtf("Test3 done",11,0)}).$a);
}

void Tester$Test4() {
    struct som$RedBlackTree$4765cc5acb$RedBlackTree * t;
    char s[32];
    struct Tester$Test4$FI it;
    void* $t0;
    struct OBX$Array$1 (* $t1)(void*, int32_t *, struct OBX$Array$1);
    struct OBX$Array$1 (* $t2)(void*, int32_t *);
    void (* $t3)(void*, struct som$Interfaces$53de0d3f29$ForEachInterface *);
    t = 0;
    memset(&s,0,sizeof(s));
    memset(&it,0,sizeof(it));
    Tester$Test4$FI$init$(&it);
    t = som$RedBlackTree$4765cc5acb$create(Tester$Test4$intComp);
    OBX$StrCopy(&(struct OBX$Array$1){32,1,s},0,&((struct OBX$Array$1[1]){($t1 = ((struct som$RedBlackTree$4765cc5acb$RedBlackTree *)($t0 = &(*t)))->class$->put, $t1($t0, &(int32_t){10}, (const struct OBX$Array$1){11,0,OBX$FromUtf("Mandelbrot",11,0)}))})[0],0);
    OBX$StrCopy(&(struct OBX$Array$1){32,1,s},0,&((struct OBX$Array$1[1]){($t1 = ((struct som$RedBlackTree$4765cc5acb$RedBlackTree *)($t0 = &(*t)))->class$->put, $t1($t0, &(int32_t){3}, (const struct OBX$Array$1){6,0,OBX$FromUtf("Nbody",6,0)}))})[0],0);
    OBX$StrCopy(&(struct OBX$Array$1){32,1,s},0,&((struct OBX$Array$1[1]){($t1 = ((struct som$RedBlackTree$4765cc5acb$RedBlackTree *)($t0 = &(*t)))->class$->put, $t1($t0, &(int32_t){6}, (const struct OBX$Array$1){8,0,OBX$FromUtf("Permute",8,0)}))})[0],0);
    OBX$StrCopy(&(struct OBX$Array$1){32,1,s},0,&((struct OBX$Array$1[1]){($t1 = ((struct som$RedBlackTree$4765cc5acb$RedBlackTree *)($t0 = &(*t)))->class$->put, $t1($t0, &(int32_t){2}, (const struct OBX$Array$1){7,0,OBX$FromUtf("Queens",7,0)}))})[0],0);
    OBX$StrCopy(&(struct OBX$Array$1){32,1,s},0,&((struct OBX$Array$1[1]){($t1 = ((struct som$RedBlackTree$4765cc5acb$RedBlackTree *)($t0 = &(*t)))->class$->put, $t1($t0, &(int32_t){4}, (const struct OBX$Array$1){9,0,OBX$FromUtf("Richards",9,0)}))})[0],0);
    OBX$StrCopy(&(struct OBX$Array$1){32,1,s},0,&((struct OBX$Array$1[1]){($t1 = ((struct som$RedBlackTree$4765cc5acb$RedBlackTree *)($t0 = &(*t)))->class$->put, $t1($t0, &(int32_t){8}, (const struct OBX$Array$1){6,0,OBX$FromUtf("Sieve",6,0)}))})[0],0);
    OBX$StrCopy(&(struct OBX$Array$1){32,1,s},0,&((struct OBX$Array$1[1]){($t1 = ((struct som$RedBlackTree$4765cc5acb$RedBlackTree *)($t0 = &(*t)))->class$->put, $t1($t0, &(int32_t){11}, (const struct OBX$Array$1){8,0,OBX$FromUtf("Storage",8,0)}))})[0],0);
    OBX$StrCopy(&(struct OBX$Array$1){32,1,s},0,&((struct OBX$Array$1[1]){($t1 = ((struct som$RedBlackTree$4765cc5acb$RedBlackTree *)($t0 = &(*t)))->class$->put, $t1($t0, &(int32_t){9}, (const struct OBX$Array$1){6,0,OBX$FromUtf("Tower",6,0)}))})[0],0);
    OBX$StrCopy(&(struct OBX$Array$1){32,1,s},0,&((struct OBX$Array$1[1]){($t1 = ((struct som$RedBlackTree$4765cc5acb$RedBlackTree *)($t0 = &(*t)))->class$->put, $t1($t0, &(int32_t){3}, (const struct OBX$Array$1){5,0,OBX$FromUtf("Json",5,0)}))})[0],0);
    OBX$StrCopy(&(struct OBX$Array$1){32,1,s},0,&((struct OBX$Array$1[1]){($t2 = ((struct som$RedBlackTree$4765cc5acb$RedBlackTree *)($t0 = &(*t)))->class$->remove, $t2($t0, &(int32_t){11}))})[0],0);
    ;
    it.i = 33;
    ($t3 = ((struct som$RedBlackTree$4765cc5acb$RedBlackTree *)($t0 = &(*t)))->class$->forEach, $t3($t0, ((struct som$Interfaces$53de0d3f29$ForEachInterface *)&it)));
    OBX$PrintA(1,(const char*)((const struct OBX$Array$1){11,0,OBX$FromUtf("Done Test4",11,0)}).$a);
}

int32_t Tester$Test4$intComp(int32_t * lhs, int32_t * rhs) {
    if( ((*lhs) < (*rhs)) ) {
        return (-1);
    } else if( ((*lhs) > (*rhs)) ) {
        return 1;
    } else {
        return 0;
    }
    return 0;
}

void Tester$Test4$FI$apply(void* this, struct som$RedBlackTree$4765cc5acb$Entry * elem) {
    struct Tester$Test4$FI* this$ = this;
    Out$Int((*elem).key, 0);
    Out$String((const struct OBX$Array$1){2,0,OBX$FromUtf("=",2,0)});
    Out$String((struct OBX$Array$1){32,1,(*elem).value});
    Out$Ln();
}

void Tester$Test5() {
    struct som$RedBlackTree$0983872a44$RedBlackTree * t;
    struct Tester$Test5$FI it;
    struct CD$Vector2D point;
    struct som$Vector$e873043a5e$Vector * vec;
    void* $t0;
    void (* $t1)(void*, struct OBX$Array$1);
    struct som$Vector$e873043a5e$Vector * (* $t2)(void*, struct CD$Vector2D *, struct som$Vector$e873043a5e$Vector * *);
    void (* $t3)(void*, struct som$Interfaces$6b0df483d0$ForEachInterface *);
    t = 0;
    memset(&it,0,sizeof(it));
    Tester$Test5$FI$init$(&it);
    memset(&point,0,sizeof(point));
    CD$Vector2D$init$(&point);
    vec = 0;
    t = som$RedBlackTree$0983872a44$create(CD$compareVector2D);
    vec = som$Vector$e873043a5e$create();
    ($t1 = ((struct som$Vector$e873043a5e$Vector *)($t0 = &(*vec)))->class$->append, $t1($t0, (const struct OBX$Array$1){11,0,OBX$FromUtf("Mandelbrot",11,0)}));
    ($t1 = ((struct som$Vector$e873043a5e$Vector *)($t0 = &(*vec)))->class$->append, $t1($t0, (const struct OBX$Array$1){6,0,OBX$FromUtf("Nbody",6,0)}));
    ($t1 = ((struct som$Vector$e873043a5e$Vector *)($t0 = &(*vec)))->class$->append, $t1($t0, (const struct OBX$Array$1){8,0,OBX$FromUtf("Permute",8,0)}));
    point.x = 10;
    point.y = 20;
    vec = ($t2 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*t)))->class$->put, $t2($t0, &point, &vec));
    vec = som$Vector$e873043a5e$create();
    ($t1 = ((struct som$Vector$e873043a5e$Vector *)($t0 = &(*vec)))->class$->append, $t1($t0, (const struct OBX$Array$1){7,0,OBX$FromUtf("Queens",7,0)}));
    ($t1 = ((struct som$Vector$e873043a5e$Vector *)($t0 = &(*vec)))->class$->append, $t1($t0, (const struct OBX$Array$1){9,0,OBX$FromUtf("Richards",9,0)}));
    ($t1 = ((struct som$Vector$e873043a5e$Vector *)($t0 = &(*vec)))->class$->append, $t1($t0, (const struct OBX$Array$1){6,0,OBX$FromUtf("Sieve",6,0)}));
    point.x = 30;
    point.y = 40;
    vec = ($t2 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*t)))->class$->put, $t2($t0, &point, &vec));
    vec = som$Vector$e873043a5e$create();
    ($t1 = ((struct som$Vector$e873043a5e$Vector *)($t0 = &(*vec)))->class$->append, $t1($t0, (const struct OBX$Array$1){8,0,OBX$FromUtf("Storage",8,0)}));
    ($t1 = ((struct som$Vector$e873043a5e$Vector *)($t0 = &(*vec)))->class$->append, $t1($t0, (const struct OBX$Array$1){6,0,OBX$FromUtf("Tower",6,0)}));
    ($t1 = ((struct som$Vector$e873043a5e$Vector *)($t0 = &(*vec)))->class$->append, $t1($t0, (const struct OBX$Array$1){5,0,OBX$FromUtf("Json",5,0)}));
    point.x = 50;
    point.y = 60;
    vec = ($t2 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*t)))->class$->put, $t2($t0, &point, &vec));
    it.i = 33;
    ($t3 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*t)))->class$->forEach, $t3($t0, ((struct som$Interfaces$6b0df483d0$ForEachInterface *)&it)));
    OBX$PrintA(1,(const char*)((const struct OBX$Array$1){11,0,OBX$FromUtf("Done Test5",11,0)}).$a);
}

void Tester$Test5$FI$apply(void* this, struct som$RedBlackTree$0983872a44$Entry * elem) {
    struct Tester$Test5$FI* this$ = this;
    int32_t i;
    void* $t0;
    int32_t (* $t1)(void*);
    void* $t2;
    struct OBX$Array$1 (* $t3)(void*, int32_t);
    i = 0;
    Out$String((const struct OBX$Array$1){7,0,OBX$FromUtf("Point ",7,0)});
    Out$LongReal((*(struct CD$Vector2D *)&(*elem).key).x, 0);
    Out$String((const struct OBX$Array$1){2,0,OBX$FromUtf(":",2,0)});
    Out$LongReal((*(struct CD$Vector2D *)&(*elem).key).y, 0);
    Out$Ln();
    i = 0;
    while(1) {
        if( (i <= (($t1 = ((struct som$Vector$e873043a5e$Vector *)($t0 = &(*(*elem).value)))->class$->getSize, $t1($t0)) - 1)) ) {
            Out$String(($t3 = ((struct som$Vector$e873043a5e$Vector *)($t2 = &(*(*elem).value)))->class$->at, $t3($t2, i)));
            Out$Ln();
            i = (i + 1);
        } else {
            break;
        }
    }
}

void Tester$Test6() {
    struct CD2$Vector3D * vec1;
    struct CD2$Vector2D * vec2;
    struct CD2$Vector3D * $t0;
    vec1 = 0;
    vec2 = 0;
    ;
    $t0 = OBX$Alloc(sizeof(struct CD2$Vector3D));
    memset($t0,0,sizeof(struct CD2$Vector3D));
    vec1 = $t0;
    CD2$Vector3D$init$($t0);
    (*vec1).x = 1;
    (*vec1).y = 2;
    (*vec1).z = 3;
    vec2 = CD2$voxelHash(vec1);
    printf("%1.16e\n",(*vec2).x);
}

void Tester$RunAll() {
#if 0
    Harness$run((const struct OBX$Array$1){10,0,OBX$FromUtf("DeltaBlue",10,0)}, 12000, 1);
    Harness$run((const struct OBX$Array$1){9,0,OBX$FromUtf("Richards",9,0)}, 100, 1);
    Harness$run((const struct OBX$Array$1){5,0,OBX$FromUtf("Json",5,0)}, 100, 1);
    Harness$run((const struct OBX$Array$1){7,0,OBX$FromUtf("Havlak",7,0)}, 10, 1);
    Harness$run((const struct OBX$Array$1){4,0,OBX$FromUtf("CD2",4,0)}, 250, 2);
#endif
    Harness$run((const struct OBX$Array$1){7,0,OBX$FromUtf("Bounce",7,0)}, 1500, 1);
    Harness$run((const struct OBX$Array$1){5,0,OBX$FromUtf("List",5,0)}, 1500, 1);
    Harness$run((const struct OBX$Array$1){11,0,OBX$FromUtf("Mandelbrot",11,0)}, 500, 1);
    //Harness$run((const struct OBX$Array$1){6,0,OBX$FromUtf("NBody",6,0)}, 250000, 1);
    Harness$run((const struct OBX$Array$1){8,0,OBX$FromUtf("Permute",8,0)}, 1000, 1);
    Harness$run((const struct OBX$Array$1){7,0,OBX$FromUtf("Queens",7,0)}, 1000, 1);
    Harness$run((const struct OBX$Array$1){6,0,OBX$FromUtf("Sieve",6,0)}, 3000, 1);
    //Harness$run((const struct OBX$Array$1){8,0,OBX$FromUtf("Storage",8,0)}, 1000, 1);
    Harness$run((const struct OBX$Array$1){7,0,OBX$FromUtf("Towers",7,0)}, 600, 1);
}

void Tester$RunEachOnce() {
    Harness$run((const struct OBX$Array$1){10,0,OBX$FromUtf("DeltaBlue",10,0)}, 1, 1);
    Harness$run((const struct OBX$Array$1){9,0,OBX$FromUtf("Richards",9,0)}, 1, 1);
    Harness$run((const struct OBX$Array$1){5,0,OBX$FromUtf("Json",5,0)}, 1, 1);
    Harness$run((const struct OBX$Array$1){7,0,OBX$FromUtf("Havlak",7,0)}, 1, 1);
    Harness$run((const struct OBX$Array$1){4,0,OBX$FromUtf("CD2",4,0)}, 1, 2);
    Harness$run((const struct OBX$Array$1){7,0,OBX$FromUtf("Bounce",7,0)}, 1, 1);
    Harness$run((const struct OBX$Array$1){5,0,OBX$FromUtf("List",5,0)}, 1, 1);
    Harness$run((const struct OBX$Array$1){11,0,OBX$FromUtf("Mandelbrot",11,0)}, 1, 1);
    Harness$run((const struct OBX$Array$1){6,0,OBX$FromUtf("NBody",6,0)}, 1, 1);
    Harness$run((const struct OBX$Array$1){8,0,OBX$FromUtf("Permute",8,0)}, 1, 1);
    Harness$run((const struct OBX$Array$1){7,0,OBX$FromUtf("Queens",7,0)}, 1, 1);
    Harness$run((const struct OBX$Array$1){6,0,OBX$FromUtf("Sieve",6,0)}, 1, 1);
    Harness$run((const struct OBX$Array$1){8,0,OBX$FromUtf("Storage",8,0)}, 1, 1);
    Harness$run((const struct OBX$Array$1){7,0,OBX$FromUtf("Towers",7,0)}, 1, 1);
}

struct Tester$TestVector$Comparator$Class$ Tester$TestVector$Comparator$class$ = { 
    &som$Interfaces$04445da84e$Comparator$class$,
    Tester$TestVector$Comparator$compare,
};

struct Tester$Test4$FI$Class$ Tester$Test4$FI$class$ = { 
    &som$Interfaces$53de0d3f29$ForEachInterface$class$,
    Tester$Test4$FI$apply,
};

struct Tester$TestVector$Printer$Class$ Tester$TestVector$Printer$class$ = { 
    &som$Interfaces$04445da84e$ForEachInterface$class$,
    Tester$TestVector$Printer$apply,
};

struct Tester$Test5$FI$Class$ Tester$Test5$FI$class$ = { 
    &som$Interfaces$6b0df483d0$ForEachInterface$class$,
    Tester$Test5$FI$apply,
};

static int initDone$ = 0;
void Tester$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    som$Vector$04445da84e$init$();
    som$Interfaces$04445da84e$init$();
    Harness$init$();
    som$Random$init$();
    som$RedBlackTree$4765cc5acb$init$();
    som$Interfaces$53de0d3f29$init$();
    som$Vector$e873043a5e$init$();
    CD$init$();
    CD2$init$();
    som$RedBlackTree$0983872a44$init$();
    som$Interfaces$6b0df483d0$init$();
    Out$init$();
    memset(&Tester$str,0,sizeof(Tester$str));
    Tester$RunAll();
    //Tester$RunEachOnce();
    OBX$PrintA(1,(const char*)((const struct OBX$Array$1){11,0,OBX$FromUtf("End Tester",11,0)}).$a);
}
OBX$Cmd Tester$cmd$(const char* name) {
    if( name == 0 ) return Tester$init$;
    if( strcmp(name,"TestVector") == 0 ) return Tester$TestVector;
    if( strcmp(name,"Test2") == 0 ) return Tester$Test2;
    if( strcmp(name,"Test3") == 0 ) return Tester$Test3;
    if( strcmp(name,"Test4") == 0 ) return Tester$Test4;
    if( strcmp(name,"Test5") == 0 ) return Tester$Test5;
    if( strcmp(name,"Test6") == 0 ) return Tester$Test6;
    if( strcmp(name,"RunAll") == 0 ) return Tester$RunAll;
    if( strcmp(name,"RunEachOnce") == 0 ) return Tester$RunEachOnce;
    return 0;
}