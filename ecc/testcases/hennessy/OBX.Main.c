// Generated by Oberon+ IDE (Mono) 0.9.107 on 2024-08-10T01:27:54

#include <locale.h>
#include "Main.h"
#include "Bubble.h"
#include "Oscar.h"
#include "Perm.h"
#include "Intmm.h"
#include "Queens.h"
#include "Mm.h"
#include "Trees.h"
#include "Quick.h"
#include "Towers.h"
#include "Util.h"
#include "Input.h"
#include "Out.h"

int main(int argc, char **argv) {
    setlocale(LC_ALL, "C.UTF-8");
    OBX$InitApp(argc,argv);
    OBX$RegisterModule("Main",Main$cmd$ );
    OBX$RegisterModule("Bubble",Bubble$cmd$ );
    OBX$RegisterModule("Oscar",Oscar$cmd$ );
    OBX$RegisterModule("Perm",Perm$cmd$ );
    OBX$RegisterModule("Intmm",Intmm$cmd$ );
    OBX$RegisterModule("Queens",Queens$cmd$ );
    OBX$RegisterModule("Mm",Mm$cmd$ );
    OBX$RegisterModule("Trees",Trees$cmd$ );
    OBX$RegisterModule("Quick",Quick$cmd$ );
    OBX$RegisterModule("Towers",Towers$cmd$ );
    OBX$RegisterModule("Util",Util$cmd$ );
    OBX$RegisterModule("Input",Input$cmd$ );
    OBX$RegisterModule("Out",Out$cmd$ );
    Main$init$();
    return 0;
}