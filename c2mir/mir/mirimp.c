#include "mir.h"

struct MIR_context {
    DLIST (MIR_module_t) all_modules;
};


#define TO_IMP printf("not yet implemented: %s\n", __FUNCTION__); fflush(stdout);

void MIR_NO_RETURN error_exit (MIR_error_type_t error_type, const char *format, ...)
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
    return error_exit;
}

MIR_reg_t MIR_new_func_reg (MIR_context_t ctx, MIR_func_t func, MIR_type_t type,
                                   const char *name)
{
    TO_IMP
    return 0;
}

MIR_reg_t MIR_reg (MIR_context_t ctx, const char *reg_name, MIR_func_t func)
{
    TO_IMP
    return 0;
}

const char *MIR_reg_name (MIR_context_t ctx, MIR_reg_t reg, MIR_func_t func)
{
    TO_IMP
    return "<register>";
}

MIR_insn_t MIR_new_insn (MIR_context_t ctx, MIR_insn_code_t code, ...)
{
    TO_IMP
    return 0;
}

#define DEFAULT_OP     TO_IMP MIR_op_t res; memset(&res,0,sizeof(MIR_op_t)); return res;

MIR_op_t MIR_new_reg_op (MIR_context_t ctx, MIR_reg_t reg)
{
    DEFAULT_OP
}

MIR_op_t MIR_new_float_op (MIR_context_t ctx, float v)
{
    DEFAULT_OP
}

MIR_op_t MIR_new_double_op (MIR_context_t ctx, double v)
{
    DEFAULT_OP
}

MIR_op_t MIR_new_ldouble_op (MIR_context_t ctx, long double v)
{
    DEFAULT_OP
}

MIR_op_t MIR_new_int_op (MIR_context_t ctx, int64_t v)
{
    DEFAULT_OP
}

MIR_op_t MIR_new_uint_op (MIR_context_t ctx, uint64_t v)
{
    DEFAULT_OP
}

MIR_op_t MIR_new_mem_op (MIR_context_t ctx, MIR_type_t type, MIR_disp_t disp, MIR_reg_t base,
                                MIR_reg_t index, MIR_scale_t scale)
{
    DEFAULT_OP
}

MIR_insn_code_t MIR_reverse_branch_code (MIR_insn_code_t code)
{
    TO_IMP
    return code;
}

void MIR_append_insn (MIR_context_t ctx, MIR_item_t func, MIR_insn_t insn)
{
    TO_IMP
}

void MIR_remove_insn (MIR_context_t ctx, MIR_item_t func, MIR_insn_t insn)
{
    TO_IMP
}

MIR_op_mode_t MIR_insn_op_mode (MIR_context_t ctx, MIR_insn_t insn, size_t nop, int *out_p)
{
    TO_IMP
    return MIR_OP_UNDEF;
}

size_t MIR_insn_nops (MIR_context_t ctx, MIR_insn_t insn)
{
    TO_IMP
    return 0;
}

MIR_insn_t MIR_new_label (MIR_context_t ctx)
{
    TO_IMP
    return 0;
}

MIR_op_t MIR_new_label_op (MIR_context_t ctx, MIR_label_t label)
{
    DEFAULT_OP
}

int MIR_op_eq_p (MIR_context_t ctx, MIR_op_t op1, MIR_op_t op2)
{
    TO_IMP
    return 0;
}

const char *_MIR_uniq_string (MIR_context_t ctx, const char *str)
{
    TO_IMP
    return str;
}

MIR_item_t MIR_new_proto_arr (MIR_context_t ctx, const char *name, size_t nres,
                                     MIR_type_t *res_types, size_t nargs, MIR_var_t *vars)
{
    TO_IMP
    return 0;
}

MIR_item_t MIR_new_import (MIR_context_t ctx, const char *name)
{
    TO_IMP
    return 0;
}

MIR_op_t MIR_new_ref_op (MIR_context_t ctx, MIR_item_t item)
{
    DEFAULT_OP
}

MIR_insn_t MIR_new_insn_arr (MIR_context_t ctx, MIR_insn_code_t code, size_t nops,
                                    MIR_op_t *ops)
{
    TO_IMP
    return 0;
}

DLIST (MIR_module_t) * MIR_get_module_list (MIR_context_t ctx)
{
    return &ctx->all_modules;
}

MIR_module_t MIR_new_module (MIR_context_t ctx, const char *name)
{
    MIR_module_t m = malloc(sizeof(struct MIR_module));
    return m;
}

void MIR_output_module (MIR_context_t ctx, FILE *f, MIR_module_t module)
{
    TO_IMP
}

void MIR_write_module (MIR_context_t ctx, FILE *f, MIR_module_t module)
{
    TO_IMP
}

void MIR_finish_module (MIR_context_t ctx)
{
    TO_IMP
}

void MIR_finish (MIR_context_t ctx)
{
    free(ctx);
}

void MIR_write (MIR_context_t ctx, FILE *f)
{
    TO_IMP
}

void _MIR_get_temp_item_name (MIR_context_t ctx, MIR_module_t module, char *buff,
                                     size_t buff_len)
{
    TO_IMP
}

MIR_item_t MIR_new_string_data (MIR_context_t ctx, const char *name,
                                       MIR_str_t str)
{
    TO_IMP
    return 0;
}

MIR_item_t MIR_new_data (MIR_context_t ctx, const char *name, MIR_type_t el_type, size_t nel,
                                const void *els)
{
    TO_IMP
    return 0;
}

size_t _MIR_type_size (MIR_context_t ctx, MIR_type_t type)
{
    TO_IMP
    return 0;
}

MIR_item_t MIR_new_bss (MIR_context_t ctx, const char *name,
                               size_t len)
{
    TO_IMP
    return 0;
}

MIR_item_t MIR_new_ref_data (MIR_context_t ctx, const char *name, MIR_item_t item,
                                    int64_t disp)
{
    TO_IMP
    return 0;
}

MIR_item_t MIR_new_export (MIR_context_t ctx, const char *name)
{
    TO_IMP
    return 0;
}

MIR_item_t MIR_new_forward (MIR_context_t ctx, const char *name)
{
    TO_IMP
    return 0;
}

MIR_op_t MIR_new_str_op (MIR_context_t ctx, MIR_str_t str)
{
    TO_IMP
    DEFAULT_OP
}

MIR_item_t MIR_new_func_arr (MIR_context_t ctx, const char *name, size_t nres,
                                    MIR_type_t *res_types, size_t nargs, MIR_var_t *vars)
{
    TO_IMP
    return 0;
}

MIR_item_t MIR_new_vararg_func_arr (MIR_context_t ctx, const char *name, size_t nres,
                                           MIR_type_t *res_types, size_t nargs, MIR_var_t *vars)
{
    TO_IMP
    return 0;
}

MIR_insn_t MIR_new_ret_insn (MIR_context_t ctx, size_t nops, ...)
{
    TO_IMP
    return 0;
}

void MIR_finish_func (MIR_context_t ctx)
{
    TO_IMP
}

MIR_item_t MIR_new_vararg_proto_arr (MIR_context_t ctx, const char *name, size_t nres,
                                            MIR_type_t *res_types, size_t nargs, MIR_var_t *vars)
{
    TO_IMP
    return 0;
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

MIR_context_t _MIR_init (void)
{
    MIR_context_t ctx =
            malloc(sizeof(struct MIR_context));
    return ctx;
}

int _MIR_name_char_p (MIR_context_t ctx, int ch, int first_p)
{
    TO_IMP
}

MIR_op_t MIR_new_alias_mem_op (MIR_context_t ctx, MIR_type_t type, MIR_disp_t disp,
                                      MIR_reg_t base, MIR_reg_t index, MIR_scale_t scale,
                                      MIR_alias_t alias, MIR_alias_t noalias)
{
    TO_IMP
}

MIR_alias_t MIR_alias (MIR_context_t ctx, const char *name)
{
    TO_IMP
}

const char *MIR_alias_name (MIR_context_t ctx, MIR_alias_t alias)
{
    TO_IMP
}

MIR_item_t MIR_new_lref_data (MIR_context_t ctx, const char *name, MIR_label_t label,
                                     MIR_label_t label2,
                                     int64_t disp)
{
    TO_IMP
}

MIR_reg_t MIR_new_global_func_reg (MIR_context_t ctx, MIR_func_t func, MIR_type_t type,
                                          const char *name, const char *hard_reg_name)
{
    TO_IMP
}
