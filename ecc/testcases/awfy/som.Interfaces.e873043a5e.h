#ifndef _SOM$INTERFACES$E873043A5E_
#define _SOM$INTERFACES$E873043A5E_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"

// Declaration of module som.Interfaces(Tester.String)

struct som$Interfaces$e873043a5e$TestInterface$Class$;
struct som$Interfaces$e873043a5e$TestInterface;
struct som$Interfaces$e873043a5e$Comparator$Class$;
struct som$Interfaces$e873043a5e$Comparator;
struct som$Interfaces$e873043a5e$ForEachInterface$Class$;
struct som$Interfaces$e873043a5e$ForEachInterface;
struct som$Interfaces$e873043a5e$ForEachInterfaceRW$Class$;
struct som$Interfaces$e873043a5e$ForEachInterfaceRW;
struct som$Interfaces$e873043a5e$TestInterface {
    struct som$Interfaces$e873043a5e$TestInterface$Class$* class$;
};

extern void som$Interfaces$e873043a5e$TestInterface$init$(struct som$Interfaces$e873043a5e$TestInterface*);
struct som$Interfaces$e873043a5e$Comparator {
    struct som$Interfaces$e873043a5e$Comparator$Class$* class$;
};

extern void som$Interfaces$e873043a5e$Comparator$init$(struct som$Interfaces$e873043a5e$Comparator*);
struct som$Interfaces$e873043a5e$ForEachInterface {
    struct som$Interfaces$e873043a5e$ForEachInterface$Class$* class$;
};

extern void som$Interfaces$e873043a5e$ForEachInterface$init$(struct som$Interfaces$e873043a5e$ForEachInterface*);
struct som$Interfaces$e873043a5e$ForEachInterfaceRW {
    struct som$Interfaces$e873043a5e$ForEachInterfaceRW$Class$* class$;
};

extern void som$Interfaces$e873043a5e$ForEachInterfaceRW$init$(struct som$Interfaces$e873043a5e$ForEachInterfaceRW*);
void som$Interfaces$e873043a5e$ForEachInterface$apply(void* this, struct OBX$Array$1 elem);
void som$Interfaces$e873043a5e$ForEachInterfaceRW$apply(void* this, struct OBX$Array$1 elem);
uint8_t som$Interfaces$e873043a5e$TestInterface$test(void* this, struct OBX$Array$1 elem);
int32_t som$Interfaces$e873043a5e$Comparator$compare(void* this, struct OBX$Array$1 i, struct OBX$Array$1 j);
struct som$Interfaces$e873043a5e$TestInterface$Class$ {
    struct som$Interfaces$e873043a5e$TestInterface$Class$* super$;
    uint8_t (*test)(void* this, struct OBX$Array$1 elem);
};
extern struct som$Interfaces$e873043a5e$TestInterface$Class$ som$Interfaces$e873043a5e$TestInterface$class$;

struct som$Interfaces$e873043a5e$Comparator$Class$ {
    struct som$Interfaces$e873043a5e$Comparator$Class$* super$;
    int32_t (*compare)(void* this, struct OBX$Array$1 i, struct OBX$Array$1 j);
};
extern struct som$Interfaces$e873043a5e$Comparator$Class$ som$Interfaces$e873043a5e$Comparator$class$;

struct som$Interfaces$e873043a5e$ForEachInterface$Class$ {
    struct som$Interfaces$e873043a5e$ForEachInterface$Class$* super$;
    void (*apply)(void* this, struct OBX$Array$1 elem);
};
extern struct som$Interfaces$e873043a5e$ForEachInterface$Class$ som$Interfaces$e873043a5e$ForEachInterface$class$;

struct som$Interfaces$e873043a5e$ForEachInterfaceRW$Class$ {
    struct som$Interfaces$e873043a5e$ForEachInterfaceRW$Class$* super$;
    void (*apply)(void* this, struct OBX$Array$1 elem);
};
extern struct som$Interfaces$e873043a5e$ForEachInterfaceRW$Class$ som$Interfaces$e873043a5e$ForEachInterfaceRW$class$;

extern void som$Interfaces$e873043a5e$init$(void);
extern OBX$Cmd som$Interfaces$e873043a5e$cmd$(const char* name);
#endif