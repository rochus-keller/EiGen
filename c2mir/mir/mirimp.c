/* This file is a part of MIR project.
   Copyright (C) 2018-2024 Vladimir Makarov <vmakarov.gcc@gmail.com>.
*/
// This file is a subset of mir.c; it just includes the functions to manage the AST
// during parsing

#include "mirimp.h"
#include "mir-hash.h"
#include "mir-bitmap.h"
#include <alloca.h>
#include <inttypes.h>

////////////////////////////////////
// Declarations

typedef struct string {
  size_t num; /* string number starting with 1 */
  MIR_str_t str;
} string_t;

DEF_VARR (MIR_insn_t)
DEF_VARR (MIR_reg_t)
DEF_VARR (MIR_type_t)
DEF_VARR (MIR_module_t)
DEF_VARR (char)
DEF_VARR (uint8_t)
DEF_VARR (MIR_str_t)
DEF_VARR (uint64_t)
DEF_VARR (MIR_label_t)
DEF_VARR (string_t)

DEF_HTAB (string_t)
DEF_HTAB (size_t)


struct string_ctx {
  VARR (string_t) * strings;
  HTAB (string_t) * string_tab;
};

#define strings ctx->string_ctx->strings
#define string_tab ctx->string_ctx->string_tab

DEF_VARR (reg_desc_t)

typedef struct func_regs {
  VARR (reg_desc_t) * reg_descs;
  HTAB (size_t) * name2rdn_tab;
  HTAB (size_t) * hrn2rdn_tab;
  HTAB (size_t) * reg2rdn_tab;
} *func_regs_t;

/* Functions to work with aliases.  */

struct alias_ctx {
  VARR (string_t) * aliases;
  HTAB (string_t) * alias_tab;
};

struct hard_reg_desc {
  const char *name;
  int num;
};
typedef struct hard_reg_desc hard_reg_desc_t;

DEF_HTAB (hard_reg_desc_t);

struct hard_reg_ctx {
  HTAB (hard_reg_desc_t) * hard_reg_desc_tab;
};

#define hard_reg_desc_tab ctx->hard_reg_ctx->hard_reg_desc_tab

static const char *const target_hard_reg_names[] = {
  "r0",  "r1",  "r2",  "r3",  "r4",  "r5",  "r6",  "r7" // TODO
};

#define OUT_FLAG (1 << 7)

const struct insn_desc insn_descs[] = {
  {MIR_MOV, "mov", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FMOV, "fmov", {MIR_OP_FLOAT | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DMOV, "dmov", {MIR_OP_DOUBLE | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDMOV, "ldmov", {MIR_OP_LDOUBLE | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_EXT8, "ext8", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_EXT16, "ext16", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_EXT32, "ext32", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UEXT8, "uext8", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UEXT16, "uext16", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UEXT32, "uext32", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_I2F, "i2f", {MIR_OP_FLOAT | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_I2D, "i2d", {MIR_OP_DOUBLE | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_I2LD, "i2ld", {MIR_OP_LDOUBLE | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UI2F, "ui2f", {MIR_OP_FLOAT | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UI2D, "ui2d", {MIR_OP_DOUBLE | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UI2LD, "ui2ld", {MIR_OP_LDOUBLE | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_F2I, "f2i", {MIR_OP_INT | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_D2I, "d2i", {MIR_OP_INT | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LD2I, "ld2i", {MIR_OP_INT | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_F2D, "f2d", {MIR_OP_DOUBLE | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_F2LD, "f2ld", {MIR_OP_LDOUBLE | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_D2F, "d2f", {MIR_OP_FLOAT | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_D2LD, "d2ld", {MIR_OP_LDOUBLE | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LD2F, "ld2f", {MIR_OP_FLOAT | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_LD2D, "ld2d", {MIR_OP_DOUBLE | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_NEG, "neg", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_NEGS, "negs", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FNEG, "fneg", {MIR_OP_FLOAT | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DNEG, "dneg", {MIR_OP_DOUBLE | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDNEG, "ldneg", {MIR_OP_LDOUBLE | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_ADDR, "addr", {MIR_OP_INT | OUT_FLAG, MIR_OP_REG, MIR_OP_BOUND}},     /* MIR_OP_REG! */
  {MIR_ADDR8, "addr8", {MIR_OP_INT | OUT_FLAG, MIR_OP_REG, MIR_OP_BOUND}},   /* MIR_OP_REG! */
  {MIR_ADDR16, "addr16", {MIR_OP_INT | OUT_FLAG, MIR_OP_REG, MIR_OP_BOUND}}, /* MIR_OP_REG! */
  {MIR_ADDR32, "addr32", {MIR_OP_INT | OUT_FLAG, MIR_OP_REG, MIR_OP_BOUND}}, /* MIR_OP_REG! */
  {MIR_ADD, "add", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_ADDS, "adds", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FADD, "fadd", {MIR_OP_FLOAT | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DADD, "dadd", {MIR_OP_DOUBLE | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDADD, "ldadd", {MIR_OP_LDOUBLE | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_SUB, "sub", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_SUBS, "subs", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FSUB, "fsub", {MIR_OP_FLOAT | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DSUB, "dsub", {MIR_OP_DOUBLE | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDSUB, "ldsub", {MIR_OP_LDOUBLE | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_MUL, "mul", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_MULS, "muls", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FMUL, "fmul", {MIR_OP_FLOAT | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DMUL, "dmul", {MIR_OP_DOUBLE | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDMUL, "ldmul", {MIR_OP_LDOUBLE | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_DIV, "div", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_DIVS, "divs", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UDIV, "udiv", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UDIVS, "udivs", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FDIV, "fdiv", {MIR_OP_FLOAT | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DDIV, "ddiv", {MIR_OP_DOUBLE | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDDIV, "lddiv", {MIR_OP_LDOUBLE | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_MOD, "mod", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_MODS, "mods", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UMOD, "umod", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UMODS, "umods", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_AND, "and", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_ANDS, "ands", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_OR, "or", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_ORS, "ors", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_XOR, "xor", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_XORS, "xors", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_LSH, "lsh", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_LSHS, "lshs", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_RSH, "rsh", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_RSHS, "rshs", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_URSH, "ursh", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_URSHS, "urshs", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_EQ, "eq", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_EQS, "eqs", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FEQ, "feq", {MIR_OP_INT | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DEQ, "deq", {MIR_OP_INT | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDEQ, "ldeq", {MIR_OP_INT | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_NE, "ne", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_NES, "nes", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FNE, "fne", {MIR_OP_INT | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DNE, "dne", {MIR_OP_INT | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDNE, "ldne", {MIR_OP_INT | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_LT, "lt", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_LTS, "lts", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_ULT, "ult", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_ULTS, "ults", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FLT, "flt", {MIR_OP_INT | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DLT, "dlt", {MIR_OP_INT | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDLT, "ldlt", {MIR_OP_INT | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_LE, "le", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_LES, "les", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_ULE, "ule", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_ULES, "ules", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FLE, "fle", {MIR_OP_INT | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DLE, "dle", {MIR_OP_INT | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDLE, "ldle", {MIR_OP_INT | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_GT, "gt", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_GTS, "gts", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UGT, "ugt", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UGTS, "ugts", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FGT, "fgt", {MIR_OP_INT | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DGT, "dgt", {MIR_OP_INT | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDGT, "ldgt", {MIR_OP_INT | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_GE, "ge", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_GES, "ges", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UGE, "uge", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UGES, "uges", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FGE, "fge", {MIR_OP_INT | OUT_FLAG, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DGE, "dge", {MIR_OP_INT | OUT_FLAG, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDGE, "ldge", {MIR_OP_INT | OUT_FLAG, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_ADDO, "addo", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_ADDOS, "addos", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_SUBO, "subo", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_SUBOS, "subos", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_MULO, "mulo", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_MULOS, "mulos", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UMULO, "umulo", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UMULOS, "umulos", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_JMP, "jmp", {MIR_OP_LABEL, MIR_OP_BOUND}},
  {MIR_BT, "bt", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_BTS, "bts", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_BF, "bf", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_BFS, "bfs", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_BEQ, "beq", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_BEQS, "beqs", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FBEQ, "fbeq", {MIR_OP_LABEL, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DBEQ, "dbeq", {MIR_OP_LABEL, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDBEQ, "ldbeq", {MIR_OP_LABEL, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_BNE, "bne", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_BNES, "bnes", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FBNE, "fbne", {MIR_OP_LABEL, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DBNE, "dbne", {MIR_OP_LABEL, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDBNE, "ldbne", {MIR_OP_LABEL, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_BLT, "blt", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_BLTS, "blts", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UBLT, "ublt", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UBLTS, "ublts", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FBLT, "fblt", {MIR_OP_LABEL, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DBLT, "dblt", {MIR_OP_LABEL, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDBLT, "ldblt", {MIR_OP_LABEL, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_BLE, "ble", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_BLES, "bles", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UBLE, "uble", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UBLES, "ubles", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FBLE, "fble", {MIR_OP_LABEL, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DBLE, "dble", {MIR_OP_LABEL, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDBLE, "ldble", {MIR_OP_LABEL, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_BGT, "bgt", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_BGTS, "bgts", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UBGT, "ubgt", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UBGTS, "ubgts", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FBGT, "fbgt", {MIR_OP_LABEL, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DBGT, "dbgt", {MIR_OP_LABEL, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDBGT, "ldbgt", {MIR_OP_LABEL, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_BGE, "bge", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_BGES, "bges", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UBGE, "ubge", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_UBGES, "ubges", {MIR_OP_LABEL, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_FBGE, "fbge", {MIR_OP_LABEL, MIR_OP_FLOAT, MIR_OP_FLOAT, MIR_OP_BOUND}},
  {MIR_DBGE, "dbge", {MIR_OP_LABEL, MIR_OP_DOUBLE, MIR_OP_DOUBLE, MIR_OP_BOUND}},
  {MIR_LDBGE, "ldbge", {MIR_OP_LABEL, MIR_OP_LDOUBLE, MIR_OP_LDOUBLE, MIR_OP_BOUND}},
  {MIR_BO, "bo", {MIR_OP_LABEL, MIR_OP_BOUND}},
  {MIR_UBO, "ubo", {MIR_OP_LABEL, MIR_OP_BOUND}},
  {MIR_BNO, "bno", {MIR_OP_LABEL, MIR_OP_BOUND}},
  {MIR_UBNO, "ubno", {MIR_OP_LABEL, MIR_OP_BOUND}},
  {MIR_LADDR, "laddr", {MIR_OP_INT, MIR_OP_LABEL, MIR_OP_BOUND}},
  {MIR_JMPI, "jmpi", {MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_CALL, "call", {MIR_OP_BOUND}},
  {MIR_INLINE, "inline", {MIR_OP_BOUND}},
  {MIR_JCALL, "jcall", {MIR_OP_BOUND}},
  {MIR_SWITCH, "switch", {MIR_OP_BOUND}},
  {MIR_RET, "ret", {MIR_OP_BOUND}},
  {MIR_JRET, "jret", {MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_ALLOCA, "alloca", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_BSTART, "bstart", {MIR_OP_INT | OUT_FLAG, MIR_OP_BOUND}},
  {MIR_BEND, "bend", {MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_VA_ARG, "va_arg", {MIR_OP_INT | OUT_FLAG, MIR_OP_INT, MIR_OP_UNDEF, MIR_OP_BOUND}},
  {MIR_VA_BLOCK_ARG,
   "va_block_arg",
   {MIR_OP_INT, MIR_OP_INT, MIR_OP_INT, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_VA_START, "va_start", {MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_VA_END, "va_end", {MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_LABEL, "label", {MIR_OP_BOUND}},
  {MIR_UNSPEC, "unspec", {MIR_OP_BOUND}},
  {MIR_PRSET, "prset", {MIR_OP_UNDEF, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_PRBEQ, "prbeq", {MIR_OP_LABEL, MIR_OP_UNDEF, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_PRBNE, "prbne", {MIR_OP_LABEL, MIR_OP_UNDEF, MIR_OP_INT, MIR_OP_BOUND}},
  {MIR_USE, "use", {MIR_OP_BOUND}},
  {MIR_PHI, "phi", {MIR_OP_BOUND}},
  {MIR_INVALID_INSN, "invalid-insn", {MIR_OP_BOUND}},
};

///////////////////////////////////////
// Implementation

void MIR_NO_RETURN default_error (MIR_error_type_t error_type, const char *format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    vfprintf(stderr,format,argptr);
    fprintf (stderr, "\n");
    va_end(argptr);
    exit(-1);
}

MIR_error_func_t MIR_get_error_func (MIR_context_t ctx)
{
    return default_error;
}

static int string_find (VARR (string_t) * *strs MIR_UNUSED, HTAB (string_t) * *str_tab,
                        MIR_str_t str, string_t *s) {
  string_t string;

  string.str = str;
  return HTAB_DO (string_t, *str_tab, string, HTAB_FIND, *s);
}

static string_t string_store (MIR_context_t ctx, VARR (string_t) * *strs,
                              HTAB (string_t) * *str_tab, MIR_str_t str) {
  char *heap_str;
  string_t el, string;

  if (string_find (strs, str_tab, str, &el)) return el;
  if ((heap_str = malloc (str.len)) == NULL)
    MIR_get_error_func (ctx) (MIR_alloc_error, "Not enough memory for strings");
  memcpy (heap_str, str.s, str.len);
  string.str.s = heap_str;
  string.str.len = str.len;
  string.num = VARR_LENGTH (string_t, *strs);
  VARR_PUSH (string_t, *strs, string);
  HTAB_DO (string_t, *str_tab, string, HTAB_INSERT, el);
  return string;
}

static struct string get_ctx_string (MIR_context_t ctx, MIR_str_t str) {
  return string_store (ctx, &strings, &string_tab, str);
}

static const char *get_ctx_str (MIR_context_t ctx, const char *string) {
  return get_ctx_string (ctx, (MIR_str_t){strlen (string) + 1, string}).str.s;
}

static const char *type_str (MIR_context_t ctx, MIR_type_t tp) {
  int n;
  char str[100];

  switch (tp) {
  case MIR_T_I8: return "i8";
  case MIR_T_U8: return "u8";
  case MIR_T_I16: return "i16";
  case MIR_T_U16: return "u16";
  case MIR_T_I32: return "i32";
  case MIR_T_U32: return "u32";
  case MIR_T_I64: return "i64";
  case MIR_T_U64: return "u64";
  case MIR_T_F: return "f";
  case MIR_T_D: return "d";
  case MIR_T_LD: return "ld";
  case MIR_T_P: return "p";
  case MIR_T_RBLK: return "rblk";
  case MIR_T_UNDEF: return "undef";
  default:
    if (MIR_blk_type_p (tp) && (n = tp - MIR_T_BLK) >= 0 && n < MIR_BLK_NUM) {
      sprintf (str, "blk%d", n);
      return get_ctx_str (ctx, str);
    }
    return "";
  }
}

const char *MIR_type_str (MIR_context_t ctx, MIR_type_t tp) {
  const char *str = type_str (ctx, tp);

  if (strcmp (str, "") == 0)
    MIR_get_error_func (ctx) (MIR_wrong_param_value_error, "MIR_type_str: wrong type");
  return str;
}

#define HARD_REG_NAME_PREFIX "hr"
#define TEMP_REG_NAME_PREFIX "t"
#define TEMP_ITEM_NAME_PREFIX ".lc"

int _MIR_reserved_ref_name_p (MIR_context_t ctx MIR_UNUSED, const char *name) {
  return strncmp (name, TEMP_ITEM_NAME_PREFIX, strlen (TEMP_ITEM_NAME_PREFIX)) == 0;
}

/* Reserved names:
   fp - frame pointer
   hr<number> - a hardware reg
   lc<number> - a temp item */
int _MIR_reserved_name_p (MIR_context_t ctx, const char *name) {
  size_t i, start;

  if (_MIR_reserved_ref_name_p (ctx, name))
    return TRUE;
  else if (strncmp (name, HARD_REG_NAME_PREFIX, strlen (HARD_REG_NAME_PREFIX)) == 0)
    start = strlen (HARD_REG_NAME_PREFIX);
  else
    return FALSE;
  for (i = start; name[i] != '\0'; i++)
    if (name[i] < '0' || name[i] > '9') return FALSE;
  return TRUE;
}

int _MIR_get_hard_reg (MIR_context_t ctx, const char *hard_reg_name) {
  hard_reg_desc_t desc, tab_desc;

  desc.name = hard_reg_name;
  if (!HTAB_DO (hard_reg_desc_t, hard_reg_desc_tab, desc, HTAB_FIND, tab_desc)) return -1;
  return tab_desc.num;
}

static inline int target_hard_reg_type_ok_p (MIR_reg_t hard_reg, MIR_type_t type) {
  return 0; // TODO
}

static inline int target_fixed_hard_reg_p (MIR_reg_t hard_reg) {
  return 0; // TODO
}

static int target_locs_num (MIR_reg_t loc MIR_UNUSED, MIR_type_t type) {
  return 0; // TODO
}

static MIR_reg_t create_func_reg (MIR_context_t ctx, MIR_func_t func, const char *name,
                                  const char *hard_reg_name, MIR_reg_t reg, MIR_type_t type,
                                  int any_p, char **name_ptr) {
  func_regs_t func_regs = func->internal;
  MIR_module_t func_module;
  reg_desc_t rd, *rd_ref;
  size_t rdn, tab_rdn;
  int htab_res;
  MIR_reg_t hr;

  if (!any_p && _MIR_reserved_name_p (ctx, name))
    MIR_get_error_func (ctx) (MIR_reserved_name_error, "redefining a reserved name %s", name);
  rd.name = (char *) get_ctx_str (ctx, name);
  if (hard_reg_name != NULL) hard_reg_name = get_ctx_str (ctx, hard_reg_name);
  rd.hard_reg_name = (char *) hard_reg_name;
  rd.type = type;
  rd.reg = reg; /* 0 is reserved */
  rdn = VARR_LENGTH (reg_desc_t, func_regs->reg_descs);
  VARR_PUSH (reg_desc_t, func_regs->reg_descs, rd);
  if (HTAB_DO (size_t, func_regs->name2rdn_tab, rdn, HTAB_FIND, tab_rdn)) {
    VARR_POP (reg_desc_t, func_regs->reg_descs);
    MIR_get_error_func (ctx) (MIR_repeated_decl_error, "Repeated reg declaration %s", name);
  }
  if (hard_reg_name != NULL) {
    if ((hr = _MIR_get_hard_reg (ctx, hard_reg_name)) == MIR_NON_VAR) {
      MIR_get_error_func (ctx) (MIR_hard_reg_error, "unknown hard reg %s", hard_reg_name);
    } else if (!target_hard_reg_type_ok_p (hr, type)) {
      MIR_get_error_func (ctx) (MIR_hard_reg_error,
                                "reg %s tied to hard reg %s can not be of type %s", name,
                                hard_reg_name, MIR_type_str (ctx, type));
    } else if (target_fixed_hard_reg_p (hr)) {
      MIR_get_error_func (ctx) (MIR_hard_reg_error,
                                "reg %s can not be tied to reserved hard reg %s", name,
                                hard_reg_name);
    } else if (target_locs_num (hr, type) > 1)
      MIR_get_error_func (ctx) (MIR_hard_reg_error, "reg %s tied to %s requires more one hard reg",
                                name, hard_reg_name);
    if (HTAB_DO (size_t, func_regs->hrn2rdn_tab, rdn, HTAB_FIND, tab_rdn)) {
      rd_ref = &VARR_ADDR (reg_desc_t, func_regs->reg_descs)[tab_rdn];
      if (type != rd_ref->type)
        MIR_get_error_func (ctx) (MIR_repeated_decl_error,
                                  "regs %s and %s tied to hard reg %s have different types", name,
                                  rd_ref->name, hard_reg_name);
      /* Use always one reg for global vars assigned to hard regs: */
      VARR_POP (reg_desc_t, func_regs->reg_descs);
      *name_ptr = rd_ref->name;
      return rd_ref->reg;
    }
    func_module = func->func_item->module;
    if (func_module->data == NULL) func_module->data = bitmap_create2 (128);
    bitmap_set_bit_p (func_module->data, hr); /* hard regs used for globals */
  }
  *name_ptr = rd.name;
  htab_res = HTAB_DO (size_t, func_regs->name2rdn_tab, rdn, HTAB_INSERT, tab_rdn);
  mir_assert (!htab_res);
  if (hard_reg_name != NULL) {
    htab_res = HTAB_DO (size_t, func_regs->hrn2rdn_tab, rdn, HTAB_INSERT, tab_rdn);
    mir_assert (!htab_res);
  }
  htab_res = HTAB_DO (size_t, func_regs->reg2rdn_tab, rdn, HTAB_INSERT, tab_rdn);
  mir_assert (!htab_res);
  return reg;
}

static MIR_reg_t new_func_reg (MIR_context_t ctx, MIR_func_t func, MIR_type_t type,
                               const char *name, const char *hard_reg_name) {
  MIR_var_t var;
  MIR_reg_t res, reg;
  char *stored_name;

  if (func == NULL)
    MIR_get_error_func (ctx) (MIR_reg_type_error, "func can not be NULL for new reg creation");
  if (type != MIR_T_I64 && type != MIR_T_F && type != MIR_T_D && type != MIR_T_LD)
    MIR_get_error_func (ctx) (MIR_reg_type_error, "wrong type for var %s: got '%s'", name,
                              type_str (ctx, type));
  reg = (MIR_reg_t) VARR_LENGTH (MIR_var_t, func->vars) + 1;
  if (func->global_vars != NULL) reg += (MIR_reg_t) VARR_LENGTH (MIR_var_t, func->global_vars);
  res = create_func_reg (ctx, func, name, hard_reg_name, reg, type, FALSE, &stored_name);
  if (res != reg) return res; /* already exists */
  var.type = type;
  var.name = stored_name;
  if (hard_reg_name == NULL) {
    VARR_PUSH (MIR_var_t, func->vars, var);
  } else {
    if (func->global_vars == NULL) VARR_CREATE (MIR_var_t, func->global_vars, 8);
    VARR_PUSH (MIR_var_t, func->global_vars, var);
  }
  return res;
}

MIR_reg_t MIR_new_func_reg (MIR_context_t ctx, MIR_func_t func, MIR_type_t type, const char *name)
{
    return new_func_reg (ctx, func, type, name, NULL);
}

static reg_desc_t *find_rd_by_name (MIR_context_t ctx MIR_UNUSED, const char *name,
                                    MIR_func_t func) {
  func_regs_t func_regs = func->internal;
  size_t rdn, temp_rdn;
  reg_desc_t rd;

  rd.name = (char *) name;
  rd.type = MIR_T_I64;
  rd.reg = 0; /* to eliminate warnings */
  temp_rdn = VARR_LENGTH (reg_desc_t, func_regs->reg_descs);
  VARR_PUSH (reg_desc_t, func_regs->reg_descs, rd);
  if (!HTAB_DO (size_t, func_regs->name2rdn_tab, temp_rdn, HTAB_FIND, rdn)) {
    VARR_POP (reg_desc_t, func_regs->reg_descs);
    return NULL; /* undeclared */
  }
  VARR_POP (reg_desc_t, func_regs->reg_descs);
  return &VARR_ADDR (reg_desc_t, func_regs->reg_descs)[rdn];
}

static reg_desc_t *get_func_rd_by_name (MIR_context_t ctx, const char *reg_name, MIR_func_t func) {
  reg_desc_t *rd;

  rd = find_rd_by_name (ctx, reg_name, func);
  if (rd == NULL)
    MIR_get_error_func (ctx) (MIR_undeclared_func_reg_error, "undeclared func reg %s", reg_name);
  return rd;
}

MIR_reg_t MIR_reg (MIR_context_t ctx, const char *reg_name, MIR_func_t func)
{
    return get_func_rd_by_name (ctx, reg_name, func)->reg;
}

static reg_desc_t *find_rd_by_reg (MIR_context_t ctx, MIR_reg_t reg, MIR_func_t func) {
  func_regs_t func_regs = func->internal;
  size_t rdn, temp_rdn;
  reg_desc_t rd;

  rd.reg = reg;
  rd.name = NULL;
  rd.type = MIR_T_I64; /* to eliminate warnings */
  temp_rdn = VARR_LENGTH (reg_desc_t, func_regs->reg_descs);
  VARR_PUSH (reg_desc_t, func_regs->reg_descs, rd);
  if (!HTAB_DO (size_t, func_regs->reg2rdn_tab, temp_rdn, HTAB_FIND, rdn)) {
    VARR_POP (reg_desc_t, func_regs->reg_descs);
    MIR_get_error_func (ctx) (MIR_undeclared_func_reg_error, "undeclared reg %u of func %s", reg,
                              func->name);
  }
  VARR_POP (reg_desc_t, func_regs->reg_descs);
  return &VARR_ADDR (reg_desc_t, func_regs->reg_descs)[rdn];
}

reg_desc_t *get_func_rd_by_reg (MIR_context_t ctx, MIR_reg_t reg, MIR_func_t func) {
  reg_desc_t *rd;

  rd = find_rd_by_reg (ctx, reg, func);
  return rd;
}

const char *MIR_reg_name (MIR_context_t ctx, MIR_reg_t reg, MIR_func_t func)
{
    return get_func_rd_by_reg (ctx, reg, func)->name;
}

#define insn_nops ctx->insn_nops

static size_t insn_code_nops (MIR_context_t ctx, MIR_insn_code_t code) { /* 0 for calls */
  if ((unsigned) code >= MIR_INSN_BOUND)
    MIR_get_error_func (ctx) (MIR_wrong_param_value_error, "insn_code_nops: wrong insn code %d",
                              (int) code);
  return VARR_GET (size_t, insn_nops, code);
}

static MIR_insn_t new_insn (MIR_context_t ctx, MIR_insn_code_t code, size_t nops, va_list argp) {
  MIR_op_t *insn_ops = alloca (sizeof (MIR_op_t) * nops);

  for (size_t i = 0; i < nops; i++) insn_ops[i] = va_arg (argp, MIR_op_t);
  va_end (argp);
  return MIR_new_insn_arr (ctx, code, nops, insn_ops);
}

MIR_insn_t MIR_new_insn (MIR_context_t ctx, MIR_insn_code_t code, ...)
{
    va_list argp;
    size_t nops = insn_code_nops (ctx, code);

    if (code == MIR_USE || code == MIR_PHI)
      MIR_get_error_func (ctx) (MIR_call_op_error,
                                "Use only MIR_new_insn_arr for creating use or phi insn");
    else if (MIR_call_code_p (code) || code == MIR_UNSPEC || code == MIR_RET || code == MIR_SWITCH)
      MIR_get_error_func (
        ctx) (MIR_call_op_error,
              "Use only MIR_new_insn_arr or MIR_new_{call,unspec,ret}_insn for creating a "
              "call/unspec/ret/jret/switch insn");
    va_start (argp, code);
    return new_insn (ctx, code, nops, argp);
}

static void init_op (MIR_op_t *op, MIR_op_mode_t mode) {
  op->mode = mode;
  op->data = NULL;
}

MIR_op_t MIR_new_reg_op (MIR_context_t ctx, MIR_reg_t reg)
{
    MIR_op_t op;

    init_op (&op, MIR_OP_REG);
    op.u.reg = reg;
    return op;
}

MIR_op_t MIR_new_float_op (MIR_context_t ctx, float f)
{
    MIR_op_t op;

    mir_assert (sizeof (float) == 4); /* IEEE single */
    init_op (&op, MIR_OP_FLOAT);
    op.u.f = f;
    return op;
}

MIR_op_t MIR_new_double_op (MIR_context_t ctx, double d)
{
    MIR_op_t op;

    mir_assert (sizeof (double) == 8); /* IEEE double */
    init_op (&op, MIR_OP_DOUBLE);
    op.u.d = d;
    return op;
}

MIR_op_t MIR_new_ldouble_op (MIR_context_t ctx, long double ld)
{
    MIR_op_t op;

  #if defined(_WIN32) || __SIZEOF_LONG_DOUBLE__ == 8
    return MIR_new_double_op (ctx, ld);
  #endif
    mir_assert (sizeof (long double) == 16); /* machine-defined 80- or 128-bit FP  */
    init_op (&op, MIR_OP_LDOUBLE);
    op.u.ld = ld;
    return op;
}

MIR_op_t MIR_new_int_op (MIR_context_t ctx, int64_t i)
{
    MIR_op_t op;

    init_op (&op, MIR_OP_INT);
    op.u.i = i;
    return op;
}

MIR_op_t MIR_new_uint_op (MIR_context_t ctx, uint64_t u)
{
    MIR_op_t op;

    init_op (&op, MIR_OP_UINT);
    op.u.u = u;
    return op;
}

static MIR_type_t canon_type (MIR_type_t type) {
#if defined(_WIN32) || __SIZEOF_LONG_DOUBLE__ == 8
  if (type == MIR_T_LD) type = MIR_T_D;
#endif
  return type;
}

static MIR_op_t new_mem_op (MIR_context_t ctx MIR_UNUSED, MIR_type_t type, MIR_disp_t disp,
                            MIR_reg_t base, MIR_reg_t index, MIR_scale_t scale, MIR_alias_t alias,
                            MIR_alias_t nonalias) {
  MIR_op_t op;

  init_op (&op, MIR_OP_MEM);
  op.u.mem.type = canon_type (type);
  op.u.mem.disp = disp;
  op.u.mem.base = base;
  op.u.mem.index = index;
  op.u.mem.scale = scale;
  op.u.mem.nloc = 0;
  op.u.mem.alias = alias;
  op.u.mem.nonalias = nonalias;
  return op;
}

MIR_op_t MIR_new_mem_op (MIR_context_t ctx, MIR_type_t type, MIR_disp_t disp, MIR_reg_t base,
                                MIR_reg_t index, MIR_scale_t scale)
{
    return new_mem_op (ctx, type, disp, base, index, scale, 0, 0);
}

MIR_insn_code_t MIR_reverse_branch_code (MIR_insn_code_t code)
{
    switch (code) {
    case MIR_BT: return MIR_BF;
    case MIR_BTS: return MIR_BFS;
    case MIR_BF: return MIR_BT;
    case MIR_BFS: return MIR_BTS;
    case MIR_BEQ: return MIR_BNE;
    case MIR_BEQS: return MIR_BNES;
    case MIR_BNE: return MIR_BEQ;
    case MIR_BNES: return MIR_BEQS;
    case MIR_BLT: return MIR_BGE;
    case MIR_BLTS: return MIR_BGES;
    case MIR_UBLT: return MIR_UBGE;
    case MIR_UBLTS: return MIR_UBGES;
    case MIR_BLE: return MIR_BGT;
    case MIR_BLES: return MIR_BGTS;
    case MIR_UBLE: return MIR_UBGT;
    case MIR_UBLES: return MIR_UBGTS;
    case MIR_BGT: return MIR_BLE;
    case MIR_BGTS: return MIR_BLES;
    case MIR_UBGT: return MIR_UBLE;
    case MIR_UBGTS: return MIR_UBLES;
    case MIR_BGE: return MIR_BLT;
    case MIR_BGES: return MIR_BLTS;
    case MIR_UBGE: return MIR_UBLT;
    case MIR_UBGES: return MIR_UBLTS;
    case MIR_BO: return MIR_BNO;
    case MIR_UBO: return MIR_UBNO;
    case MIR_BNO: return MIR_BO;
    case MIR_UBNO: return MIR_UBO;
    case MIR_PRBEQ: return MIR_PRBNE;
    case MIR_PRBNE: return MIR_PRBEQ;
    default: return MIR_INSN_BOUND;
    }
}

void MIR_append_insn (MIR_context_t ctx, MIR_item_t func_item, MIR_insn_t insn)
{
    mir_assert (func_item != NULL);
    if (func_item->item_type != MIR_func_item)
      MIR_get_error_func (ctx) (MIR_wrong_param_value_error, "MIR_append_insn: wrong func item");
    DLIST_APPEND (MIR_insn_t, func_item->u.func->insns, insn);
}

static void remove_insn (MIR_context_t ctx, MIR_item_t func_item, MIR_insn_t insn,
                         DLIST (MIR_insn_t) * insns) {
  mir_assert (func_item != NULL);
  if (func_item->item_type != MIR_func_item)
    MIR_get_error_func (ctx) (MIR_wrong_param_value_error, "MIR_remove_insn: wrong func item");
  DLIST_REMOVE (MIR_insn_t, *insns, insn);
  free (insn);
}

void MIR_remove_insn (MIR_context_t ctx, MIR_item_t func_item, MIR_insn_t insn)
{
    remove_insn (ctx, func_item, insn, &func_item->u.func->insns);
}

#define unspec_protos ctx->unspec_protos

static MIR_op_mode_t type2mode (MIR_type_t type) {
  return (type == MIR_T_UNDEF ? MIR_OP_UNDEF
          : type == MIR_T_F   ? MIR_OP_FLOAT
          : type == MIR_T_D   ? MIR_OP_DOUBLE
          : type == MIR_T_LD  ? MIR_OP_LDOUBLE
                              : MIR_OP_INT);
}

MIR_op_mode_t MIR_insn_op_mode (MIR_context_t ctx, MIR_insn_t insn, size_t nop, int *out_p)
{
    MIR_insn_code_t code = insn->code;
    size_t nargs, nops = MIR_insn_nops (ctx, insn);
    unsigned mode;

    *out_p = FALSE; /* to remove unitialized warning */
    if (nop >= nops) return MIR_OP_BOUND;
    mir_assert (out_p != NULL);
    switch (code) {
    case MIR_RET:
    case MIR_SWITCH:
      /* should be already checked in MIR_finish_func */
      return nop == 0 && code != MIR_RET ? MIR_OP_INT : insn->ops[nop].mode;
    case MIR_ADDR:
    case MIR_ADDR8:
    case MIR_ADDR16:
    case MIR_ADDR32: *out_p = nop == 0; return nop == 0 ? MIR_OP_INT : insn->ops[nop].mode;
    case MIR_PHI: *out_p = nop == 0; return insn->ops[nop].mode;
    case MIR_USE: return insn->ops[nop].mode;
    case MIR_CALL:
    case MIR_INLINE:
    case MIR_UNSPEC: {
      MIR_op_t proto_op;
      MIR_proto_t proto;
      size_t args_start;

      if (code == MIR_UNSPEC) {
        args_start = 1;
        mir_assert (insn->ops[0].mode == MIR_OP_INT);
        mir_assert (insn->ops[0].u.u < VARR_LENGTH (MIR_proto_t, unspec_protos));
        proto = VARR_GET (MIR_proto_t, unspec_protos, insn->ops[0].u.u);
      } else {
        args_start = 2;
        proto_op = insn->ops[0];
        mir_assert (proto_op.mode == MIR_OP_REF && proto_op.u.ref->item_type == MIR_proto_item);
        proto = proto_op.u.ref->u.proto;
      }
      *out_p = args_start <= nop && nop < proto->nres + args_start;
      nargs
        = proto->nres + args_start + (proto->args == NULL ? 0 : VARR_LENGTH (MIR_var_t, proto->args));
      if (proto->vararg_p && nop >= nargs) return MIR_OP_UNDEF; /* unknown */
      mir_assert (nops >= nargs && (proto->vararg_p || nops == nargs));
      if (nop == 0) return insn->ops[nop].mode;
      if (nop == 1 && code != MIR_UNSPEC) return MIR_OP_INT; /* call func addr */
      if (args_start <= nop && nop < proto->nres + args_start)
        return type2mode (proto->res_types[nop - args_start]);
      return type2mode (VARR_GET (MIR_var_t, proto->args, nop - args_start - proto->nres).type);
    }
    default:
      mode = insn_descs[code].op_modes[nop];
      if ((mode & OUT_FLAG) == 0) return mode;
      *out_p = TRUE;
      return mode ^ OUT_FLAG;
    }
}

size_t MIR_insn_nops (MIR_context_t ctx, MIR_insn_t insn)
{
    mir_assert (insn != NULL);
    return insn->nops;
}

static MIR_insn_t create_insn (MIR_context_t ctx, size_t nops, MIR_insn_code_t code) {
  MIR_insn_t insn;

  if (nops == 0) nops = 1;
  insn = malloc (sizeof (struct MIR_insn) + sizeof (MIR_op_t) * (nops - 1));
  if (insn == NULL)
    MIR_get_error_func (ctx) (MIR_alloc_error, "Not enough memory for insn creation");
#if defined(_WIN32) || __SIZEOF_LONG_DOUBLE__ == 8
  switch (code) {
  case MIR_LDMOV: code = MIR_DMOV; break;
  case MIR_I2LD: code = MIR_I2D; break;
  case MIR_UI2LD: code = MIR_UI2D; break;
  case MIR_LD2I: code = MIR_D2I; break;
  case MIR_F2LD: code = MIR_F2D; break;
  case MIR_D2LD: code = MIR_DMOV; break;
  case MIR_LD2F: code = MIR_D2F; break;
  case MIR_LD2D: code = MIR_DMOV; break;
  case MIR_LDNEG: code = MIR_DNEG; break;
  case MIR_LDADD: code = MIR_DADD; break;
  case MIR_LDSUB: code = MIR_DSUB; break;
  case MIR_LDMUL: code = MIR_DMUL; break;
  case MIR_LDDIV: code = MIR_DDIV; break;
  case MIR_LDEQ: code = MIR_DEQ; break;
  case MIR_LDNE: code = MIR_DNE; break;
  case MIR_LDLT: code = MIR_DLT; break;
  case MIR_LDLE: code = MIR_DLE; break;
  case MIR_LDGT: code = MIR_DGT; break;
  case MIR_LDGE: code = MIR_DGE; break;
  case MIR_LDBEQ: code = MIR_DBEQ; break;
  case MIR_LDBNE: code = MIR_DBNE; break;
  case MIR_LDBLT: code = MIR_DBLT; break;
  case MIR_LDBLE: code = MIR_DBLE; break;
  case MIR_LDBGT: code = MIR_DBGT; break;
  case MIR_LDBGE: code = MIR_DBGE; break;
  default: break;
  }
#endif
  insn->code = code;
  insn->data = NULL;
  return insn;
}

static MIR_insn_t new_insn1 (MIR_context_t ctx, MIR_insn_code_t code) {
  return create_insn (ctx, 1, code);
}

static MIR_insn_t create_label (MIR_context_t ctx, int64_t label_num) {
  MIR_insn_t insn = new_insn1 (ctx, MIR_LABEL);

  insn->ops[0] = MIR_new_int_op (ctx, label_num);
  insn->nops = 0;
  return insn;
}

#define curr_label_num ctx->curr_label_num

MIR_insn_t MIR_new_label (MIR_context_t ctx)
{
    return create_label (ctx, ++curr_label_num);
}

MIR_op_t MIR_new_label_op (MIR_context_t ctx, MIR_label_t label)
{
    MIR_op_t op;

    init_op (&op, MIR_OP_LABEL);
    op.u.label = label;
    return op;
}

const char *MIR_item_name (MIR_context_t ctx MIR_UNUSED, MIR_item_t item) {
  mir_assert (item != NULL);
  switch (item->item_type) {
  case MIR_func_item: return item->u.func->name;
  case MIR_proto_item: return item->u.proto->name;
  case MIR_import_item: return item->u.import_id;
  case MIR_export_item: return item->u.export_id;
  case MIR_forward_item: return item->u.forward_id;
  case MIR_bss_item: return item->u.bss->name;
  case MIR_data_item: return item->u.data->name;
  case MIR_ref_data_item: return item->u.ref_data->name;
  case MIR_lref_data_item: return item->u.lref_data->name;
  case MIR_expr_data_item: return item->u.expr_data->name;
  default: mir_assert (FALSE); return NULL;
  }
}

int MIR_op_eq_p (MIR_context_t ctx, MIR_op_t op1, MIR_op_t op2)
{
    if (op1.mode != op2.mode) return FALSE;
    switch (op1.mode) {
    case MIR_OP_REG: return op1.u.reg == op2.u.reg;
    case MIR_OP_VAR: return op1.u.var == op2.u.var;
    case MIR_OP_INT: return op1.u.i == op2.u.i;
    case MIR_OP_UINT: return op1.u.u == op2.u.u;
    case MIR_OP_FLOAT: return op1.u.f == op2.u.f;
    case MIR_OP_DOUBLE: return op1.u.d == op2.u.d;
    case MIR_OP_LDOUBLE: return op1.u.ld == op2.u.ld;
    case MIR_OP_REF:
      if (op1.u.ref->item_type == MIR_export_item || op1.u.ref->item_type == MIR_import_item)
        return strcmp (MIR_item_name (ctx, op1.u.ref), MIR_item_name (ctx, op2.u.ref)) == 0;
      return op1.u.ref == op2.u.ref;
    case MIR_OP_STR:
      return op1.u.str.len == op2.u.str.len && memcmp (op1.u.str.s, op2.u.str.s, op1.u.str.len) == 0;
    case MIR_OP_MEM:
      return (op1.u.mem.type == op2.u.mem.type && op1.u.mem.disp == op2.u.mem.disp
              && op1.u.mem.base == op2.u.mem.base && op1.u.mem.index == op2.u.mem.index
              && (op1.u.mem.index == 0 || op1.u.mem.scale == op2.u.mem.scale));
    case MIR_OP_VAR_MEM:
      return (op1.u.var_mem.type == op2.u.var_mem.type && op1.u.var_mem.disp == op2.u.var_mem.disp
              && op1.u.var_mem.base == op2.u.var_mem.base
              && op1.u.var_mem.index == op2.u.var_mem.index
              && (op1.u.var_mem.index == MIR_NON_VAR || op1.u.var_mem.scale == op2.u.var_mem.scale));
    case MIR_OP_LABEL: return op1.u.label == op2.u.label;
    default: mir_assert (FALSE); /* we should not have other operands here */
    }
    return FALSE;
}

const char *_MIR_uniq_string (MIR_context_t ctx, const char *str)
{
    return get_ctx_str (ctx, str);
}

#define curr_module ctx->curr_module

static int wrong_type_p (MIR_type_t type) { return type < MIR_T_I8 || type >= MIR_T_BLK; }

static MIR_item_t create_item (MIR_context_t ctx, MIR_item_type_t item_type,
                               const char *item_name) {
  MIR_item_t item;

  if (curr_module == NULL)
    MIR_get_error_func (ctx) (MIR_no_module_error, "%s outside module", item_name);
  if ((item = malloc (sizeof (struct MIR_item))) == NULL)
    MIR_get_error_func (ctx) (MIR_alloc_error, "Not enough memory for creation of item %s",
                              item_name);
  item->data = NULL;
  item->module = curr_module;
  item->item_type = item_type;
  item->ref_def = NULL;
  item->export_p = FALSE;
  item->section_head_p = FALSE;
  item->addr = NULL;
  return item;
}

static MIR_proto_t create_proto (MIR_context_t ctx, const char *name, size_t nres,
                                 MIR_type_t *res_types, size_t nargs, int vararg_p,
                                 MIR_var_t *args) {
  MIR_proto_t proto = malloc (sizeof (struct MIR_proto) + nres * sizeof (MIR_type_t));
  MIR_var_t arg;

  if (proto == NULL)
    MIR_get_error_func (ctx) (MIR_alloc_error, "Not enough memory for creation of proto %s", name);
  proto->name = get_ctx_str (ctx, name);
  proto->res_types = (MIR_type_t *) ((char *) proto + sizeof (struct MIR_proto));
  if (nres != 0) memcpy (proto->res_types, res_types, nres * sizeof (MIR_type_t));
  proto->nres = (uint32_t) nres;
  proto->vararg_p = vararg_p != 0;
  VARR_CREATE (MIR_var_t, proto->args, nargs);
  for (size_t i = 0; i < nargs; i++) {
    arg = args[i];
    arg.name = get_ctx_str (ctx, arg.name);
    VARR_PUSH (MIR_var_t, proto->args, arg);
  }
  return proto;
}

#define module_item_tab ctx->module_item_tab

static MIR_item_t item_tab_find (MIR_context_t ctx, const char *name, MIR_module_t module) {
  MIR_item_t tab_item;
  struct MIR_item item_s;
  struct MIR_func func_s;

  item_s.item_type = MIR_func_item;
  func_s.name = name;
  item_s.module = module;
  item_s.u.func = &func_s;
  if (HTAB_DO (MIR_item_t, module_item_tab, &item_s, HTAB_FIND, tab_item)) return tab_item;
  return NULL;
}

static MIR_item_t item_tab_insert (MIR_context_t ctx, MIR_item_t item) {
  MIR_item_t tab_item;

  HTAB_DO (MIR_item_t, module_item_tab, item, HTAB_INSERT, tab_item);
  return tab_item;
}

static void item_tab_remove (MIR_context_t ctx, MIR_item_t item) {
  HTAB_DO (MIR_item_t, module_item_tab, item, HTAB_DELETE, item);
}

static MIR_item_t add_item (MIR_context_t ctx, MIR_item_t item) {
  int replace_p;
  MIR_item_t tab_item;

  if ((tab_item = item_tab_find (ctx, MIR_item_name (ctx, item), item->module)) == NULL) {
    DLIST_APPEND (MIR_item_t, curr_module->items, item);
    HTAB_DO (MIR_item_t, module_item_tab, item, HTAB_INSERT, item);
    return item;
  }
  switch (tab_item->item_type) {
  case MIR_import_item:
    if (item->item_type != MIR_import_item)
      MIR_get_error_func (ctx) (MIR_import_export_error,
                                "existing module definition %s already defined as import",
                                tab_item->u.import_id);
    item = tab_item;
    break;
  case MIR_export_item:
  case MIR_forward_item:
    replace_p = FALSE;
    if (item->item_type == MIR_import_item) {
      MIR_get_error_func (ctx) (MIR_import_export_error, "export/forward of import %s",
                                item->u.import_id);
    } else if (item->item_type != MIR_export_item && item->item_type != MIR_forward_item) {
      replace_p = TRUE;
      DLIST_APPEND (MIR_item_t, curr_module->items, item);
    } else {
      if (tab_item->item_type == item->item_type)
        item = tab_item;
      else
        DLIST_APPEND (MIR_item_t, curr_module->items, item);
      if (item->item_type == MIR_export_item && tab_item->item_type == MIR_forward_item)
        replace_p = TRUE;
    }
    if (replace_p) { /* replace forward by export or export/forward by its definition: */
      tab_item->ref_def = item;
      if (tab_item->item_type == MIR_export_item) item->export_p = TRUE;
      item_tab_remove (ctx, tab_item);
      tab_item = item_tab_insert (ctx, item);
      mir_assert (item == tab_item);
    }
    break;
  case MIR_proto_item:
    MIR_get_error_func (ctx) (MIR_repeated_decl_error, "item %s was already defined as proto",
                              tab_item->u.proto->name);
    break;
  case MIR_bss_item:
  case MIR_data_item:
  case MIR_ref_data_item:
  case MIR_lref_data_item:
  case MIR_expr_data_item:
  case MIR_func_item:
    if (item->item_type == MIR_export_item) {
      if (tab_item->export_p) {
        item = tab_item;
      } else { /* just keep one export: */
        tab_item->export_p = TRUE;
        DLIST_APPEND (MIR_item_t, curr_module->items, item);
        item->ref_def = tab_item;
      }
    } else if (item->item_type == MIR_forward_item) {
      DLIST_APPEND (MIR_item_t, curr_module->items, item);
      item->ref_def = tab_item;
    } else if (item->item_type == MIR_import_item) {
      MIR_get_error_func (ctx) (MIR_import_export_error, "import of local definition %s",
                                item->u.import_id);
    } else {
      MIR_get_error_func (ctx) (MIR_repeated_decl_error, "Repeated item declaration %s",
                                MIR_item_name (ctx, item));
    }
    break;
  default: mir_assert (FALSE);
  }
  return item;
}

static MIR_item_t new_proto_arr (MIR_context_t ctx, const char *name, size_t nres,
                                 MIR_type_t *res_types, size_t nargs, int vararg_p,
                                 MIR_var_t *args) {
  MIR_item_t proto_item, tab_item;

  if (curr_module == NULL)
    MIR_get_error_func (ctx) (MIR_no_module_error, "Creating proto %s outside module", name);
  for (size_t i = 0; i < nres; i++)
    if (wrong_type_p (res_types[i]))
      MIR_get_error_func (ctx) (MIR_wrong_type_error, "wrong result type in proto %s", name);
  proto_item = create_item (ctx, MIR_proto_item, "proto");
  proto_item->u.proto = create_proto (ctx, name, nres, res_types, nargs, vararg_p, args);
  tab_item = add_item (ctx, proto_item);
  mir_assert (tab_item == proto_item);
  return proto_item;
}

MIR_item_t MIR_new_proto_arr (MIR_context_t ctx, const char *name, size_t nres,
                                     MIR_type_t *res_types, size_t nargs, MIR_var_t *args)
{
    return new_proto_arr (ctx, name, nres, res_types, nargs, FALSE, args);
}

static MIR_item_t new_export_import_forward (MIR_context_t ctx, const char *name,
                                             MIR_item_type_t item_type, const char *item_name,
                                             int create_only_p) {
  MIR_item_t item, tab_item;
  const char *uniq_name;

  item = create_item (ctx, item_type, item_name);
  uniq_name = get_ctx_str (ctx, name);
  if (item_type == MIR_export_item)
    item->u.export_id = uniq_name;
  else if (item_type == MIR_import_item)
    item->u.import_id = uniq_name;
  else
    item->u.forward_id = uniq_name;
  if (create_only_p) return item;
  if ((tab_item = add_item (ctx, item)) != item) {
    free (item);
    item = tab_item;
  }
  return item;
}

MIR_item_t MIR_new_import (MIR_context_t ctx, const char *name)
{
    return new_export_import_forward (ctx, name, MIR_import_item, "import", FALSE);
}

MIR_op_t MIR_new_ref_op (MIR_context_t ctx, MIR_item_t item)
{
    MIR_op_t op;

    init_op (&op, MIR_OP_REF);
    op.u.ref = item;
    return op;
}

MIR_insn_t MIR_new_insn_arr (MIR_context_t ctx, MIR_insn_code_t code, size_t nops,
                                    MIR_op_t *ops)
{
    MIR_insn_t insn;
    MIR_proto_t proto;
    size_t args_start, narg, i = 0, expected_nops = insn_code_nops (ctx, code);
    mir_assert (nops == 0 || ops != NULL);

    if (!MIR_call_code_p (code) && code != MIR_UNSPEC && code != MIR_USE && code != MIR_PHI
        && code != MIR_RET && code != MIR_SWITCH && nops != expected_nops) {
      MIR_get_error_func (ctx) (MIR_ops_num_error, "wrong number of operands for insn %s",
                                insn_descs[code].name);
    } else if (code == MIR_SWITCH) {
      if (nops < 2)
        MIR_get_error_func (ctx) (MIR_ops_num_error, "number of MIR_SWITCH operands is less 2");
    } else if (code == MIR_PHI) {
      if (nops < 3)
        MIR_get_error_func (ctx) (MIR_ops_num_error, "number of MIR_PHI operands is less 3");
    } else if (MIR_call_code_p (code) || code == MIR_UNSPEC) {
      args_start = code == MIR_UNSPEC ? 1 : 2;
      if (nops < args_start)
        MIR_get_error_func (ctx) (MIR_ops_num_error, "wrong number of call/unspec operands");
      if (code == MIR_UNSPEC) {
        if (ops[0].mode != MIR_OP_INT || ops[0].u.u >= VARR_LENGTH (MIR_proto_t, unspec_protos))
          MIR_get_error_func (ctx) (MIR_unspec_op_error,
                                    "the 1st unspec operand should be valid unspec code");
        proto = VARR_GET (MIR_proto_t, unspec_protos, ops[0].u.u);
      } else {
        if (ops[0].mode != MIR_OP_REF || ops[0].u.ref->item_type != MIR_proto_item)
          MIR_get_error_func (ctx) (MIR_call_op_error, "the 1st call operand should be a prototype");
        proto = ops[0].u.ref->u.proto;
      }
      i = proto->nres;
      if (proto->args != NULL) i += VARR_LENGTH (MIR_var_t, proto->args);
      if (nops < i + args_start || (nops != i + args_start && !proto->vararg_p))
        MIR_get_error_func (
          ctx) (code == MIR_UNSPEC ? MIR_unspec_op_error : MIR_call_op_error,
                "number of %s operands or results does not correspond to prototype %s",
                code == MIR_UNSPEC ? "unspec" : "call", proto->name);
      for (i = args_start; i < nops; i++) {
        if (ops[i].mode == MIR_OP_MEM && MIR_all_blk_type_p (ops[i].u.mem.type)) {
          if (i - args_start < proto->nres)
            MIR_get_error_func (ctx) (MIR_wrong_type_error, "result of %s is block type memory",
                                      code == MIR_UNSPEC ? "unspec" : "call");
          else if ((narg = i - args_start - proto->nres) < VARR_LENGTH (MIR_var_t, proto->args)) {
            if (VARR_GET (MIR_var_t, proto->args, narg).type != ops[i].u.mem.type) {
              MIR_get_error_func (
                ctx) (MIR_wrong_type_error,
                      "arg of %s is block type memory but param is not of block type",
                      code == MIR_UNSPEC ? "unspec" : "call");
            } else if (VARR_GET (MIR_var_t, proto->args, narg).size != (size_t) ops[i].u.mem.disp) {
              MIR_get_error_func (
                ctx) (MIR_wrong_type_error,
                      "different sizes (%lu vs %lu) of arg and param block memory in %s insn",
                      (unsigned long) VARR_GET (MIR_var_t, proto->args, narg).size,
                      (unsigned long) ops[i].u.mem.disp, code == MIR_UNSPEC ? "unspec" : "call");
            }
          } else if (ops[i].u.mem.type == MIR_T_RBLK) {
            MIR_get_error_func (ctx) (MIR_wrong_type_error,
                                      "RBLK memory can not correspond to unnamed param in %s insn",
                                      code == MIR_UNSPEC ? "unspec" : "call");
          }
        } else if (i - args_start >= proto->nres
                   && (narg = i - args_start - proto->nres) < VARR_LENGTH (MIR_var_t, proto->args)
                   && MIR_all_blk_type_p (VARR_GET (MIR_var_t, proto->args, narg).type)) {
          MIR_get_error_func (
            ctx) (MIR_wrong_type_error,
                  "param of %s is of block type but arg is not of block type memory",
                  code == MIR_UNSPEC ? "unspec" : "call");
        }
      }
    } else if (code == MIR_VA_ARG) {  // undef mem ???
      if (ops[2].mode != MIR_OP_MEM)
        MIR_get_error_func (ctx) (MIR_op_mode_error,
                                  "3rd operand of va_arg should be any memory with given type");
    } else if (code == MIR_PRSET) {
      if (ops[1].mode != MIR_OP_INT)
        MIR_get_error_func (ctx) (MIR_op_mode_error, "property should be a integer operand");
    } else if (code == MIR_PRBEQ || code == MIR_PRBNE) {
      if (ops[2].mode != MIR_OP_INT)
        MIR_get_error_func (ctx) (MIR_op_mode_error, "property should be a integer operand");
      if (ops[1].mode != MIR_OP_REG && ops[1].mode != MIR_OP_MEM)
        MIR_get_error_func (
          ctx) (MIR_op_mode_error,
                "2nd operand of property branch should be any memory or reg with given type");
    }
    insn = create_insn (ctx, nops, code);
    insn->nops = (unsigned int) nops;
    for (i = 0; i < nops; i++) insn->ops[i] = ops[i];
    return insn;
}

DLIST (MIR_module_t) * MIR_get_module_list (MIR_context_t ctx)
{
    return &ctx->all_modules;
}

static void init_module (MIR_context_t ctx, MIR_module_t m, const char *name) {
  m->data = NULL;
  m->last_temp_item_num = 0;
  m->name = get_ctx_str (ctx, name);
  DLIST_INIT (MIR_item_t, m->items);
}

MIR_module_t MIR_new_module (MIR_context_t ctx, const char *name)
{
    if (curr_module != NULL)
      MIR_get_error_func (ctx) (MIR_nested_module_error,
                                "Creating module when previous module %s is not finished",
                                curr_module->name);
    if ((curr_module = malloc (sizeof (struct MIR_module))) == NULL)
      MIR_get_error_func (ctx) (MIR_alloc_error, "Not enough memory for module %s creation", name);
    init_module (ctx, curr_module, name);
    //DLIST_APPEND (MIR_module_t, ctx->all_modules, curr_module);
    return curr_module;
}

void _MIR_get_temp_item_name (MIR_context_t ctx, MIR_module_t module, char *buff,
                                     size_t buff_len)
{
    if( module == NULL )
        module = curr_module;
    mir_assert (module != NULL);
    module->last_temp_item_num++;
    snprintf (buff, buff_len, "%s%u", TEMP_ITEM_NAME_PREFIX, (unsigned) module->last_temp_item_num);
}

MIR_item_t MIR_new_string_data (MIR_context_t ctx, const char *name,
                                       MIR_str_t str)
{
    return MIR_new_data (ctx, name, MIR_T_U8, str.len, str.s);
}

MIR_item_t MIR_new_data (MIR_context_t ctx, const char *name, MIR_type_t el_type, size_t nel,
                                const void *els)
{
    MIR_item_t tab_item, item = create_item (ctx, MIR_data_item, "data");
    MIR_data_t data;
    size_t el_len;

    if (wrong_type_p (el_type)) {
      free (item);
      MIR_get_error_func (ctx) (MIR_wrong_type_error, "wrong type in data %s", name);
    }
    el_len = _MIR_type_size (ctx, el_type);
    item->u.data = data = malloc (sizeof (struct MIR_data) + el_len * nel);
    if (data == NULL) {
      free (item);
      MIR_get_error_func (ctx) (MIR_alloc_error, "Not enough memory for creation of data %s",
                                name == NULL ? "" : name);
    }
    if (name != NULL) name = get_ctx_str (ctx, name);
    data->name = name;
    if (name == NULL) {
      DLIST_APPEND (MIR_item_t, curr_module->items, item);
    } else if ((tab_item = add_item (ctx, item)) != item) {
      free (item);
      item = tab_item;
    }
    data->el_type = canon_type (el_type);
    data->nel = nel;
    memcpy (data->u.els, els, el_len * nel);
    return item;
}

size_t _MIR_type_size (MIR_context_t ctx, MIR_type_t type)
{
    switch (type) {
    case MIR_T_I8: return sizeof (int8_t);
    case MIR_T_U8: return sizeof (uint8_t);
    case MIR_T_I16: return sizeof (int16_t);
    case MIR_T_U16: return sizeof (uint16_t);
    case MIR_T_I32: return sizeof (int32_t);
    case MIR_T_U32: return sizeof (uint32_t);
    case MIR_T_I64: return sizeof (int64_t);
    case MIR_T_U64: return sizeof (uint64_t);
    case MIR_T_F: return sizeof (float);
    case MIR_T_D: return sizeof (double);
    case MIR_T_LD: return sizeof (long double);
    case MIR_T_P: return sizeof (void *);
    default: mir_assert (FALSE); return 1;
    }
}

MIR_item_t MIR_new_bss (MIR_context_t ctx, const char *name, size_t len)
{
    MIR_item_t tab_item, item = create_item (ctx, MIR_bss_item, "bss");

    item->u.bss = malloc (sizeof (struct MIR_bss));
    if (item->u.bss == NULL) {
      free (item);
      MIR_get_error_func (ctx) (MIR_alloc_error, "Not enough memory for creation of bss %s", name);
    }
    if (name != NULL) name = get_ctx_str (ctx, name);
    item->u.bss->name = name;
    item->u.bss->len = len;
    if (name == NULL) {
      DLIST_APPEND (MIR_item_t, curr_module->items, item);
    } else if ((tab_item = add_item (ctx, item)) != item) {
      free (item);
      item = tab_item;
    }
    return item;
}

MIR_item_t MIR_new_ref_data (MIR_context_t ctx, const char *name, MIR_item_t ref_item, int64_t disp)
{
    MIR_item_t tab_item, item = create_item (ctx, MIR_ref_data_item, "ref data");
    MIR_ref_data_t ref_data;

    item->u.ref_data = ref_data = malloc (sizeof (struct MIR_ref_data));
    if (ref_data == NULL) {
      free (item);
      MIR_get_error_func (ctx) (MIR_alloc_error, "Not enough memory for creation of ref data %s",
                                name == NULL ? "" : name);
    }
    if (name != NULL) name = get_ctx_str (ctx, name);
    ref_data->name = name;
    ref_data->ref_item = ref_item;
    ref_data->disp = disp;
    if (name == NULL) {
      DLIST_APPEND (MIR_item_t, curr_module->items, item);
    } else if ((tab_item = add_item (ctx, item)) != item) {
      free (item);
      item = tab_item;
    }
    return item;
}

MIR_item_t MIR_new_export (MIR_context_t ctx, const char *name)
{
    return new_export_import_forward (ctx, name, MIR_export_item, "export", FALSE);
}

MIR_item_t MIR_new_forward (MIR_context_t ctx, const char *name)
{
    return new_export_import_forward (ctx, name, MIR_forward_item, "forward", FALSE);
}

MIR_op_t MIR_new_str_op (MIR_context_t ctx, MIR_str_t str)
{
    MIR_op_t op;

    init_op (&op, MIR_OP_STR);
    op.u.str = get_ctx_string (ctx, str).str;
    return op;
}

static int name2rdn_eq (size_t rdn1, size_t rdn2, void *arg) {
  func_regs_t func_regs = arg;
  reg_desc_t *addr = VARR_ADDR (reg_desc_t, func_regs->reg_descs);

  return strcmp (addr[rdn1].name, addr[rdn2].name) == 0;
}

static htab_hash_t name2rdn_hash (size_t rdn, void *arg) {
  func_regs_t func_regs = arg;
  reg_desc_t *addr = VARR_ADDR (reg_desc_t, func_regs->reg_descs);

  return (htab_hash_t) mir_hash (addr[rdn].name, strlen (addr[rdn].name), 0);
}

static int hrn2rdn_eq (size_t rdn1, size_t rdn2, void *arg) {
  func_regs_t func_regs = arg;
  reg_desc_t *addr = VARR_ADDR (reg_desc_t, func_regs->reg_descs);

  return strcmp (addr[rdn1].hard_reg_name, addr[rdn2].hard_reg_name) == 0;
}

static htab_hash_t hrn2rdn_hash (size_t rdn, void *arg) {
  func_regs_t func_regs = arg;
  reg_desc_t *addr = VARR_ADDR (reg_desc_t, func_regs->reg_descs);

  return (htab_hash_t) mir_hash (addr[rdn].hard_reg_name, strlen (addr[rdn].hard_reg_name), 0);
}

static int reg2rdn_eq (size_t rdn1, size_t rdn2, void *arg) {
  func_regs_t func_regs = arg;
  reg_desc_t *addr = VARR_ADDR (reg_desc_t, func_regs->reg_descs);

  return addr[rdn1].reg == addr[rdn2].reg;
}

static htab_hash_t reg2rdn_hash (size_t rdn, void *arg) {
  func_regs_t func_regs = arg;
  reg_desc_t *addr = VARR_ADDR (reg_desc_t, func_regs->reg_descs);

  return (htab_hash_t) mir_hash_finish (mir_hash_step (mir_hash_init (0), addr[rdn].reg));
}

static void func_regs_init (MIR_context_t ctx, MIR_func_t func) {
  func_regs_t func_regs;
  reg_desc_t rd = {MIR_T_I64, 0, NULL, NULL};

  if ((func_regs = func->internal = malloc (sizeof (struct func_regs))) == NULL)
    MIR_get_error_func (ctx) (MIR_alloc_error, "Not enough memory for func regs info");
  VARR_CREATE (reg_desc_t, func_regs->reg_descs, 50);
  VARR_PUSH (reg_desc_t, func_regs->reg_descs, rd); /* for 0 reg */
  HTAB_CREATE (size_t, func_regs->name2rdn_tab, 100, name2rdn_hash, name2rdn_eq, func_regs);
  HTAB_CREATE (size_t, func_regs->hrn2rdn_tab, 10, hrn2rdn_hash, hrn2rdn_eq, func_regs);
  HTAB_CREATE (size_t, func_regs->reg2rdn_tab, 100, reg2rdn_hash, reg2rdn_eq, func_regs);
}

static MIR_item_t new_func_arr (MIR_context_t ctx, const char *name, size_t nres,
                                MIR_type_t *res_types, size_t nargs, int vararg_p,
                                MIR_var_t *vars) {
  MIR_item_t func_item, tab_item;
  MIR_func_t func;

  if (ctx->curr_func != NULL)
    MIR_get_error_func (ctx) (MIR_nested_func_error,
                              "Creating function when previous function %s is not finished",
                              ctx->curr_func->name);
  if (nargs == 0 && vararg_p)
    MIR_get_error_func (ctx) (MIR_vararg_func_error,
                              "Variable arg function %s w/o any mandatory argument", name);
  for (size_t i = 0; i < nres; i++)
    if (wrong_type_p (res_types[i]))
      MIR_get_error_func (ctx) (MIR_wrong_type_error, "wrong result type in func %s", name);
  func_item = create_item (ctx, MIR_func_item, "function");
  ctx->curr_func = func_item->u.func = func
    = malloc (sizeof (struct MIR_func) + nres * sizeof (MIR_type_t));
  if (func == NULL) {
    free (func_item);
    MIR_get_error_func (ctx) (MIR_alloc_error, "Not enough memory for creation of func %s", name);
  }
  func->name = get_ctx_str (ctx, name);
  func->func_item = func_item;
  func->nres = (uint32_t) nres;
  func->res_types = (MIR_type_t *) ((char *) func + sizeof (struct MIR_func));
  for (size_t i = 0; i < nres; i++) func->res_types[i] = canon_type (res_types[i]);
  tab_item = add_item (ctx, func_item);
  mir_assert (tab_item == func_item);
  DLIST_INIT (MIR_insn_t, func->insns);
  DLIST_INIT (MIR_insn_t, func->original_insns);
  VARR_CREATE (MIR_var_t, func->vars, nargs + 8);
  func->global_vars = NULL;
  func->nargs = (uint32_t) nargs;
  func->last_temp_num = 0;
  func->vararg_p = vararg_p != 0;
  func->expr_p = func->jret_p = FALSE;
  func->n_inlines = 0;
  func->machine_code = func->call_addr = NULL;
  func->first_lref = NULL;
  func_regs_init (ctx, func);
  for (size_t i = 0; i < nargs; i++) {
    char *stored_name;
    MIR_type_t type = canon_type (vars[i].type);
    MIR_reg_t reg
      = create_func_reg (ctx, func, vars[i].name, NULL, (MIR_reg_t) (i + 1),
                         type == MIR_T_F || type == MIR_T_D || type == MIR_T_LD ? type : MIR_T_I64,
                         FALSE, &stored_name);
    mir_assert (i + 1 == reg);
    vars[i].name = stored_name;
    VARR_PUSH (MIR_var_t, func->vars, vars[i]);
  }
  return func_item;
}

MIR_item_t MIR_new_func_arr (MIR_context_t ctx, const char *name, size_t nres,
                                    MIR_type_t *res_types, size_t nargs, MIR_var_t *vars)
{
    return new_func_arr (ctx, name, nres, res_types, nargs, FALSE, vars);
}

MIR_item_t MIR_new_vararg_func_arr (MIR_context_t ctx, const char *name, size_t nres,
                                           MIR_type_t *res_types, size_t nargs, MIR_var_t *vars)
{
    return new_func_arr (ctx, name, nres, res_types, nargs, TRUE, vars);
}

MIR_insn_t MIR_new_ret_insn (MIR_context_t ctx, size_t nops, ...)
{
    va_list argp;

    va_start (argp, nops);
    return new_insn (ctx, MIR_RET, nops, argp);
}

static const char *mode_str (MIR_op_mode_t mode) {
  switch (mode) {
  case MIR_OP_REG: return "reg";
  case MIR_OP_VAR: return "var";
  case MIR_OP_INT: return "int";
  case MIR_OP_UINT: return "uint";
  case MIR_OP_FLOAT: return "float";
  case MIR_OP_DOUBLE: return "double";
  case MIR_OP_LDOUBLE: return "ldouble";
  case MIR_OP_REF: return "ref";
  case MIR_OP_STR: return "str";
  case MIR_OP_MEM: return "mem";
  case MIR_OP_VAR_MEM: return "var_mem";
  case MIR_OP_LABEL: return "label";
  case MIR_OP_BOUND: return "bound";
  case MIR_OP_UNDEF: return "undef";
  default: return "";
  }
}

void MIR_finish_func (MIR_context_t ctx)
{
    int expr_p = TRUE;
    MIR_insn_t insn, prev_insn;
    MIR_insn_code_t code;
    const char *func_name;
    int ret_p = FALSE, jret_p = FALSE;

    if (ctx->curr_func == NULL)
      MIR_get_error_func (ctx) (MIR_no_func_error, "finish of non-existing function");
    func_name = ctx->curr_func->name;
    if (ctx->curr_func->vararg_p || ctx->curr_func->nargs != 0 || ctx->curr_func->nres != 1) expr_p = FALSE;
    for (insn = DLIST_HEAD (MIR_insn_t, ctx->curr_func->insns); insn != NULL;
         insn = DLIST_NEXT (MIR_insn_t, insn)) {
      size_t i, actual_nops = MIR_insn_nops (ctx, insn);
      MIR_op_mode_t mode, expected_mode;
      reg_desc_t *rd;
      int out_p, can_be_out_p;

      code = insn->code;
      if (code == MIR_RET) ret_p = TRUE;
      if (code == MIR_JRET) jret_p = TRUE;
      if (code == MIR_PHI || code == MIR_USE) {
        ctx->curr_func = NULL;
        MIR_get_error_func (ctx) (MIR_vararg_func_error, "use or phi can be used only internally");
      } else if (!ctx->curr_func->vararg_p && code == MIR_VA_START) {
        ctx->curr_func = NULL;
        MIR_get_error_func (ctx) (MIR_vararg_func_error, "va_start is not in vararg function");
      } else if (code == MIR_JRET && ctx->curr_func->nres != 0) {
        ctx->curr_func = NULL;
        MIR_get_error_func (
          ctx) (MIR_vararg_func_error,
                "func %s: in insn '%s': function should not have results in this case", func_name,
                insn_descs[code].name);
      } else if ((code == MIR_JRET && ret_p) || (code == MIR_RET && jret_p)) {
        ctx->curr_func = NULL;
        MIR_get_error_func (ctx) (MIR_vararg_func_error, "func %s: mix of RET and JRET insns",
                                  func_name);
      } else if (code == MIR_RET && actual_nops != ctx->curr_func->nres) {
        ctx->curr_func = NULL;
        MIR_get_error_func (
          ctx) (MIR_vararg_func_error,
                "func %s: in instruction '%s': number of operands in return does not "
                "correspond number of function returns. Expected %d, got %d",
                func_name, insn_descs[code].name, ctx->curr_func->nres, actual_nops);
      } else if (MIR_call_code_p (code)) {
        expr_p = FALSE;
      } else if (code == MIR_BO || code == MIR_UBO || code == MIR_BNO || code == MIR_UBNO) {
        for (prev_insn = DLIST_PREV (MIR_insn_t, insn); prev_insn != NULL;
             prev_insn = DLIST_PREV (MIR_insn_t, prev_insn))
          if (prev_insn->code != MIR_MOV || prev_insn->ops[1].mode != MIR_OP_REG) break;
        if (prev_insn == NULL || !MIR_overflow_insn_code_p (prev_insn->code))
          MIR_get_error_func (ctx) (MIR_invalid_insn_error,
                                    "func %s: instruction '%s' has no previous overflow insn "
                                    "separated only by stores and reg moves",
                                    func_name, insn_descs[code].name);
        else if ((code == MIR_UBO || code == MIR_UBNO)
                 && (prev_insn->code == MIR_MULO || prev_insn->code == MIR_MULOS))
          MIR_get_error_func (
            ctx) (MIR_invalid_insn_error,
                  "func %s: unsigned overflow branch '%s' consumes flag of signed overflow insn '%s'",
                  func_name, insn_descs[code].name, insn_descs[prev_insn->code].name);
        else if ((code == MIR_BO || code == MIR_BNO)
                 && (prev_insn->code == MIR_UMULO || prev_insn->code == MIR_UMULOS))
          MIR_get_error_func (
            ctx) (MIR_invalid_insn_error,
                  "func %s: signed overflow branch '%s' consumes flag of unsigned overflow insn '%s'",
                  func_name, insn_descs[code].name, insn_descs[prev_insn->code].name);
      }
      for (i = 0; i < actual_nops; i++) {
        if (code == MIR_UNSPEC && i == 0) {
          mir_assert (insn->ops[i].mode == MIR_OP_INT);
          continue;
        } else if (MIR_call_code_p (code)) {
          if (i == 0) {
            mir_assert (insn->ops[i].mode == MIR_OP_REF
                        && insn->ops[i].u.ref->item_type == MIR_proto_item);
            continue; /* We checked the operand during insn creation -- skip the prototype */
          } else if (i == 1 && insn->ops[i].mode == MIR_OP_REF) {
            mir_assert (insn->ops[i].u.ref->item_type == MIR_import_item
                        || insn->ops[i].u.ref->item_type == MIR_export_item
                        || insn->ops[i].u.ref->item_type == MIR_forward_item
                        || insn->ops[i].u.ref->item_type == MIR_func_item);
            continue; /* We checked the operand during insn creation -- skip the func */
          }
        }
        if (code == MIR_VA_ARG && i == 2) {
          mir_assert (insn->ops[i].mode == MIR_OP_MEM);
          continue; /* We checked the operand during insn creation -- skip va_arg type  */
        }
        if (code == MIR_SWITCH) {
          out_p = FALSE;
          expected_mode = i == 0 ? MIR_OP_INT : MIR_OP_LABEL;
        } else if (code == MIR_RET) {
          out_p = FALSE;
          expected_mode = type2mode (ctx->curr_func->res_types[i]);
        } else {
          expected_mode = MIR_insn_op_mode (ctx, insn, i, &out_p);
        }
        can_be_out_p = TRUE;
        switch (insn->ops[i].mode) {
        case MIR_OP_REG:
          rd = find_rd_by_reg (ctx, insn->ops[i].u.reg, ctx->curr_func);
          mir_assert (rd != NULL && insn->ops[i].u.reg == rd->reg);
          mode = type2mode (rd->type);
          break;
        case MIR_OP_MEM:
          expr_p = FALSE;
          if (wrong_type_p (insn->ops[i].u.mem.type)
              && (!MIR_all_blk_type_p (insn->ops[i].u.mem.type) || !MIR_call_code_p (code))) {
            ctx->curr_func = NULL;
            MIR_get_error_func (ctx) (MIR_wrong_type_error,
                                      "func %s: in instruction '%s': wrong type memory", func_name,
                                      insn_descs[code].name);
          }
          if (MIR_all_blk_type_p (insn->ops[i].u.mem.type) && insn->ops[i].u.mem.disp < 0) {
            ctx->curr_func = NULL;
            MIR_get_error_func (ctx) (MIR_wrong_type_error,
                                      "func %s: in instruction '%s': block type memory with disp < 0",
                                      func_name, insn_descs[code].name);
          }
          if (insn->ops[i].u.mem.base != 0) {
            rd = find_rd_by_reg (ctx, insn->ops[i].u.mem.base, ctx->curr_func);
            mir_assert (rd != NULL && insn->ops[i].u.mem.base == rd->reg);
            if (type2mode (rd->type) != MIR_OP_INT) {
              ctx->curr_func = NULL;
              MIR_get_error_func (
                ctx) (MIR_reg_type_error,
                      "func %s: in instruction '%s': base reg of non-integer type for operand "
                      "#%d",
                      func_name, insn_descs[code].name, i + 1);
            }
          }
          if (insn->ops[i].u.mem.index != 0) {
            rd = find_rd_by_reg (ctx, insn->ops[i].u.mem.index, ctx->curr_func);
            mir_assert (rd != NULL && insn->ops[i].u.mem.index == rd->reg);
            if (type2mode (rd->type) != MIR_OP_INT) {
              ctx->curr_func = NULL;
              MIR_get_error_func (
                ctx) (MIR_reg_type_error,
                      "func %s: in instruction '%s': index reg of non-integer type for "
                      "operand #%d",
                      func_name, insn_descs[code].name, i + 1);
            }
          }
          mode = type2mode (insn->ops[i].u.mem.type);
          break;
        case MIR_OP_VAR:
        case MIR_OP_VAR_MEM:
          expr_p = FALSE;
          mode = expected_mode;
          mir_assert (FALSE); /* Should not be here */
          break;
        default:
          can_be_out_p = FALSE;
          mode = insn->ops[i].mode;
          if (mode == MIR_OP_REF || mode == MIR_OP_STR) mode = MIR_OP_INT; /* just an address */
          break;
        }
        insn->ops[i].value_mode = mode;
        if (mode == MIR_OP_UNDEF && insn->ops[i].mode == MIR_OP_MEM
            && ((code == MIR_VA_START && i == 0)
                || ((code == MIR_VA_ARG || code == MIR_VA_BLOCK_ARG) && i == 1)
                || (code == MIR_VA_END && i == 1))) { /* a special case: va_list as undef type mem */
          insn->ops[i].value_mode = expected_mode;
        } else if (expected_mode == MIR_OP_REG) {
          if (insn->ops[i].mode != MIR_OP_REG && insn->ops[i].mode != MIR_OP_VAR)
            MIR_get_error_func (
              ctx) (MIR_op_mode_error,
                    "func %s: in instruction '%s': expected reg for operand #%d. Got '%s'", func_name,
                    insn_descs[code].name, i + 1, mode_str (insn->ops[i].mode));
        } else if (expected_mode != MIR_OP_UNDEF
                   && (mode == MIR_OP_UINT ? MIR_OP_INT : mode) != expected_mode) {
          ctx->curr_func = NULL;
          MIR_get_error_func (
            ctx) (MIR_op_mode_error,
                  "func %s: in instruction '%s': unexpected operand mode for operand #%d. Got "
                  "'%s', expected '%s'",
                  func_name, insn_descs[code].name, i + 1, mode_str (mode), mode_str (expected_mode));
        }
        if (out_p && !can_be_out_p) {
          ctx->curr_func = NULL;
          MIR_get_error_func (ctx) (MIR_out_op_error,
                                    "func %s; in instruction '%s': wrong operand #%d for insn output",
                                    func_name, insn_descs[code].name, i + 1);
        }
      }
    }
    if (!ret_p && !jret_p
        && ((insn = DLIST_TAIL (MIR_insn_t, ctx->curr_func->insns)) == NULL || insn->code != MIR_JMP)) {
      VARR_TRUNC (MIR_op_t, ctx->temp_ops, 0);
      for (size_t i = 0; i < ctx->curr_func->nres; i++) { /* add absent ret */
        MIR_op_t op;
        if (ctx->curr_func->res_types[i] == MIR_T_F)
          op = MIR_new_float_op (ctx, 0.0f);
        else if (ctx->curr_func->res_types[i] == MIR_T_D)
          op = MIR_new_double_op (ctx, 0.0);
        else if (ctx->curr_func->res_types[i] == MIR_T_LD)
          op = MIR_new_ldouble_op (ctx, 0.0);
        else
          op = MIR_new_int_op (ctx, 0);
        VARR_PUSH (MIR_op_t, ctx->temp_ops, op);
      }
      MIR_append_insn (ctx, ctx->curr_func->func_item,
                       MIR_new_insn_arr (ctx, MIR_RET, ctx->curr_func->nres,
                                         VARR_ADDR (MIR_op_t, ctx->temp_ops)));
    }
    ctx->curr_func->expr_p = expr_p;
    ctx->curr_func->jret_p = jret_p;
    ctx->curr_func = NULL;
}

MIR_item_t MIR_new_vararg_proto_arr (MIR_context_t ctx, const char *name, size_t nres,
                                            MIR_type_t *res_types, size_t nargs, MIR_var_t *args)
{
    return new_proto_arr (ctx, name, nres, res_types, nargs, TRUE, args);
}

int _MIR_name_char_p (MIR_context_t ctx, int ch, int first_p)
{
    if (isalpha (ch) || ch == '_' || ch == '$' || ch == '%' || ch == '.') return TRUE;
    return !first_p && isdigit (ch);
}

MIR_op_t MIR_new_alias_mem_op (MIR_context_t ctx, MIR_type_t type, MIR_disp_t disp,
                                      MIR_reg_t base, MIR_reg_t index, MIR_scale_t scale,
                                      MIR_alias_t alias, MIR_alias_t nonalias)
{
    return new_mem_op (ctx, type, disp, base, index, scale, alias, nonalias);
}

#define aliases ctx->alias_ctx->aliases
#define alias_tab ctx->alias_ctx->alias_tab

MIR_alias_t MIR_alias (MIR_context_t ctx, const char *name)
{
    return (MIR_alias_t) string_store (ctx, &aliases, &alias_tab,
                                       (MIR_str_t){strlen (name) + 1, name}).num;
}

const char *MIR_alias_name (MIR_context_t ctx, MIR_alias_t alias)
{
    if (alias == 0) return "";
    if (alias >= VARR_LENGTH (string_t, aliases))
      MIR_get_error_func (ctx) (MIR_alloc_error, "Wrong alias number");
    return VARR_ADDR (string_t, aliases)[alias].str.s;
}

MIR_item_t MIR_new_lref_data (MIR_context_t ctx, const char *name, MIR_label_t label,
                                     MIR_label_t label2,
                                     int64_t disp)
{
    MIR_item_t tab_item, item = create_item (ctx, MIR_lref_data_item, "lref data");
    MIR_lref_data_t lref_data;

    if (label == NULL) {
      free (item);
      MIR_get_error_func (ctx) (MIR_alloc_error, "null label for lref data %s",
                                name == NULL ? "" : name);
    }
    item->u.lref_data = lref_data = malloc (sizeof (struct MIR_lref_data));
    if (lref_data == NULL) {
      free (item);
      MIR_get_error_func (ctx) (MIR_alloc_error, "Not enough memory for creation of lref data %s",
                                name == NULL ? "" : name);
    }
    if (name != NULL) name = get_ctx_str (ctx, name);
    lref_data->name = name;
    lref_data->label = label;
    lref_data->label2 = label2;
    lref_data->disp = disp;
    lref_data->orig_label = lref_data->orig_label2 = NULL;
    lref_data->next = NULL;
    if (name == NULL) {
      DLIST_APPEND (MIR_item_t, curr_module->items, item);
    } else if ((tab_item = add_item (ctx, item)) != item) {
      free (item);
      item = tab_item;
    }
    return item;
}

MIR_reg_t MIR_new_global_func_reg (MIR_context_t ctx, MIR_func_t func, MIR_type_t type,
                                          const char *name, const char *hard_reg_name)
{
    if (hard_reg_name == NULL)
      MIR_get_error_func (ctx) (MIR_hard_reg_error,
                                "global var %s should have non-null hard reg name", name);
    return new_func_reg (ctx, func, type, name, hard_reg_name);
}

void MIR_finish_module (MIR_context_t ctx)
{
    if (curr_module == NULL)
      MIR_get_error_func (ctx) (MIR_no_module_error, "finish of non-existing module");
    curr_module = NULL;
}

static void remove_func_insns (MIR_context_t ctx, MIR_item_t func_item,
                               DLIST (MIR_insn_t) * insns) {
  MIR_insn_t insn;

  mir_assert (func_item->item_type == MIR_func_item);
  while ((insn = DLIST_HEAD (MIR_insn_t, *insns)) != NULL) {
    remove_insn (ctx, func_item, insn, insns);
  }
}

static void func_regs_finish (MIR_context_t ctx MIR_UNUSED, MIR_func_t func) {
  func_regs_t func_regs = func->internal;

  VARR_DESTROY (reg_desc_t, func_regs->reg_descs);
  HTAB_DESTROY (size_t, func_regs->name2rdn_tab);
  HTAB_DESTROY (size_t, func_regs->hrn2rdn_tab);
  HTAB_DESTROY (size_t, func_regs->reg2rdn_tab);
  free (func->internal);
  func->internal = NULL;
}

static void remove_item (MIR_context_t ctx, MIR_item_t item) {
  switch (item->item_type) {
  case MIR_func_item:
    remove_func_insns (ctx, item, &item->u.func->insns);
    remove_func_insns (ctx, item, &item->u.func->original_insns);
    VARR_DESTROY (MIR_var_t, item->u.func->vars);
    if (item->u.func->global_vars != NULL) VARR_DESTROY (MIR_var_t, item->u.func->global_vars);
    func_regs_finish (ctx, item->u.func);
    free (item->u.func);
    break;
  case MIR_proto_item:
    VARR_DESTROY (MIR_var_t, item->u.proto->args);
    free (item->u.proto);
    break;
  case MIR_import_item:
  case MIR_export_item:
  case MIR_forward_item: break;
  case MIR_data_item:
    if (item->addr != NULL && item->section_head_p) free (item->addr);
    free (item->u.data);
    break;
  case MIR_ref_data_item:
    if (item->addr != NULL && item->section_head_p) free (item->addr);
    free (item->u.ref_data);
    break;
  case MIR_lref_data_item:
    if (item->addr != NULL && item->section_head_p) free (item->addr);
    free (item->u.lref_data);
    break;
  case MIR_expr_data_item:
    if (item->addr != NULL && item->section_head_p) free (item->addr);
    free (item->u.expr_data);
    break;
  case MIR_bss_item:
    if (item->addr != NULL && item->section_head_p) free (item->addr);
    free (item->u.bss);
    break;
  default: mir_assert (FALSE);
  }
  if (item->data != NULL) free (item->data);
  free (item);
}

static void remove_module (MIR_context_t ctx, MIR_module_t module, int free_module_p) {
  MIR_item_t item;

  while ((item = DLIST_HEAD (MIR_item_t, module->items)) != NULL) {
    DLIST_REMOVE (MIR_item_t, module->items, item);
    remove_item (ctx, item);
  }
  if (module->data != NULL) bitmap_destroy (module->data);
  if (free_module_p) free (module);
}

static void remove_all_modules (MIR_context_t ctx) {
  MIR_module_t module;

  while ((module = DLIST_HEAD (MIR_module_t, ctx->all_modules)) != NULL) {
    DLIST_REMOVE (MIR_module_t, ctx->all_modules, module);
    remove_module (ctx, module, TRUE);
  }
  //remove_module (ctx, &environment_module, FALSE);
}

static void hard_reg_name_finish (MIR_context_t ctx) {
  HTAB_DESTROY (hard_reg_desc_t, hard_reg_desc_tab);
  free (ctx->hard_reg_ctx);
  ctx->hard_reg_ctx = NULL;
}

static void string_finish (VARR (string_t) * *strs, HTAB (string_t) * *str_tab) {
  size_t i;

  for (i = 1; i < VARR_LENGTH (string_t, *strs); i++)
    free ((char *) VARR_ADDR (string_t, *strs)[i].str.s);
  VARR_DESTROY (string_t, *strs);
  HTAB_DESTROY (string_t, *str_tab);
}

void MIR_finish (MIR_context_t ctx)
{
    //interp_finish (ctx);
    remove_all_modules (ctx);
    HTAB_DESTROY (MIR_item_t, module_item_tab);
    //VARR_DESTROY (MIR_module_t, modules_to_link);
    VARR_DESTROY (MIR_op_t, ctx->temp_ops);
  #if !MIR_NO_SCAN
    //scan_finish (ctx);
  #endif
  #if !MIR_NO_IO
    //io_finish (ctx);
  #endif
    //VARR_DESTROY (uint8_t, temp_data);
    //VARR_DESTROY (uint8_t, used_label_p);
    //VARR_DESTROY (char, temp_string);
    while (VARR_LENGTH (MIR_proto_t, unspec_protos) != 0) {
      MIR_proto_t proto = VARR_POP (MIR_proto_t, unspec_protos);
      VARR_DESTROY (MIR_var_t, proto->args);
      free (proto);
    }
    VARR_DESTROY (MIR_proto_t, unspec_protos);
    string_finish (&strings, &string_tab);
    string_finish (&aliases, &alias_tab);
    //simplify_finish (ctx);
    VARR_DESTROY (size_t, insn_nops);
    //code_finish (ctx);
    hard_reg_name_finish (ctx);
    if (ctx->curr_func != NULL)
      MIR_get_error_func (ctx) (MIR_finish_error, "finish when function %s is not finished",
                                ctx->curr_func->name);
    if (curr_module != NULL)
      MIR_get_error_func (ctx) (MIR_finish_error, "finish when module %s is not finished",
                                curr_module->name);
    free (ctx->string_ctx);
    free (ctx->alias_ctx);
    free (ctx);
    ctx = NULL;
}

static htab_hash_t item_hash (MIR_item_t it, void *arg MIR_UNUSED) {
  return (htab_hash_t) mir_hash_finish (
    mir_hash_step (mir_hash_step (mir_hash_init (28), (uint64_t) MIR_item_name (NULL, it)),
                   (uint64_t) it->module));
}
static int item_eq (MIR_item_t it1, MIR_item_t it2, void *arg MIR_UNUSED) {
  return it1->module == it2->module && MIR_item_name (NULL, it1) == MIR_item_name (NULL, it2);
}

static htab_hash_t str_hash (string_t str, void *arg MIR_UNUSED) {
  return (htab_hash_t) mir_hash (str.str.s, str.str.len, 0);
}
static int str_eq (string_t str1, string_t str2, void *arg MIR_UNUSED) {
  return str1.str.len == str2.str.len && memcmp (str1.str.s, str2.str.s, str1.str.len) == 0;
}

static void string_init (VARR (string_t) * *strs, HTAB (string_t) * *str_tab) {
  string_t string = {0, {0, NULL}};

  VARR_CREATE (string_t, *strs, 0);
  VARR_PUSH (string_t, *strs, string); /* don't use 0th string */
  HTAB_CREATE (string_t, *str_tab, 1000, str_hash, str_eq, NULL);
}

static htab_hash_t hard_reg_desc_hash (hard_reg_desc_t desc, void *arg MIR_UNUSED) {
  return (htab_hash_t) mir_hash (desc.name, strlen (desc.name), 0);
}
static int hard_reg_desc_eq (hard_reg_desc_t desc1, hard_reg_desc_t desc2, void *arg MIR_UNUSED) {
  return strcmp (desc1.name, desc2.name) == 0;
}

static void hard_reg_name_init (MIR_context_t ctx) {
  hard_reg_desc_t desc, tab_desc;
  int res;

  if ((ctx->hard_reg_ctx = malloc (sizeof (struct hard_reg_ctx))) == NULL)
    MIR_get_error_func (ctx) (MIR_alloc_error, "Not enough memory for ctx");
  HTAB_CREATE (hard_reg_desc_t, hard_reg_desc_tab, 200, hard_reg_desc_hash, hard_reg_desc_eq, NULL);
  for (size_t i = 0; i * sizeof (char *) < sizeof (target_hard_reg_names); i++) {
    desc.num = (int) i;
    desc.name = target_hard_reg_names[i];
    res = HTAB_DO (hard_reg_desc_t, hard_reg_desc_tab, desc, HTAB_INSERT, tab_desc);
    mir_assert (!res);
  }
}

static void check_and_prepare_insn_descs (MIR_context_t ctx) {
  size_t i, j;

  VARR_CREATE (size_t, insn_nops, 0);
  for (i = 0; i < MIR_INSN_BOUND; i++) {
    mir_assert (insn_descs[i].code == i);
    for (j = 0; insn_descs[i].op_modes[j] != MIR_OP_BOUND; j++)
      ;
    VARR_PUSH (size_t, insn_nops, j);
  }
}

MIR_context_t _MIR_init (void)
{
    MIR_context_t ctx;

     mir_assert (MIR_OP_BOUND < OUT_FLAG);
     if ((ctx = malloc (sizeof (struct MIR_context))) == NULL)
       default_error (MIR_alloc_error, "Not enough memory for ctx");
     ctx->string_ctx = NULL;
     ctx->alias_ctx = NULL;
     //ctx->reg_ctx = NULL;
     //ctx->simplify_ctx = NULL;
     //ctx->machine_code_ctx = NULL;
     //ctx->io_ctx = NULL;
     //ctx->scan_ctx = NULL;
     ctx->hard_reg_ctx = NULL;
     //ctx->interp_ctx = NULL;
   #ifndef NDEBUG
     for (MIR_insn_code_t c = 0; c < MIR_INVALID_INSN; c++) mir_assert (c == insn_descs[c].code);
   #endif
     //error_func = default_error;
     //func_redef_permission_p = FALSE;
     curr_module = NULL;
     ctx->curr_func = NULL;
     curr_label_num = 0;
     if ((ctx->string_ctx = malloc (sizeof (struct string_ctx))) == NULL
         || (ctx->alias_ctx = malloc (sizeof (struct string_ctx))) == NULL)
       MIR_get_error_func (ctx) (MIR_alloc_error, "Not enough memory for ctx");
     string_init (&strings, &string_tab);
     string_init (&aliases, &alias_tab);
     VARR_CREATE (MIR_proto_t, unspec_protos, 0);
     check_and_prepare_insn_descs (ctx);
     DLIST_INIT (MIR_module_t, ctx->all_modules);
     //simplify_init (ctx);
     //VARR_CREATE (char, temp_string, 64);
     //VARR_CREATE (uint8_t, temp_data, 512);
     //VARR_CREATE (uint8_t, used_label_p, 512);
   #if !MIR_NO_IO
     //io_init (ctx);
   #endif
   #if !MIR_NO_SCAN
     //scan_init (ctx);
   #endif
     //VARR_CREATE (MIR_module_t, modules_to_link, 0);
     VARR_CREATE (MIR_op_t, ctx->temp_ops, 0);
     //init_module (ctx, &environment_module, ".environment");
     HTAB_CREATE (MIR_item_t, module_item_tab, 512, item_hash, item_eq, NULL);
     //setjmp_addr = NULL;
     //code_init (ctx);
     //wrapper_end_addr = _MIR_get_wrapper_end (ctx); /* should be after code_init */
     hard_reg_name_init (ctx);
     //interp_init (ctx);
     return ctx;
}

double _MIR_get_api_version (void)
{
    return MIR_API_VERSION;
}

MIR_context_t MIR_init (void) {
    const double a = _MIR_get_api_version();
    const double b = MIR_API_VERSION;
    if (a != b) {
        fprintf (stderr,
                 "mir.h header has version %g different from used mir code version %g -- good bye!\n",
                 b, a);
        exit (1);
    }
    return _MIR_init ();
}


