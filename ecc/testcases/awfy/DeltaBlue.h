#ifndef _DELTABLUE_
#define _DELTABLUE_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "Benchmark.h"
#include "som.IdentityDictionary2.df63a5a394.h"
#include "som.IdentityDictionary2.ec88893d1b.h"
#include "som.Interfaces.7850aff62d.h"
#include "som.Vector.ad6c2c594a.h"
#include "som.Interfaces.ad6c2c594a.h"
#include "som.Vector.7850aff62d.h"

// Declaration of module DeltaBlue

struct DeltaBlue$AbstractConstraint$inputsKnown$TI$Class$;
struct DeltaBlue$AbstractConstraint$inputsKnown$TI;
struct DeltaBlue$Variable$Class$;
struct DeltaBlue$Variable;
struct DeltaBlue$Planner$removePropagateFrom$IC$Class$;
struct DeltaBlue$Planner$removePropagateFrom$IC;
struct DeltaBlue$StayConstraint$Class$;
struct DeltaBlue$StayConstraint;
struct DeltaBlue$BinaryConstraint$Class$;
struct DeltaBlue$BinaryConstraint;
struct DeltaBlue$EqualityConstraint$Class$;
struct DeltaBlue$EqualityConstraint;
struct DeltaBlue$Strength$Class$;
struct DeltaBlue$Strength;
struct DeltaBlue$AbstractConstraint$satisfy$FI$Class$;
struct DeltaBlue$AbstractConstraint$satisfy$FI;
struct DeltaBlue$EditConstraint$Class$;
struct DeltaBlue$EditConstraint;
struct DeltaBlue$Planner$Class$;
struct DeltaBlue$Planner;
struct DeltaBlue$ScaleConstraint$Class$;
struct DeltaBlue$ScaleConstraint;
struct DeltaBlue$DeltaBlue$Class$;
struct DeltaBlue$DeltaBlue;
struct DeltaBlue$Sym$Class$;
struct DeltaBlue$Sym;
struct DeltaBlue$Planner$removePropagateFrom$FI$Class$;
struct DeltaBlue$Planner$removePropagateFrom$FI;
struct DeltaBlue$UnaryConstraint$Class$;
struct DeltaBlue$UnaryConstraint;
struct DeltaBlue$Plan$Class$;
struct DeltaBlue$Plan;
struct DeltaBlue$AbstractConstraint$Class$;
struct DeltaBlue$AbstractConstraint;
struct DeltaBlue$AbstractConstraint$inputsKnown$TI {
    struct DeltaBlue$AbstractConstraint$inputsKnown$TI$Class$* class$;
    int32_t mark;
};

extern void DeltaBlue$AbstractConstraint$inputsKnown$TI$init$(struct DeltaBlue$AbstractConstraint$inputsKnown$TI*);
struct DeltaBlue$Variable {
    struct DeltaBlue$Variable$Class$* class$;
    int32_t value;
    struct som$Vector$ad6c2c594a$Vector * constraints;
    struct DeltaBlue$AbstractConstraint * determinedBy;
    int32_t mark;
    struct DeltaBlue$Strength * walkStrength;
    uint8_t stay;
};

extern void DeltaBlue$Variable$init$(struct DeltaBlue$Variable*);
struct DeltaBlue$Planner$removePropagateFrom$IC {
    struct DeltaBlue$Planner$removePropagateFrom$IC$Class$* class$;
};

extern void DeltaBlue$Planner$removePropagateFrom$IC$init$(struct DeltaBlue$Planner$removePropagateFrom$IC*);
struct DeltaBlue$StayConstraint {
    struct DeltaBlue$StayConstraint$Class$* class$;
    struct DeltaBlue$Strength * strength;
    struct DeltaBlue$Variable * output;
    uint8_t satisfied;
};

extern void DeltaBlue$StayConstraint$init$(struct DeltaBlue$StayConstraint*);
struct DeltaBlue$BinaryConstraint {
    struct DeltaBlue$BinaryConstraint$Class$* class$;
    struct DeltaBlue$Strength * strength;
    struct DeltaBlue$Variable * v1;
    struct DeltaBlue$Variable * v2;
    int direction;
};

extern void DeltaBlue$BinaryConstraint$init$(struct DeltaBlue$BinaryConstraint*);
struct DeltaBlue$EqualityConstraint {
    struct DeltaBlue$EqualityConstraint$Class$* class$;
    struct DeltaBlue$Strength * strength;
    struct DeltaBlue$Variable * v1;
    struct DeltaBlue$Variable * v2;
    int direction;
};

extern void DeltaBlue$EqualityConstraint$init$(struct DeltaBlue$EqualityConstraint*);
struct DeltaBlue$Strength {
    struct DeltaBlue$Strength$Class$* class$;
    int32_t arithmeticValue;
    struct DeltaBlue$Sym * symbolicValue;
};

extern void DeltaBlue$Strength$init$(struct DeltaBlue$Strength*);
struct DeltaBlue$AbstractConstraint$satisfy$FI {
    struct DeltaBlue$AbstractConstraint$satisfy$FI$Class$* class$;
    int32_t mark;
};

extern void DeltaBlue$AbstractConstraint$satisfy$FI$init$(struct DeltaBlue$AbstractConstraint$satisfy$FI*);
struct DeltaBlue$EditConstraint {
    struct DeltaBlue$EditConstraint$Class$* class$;
    struct DeltaBlue$Strength * strength;
    struct DeltaBlue$Variable * output;
    uint8_t satisfied;
};

extern void DeltaBlue$EditConstraint$init$(struct DeltaBlue$EditConstraint*);
struct DeltaBlue$Planner {
    struct DeltaBlue$Planner$Class$* class$;
    int32_t currentMark;
};

extern void DeltaBlue$Planner$init$(struct DeltaBlue$Planner*);
struct DeltaBlue$ScaleConstraint {
    struct DeltaBlue$ScaleConstraint$Class$* class$;
    struct DeltaBlue$Strength * strength;
    struct DeltaBlue$Variable * v1;
    struct DeltaBlue$Variable * v2;
    int direction;
    struct DeltaBlue$Variable * scale;
    struct DeltaBlue$Variable * offset;
};

extern void DeltaBlue$ScaleConstraint$init$(struct DeltaBlue$ScaleConstraint*);
struct DeltaBlue$DeltaBlue {
    struct DeltaBlue$DeltaBlue$Class$* class$;
};

extern void DeltaBlue$DeltaBlue$init$(struct DeltaBlue$DeltaBlue*);
struct DeltaBlue$Sym {
    struct DeltaBlue$Sym$Class$* class$;
    int32_t hash;
};

extern void DeltaBlue$Sym$init$(struct DeltaBlue$Sym*);
struct DeltaBlue$Planner$removePropagateFrom$FI {
    struct DeltaBlue$Planner$removePropagateFrom$FI$Class$* class$;
    struct som$Vector$7850aff62d$Vector * todo;
};

extern void DeltaBlue$Planner$removePropagateFrom$FI$init$(struct DeltaBlue$Planner$removePropagateFrom$FI*);
struct DeltaBlue$UnaryConstraint {
    struct DeltaBlue$UnaryConstraint$Class$* class$;
    struct DeltaBlue$Strength * strength;
    struct DeltaBlue$Variable * output;
    uint8_t satisfied;
};

extern void DeltaBlue$UnaryConstraint$init$(struct DeltaBlue$UnaryConstraint*);
struct DeltaBlue$Plan {
    struct DeltaBlue$Plan$Class$* class$;
    struct som$Vector$ad6c2c594a$Vector * plan;
};

extern void DeltaBlue$Plan$init$(struct DeltaBlue$Plan*);
struct DeltaBlue$AbstractConstraint {
    struct DeltaBlue$AbstractConstraint$Class$* class$;
    struct DeltaBlue$Strength * strength;
};

extern void DeltaBlue$AbstractConstraint$init$(struct DeltaBlue$AbstractConstraint*);
extern struct DeltaBlue$Sym * DeltaBlue$ABSOLUTE_STRONGEST;
extern struct DeltaBlue$Sym * DeltaBlue$REQUIRED;
extern struct DeltaBlue$Sym * DeltaBlue$STRONG_PREFERRED;
extern struct DeltaBlue$Sym * DeltaBlue$PREFERRED;
extern struct DeltaBlue$Sym * DeltaBlue$STRONG_DEFAULT;
extern struct DeltaBlue$Sym * DeltaBlue$DEFAULT;
extern struct DeltaBlue$Sym * DeltaBlue$WEAK_DEFAULT;
extern struct DeltaBlue$Sym * DeltaBlue$ABSOLUTE_WEAKEST;
extern struct DeltaBlue$Strength * DeltaBlue$absoluteWeakest;
extern struct DeltaBlue$Strength * DeltaBlue$required;
extern struct som$Dictionary2$5c466e54b6$Dictionary * DeltaBlue$strengthTable;
extern struct som$Dictionary2$1fc4d3b22f$Dictionary * DeltaBlue$strengthConstant;
struct DeltaBlue$DeltaBlue * DeltaBlue$create();
struct Benchmark$Result * DeltaBlue$DeltaBlue$benchmark(void* this);
uint8_t DeltaBlue$DeltaBlue$verifyResult(void* this, struct Benchmark$Result * result);
uint8_t DeltaBlue$DeltaBlue$innerBenchmarkLoop(void* this, int32_t innerIterations);
struct DeltaBlue$Sym * DeltaBlue$createSym(int32_t hash);
int32_t DeltaBlue$symHash(struct DeltaBlue$Sym * * k);
struct DeltaBlue$Strength * DeltaBlue$createStrength(struct DeltaBlue$Sym * symbolicValue);
uint8_t DeltaBlue$Strength$sameAs(void* this, struct DeltaBlue$Strength * s);
uint8_t DeltaBlue$Strength$stronger(void* this, struct DeltaBlue$Strength * s);
uint8_t DeltaBlue$Strength$weaker(void* this, struct DeltaBlue$Strength * s);
struct DeltaBlue$Strength * DeltaBlue$Strength$strongest(void* this, struct DeltaBlue$Strength * s);
struct DeltaBlue$Strength * DeltaBlue$Strength$weakest(void* this, struct DeltaBlue$Strength * s);
void DeltaBlue$AbstractConstraint$initAbstractConstraint(void* this, struct DeltaBlue$Sym * strength);
uint8_t DeltaBlue$equalConstraint(struct DeltaBlue$AbstractConstraint * * lhs, struct DeltaBlue$AbstractConstraint * * rhs);
uint8_t DeltaBlue$AbstractConstraint$isInput(void* this);
uint8_t DeltaBlue$AbstractConstraint$isSatisfied(void* this);
void DeltaBlue$AbstractConstraint$addToGraph(void* this);
void DeltaBlue$AbstractConstraint$removeFromGraph(void* this);
int DeltaBlue$AbstractConstraint$chooseMethod(void* this, int32_t mark);
void DeltaBlue$AbstractConstraint$execute(void* this);
void DeltaBlue$AbstractConstraint$addConstraint(void* this, struct DeltaBlue$Planner * planner);
void DeltaBlue$AbstractConstraint$destroyConstraint(void* this, struct DeltaBlue$Planner * planner);
void DeltaBlue$AbstractConstraint$inputsDo(void* this, struct som$Interfaces$7850aff62d$ForEachInterfaceRW * fn);
uint8_t DeltaBlue$AbstractConstraint$inputsHasOne(void* this, struct som$Interfaces$7850aff62d$TestInterface * fn);
uint8_t DeltaBlue$AbstractConstraint$inputsKnown(void* this, int32_t mark);
uint8_t DeltaBlue$AbstractConstraint$inputsKnown$TI$test(void* this, struct DeltaBlue$Variable * * v);
void DeltaBlue$AbstractConstraint$markUnsatisfied(void* this);
struct DeltaBlue$Variable * DeltaBlue$AbstractConstraint$getOutput(void* this);
void DeltaBlue$AbstractConstraint$recalculate(void* this);
struct DeltaBlue$AbstractConstraint * DeltaBlue$AbstractConstraint$satisfy(void* this, int32_t mark, struct DeltaBlue$Planner * planner);
void DeltaBlue$AbstractConstraint$satisfy$FI$apply(void* this, struct DeltaBlue$Variable * * v);
struct DeltaBlue$Variable * DeltaBlue$value(int32_t aValue);
void DeltaBlue$Variable$addConstraint(void* this, struct DeltaBlue$AbstractConstraint * c);
void DeltaBlue$Variable$removeConstraint(void* this, struct DeltaBlue$AbstractConstraint * c);
void DeltaBlue$Plan$execute(void* this);
struct DeltaBlue$Planner * DeltaBlue$createPlanner();
void DeltaBlue$Planner$incrementalAdd(void* this, struct DeltaBlue$AbstractConstraint * c);
void DeltaBlue$Planner$incrementalRemove(void* this, struct DeltaBlue$AbstractConstraint * c);
struct DeltaBlue$Plan * DeltaBlue$Planner$extractPlanFromConstraints(void* this, struct som$Vector$ad6c2c594a$Vector * constraints);
struct DeltaBlue$Plan * DeltaBlue$Planner$makePlan(void* this, struct som$Vector$ad6c2c594a$Vector * sources);
void DeltaBlue$Planner$propagateFrom(void* this, struct DeltaBlue$Variable * v);
void DeltaBlue$Planner$addConstraintsConsumingTo(void* this, struct DeltaBlue$Variable * v, struct som$Vector$ad6c2c594a$Vector * coll);
uint8_t DeltaBlue$Planner$addPropagate(void* this, struct DeltaBlue$AbstractConstraint * c, int32_t mark);
void DeltaBlue$Planner$change(void* this, struct DeltaBlue$Variable * v, int32_t newValue);
void DeltaBlue$Planner$constraintsConsuming(void* this, struct DeltaBlue$Variable * v, struct som$Interfaces$ad6c2c594a$ForEachInterface * fn);
int32_t DeltaBlue$Planner$newMark(void* this);
struct som$Vector$ad6c2c594a$Vector * DeltaBlue$Planner$removePropagateFrom(void* this, struct DeltaBlue$Variable * out);
void DeltaBlue$Planner$removePropagateFrom$FI$apply(void* this, struct DeltaBlue$AbstractConstraint * * c);
int32_t DeltaBlue$Planner$removePropagateFrom$IC$compare(void* this, struct DeltaBlue$AbstractConstraint * * c1, struct DeltaBlue$AbstractConstraint * * c2);
void DeltaBlue$chainTest(int32_t n);
void DeltaBlue$projectionTest(int32_t n);
void DeltaBlue$UnaryConstraint$initUnaryConstraint(void* this, struct DeltaBlue$Variable * v, struct DeltaBlue$Sym * strength, struct DeltaBlue$Planner * planner);
uint8_t DeltaBlue$UnaryConstraint$isSatisfied(void* this);
void DeltaBlue$UnaryConstraint$addToGraph(void* this);
void DeltaBlue$UnaryConstraint$removeFromGraph(void* this);
int DeltaBlue$UnaryConstraint$chooseMethod(void* this, int32_t mark);
void DeltaBlue$UnaryConstraint$markUnsatisfied(void* this);
struct DeltaBlue$Variable * DeltaBlue$UnaryConstraint$getOutput(void* this);
void DeltaBlue$UnaryConstraint$recalculate(void* this);
struct DeltaBlue$EditConstraint * DeltaBlue$createEditConstraint(struct DeltaBlue$Variable * v, struct DeltaBlue$Sym * strength, struct DeltaBlue$Planner * planner);
uint8_t DeltaBlue$EditConstraint$isInput(void* this);
struct DeltaBlue$StayConstraint * DeltaBlue$createStayConstraint(struct DeltaBlue$Variable * v, struct DeltaBlue$Sym * strength, struct DeltaBlue$Planner * planner);
void DeltaBlue$BinaryConstraint$initBinaryConstraint(void* this, struct DeltaBlue$Variable * var1, struct DeltaBlue$Variable * var2, struct DeltaBlue$Sym * strength, struct DeltaBlue$Planner * planner);
uint8_t DeltaBlue$BinaryConstraint$isSatisfied(void* this);
void DeltaBlue$BinaryConstraint$addToGraph(void* this);
void DeltaBlue$BinaryConstraint$removeFromGraph(void* this);
int DeltaBlue$BinaryConstraint$chooseMethod(void* this, int32_t mark);
void DeltaBlue$BinaryConstraint$inputsDo(void* this, struct som$Interfaces$7850aff62d$ForEachInterfaceRW * fn);
uint8_t DeltaBlue$BinaryConstraint$inputsHasOne(void* this, struct som$Interfaces$7850aff62d$TestInterface * fn);
void DeltaBlue$BinaryConstraint$markUnsatisfied(void* this);
struct DeltaBlue$Variable * DeltaBlue$BinaryConstraint$getOutput(void* this);
void DeltaBlue$BinaryConstraint$recalculate(void* this);
struct DeltaBlue$EqualityConstraint * DeltaBlue$createEqualityConstraint(struct DeltaBlue$Variable * var1, struct DeltaBlue$Variable * var2, struct DeltaBlue$Sym * strength, struct DeltaBlue$Planner * planner);
void DeltaBlue$EqualityConstraint$execute(void* this);
struct DeltaBlue$ScaleConstraint * DeltaBlue$createScaleConstraint(struct DeltaBlue$Variable * src, struct DeltaBlue$Variable * scale, struct DeltaBlue$Variable * offset, struct DeltaBlue$Variable * dest, struct DeltaBlue$Sym * strength, struct DeltaBlue$Planner * planner);
void DeltaBlue$ScaleConstraint$addToGraph(void* this);
void DeltaBlue$ScaleConstraint$removeFromGraph(void* this);
void DeltaBlue$ScaleConstraint$execute(void* this);
void DeltaBlue$ScaleConstraint$inputsDo(void* this, struct som$Interfaces$7850aff62d$ForEachInterfaceRW * fn);
void DeltaBlue$ScaleConstraint$recalculate(void* this);
struct DeltaBlue$AbstractConstraint$inputsKnown$TI$Class$ {
    struct som$Interfaces$7850aff62d$TestInterface$Class$* super$;
    uint8_t (*test)(void* this, struct DeltaBlue$Variable * * v);
};
extern struct DeltaBlue$AbstractConstraint$inputsKnown$TI$Class$ DeltaBlue$AbstractConstraint$inputsKnown$TI$class$;

struct DeltaBlue$Variable$Class$ {
    struct DeltaBlue$Variable$Class$* super$;
    void (*addConstraint)(void* this, struct DeltaBlue$AbstractConstraint * c);
    void (*removeConstraint)(void* this, struct DeltaBlue$AbstractConstraint * c);
};
extern struct DeltaBlue$Variable$Class$ DeltaBlue$Variable$class$;

struct DeltaBlue$Planner$removePropagateFrom$IC$Class$ {
    struct som$Interfaces$ad6c2c594a$Comparator$Class$* super$;
    int32_t (*compare)(void* this, struct DeltaBlue$AbstractConstraint * * c1, struct DeltaBlue$AbstractConstraint * * c2);
};
extern struct DeltaBlue$Planner$removePropagateFrom$IC$Class$ DeltaBlue$Planner$removePropagateFrom$IC$class$;

struct DeltaBlue$StayConstraint$Class$ {
    struct DeltaBlue$UnaryConstraint$Class$* super$;
    void (*initAbstractConstraint)(void* this, struct DeltaBlue$Sym * strength);
    uint8_t (*isInput)(void* this);
    uint8_t (*isSatisfied)(void* this);
    void (*addToGraph)(void* this);
    void (*removeFromGraph)(void* this);
    int (*chooseMethod)(void* this, int32_t mark);
    void (*execute)(void* this);
    void (*addConstraint)(void* this, struct DeltaBlue$Planner * planner);
    void (*destroyConstraint)(void* this, struct DeltaBlue$Planner * planner);
    void (*inputsDo)(void* this, struct som$Interfaces$7850aff62d$ForEachInterfaceRW * fn);
    uint8_t (*inputsHasOne)(void* this, struct som$Interfaces$7850aff62d$TestInterface * fn);
    uint8_t (*inputsKnown)(void* this, int32_t mark);
    void (*markUnsatisfied)(void* this);
    struct DeltaBlue$Variable * (*getOutput)(void* this);
    void (*recalculate)(void* this);
    struct DeltaBlue$AbstractConstraint * (*satisfy)(void* this, int32_t mark, struct DeltaBlue$Planner * planner);
    void (*initUnaryConstraint)(void* this, struct DeltaBlue$Variable * v, struct DeltaBlue$Sym * strength, struct DeltaBlue$Planner * planner);
};
extern struct DeltaBlue$StayConstraint$Class$ DeltaBlue$StayConstraint$class$;

struct DeltaBlue$BinaryConstraint$Class$ {
    struct DeltaBlue$AbstractConstraint$Class$* super$;
    void (*initAbstractConstraint)(void* this, struct DeltaBlue$Sym * strength);
    uint8_t (*isInput)(void* this);
    uint8_t (*isSatisfied)(void* this);
    void (*addToGraph)(void* this);
    void (*removeFromGraph)(void* this);
    int (*chooseMethod)(void* this, int32_t mark);
    void (*execute)(void* this);
    void (*addConstraint)(void* this, struct DeltaBlue$Planner * planner);
    void (*destroyConstraint)(void* this, struct DeltaBlue$Planner * planner);
    void (*inputsDo)(void* this, struct som$Interfaces$7850aff62d$ForEachInterfaceRW * fn);
    uint8_t (*inputsHasOne)(void* this, struct som$Interfaces$7850aff62d$TestInterface * fn);
    uint8_t (*inputsKnown)(void* this, int32_t mark);
    void (*markUnsatisfied)(void* this);
    struct DeltaBlue$Variable * (*getOutput)(void* this);
    void (*recalculate)(void* this);
    struct DeltaBlue$AbstractConstraint * (*satisfy)(void* this, int32_t mark, struct DeltaBlue$Planner * planner);
    void (*initBinaryConstraint)(void* this, struct DeltaBlue$Variable * var1, struct DeltaBlue$Variable * var2, struct DeltaBlue$Sym * strength, struct DeltaBlue$Planner * planner);
};
extern struct DeltaBlue$BinaryConstraint$Class$ DeltaBlue$BinaryConstraint$class$;

struct DeltaBlue$EqualityConstraint$Class$ {
    struct DeltaBlue$BinaryConstraint$Class$* super$;
    void (*initAbstractConstraint)(void* this, struct DeltaBlue$Sym * strength);
    uint8_t (*isInput)(void* this);
    uint8_t (*isSatisfied)(void* this);
    void (*addToGraph)(void* this);
    void (*removeFromGraph)(void* this);
    int (*chooseMethod)(void* this, int32_t mark);
    void (*execute)(void* this);
    void (*addConstraint)(void* this, struct DeltaBlue$Planner * planner);
    void (*destroyConstraint)(void* this, struct DeltaBlue$Planner * planner);
    void (*inputsDo)(void* this, struct som$Interfaces$7850aff62d$ForEachInterfaceRW * fn);
    uint8_t (*inputsHasOne)(void* this, struct som$Interfaces$7850aff62d$TestInterface * fn);
    uint8_t (*inputsKnown)(void* this, int32_t mark);
    void (*markUnsatisfied)(void* this);
    struct DeltaBlue$Variable * (*getOutput)(void* this);
    void (*recalculate)(void* this);
    struct DeltaBlue$AbstractConstraint * (*satisfy)(void* this, int32_t mark, struct DeltaBlue$Planner * planner);
    void (*initBinaryConstraint)(void* this, struct DeltaBlue$Variable * var1, struct DeltaBlue$Variable * var2, struct DeltaBlue$Sym * strength, struct DeltaBlue$Planner * planner);
};
extern struct DeltaBlue$EqualityConstraint$Class$ DeltaBlue$EqualityConstraint$class$;

struct DeltaBlue$Strength$Class$ {
    struct DeltaBlue$Strength$Class$* super$;
    uint8_t (*sameAs)(void* this, struct DeltaBlue$Strength * s);
    uint8_t (*stronger)(void* this, struct DeltaBlue$Strength * s);
    uint8_t (*weaker)(void* this, struct DeltaBlue$Strength * s);
    struct DeltaBlue$Strength * (*strongest)(void* this, struct DeltaBlue$Strength * s);
    struct DeltaBlue$Strength * (*weakest)(void* this, struct DeltaBlue$Strength * s);
};
extern struct DeltaBlue$Strength$Class$ DeltaBlue$Strength$class$;

struct DeltaBlue$AbstractConstraint$satisfy$FI$Class$ {
    struct som$Interfaces$7850aff62d$ForEachInterfaceRW$Class$* super$;
    void (*apply)(void* this, struct DeltaBlue$Variable * * v);
};
extern struct DeltaBlue$AbstractConstraint$satisfy$FI$Class$ DeltaBlue$AbstractConstraint$satisfy$FI$class$;

struct DeltaBlue$EditConstraint$Class$ {
    struct DeltaBlue$UnaryConstraint$Class$* super$;
    void (*initAbstractConstraint)(void* this, struct DeltaBlue$Sym * strength);
    uint8_t (*isInput)(void* this);
    uint8_t (*isSatisfied)(void* this);
    void (*addToGraph)(void* this);
    void (*removeFromGraph)(void* this);
    int (*chooseMethod)(void* this, int32_t mark);
    void (*execute)(void* this);
    void (*addConstraint)(void* this, struct DeltaBlue$Planner * planner);
    void (*destroyConstraint)(void* this, struct DeltaBlue$Planner * planner);
    void (*inputsDo)(void* this, struct som$Interfaces$7850aff62d$ForEachInterfaceRW * fn);
    uint8_t (*inputsHasOne)(void* this, struct som$Interfaces$7850aff62d$TestInterface * fn);
    uint8_t (*inputsKnown)(void* this, int32_t mark);
    void (*markUnsatisfied)(void* this);
    struct DeltaBlue$Variable * (*getOutput)(void* this);
    void (*recalculate)(void* this);
    struct DeltaBlue$AbstractConstraint * (*satisfy)(void* this, int32_t mark, struct DeltaBlue$Planner * planner);
    void (*initUnaryConstraint)(void* this, struct DeltaBlue$Variable * v, struct DeltaBlue$Sym * strength, struct DeltaBlue$Planner * planner);
};
extern struct DeltaBlue$EditConstraint$Class$ DeltaBlue$EditConstraint$class$;

struct DeltaBlue$Planner$Class$ {
    struct DeltaBlue$Planner$Class$* super$;
    void (*incrementalAdd)(void* this, struct DeltaBlue$AbstractConstraint * c);
    void (*incrementalRemove)(void* this, struct DeltaBlue$AbstractConstraint * c);
    struct DeltaBlue$Plan * (*extractPlanFromConstraints)(void* this, struct som$Vector$ad6c2c594a$Vector * constraints);
    struct DeltaBlue$Plan * (*makePlan)(void* this, struct som$Vector$ad6c2c594a$Vector * sources);
    void (*propagateFrom)(void* this, struct DeltaBlue$Variable * v);
    void (*addConstraintsConsumingTo)(void* this, struct DeltaBlue$Variable * v, struct som$Vector$ad6c2c594a$Vector * coll);
    uint8_t (*addPropagate)(void* this, struct DeltaBlue$AbstractConstraint * c, int32_t mark);
    void (*change)(void* this, struct DeltaBlue$Variable * v, int32_t newValue);
    void (*constraintsConsuming)(void* this, struct DeltaBlue$Variable * v, struct som$Interfaces$ad6c2c594a$ForEachInterface * fn);
    int32_t (*newMark)(void* this);
    struct som$Vector$ad6c2c594a$Vector * (*removePropagateFrom)(void* this, struct DeltaBlue$Variable * out);
};
extern struct DeltaBlue$Planner$Class$ DeltaBlue$Planner$class$;

struct DeltaBlue$ScaleConstraint$Class$ {
    struct DeltaBlue$BinaryConstraint$Class$* super$;
    void (*initAbstractConstraint)(void* this, struct DeltaBlue$Sym * strength);
    uint8_t (*isInput)(void* this);
    uint8_t (*isSatisfied)(void* this);
    void (*addToGraph)(void* this);
    void (*removeFromGraph)(void* this);
    int (*chooseMethod)(void* this, int32_t mark);
    void (*execute)(void* this);
    void (*addConstraint)(void* this, struct DeltaBlue$Planner * planner);
    void (*destroyConstraint)(void* this, struct DeltaBlue$Planner * planner);
    void (*inputsDo)(void* this, struct som$Interfaces$7850aff62d$ForEachInterfaceRW * fn);
    uint8_t (*inputsHasOne)(void* this, struct som$Interfaces$7850aff62d$TestInterface * fn);
    uint8_t (*inputsKnown)(void* this, int32_t mark);
    void (*markUnsatisfied)(void* this);
    struct DeltaBlue$Variable * (*getOutput)(void* this);
    void (*recalculate)(void* this);
    struct DeltaBlue$AbstractConstraint * (*satisfy)(void* this, int32_t mark, struct DeltaBlue$Planner * planner);
    void (*initBinaryConstraint)(void* this, struct DeltaBlue$Variable * var1, struct DeltaBlue$Variable * var2, struct DeltaBlue$Sym * strength, struct DeltaBlue$Planner * planner);
};
extern struct DeltaBlue$ScaleConstraint$Class$ DeltaBlue$ScaleConstraint$class$;

struct DeltaBlue$DeltaBlue$Class$ {
    struct Benchmark$Benchmark$Class$* super$;
    struct Benchmark$Result * (*benchmark)(void* this);
    uint8_t (*verifyResult)(void* this, struct Benchmark$Result * result);
    uint8_t (*innerBenchmarkLoop)(void* this, int32_t innerIterations);
};
extern struct DeltaBlue$DeltaBlue$Class$ DeltaBlue$DeltaBlue$class$;

struct DeltaBlue$Sym$Class$ {
    struct DeltaBlue$Sym$Class$* super$;
};
extern struct DeltaBlue$Sym$Class$ DeltaBlue$Sym$class$;

struct DeltaBlue$Planner$removePropagateFrom$FI$Class$ {
    struct som$Interfaces$ad6c2c594a$ForEachInterface$Class$* super$;
    void (*apply)(void* this, struct DeltaBlue$AbstractConstraint * * c);
};
extern struct DeltaBlue$Planner$removePropagateFrom$FI$Class$ DeltaBlue$Planner$removePropagateFrom$FI$class$;

struct DeltaBlue$UnaryConstraint$Class$ {
    struct DeltaBlue$AbstractConstraint$Class$* super$;
    void (*initAbstractConstraint)(void* this, struct DeltaBlue$Sym * strength);
    uint8_t (*isInput)(void* this);
    uint8_t (*isSatisfied)(void* this);
    void (*addToGraph)(void* this);
    void (*removeFromGraph)(void* this);
    int (*chooseMethod)(void* this, int32_t mark);
    void (*execute)(void* this);
    void (*addConstraint)(void* this, struct DeltaBlue$Planner * planner);
    void (*destroyConstraint)(void* this, struct DeltaBlue$Planner * planner);
    void (*inputsDo)(void* this, struct som$Interfaces$7850aff62d$ForEachInterfaceRW * fn);
    uint8_t (*inputsHasOne)(void* this, struct som$Interfaces$7850aff62d$TestInterface * fn);
    uint8_t (*inputsKnown)(void* this, int32_t mark);
    void (*markUnsatisfied)(void* this);
    struct DeltaBlue$Variable * (*getOutput)(void* this);
    void (*recalculate)(void* this);
    struct DeltaBlue$AbstractConstraint * (*satisfy)(void* this, int32_t mark, struct DeltaBlue$Planner * planner);
    void (*initUnaryConstraint)(void* this, struct DeltaBlue$Variable * v, struct DeltaBlue$Sym * strength, struct DeltaBlue$Planner * planner);
};
extern struct DeltaBlue$UnaryConstraint$Class$ DeltaBlue$UnaryConstraint$class$;

struct DeltaBlue$Plan$Class$ {
    struct DeltaBlue$Plan$Class$* super$;
    void (*execute)(void* this);
};
extern struct DeltaBlue$Plan$Class$ DeltaBlue$Plan$class$;

struct DeltaBlue$AbstractConstraint$Class$ {
    struct DeltaBlue$AbstractConstraint$Class$* super$;
    void (*initAbstractConstraint)(void* this, struct DeltaBlue$Sym * strength);
    uint8_t (*isInput)(void* this);
    uint8_t (*isSatisfied)(void* this);
    void (*addToGraph)(void* this);
    void (*removeFromGraph)(void* this);
    int (*chooseMethod)(void* this, int32_t mark);
    void (*execute)(void* this);
    void (*addConstraint)(void* this, struct DeltaBlue$Planner * planner);
    void (*destroyConstraint)(void* this, struct DeltaBlue$Planner * planner);
    void (*inputsDo)(void* this, struct som$Interfaces$7850aff62d$ForEachInterfaceRW * fn);
    uint8_t (*inputsHasOne)(void* this, struct som$Interfaces$7850aff62d$TestInterface * fn);
    uint8_t (*inputsKnown)(void* this, int32_t mark);
    void (*markUnsatisfied)(void* this);
    struct DeltaBlue$Variable * (*getOutput)(void* this);
    void (*recalculate)(void* this);
    struct DeltaBlue$AbstractConstraint * (*satisfy)(void* this, int32_t mark, struct DeltaBlue$Planner * planner);
};
extern struct DeltaBlue$AbstractConstraint$Class$ DeltaBlue$AbstractConstraint$class$;

extern void DeltaBlue$init$(void);
extern OBX$Cmd DeltaBlue$cmd$(const char* name);
#endif