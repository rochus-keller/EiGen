/* This file is a part of MIR project.
   Copyright (C) 2018-2024 Vladimir Makarov <vmakarov.gcc@gmail.com>.
*/
// This file is a subset of mir.c; it just includes the functions to
// render the AST to a textual IR representation

#include "mirimp.h"
#include <inttypes.h>
#include <ctype.h>
#include <float.h>

void MIR_output_str (MIR_context_t ctx MIR_UNUSED, FILE *f, MIR_str_t str) {
  fprintf (f, "\"");
  for (size_t i = 0; i < str.len; i++)
    if (str.s[i] == '\\')
      fprintf (f, "\\\\");
    else if (str.s[i] == '"')
      fprintf (f, "\\\"");
    else if (isprint (str.s[i]))
      fprintf (f, "%c", str.s[i]);
    else if (str.s[i] == '\n')
      fprintf (f, "\\n");
    else if (str.s[i] == '\t')
      fprintf (f, "\\t");
    else if (str.s[i] == '\v')
      fprintf (f, "\\v");
    else if (str.s[i] == '\a')
      fprintf (f, "\\a");
    else if (str.s[i] == '\b')
      fprintf (f, "\\b");
    else if (str.s[i] == '\f')
      fprintf (f, "\\f");
    else
      fprintf (f, "\\%03o", (unsigned char) str.s[i]);
  fprintf (f, "\"");
}

void _MIR_output_data_item_els (MIR_context_t ctx, FILE *f, MIR_item_t item, int c_p) {
  mir_assert (item->item_type == MIR_data_item);
  MIR_data_t data = item->u.data;
  for (size_t i = 0; i < data->nel; i++) {
    switch (data->el_type) {
    case MIR_T_I8: fprintf (f, "%" PRId8, ((int8_t *) data->u.els)[i]); break;
    case MIR_T_U8: fprintf (f, "%" PRIu8, ((uint8_t *) data->u.els)[i]); break;
    case MIR_T_I16: fprintf (f, "%" PRId16, ((int16_t *) data->u.els)[i]); break;
    case MIR_T_U16: fprintf (f, "%" PRIu16, ((uint16_t *) data->u.els)[i]); break;
    case MIR_T_I32: fprintf (f, "%" PRId32, ((int32_t *) data->u.els)[i]); break;
    case MIR_T_U32: fprintf (f, "%" PRIu32, ((uint32_t *) data->u.els)[i]); break;
    case MIR_T_I64: fprintf (f, "%" PRId64, ((int64_t *) data->u.els)[i]); break;
    case MIR_T_U64: fprintf (f, "%" PRIu64, ((uint64_t *) data->u.els)[i]); break;
    case MIR_T_F: fprintf (f, "%.*ef", FLT_MANT_DIG, ((float *) data->u.els)[i]); break;
    case MIR_T_D: fprintf (f, "%.*e", DBL_MANT_DIG, ((double *) data->u.els)[i]); break;
    case MIR_T_LD:
      fprintf (f, "%.*LeL", LDBL_MANT_DIG, ((long double *) data->u.els)[i]);
      break;
      /* only ptr as ref ??? */
    case MIR_T_P: fprintf (f, "0x%" PRIxPTR, ((uintptr_t *) data->u.els)[i]); break;
    default: mir_assert (FALSE);
    }
    if (i + 1 < data->nel) fprintf (f, ", ");
  }
  if (data->el_type == MIR_T_U8 && data->nel != 0 && data->u.els[data->nel - 1] == '\0') {
    fprintf (f, c_p ? "/* " : " # "); /* print possible string as a comment */
    MIR_output_str (ctx, f, (MIR_str_t){data->nel, (char *) data->u.els});
    if (c_p) fprintf (f, " */");
  }
}

const char *MIR_reg_hard_reg_name (MIR_context_t ctx, MIR_reg_t reg, MIR_func_t func) {
  const reg_desc_t *rd = get_func_rd_by_reg (ctx, reg, func);
  return rd->hard_reg_name;
}

static void output_vars (MIR_context_t ctx, FILE *f, MIR_func_t func, VARR (MIR_var_t) * vars,
                         size_t start, size_t vars_num, const char *prefix) {
  if (vars == NULL || vars_num == 0) return;
  for (size_t i = 0; i < vars_num; i++) {
    MIR_var_t var = VARR_GET (MIR_var_t, vars, i + start);
    if (i % 8 == 0) {
      if (i != 0) fprintf (f, "\n");
      fprintf (f, "\t%s\t", prefix);
    }
    if (i % 8 != 0) fprintf (f, ", ");
    fprintf (f, "%s:%s", MIR_type_str (ctx, var.type), var.name);
    MIR_reg_t reg = MIR_reg (ctx, var.name, func);
    const char *hard_reg_name = MIR_reg_hard_reg_name (ctx, reg, func);
    if (hard_reg_name != NULL) fprintf (f, ":%s", hard_reg_name);
  }
  fprintf (f, "\n");
}

static void output_label (MIR_context_t ctx, FILE *f, MIR_func_t func, MIR_label_t label) {
  fprintf (f, "L");
  MIR_output_op (ctx, f, label->ops[0], func);
}

static void output_reg (MIR_context_t ctx, FILE *f, MIR_func_t func, MIR_reg_t reg) {
  fprintf (f, "%s", MIR_reg_name (ctx, reg, func));
}

#define MAX_HARD_REG 8 // TODO
static int var_is_reg_p (MIR_reg_t var) { return var > MAX_HARD_REG; }

static MIR_reg_t var2reg (MIR_reg_t var) {
  mir_assert (var_is_reg_p (var));
  return var == MIR_NON_VAR ? 0 : var - MAX_HARD_REG;
}

static void output_hard_reg (FILE *f, MIR_reg_t hreg) { fprintf (f, "hr%u", hreg); }

static void output_var (MIR_context_t ctx, FILE *f, MIR_func_t func, MIR_reg_t var) {
  var_is_reg_p (var) ? output_reg (ctx, f, func, var2reg (var)) : output_hard_reg (f, var);
}

static void output_type (MIR_context_t ctx, FILE *f, MIR_type_t tp) {
  fprintf (f, "%s", MIR_type_str (ctx, tp));
}

static void output_disp (FILE *f, MIR_disp_t disp) { fprintf (f, "%" PRId64, (int64_t) disp); }

static void output_scale (FILE *f, unsigned scale) { fprintf (f, "%u", scale); }

void MIR_output_op (MIR_context_t ctx, FILE *f, MIR_op_t op, MIR_func_t func) {
  switch (op.mode) {
  case MIR_OP_REG: output_reg (ctx, f, func, op.u.reg); break;
  case MIR_OP_VAR: output_var (ctx, f, func, op.u.var); break;
  case MIR_OP_INT: fprintf (f, "%" PRId64, op.u.i); break;
  case MIR_OP_UINT: fprintf (f, "%" PRIu64, op.u.u); break;
  case MIR_OP_FLOAT: fprintf (f, "%.*ef", FLT_MANT_DIG, op.u.f); break;
  case MIR_OP_DOUBLE: fprintf (f, "%.*e", DBL_MANT_DIG, op.u.d); break;
  case MIR_OP_LDOUBLE: fprintf (f, "%.*LeL", LDBL_MANT_DIG, op.u.ld); break;
  case MIR_OP_MEM:
  case MIR_OP_VAR_MEM: {
    MIR_reg_t no_reg = op.mode == MIR_OP_MEM ? 0 : MIR_NON_VAR;

    output_type (ctx, f, op.u.mem.type);
    fprintf (f, ":");
    if (op.u.mem.disp != 0 || (op.u.mem.base == no_reg && op.u.mem.index == no_reg))
      output_disp (f, op.u.mem.disp);
    if (op.u.mem.base != no_reg || op.u.mem.index != no_reg) {
      fprintf (f, "(");
      if (op.u.mem.base != no_reg)
        (op.mode == MIR_OP_MEM ? output_reg : output_var) (ctx, f, func, op.u.mem.base);
      if (op.u.mem.index != no_reg) {
        fprintf (f, ", ");
        (op.mode == MIR_OP_MEM ? output_reg : output_var) (ctx, f, func, op.u.mem.index);
        if (op.u.mem.scale != 1) {
          fprintf (f, ", ");
          output_scale (f, op.u.mem.scale);
        }
      }
      fprintf (f, ")");
    }
    if (op.u.mem.alias != 0 || op.u.mem.nonalias != 0) {
      fprintf (f, ":");
      if (op.u.mem.alias != 0) fprintf (f, "%s", MIR_alias_name (ctx, op.u.mem.alias));
      if (op.u.mem.nonalias != 0) fprintf (f, ":%s", MIR_alias_name (ctx, op.u.mem.nonalias));
    }
    break;
  }
  case MIR_OP_REF:
    if (op.u.ref->module != func->func_item->module) fprintf (f, "%s.", op.u.ref->module->name);
    fprintf (f, "%s", MIR_item_name (ctx, op.u.ref));
    break;
  case MIR_OP_STR: MIR_output_str (ctx, f, op.u.str); break;
  case MIR_OP_LABEL: output_label (ctx, f, func, op.u.label); break;
  default: mir_assert (FALSE);
  }
}

static void output_func_proto (MIR_context_t ctx, FILE *f, size_t nres, MIR_type_t *types,
                               size_t nargs, VARR (MIR_var_t) * args, int vararg_p) {
  size_t i;
  MIR_var_t var;

  for (i = 0; i < nres; i++) {
    if (i != 0) fprintf (f, ", ");
    fprintf (f, "%s", MIR_type_str (ctx, types[i]));
  }
  for (i = 0; i < nargs; i++) {
    var = VARR_GET (MIR_var_t, args, i);
    if (i != 0 || nres != 0) fprintf (f, ", ");
    mir_assert (var.name != NULL);
    if (!MIR_all_blk_type_p (var.type))
      fprintf (f, "%s:%s", MIR_type_str (ctx, var.type), var.name);
    else
      fprintf (f, "%s:%lu(%s)", MIR_type_str (ctx, var.type), (unsigned long) var.size, var.name);
  }
  if (vararg_p) fprintf (f, nargs == 0 && nres == 0 ? "..." : ", ...");
  fprintf (f, "\n");
}

const char *MIR_insn_name (MIR_context_t ctx, MIR_insn_code_t code) {
  if ((unsigned) code >= MIR_INSN_BOUND)
    MIR_get_error_func (ctx) (MIR_wrong_param_value_error, "MIR_insn_name: wrong insn code %d",
                              (int) code);
  return insn_descs[code].name;
}

void MIR_output_insn (MIR_context_t ctx, FILE *f, MIR_insn_t insn, MIR_func_t func, int newline_p) {
  size_t i, nops;

  mir_assert (insn != NULL);
  if (insn->code == MIR_LABEL) {
    output_label (ctx, f, func, insn);
    if (newline_p) fprintf (f, ":\n");
    return;
  }
  fprintf (f, "\t%s", MIR_insn_name (ctx, insn->code));
  nops = MIR_insn_nops (ctx, insn);
  for (i = 0; i < nops; i++) {
    fprintf (f, i == 0 ? "\t" : ", ");
    MIR_output_op (ctx, f, insn->ops[i], func);
  }
  if (insn->code == MIR_UNSPEC)
    fprintf (f, " # %s", VARR_GET (MIR_proto_t, ctx->unspec_protos, insn->ops[0].u.u)->name);
  if (newline_p) fprintf (f, "\n");
}

void MIR_output_item (MIR_context_t ctx, FILE *f, MIR_item_t item) {
  MIR_insn_t insn;
  MIR_func_t func;
  MIR_proto_t proto;
  MIR_data_t data;
  MIR_ref_data_t ref_data;
  MIR_expr_data_t expr_data;
  size_t vars_num, nglobal;

  mir_assert (f != NULL && item != NULL);
  if (item->item_type == MIR_export_item) {
    fprintf (f, "\texport\t%s\n", item->u.export_id);
    return;
  }
  if (item->item_type == MIR_import_item) {
    fprintf (f, "\timport\t%s\n", item->u.import_id);
    return;
  }
  if (item->item_type == MIR_forward_item) {
    fprintf (f, "\tforward\t%s\n", item->u.forward_id);
    return;
  }
  if (item->item_type == MIR_bss_item) {
    if (item->u.bss->name != NULL) fprintf (f, "%s:", item->u.bss->name);
    fprintf (f, "\tbss\t%" PRIu64 "\n", item->u.bss->len);
    return;
  }
  if (item->item_type == MIR_ref_data_item) {
    ref_data = item->u.ref_data;
    if (ref_data->name != NULL) fprintf (f, "%s:", ref_data->name);
    fprintf (f, "\tref\t%s, %" PRId64 "\n", MIR_item_name (ctx, ref_data->ref_item),
             (int64_t) ref_data->disp);
    return;
  }
  if (item->item_type == MIR_lref_data_item) {
    MIR_lref_data_t lref_data = item->u.lref_data;
    if (lref_data->name != NULL) fprintf (f, "%s:", lref_data->name);
    mir_assert (lref_data->label->ops[0].mode == MIR_OP_INT);
    fprintf (f, "\tlref\tL%" PRId64, lref_data->label->ops[0].u.i);
    mir_assert (lref_data->label2 == NULL || lref_data->label2->ops[0].mode == MIR_OP_INT);
    if (lref_data->label2 != NULL) fprintf (f, ", L%" PRId64, lref_data->label2->ops[0].u.i);
    if (lref_data->disp != 0) fprintf (f, ", %" PRId64, (int64_t) lref_data->disp);
    fprintf (f, "\n");
    return;
  }
  if (item->item_type == MIR_expr_data_item) {
    expr_data = item->u.expr_data;
    if (expr_data->name != NULL) fprintf (f, "%s:", expr_data->name);
    fprintf (f, "\texpr\t%s", MIR_item_name (ctx, expr_data->expr_item));
  }
  if (item->item_type == MIR_data_item) {
    data = item->u.data;
    if (data->name != NULL) fprintf (f, "%s:", data->name);
    fprintf (f, "\t%s\t", MIR_type_str (ctx, data->el_type));
    _MIR_output_data_item_els (ctx, f, item, FALSE);
    fprintf (f, "\n");
    return;
  }
  if (item->item_type == MIR_proto_item) {
    proto = item->u.proto;
    fprintf (f, "%s:\tproto\t", proto->name);
    output_func_proto (ctx, f, proto->nres, proto->res_types, VARR_LENGTH (MIR_var_t, proto->args),
                       proto->args, proto->vararg_p);
    return;
  }
  func = item->u.func;
  fprintf (f, "%s:\tfunc\t", func->name);
  output_func_proto (ctx, f, func->nres, func->res_types, func->nargs, func->vars, func->vararg_p);
  vars_num = VARR_LENGTH (MIR_var_t, func->vars) - func->nargs;
  nglobal = func->global_vars == NULL ? 0 : VARR_LENGTH (MIR_var_t, func->global_vars);
  output_vars (ctx, f, func, func->vars, func->nargs, vars_num, "local");
  output_vars (ctx, f, func, func->global_vars, 0, nglobal, "global");
  fprintf (f, "\n# %u arg%s, %ld local%s, %ld global%s\n", func->nargs, func->nargs == 1 ? "" : "s",
           (long) vars_num, vars_num == 1 ? "" : "s", (long) nglobal, nglobal == 1 ? "" : "s");
  for (insn = DLIST_HEAD (MIR_insn_t, func->insns); insn != NULL;
       insn = DLIST_NEXT (MIR_insn_t, insn))
    MIR_output_insn (ctx, f, insn, func, TRUE);
  fprintf (f, "\tendfunc\n");
}

void MIR_output_module (MIR_context_t ctx, FILE *f, MIR_module_t module)
{
    mir_assert (f != NULL && module != NULL);

    fprintf (f, "%s:\tmodule\n", module->name);
    for (MIR_item_t item = DLIST_HEAD (MIR_item_t, module->items); item != NULL;
         item = DLIST_NEXT (MIR_item_t, item))
      MIR_output_item (ctx, f, item);
    fprintf (f, "\tendmodule\n");
}

#define TO_IMP printf("not yet implemented: %s\n", __FUNCTION__); fflush(stdout);

void MIR_write_module (MIR_context_t ctx, FILE *f, MIR_module_t module)
{
    TO_IMP
}

void MIR_write (MIR_context_t ctx, FILE *f)
{
    TO_IMP
}
