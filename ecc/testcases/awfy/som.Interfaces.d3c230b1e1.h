#ifndef _SOM$INTERFACES$D3C230B1E1_
#define _SOM$INTERFACES$D3C230B1E1_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"

// Declaration of module som.Interfaces(som.RedBlackTree(CD2.Vector2D,BOOLEAN).Entry)

struct som$RedBlackTree$9e53bca141$Entry;
struct som$RedBlackTree$9e53bca141$Entry; // meta actual
struct som$Interfaces$d3c230b1e1$ForEachInterfaceRW$Class$;
struct som$Interfaces$d3c230b1e1$ForEachInterfaceRW;
struct som$Interfaces$d3c230b1e1$TestInterface$Class$;
struct som$Interfaces$d3c230b1e1$TestInterface;
struct som$Interfaces$d3c230b1e1$ForEachInterface$Class$;
struct som$Interfaces$d3c230b1e1$ForEachInterface;
struct som$Interfaces$d3c230b1e1$Comparator$Class$;
struct som$Interfaces$d3c230b1e1$Comparator;
struct som$Interfaces$d3c230b1e1$ForEachInterfaceRW {
    struct som$Interfaces$d3c230b1e1$ForEachInterfaceRW$Class$* class$;
};

extern void som$Interfaces$d3c230b1e1$ForEachInterfaceRW$init$(struct som$Interfaces$d3c230b1e1$ForEachInterfaceRW*);
struct som$Interfaces$d3c230b1e1$TestInterface {
    struct som$Interfaces$d3c230b1e1$TestInterface$Class$* class$;
};

extern void som$Interfaces$d3c230b1e1$TestInterface$init$(struct som$Interfaces$d3c230b1e1$TestInterface*);
struct som$Interfaces$d3c230b1e1$ForEachInterface {
    struct som$Interfaces$d3c230b1e1$ForEachInterface$Class$* class$;
};

extern void som$Interfaces$d3c230b1e1$ForEachInterface$init$(struct som$Interfaces$d3c230b1e1$ForEachInterface*);
struct som$Interfaces$d3c230b1e1$Comparator {
    struct som$Interfaces$d3c230b1e1$Comparator$Class$* class$;
};

extern void som$Interfaces$d3c230b1e1$Comparator$init$(struct som$Interfaces$d3c230b1e1$Comparator*);
void som$Interfaces$d3c230b1e1$ForEachInterface$apply(void* this, struct som$RedBlackTree$9e53bca141$Entry * elem);
void som$Interfaces$d3c230b1e1$ForEachInterfaceRW$apply(void* this, struct som$RedBlackTree$9e53bca141$Entry * elem);
uint8_t som$Interfaces$d3c230b1e1$TestInterface$test(void* this, struct som$RedBlackTree$9e53bca141$Entry * elem);
int32_t som$Interfaces$d3c230b1e1$Comparator$compare(void* this, struct som$RedBlackTree$9e53bca141$Entry * i, struct som$RedBlackTree$9e53bca141$Entry * j);
struct som$Interfaces$d3c230b1e1$ForEachInterfaceRW$Class$ {
    struct som$Interfaces$d3c230b1e1$ForEachInterfaceRW$Class$* super$;
    void (*apply)(void* this, struct som$RedBlackTree$9e53bca141$Entry * elem);
};
extern struct som$Interfaces$d3c230b1e1$ForEachInterfaceRW$Class$ som$Interfaces$d3c230b1e1$ForEachInterfaceRW$class$;

struct som$Interfaces$d3c230b1e1$TestInterface$Class$ {
    struct som$Interfaces$d3c230b1e1$TestInterface$Class$* super$;
    uint8_t (*test)(void* this, struct som$RedBlackTree$9e53bca141$Entry * elem);
};
extern struct som$Interfaces$d3c230b1e1$TestInterface$Class$ som$Interfaces$d3c230b1e1$TestInterface$class$;

struct som$Interfaces$d3c230b1e1$ForEachInterface$Class$ {
    struct som$Interfaces$d3c230b1e1$ForEachInterface$Class$* super$;
    void (*apply)(void* this, struct som$RedBlackTree$9e53bca141$Entry * elem);
};
extern struct som$Interfaces$d3c230b1e1$ForEachInterface$Class$ som$Interfaces$d3c230b1e1$ForEachInterface$class$;

struct som$Interfaces$d3c230b1e1$Comparator$Class$ {
    struct som$Interfaces$d3c230b1e1$Comparator$Class$* super$;
    int32_t (*compare)(void* this, struct som$RedBlackTree$9e53bca141$Entry * i, struct som$RedBlackTree$9e53bca141$Entry * j);
};
extern struct som$Interfaces$d3c230b1e1$Comparator$Class$ som$Interfaces$d3c230b1e1$Comparator$class$;

extern void som$Interfaces$d3c230b1e1$init$(void);
extern OBX$Cmd som$Interfaces$d3c230b1e1$cmd$(const char* name);
#endif
