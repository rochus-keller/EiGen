#ifndef _SOM$INTERFACES$03BC1D2B30_
#define _SOM$INTERFACES$03BC1D2B30_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"

// Declaration of module som.Interfaces(CD2.CallSign)

struct CD2$CallSign; // meta actual
struct som$Interfaces$03bc1d2b30$ForEachInterface$Class$;
struct som$Interfaces$03bc1d2b30$ForEachInterface;
struct som$Interfaces$03bc1d2b30$TestInterface$Class$;
struct som$Interfaces$03bc1d2b30$TestInterface;
struct som$Interfaces$03bc1d2b30$Comparator$Class$;
struct som$Interfaces$03bc1d2b30$Comparator;
struct som$Interfaces$03bc1d2b30$ForEachInterfaceRW$Class$;
struct som$Interfaces$03bc1d2b30$ForEachInterfaceRW;
struct som$Interfaces$03bc1d2b30$ForEachInterface {
    struct som$Interfaces$03bc1d2b30$ForEachInterface$Class$* class$;
};

extern void som$Interfaces$03bc1d2b30$ForEachInterface$init$(struct som$Interfaces$03bc1d2b30$ForEachInterface*);
struct som$Interfaces$03bc1d2b30$TestInterface {
    struct som$Interfaces$03bc1d2b30$TestInterface$Class$* class$;
};

extern void som$Interfaces$03bc1d2b30$TestInterface$init$(struct som$Interfaces$03bc1d2b30$TestInterface*);
struct som$Interfaces$03bc1d2b30$Comparator {
    struct som$Interfaces$03bc1d2b30$Comparator$Class$* class$;
};

extern void som$Interfaces$03bc1d2b30$Comparator$init$(struct som$Interfaces$03bc1d2b30$Comparator*);
struct som$Interfaces$03bc1d2b30$ForEachInterfaceRW {
    struct som$Interfaces$03bc1d2b30$ForEachInterfaceRW$Class$* class$;
};

extern void som$Interfaces$03bc1d2b30$ForEachInterfaceRW$init$(struct som$Interfaces$03bc1d2b30$ForEachInterfaceRW*);
void som$Interfaces$03bc1d2b30$ForEachInterface$apply(void* this, struct CD2$CallSign * * elem);
void som$Interfaces$03bc1d2b30$ForEachInterfaceRW$apply(void* this, struct CD2$CallSign * * elem);
uint8_t som$Interfaces$03bc1d2b30$TestInterface$test(void* this, struct CD2$CallSign * * elem);
int32_t som$Interfaces$03bc1d2b30$Comparator$compare(void* this, struct CD2$CallSign * * i, struct CD2$CallSign * * j);
struct som$Interfaces$03bc1d2b30$ForEachInterface$Class$ {
    struct som$Interfaces$03bc1d2b30$ForEachInterface$Class$* super$;
    void (*apply)(void* this, struct CD2$CallSign * * elem);
};
extern struct som$Interfaces$03bc1d2b30$ForEachInterface$Class$ som$Interfaces$03bc1d2b30$ForEachInterface$class$;

struct som$Interfaces$03bc1d2b30$TestInterface$Class$ {
    struct som$Interfaces$03bc1d2b30$TestInterface$Class$* super$;
    uint8_t (*test)(void* this, struct CD2$CallSign * * elem);
};
extern struct som$Interfaces$03bc1d2b30$TestInterface$Class$ som$Interfaces$03bc1d2b30$TestInterface$class$;

struct som$Interfaces$03bc1d2b30$Comparator$Class$ {
    struct som$Interfaces$03bc1d2b30$Comparator$Class$* super$;
    int32_t (*compare)(void* this, struct CD2$CallSign * * i, struct CD2$CallSign * * j);
};
extern struct som$Interfaces$03bc1d2b30$Comparator$Class$ som$Interfaces$03bc1d2b30$Comparator$class$;

struct som$Interfaces$03bc1d2b30$ForEachInterfaceRW$Class$ {
    struct som$Interfaces$03bc1d2b30$ForEachInterfaceRW$Class$* super$;
    void (*apply)(void* this, struct CD2$CallSign * * elem);
};
extern struct som$Interfaces$03bc1d2b30$ForEachInterfaceRW$Class$ som$Interfaces$03bc1d2b30$ForEachInterfaceRW$class$;

extern void som$Interfaces$03bc1d2b30$init$(void);
extern OBX$Cmd som$Interfaces$03bc1d2b30$cmd$(const char* name);
#endif
