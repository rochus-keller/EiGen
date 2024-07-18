#include "gen_arm_new_nodes.h"

#include "benode.h"
#include "arm_bearch_t.h"
#include "gen_arm_regalloc_if.h"
#include "arm_new_nodes_t.h"
#include "fourcc.h"
#include "irgopt.h"
#include "ircons_t.h"

ir_op *op_arm_AdC = NULL;
ir_op *op_arm_AdC_t = NULL;
ir_op *op_arm_Add = NULL;
ir_op *op_arm_AddS = NULL;
ir_op *op_arm_AddS_t = NULL;
ir_op *op_arm_Address = NULL;
ir_op *op_arm_Adf = NULL;
ir_op *op_arm_And = NULL;
ir_op *op_arm_B = NULL;
ir_op *op_arm_Bcc = NULL;
ir_op *op_arm_Bic = NULL;
ir_op *op_arm_Bl = NULL;
ir_op *op_arm_Clz = NULL;
ir_op *op_arm_Cmfe = NULL;
ir_op *op_arm_Cmn = NULL;
ir_op *op_arm_Cmp = NULL;
ir_op *op_arm_Dvf = NULL;
ir_op *op_arm_Eor = NULL;
ir_op *op_arm_Flt = NULL;
ir_op *op_arm_FrameAddr = NULL;
ir_op *op_arm_IJmp = NULL;
ir_op *op_arm_Ldf = NULL;
ir_op *op_arm_Ldr = NULL;
ir_op *op_arm_LinkLdrPC = NULL;
ir_op *op_arm_LinkMovPC = NULL;
ir_op *op_arm_Mla = NULL;
ir_op *op_arm_Mls = NULL;
ir_op *op_arm_Mov = NULL;
ir_op *op_arm_Muf = NULL;
ir_op *op_arm_Mul = NULL;
ir_op *op_arm_Mvf = NULL;
ir_op *op_arm_Mvn = NULL;
ir_op *op_arm_OrPl_t = NULL;
ir_op *op_arm_Orr = NULL;
ir_op *op_arm_OrrPl = NULL;
ir_op *op_arm_Pkhbt = NULL;
ir_op *op_arm_Pkhtb = NULL;
ir_op *op_arm_Return = NULL;
ir_op *op_arm_RsC = NULL;
ir_op *op_arm_Rsb = NULL;
ir_op *op_arm_RsbS = NULL;
ir_op *op_arm_SMulL = NULL;
ir_op *op_arm_SMulL_t = NULL;
ir_op *op_arm_SbC = NULL;
ir_op *op_arm_SbC_t = NULL;
ir_op *op_arm_Stf = NULL;
ir_op *op_arm_Str = NULL;
ir_op *op_arm_Sub = NULL;
ir_op *op_arm_SubS = NULL;
ir_op *op_arm_SubS_t = NULL;
ir_op *op_arm_Suf = NULL;
ir_op *op_arm_SwitchJmp = NULL;
ir_op *op_arm_Tst = NULL;
ir_op *op_arm_UMulL = NULL;
ir_op *op_arm_UMulL_t = NULL;
ir_op *op_arm_fConst = NULL;


static int arm_opcode_start = -1;

/** A tag for the arm opcodes. */
#define arm_op_tag FOURCC('a', 'r', 'm', '\0')

/** Return 1 if the given opcode is a arm machine op, 0 otherwise */
int is_arm_op(const ir_op *op)
{
	return get_op_tag(op) == arm_op_tag;
}

/** Return 1 if the given node is a arm machine node, 0 otherwise */
int is_arm_irn(const ir_node *node)
{
	return is_arm_op(get_irn_op(node));
}

int get_arm_irn_opcode(const ir_node *node)
{
	assert(is_arm_irn(node));
	return get_irn_opcode(node) - arm_opcode_start;
}

#undef BIT
#define BIT(x)  (1 << (x))


static const arch_register_req_t arm_requirements_gp_not_in_r0 = {
	.cls               = &arm_reg_classes[CLASS_arm_gp],
	.limited           = NULL,
	.should_be_same    = 0,
	.must_be_different = 1,
	.width             = 1,
};

static const arch_register_req_t arm_requirements_gp_in_r2_not_in_r0_not_in_r3 = {
	.cls               = &arm_reg_classes[CLASS_arm_gp],
	.limited           = NULL,
	.should_be_same    = 4,
	.must_be_different = 9,
	.width             = 1,
};



ir_node *new_bd_arm_AdC_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *flags, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_AdC, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_AdC_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *flags)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_AdC, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_AdC_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *flags, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_AdC, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_AdC_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, ir_node *flags, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_AdC, arm_mode_gp, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_AdC_t(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *flags, ir_mode *mode)
{

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_AdC_t, mode, 3, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Add_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Add, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Add_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Add, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Add_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Add, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Add_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Add, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_AddS_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_AddS, mode_T, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_AddS_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_AddS, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_AddS_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_AddS, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_AddS_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_AddS, mode_T, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_AddS_t(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_AddS_t, mode_T, 2, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Address(dbg_info *dbgi, ir_node *block, ir_entity *entity, int offset)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Address, arm_mode_gp, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_Address_attr_t *const attr = (arm_Address_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_Address_attributes(res, entity, offset);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Adf(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1, ir_mode *op_mode)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_fpa,
		&arm_class_reg_req_fpa,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Adf, mode_F, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_farith_attr_t *const attr = (arm_farith_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_farith_attributes(res, op_mode);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_fpa;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_And_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_And, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_And_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_And, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_And_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_And, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_And_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_And, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_B(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_B, mode_X, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_simple_jump;
	irn_flags |= arch_irn_flag_fallthrough;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_attr_t *const attr = (arm_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Bcc(dbg_info *dbgi, ir_node *block, ir_node *flags, ir_relation relation)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Bcc, mode_T, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_fallthrough;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_CondJmp_attr_t *const attr = (arm_CondJmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
		set_arm_CondJmp_relation(res, relation);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_exec_requirement;
	out_infos[1].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Bic_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Bic, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Bic_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Bic, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Bic_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Bic, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Bic_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Bic, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Bl(dbg_info *dbgi, ir_node *block, int const arity, ir_node *const *const in, arch_register_req_t const **const in_reqs, int n_res, ir_entity *entity, int offset)
{


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Bl, mode_T, arity, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_Address_attr_t *const attr = (arm_Address_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_Address_attributes(res, entity, offset);

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Clz(dbg_info *dbgi, ir_node *block, ir_node *op0)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Clz, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_attr_t *const attr = (arm_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Cmfe(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1, bool ins_permuted)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_fpa,
		&arm_class_reg_req_fpa,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Cmfe, arm_mode_flags, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_cmp_attr_t *const attr = (arm_cmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	bool const is_unsigned = false;
	init_arm_attributes(res);
	init_arm_cmp_attr(res, ins_permuted, is_unsigned);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Cmn_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot, bool ins_permuted, bool is_unsigned)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Cmn, arm_mode_flags, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_cmp_attr_t *const attr = (arm_cmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_cmp_attr(res, ins_permuted, is_unsigned);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);

	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Cmn_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, bool ins_permuted, bool is_unsigned)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Cmn, arm_mode_flags, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_cmp_attr_t *const attr = (arm_cmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_cmp_attr(res, ins_permuted, is_unsigned);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);

	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Cmn_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate, bool ins_permuted, bool is_unsigned)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Cmn, arm_mode_flags, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_cmp_attr_t *const attr = (arm_cmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_cmp_attr(res, ins_permuted, is_unsigned);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);

	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Cmn_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier, bool ins_permuted, bool is_unsigned)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Cmn, arm_mode_flags, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_cmp_attr_t *const attr = (arm_cmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_cmp_attr(res, ins_permuted, is_unsigned);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);

	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Cmp_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot, bool ins_permuted, bool is_unsigned)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Cmp, arm_mode_flags, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_cmp_attr_t *const attr = (arm_cmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_cmp_attr(res, ins_permuted, is_unsigned);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);

	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Cmp_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, bool ins_permuted, bool is_unsigned)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Cmp, arm_mode_flags, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_cmp_attr_t *const attr = (arm_cmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_cmp_attr(res, ins_permuted, is_unsigned);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);

	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Cmp_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate, bool ins_permuted, bool is_unsigned)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Cmp, arm_mode_flags, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_cmp_attr_t *const attr = (arm_cmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_cmp_attr(res, ins_permuted, is_unsigned);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);

	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Cmp_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier, bool ins_permuted, bool is_unsigned)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Cmp, arm_mode_flags, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_cmp_attr_t *const attr = (arm_cmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_cmp_attr(res, ins_permuted, is_unsigned);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);

	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Dvf(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1, ir_mode *op_mode)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_fpa,
		&arm_class_reg_req_fpa,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Dvf, mode_F, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_farith_attr_t *const attr = (arm_farith_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_farith_attributes(res, op_mode);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_fpa;
	out_infos[1].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Eor_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Eor, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Eor_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Eor, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Eor_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Eor, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Eor_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Eor, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Flt(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_mode *op_mode)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Flt, mode_F, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_farith_attr_t *const attr = (arm_farith_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_farith_attributes(res, op_mode);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_fpa;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_FrameAddr(dbg_info *dbgi, ir_node *block, ir_node *base, ir_entity *entity, int offset)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_FrameAddr, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_Address_attr_t *const attr = (arm_Address_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_Address_attributes(res, entity, offset);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_IJmp(dbg_info *dbgi, ir_node *block, ir_node *target)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		target,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_IJmp, mode_X, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_attr_t *const attr = (arm_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Ldf(dbg_info *dbgi, ir_node *block, ir_node *ptr, ir_node *mem, ir_mode *ls_mode, ir_entity *entity, int entity_sign, long offset, bool is_frame_entity)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		ptr,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Ldf, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_load_store_attr_t *const attr = (arm_load_store_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_load_store_attributes(res, ls_mode, entity, entity_sign, offset, is_frame_entity);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_fpa;
	out_infos[1].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Ldr(dbg_info *dbgi, ir_node *block, ir_node *ptr, ir_node *mem, ir_mode *ls_mode, ir_entity *entity, int entity_sign, long offset, bool is_frame_entity)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		ptr,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Ldr, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_load_store_attr_t *const attr = (arm_load_store_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_load_store_attributes(res, ls_mode, entity, entity_sign, offset, is_frame_entity);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_LinkLdrPC(dbg_info *dbgi, ir_node *block, int const arity, ir_node *const *const in, arch_register_req_t const **const in_reqs, int n_res, ir_mode *ls_mode, ir_entity *entity, int entity_sign, long offset, bool is_frame_entity)
{


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_LinkLdrPC, mode_T, arity, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_load_store_attr_t *const attr = (arm_load_store_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_load_store_attributes(res, ls_mode, entity, entity_sign, offset, is_frame_entity);

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_LinkMovPC(dbg_info *dbgi, ir_node *block, int const arity, ir_node *const *const in, arch_register_req_t const **const in_reqs, int n_res, unsigned shiftop_input, arm_shift_modifier_t shift_modifier, unsigned char immediate_value, unsigned char immediate_rot)
{


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_LinkMovPC, mode_T, arity, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, shiftop_input, immediate_value, shift_modifier, immediate_rot);


	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Mla(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *add)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		add,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Mla, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_attr_t *const attr = (arm_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Mla_v5(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *add)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		add,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Mla, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_attr_t *const attr = (arm_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_requirements_gp_not_in_r0;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Mls(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *sub)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		sub,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Mls, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_attr_t *const attr = (arm_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Mov_imm(dbg_info *dbgi, ir_node *block, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
	};


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Mov, arm_mode_gp, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 0, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Mov_reg(dbg_info *dbgi, ir_node *block, ir_node *Rm)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		Rm,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Mov, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 0, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Mov_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *Rm, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		Rm,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Mov, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 0, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Mov_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *Rm, ir_node *Rs, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		Rm,
		Rs,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Mov, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 0, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Muf(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1, ir_mode *op_mode)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_fpa,
		&arm_class_reg_req_fpa,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Muf, mode_F, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_farith_attr_t *const attr = (arm_farith_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_farith_attributes(res, op_mode);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_fpa;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Mul(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Mul, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_attr_t *const attr = (arm_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Mul_v5(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Mul, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_attr_t *const attr = (arm_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_requirements_gp_not_in_r0;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Mvf(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_mode *op_mode)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_fpa,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Mvf, mode_F, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_farith_attr_t *const attr = (arm_farith_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_farith_attributes(res, op_mode);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_fpa;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Mvn_imm(dbg_info *dbgi, ir_node *block, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
	};


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Mvn, arm_mode_gp, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 0, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Mvn_reg(dbg_info *dbgi, ir_node *block, ir_node *Rm)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		Rm,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Mvn, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 0, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Mvn_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *Rm, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		Rm,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Mvn, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 0, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Mvn_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *Rm, ir_node *Rs, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		Rm,
		Rs,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Mvn, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 0, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_OrPl_t(dbg_info *dbgi, ir_node *block, ir_node *falseval, ir_node *flags, ir_node *left, ir_node *right, ir_mode *mode)
{

	/* construct in array */
	ir_node *const in[] = {
		falseval,
		flags,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_OrPl_t, mode, 4, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Orr_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Orr, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Orr_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Orr, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Orr_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Orr, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Orr_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Orr, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_OrrPl(dbg_info *dbgi, ir_node *block, ir_node *falseval, ir_node *flags, ir_node *left, ir_node *right)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_flags,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		falseval,
		flags,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_OrrPl, arm_mode_gp, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 3, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_requirements_gp_in_r2_not_in_r0_not_in_r3;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Pkhbt_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Pkhbt, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Pkhbt_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Pkhbt, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Pkhbt_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Pkhbt, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Pkhbt_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Pkhbt, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Pkhtb_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Pkhtb, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Pkhtb_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Pkhtb, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Pkhtb_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Pkhtb, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Pkhtb_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Pkhtb, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Return(dbg_info *dbgi, ir_node *block, int const arity, ir_node *const *const in, arch_register_req_t const **const in_reqs)
{


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Return, mode_X, arity, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_attr_t *const attr = (arm_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_RsC_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *flags, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_RsC, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_RsC_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *flags)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_RsC, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_RsC_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *flags, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_RsC, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_RsC_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, ir_node *flags, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_RsC, arm_mode_gp, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Rsb_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Rsb, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Rsb_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Rsb, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Rsb_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Rsb, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Rsb_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Rsb, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_RsbS_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_RsbS, mode_T, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_RsbS_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_RsbS, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_RsbS_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_RsbS, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_RsbS_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_RsbS, mode_T, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_SMulL(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_SMulL, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_attr_t *const attr = (arm_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_SMulL_t(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_SMulL_t, mode_T, 2, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_SbC_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *flags, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_SbC, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_SbC_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *flags)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_SbC, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_SbC_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *flags, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_SbC, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_SbC_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, ir_node *flags, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_SbC, arm_mode_gp, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_SbC_t(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *flags, ir_mode *mode)
{

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		flags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_SbC_t, mode, 3, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Stf(dbg_info *dbgi, ir_node *block, ir_node *ptr, ir_node *val, ir_node *mem, ir_mode *ls_mode, ir_entity *entity, int entity_sign, long offset, bool is_frame_entity)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_fpa,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		ptr,
		val,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Stf, mode_M, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_load_store_attr_t *const attr = (arm_load_store_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_load_store_attributes(res, ls_mode, entity, entity_sign, offset, is_frame_entity);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Str(dbg_info *dbgi, ir_node *block, ir_node *ptr, ir_node *val, ir_node *mem, ir_mode *ls_mode, ir_entity *entity, int entity_sign, long offset, bool is_frame_entity)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		ptr,
		val,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Str, mode_M, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_load_store_attr_t *const attr = (arm_load_store_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_load_store_attributes(res, ls_mode, entity, entity_sign, offset, is_frame_entity);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Sub_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Sub, arm_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Sub_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Sub, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Sub_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Sub, arm_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Sub_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Sub, arm_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_SubS_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_SubS, mode_T, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_SubS_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_SubS, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_SubS_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_SubS, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_SubS_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_SubS, mode_T, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_shifter_operand_t *const attr = (arm_shifter_operand_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_SubS_t(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_SubS_t, mode_T, 2, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Suf(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1, ir_mode *op_mode)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_fpa,
		&arm_class_reg_req_fpa,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Suf, mode_F, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_farith_attr_t *const attr = (arm_farith_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_farith_attributes(res, op_mode);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_fpa;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_SwitchJmp(dbg_info *dbgi, ir_node *block, ir_node *op0, int n_res, const ir_switch_table *table)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_SwitchJmp, mode_T, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_SwitchJmp_attr_t *const attr = (arm_SwitchJmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	be_switch_attr_init(res, &attr->swtch, table, NULL);

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Tst_imm(dbg_info *dbgi, ir_node *block, ir_node *left, unsigned char immediate_value, unsigned char immediate_rot, bool ins_permuted, bool is_unsigned)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Tst, arm_mode_flags, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_cmp_attr_t *const attr = (arm_cmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_cmp_attr(res, ins_permuted, is_unsigned);
	init_arm_shifter_operand(res, 1, immediate_value, ARM_SHF_IMM, immediate_rot);

	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Tst_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, bool ins_permuted, bool is_unsigned)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Tst, arm_mode_flags, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_cmp_attr_t *const attr = (arm_cmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_cmp_attr(res, ins_permuted, is_unsigned);
	init_arm_shifter_operand(res, 1, 0, ARM_SHF_REG, 0);

	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Tst_reg_shift_imm(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, arm_shift_modifier_t shift_modifier, unsigned shift_immediate, bool ins_permuted, bool is_unsigned)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Tst, arm_mode_flags, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_cmp_attr_t *const attr = (arm_cmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_cmp_attr(res, ins_permuted, is_unsigned);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, shift_immediate);

	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_Tst_reg_shift_reg(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *shift, arm_shift_modifier_t shift_modifier, bool ins_permuted, bool is_unsigned)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		shift,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_Tst, arm_mode_flags, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_cmp_attr_t *const attr = (arm_cmp_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	init_arm_cmp_attr(res, ins_permuted, is_unsigned);
	init_arm_shifter_operand(res, 1, 0, shift_modifier, 0);

	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_UMulL(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&arm_class_reg_req_gp,
		&arm_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_UMulL, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_attr_t *const attr = (arm_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_gp;
	out_infos[1].req = &arm_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_UMulL_t(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_UMulL_t, mode_T, 2, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_arm_fConst(dbg_info *dbgi, ir_node *block, ir_tarval *tv)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_arm_fConst, mode_F, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	arm_fConst_attr_t *const attr = (arm_fConst_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_arm_attributes(res);
	attr->tv = tv;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arm_class_reg_req_fpa;

	verify_new_node(res);
	return optimize_node(res);
}


/**
 * Creates the arm specific Firm machine operations
 * needed for the assembler irgs.
 */
void arm_create_opcodes(void)
{
	ir_op *op;
	int    cur_opcode = get_next_ir_opcodes(iro_arm_last);

	arm_opcode_start = cur_opcode;
	op = new_ir_op(cur_opcode + iro_arm_AdC, "arm_AdC", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_AdC = op;
	op = new_ir_op(cur_opcode + iro_arm_AdC_t, "arm_AdC_t", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, arm_op_tag);
	op_arm_AdC_t = op;
	op = new_ir_op(cur_opcode + iro_arm_Add, "arm_Add", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Add = op;
	op = new_ir_op(cur_opcode + iro_arm_AddS, "arm_AddS", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_AddS = op;
	op = new_ir_op(cur_opcode + iro_arm_AddS_t, "arm_AddS_t", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, arm_op_tag);
	op_arm_AddS_t = op;
	op = new_ir_op(cur_opcode + iro_arm_Address, "arm_Address", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(arm_Address_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_Address_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Address = op;
	op = new_ir_op(cur_opcode + iro_arm_Adf, "arm_Adf", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_farith_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_farith_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Adf = op;
	op = new_ir_op(cur_opcode + iro_arm_And, "arm_And", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_And = op;
	op = new_ir_op(cur_opcode + iro_arm_B, "arm_B", op_pin_state_pinned, irop_flag_cfopcode, oparity_any, -1, sizeof(arm_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_B = op;
	op = new_ir_op(cur_opcode + iro_arm_Bcc, "arm_Bcc", op_pin_state_pinned, irop_flag_cfopcode|irop_flag_forking, oparity_any, -1, sizeof(arm_CondJmp_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_CondJmp_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Bcc = op;
	op = new_ir_op(cur_opcode + iro_arm_Bic, "arm_Bic", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Bic = op;
	op = new_ir_op(cur_opcode + iro_arm_Bl, "arm_Bl", op_pin_state_exc_pinned, irop_flag_none, oparity_any, -1, sizeof(arm_Address_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_Address_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Bl = op;
	op = new_ir_op(cur_opcode + iro_arm_Clz, "arm_Clz", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Clz = op;
	op = new_ir_op(cur_opcode + iro_arm_Cmfe, "arm_Cmfe", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_cmp_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_cmp_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Cmfe = op;
	op = new_ir_op(cur_opcode + iro_arm_Cmn, "arm_Cmn", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_cmp_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_cmp_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Cmn = op;
	op = new_ir_op(cur_opcode + iro_arm_Cmp, "arm_Cmp", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_cmp_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_cmp_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Cmp = op;
	op = new_ir_op(cur_opcode + iro_arm_Dvf, "arm_Dvf", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_farith_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_farith_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Dvf = op;
	op = new_ir_op(cur_opcode + iro_arm_Eor, "arm_Eor", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Eor = op;
	op = new_ir_op(cur_opcode + iro_arm_Flt, "arm_Flt", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_farith_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_farith_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Flt = op;
	op = new_ir_op(cur_opcode + iro_arm_FrameAddr, "arm_FrameAddr", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(arm_Address_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_Address_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_FrameAddr = op;
	op = new_ir_op(cur_opcode + iro_arm_IJmp, "arm_IJmp", op_pin_state_pinned, irop_flag_cfopcode|irop_flag_forking, oparity_any, -1, sizeof(arm_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_IJmp = op;
	op = new_ir_op(cur_opcode + iro_arm_Ldf, "arm_Ldf", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(arm_load_store_attr_t));
	ir_op_set_memory_index(op, 1);	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_load_store_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Ldf = op;
	op = new_ir_op(cur_opcode + iro_arm_Ldr, "arm_Ldr", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(arm_load_store_attr_t));
	ir_op_set_memory_index(op, 1);	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_load_store_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Ldr = op;
	op = new_ir_op(cur_opcode + iro_arm_LinkLdrPC, "arm_LinkLdrPC", op_pin_state_exc_pinned, irop_flag_none, oparity_any, -1, sizeof(arm_load_store_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_load_store_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_LinkLdrPC = op;
	op = new_ir_op(cur_opcode + iro_arm_LinkMovPC, "arm_LinkMovPC", op_pin_state_exc_pinned, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_LinkMovPC = op;
	op = new_ir_op(cur_opcode + iro_arm_Mla, "arm_Mla", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Mla = op;
	op = new_ir_op(cur_opcode + iro_arm_Mls, "arm_Mls", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Mls = op;
	op = new_ir_op(cur_opcode + iro_arm_Mov, "arm_Mov", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Mov = op;
	op = new_ir_op(cur_opcode + iro_arm_Muf, "arm_Muf", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_farith_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_farith_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Muf = op;
	op = new_ir_op(cur_opcode + iro_arm_Mul, "arm_Mul", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Mul = op;
	op = new_ir_op(cur_opcode + iro_arm_Mvf, "arm_Mvf", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_farith_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_farith_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Mvf = op;
	op = new_ir_op(cur_opcode + iro_arm_Mvn, "arm_Mvn", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Mvn = op;
	op = new_ir_op(cur_opcode + iro_arm_OrPl_t, "arm_OrPl_t", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, arm_op_tag);
	op_arm_OrPl_t = op;
	op = new_ir_op(cur_opcode + iro_arm_Orr, "arm_Orr", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Orr = op;
	op = new_ir_op(cur_opcode + iro_arm_OrrPl, "arm_OrrPl", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_OrrPl = op;
	op = new_ir_op(cur_opcode + iro_arm_Pkhbt, "arm_Pkhbt", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Pkhbt = op;
	op = new_ir_op(cur_opcode + iro_arm_Pkhtb, "arm_Pkhtb", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Pkhtb = op;
	op = new_ir_op(cur_opcode + iro_arm_Return, "arm_Return", op_pin_state_pinned, irop_flag_cfopcode, oparity_any, -1, sizeof(arm_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Return = op;
	op = new_ir_op(cur_opcode + iro_arm_RsC, "arm_RsC", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_RsC = op;
	op = new_ir_op(cur_opcode + iro_arm_Rsb, "arm_Rsb", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Rsb = op;
	op = new_ir_op(cur_opcode + iro_arm_RsbS, "arm_RsbS", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_RsbS = op;
	op = new_ir_op(cur_opcode + iro_arm_SMulL, "arm_SMulL", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_SMulL = op;
	op = new_ir_op(cur_opcode + iro_arm_SMulL_t, "arm_SMulL_t", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, arm_op_tag);
	op_arm_SMulL_t = op;
	op = new_ir_op(cur_opcode + iro_arm_SbC, "arm_SbC", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_SbC = op;
	op = new_ir_op(cur_opcode + iro_arm_SbC_t, "arm_SbC_t", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, arm_op_tag);
	op_arm_SbC_t = op;
	op = new_ir_op(cur_opcode + iro_arm_Stf, "arm_Stf", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(arm_load_store_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_load_store_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Stf = op;
	op = new_ir_op(cur_opcode + iro_arm_Str, "arm_Str", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(arm_load_store_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_load_store_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Str = op;
	op = new_ir_op(cur_opcode + iro_arm_Sub, "arm_Sub", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Sub = op;
	op = new_ir_op(cur_opcode + iro_arm_SubS, "arm_SubS", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_shifter_operand_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_shifter_operands_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_SubS = op;
	op = new_ir_op(cur_opcode + iro_arm_SubS_t, "arm_SubS_t", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, arm_op_tag);
	op_arm_SubS_t = op;
	op = new_ir_op(cur_opcode + iro_arm_Suf, "arm_Suf", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_farith_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_farith_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Suf = op;
	op = new_ir_op(cur_opcode + iro_arm_SwitchJmp, "arm_SwitchJmp", op_pin_state_pinned, irop_flag_cfopcode|irop_flag_forking, oparity_any, -1, sizeof(arm_SwitchJmp_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_SwitchJmp_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_SwitchJmp = op;
	op = new_ir_op(cur_opcode + iro_arm_Tst, "arm_Tst", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_cmp_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_cmp_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_Tst = op;
	op = new_ir_op(cur_opcode + iro_arm_UMulL, "arm_UMulL", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(arm_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_UMulL = op;
	op = new_ir_op(cur_opcode + iro_arm_UMulL_t, "arm_UMulL_t", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, arm_op_tag);
	op_arm_UMulL_t = op;
	op = new_ir_op(cur_opcode + iro_arm_fConst, "arm_fConst", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(arm_fConst_attr_t));
	set_op_dump(op, arm_dump_node);
	set_op_attrs_equal(op, arm_fConst_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, arm_op_tag);
	op_arm_fConst = op;

}

void arm_free_opcodes(void)
{
	free_ir_op(op_arm_AdC); op_arm_AdC = NULL;
	free_ir_op(op_arm_AdC_t); op_arm_AdC_t = NULL;
	free_ir_op(op_arm_Add); op_arm_Add = NULL;
	free_ir_op(op_arm_AddS); op_arm_AddS = NULL;
	free_ir_op(op_arm_AddS_t); op_arm_AddS_t = NULL;
	free_ir_op(op_arm_Address); op_arm_Address = NULL;
	free_ir_op(op_arm_Adf); op_arm_Adf = NULL;
	free_ir_op(op_arm_And); op_arm_And = NULL;
	free_ir_op(op_arm_B); op_arm_B = NULL;
	free_ir_op(op_arm_Bcc); op_arm_Bcc = NULL;
	free_ir_op(op_arm_Bic); op_arm_Bic = NULL;
	free_ir_op(op_arm_Bl); op_arm_Bl = NULL;
	free_ir_op(op_arm_Clz); op_arm_Clz = NULL;
	free_ir_op(op_arm_Cmfe); op_arm_Cmfe = NULL;
	free_ir_op(op_arm_Cmn); op_arm_Cmn = NULL;
	free_ir_op(op_arm_Cmp); op_arm_Cmp = NULL;
	free_ir_op(op_arm_Dvf); op_arm_Dvf = NULL;
	free_ir_op(op_arm_Eor); op_arm_Eor = NULL;
	free_ir_op(op_arm_Flt); op_arm_Flt = NULL;
	free_ir_op(op_arm_FrameAddr); op_arm_FrameAddr = NULL;
	free_ir_op(op_arm_IJmp); op_arm_IJmp = NULL;
	free_ir_op(op_arm_Ldf); op_arm_Ldf = NULL;
	free_ir_op(op_arm_Ldr); op_arm_Ldr = NULL;
	free_ir_op(op_arm_LinkLdrPC); op_arm_LinkLdrPC = NULL;
	free_ir_op(op_arm_LinkMovPC); op_arm_LinkMovPC = NULL;
	free_ir_op(op_arm_Mla); op_arm_Mla = NULL;
	free_ir_op(op_arm_Mls); op_arm_Mls = NULL;
	free_ir_op(op_arm_Mov); op_arm_Mov = NULL;
	free_ir_op(op_arm_Muf); op_arm_Muf = NULL;
	free_ir_op(op_arm_Mul); op_arm_Mul = NULL;
	free_ir_op(op_arm_Mvf); op_arm_Mvf = NULL;
	free_ir_op(op_arm_Mvn); op_arm_Mvn = NULL;
	free_ir_op(op_arm_OrPl_t); op_arm_OrPl_t = NULL;
	free_ir_op(op_arm_Orr); op_arm_Orr = NULL;
	free_ir_op(op_arm_OrrPl); op_arm_OrrPl = NULL;
	free_ir_op(op_arm_Pkhbt); op_arm_Pkhbt = NULL;
	free_ir_op(op_arm_Pkhtb); op_arm_Pkhtb = NULL;
	free_ir_op(op_arm_Return); op_arm_Return = NULL;
	free_ir_op(op_arm_RsC); op_arm_RsC = NULL;
	free_ir_op(op_arm_Rsb); op_arm_Rsb = NULL;
	free_ir_op(op_arm_RsbS); op_arm_RsbS = NULL;
	free_ir_op(op_arm_SMulL); op_arm_SMulL = NULL;
	free_ir_op(op_arm_SMulL_t); op_arm_SMulL_t = NULL;
	free_ir_op(op_arm_SbC); op_arm_SbC = NULL;
	free_ir_op(op_arm_SbC_t); op_arm_SbC_t = NULL;
	free_ir_op(op_arm_Stf); op_arm_Stf = NULL;
	free_ir_op(op_arm_Str); op_arm_Str = NULL;
	free_ir_op(op_arm_Sub); op_arm_Sub = NULL;
	free_ir_op(op_arm_SubS); op_arm_SubS = NULL;
	free_ir_op(op_arm_SubS_t); op_arm_SubS_t = NULL;
	free_ir_op(op_arm_Suf); op_arm_Suf = NULL;
	free_ir_op(op_arm_SwitchJmp); op_arm_SwitchJmp = NULL;
	free_ir_op(op_arm_Tst); op_arm_Tst = NULL;
	free_ir_op(op_arm_UMulL); op_arm_UMulL = NULL;
	free_ir_op(op_arm_UMulL_t); op_arm_UMulL_t = NULL;
	free_ir_op(op_arm_fConst); op_arm_fConst = NULL;

}
