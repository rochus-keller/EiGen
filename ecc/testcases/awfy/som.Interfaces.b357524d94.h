#ifndef _SOM$INTERFACES$B357524D94_
#define _SOM$INTERFACES$B357524D94_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"

// Declaration of module som.Interfaces(som.RedBlackTree(CD.CallSign,BOOLEAN).Entry)

struct som$RedBlackTree$adef759a05$Entry;
struct som$RedBlackTree$adef759a05$Entry; // meta actual
struct som$Interfaces$b357524d94$ForEachInterface$Class$;
struct som$Interfaces$b357524d94$ForEachInterface;
struct som$Interfaces$b357524d94$Comparator$Class$;
struct som$Interfaces$b357524d94$Comparator;
struct som$Interfaces$b357524d94$ForEachInterfaceRW$Class$;
struct som$Interfaces$b357524d94$ForEachInterfaceRW;
struct som$Interfaces$b357524d94$TestInterface$Class$;
struct som$Interfaces$b357524d94$TestInterface;
struct som$Interfaces$b357524d94$ForEachInterface {
    struct som$Interfaces$b357524d94$ForEachInterface$Class$* class$;
};

extern void som$Interfaces$b357524d94$ForEachInterface$init$(struct som$Interfaces$b357524d94$ForEachInterface*);
struct som$Interfaces$b357524d94$Comparator {
    struct som$Interfaces$b357524d94$Comparator$Class$* class$;
};

extern void som$Interfaces$b357524d94$Comparator$init$(struct som$Interfaces$b357524d94$Comparator*);
struct som$Interfaces$b357524d94$ForEachInterfaceRW {
    struct som$Interfaces$b357524d94$ForEachInterfaceRW$Class$* class$;
};

extern void som$Interfaces$b357524d94$ForEachInterfaceRW$init$(struct som$Interfaces$b357524d94$ForEachInterfaceRW*);
struct som$Interfaces$b357524d94$TestInterface {
    struct som$Interfaces$b357524d94$TestInterface$Class$* class$;
};

extern void som$Interfaces$b357524d94$TestInterface$init$(struct som$Interfaces$b357524d94$TestInterface*);
void som$Interfaces$b357524d94$ForEachInterface$apply(void* this, struct som$RedBlackTree$adef759a05$Entry * elem);
void som$Interfaces$b357524d94$ForEachInterfaceRW$apply(void* this, struct som$RedBlackTree$adef759a05$Entry * elem);
uint8_t som$Interfaces$b357524d94$TestInterface$test(void* this, struct som$RedBlackTree$adef759a05$Entry * elem);
int32_t som$Interfaces$b357524d94$Comparator$compare(void* this, struct som$RedBlackTree$adef759a05$Entry * i, struct som$RedBlackTree$adef759a05$Entry * j);
struct som$Interfaces$b357524d94$ForEachInterface$Class$ {
    struct som$Interfaces$b357524d94$ForEachInterface$Class$* super$;
    void (*apply)(void* this, struct som$RedBlackTree$adef759a05$Entry * elem);
};
extern struct som$Interfaces$b357524d94$ForEachInterface$Class$ som$Interfaces$b357524d94$ForEachInterface$class$;

struct som$Interfaces$b357524d94$Comparator$Class$ {
    struct som$Interfaces$b357524d94$Comparator$Class$* super$;
    int32_t (*compare)(void* this, struct som$RedBlackTree$adef759a05$Entry * i, struct som$RedBlackTree$adef759a05$Entry * j);
};
extern struct som$Interfaces$b357524d94$Comparator$Class$ som$Interfaces$b357524d94$Comparator$class$;

struct som$Interfaces$b357524d94$ForEachInterfaceRW$Class$ {
    struct som$Interfaces$b357524d94$ForEachInterfaceRW$Class$* super$;
    void (*apply)(void* this, struct som$RedBlackTree$adef759a05$Entry * elem);
};
extern struct som$Interfaces$b357524d94$ForEachInterfaceRW$Class$ som$Interfaces$b357524d94$ForEachInterfaceRW$class$;

struct som$Interfaces$b357524d94$TestInterface$Class$ {
    struct som$Interfaces$b357524d94$TestInterface$Class$* super$;
    uint8_t (*test)(void* this, struct som$RedBlackTree$adef759a05$Entry * elem);
};
extern struct som$Interfaces$b357524d94$TestInterface$Class$ som$Interfaces$b357524d94$TestInterface$class$;

extern void som$Interfaces$b357524d94$init$(void);
extern OBX$Cmd som$Interfaces$b357524d94$cmd$(const char* name);
#endif
