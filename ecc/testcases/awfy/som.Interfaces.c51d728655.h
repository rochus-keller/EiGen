#ifndef _SOM$INTERFACES$C51D728655_
#define _SOM$INTERFACES$C51D728655_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"

// Declaration of module som.Interfaces(DeltaBlue.Strength)

struct DeltaBlue$Strength; // meta actual
struct som$Interfaces$c51d728655$ForEachInterface$Class$;
struct som$Interfaces$c51d728655$ForEachInterface;
struct som$Interfaces$c51d728655$ForEachInterfaceRW$Class$;
struct som$Interfaces$c51d728655$ForEachInterfaceRW;
struct som$Interfaces$c51d728655$Comparator$Class$;
struct som$Interfaces$c51d728655$Comparator;
struct som$Interfaces$c51d728655$TestInterface$Class$;
struct som$Interfaces$c51d728655$TestInterface;
struct som$Interfaces$c51d728655$ForEachInterface {
    struct som$Interfaces$c51d728655$ForEachInterface$Class$* class$;
};

extern void som$Interfaces$c51d728655$ForEachInterface$init$(struct som$Interfaces$c51d728655$ForEachInterface*);
struct som$Interfaces$c51d728655$ForEachInterfaceRW {
    struct som$Interfaces$c51d728655$ForEachInterfaceRW$Class$* class$;
};

extern void som$Interfaces$c51d728655$ForEachInterfaceRW$init$(struct som$Interfaces$c51d728655$ForEachInterfaceRW*);
struct som$Interfaces$c51d728655$Comparator {
    struct som$Interfaces$c51d728655$Comparator$Class$* class$;
};

extern void som$Interfaces$c51d728655$Comparator$init$(struct som$Interfaces$c51d728655$Comparator*);
struct som$Interfaces$c51d728655$TestInterface {
    struct som$Interfaces$c51d728655$TestInterface$Class$* class$;
};

extern void som$Interfaces$c51d728655$TestInterface$init$(struct som$Interfaces$c51d728655$TestInterface*);
void som$Interfaces$c51d728655$ForEachInterface$apply(void* this, struct DeltaBlue$Strength * * elem);
void som$Interfaces$c51d728655$ForEachInterfaceRW$apply(void* this, struct DeltaBlue$Strength * * elem);
uint8_t som$Interfaces$c51d728655$TestInterface$test(void* this, struct DeltaBlue$Strength * * elem);
int32_t som$Interfaces$c51d728655$Comparator$compare(void* this, struct DeltaBlue$Strength * * i, struct DeltaBlue$Strength * * j);
struct som$Interfaces$c51d728655$ForEachInterface$Class$ {
    struct som$Interfaces$c51d728655$ForEachInterface$Class$* super$;
    void (*apply)(void* this, struct DeltaBlue$Strength * * elem);
};
extern struct som$Interfaces$c51d728655$ForEachInterface$Class$ som$Interfaces$c51d728655$ForEachInterface$class$;

struct som$Interfaces$c51d728655$ForEachInterfaceRW$Class$ {
    struct som$Interfaces$c51d728655$ForEachInterfaceRW$Class$* super$;
    void (*apply)(void* this, struct DeltaBlue$Strength * * elem);
};
extern struct som$Interfaces$c51d728655$ForEachInterfaceRW$Class$ som$Interfaces$c51d728655$ForEachInterfaceRW$class$;

struct som$Interfaces$c51d728655$Comparator$Class$ {
    struct som$Interfaces$c51d728655$Comparator$Class$* super$;
    int32_t (*compare)(void* this, struct DeltaBlue$Strength * * i, struct DeltaBlue$Strength * * j);
};
extern struct som$Interfaces$c51d728655$Comparator$Class$ som$Interfaces$c51d728655$Comparator$class$;

struct som$Interfaces$c51d728655$TestInterface$Class$ {
    struct som$Interfaces$c51d728655$TestInterface$Class$* super$;
    uint8_t (*test)(void* this, struct DeltaBlue$Strength * * elem);
};
extern struct som$Interfaces$c51d728655$TestInterface$Class$ som$Interfaces$c51d728655$TestInterface$class$;

extern void som$Interfaces$c51d728655$init$(void);
extern OBX$Cmd som$Interfaces$c51d728655$cmd$(const char* name);
#endif
