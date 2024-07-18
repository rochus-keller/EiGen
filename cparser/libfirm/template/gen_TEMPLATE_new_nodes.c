#include "gen_TEMPLATE_new_nodes.h"

#include "benode.h"
#include "TEMPLATE_bearch_t.h"
#include "gen_TEMPLATE_regalloc_if.h"
#include "TEMPLATE_new_nodes_t.h"
#include "fourcc.h"
#include "irgopt.h"
#include "ircons_t.h"

ir_op *op_TEMPLATE_Add = NULL;
ir_op *op_TEMPLATE_And = NULL;
ir_op *op_TEMPLATE_Const = NULL;
ir_op *op_TEMPLATE_Jmp = NULL;
ir_op *op_TEMPLATE_Load = NULL;
ir_op *op_TEMPLATE_Minus = NULL;
ir_op *op_TEMPLATE_Mul = NULL;
ir_op *op_TEMPLATE_Not = NULL;
ir_op *op_TEMPLATE_Or = NULL;
ir_op *op_TEMPLATE_Return = NULL;
ir_op *op_TEMPLATE_Shl = NULL;
ir_op *op_TEMPLATE_Shr = NULL;
ir_op *op_TEMPLATE_Store = NULL;
ir_op *op_TEMPLATE_Sub = NULL;
ir_op *op_TEMPLATE_Xor = NULL;
ir_op *op_TEMPLATE_fAdd = NULL;
ir_op *op_TEMPLATE_fConst = NULL;
ir_op *op_TEMPLATE_fDiv = NULL;
ir_op *op_TEMPLATE_fLoad = NULL;
ir_op *op_TEMPLATE_fMinus = NULL;
ir_op *op_TEMPLATE_fMul = NULL;
ir_op *op_TEMPLATE_fStore = NULL;
ir_op *op_TEMPLATE_fSub = NULL;


static int TEMPLATE_opcode_start = -1;

/** A tag for the TEMPLATE opcodes. */
#define TEMPLATE_op_tag FOURCC('T', 'E', 'M', 'P')

/** Return 1 if the given opcode is a TEMPLATE machine op, 0 otherwise */
int is_TEMPLATE_op(const ir_op *op)
{
	return get_op_tag(op) == TEMPLATE_op_tag;
}

/** Return 1 if the given node is a TEMPLATE machine node, 0 otherwise */
int is_TEMPLATE_irn(const ir_node *node)
{
	return is_TEMPLATE_op(get_irn_op(node));
}

int get_TEMPLATE_irn_opcode(const ir_node *node)
{
	assert(is_TEMPLATE_irn(node));
	return get_irn_opcode(node) - TEMPLATE_opcode_start;
}

#undef BIT
#define BIT(x)  (1 << (x))




ir_node *new_bd_TEMPLATE_Add(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_gp,
		&TEMPLATE_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_Add, mode_Iu, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_And(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_gp,
		&TEMPLATE_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_And, mode_Iu, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_Const(dbg_info *dbgi, ir_node *block, ir_entity *entity, ir_tarval *value)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_Const, mode_Iu, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	set_TEMPLATE_value(res, entity, value);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_Jmp(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_Jmp, mode_X, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_simple_jump;
	irn_flags |= arch_irn_flag_fallthrough;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_Load(dbg_info *dbgi, ir_node *block, ir_node *mem, ir_node *ptr)
{
	static arch_register_req_t const *in_reqs[] = {
		&arch_memory_requirement,
		&TEMPLATE_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		mem,
		ptr,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_Load, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_gp;
	out_infos[1].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_Minus(dbg_info *dbgi, ir_node *block, ir_node *op0)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_Minus, mode_Iu, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_Mul(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_gp,
		&TEMPLATE_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_Mul, mode_Iu, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_Not(dbg_info *dbgi, ir_node *block, ir_node *op0)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_Not, mode_Iu, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_Or(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_gp,
		&TEMPLATE_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_Or, mode_Iu, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_Return(dbg_info *dbgi, ir_node *block, int const arity, ir_node *const *const in, arch_register_req_t const **const in_reqs)
{


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_Return, mode_X, arity, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_Shl(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_gp,
		&TEMPLATE_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_Shl, mode_Iu, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_Shr(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_gp,
		&TEMPLATE_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_Shr, mode_Iu, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_Store(dbg_info *dbgi, ir_node *block, ir_node *mem, ir_node *ptr, ir_node *val)
{
	static arch_register_req_t const *in_reqs[] = {
		&arch_memory_requirement,
		&TEMPLATE_class_reg_req_gp,
		&TEMPLATE_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		mem,
		ptr,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_Store, mode_M, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_Sub(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_gp,
		&TEMPLATE_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_Sub, mode_Iu, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_Xor(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_gp,
		&TEMPLATE_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_Xor, mode_Iu, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_fAdd(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_fp,
		&TEMPLATE_class_reg_req_fp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_fAdd, mode_F, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_fConst(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_fConst, mode_F, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_fDiv(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_fp,
		&TEMPLATE_class_reg_req_fp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_fDiv, mode_F, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_fLoad(dbg_info *dbgi, ir_node *block, ir_node *mem, ir_node *ptr)
{
	static arch_register_req_t const *in_reqs[] = {
		&arch_memory_requirement,
		&TEMPLATE_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		mem,
		ptr,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_fLoad, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_fp;
	out_infos[1].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_fMinus(dbg_info *dbgi, ir_node *block, ir_node *op0)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_fp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_fMinus, mode_F, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_fMul(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_fp,
		&TEMPLATE_class_reg_req_fp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_fMul, mode_F, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_fStore(dbg_info *dbgi, ir_node *block, ir_node *mem, ir_node *ptr, ir_node *val)
{
	static arch_register_req_t const *in_reqs[] = {
		&arch_memory_requirement,
		&TEMPLATE_class_reg_req_gp,
		&TEMPLATE_class_reg_req_fp,
	};

	/* construct in array */
	ir_node *const in[] = {
		mem,
		ptr,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_fStore, mode_M, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_TEMPLATE_fSub(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&TEMPLATE_class_reg_req_fp,
		&TEMPLATE_class_reg_req_fp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_TEMPLATE_fSub, mode_F, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	TEMPLATE_attr_t *const attr = (TEMPLATE_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &TEMPLATE_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}


/**
 * Creates the TEMPLATE specific Firm machine operations
 * needed for the assembler irgs.
 */
void TEMPLATE_create_opcodes(void)
{
	ir_op *op;
	int    cur_opcode = get_next_ir_opcodes(iro_TEMPLATE_last);

	TEMPLATE_opcode_start = cur_opcode;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_Add, "TEMPLATE_Add", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_Add = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_And, "TEMPLATE_And", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_And = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_Const, "TEMPLATE_Const", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_Const = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_Jmp, "TEMPLATE_Jmp", op_pin_state_pinned, irop_flag_cfopcode, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_Jmp = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_Load, "TEMPLATE_Load", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	ir_op_set_memory_index(op, 0);	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_Load = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_Minus, "TEMPLATE_Minus", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_Minus = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_Mul, "TEMPLATE_Mul", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_Mul = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_Not, "TEMPLATE_Not", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_Not = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_Or, "TEMPLATE_Or", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_Or = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_Return, "TEMPLATE_Return", op_pin_state_pinned, irop_flag_cfopcode, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_Return = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_Shl, "TEMPLATE_Shl", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_Shl = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_Shr, "TEMPLATE_Shr", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_Shr = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_Store, "TEMPLATE_Store", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	ir_op_set_memory_index(op, 0);	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_Store = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_Sub, "TEMPLATE_Sub", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_Sub = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_Xor, "TEMPLATE_Xor", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_Xor = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_fAdd, "TEMPLATE_fAdd", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_fAdd = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_fConst, "TEMPLATE_fConst", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_fConst = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_fDiv, "TEMPLATE_fDiv", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_fDiv = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_fLoad, "TEMPLATE_fLoad", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	ir_op_set_memory_index(op, 0);	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_fLoad = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_fMinus, "TEMPLATE_fMinus", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_fMinus = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_fMul, "TEMPLATE_fMul", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_fMul = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_fStore, "TEMPLATE_fStore", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	ir_op_set_memory_index(op, 0);	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_fStore = op;
	op = new_ir_op(cur_opcode + iro_TEMPLATE_fSub, "TEMPLATE_fSub", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(TEMPLATE_attr_t));
	set_op_dump(op, TEMPLATE_dump_node);
	set_op_attrs_equal(op, TEMPLATE_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, TEMPLATE_op_tag);
	op_TEMPLATE_fSub = op;

}

void TEMPLATE_free_opcodes(void)
{
	free_ir_op(op_TEMPLATE_Add); op_TEMPLATE_Add = NULL;
	free_ir_op(op_TEMPLATE_And); op_TEMPLATE_And = NULL;
	free_ir_op(op_TEMPLATE_Const); op_TEMPLATE_Const = NULL;
	free_ir_op(op_TEMPLATE_Jmp); op_TEMPLATE_Jmp = NULL;
	free_ir_op(op_TEMPLATE_Load); op_TEMPLATE_Load = NULL;
	free_ir_op(op_TEMPLATE_Minus); op_TEMPLATE_Minus = NULL;
	free_ir_op(op_TEMPLATE_Mul); op_TEMPLATE_Mul = NULL;
	free_ir_op(op_TEMPLATE_Not); op_TEMPLATE_Not = NULL;
	free_ir_op(op_TEMPLATE_Or); op_TEMPLATE_Or = NULL;
	free_ir_op(op_TEMPLATE_Return); op_TEMPLATE_Return = NULL;
	free_ir_op(op_TEMPLATE_Shl); op_TEMPLATE_Shl = NULL;
	free_ir_op(op_TEMPLATE_Shr); op_TEMPLATE_Shr = NULL;
	free_ir_op(op_TEMPLATE_Store); op_TEMPLATE_Store = NULL;
	free_ir_op(op_TEMPLATE_Sub); op_TEMPLATE_Sub = NULL;
	free_ir_op(op_TEMPLATE_Xor); op_TEMPLATE_Xor = NULL;
	free_ir_op(op_TEMPLATE_fAdd); op_TEMPLATE_fAdd = NULL;
	free_ir_op(op_TEMPLATE_fConst); op_TEMPLATE_fConst = NULL;
	free_ir_op(op_TEMPLATE_fDiv); op_TEMPLATE_fDiv = NULL;
	free_ir_op(op_TEMPLATE_fLoad); op_TEMPLATE_fLoad = NULL;
	free_ir_op(op_TEMPLATE_fMinus); op_TEMPLATE_fMinus = NULL;
	free_ir_op(op_TEMPLATE_fMul); op_TEMPLATE_fMul = NULL;
	free_ir_op(op_TEMPLATE_fStore); op_TEMPLATE_fStore = NULL;
	free_ir_op(op_TEMPLATE_fSub); op_TEMPLATE_fSub = NULL;

}
