/*
 * This file is part of cparser.
 * Copyright (C) 2014 Matthias Braun <matze@braunis.de>
 */
#ifndef TARGET_H
#define TARGET_H

#include <stdbool.h>
//#include <libfirm/irmode.h>
//#include <libfirm/target.h>

#include "util.h"
#include "options.h"

typedef enum {NoTarget, AMD32Linux, AMD64Linux, ARMA32Linux, ARMA64Linux, ARMT32Linux, ARMT32FPELinux,
              BIOS16, BIOS32, BIOS64, DOS, EFI32, EFI64, OSX32, OSX64, RPi2B, Win32, Win64,
              BareAmd16, BareAmd32, BareAmd64, BareArmA32, BareArmT32, BareArmA64,
              MaxTarget} TargetCode;
typedef enum { NoProcessor, Amd16, Amd32, Amd64, Arma32, Armt32, Arma64} ProcessorCode;

struct TargetData
{
    const char*const name;
    const char*const backend;
    ProcessorCode architecture;
    bool has_linkregister; // 0, 1
    unsigned char pointer_width; // 2, 4, 8
    unsigned char stack_align; // 4, 8, 16
    unsigned char int_width; // usually 4
    const bool executable;
    const char*const description;
    const char*const converter;
};
extern struct TargetData target_data[];

typedef struct target_t {
	char          user_label_prefix;
	unsigned char biggest_alignment;
	bool pic                   : 1;
	bool set_pic               : 1;
	bool pic_noplt             : 1;
	bool set_noplt             : 1;
	bool byte_order_big_endian : 1;
	bool set_use_frame_pointer : 1;
	bool use_frame_pointer     : 1;
    bool debug_info            : 1;

    TargetCode target;
    const char* name;
} target_t;

extern target_t target;

extern unsigned char target_stack_align();
extern unsigned char target_pointer_width();
extern unsigned char target_has_linkregister();

void init_firm_target(void);
bool target_setup(void);

void target_adjust_types_and_dialect(void);

void set_target_option(char const *arg);

typedef struct codegen_option_t codegen_option_t;
struct codegen_option_t {
	codegen_option_t *next;
	char              option[];
};

//extern optimization_level_t opt_level;
extern codegen_option_t    *codegen_options;
extern codegen_option_t   **codegen_options_anchor;
extern bool                 profile_generate;
extern bool                 profile_use;
extern const char          *multilib_directory_target_triple;
extern unsigned             target_size_override;
extern bool                 set_wchar;
extern bool                 short_wchar;
extern bool                 unsigned_char;

#endif
