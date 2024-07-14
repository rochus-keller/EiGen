// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "CD2.h"

void CD2$CollisionDetector$handleNewFrame$ForEachInterface$init$(struct CD2$CollisionDetector$handleNewFrame$ForEachInterface* inst){
    inst->class$ = &CD2$CollisionDetector$handleNewFrame$ForEachInterface$class$;
}
void CD2$Motion$init$(struct CD2$Motion* inst){
    inst->class$ = &CD2$Motion$class$;
}
void CD2$Simulator$init$(struct CD2$Simulator* inst){
    inst->class$ = &CD2$Simulator$class$;
}
void CD2$Aircraft$init$(struct CD2$Aircraft* inst){
    inst->class$ = &CD2$Aircraft$class$;
}
void CD2$Vector2D$init$(struct CD2$Vector2D* inst){
    inst->class$ = &CD2$Vector2D$class$;
}
void CD2$CallSign$init$(struct CD2$CallSign* inst){
    inst->class$ = &CD2$CallSign$class$;
}
void CD2$Collision$init$(struct CD2$Collision* inst){
    inst->class$ = &CD2$Collision$class$;
}
void CD2$CollisionDetector$init$(struct CD2$CollisionDetector* inst){
    inst->class$ = &CD2$CollisionDetector$class$;
}
void CD2$reduceCollisionSet$ForEachInterface$init$(struct CD2$reduceCollisionSet$ForEachInterface* inst){
    inst->class$ = &CD2$reduceCollisionSet$ForEachInterface$class$;
}
void CD2$CD$init$(struct CD2$CD* inst){
    inst->class$ = &CD2$CD$class$;
}
void CD2$Vector3D$init$(struct CD2$Vector3D* inst){
    inst->class$ = &CD2$Vector3D$class$;
}
struct CD2$Vector2D * CD2$horizontal = 0;
struct CD2$Vector2D * CD2$vertical = 0;
struct CD2$CD * CD2$create() {
    struct CD2$CD * c;
    struct CD2$CD * $t0;
    c = 0;
    $t0 = OBX$Alloc(sizeof(struct CD2$CD));
    memset($t0,0,sizeof(struct CD2$CD));
    c = $t0;
    CD2$CD$init$($t0);
    return c;
}

struct Benchmark$Result * CD2$CD$benchmark(void* this) {
    struct CD2$CD* this$ = this;
    assert(0);
    return 0;
}

uint8_t CD2$CD$verifyResult(void* this, struct Benchmark$Result * result) {
    struct CD2$CD* this$ = this;
    assert(0);
    return 0;
}

int32_t CD2$benchmark2(int32_t numAircrafts) {
    struct CD2$Simulator * simulator;
    struct CD2$CollisionDetector * detector;
    int32_t actualCollisions;
    int32_t i;
    double time;
    struct som$Vector$1c1b29cf70$Vector * collisions;
    void* $t0;
    struct som$Vector$1c1b29cf70$Vector * (* $t1)(void*, struct som$Vector$f13888695d$Vector *);
    void* $t2;
    struct som$Vector$f13888695d$Vector * (* $t3)(void*, double);
    int32_t (* $t4)(void*);
    simulator = 0;
    detector = 0;
    actualCollisions = 0;
    i = 0;
    time = 0;
    collisions = 0;
    simulator = CD2$createSimulator(numAircrafts);
    detector = CD2$createCD();
    actualCollisions = 0;
    i = 0;
    while(1) {
        if( (i <= (200 - 1)) ) {
            time = ((double)i / 1.0000000e+01);
            collisions = ($t1 = ((struct CD2$CollisionDetector *)($t0 = &(*detector)))->class$->handleNewFrame, $t1($t0, ($t3 = ((struct CD2$Simulator *)($t2 = &(*simulator)))->class$->simulate, $t3($t2, time))));
            actualCollisions = (actualCollisions + ($t4 = ((struct som$Vector$1c1b29cf70$Vector *)($t0 = &(*collisions)))->class$->getSize, $t4($t0)));
            i = (i + 1);
        } else {
            break;
        }
    }
    return actualCollisions;
}

uint8_t CD2$CD$innerBenchmarkLoop(void* this, int32_t innerIterations) {
    struct CD2$CD* this$ = this;
    if( (innerIterations < 2) ) {
        innerIterations = 2;
    } 
    return CD2$verifyResult2(CD2$benchmark2(innerIterations), innerIterations);
}

uint8_t CD2$verifyResult2(int32_t actualCollisions, int32_t numAircrafts) {
    if( (numAircrafts == 1000) ) {
        return (actualCollisions == 14484);
    } 
    if( (numAircrafts == 500) ) {
        return (actualCollisions == 14484);
    } 
    if( (numAircrafts == 250) ) {
        return (actualCollisions == 10830);
    } 
    if( (numAircrafts == 200) ) {
        return (actualCollisions == 8655);
    } 
    if( (numAircrafts == 100) ) {
        return (actualCollisions == 4305);
    } 
    if( (numAircrafts == 50) ) {
        return (actualCollisions == 2130);
    } 
    if( (numAircrafts == 10) ) {
        return (actualCollisions == 390);
    } 
    if( (numAircrafts == 2) ) {
        return (actualCollisions == 42);
    } 
    Out$String((const struct OBX$Array$1){28,0,OBX$FromUtf("No verification result for ",28,0)});
    Out$Int(numAircrafts, 0);
    Out$String((const struct OBX$Array$1){7,0,OBX$FromUtf(" found",7,0)});
    Out$Ln();
    Out$String((const struct OBX$Array$1){12,0,OBX$FromUtf("Result is: ",12,0)});
    Out$Int(actualCollisions, 0);
    Out$Ln();
    return 0;
}

struct CD2$Vector2D * CD2$Vector2D$plus(void* this, struct CD2$Vector2D * other) {
    struct CD2$Vector2D* this$ = this;
    struct CD2$Vector2D * res;
    struct CD2$Vector2D * $t0;
    res = 0;
    $t0 = OBX$Alloc(sizeof(struct CD2$Vector2D));
    memset($t0,0,sizeof(struct CD2$Vector2D));
    res = $t0;
    CD2$Vector2D$init$($t0);
    (*res).x = ((*this$).x + (*other).x);
    (*res).y = ((*this$).y + (*other).y);
    return res;
}

struct CD2$Vector2D * CD2$Vector2D$minus(void* this, struct CD2$Vector2D * other) {
    struct CD2$Vector2D* this$ = this;
    struct CD2$Vector2D * res;
    struct CD2$Vector2D * $t0;
    res = 0;
    $t0 = OBX$Alloc(sizeof(struct CD2$Vector2D));
    memset($t0,0,sizeof(struct CD2$Vector2D));
    res = $t0;
    CD2$Vector2D$init$($t0);
    (*res).x = ((*this$).x - (*other).x);
    (*res).y = ((*this$).y - (*other).y);
    return res;
}

int32_t CD2$compareVector2D(struct CD2$Vector2D * * lhs, struct CD2$Vector2D * * rhs) {
    int32_t result;
    result = 0;
    result = CD2$compareNumbers((*(*lhs)).x, (*(*rhs)).x);
    if( (result != 0) ) {
        return result;
    } 
    return CD2$compareNumbers((*(*lhs)).y, (*(*rhs)).y);
}

int32_t CD2$compareNumbers(double a, double b) {
    if( (a == b) ) {
        return 0;
    } 
    if( (a < b) ) {
        return (-1);
    } 
    if( (a > b) ) {
        return 1;
    } 
    if( (a == a) ) {
        return 1;
    } 
    return (-1);
}

struct CD2$Vector3D * CD2$Vector3D$plus(void* this, struct CD2$Vector3D * other) {
    struct CD2$Vector3D* this$ = this;
    struct CD2$Vector3D * res;
    struct CD2$Vector3D * $t0;
    res = 0;
    $t0 = OBX$Alloc(sizeof(struct CD2$Vector3D));
    memset($t0,0,sizeof(struct CD2$Vector3D));
    res = $t0;
    CD2$Vector3D$init$($t0);
    (*res).x = ((*this$).x + (*other).x);
    (*res).y = ((*this$).y + (*other).y);
    (*res).z = ((*this$).z + (*other).z);
    return res;
}

struct CD2$Vector3D * CD2$Vector3D$minus(void* this, struct CD2$Vector3D * other) {
    struct CD2$Vector3D* this$ = this;
    struct CD2$Vector3D * res;
    struct CD2$Vector3D * $t0;
    res = 0;
    $t0 = OBX$Alloc(sizeof(struct CD2$Vector3D));
    memset($t0,0,sizeof(struct CD2$Vector3D));
    res = $t0;
    CD2$Vector3D$init$($t0);
    (*res).x = ((*this$).x - (*other).x);
    (*res).y = ((*this$).y - (*other).y);
    (*res).z = ((*this$).z - (*other).z);
    return res;
}

struct CD2$Vector3D * CD2$Vector3D$times(void* this, double amount) {
    struct CD2$Vector3D* this$ = this;
    struct CD2$Vector3D * res;
    struct CD2$Vector3D * $t0;
    res = 0;
    $t0 = OBX$Alloc(sizeof(struct CD2$Vector3D));
    memset($t0,0,sizeof(struct CD2$Vector3D));
    res = $t0;
    CD2$Vector3D$init$($t0);
    (*res).x = ((*this$).x * amount);
    (*res).y = ((*this$).y * amount);
    (*res).z = ((*this$).z * amount);
    return res;
}

double CD2$Vector3D$dot(void* this, struct CD2$Vector3D * other) {
    struct CD2$Vector3D* this$ = this;
    return ((((*this$).x * (*other).x) + ((*this$).y * (*other).y)) + ((*this$).z * (*other).z));
}

double CD2$Vector3D$squaredMagnitude(void* this) {
    struct CD2$Vector3D* this$ = this;
    void* $t0;
    double (* $t1)(void*, struct CD2$Vector3D *);
    return ($t1 = ((struct CD2$Vector3D *)($t0 = &(*this$)))->class$->dot, $t1($t0, this$));
}

double CD2$Vector3D$magnitude(void* this) {
    struct CD2$Vector3D* this$ = this;
    void* $t0;
    double (* $t1)(void*);
    return Math$sqrt(($t1 = ((struct CD2$Vector3D *)($t0 = &(*this$)))->class$->squaredMagnitude, $t1($t0)));
}

int32_t CD2$compareCallSign(struct CD2$CallSign * * lhs, struct CD2$CallSign * * rhs) {
    if( ((*(*lhs)).value == (*(*rhs)).value) ) {
        return 0;
    } else if( ((*(*lhs)).value < (*(*rhs)).value) ) {
        return (-1);
    } else {
        return 1;
    }
    return 0;
}

struct CD2$Collision * CD2$createCollision(struct CD2$CallSign * aircraftA, struct CD2$CallSign * aircraftB, struct CD2$Vector3D * position) {
    struct CD2$Collision * res;
    struct CD2$Collision * $t0;
    res = 0;
    $t0 = OBX$Alloc(sizeof(struct CD2$Collision));
    memset($t0,0,sizeof(struct CD2$Collision));
    res = $t0;
    CD2$Collision$init$($t0);
    (*res).aircraftA = aircraftA;
    (*res).aircraftB = aircraftB;
    (*res).position = position;
    return res;
}

struct CD2$Simulator * CD2$createSimulator(int32_t numAircraft) {
    struct CD2$Simulator * sim;
    int32_t i;
    struct CD2$CallSign * cs;
    struct CD2$Simulator * $t0;
    struct CD2$CallSign * $t1;
    void* $t2;
    void (* $t3)(void*, struct CD2$CallSign * *);
    sim = 0;
    i = 0;
    cs = 0;
    $t0 = OBX$Alloc(sizeof(struct CD2$Simulator));
    memset($t0,0,sizeof(struct CD2$Simulator));
    sim = $t0;
    CD2$Simulator$init$($t0);
    (*sim).aircraft = som$Vector$03bc1d2b30$create();
    i = 0;
    while(1) {
        if( (i <= (numAircraft - 1)) ) {
            $t1 = OBX$Alloc(sizeof(struct CD2$CallSign));
            memset($t1,0,sizeof(struct CD2$CallSign));
            cs = $t1;
            CD2$CallSign$init$($t1);
            (*cs).value = i;
            ($t3 = ((struct som$Vector$03bc1d2b30$Vector *)($t2 = &(*(*sim).aircraft)))->class$->append, $t3($t2, &cs));
            i = (i + 1);
        } else {
            break;
        }
    }
    return sim;
}

struct som$Vector$f13888695d$Vector * CD2$Simulator$simulate(void* this, double time) {
    struct CD2$Simulator* this$ = this;
    struct som$Vector$f13888695d$Vector * frame;
    int32_t i;
    struct CD2$Aircraft * ac;
    void* $t0;
    int32_t (* $t1)(void*);
    struct CD2$Aircraft * $t2;
    struct CD2$Vector3D * $t3;
    struct CD2$CallSign * (* $t4)(void*, int32_t);
    void (* $t5)(void*, struct CD2$Aircraft * *);
    frame = 0;
    i = 0;
    ac = 0;
    frame = som$Vector$f13888695d$create();
    i = 0;
    while(1) {
        if( (i <= (($t1 = ((struct som$Vector$03bc1d2b30$Vector *)($t0 = &(*(*this$).aircraft)))->class$->getSize, $t1($t0)) - 1)) ) {
            $t2 = OBX$Alloc(sizeof(struct CD2$Aircraft));
            memset($t2,0,sizeof(struct CD2$Aircraft));
            ac = $t2;
            CD2$Aircraft$init$($t2);
            $t3 = OBX$Alloc(sizeof(struct CD2$Vector3D));
            memset($t3,0,sizeof(struct CD2$Vector3D));
            (*ac).position = $t3;
            CD2$Vector3D$init$($t3);
            (*ac).callsign = ($t4 = ((struct som$Vector$03bc1d2b30$Vector *)($t0 = &(*(*this$).aircraft)))->class$->at, $t4($t0, i));
            (*(*ac).position).x = time;
            (*(*ac).position).y = ((Math$cos(time) * 2.0000000e+00) + ((double)i * 3.0000000e+00));
            (*(*ac).position).z = 10;
            ($t5 = ((struct som$Vector$f13888695d$Vector *)($t0 = &(*frame)))->class$->append, $t5($t0, &ac));
            $t2 = OBX$Alloc(sizeof(struct CD2$Aircraft));
            memset($t2,0,sizeof(struct CD2$Aircraft));
            ac = $t2;
            CD2$Aircraft$init$($t2);
            $t3 = OBX$Alloc(sizeof(struct CD2$Vector3D));
            memset($t3,0,sizeof(struct CD2$Vector3D));
            (*ac).position = $t3;
            CD2$Vector3D$init$($t3);
            (*ac).callsign = ($t4 = ((struct som$Vector$03bc1d2b30$Vector *)($t0 = &(*(*this$).aircraft)))->class$->at, $t4($t0, (i + 1)));
            (*(*ac).position).x = time;
            (*(*ac).position).y = ((Math$sin(time) * 2.0000000e+00) + ((double)i * 3.0000000e+00));
            (*(*ac).position).z = 10;
            ($t5 = ((struct som$Vector$f13888695d$Vector *)($t0 = &(*frame)))->class$->append, $t5($t0, &ac));
            i = (i + 2);
        } else {
            break;
        }
    }
    return frame;
}

struct CD2$Motion * CD2$createMotion(struct CD2$CallSign * * callsign, struct CD2$Vector3D * posOne, struct CD2$Vector3D * posTwo) {
    struct CD2$Motion * m;
    struct CD2$Motion * $t0;
    m = 0;
    $t0 = OBX$Alloc(sizeof(struct CD2$Motion));
    memset($t0,0,sizeof(struct CD2$Motion));
    m = $t0;
    CD2$Motion$init$($t0);
    (*m).callsign = (*callsign);
    (*m).posOne = posOne;
    (*m).posTwo = posTwo;
    return m;
}

struct CD2$Vector3D * CD2$Motion$delta(void* this) {
    struct CD2$Motion* this$ = this;
    void* $t0;
    struct CD2$Vector3D * (* $t1)(void*, struct CD2$Vector3D *);
    return ($t1 = ((struct CD2$Vector3D *)($t0 = &(*(*this$).posTwo)))->class$->minus, $t1($t0, (*this$).posOne));
}

struct CD2$Vector3D * CD2$Motion$findIntersection(void* this, struct CD2$Motion * other) {
    struct CD2$Motion* this$ = this;
    struct CD2$Vector3D * init1;
    struct CD2$Vector3D * init2;
    struct CD2$Vector3D * vec1;
    struct CD2$Vector3D * vec2;
    struct CD2$Vector3D * result1;
    struct CD2$Vector3D * result2;
    struct CD2$Vector3D * result;
    double radius;
    double a;
    double b;
    double c;
    double discr;
    double v;
    double v1;
    double v2;
    double dist;
    void* $t0;
    struct CD2$Vector3D * (* $t1)(void*);
    double (* $t2)(void*);
    void* $t3;
    struct CD2$Vector3D * (* $t4)(void*, struct CD2$Vector3D *);
    double (* $t5)(void*, struct CD2$Vector3D *);
    void* $t6;
    struct CD2$Vector3D * (* $t7)(void*, struct CD2$Vector3D *);
    struct CD2$Vector3D * (* $t8)(void*, double);
    init1 = 0;
    init2 = 0;
    vec1 = 0;
    vec2 = 0;
    result1 = 0;
    result2 = 0;
    result = 0;
    radius = 0;
    a = 0;
    b = 0;
    c = 0;
    discr = 0;
    v = 0;
    v1 = 0;
    v2 = 0;
    dist = 0;
    init1 = (*this$).posOne;
    init2 = (*other).posOne;
    vec1 = ($t1 = ((struct CD2$Motion *)($t0 = &(*this$)))->class$->delta, $t1($t0));
    vec2 = ($t1 = ((struct CD2$Motion *)($t0 = &(*other)))->class$->delta, $t1($t0));
    radius = 1.0000000e+00;
    a = ($t2 = ((struct CD2$Vector3D *)($t0 = &(*($t4 = ((struct CD2$Vector3D *)($t3 = &(*vec2)))->class$->minus, $t4($t3, vec1)))))->class$->squaredMagnitude, $t2($t0));
    if( (a != 0.0000000e+00) ) {
        b = (2.0000000e+00 * ($t5 = ((struct CD2$Vector3D *)($t0 = &(*($t4 = ((struct CD2$Vector3D *)($t3 = &(*init1)))->class$->minus, $t4($t3, init2)))))->class$->dot, $t5($t0, ($t7 = ((struct CD2$Vector3D *)($t6 = &(*vec1)))->class$->minus, $t7($t6, vec2)))));
        c = ((-(radius * radius)) + ($t2 = ((struct CD2$Vector3D *)($t0 = &(*($t4 = ((struct CD2$Vector3D *)($t3 = &(*init2)))->class$->minus, $t4($t3, init1)))))->class$->squaredMagnitude, $t2($t0)));
        discr = ((b * b) - ((4.0000000e+00 * a) * c));
        if( (discr < 0.0000000e+00) ) {
            return 0;
        } 
        v1 = (((-b) - Math$sqrt(discr)) / (2.0000000e+00 * a));
        v2 = (((-b) + Math$sqrt(discr)) / (2.0000000e+00 * a));
        if( ((v1 <= v2) && ((((v1 <= 1.0000000e+00) && (1.0000000e+00 <= v2)) || ((v1 <= 0.0000000e+00) && (0.0000000e+00 <= v2))) || ((0.0000000e+00 <= v1) && (v2 <= 1.0000000e+00)))) ) {
            if( (v1 <= 0.0000000e+00) ) {
                v = 0.0000000e+00;
            } else {
                v = v1;
            }
            result1 = ($t4 = ((struct CD2$Vector3D *)($t0 = &(*init1)))->class$->plus, $t4($t0, ($t8 = ((struct CD2$Vector3D *)($t3 = &(*vec1)))->class$->times, $t8($t3, v))));
            result2 = ($t4 = ((struct CD2$Vector3D *)($t0 = &(*init2)))->class$->plus, $t4($t0, ($t8 = ((struct CD2$Vector3D *)($t3 = &(*vec2)))->class$->times, $t8($t3, v))));
            result = ($t8 = ((struct CD2$Vector3D *)($t0 = &(*($t4 = ((struct CD2$Vector3D *)($t3 = &(*result1)))->class$->plus, $t4($t3, result2)))))->class$->times, $t8($t0, 5.0000000e-01));
            if( (((((((*result).x >= 0.0000000e+00) && ((*result).x <= 1.0000000e+03)) && ((*result).y >= 0.0000000e+00)) && ((*result).y <= 1.0000000e+03)) && ((*result).z >= 0.0000000e+00)) && ((*result).z <= 1.0000000e+01)) ) {
                return result;
            } 
        } 
        return 0;
    } 
    dist = ($t2 = ((struct CD2$Vector3D *)($t0 = &(*($t4 = ((struct CD2$Vector3D *)($t3 = &(*init2)))->class$->minus, $t4($t3, init1)))))->class$->magnitude, $t2($t0));
    if( (dist <= radius) ) {
        return ($t8 = ((struct CD2$Vector3D *)($t0 = &(*($t4 = ((struct CD2$Vector3D *)($t3 = &(*init1)))->class$->plus, $t4($t3, init2)))))->class$->times, $t8($t0, 5.0000000e-01));
    } 
    return 0;
}

struct CD2$CollisionDetector * CD2$createCD() {
    struct CD2$CollisionDetector * cd;
    struct CD2$CollisionDetector * $t0;
    cd = 0;
    $t0 = OBX$Alloc(sizeof(struct CD2$CollisionDetector));
    memset($t0,0,sizeof(struct CD2$CollisionDetector));
    cd = $t0;
    CD2$CollisionDetector$init$($t0);
    (*cd).state = som$RedBlackTree$1a37460855$create(CD2$compareCallSign);
    return cd;
}

struct som$Vector$1c1b29cf70$Vector * CD2$CollisionDetector$handleNewFrame(void* this, struct som$Vector$f13888695d$Vector * frame) {
    struct CD2$CollisionDetector* this$ = this;
    struct som$Vector$d424285281$Vector * motions;
    struct som$RedBlackTree$baea382c58$RedBlackTree * seen;
    int32_t i;
    int32_t j;
    int32_t k;
    struct CD2$Aircraft * aircraft;
    struct CD2$Vector3D * oldPosition;
    struct CD2$Vector3D * newPosition;
    struct som$Vector$03bc1d2b30$Vector * toRemove;
    struct som$Vector$1c1b29cf70$Vector * collisions;
    uint8_t dummy;
    struct CD2$Vector3D * dummy2;
    struct CD2$CollisionDetector$handleNewFrame$ForEachInterface it;
    struct som$Vector$3765c927e5$Vector * allReduced;
    struct som$Vector$d424285281$Vector * reduced;
    struct CD2$Motion * motion1;
    struct CD2$Motion * motion2;
    struct CD2$Vector3D * collision;
    void* $t0;
    int32_t (* $t1)(void*);
    void* $t2;
    struct CD2$Aircraft * (* $t3)(void*, int32_t);
    struct CD2$Vector3D * (* $t4)(void*, struct CD2$CallSign * *, struct CD2$Vector3D * *);
    uint8_t (* $t5)(void*, struct CD2$CallSign * *, uint8_t *);
    void (* $t6)(void*, struct CD2$Motion * *);
    void (* $t7)(void*, struct som$Interfaces$57f847cd33$ForEachInterface *);
    struct CD2$Vector3D * (* $t8)(void*, struct CD2$CallSign * *);
    void* $t9;
    struct CD2$CallSign * (* $t10)(void*, int32_t);
    struct som$Vector$d424285281$Vector * (* $t11)(void*, int32_t);
    struct CD2$Motion * (* $t12)(void*, int32_t);
    struct CD2$Vector3D * (* $t13)(void*, struct CD2$Motion *);
    void (* $t14)(void*, struct CD2$Collision * *);
    motions = 0;
    seen = 0;
    i = 0;
    j = 0;
    k = 0;
    aircraft = 0;
    oldPosition = 0;
    newPosition = 0;
    toRemove = 0;
    collisions = 0;
    dummy = 0;
    dummy2 = 0;
    memset(&it,0,sizeof(it));
    CD2$CollisionDetector$handleNewFrame$ForEachInterface$init$(&it);
    allReduced = 0;
    reduced = 0;
    motion1 = 0;
    motion2 = 0;
    collision = 0;
    motions = som$Vector$d424285281$create();
    seen = som$RedBlackTree$baea382c58$create(CD2$compareCallSign);
    i = 0;
    while(1) {
        if( (i <= (($t1 = ((struct som$Vector$f13888695d$Vector *)($t0 = &(*frame)))->class$->getSize, $t1($t0)) - 1)) ) {
            aircraft = ($t3 = ((struct som$Vector$f13888695d$Vector *)($t2 = &(*frame)))->class$->at, $t3($t2, i));
            oldPosition = ($t4 = ((struct som$RedBlackTree$1a37460855$RedBlackTree *)($t0 = &(*(*this$).state)))->class$->put, $t4($t0, &(*aircraft).callsign, &(*aircraft).position));
            newPosition = (*aircraft).position;
            dummy = ($t5 = ((struct som$RedBlackTree$baea382c58$RedBlackTree *)($t0 = &(*seen)))->class$->put, $t5($t0, &(*aircraft).callsign, &(uint8_t){1}));
            if( ((void*)oldPosition == (void*)0) ) {
                oldPosition = newPosition;
            } 
            ($t6 = ((struct som$Vector$d424285281$Vector *)($t0 = &(*motions)))->class$->append, $t6($t0, &((struct CD2$Motion *[1]){CD2$createMotion(&(*aircraft).callsign, oldPosition, newPosition)})[0]));
            i = (i + 1);
        } else {
            break;
        }
    }
    toRemove = som$Vector$03bc1d2b30$create();
    it.toRemove = toRemove;
    it.seen = seen;
    ($t7 = ((struct som$RedBlackTree$1a37460855$RedBlackTree *)($t0 = &(*(*this$).state)))->class$->forEach, $t7($t0, ((struct som$Interfaces$57f847cd33$ForEachInterface *)&it)));
    i = 0;
    while(1) {
        if( (i <= (($t1 = ((struct som$Vector$03bc1d2b30$Vector *)($t0 = &(*toRemove)))->class$->getSize, $t1($t0)) - 1)) ) {
            dummy2 = ($t8 = ((struct som$RedBlackTree$1a37460855$RedBlackTree *)($t2 = &(*(*this$).state)))->class$->remove, $t8($t2, &((struct CD2$CallSign *[1]){($t10 = ((struct som$Vector$03bc1d2b30$Vector *)($t9 = &(*toRemove)))->class$->at, $t10($t9, i))})[0]));
            i = (i + 1);
        } else {
            break;
        }
    }
    allReduced = CD2$reduceCollisionSet(motions);
    collisions = som$Vector$1c1b29cf70$create();
    k = 0;
    while(1) {
        if( (k <= (($t1 = ((struct som$Vector$3765c927e5$Vector *)($t0 = &(*allReduced)))->class$->getSize, $t1($t0)) - 1)) ) {
            reduced = ($t11 = ((struct som$Vector$3765c927e5$Vector *)($t2 = &(*allReduced)))->class$->at, $t11($t2, k));
            i = 0;
            while(1) {
                if( (i <= (($t1 = ((struct som$Vector$d424285281$Vector *)($t0 = &(*reduced)))->class$->getSize, $t1($t0)) - 1)) ) {
                    motion1 = ($t12 = ((struct som$Vector$d424285281$Vector *)($t2 = &(*reduced)))->class$->at, $t12($t2, i));
                    j = (i + 1);
                    while(1) {
                        if( (j <= (($t1 = ((struct som$Vector$d424285281$Vector *)($t0 = &(*reduced)))->class$->getSize, $t1($t0)) - 1)) ) {
                            motion2 = ($t12 = ((struct som$Vector$d424285281$Vector *)($t2 = &(*reduced)))->class$->at, $t12($t2, j));
                            collision = ($t13 = ((struct CD2$Motion *)($t0 = &(*motion1)))->class$->findIntersection, $t13($t0, motion2));
                            if( ((void*)collision != (void*)0) ) {
                                ($t14 = ((struct som$Vector$1c1b29cf70$Vector *)($t0 = &(*collisions)))->class$->append, $t14($t0, &((struct CD2$Collision *[1]){CD2$createCollision((*motion1).callsign, (*motion2).callsign, collision)})[0]));
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
            k = (k + 1);
        } else {
            break;
        }
    }
    return collisions;
}

void CD2$CollisionDetector$handleNewFrame$ForEachInterface$apply(void* this, struct som$RedBlackTree$1a37460855$Entry * elem) {
    struct CD2$CollisionDetector$handleNewFrame$ForEachInterface* this$ = this;
    void* $t0;
    uint8_t (* $t1)(void*, struct CD2$CallSign * *);
    void* $t2;
    void (* $t3)(void*, struct CD2$CallSign * *);
    if( (!($t1 = ((struct som$RedBlackTree$baea382c58$RedBlackTree *)($t0 = &(*(*this$).seen)))->class$->get, $t1($t0, &(*elem).key))) ) {
        ($t3 = ((struct som$Vector$03bc1d2b30$Vector *)($t2 = &(*(*this$).toRemove)))->class$->append, $t3($t2, &(*elem).key));
    } 
}

uint8_t CD2$isInVoxel(struct CD2$Vector2D * voxel, struct CD2$Motion * motion) {
    struct CD2$Vector3D * init;
    struct CD2$Vector3D * fin;
    double v_s;
    double r;
    double v_x;
    double x0;
    double xv;
    double v_y;
    double y0;
    double yv;
    double low_x;
    double high_x;
    double tmp;
    double low_y;
    double high_y;
    init = 0;
    fin = 0;
    v_s = 0;
    r = 0;
    v_x = 0;
    x0 = 0;
    xv = 0;
    v_y = 0;
    y0 = 0;
    yv = 0;
    low_x = 0;
    high_x = 0;
    tmp = 0;
    low_y = 0;
    high_y = 0;
    if( (((((*voxel).x > 1.0000000e+03) || ((*voxel).x < 0.0000000e+00)) || ((*voxel).y > 1.0000000e+03)) || ((*voxel).y < 0.0000000e+00)) ) {
        return 0;
    } 
    init = (*motion).posOne;
    fin = (*motion).posTwo;
    v_s = 2.0000000e+00;
    r = (1.0000000e+00 / 2.0000000e+00);
    v_x = (*voxel).x;
    x0 = (*init).x;
    xv = ((*fin).x - (*init).x);
    v_y = (*voxel).y;
    y0 = (*init).y;
    yv = ((*fin).y - (*init).y);
    low_x = (((v_x - r) - x0) / xv);
    high_x = ((((v_x + v_s) + r) - x0) / xv);
    if( (xv < 0.0000000e+00) ) {
        tmp = low_x;
        low_x = high_x;
        high_x = tmp;
    } 
    low_y = (((v_y - r) - y0) / yv);
    high_y = ((((v_y + v_s) + r) - y0) / yv);
    if( (yv < 0.0000000e+00) ) {
        tmp = low_y;
        low_y = high_y;
        high_y = tmp;
    } 
    return ((((((((xv == 0.0000000e+00) && (v_x <= (x0 + r))) && ((x0 - r) <= (v_x + v_s))) || ((low_x <= 1.0000000e+00) && (1.0000000e+00 <= high_x))) || ((low_x <= 0.0000000e+00) && (0.0000000e+00 <= high_x))) || ((0.0000000e+00 <= low_x) && (high_x <= 1.0000000e+00))) && ((((yv == 0.0000000e+00) && (v_y <= (y0 + r))) && ((y0 - r) <= (v_y + v_s))) || ((((low_y <= 1.0000000e+00) && (1.0000000e+00 <= high_y)) || ((low_y <= 0.0000000e+00) && (0.0000000e+00 <= high_y))) || ((0.0000000e+00 <= low_y) && (high_y <= 1.0000000e+00))))) && (((((xv == 0.0000000e+00) || (yv == 0.0000000e+00)) || ((low_y <= high_x) && (high_x <= high_y))) || ((low_y <= low_x) && (low_x <= high_y))) || ((low_x <= low_y) && (high_y <= high_x))));
}

void CD2$putIntoMap(struct som$RedBlackTree$c4a1631837$RedBlackTree * voxelMap, struct CD2$Vector2D * voxel, struct CD2$Motion * motion) {
    struct som$Vector$d424285281$Vector * arr;
    struct som$Vector$d424285281$Vector * dummy;
    void* $t0;
    struct som$Vector$d424285281$Vector * (* $t1)(void*, struct CD2$Vector2D * *);
    struct som$Vector$d424285281$Vector * (* $t2)(void*, struct CD2$Vector2D * *, struct som$Vector$d424285281$Vector * *);
    void (* $t3)(void*, struct CD2$Motion * *);
    arr = 0;
    dummy = 0;
    arr = ($t1 = ((struct som$RedBlackTree$c4a1631837$RedBlackTree *)($t0 = &(*voxelMap)))->class$->get, $t1($t0, &voxel));
    if( ((void*)arr == (void*)0) ) {
        arr = som$Vector$d424285281$create();
        dummy = ($t2 = ((struct som$RedBlackTree$c4a1631837$RedBlackTree *)($t0 = &(*voxelMap)))->class$->put, $t2($t0, &voxel, &arr));
    } 
    ($t3 = ((struct som$Vector$d424285281$Vector *)($t0 = &(*arr)))->class$->append, $t3($t0, &motion));
}

struct som$Vector$3765c927e5$Vector * CD2$reduceCollisionSet(struct som$Vector$d424285281$Vector * motions) {
    struct som$RedBlackTree$c4a1631837$RedBlackTree * voxelMap;
    struct som$Vector$3765c927e5$Vector * result;
    int32_t i;
    struct CD2$reduceCollisionSet$ForEachInterface it;
    void* $t0;
    int32_t (* $t1)(void*);
    void* $t2;
    struct CD2$Motion * (* $t3)(void*, int32_t);
    void (* $t4)(void*, struct som$Interfaces$017cf6702e$ForEachInterface *);
    voxelMap = 0;
    result = 0;
    i = 0;
    memset(&it,0,sizeof(it));
    CD2$reduceCollisionSet$ForEachInterface$init$(&it);
    voxelMap = som$RedBlackTree$c4a1631837$create(CD2$compareVector2D);
    i = 0;
    while(1) {
        if( (i <= (($t1 = ((struct som$Vector$d424285281$Vector *)($t0 = &(*motions)))->class$->getSize, $t1($t0)) - 1)) ) {
            CD2$drawMotionOnVoxelMap(voxelMap, ($t3 = ((struct som$Vector$d424285281$Vector *)($t2 = &(*motions)))->class$->at, $t3($t2, i)));
            i = (i + 1);
        } else {
            break;
        }
    }
    result = som$Vector$3765c927e5$create();
    it.result = result;
    ($t4 = ((struct som$RedBlackTree$c4a1631837$RedBlackTree *)($t0 = &(*voxelMap)))->class$->forEach, $t4($t0, ((struct som$Interfaces$017cf6702e$ForEachInterface *)&it)));
    return result;
}

void CD2$reduceCollisionSet$ForEachInterface$apply(void* this, struct som$RedBlackTree$c4a1631837$Entry * elem) {
    struct CD2$reduceCollisionSet$ForEachInterface* this$ = this;
    void* $t0;
    int32_t (* $t1)(void*);
    void* $t2;
    void (* $t3)(void*, struct som$Vector$d424285281$Vector * *);
    if( (($t1 = ((struct som$Vector$d424285281$Vector *)($t0 = &(*(*elem).value)))->class$->getSize, $t1($t0)) > 1) ) {
        ($t3 = ((struct som$Vector$3765c927e5$Vector *)($t2 = &(*(*this$).result)))->class$->append, $t3($t2, &(*elem).value));
    } 
}

void CD2$recurse(struct som$RedBlackTree$c4a1631837$RedBlackTree * voxelMap, struct som$RedBlackTree$9e53bca141$RedBlackTree * seen, struct CD2$Vector2D * nextVoxel, struct CD2$Motion * motion) {
    void* $t0;
    uint8_t (* $t1)(void*, struct CD2$Vector2D * *, uint8_t *);
    struct CD2$Vector2D * (* $t2)(void*, struct CD2$Vector2D *);
    void* $t3;
    struct CD2$Vector2D * (* $t4)(void*, struct CD2$Vector2D *);
    if( (!CD2$isInVoxel(nextVoxel, motion)) ) {
        return ;
    } 
    if( ($t1 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*seen)))->class$->put, $t1($t0, &nextVoxel, &(uint8_t){1})) ) {
        return ;
    } 
    CD2$putIntoMap(voxelMap, nextVoxel, motion);
    CD2$recurse(voxelMap, seen, ($t2 = ((struct CD2$Vector2D *)($t0 = &(*nextVoxel)))->class$->minus, $t2($t0, CD2$horizontal)), motion);
    CD2$recurse(voxelMap, seen, ($t2 = ((struct CD2$Vector2D *)($t0 = &(*nextVoxel)))->class$->plus, $t2($t0, CD2$horizontal)), motion);
    CD2$recurse(voxelMap, seen, ($t2 = ((struct CD2$Vector2D *)($t0 = &(*nextVoxel)))->class$->minus, $t2($t0, CD2$vertical)), motion);
    CD2$recurse(voxelMap, seen, ($t2 = ((struct CD2$Vector2D *)($t0 = &(*nextVoxel)))->class$->plus, $t2($t0, CD2$vertical)), motion);
    CD2$recurse(voxelMap, seen, ($t2 = ((struct CD2$Vector2D *)($t0 = &(*($t4 = ((struct CD2$Vector2D *)($t3 = &(*nextVoxel)))->class$->minus, $t4($t3, CD2$horizontal)))))->class$->minus, $t2($t0, CD2$vertical)), motion);
    CD2$recurse(voxelMap, seen, ($t2 = ((struct CD2$Vector2D *)($t0 = &(*($t4 = ((struct CD2$Vector2D *)($t3 = &(*nextVoxel)))->class$->minus, $t4($t3, CD2$horizontal)))))->class$->plus, $t2($t0, CD2$vertical)), motion);
    CD2$recurse(voxelMap, seen, ($t2 = ((struct CD2$Vector2D *)($t0 = &(*($t4 = ((struct CD2$Vector2D *)($t3 = &(*nextVoxel)))->class$->plus, $t4($t3, CD2$horizontal)))))->class$->minus, $t2($t0, CD2$vertical)), motion);
    CD2$recurse(voxelMap, seen, ($t2 = ((struct CD2$Vector2D *)($t0 = &(*($t4 = ((struct CD2$Vector2D *)($t3 = &(*nextVoxel)))->class$->plus, $t4($t3, CD2$horizontal)))))->class$->plus, $t2($t0, CD2$vertical)), motion);
}

struct CD2$Vector2D * CD2$voxelHash(struct CD2$Vector3D * position) {
    int32_t xDiv;
    int32_t yDiv;
    double x;
    double y;
    struct CD2$Vector2D * res;
    struct CD2$Vector2D * $t0;
    xDiv = 0;
    yDiv = 0;
    x = 0;
    y = 0;
    res = 0;
    xDiv = (int64_t)floor(((*position).x / 2.0000000e+00));
    yDiv = (int64_t)floor(((*position).y / 2.0000000e+00));
    x = (2.0000000e+00 * (double)xDiv);
    y = (2.0000000e+00 * (double)yDiv);
    if( ((*position).x < 0.0000000e+00) ) {
        x = (x - 2.0000000e+00);
    } 
    if( ((*position).y < 0.0000000e+00) ) {
        y = (y - 2.0000000e+00);
    } 
    $t0 = OBX$Alloc(sizeof(struct CD2$Vector2D));
    memset($t0,0,sizeof(struct CD2$Vector2D));
    res = $t0;
    CD2$Vector2D$init$($t0);
    (*res).x = x;
    (*res).y = y;
    return res;
}

void CD2$drawMotionOnVoxelMap(struct som$RedBlackTree$c4a1631837$RedBlackTree * voxelMap, struct CD2$Motion * motion) {
    struct som$RedBlackTree$9e53bca141$RedBlackTree * seen;
    seen = 0;
    seen = som$RedBlackTree$9e53bca141$create(CD2$compareVector2D);
    CD2$recurse(voxelMap, seen, CD2$voxelHash((*motion).posOne), motion);
}

struct CD2$CollisionDetector$handleNewFrame$ForEachInterface$Class$ CD2$CollisionDetector$handleNewFrame$ForEachInterface$class$ = { 
    &som$Interfaces$57f847cd33$ForEachInterface$class$,
    CD2$CollisionDetector$handleNewFrame$ForEachInterface$apply,
};

struct CD2$Motion$Class$ CD2$Motion$class$ = { 
    0,
    CD2$Motion$delta,
    CD2$Motion$findIntersection,
};

struct CD2$Simulator$Class$ CD2$Simulator$class$ = { 
    0,
    CD2$Simulator$simulate,
};

struct CD2$Aircraft$Class$ CD2$Aircraft$class$ = { 
    0,
};

struct CD2$Vector2D$Class$ CD2$Vector2D$class$ = { 
    0,
    CD2$Vector2D$plus,
    CD2$Vector2D$minus,
};

struct CD2$CallSign$Class$ CD2$CallSign$class$ = { 
    0,
};

struct CD2$Collision$Class$ CD2$Collision$class$ = { 
    0,
};

struct CD2$CollisionDetector$Class$ CD2$CollisionDetector$class$ = { 
    0,
    CD2$CollisionDetector$handleNewFrame,
};

struct CD2$reduceCollisionSet$ForEachInterface$Class$ CD2$reduceCollisionSet$ForEachInterface$class$ = { 
    &som$Interfaces$017cf6702e$ForEachInterface$class$,
    CD2$reduceCollisionSet$ForEachInterface$apply,
};

struct CD2$CD$Class$ CD2$CD$class$ = { 
    &Benchmark$Benchmark$class$,
    CD2$CD$benchmark,
    CD2$CD$verifyResult,
    CD2$CD$innerBenchmarkLoop,
};

struct CD2$Vector3D$Class$ CD2$Vector3D$class$ = { 
    0,
    CD2$Vector3D$plus,
    CD2$Vector3D$minus,
    CD2$Vector3D$times,
    CD2$Vector3D$dot,
    CD2$Vector3D$squaredMagnitude,
    CD2$Vector3D$magnitude,
};

static int initDone$ = 0;
void CD2$init$(void) {
    struct CD2$Vector2D * $t0;
    if(initDone$) return; else initDone$ = 1;
    Benchmark$init$();
    Out$init$();
    Math$init$();
    som$Vector$03bc1d2b30$init$();
    som$Vector$f13888695d$init$();
    som$Vector$d424285281$init$();
    som$Vector$1c1b29cf70$init$();
    som$Vector$3765c927e5$init$();
    som$RedBlackTree$1a37460855$init$();
    som$RedBlackTree$c4a1631837$init$();
    som$RedBlackTree$9e53bca141$init$();
    som$RedBlackTree$baea382c58$init$();
    $t0 = OBX$Alloc(sizeof(struct CD2$Vector2D));
    memset($t0,0,sizeof(struct CD2$Vector2D));
    CD2$horizontal = $t0;
    CD2$Vector2D$init$($t0);
    (*CD2$horizontal).x = 2.0000000e+00;
    (*CD2$horizontal).y = 0.0000000e+00;
    $t0 = OBX$Alloc(sizeof(struct CD2$Vector2D));
    memset($t0,0,sizeof(struct CD2$Vector2D));
    CD2$vertical = $t0;
    CD2$Vector2D$init$($t0);
    (*CD2$vertical).x = 0.0000000e+00;
    (*CD2$vertical).y = 2.0000000e+00;
}
OBX$Cmd CD2$cmd$(const char* name) {
    if( name == 0 ) return CD2$init$;
    return 0;
}