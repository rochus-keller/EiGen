// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.IdentityDictionary2.df63a5a394.h"
#include "DeltaBlue.h"

struct som$Dictionary2$5c466e54b6$Dictionary * som$IdentityDictionary2$df63a5a394$create() {
    return som$Dictionary2$5c466e54b6$create();
}

struct som$Dictionary2$5c466e54b6$Dictionary * som$IdentityDictionary2$df63a5a394$createWithSize(int32_t size) {
    return som$Dictionary2$5c466e54b6$createWithSize(size);
}

static int initDone$ = 0;
void som$IdentityDictionary2$df63a5a394$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    som$Dictionary2$5c466e54b6$init$();
}
OBX$Cmd som$IdentityDictionary2$df63a5a394$cmd$(const char* name) {
    if( name == 0 ) return som$IdentityDictionary2$df63a5a394$init$;
    return 0;
}
