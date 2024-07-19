/*
 * This file is part of libFirm.
 * Copyright (C) 2012 University of Karlsruhe.
 */

/**
 * @file
 * @brief   This file implements the creation of the achitecture specific firm
 *          opcodes and the coresponding node constructors for the eigen
 *          assembler irg.
 */
#include "eigen_new_nodes_t.h"

#include "eigen_nodes_attr.h"
#include "bedump.h"
#include "eigen_regalloc_if.h"
#include "ircons_t.h"
#include "irgraph_t.h"
#include "irmode_t.h"
#include "irnode_t.h"
#include "irop_t.h"
#include "iropt_t.h"
#include "irprintf.h"
#include "irprog_t.h"
#include "xmalloc.h"
#include "benode.h"
#include "fourcc.h"
#include <stdlib.h>

void eigen_dump_node(FILE *F, const ir_node *n, dump_reason_t reason)
{
	switch (reason) {
	case dump_node_opcode_txt:
		fprintf(F, "%s", get_irn_opname(n));
		break;

	case dump_node_mode_txt:
		break;

	case dump_node_nodeattr_txt:

		/* TODO: dump some attributes which should show up */
		/* in node name in dump (e.g. consts or the like)  */

		break;

	case dump_node_info_txt:
		break;
	}
}

const eigen_attr_t *get_eigen_attr_const(const ir_node *node)
{
    assert(is_eigen_irn(node) && "need eigen node to get attributes");
    return (const eigen_attr_t *)get_irn_generic_attr_const(node);
}

eigen_attr_t *get_eigen_attr(ir_node *node)
{
    assert(is_eigen_irn(node) && "need eigen node to get attributes");
    return (eigen_attr_t *)get_irn_generic_attr(node);
}

void set_eigen_value(ir_node *const node, ir_entity *const entity,
                        ir_tarval *const value)
{
    eigen_attr_t *attr = get_eigen_attr(node);
	attr->entity = entity;
	attr->value  = value;
}

int eigen_attrs_equal(const ir_node *a, const ir_node *b)
{
    const eigen_attr_t *attr_a = get_eigen_attr_const(a);
    const eigen_attr_t *attr_b = get_eigen_attr_const(b);
	return attr_a->value == attr_b->value
	    && attr_a->entity == attr_b->entity;
}

ir_op *op_eigen_Add = NULL;
ir_op *op_eigen_And = NULL;
ir_op *op_eigen_Const = NULL;
ir_op *op_eigen_Jmp = NULL;
ir_op *op_eigen_Load = NULL;
ir_op *op_eigen_Minus = NULL;
ir_op *op_eigen_Mul = NULL;
ir_op *op_eigen_Not = NULL;
ir_op *op_eigen_Or = NULL;
ir_op *op_eigen_Return = NULL;
ir_op *op_eigen_Shl = NULL;
ir_op *op_eigen_Shr = NULL;
ir_op *op_eigen_Store = NULL;
ir_op *op_eigen_Sub = NULL;
ir_op *op_eigen_Xor = NULL;
ir_op *op_eigen_fAdd = NULL;
ir_op *op_eigen_fConst = NULL;
ir_op *op_eigen_fDiv = NULL;
ir_op *op_eigen_fLoad = NULL;
ir_op *op_eigen_fMinus = NULL;
ir_op *op_eigen_fMul = NULL;
ir_op *op_eigen_fStore = NULL;
ir_op *op_eigen_fSub = NULL;


static int eigen_opcode_start = -1;

/** A tag for the eigen opcodes. */
#define eigen_op_tag FOURCC('T', 'E', 'M', 'P')

/** Return 1 if the given opcode is a eigen machine op, 0 otherwise */
int is_eigen_op(const ir_op *op)
{
    return get_op_tag(op) == eigen_op_tag;
}

/** Return 1 if the given node is a eigen machine node, 0 otherwise */
int is_eigen_irn(const ir_node *node)
{
    return is_eigen_op(get_irn_op(node));
}

int get_eigen_irn_opcode(const ir_node *node)
{
    assert(is_eigen_irn(node));
    return get_irn_opcode(node) - eigen_opcode_start;
}

#undef BIT
#define BIT(x)  (1 << (x))




ir_node *new_bd_eigen_Add(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_gp,
        &eigen_class_reg_req_gp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
        op1,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_Add, mode_Iu, 2, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_gp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_And(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_gp,
        &eigen_class_reg_req_gp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
        op1,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_And, mode_Iu, 2, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_gp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_Const(dbg_info *dbgi, ir_node *block, ir_entity *entity, ir_tarval *value)
{
    arch_register_req_t const **const in_reqs = NULL;


    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_Const, mode_Iu, 0, NULL);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    set_eigen_value(res, entity, value);
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_gp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_Jmp(dbg_info *dbgi, ir_node *block)
{
    arch_register_req_t const **const in_reqs = NULL;


    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_Jmp, mode_X, 0, NULL);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_simple_jump;
    irn_flags |= arch_irn_flag_fallthrough;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &arch_exec_requirement;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_Load(dbg_info *dbgi, ir_node *block, ir_node *mem, ir_node *ptr)
{
    static arch_register_req_t const *in_reqs[] = {
        &arch_memory_requirement,
        &eigen_class_reg_req_gp,
    };

    /* construct in array */
    ir_node *const in[] = {
        mem,
        ptr,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_Load, mode_T, 2, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 2;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_gp;
    out_infos[1].req = &arch_memory_requirement;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_Minus(dbg_info *dbgi, ir_node *block, ir_node *op0)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_gp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_Minus, mode_Iu, 1, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_gp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_Mul(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_gp,
        &eigen_class_reg_req_gp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
        op1,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_Mul, mode_Iu, 2, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_gp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_Not(dbg_info *dbgi, ir_node *block, ir_node *op0)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_gp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_Not, mode_Iu, 1, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_gp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_Or(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_gp,
        &eigen_class_reg_req_gp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
        op1,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_Or, mode_Iu, 2, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_gp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_Return(dbg_info *dbgi, ir_node *block, int const arity, ir_node *const *const in, arch_register_req_t const **const in_reqs)
{


    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_Return, mode_X, arity, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &arch_exec_requirement;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_Shl(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_gp,
        &eigen_class_reg_req_gp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
        op1,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_Shl, mode_Iu, 2, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_gp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_Shr(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_gp,
        &eigen_class_reg_req_gp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
        op1,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_Shr, mode_Iu, 2, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_gp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_Store(dbg_info *dbgi, ir_node *block, ir_node *mem, ir_node *ptr, ir_node *val)
{
    static arch_register_req_t const *in_reqs[] = {
        &arch_memory_requirement,
        &eigen_class_reg_req_gp,
        &eigen_class_reg_req_gp,
    };

    /* construct in array */
    ir_node *const in[] = {
        mem,
        ptr,
        val,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_Store, mode_M, 3, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &arch_memory_requirement;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_Sub(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_gp,
        &eigen_class_reg_req_gp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
        op1,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_Sub, mode_Iu, 2, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_gp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_Xor(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_gp,
        &eigen_class_reg_req_gp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
        op1,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_Xor, mode_Iu, 2, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_gp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_fAdd(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_sp,
        &eigen_class_reg_req_sp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
        op1,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_fAdd, mode_F, 2, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_sp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_fConst(dbg_info *dbgi, ir_node *block)
{
    arch_register_req_t const **const in_reqs = NULL;


    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_fConst, mode_F, 0, NULL);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_sp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_fDiv(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_sp,
        &eigen_class_reg_req_sp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
        op1,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_fDiv, mode_F, 2, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_sp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_fLoad(dbg_info *dbgi, ir_node *block, ir_node *mem, ir_node *ptr)
{
    static arch_register_req_t const *in_reqs[] = {
        &arch_memory_requirement,
        &eigen_class_reg_req_gp,
    };

    /* construct in array */
    ir_node *const in[] = {
        mem,
        ptr,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_fLoad, mode_T, 2, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 2;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_sp;
    out_infos[1].req = &arch_memory_requirement;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_fMinus(dbg_info *dbgi, ir_node *block, ir_node *op0)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_sp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_fMinus, mode_F, 1, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_sp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_fMul(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_sp,
        &eigen_class_reg_req_sp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
        op1,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_fMul, mode_F, 2, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_sp;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_fStore(dbg_info *dbgi, ir_node *block, ir_node *mem, ir_node *ptr, ir_node *val)
{
    static arch_register_req_t const *in_reqs[] = {
        &arch_memory_requirement,
        &eigen_class_reg_req_gp,
        &eigen_class_reg_req_sp,
    };

    /* construct in array */
    ir_node *const in[] = {
        mem,
        ptr,
        val,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_fStore, mode_M, 3, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &arch_memory_requirement;

    verify_new_node(res);
    return optimize_node(res);
}

ir_node *new_bd_eigen_fSub(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
    static arch_register_req_t const *in_reqs[] = {
        &eigen_class_reg_req_sp,
        &eigen_class_reg_req_sp,
    };

    /* construct in array */
    ir_node *const in[] = {
        op0,
        op1,
    };

    ir_graph *const irg = get_irn_irg(block);
    ir_node  *const res = new_ir_node(dbgi, irg, block, op_eigen_fSub, mode_F, 2, in);

    /* init node attributes */

    /* flags */
    arch_irn_flags_t irn_flags = arch_irn_flags_none;
    irn_flags |= arch_irn_flag_rematerializable;
    int const n_res = 1;
    be_info_init_irn(res, irn_flags, in_reqs, n_res);
    eigen_attr_t *const attr = (eigen_attr_t*)get_irn_generic_attr(res);
    (void)attr; /* avoid potential warning */
    reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
    out_infos[0].req = &eigen_class_reg_req_sp;

    verify_new_node(res);
    return optimize_node(res);
}


/**
 * Creates the eigen specific Firm machine operations
 * needed for the assembler irgs.
 */
void eigen_create_opcodes(void)
{
    ir_op *op;
    int    cur_opcode = get_next_ir_opcodes(iro_eigen_last);

    eigen_opcode_start = cur_opcode;
    op = new_ir_op(cur_opcode + iro_eigen_Add, "eigen_Add", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_Add = op;
    op = new_ir_op(cur_opcode + iro_eigen_And, "eigen_And", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_And = op;
    op = new_ir_op(cur_opcode + iro_eigen_Const, "eigen_Const", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_Const = op;
    op = new_ir_op(cur_opcode + iro_eigen_Jmp, "eigen_Jmp", op_pin_state_pinned, irop_flag_cfopcode, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_Jmp = op;
    op = new_ir_op(cur_opcode + iro_eigen_Load, "eigen_Load", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(eigen_attr_t));
    ir_op_set_memory_index(op, 0);	set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_Load = op;
    op = new_ir_op(cur_opcode + iro_eigen_Minus, "eigen_Minus", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_Minus = op;
    op = new_ir_op(cur_opcode + iro_eigen_Mul, "eigen_Mul", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_Mul = op;
    op = new_ir_op(cur_opcode + iro_eigen_Not, "eigen_Not", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_Not = op;
    op = new_ir_op(cur_opcode + iro_eigen_Or, "eigen_Or", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_Or = op;
    op = new_ir_op(cur_opcode + iro_eigen_Return, "eigen_Return", op_pin_state_pinned, irop_flag_cfopcode, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_Return = op;
    op = new_ir_op(cur_opcode + iro_eigen_Shl, "eigen_Shl", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_Shl = op;
    op = new_ir_op(cur_opcode + iro_eigen_Shr, "eigen_Shr", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_Shr = op;
    op = new_ir_op(cur_opcode + iro_eigen_Store, "eigen_Store", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(eigen_attr_t));
    ir_op_set_memory_index(op, 0);	set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_Store = op;
    op = new_ir_op(cur_opcode + iro_eigen_Sub, "eigen_Sub", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_Sub = op;
    op = new_ir_op(cur_opcode + iro_eigen_Xor, "eigen_Xor", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_Xor = op;
    op = new_ir_op(cur_opcode + iro_eigen_fAdd, "eigen_fAdd", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_fAdd = op;
    op = new_ir_op(cur_opcode + iro_eigen_fConst, "eigen_fConst", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_fConst = op;
    op = new_ir_op(cur_opcode + iro_eigen_fDiv, "eigen_fDiv", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_fDiv = op;
    op = new_ir_op(cur_opcode + iro_eigen_fLoad, "eigen_fLoad", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(eigen_attr_t));
    ir_op_set_memory_index(op, 0);	set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_fLoad = op;
    op = new_ir_op(cur_opcode + iro_eigen_fMinus, "eigen_fMinus", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_fMinus = op;
    op = new_ir_op(cur_opcode + iro_eigen_fMul, "eigen_fMul", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_fMul = op;
    op = new_ir_op(cur_opcode + iro_eigen_fStore, "eigen_fStore", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(eigen_attr_t));
    ir_op_set_memory_index(op, 0);	set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_fStore = op;
    op = new_ir_op(cur_opcode + iro_eigen_fSub, "eigen_fSub", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(eigen_attr_t));
    set_op_dump(op, eigen_dump_node);
    set_op_attrs_equal(op, eigen_attrs_equal);
    set_op_copy_attr(op, be_copy_attr);
    set_op_tag(op, eigen_op_tag);
    op_eigen_fSub = op;

}

void eigen_free_opcodes(void)
{
    free_ir_op(op_eigen_Add); op_eigen_Add = NULL;
    free_ir_op(op_eigen_And); op_eigen_And = NULL;
    free_ir_op(op_eigen_Const); op_eigen_Const = NULL;
    free_ir_op(op_eigen_Jmp); op_eigen_Jmp = NULL;
    free_ir_op(op_eigen_Load); op_eigen_Load = NULL;
    free_ir_op(op_eigen_Minus); op_eigen_Minus = NULL;
    free_ir_op(op_eigen_Mul); op_eigen_Mul = NULL;
    free_ir_op(op_eigen_Not); op_eigen_Not = NULL;
    free_ir_op(op_eigen_Or); op_eigen_Or = NULL;
    free_ir_op(op_eigen_Return); op_eigen_Return = NULL;
    free_ir_op(op_eigen_Shl); op_eigen_Shl = NULL;
    free_ir_op(op_eigen_Shr); op_eigen_Shr = NULL;
    free_ir_op(op_eigen_Store); op_eigen_Store = NULL;
    free_ir_op(op_eigen_Sub); op_eigen_Sub = NULL;
    free_ir_op(op_eigen_Xor); op_eigen_Xor = NULL;
    free_ir_op(op_eigen_fAdd); op_eigen_fAdd = NULL;
    free_ir_op(op_eigen_fConst); op_eigen_fConst = NULL;
    free_ir_op(op_eigen_fDiv); op_eigen_fDiv = NULL;
    free_ir_op(op_eigen_fLoad); op_eigen_fLoad = NULL;
    free_ir_op(op_eigen_fMinus); op_eigen_fMinus = NULL;
    free_ir_op(op_eigen_fMul); op_eigen_fMul = NULL;
    free_ir_op(op_eigen_fStore); op_eigen_fStore = NULL;
    free_ir_op(op_eigen_fSub); op_eigen_fSub = NULL;

}
