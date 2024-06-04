#ifndef MIR_MIRIMP_H
#define MIR_MIRIMP_H

/* This file is a part of MIR project.
   Copyright (C) 2018-2024 Vladimir Makarov <vmakarov.gcc@gmail.com>.
*/
// This file is a subset of mir.c; it just includes common internal declarations

#include "mir.h"

typedef struct reg_desc {
  char *name; /* 1st key for the name2rdn hash tab */
  MIR_type_t type;
  MIR_reg_t reg; /* 1st key reg2rdn hash tab */
  char *hard_reg_name; /* NULL unless tied global, key for hrn2rdn */
} reg_desc_t;

struct insn_desc {
  MIR_insn_code_t code;
  const char *name;
  unsigned char op_modes[5];
};

extern const struct insn_desc insn_descs[];

DEF_VARR (size_t)
DEF_VARR (MIR_proto_t)
DEF_HTAB (MIR_item_t)
DEF_VARR (MIR_op_t)

struct MIR_context {
    int curr_label_num;
    DLIST (MIR_module_t) all_modules;
    struct string_ctx* string_ctx;
    VARR (size_t) * insn_nops;          /* constant after initialization */
    VARR (MIR_proto_t) * unspec_protos; /* protos of unspec insns (set only during initialization) */
    MIR_module_t curr_module;
    HTAB (MIR_item_t) * module_item_tab;
    MIR_func_t curr_func;
    struct hard_reg_ctx *hard_reg_ctx;
    VARR (MIR_op_t) * temp_ops;
    struct alias_ctx *alias_ctx;
};

extern reg_desc_t *get_func_rd_by_reg (MIR_context_t ctx, MIR_reg_t reg, MIR_func_t func);

#endif
