/*
 * This file is part of cparser.
 * Copyright (C) 2014 Matthias Braun <matze@braunis.de>
 */

#include "panic.h"
#include "strutil.h"
#include "util.h"
#include "dialect.h"
#include "type_t.h"
#include "types.h"
#include "c_driver.h"
#include "diagnostic.h"
#include "ast2ir.h"
#include "target.h"
#include "warning.h"

#include "hostdetect.h"

target_t target;

const char *multilib_directory_target_triple;
unsigned target_size_override;
bool set_wchar;
bool short_wchar;
bool unsigned_char;

struct TargetData target_data[] = {
    // all linkbin or linklib
    {"", "none", NoProcessor, false, 0, 0, 0, true, "undefined", "none"},
    {"amd32linux", "amd32", Amd32, false, 4, 4, 4, true, "Linux-based 32-bit systems", "dbgdwarf"}, // amd32run.obf amd32linuxrun.obf
    {"amd64linux", "amd64", Amd64, false, 8, 8, 4, true, "Linux-based 64-bit systems", "dbgdwarf"}, // amd64run.obf amd64linuxrun.obf
    {"arma32linux", "arma32", Arma32, true, 4, 4, 4, true, "Linux-based systems", "dbgdwarf"}, // arma32run.obf arma32linuxrun.obf
    {"arma64linux", "arma64", Arma64, true, 8, 16, 4, true, "Linux-based systems", "dbgdwarf"},
    {"armt32linux", "armt32", Armt32, true, 4, 4, 4, true, "Linux-based systems", "dbgdwarf"},
    {"armt32fpelinux", "armt32fpe", Armt32, true, 4, 4, 4, true, "Linux-based systems", "dbgdwarf"}, // armt32fperun.obf armt32fpelinuxrun.obf
    {"bios16", "amd16", Amd16, false, 2, 2, 2, false, "BIOS-based 16-bit systems"}, // amd16run.obf bios16run.obf
    {"bios32", "amd32", Amd32, false, 4, 4, 4, false, "BIOS-based 32-bit systems"},
    {"bios64", "amd64", Amd64, false, 8, 8, 4, false, "BIOS-based 64-bit systems"},
    {"dos", "amd16", Amd16, false, 2, 2, 2, false, "DOS systems"},
    {"efi32", "amd32", Amd32, false, 4, 4, 4, false, "EFI-based 32-bit systems"},
    {"efi64", "amd64", Amd64, false, 8, 8, 4, false, "EFI-based 64-bit systems"},
    {"osx32", "amd32", Amd32, false, 4, 4, 4, true, "32-bit OS X systems", "dbgdwarf"},
    {"osx64", "amd64", Amd64, false, 8, 8, 4, true, "64-bit OS X systems", "dbgdwarf"},
    {"rpi2b", "arma32", Arma32, true, 4, 4, 4, false, "Raspberry Pi 2 Model B"},
    {"win32", "amd32", Amd32, false, 4, 4, 4, false, "32-bit Windows systems"},
    {"win64", "amd64", Amd64, false, 8, 8, 4, false, "64-bit Windows systems"},
    {"amd16", "amd16", Amd16, false, 2, 2, 2, false, "barebone x86 real mode"},
    {"amd32", "amd32", Amd32, false, 4, 4, 4, false, "barebone x86 protected mode"},
    {"amd64", "amd64", Amd64, false, 8, 8, 4, false, "barebone x86 long mode"},
    {"arma32", "arma32", Arma32, true, 4, 4, 4, false, "barebone ARMv7"},
    {"armt32", "armt32", Armt32, true, 4, 4, 4, false, "barebone ARMv7 thumb"},
    {"arma64", "arma64", Arma64, true, 8, 16, 4, false, "barebone ARMv8"},
};

void set_target_option(char const *const arg)
{
    // TODO RK
}

void target_adjust_types_and_dialect(void)
{
    unsigned int_size     = 4;
    unsigned long_size    = target_data[target.target].pointer_width;
    unsigned pointer_size = target_data[target.target].pointer_width;;
    atomic_type_kind_t pointer_sized_int = ATOMIC_TYPE_LONG;
    atomic_type_kind_t pointer_sized_uint = ATOMIC_TYPE_ULONG;
    atomic_type_kind_t wchar_atomic_kind = ATOMIC_TYPE_USHORT;

    init_types(int_size, long_size, pointer_size, wchar_atomic_kind,
               pointer_sized_int, pointer_sized_uint);

}

void init_firm_target(void)
{
    memset(&target,0,sizeof(target));
#ifdef Q_PROCESSOR_ARM
#ifdef Q_OS_LINUX
target.target = sizeof(void*) == 8 ? ARMA64Linux : ARMA32Linux;
#elif defined Q_OS_MACOS
target.target = NoTarget; // TODO
#else
target.target = NoTarget;
#endif
#elif defined Q_PROCESSOR_X86
#ifdef Q_OS_LINUX
target.target = sizeof(void*) == 8 ? AMD64Linux : AMD32Linux;
#elif defined Q_OS_WIN32
target.target = sizeof(void*) == 8 ? Win64 : Win32;
#elif defined Q_OS_MACOS
target.target = sizeof(void*) == 8 ? OSX64 : OSX32;
#else
target.target = NoTarget;
#endif
#else
target.target = NoTarget;
#endif

}

bool target_setup(void)
{
    target.biggest_alignment     = 8;
    target.user_label_prefix     = '.';
    target.byte_order_big_endian = 1;
    target.name = target_data[target.target].name;
    return 1;
}

bool parse_target_triple(char const *const arg)
{
    bool found = false;
    for( int i = 1; i < MaxTarget; i++ )
    {
        if( strcmp(arg,target_data[i].name) == 0 )
        {
            target.target = i;
            found = true;
            break;
        }
    }
    return found;
}

unsigned char target_stack_align()
{
    return target_data[target.target].stack_align;
}

unsigned char target_pointer_width()
{
    return target_data[target.target].pointer_width;
}

unsigned char target_has_linkregister()
{
    return target_data[target.target].has_linkregister;
}
