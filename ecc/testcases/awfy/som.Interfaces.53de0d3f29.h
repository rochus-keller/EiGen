#ifndef _SOM$INTERFACES$53DE0D3F29_
#define _SOM$INTERFACES$53DE0D3F29_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"

// Declaration of module som.Interfaces(som.RedBlackTree(INT32,Tester.String).Entry)

struct som$RedBlackTree$4765cc5acb$Entry;
struct som$RedBlackTree$4765cc5acb$Entry; // meta actual
struct som$Interfaces$53de0d3f29$ForEachInterface$Class$;
struct som$Interfaces$53de0d3f29$ForEachInterface;
struct som$Interfaces$53de0d3f29$TestInterface$Class$;
struct som$Interfaces$53de0d3f29$TestInterface;
struct som$Interfaces$53de0d3f29$Comparator$Class$;
struct som$Interfaces$53de0d3f29$Comparator;
struct som$Interfaces$53de0d3f29$ForEachInterfaceRW$Class$;
struct som$Interfaces$53de0d3f29$ForEachInterfaceRW;
struct som$Interfaces$53de0d3f29$ForEachInterface {
    struct som$Interfaces$53de0d3f29$ForEachInterface$Class$* class$;
};

extern void som$Interfaces$53de0d3f29$ForEachInterface$init$(struct som$Interfaces$53de0d3f29$ForEachInterface*);
struct som$Interfaces$53de0d3f29$TestInterface {
    struct som$Interfaces$53de0d3f29$TestInterface$Class$* class$;
};

extern void som$Interfaces$53de0d3f29$TestInterface$init$(struct som$Interfaces$53de0d3f29$TestInterface*);
struct som$Interfaces$53de0d3f29$Comparator {
    struct som$Interfaces$53de0d3f29$Comparator$Class$* class$;
};

extern void som$Interfaces$53de0d3f29$Comparator$init$(struct som$Interfaces$53de0d3f29$Comparator*);
struct som$Interfaces$53de0d3f29$ForEachInterfaceRW {
    struct som$Interfaces$53de0d3f29$ForEachInterfaceRW$Class$* class$;
};

extern void som$Interfaces$53de0d3f29$ForEachInterfaceRW$init$(struct som$Interfaces$53de0d3f29$ForEachInterfaceRW*);
void som$Interfaces$53de0d3f29$ForEachInterface$apply(void* this, struct som$RedBlackTree$4765cc5acb$Entry * elem);
void som$Interfaces$53de0d3f29$ForEachInterfaceRW$apply(void* this, struct som$RedBlackTree$4765cc5acb$Entry * elem);
uint8_t som$Interfaces$53de0d3f29$TestInterface$test(void* this, struct som$RedBlackTree$4765cc5acb$Entry * elem);
int32_t som$Interfaces$53de0d3f29$Comparator$compare(void* this, struct som$RedBlackTree$4765cc5acb$Entry * i, struct som$RedBlackTree$4765cc5acb$Entry * j);
struct som$Interfaces$53de0d3f29$ForEachInterface$Class$ {
    struct som$Interfaces$53de0d3f29$ForEachInterface$Class$* super$;
    void (*apply)(void* this, struct som$RedBlackTree$4765cc5acb$Entry * elem);
};
extern struct som$Interfaces$53de0d3f29$ForEachInterface$Class$ som$Interfaces$53de0d3f29$ForEachInterface$class$;

struct som$Interfaces$53de0d3f29$TestInterface$Class$ {
    struct som$Interfaces$53de0d3f29$TestInterface$Class$* super$;
    uint8_t (*test)(void* this, struct som$RedBlackTree$4765cc5acb$Entry * elem);
};
extern struct som$Interfaces$53de0d3f29$TestInterface$Class$ som$Interfaces$53de0d3f29$TestInterface$class$;

struct som$Interfaces$53de0d3f29$Comparator$Class$ {
    struct som$Interfaces$53de0d3f29$Comparator$Class$* super$;
    int32_t (*compare)(void* this, struct som$RedBlackTree$4765cc5acb$Entry * i, struct som$RedBlackTree$4765cc5acb$Entry * j);
};
extern struct som$Interfaces$53de0d3f29$Comparator$Class$ som$Interfaces$53de0d3f29$Comparator$class$;

struct som$Interfaces$53de0d3f29$ForEachInterfaceRW$Class$ {
    struct som$Interfaces$53de0d3f29$ForEachInterfaceRW$Class$* super$;
    void (*apply)(void* this, struct som$RedBlackTree$4765cc5acb$Entry * elem);
};
extern struct som$Interfaces$53de0d3f29$ForEachInterfaceRW$Class$ som$Interfaces$53de0d3f29$ForEachInterfaceRW$class$;

extern void som$Interfaces$53de0d3f29$init$(void);
extern OBX$Cmd som$Interfaces$53de0d3f29$cmd$(const char* name);
#endif
