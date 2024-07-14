#ifndef _CD2_
#define _CD2_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "Benchmark.h"
#include "Out.h"
#include "Math.h"
#include "som.Vector.03bc1d2b30.h"
#include "som.Vector.f13888695d.h"
#include "som.Vector.d424285281.h"
#include "som.Vector.1c1b29cf70.h"
#include "som.Vector.3765c927e5.h"
#include "som.RedBlackTree.1a37460855.h"
#include "som.RedBlackTree.c4a1631837.h"
#include "som.RedBlackTree.9e53bca141.h"
#include "som.RedBlackTree.baea382c58.h"

// Declaration of module CD2

struct CD2$CollisionDetector$handleNewFrame$ForEachInterface$Class$;
struct CD2$CollisionDetector$handleNewFrame$ForEachInterface;
struct CD2$Motion$Class$;
struct CD2$Motion;
struct CD2$Simulator$Class$;
struct CD2$Simulator;
struct CD2$Aircraft$Class$;
struct CD2$Aircraft;
struct CD2$Vector2D$Class$;
struct CD2$Vector2D;
struct CD2$CallSign$Class$;
struct CD2$CallSign;
struct CD2$Collision$Class$;
struct CD2$Collision;
struct CD2$CollisionDetector$Class$;
struct CD2$CollisionDetector;
struct CD2$reduceCollisionSet$ForEachInterface$Class$;
struct CD2$reduceCollisionSet$ForEachInterface;
struct CD2$CD$Class$;
struct CD2$CD;
struct CD2$Vector3D$Class$;
struct CD2$Vector3D;
struct CD2$CollisionDetector$handleNewFrame$ForEachInterface {
    struct CD2$CollisionDetector$handleNewFrame$ForEachInterface$Class$* class$;
    struct som$Vector$03bc1d2b30$Vector * toRemove;
    struct som$RedBlackTree$baea382c58$RedBlackTree * seen;
};

extern void CD2$CollisionDetector$handleNewFrame$ForEachInterface$init$(struct CD2$CollisionDetector$handleNewFrame$ForEachInterface*);
struct CD2$Motion {
    struct CD2$Motion$Class$* class$;
    struct CD2$CallSign * callsign;
    struct CD2$Vector3D * posOne;
    struct CD2$Vector3D * posTwo;
};

extern void CD2$Motion$init$(struct CD2$Motion*);
struct CD2$Simulator {
    struct CD2$Simulator$Class$* class$;
    struct som$Vector$03bc1d2b30$Vector * aircraft;
};

extern void CD2$Simulator$init$(struct CD2$Simulator*);
struct CD2$Aircraft {
    struct CD2$Aircraft$Class$* class$;
    struct CD2$CallSign * callsign;
    struct CD2$Vector3D * position;
};

extern void CD2$Aircraft$init$(struct CD2$Aircraft*);
struct CD2$Vector2D {
    struct CD2$Vector2D$Class$* class$;
    double x;
    double y;
};

extern void CD2$Vector2D$init$(struct CD2$Vector2D*);
struct CD2$CallSign {
    struct CD2$CallSign$Class$* class$;
    int32_t value;
};

extern void CD2$CallSign$init$(struct CD2$CallSign*);
struct CD2$Collision {
    struct CD2$Collision$Class$* class$;
    struct CD2$CallSign * aircraftA;
    struct CD2$CallSign * aircraftB;
    struct CD2$Vector3D * position;
};

extern void CD2$Collision$init$(struct CD2$Collision*);
struct CD2$CollisionDetector {
    struct CD2$CollisionDetector$Class$* class$;
    struct som$RedBlackTree$1a37460855$RedBlackTree * state;
};

extern void CD2$CollisionDetector$init$(struct CD2$CollisionDetector*);
struct CD2$reduceCollisionSet$ForEachInterface {
    struct CD2$reduceCollisionSet$ForEachInterface$Class$* class$;
    struct som$Vector$3765c927e5$Vector * result;
};

extern void CD2$reduceCollisionSet$ForEachInterface$init$(struct CD2$reduceCollisionSet$ForEachInterface*);
struct CD2$CD {
    struct CD2$CD$Class$* class$;
};

extern void CD2$CD$init$(struct CD2$CD*);
struct CD2$Vector3D {
    struct CD2$Vector3D$Class$* class$;
    double x;
    double y;
    double z;
};

extern void CD2$Vector3D$init$(struct CD2$Vector3D*);
extern struct CD2$Vector2D * CD2$horizontal;
extern struct CD2$Vector2D * CD2$vertical;
struct CD2$CD * CD2$create();
struct Benchmark$Result * CD2$CD$benchmark(void* this);
uint8_t CD2$CD$verifyResult(void* this, struct Benchmark$Result * result);
int32_t CD2$benchmark2(int32_t numAircrafts);
uint8_t CD2$CD$innerBenchmarkLoop(void* this, int32_t innerIterations);
uint8_t CD2$verifyResult2(int32_t actualCollisions, int32_t numAircrafts);
struct CD2$Vector2D * CD2$Vector2D$plus(void* this, struct CD2$Vector2D * other);
struct CD2$Vector2D * CD2$Vector2D$minus(void* this, struct CD2$Vector2D * other);
int32_t CD2$compareVector2D(struct CD2$Vector2D * * lhs, struct CD2$Vector2D * * rhs);
int32_t CD2$compareNumbers(double a, double b);
struct CD2$Vector3D * CD2$Vector3D$plus(void* this, struct CD2$Vector3D * other);
struct CD2$Vector3D * CD2$Vector3D$minus(void* this, struct CD2$Vector3D * other);
struct CD2$Vector3D * CD2$Vector3D$times(void* this, double amount);
double CD2$Vector3D$dot(void* this, struct CD2$Vector3D * other);
double CD2$Vector3D$squaredMagnitude(void* this);
double CD2$Vector3D$magnitude(void* this);
int32_t CD2$compareCallSign(struct CD2$CallSign * * lhs, struct CD2$CallSign * * rhs);
struct CD2$Collision * CD2$createCollision(struct CD2$CallSign * aircraftA, struct CD2$CallSign * aircraftB, struct CD2$Vector3D * position);
struct CD2$Simulator * CD2$createSimulator(int32_t numAircraft);
struct som$Vector$f13888695d$Vector * CD2$Simulator$simulate(void* this, double time);
struct CD2$Motion * CD2$createMotion(struct CD2$CallSign * * callsign, struct CD2$Vector3D * posOne, struct CD2$Vector3D * posTwo);
struct CD2$Vector3D * CD2$Motion$delta(void* this);
struct CD2$Vector3D * CD2$Motion$findIntersection(void* this, struct CD2$Motion * other);
struct CD2$CollisionDetector * CD2$createCD();
struct som$Vector$1c1b29cf70$Vector * CD2$CollisionDetector$handleNewFrame(void* this, struct som$Vector$f13888695d$Vector * frame);
void CD2$CollisionDetector$handleNewFrame$ForEachInterface$apply(void* this, struct som$RedBlackTree$1a37460855$Entry * elem);
uint8_t CD2$isInVoxel(struct CD2$Vector2D * voxel, struct CD2$Motion * motion);
void CD2$putIntoMap(struct som$RedBlackTree$c4a1631837$RedBlackTree * voxelMap, struct CD2$Vector2D * voxel, struct CD2$Motion * motion);
struct som$Vector$3765c927e5$Vector * CD2$reduceCollisionSet(struct som$Vector$d424285281$Vector * motions);
void CD2$reduceCollisionSet$ForEachInterface$apply(void* this, struct som$RedBlackTree$c4a1631837$Entry * elem);
void CD2$recurse(struct som$RedBlackTree$c4a1631837$RedBlackTree * voxelMap, struct som$RedBlackTree$9e53bca141$RedBlackTree * seen, struct CD2$Vector2D * nextVoxel, struct CD2$Motion * motion);
struct CD2$Vector2D * CD2$voxelHash(struct CD2$Vector3D * position);
void CD2$drawMotionOnVoxelMap(struct som$RedBlackTree$c4a1631837$RedBlackTree * voxelMap, struct CD2$Motion * motion);
struct CD2$CollisionDetector$handleNewFrame$ForEachInterface$Class$ {
    struct som$Interfaces$57f847cd33$ForEachInterface$Class$* super$;
    void (*apply)(void* this, struct som$RedBlackTree$1a37460855$Entry * elem);
};
extern struct CD2$CollisionDetector$handleNewFrame$ForEachInterface$Class$ CD2$CollisionDetector$handleNewFrame$ForEachInterface$class$;

struct CD2$Motion$Class$ {
    struct CD2$Motion$Class$* super$;
    struct CD2$Vector3D * (*delta)(void* this);
    struct CD2$Vector3D * (*findIntersection)(void* this, struct CD2$Motion * other);
};
extern struct CD2$Motion$Class$ CD2$Motion$class$;

struct CD2$Simulator$Class$ {
    struct CD2$Simulator$Class$* super$;
    struct som$Vector$f13888695d$Vector * (*simulate)(void* this, double time);
};
extern struct CD2$Simulator$Class$ CD2$Simulator$class$;

struct CD2$Aircraft$Class$ {
    struct CD2$Aircraft$Class$* super$;
};
extern struct CD2$Aircraft$Class$ CD2$Aircraft$class$;

struct CD2$Vector2D$Class$ {
    struct CD2$Vector2D$Class$* super$;
    struct CD2$Vector2D * (*plus)(void* this, struct CD2$Vector2D * other);
    struct CD2$Vector2D * (*minus)(void* this, struct CD2$Vector2D * other);
};
extern struct CD2$Vector2D$Class$ CD2$Vector2D$class$;

struct CD2$CallSign$Class$ {
    struct CD2$CallSign$Class$* super$;
};
extern struct CD2$CallSign$Class$ CD2$CallSign$class$;

struct CD2$Collision$Class$ {
    struct CD2$Collision$Class$* super$;
};
extern struct CD2$Collision$Class$ CD2$Collision$class$;

struct CD2$CollisionDetector$Class$ {
    struct CD2$CollisionDetector$Class$* super$;
    struct som$Vector$1c1b29cf70$Vector * (*handleNewFrame)(void* this, struct som$Vector$f13888695d$Vector * frame);
};
extern struct CD2$CollisionDetector$Class$ CD2$CollisionDetector$class$;

struct CD2$reduceCollisionSet$ForEachInterface$Class$ {
    struct som$Interfaces$017cf6702e$ForEachInterface$Class$* super$;
    void (*apply)(void* this, struct som$RedBlackTree$c4a1631837$Entry * elem);
};
extern struct CD2$reduceCollisionSet$ForEachInterface$Class$ CD2$reduceCollisionSet$ForEachInterface$class$;

struct CD2$CD$Class$ {
    struct Benchmark$Benchmark$Class$* super$;
    struct Benchmark$Result * (*benchmark)(void* this);
    uint8_t (*verifyResult)(void* this, struct Benchmark$Result * result);
    uint8_t (*innerBenchmarkLoop)(void* this, int32_t innerIterations);
};
extern struct CD2$CD$Class$ CD2$CD$class$;

struct CD2$Vector3D$Class$ {
    struct CD2$Vector3D$Class$* super$;
    struct CD2$Vector3D * (*plus)(void* this, struct CD2$Vector3D * other);
    struct CD2$Vector3D * (*minus)(void* this, struct CD2$Vector3D * other);
    struct CD2$Vector3D * (*times)(void* this, double amount);
    double (*dot)(void* this, struct CD2$Vector3D * other);
    double (*squaredMagnitude)(void* this);
    double (*magnitude)(void* this);
};
extern struct CD2$Vector3D$Class$ CD2$Vector3D$class$;

extern void CD2$init$(void);
extern OBX$Cmd CD2$cmd$(const char* name);
#endif
