#ifndef _SOM$INTERFACES$71499F4DFF_
#define _SOM$INTERFACES$71499F4DFF_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"

// Declaration of module som.Interfaces(Json.String)

struct som$Interfaces$71499f4dff$ForEachInterfaceRW$Class$;
struct som$Interfaces$71499f4dff$ForEachInterfaceRW;
struct som$Interfaces$71499f4dff$Comparator$Class$;
struct som$Interfaces$71499f4dff$Comparator;
struct som$Interfaces$71499f4dff$TestInterface$Class$;
struct som$Interfaces$71499f4dff$TestInterface;
struct som$Interfaces$71499f4dff$ForEachInterface$Class$;
struct som$Interfaces$71499f4dff$ForEachInterface;
struct som$Interfaces$71499f4dff$ForEachInterfaceRW {
    struct som$Interfaces$71499f4dff$ForEachInterfaceRW$Class$* class$;
};

extern void som$Interfaces$71499f4dff$ForEachInterfaceRW$init$(struct som$Interfaces$71499f4dff$ForEachInterfaceRW*);
struct som$Interfaces$71499f4dff$Comparator {
    struct som$Interfaces$71499f4dff$Comparator$Class$* class$;
};

extern void som$Interfaces$71499f4dff$Comparator$init$(struct som$Interfaces$71499f4dff$Comparator*);
struct som$Interfaces$71499f4dff$TestInterface {
    struct som$Interfaces$71499f4dff$TestInterface$Class$* class$;
};

extern void som$Interfaces$71499f4dff$TestInterface$init$(struct som$Interfaces$71499f4dff$TestInterface*);
struct som$Interfaces$71499f4dff$ForEachInterface {
    struct som$Interfaces$71499f4dff$ForEachInterface$Class$* class$;
};

extern void som$Interfaces$71499f4dff$ForEachInterface$init$(struct som$Interfaces$71499f4dff$ForEachInterface*);
void som$Interfaces$71499f4dff$ForEachInterface$apply(void* this, struct OBX$Array$1 * elem);
void som$Interfaces$71499f4dff$ForEachInterfaceRW$apply(void* this, struct OBX$Array$1 * elem);
uint8_t som$Interfaces$71499f4dff$TestInterface$test(void* this, struct OBX$Array$1 * elem);
int32_t som$Interfaces$71499f4dff$Comparator$compare(void* this, struct OBX$Array$1 * i, struct OBX$Array$1 * j);
struct som$Interfaces$71499f4dff$ForEachInterfaceRW$Class$ {
    struct som$Interfaces$71499f4dff$ForEachInterfaceRW$Class$* super$;
    void (*apply)(void* this, struct OBX$Array$1 * elem);
};
extern struct som$Interfaces$71499f4dff$ForEachInterfaceRW$Class$ som$Interfaces$71499f4dff$ForEachInterfaceRW$class$;

struct som$Interfaces$71499f4dff$Comparator$Class$ {
    struct som$Interfaces$71499f4dff$Comparator$Class$* super$;
    int32_t (*compare)(void* this, struct OBX$Array$1 * i, struct OBX$Array$1 * j);
};
extern struct som$Interfaces$71499f4dff$Comparator$Class$ som$Interfaces$71499f4dff$Comparator$class$;

struct som$Interfaces$71499f4dff$TestInterface$Class$ {
    struct som$Interfaces$71499f4dff$TestInterface$Class$* super$;
    uint8_t (*test)(void* this, struct OBX$Array$1 * elem);
};
extern struct som$Interfaces$71499f4dff$TestInterface$Class$ som$Interfaces$71499f4dff$TestInterface$class$;

struct som$Interfaces$71499f4dff$ForEachInterface$Class$ {
    struct som$Interfaces$71499f4dff$ForEachInterface$Class$* super$;
    void (*apply)(void* this, struct OBX$Array$1 * elem);
};
extern struct som$Interfaces$71499f4dff$ForEachInterface$Class$ som$Interfaces$71499f4dff$ForEachInterface$class$;

extern void som$Interfaces$71499f4dff$init$(void);
extern OBX$Cmd som$Interfaces$71499f4dff$cmd$(const char* name);
#endif
