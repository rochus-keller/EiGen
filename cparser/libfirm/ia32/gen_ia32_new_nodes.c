#include "gen_ia32_new_nodes.h"

#include "benode.h"
#include "ia32_bearch_t.h"
#include "gen_ia32_regalloc_if.h"
#include "ia32_new_nodes_t.h"
#include "fourcc.h"
#include "irgopt.h"
#include "ircons_t.h"

ir_op *op_ia32_Adc = NULL;
ir_op *op_ia32_Add = NULL;
ir_op *op_ia32_AddMem = NULL;
ir_op *op_ia32_AddSP = NULL;
ir_op *op_ia32_Adds = NULL;
ir_op *op_ia32_And = NULL;
ir_op *op_ia32_AndMem = NULL;
ir_op *op_ia32_Andnp = NULL;
ir_op *op_ia32_Andp = NULL;
ir_op *op_ia32_Breakpoint = NULL;
ir_op *op_ia32_Bsf = NULL;
ir_op *op_ia32_Bsr = NULL;
ir_op *op_ia32_Bswap = NULL;
ir_op *op_ia32_Bswap16 = NULL;
ir_op *op_ia32_Bt = NULL;
ir_op *op_ia32_CMovcc = NULL;
ir_op *op_ia32_Call = NULL;
ir_op *op_ia32_ChangeCW = NULL;
ir_op *op_ia32_Cltd = NULL;
ir_op *op_ia32_Cmc = NULL;
ir_op *op_ia32_Cmp = NULL;
ir_op *op_ia32_CmpXChgMem = NULL;
ir_op *op_ia32_Const = NULL;
ir_op *op_ia32_Conv_FP2FP = NULL;
ir_op *op_ia32_Conv_FP2I = NULL;
ir_op *op_ia32_Conv_I2FP = NULL;
ir_op *op_ia32_Conv_I2I = NULL;
ir_op *op_ia32_CopyB = NULL;
ir_op *op_ia32_CopyB_i = NULL;
ir_op *op_ia32_CopyEbpEsp = NULL;
ir_op *op_ia32_CvtSI2SD = NULL;
ir_op *op_ia32_CvtSI2SS = NULL;
ir_op *op_ia32_Cwtl = NULL;
ir_op *op_ia32_Dec = NULL;
ir_op *op_ia32_DecMem = NULL;
ir_op *op_ia32_Div = NULL;
ir_op *op_ia32_Divs = NULL;
ir_op *op_ia32_Enter = NULL;
ir_op *op_ia32_FldCW = NULL;
ir_op *op_ia32_FnstCW = NULL;
ir_op *op_ia32_FnstCWNOP = NULL;
ir_op *op_ia32_FtstFnstsw = NULL;
ir_op *op_ia32_FucomFnstsw = NULL;
ir_op *op_ia32_Fucomi = NULL;
ir_op *op_ia32_FucomppFnstsw = NULL;
ir_op *op_ia32_GetEIP = NULL;
ir_op *op_ia32_IDiv = NULL;
ir_op *op_ia32_IJmp = NULL;
ir_op *op_ia32_IMul = NULL;
ir_op *op_ia32_IMul1OP = NULL;
ir_op *op_ia32_IMulImm = NULL;
ir_op *op_ia32_Immediate = NULL;
ir_op *op_ia32_Inc = NULL;
ir_op *op_ia32_IncMem = NULL;
ir_op *op_ia32_Inport = NULL;
ir_op *op_ia32_Jcc = NULL;
ir_op *op_ia32_Jmp = NULL;
ir_op *op_ia32_LdTls = NULL;
ir_op *op_ia32_Lea = NULL;
ir_op *op_ia32_Leave = NULL;
ir_op *op_ia32_Load = NULL;
ir_op *op_ia32_Maxs = NULL;
ir_op *op_ia32_Mins = NULL;
ir_op *op_ia32_Minus64 = NULL;
ir_op *op_ia32_Movd = NULL;
ir_op *op_ia32_Mul = NULL;
ir_op *op_ia32_Muls = NULL;
ir_op *op_ia32_Neg = NULL;
ir_op *op_ia32_NegMem = NULL;
ir_op *op_ia32_NoReg_FP = NULL;
ir_op *op_ia32_NoReg_GP = NULL;
ir_op *op_ia32_NoReg_XMM = NULL;
ir_op *op_ia32_Not = NULL;
ir_op *op_ia32_NotMem = NULL;
ir_op *op_ia32_Or = NULL;
ir_op *op_ia32_OrMem = NULL;
ir_op *op_ia32_Orp = NULL;
ir_op *op_ia32_Outport = NULL;
ir_op *op_ia32_Pop = NULL;
ir_op *op_ia32_PopMem = NULL;
ir_op *op_ia32_Popcnt = NULL;
ir_op *op_ia32_Prefetch = NULL;
ir_op *op_ia32_PrefetchNTA = NULL;
ir_op *op_ia32_PrefetchT0 = NULL;
ir_op *op_ia32_PrefetchT1 = NULL;
ir_op *op_ia32_PrefetchT2 = NULL;
ir_op *op_ia32_PrefetchW = NULL;
ir_op *op_ia32_Pslld = NULL;
ir_op *op_ia32_Psllq = NULL;
ir_op *op_ia32_Psrld = NULL;
ir_op *op_ia32_Push = NULL;
ir_op *op_ia32_PushEax = NULL;
ir_op *op_ia32_Ret = NULL;
ir_op *op_ia32_Rol = NULL;
ir_op *op_ia32_RolMem = NULL;
ir_op *op_ia32_Ror = NULL;
ir_op *op_ia32_RorMem = NULL;
ir_op *op_ia32_Sahf = NULL;
ir_op *op_ia32_Sar = NULL;
ir_op *op_ia32_SarMem = NULL;
ir_op *op_ia32_Sbb = NULL;
ir_op *op_ia32_Sbb0 = NULL;
ir_op *op_ia32_Setcc = NULL;
ir_op *op_ia32_SetccMem = NULL;
ir_op *op_ia32_Shl = NULL;
ir_op *op_ia32_ShlD = NULL;
ir_op *op_ia32_ShlMem = NULL;
ir_op *op_ia32_Shr = NULL;
ir_op *op_ia32_ShrD = NULL;
ir_op *op_ia32_ShrMem = NULL;
ir_op *op_ia32_Stc = NULL;
ir_op *op_ia32_Store = NULL;
ir_op *op_ia32_Sub = NULL;
ir_op *op_ia32_SubMem = NULL;
ir_op *op_ia32_SubSP = NULL;
ir_op *op_ia32_Subs = NULL;
ir_op *op_ia32_SwitchJmp = NULL;
ir_op *op_ia32_Test = NULL;
ir_op *op_ia32_UD2 = NULL;
ir_op *op_ia32_Ucomis = NULL;
ir_op *op_ia32_Xor = NULL;
ir_op *op_ia32_Xor0 = NULL;
ir_op *op_ia32_XorHighLow = NULL;
ir_op *op_ia32_XorMem = NULL;
ir_op *op_ia32_Xorp = NULL;
ir_op *op_ia32_emms = NULL;
ir_op *op_ia32_fabs = NULL;
ir_op *op_ia32_fadd = NULL;
ir_op *op_ia32_fchs = NULL;
ir_op *op_ia32_fdiv = NULL;
ir_op *op_ia32_fdup = NULL;
ir_op *op_ia32_femms = NULL;
ir_op *op_ia32_ffreep = NULL;
ir_op *op_ia32_fild = NULL;
ir_op *op_ia32_fist = NULL;
ir_op *op_ia32_fistp = NULL;
ir_op *op_ia32_fisttp = NULL;
ir_op *op_ia32_fld = NULL;
ir_op *op_ia32_fld1 = NULL;
ir_op *op_ia32_fldl2e = NULL;
ir_op *op_ia32_fldl2t = NULL;
ir_op *op_ia32_fldlg2 = NULL;
ir_op *op_ia32_fldln2 = NULL;
ir_op *op_ia32_fldpi = NULL;
ir_op *op_ia32_fldz = NULL;
ir_op *op_ia32_fmul = NULL;
ir_op *op_ia32_fpop = NULL;
ir_op *op_ia32_fst = NULL;
ir_op *op_ia32_fstp = NULL;
ir_op *op_ia32_fsub = NULL;
ir_op *op_ia32_fxch = NULL;
ir_op *op_ia32_l_Adc = NULL;
ir_op *op_ia32_l_Add = NULL;
ir_op *op_ia32_l_FloattoLL = NULL;
ir_op *op_ia32_l_IMul = NULL;
ir_op *op_ia32_l_LLtoFloat = NULL;
ir_op *op_ia32_l_Minus64 = NULL;
ir_op *op_ia32_l_Mul = NULL;
ir_op *op_ia32_l_Sbb = NULL;
ir_op *op_ia32_l_Sub = NULL;
ir_op *op_ia32_xAllOnes = NULL;
ir_op *op_ia32_xLoad = NULL;
ir_op *op_ia32_xPzero = NULL;
ir_op *op_ia32_xStore = NULL;
ir_op *op_ia32_xZero = NULL;
ir_op *op_ia32_xxLoad = NULL;
ir_op *op_ia32_xxStore = NULL;


static int ia32_opcode_start = -1;

/** A tag for the ia32 opcodes. */
#define ia32_op_tag FOURCC('i', 'a', '3', '2')

/** Return 1 if the given opcode is a ia32 machine op, 0 otherwise */
int is_ia32_op(const ir_op *op)
{
	return get_op_tag(op) == ia32_op_tag;
}

/** Return 1 if the given node is a ia32 machine node, 0 otherwise */
int is_ia32_irn(const ir_node *node)
{
	return is_ia32_op(get_irn_op(node));
}

int get_ia32_irn_opcode(const ir_node *node)
{
	assert(is_ia32_irn(node));
	return get_irn_opcode(node) - ia32_opcode_start;
}

#undef BIT
#define BIT(x)  (1 << (x))

static const unsigned ia32_limit_gp_eax_ebx_ecx_edx[] = { BIT(REG_GP_EAX) | BIT(REG_GP_EBX) | BIT(REG_GP_ECX) | BIT(REG_GP_EDX), 0 };
static const unsigned ia32_limit_gp_esp[] = { BIT(REG_GP_ESP), 0 };
static const unsigned ia32_limit_gp_gp_NOREG[] = { BIT(REG_GP_GP_NOREG), 0 };
static const unsigned ia32_limit_gp_ebp[] = { BIT(REG_GP_EBP), 0 };
static const unsigned ia32_limit_fp_fp_NOREG[] = { BIT(REG_FP_FP_NOREG), 0 };
static const unsigned ia32_limit_xmm_xmm_NOREG[] = { BIT(REG_XMM_XMM_NOREG), 0 };

static const arch_register_req_t ia32_requirements_gp_in_r3_in_r4 = {
	.cls               = &ia32_reg_classes[CLASS_ia32_gp],
	.limited           = NULL,
	.should_be_same    = 24,
	.must_be_different = 0,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_gp_eax_ebx_ecx_edx = {
	.cls               = &ia32_reg_classes[CLASS_ia32_gp],
	.limited           = ia32_limit_gp_eax_ebx_ecx_edx,
	.should_be_same    = 0,
	.must_be_different = 0,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_gp_eax_ebx_ecx_edx_in_r3_in_r4 = {
	.cls               = &ia32_reg_classes[CLASS_ia32_gp],
	.limited           = ia32_limit_gp_eax_ebx_ecx_edx,
	.should_be_same    = 24,
	.must_be_different = 0,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_gp_esp_I = {
	.cls               = &ia32_reg_classes[CLASS_ia32_gp],
	.limited           = ia32_limit_gp_esp,
	.should_be_same    = 0,
	.must_be_different = 0,
	.width             = 1,
	.ignore = true,
};

static const arch_register_req_t ia32_requirements_xmm_in_r3_in_r4 = {
	.cls               = &ia32_reg_classes[CLASS_ia32_xmm],
	.limited           = NULL,
	.should_be_same    = 24,
	.must_be_different = 0,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_xmm_in_r3_not_in_r4 = {
	.cls               = &ia32_reg_classes[CLASS_ia32_xmm],
	.limited           = NULL,
	.should_be_same    = 8,
	.must_be_different = 16,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_gp_in_r0 = {
	.cls               = &ia32_reg_classes[CLASS_ia32_gp],
	.limited           = NULL,
	.should_be_same    = 1,
	.must_be_different = 0,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_gp_eax_ebx_ecx_edx_in_r0 = {
	.cls               = &ia32_reg_classes[CLASS_ia32_gp],
	.limited           = ia32_limit_gp_eax_ebx_ecx_edx,
	.should_be_same    = 1,
	.must_be_different = 0,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_gp_gp_NOREG_I = {
	.cls               = &ia32_reg_classes[CLASS_ia32_gp],
	.limited           = ia32_limit_gp_gp_NOREG,
	.should_be_same    = 0,
	.must_be_different = 0,
	.width             = 1,
	.ignore = true,
};

static const arch_register_req_t ia32_requirements_gp_ebp_I = {
	.cls               = &ia32_reg_classes[CLASS_ia32_gp],
	.limited           = ia32_limit_gp_ebp,
	.should_be_same    = 0,
	.must_be_different = 0,
	.width             = 1,
	.ignore = true,
};

static const arch_register_req_t ia32_requirements_gp_in_r1 = {
	.cls               = &ia32_reg_classes[CLASS_ia32_gp],
	.limited           = NULL,
	.should_be_same    = 2,
	.must_be_different = 0,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_fp_fp_NOREG_I = {
	.cls               = &ia32_reg_classes[CLASS_ia32_fp],
	.limited           = ia32_limit_fp_fp_NOREG,
	.should_be_same    = 0,
	.must_be_different = 0,
	.width             = 1,
	.ignore = true,
};

static const arch_register_req_t ia32_requirements_xmm_xmm_NOREG_I = {
	.cls               = &ia32_reg_classes[CLASS_ia32_xmm],
	.limited           = ia32_limit_xmm_xmm_NOREG,
	.should_be_same    = 0,
	.must_be_different = 0,
	.width             = 1,
	.ignore = true,
};

static const arch_register_req_t ia32_requirements_xmm_in_r0_not_in_r1 = {
	.cls               = &ia32_reg_classes[CLASS_ia32_xmm],
	.limited           = NULL,
	.should_be_same    = 1,
	.must_be_different = 2,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_gp_in_r0_not_in_r1 = {
	.cls               = &ia32_reg_classes[CLASS_ia32_gp],
	.limited           = NULL,
	.should_be_same    = 1,
	.must_be_different = 2,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_gp_in_r3 = {
	.cls               = &ia32_reg_classes[CLASS_ia32_gp],
	.limited           = NULL,
	.should_be_same    = 8,
	.must_be_different = 0,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_gp_in_r0_not_in_r1_not_in_r2 = {
	.cls               = &ia32_reg_classes[CLASS_ia32_gp],
	.limited           = NULL,
	.should_be_same    = 1,
	.must_be_different = 6,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_gp_in_r0_in_r1 = {
	.cls               = &ia32_reg_classes[CLASS_ia32_gp],
	.limited           = NULL,
	.should_be_same    = 3,
	.must_be_different = 0,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_gp_eax_ebx_ecx_edx_in_r3 = {
	.cls               = &ia32_reg_classes[CLASS_ia32_gp],
	.limited           = ia32_limit_gp_eax_ebx_ecx_edx,
	.should_be_same    = 8,
	.must_be_different = 0,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_xmm_in_r3 = {
	.cls               = &ia32_reg_classes[CLASS_ia32_xmm],
	.limited           = NULL,
	.should_be_same    = 8,
	.must_be_different = 0,
	.width             = 1,
};

static const arch_register_req_t ia32_requirements_fp_fp_K = {
	.cls   = &ia32_reg_classes[CLASS_ia32_fp],
	.width = 1,
	.kills_value = true,
};



ir_node *new_bd_ia32_Adc(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, ir_node *eflags, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
		eflags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Adc, ia32_mode_gp, 6, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_condcode_attr_t *const attr = (ia32_condcode_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_condition_code_t condition_code = x86_cc_carry;
	init_ia32_attributes(res, size);
	init_ia32_condcode_attributes(res, condition_code);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Add(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Add, ia32_mode_gp, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Add_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Add, ia32_mode_gp, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_eax_ebx_ecx_edx_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_AddMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_AddMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_AddMem_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_AddMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_AddSP(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *stack, ir_node *amount)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_single_reg_req_gp_esp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		stack,
		amount,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_AddSP, mode_T, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_esp_I;
	out_infos[1].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Adds(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Adds, ia32_mode_float64, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_xmm_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_And(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_And, ia32_mode_gp, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_And_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_And, ia32_mode_gp, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_eax_ebx_ecx_edx_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_AndMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_AndMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_AndMem_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_AndMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Andnp(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Andnp, ia32_mode_float64, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_xmm_in_r3_not_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Andp(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Andp, ia32_mode_float64, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_xmm_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Breakpoint(dbg_info *dbgi, ir_node *block, ir_node *mem)
{
	static arch_register_req_t const *in_reqs[] = {
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Breakpoint, mode_M, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Bsf(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *operand, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		operand,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Bsf, ia32_mode_gp, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_unary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Bsr(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *operand, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		operand,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Bsr, ia32_mode_gp, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_unary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Bswap(dbg_info *dbgi, ir_node *block, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Bswap, ia32_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Bswap16(dbg_info *dbgi, ir_node *block, ir_node *val)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Bswap16, ia32_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_8;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_eax_ebx_ecx_edx_in_r0;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Bt(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Bt, ia32_mode_flags, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_CMovcc(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val_false, ir_node *val_true, ir_node *eflags, x86_insn_size_t size, x86_condition_code_t condition_code)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val_false,
		val_true,
		eflags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_CMovcc, ia32_mode_gp, 6, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_condcode_attr_t *const attr = (ia32_condcode_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	init_ia32_condcode_attributes(res, condition_code);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r3_in_r4;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Call(dbg_info *dbgi, ir_node *block, int const arity, ir_node *const *const in, arch_register_req_t const **const in_reqs, int n_res, uint8_t pop, uint8_t n_reg_results)
{


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Call, mode_T, arity, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_call_attr_t *const attr = (ia32_call_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	init_ia32_call_attributes(res, pop, n_reg_results);
		set_ia32_am_support(res, ia32_am_unary);

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_ChangeCW(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_ChangeCW, ia32_mode_fpcw, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_not_scheduled;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fpcw;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Cltd(dbg_info *dbgi, ir_node *block, ir_node *val)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_single_reg_req_gp_eax,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Cltd, ia32_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	arch_set_additional_pressure(res, &ia32_reg_classes[CLASS_ia32_gp], 1);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_single_reg_req_gp_edx;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Cmc(dbg_info *dbgi, ir_node *block, ir_node *op0)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Cmc, ia32_mode_flags, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_condcode_attr_t *const attr = (ia32_condcode_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_condition_code_t condition_code = x86_cc_carry;
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	init_ia32_condcode_attributes(res, condition_code);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Cmp(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size, bool ins_permuted)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Cmp, ia32_mode_flags, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	attr->ins_permuted = ins_permuted;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_flags;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Cmp_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size, bool ins_permuted)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Cmp, ia32_mode_flags, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	attr->ins_permuted = ins_permuted;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_flags;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_CmpXChgMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *old, ir_node *new, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_single_reg_req_gp_eax,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		old,
		new,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_CmpXChgMem, mode_T, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_single_reg_req_gp_eax;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Const(dbg_info *dbgi, ir_node *block, const x86_imm32_t *imm)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Const, ia32_mode_gp, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_immediate_attr_t *const attr = (ia32_immediate_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	init_ia32_immediate_attributes(res, imm);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Conv_FP2FP(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Conv_FP2FP, ia32_mode_float64, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_unary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_xmm;
	out_infos[1].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Conv_FP2I(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Conv_FP2I, ia32_mode_gp, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_unary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;
	out_infos[1].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Conv_I2FP(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Conv_I2FP, ia32_mode_float64, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_unary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_xmm;
	out_infos[1].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Conv_I2I(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size, bool sign_extend)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Conv_I2I, ia32_mode_gp, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 5;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_unary);
	attr->sign_extend = sign_extend;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;
	out_infos[3].req = &arch_exec_requirement;
	out_infos[4].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Conv_I2I_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size, bool sign_extend)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Conv_I2I, ia32_mode_gp, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 5;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_unary);
	attr->sign_extend = sign_extend;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;
	out_infos[3].req = &arch_exec_requirement;
	out_infos[4].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_CopyB(dbg_info *dbgi, ir_node *block, ir_node *dest, ir_node *source, ir_node *count, ir_node *mem, unsigned size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_single_reg_req_gp_edi,
		&ia32_single_reg_req_gp_esi,
		&ia32_single_reg_req_gp_ecx,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		dest,
		source,
		count,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_CopyB, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 4;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_copyb_attr_t *const attr = (ia32_copyb_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	init_ia32_copyb_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_single_reg_req_gp_edi;
	out_infos[1].req = &ia32_single_reg_req_gp_esi;
	out_infos[2].req = &ia32_single_reg_req_gp_ecx;
	out_infos[3].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_CopyB_i(dbg_info *dbgi, ir_node *block, ir_node *dest, ir_node *source, ir_node *mem, unsigned size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_single_reg_req_gp_edi,
		&ia32_single_reg_req_gp_esi,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		dest,
		source,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_CopyB_i, mode_T, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_copyb_attr_t *const attr = (ia32_copyb_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	init_ia32_copyb_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_single_reg_req_gp_edi;
	out_infos[1].req = &ia32_single_reg_req_gp_esi;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_CopyEbpEsp(dbg_info *dbgi, ir_node *block, ir_node *ebp)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_single_reg_req_gp_ebp,
	};

	/* construct in array */
	ir_node *const in[] = {
		ebp,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_CopyEbpEsp, ia32_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_esp_I;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_CvtSI2SD(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_CvtSI2SD, ia32_mode_float64, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_unary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_xmm;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_CvtSI2SS(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_CvtSI2SS, ia32_mode_float64, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_unary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_xmm;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Cwtl(dbg_info *dbgi, ir_node *block, ir_node *val)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_single_reg_req_gp_eax,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Cwtl, ia32_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_single_reg_req_gp_eax;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Dec(dbg_info *dbgi, ir_node *block, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Dec, ia32_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_DecMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_DecMem, mode_T, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Div(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *divisor, ir_node *dividend_low, ir_node *dividend_high, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_single_reg_req_gp_eax,
		&ia32_single_reg_req_gp_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		divisor,
		dividend_low,
		dividend_high,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Div, mode_T, 6, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 6;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_unary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_single_reg_req_gp_eax;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;
	out_infos[3].req = &ia32_single_reg_req_gp_edx;
	out_infos[4].req = &arch_exec_requirement;
	out_infos[5].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Divs(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Divs, mode_T, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_xmm_in_r3_not_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Enter(dbg_info *dbgi, ir_node *block, ir_node *op0)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_single_reg_req_gp_esp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Enter, mode_T, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_single_reg_req_gp_ebp;
	out_infos[1].req = &ia32_requirements_gp_esp_I;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_FldCW(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_FldCW, ia32_mode_fpcw, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_16;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fpcw;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_FnstCW(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *fpcw)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_fpcw,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		fpcw,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_FnstCW, mode_M, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_16;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_FnstCWNOP(dbg_info *dbgi, ir_node *block, ir_node *fpcw)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_fpcw,
	};

	/* construct in array */
	ir_node *const in[] = {
		fpcw,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_FnstCWNOP, mode_M, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_16;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_FtstFnstsw(dbg_info *dbgi, ir_node *block, ir_node *left, bool ins_permuted)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_fp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_FtstFnstsw, ia32_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_16;	ia32_request_x87_sim(irg);
	init_ia32_attributes(res, size);
	attr->ins_permuted = ins_permuted;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_single_reg_req_gp_eax;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_FucomFnstsw(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, bool ins_permuted)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_fp,
		&ia32_class_reg_req_fp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_FucomFnstsw, ia32_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_16;
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
	attr->attr.ins_permuted = ins_permuted;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_single_reg_req_gp_eax;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Fucomi(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, bool ins_permuted)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_fp,
		&ia32_class_reg_req_fp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Fucomi, ia32_mode_flags, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_80;
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
	attr->attr.ins_permuted = ins_permuted;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_FucomppFnstsw(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, bool ins_permuted)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_fp,
		&ia32_class_reg_req_fp,
	};

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_FucomppFnstsw, ia32_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_16;
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
	attr->attr.ins_permuted = ins_permuted;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_single_reg_req_gp_eax;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_GetEIP(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_GetEIP, ia32_mode_gp, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_IDiv(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *divisor, ir_node *dividend_low, ir_node *dividend_high, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_single_reg_req_gp_eax,
		&ia32_single_reg_req_gp_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		divisor,
		dividend_low,
		dividend_high,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_IDiv, mode_T, 6, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 6;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_unary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_single_reg_req_gp_eax;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;
	out_infos[3].req = &ia32_single_reg_req_gp_edx;
	out_infos[4].req = &arch_exec_requirement;
	out_infos[5].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_IJmp(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *target)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		target,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_IJmp, mode_X, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_unary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_exec_requirement;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_IMul(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_IMul, ia32_mode_gp, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_IMul_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_IMul, ia32_mode_gp, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_eax_ebx_ecx_edx_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_IMul1OP(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_single_reg_req_gp_eax,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_IMul1OP, mode_T, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 4;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_single_reg_req_gp_eax;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;
	out_infos[3].req = &ia32_single_reg_req_gp_edx;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_IMulImm(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_IMulImm, ia32_mode_gp, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Immediate(dbg_info *dbgi, ir_node *block, const x86_imm32_t *imm)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Immediate, ia32_mode_gp, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_not_scheduled;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_immediate_attr_t *const attr = (ia32_immediate_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	init_ia32_immediate_attributes(res, imm);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_gp_NOREG_I;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Inc(dbg_info *dbgi, ir_node *block, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Inc, ia32_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_IncMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_IncMem, mode_T, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Inport(dbg_info *dbgi, ir_node *block, ir_node *port, ir_node *mem, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_single_reg_req_gp_edx,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		port,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Inport, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_single_reg_req_gp_eax;
	out_infos[1].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Jcc(dbg_info *dbgi, ir_node *block, ir_node *eflags, x86_condition_code_t condition_code)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		eflags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Jcc, mode_T, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_fallthrough;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_condcode_attr_t *const attr = (ia32_condcode_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	init_ia32_condcode_attributes(res, condition_code);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_exec_requirement;
	out_infos[1].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Jmp(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Jmp, mode_X, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_simple_jump;
	irn_flags |= arch_irn_flag_fallthrough;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_LdTls(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_LdTls, ia32_mode_gp, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Lea(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Lea, ia32_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Leave(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1)
{
	static arch_register_req_t const *in_reqs[] = {
		&arch_memory_requirement,
		&ia32_single_reg_req_gp_ebp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Leave, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_ebp_I;
	out_infos[1].req = &arch_memory_requirement;
	out_infos[2].req = &ia32_requirements_gp_esp_I;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Load(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, x86_insn_size_t size, bool sign_extend)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Load, mode_T, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 5;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	attr->sign_extend = sign_extend;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;
	out_infos[3].req = &arch_exec_requirement;
	out_infos[4].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Maxs(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Maxs, ia32_mode_float64, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_xmm_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Mins(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Mins, ia32_mode_float64, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_xmm_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Minus64(dbg_info *dbgi, ir_node *block, ir_node *low, ir_node *high)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		low,
		high,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Minus64, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0;
	out_infos[1].req = &ia32_requirements_gp_in_r1;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Movd(dbg_info *dbgi, ir_node *block, ir_node *op0)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Movd, ia32_mode_float64, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_xmm;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Mul(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_single_reg_req_gp_eax,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Mul, mode_T, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 4;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_single_reg_req_gp_eax;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;
	out_infos[3].req = &ia32_single_reg_req_gp_edx;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Muls(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Muls, ia32_mode_float64, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_xmm_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Neg(dbg_info *dbgi, ir_node *block, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Neg, ia32_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_NegMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_NegMem, mode_T, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_NoReg_FP(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_NoReg_FP, x86_mode_E, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_not_scheduled;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	ia32_request_x87_sim(irg);
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_fp_fp_NOREG_I;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_NoReg_GP(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_NoReg_GP, ia32_mode_gp, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_not_scheduled;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_gp_NOREG_I;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_NoReg_XMM(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_NoReg_XMM, ia32_mode_float64, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_not_scheduled;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_xmm_xmm_NOREG_I;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Not(dbg_info *dbgi, ir_node *block, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Not, ia32_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Not_8bit(dbg_info *dbgi, ir_node *block, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Not, ia32_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_NotMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_NotMem, mode_T, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Or(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Or, ia32_mode_gp, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Or_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Or, ia32_mode_gp, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_eax_ebx_ecx_edx_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_OrMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_OrMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_OrMem_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_OrMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Orp(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Orp, ia32_mode_float64, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_xmm_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Outport(dbg_info *dbgi, ir_node *block, ir_node *port, ir_node *value, ir_node *mem, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_single_reg_req_gp_edx,
		&ia32_single_reg_req_gp_eax,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		port,
		value,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Outport, mode_M, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Pop(dbg_info *dbgi, ir_node *block, ir_node *mem, ir_node *stack, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&arch_memory_requirement,
		&ia32_single_reg_req_gp_esp,
	};

	/* construct in array */
	ir_node *const in[] = {
		mem,
		stack,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Pop, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 4;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;
	out_infos[3].req = &ia32_requirements_gp_esp_I;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Pop_ebp(dbg_info *dbgi, ir_node *block, ir_node *mem, ir_node *stack, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&arch_memory_requirement,
		&ia32_single_reg_req_gp_esp,
	};

	/* construct in array */
	ir_node *const in[] = {
		mem,
		stack,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Pop, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 4;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_ebp_I;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;
	out_infos[3].req = &ia32_requirements_gp_esp_I;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_PopMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *stack, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_single_reg_req_gp_esp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		stack,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_PopMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 4;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;
	out_infos[3].req = &ia32_requirements_gp_esp_I;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Popcnt(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *operand, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		operand,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Popcnt, ia32_mode_gp, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_unary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Prefetch(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Prefetch, mode_M, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_8;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_PrefetchNTA(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_PrefetchNTA, mode_M, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_8;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_PrefetchT0(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_PrefetchT0, mode_M, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_8;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_PrefetchT1(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_PrefetchT1, mode_M, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_8;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_PrefetchT2(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_PrefetchT2, mode_M, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_8;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_PrefetchW(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_PrefetchW, mode_M, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_8;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Pslld(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_xmm,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Pslld, ia32_mode_float64, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_xmm_in_r0_not_in_r1;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Psllq(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_xmm,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Psllq, ia32_mode_float64, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_xmm_in_r0_not_in_r1;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Psrld(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_xmm,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
		op1,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Psrld, ia32_mode_float64, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_xmm_in_r0_not_in_r1;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Push(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, ir_node *stack, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_single_reg_req_gp_esp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
		stack,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Push, mode_T, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_unary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;
	out_infos[1].req = &ia32_requirements_gp_esp_I;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_PushEax(dbg_info *dbgi, ir_node *block, ir_node *stack)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_single_reg_req_gp_esp,
	};

	/* construct in array */
	ir_node *const in[] = {
		stack,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_PushEax, ia32_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_esp_I;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Ret(dbg_info *dbgi, ir_node *block, int const arity, ir_node *const *const in, arch_register_req_t const **const in_reqs, uint16_t pop)
{


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Ret, mode_X, arity, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_return_attr_t *const attr = (ia32_return_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	init_ia32_return_attributes(res, pop);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Rol(dbg_info *dbgi, ir_node *block, ir_node *val, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Rol, ia32_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0_not_in_r1;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Rol_8bit(dbg_info *dbgi, ir_node *block, ir_node *val, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_requirements_gp_eax_ebx_ecx_edx,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Rol, ia32_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0_not_in_r1;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_RolMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_RolMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Ror(dbg_info *dbgi, ir_node *block, ir_node *val, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Ror, ia32_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0_not_in_r1;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Ror_8bit(dbg_info *dbgi, ir_node *block, ir_node *val, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_requirements_gp_eax_ebx_ecx_edx,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Ror, ia32_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0_not_in_r1;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_RorMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_RorMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Sahf(dbg_info *dbgi, ir_node *block, ir_node *val)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_single_reg_req_gp_eax,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Sahf, ia32_mode_flags, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_16;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Sar(dbg_info *dbgi, ir_node *block, ir_node *val, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Sar, ia32_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0_not_in_r1;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Sar_8bit(dbg_info *dbgi, ir_node *block, ir_node *val, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_requirements_gp_eax_ebx_ecx_edx,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Sar, ia32_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0_not_in_r1;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_SarMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_SarMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Sbb(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *minuend, ir_node *subtrahend, ir_node *eflags, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		minuend,
		subtrahend,
		eflags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Sbb, ia32_mode_gp, 6, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_condcode_attr_t *const attr = (ia32_condcode_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_condition_code_t condition_code = x86_cc_carry;
	init_ia32_attributes(res, size);
	init_ia32_condcode_attributes(res, condition_code);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r3;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Sbb0(dbg_info *dbgi, ir_node *block, ir_node *op0, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		op0,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Sbb0, ia32_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_condcode_attr_t *const attr = (ia32_condcode_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_condition_code_t condition_code = x86_cc_carry;
	init_ia32_attributes(res, size);
	init_ia32_condcode_attributes(res, condition_code);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Setcc(dbg_info *dbgi, ir_node *block, ir_node *eflags, x86_condition_code_t condition_code)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		eflags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Setcc, ia32_mode_gp, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_condcode_attr_t *const attr = (ia32_condcode_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_8;
	init_ia32_attributes(res, size);
	init_ia32_condcode_attributes(res, condition_code);
	if (condition_code & x86_cc_additional_float_cases) {
		arch_add_irn_flags(res, arch_irn_flag_modify_flags);
		/* attr->latency = 3; */
	}

	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_eax_ebx_ecx_edx;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_SetccMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *eflags, x86_condition_code_t condition_code)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_flags,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		eflags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_SetccMem, mode_M, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_condcode_attr_t *const attr = (ia32_condcode_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_8;
	init_ia32_attributes(res, size);
	init_ia32_condcode_attributes(res, condition_code);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Shl(dbg_info *dbgi, ir_node *block, ir_node *val, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Shl, ia32_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0_not_in_r1;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Shl_8bit(dbg_info *dbgi, ir_node *block, ir_node *val, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_requirements_gp_eax_ebx_ecx_edx,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Shl, ia32_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0_not_in_r1;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_ShlD(dbg_info *dbgi, ir_node *block, ir_node *val_high, ir_node *val_low, ir_node *count)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val_high,
		val_low,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_ShlD, ia32_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0_not_in_r1_not_in_r2;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_ShlD_imm(dbg_info *dbgi, ir_node *block, ir_node *val_high, ir_node *val_low, ir_node *count)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val_high,
		val_low,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_ShlD, ia32_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0_in_r1;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_ShlMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_ShlMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Shr(dbg_info *dbgi, ir_node *block, ir_node *val, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Shr, ia32_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0_not_in_r1;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Shr_8bit(dbg_info *dbgi, ir_node *block, ir_node *val, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_requirements_gp_eax_ebx_ecx_edx,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Shr, ia32_mode_gp, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0_not_in_r1;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_ShrD(dbg_info *dbgi, ir_node *block, ir_node *val_high, ir_node *val_low, ir_node *count)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val_high,
		val_low,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_ShrD, ia32_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0_not_in_r1_not_in_r2;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_ShrD_imm(dbg_info *dbgi, ir_node *block, ir_node *val_high, ir_node *val_low, ir_node *count)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		val_high,
		val_low,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_ShrD, ia32_mode_gp, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r0_in_r1;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_ShrMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *count, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_single_reg_req_gp_ecx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		count,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_ShrMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Stc(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Stc, ia32_mode_flags, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Store(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Store, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;
	out_infos[1].req = &arch_exec_requirement;
	out_infos[2].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Store_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Store, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;
	out_infos[1].req = &arch_exec_requirement;
	out_infos[2].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Sub(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *minuend, ir_node *subtrahend, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		minuend,
		subtrahend,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Sub, ia32_mode_gp, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r3;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Sub_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *minuend, ir_node *subtrahend, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		minuend,
		subtrahend,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Sub, ia32_mode_gp, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_eax_ebx_ecx_edx_in_r3;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_SubMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_SubMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_SubMem_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_SubMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_SubSP(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *stack, ir_node *amount)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_single_reg_req_gp_esp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		stack,
		amount,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_SubSP, mode_T, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t size = X86_SIZE_32;
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_esp_I;
	out_infos[1].req = &ia32_class_reg_req_gp;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Subs(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *minuend, ir_node *subtrahend, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		minuend,
		subtrahend,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Subs, ia32_mode_float64, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_xmm_in_r3;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_SwitchJmp(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, int n_res, const ir_switch_table *switch_table, const ir_entity *table_entity)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_SwitchJmp, mode_T, 2, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_switch_attr_t *const attr = (ia32_switch_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	init_ia32_switch_attributes(res, switch_table, table_entity);

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Test(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size, bool ins_permuted)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Test, ia32_mode_flags, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	attr->ins_permuted = ins_permuted;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_flags;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Test_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size, bool ins_permuted)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Test, ia32_mode_flags, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	attr->ins_permuted = ins_permuted;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_flags;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_UD2(dbg_info *dbgi, ir_node *block, ir_node *mem)
{
	static arch_register_req_t const *in_reqs[] = {
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_UD2, mode_M, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Ucomis(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, bool ins_permuted)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Ucomis, ia32_mode_flags, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	attr->ins_permuted = ins_permuted;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Xor(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Xor, ia32_mode_gp, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Xor_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Xor, ia32_mode_gp, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_eax_ebx_ecx_edx_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Xor0(dbg_info *dbgi, ir_node *block, x86_insn_size_t size)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Xor0, ia32_mode_gp, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_gp;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_XorHighLow(dbg_info *dbgi, ir_node *block, ir_node *value)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		value,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_XorHighLow, mode_T, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 2;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_8;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_gp_eax_ebx_ecx_edx_in_r0;
	out_infos[1].req = &ia32_class_reg_req_flags;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_XorMem(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_gp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_XorMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_XorMem_8bit(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_gp_eax_ebx_ecx_edx,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_XorMem, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_modify_flags;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_Xorp(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_Xorp, ia32_mode_float64, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_requirements_xmm_in_r3_in_r4;
	out_infos[1].req = &ia32_class_reg_req_flags;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_emms(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_emms, mode_ANY, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;	ia32_request_x87_sim(irg);
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fabs(dbg_info *dbgi, ir_node *block, ir_node *value)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_fp,
	};

	/* construct in array */
	ir_node *const in[] = {
		value,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fabs, x86_mode_E, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_80;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fadd(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, ir_node *fpcw, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_fp,
		&ia32_class_reg_req_fp,
		&ia32_class_reg_req_fpcw,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
		fpcw,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fadd, x86_mode_E, 6, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fchs(dbg_info *dbgi, ir_node *block, ir_node *value)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_fp,
	};

	/* construct in array */
	ir_node *const in[] = {
		value,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fchs, x86_mode_E, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_80;
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fdiv(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, ir_node *fpcw, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_fp,
		&ia32_class_reg_req_fp,
		&ia32_class_reg_req_fpcw,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
		fpcw,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fdiv, mode_T, 6, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fdup(dbg_info *dbgi, ir_node *block, ir_node *val, const arch_register_t *reg)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_fp,
	};

	/* construct in array */
	ir_node *const in[] = {
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fdup, x86_mode_E, 1, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_80;
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
	attr->x87.reg = reg;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_femms(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_femms, mode_ANY, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_32;	ia32_request_x87_sim(irg);
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_ffreep(dbg_info *dbgi, ir_node *block, const arch_register_t *reg)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_ffreep, mode_ANY, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_80;
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
	attr->x87.reg = reg;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fild(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fild, mode_T, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 5;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	ia32_request_x87_sim(irg);
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;
	out_infos[3].req = &arch_exec_requirement;
	out_infos[4].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fist(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, ir_node *fpcw, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_fp,
		&ia32_class_reg_req_fpcw,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
		fpcw,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fist, mode_T, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;
	out_infos[1].req = &arch_exec_requirement;
	out_infos[2].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fistp(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, ir_node *fpcw, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_fp_fp_K,
		&ia32_class_reg_req_fpcw,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
		fpcw,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fistp, mode_T, 5, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;
	out_infos[1].req = &arch_exec_requirement;
	out_infos[2].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fisttp(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_fp_fp_K,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fisttp, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;
	out_infos[1].req = &arch_exec_requirement;
	out_infos[2].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fld(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fld, mode_T, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 5;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	ia32_request_x87_sim(irg);
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;
	out_infos[3].req = &arch_exec_requirement;
	out_infos[4].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fld1(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fld1, x86_mode_E, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_80;
	ia32_request_x87_sim(irg);
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fldl2e(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fldl2e, x86_mode_E, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_80;
	ia32_request_x87_sim(irg);
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fldl2t(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fldl2t, x86_mode_E, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_80;
	ia32_request_x87_sim(irg);
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fldlg2(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fldlg2, x86_mode_E, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_80;
	ia32_request_x87_sim(irg);
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fldln2(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fldln2, x86_mode_E, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_80;
	ia32_request_x87_sim(irg);
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fldpi(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fldpi, x86_mode_E, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_80;
	ia32_request_x87_sim(irg);
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fldz(dbg_info *dbgi, ir_node *block)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fldz, x86_mode_E, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_80;
	ia32_request_x87_sim(irg);
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fmul(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, ir_node *fpcw, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_fp,
		&ia32_class_reg_req_fp,
		&ia32_class_reg_req_fpcw,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
		fpcw,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fmul, x86_mode_E, 6, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fpop(dbg_info *dbgi, ir_node *block, const arch_register_t *reg)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fpop, mode_ANY, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_80;
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
	attr->x87.reg = reg;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fst(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_fp,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fst, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;
	out_infos[1].req = &arch_exec_requirement;
	out_infos[2].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fstp(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_requirements_fp_fp_K,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fstp, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;
	out_infos[1].req = &arch_exec_requirement;
	out_infos[2].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fsub(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *left, ir_node *right, ir_node *fpcw, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_fp,
		&ia32_class_reg_req_fp,
		&ia32_class_reg_req_fpcw,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		left,
		right,
		fpcw,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fsub, x86_mode_E, 6, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
		set_ia32_am_support(res, ia32_am_binary);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_fp;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_fxch(dbg_info *dbgi, ir_node *block, const arch_register_t *reg)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_fxch, mode_ANY, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_x87_attr_t *const attr = (ia32_x87_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	x86_insn_size_t const size = X86_SIZE_80;
	init_ia32_attributes(res, size);
	init_ia32_x87_attributes(res);
	attr->x87.reg = reg;
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_no_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_l_Adc(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right, ir_node *eflags, ir_mode *mode)
{

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
		eflags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_l_Adc, mode, 3, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_l_Add(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_l_Add, mode_T, 2, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_l_FloattoLL(dbg_info *dbgi, ir_node *block, ir_node *val)
{

	/* construct in array */
	ir_node *const in[] = {
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_l_FloattoLL, mode_T, 1, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_l_IMul(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_l_IMul, mode_T, 2, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_l_LLtoFloat(dbg_info *dbgi, ir_node *block, ir_node *val_high, ir_node *val_low, ir_mode *mode)
{

	/* construct in array */
	ir_node *const in[] = {
		val_high,
		val_low,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_l_LLtoFloat, mode, 2, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_l_Minus64(dbg_info *dbgi, ir_node *block, ir_node *low, ir_node *high)
{

	/* construct in array */
	ir_node *const in[] = {
		low,
		high,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_l_Minus64, mode_T, 2, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_l_Mul(dbg_info *dbgi, ir_node *block, ir_node *left, ir_node *right)
{

	/* construct in array */
	ir_node *const in[] = {
		left,
		right,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_l_Mul, mode_T, 2, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_l_Sbb(dbg_info *dbgi, ir_node *block, ir_node *minuend, ir_node *subtrahend, ir_node *eflags, ir_mode *mode)
{

	/* construct in array */
	ir_node *const in[] = {
		minuend,
		subtrahend,
		eflags,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_l_Sbb, mode, 3, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_l_Sub(dbg_info *dbgi, ir_node *block, ir_node *minuend, ir_node *subtrahend)
{

	/* construct in array */
	ir_node *const in[] = {
		minuend,
		subtrahend,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_l_Sub, mode_T, 2, in);

	/* init node attributes */

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_xAllOnes(dbg_info *dbgi, ir_node *block, x86_insn_size_t size)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_xAllOnes, ia32_mode_float64, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_xmm;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_xLoad(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_xLoad, mode_T, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 5;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_xmm;
	out_infos[1].req = &arch_no_requirement;
	out_infos[2].req = &arch_memory_requirement;
	out_infos[3].req = &arch_exec_requirement;
	out_infos[4].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_xPzero(dbg_info *dbgi, ir_node *block, x86_insn_size_t size)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_xPzero, ia32_mode_float64, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_xmm;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_xStore(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_xStore, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;
	out_infos[1].req = &arch_exec_requirement;
	out_infos[2].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_xZero(dbg_info *dbgi, ir_node *block, x86_insn_size_t size)
{
	arch_register_req_t const **const in_reqs = NULL;


	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_xZero, ia32_mode_float64, 0, NULL);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	irn_flags |= arch_irn_flag_rematerializable;
	int const n_res = 1;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_xmm;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_xxLoad(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_xxLoad, mode_T, 3, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 4;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &ia32_class_reg_req_xmm;
	out_infos[1].req = &arch_memory_requirement;
	out_infos[2].req = &arch_exec_requirement;
	out_infos[3].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}

ir_node *new_bd_ia32_xxStore(dbg_info *dbgi, ir_node *block, ir_node *base, ir_node *index, ir_node *mem, ir_node *val, x86_insn_size_t size)
{
	static arch_register_req_t const *in_reqs[] = {
		&ia32_class_reg_req_gp,
		&ia32_class_reg_req_gp,
		&arch_memory_requirement,
		&ia32_class_reg_req_xmm,
	};

	/* construct in array */
	ir_node *const in[] = {
		base,
		index,
		mem,
		val,
	};

	ir_graph *const irg = get_irn_irg(block);
	ir_node  *const res = new_ir_node(dbgi, irg, block, op_ia32_xxStore, mode_T, 4, in);

	/* init node attributes */

	/* flags */
	arch_irn_flags_t irn_flags = arch_irn_flags_none;
	int const n_res = 3;
	be_info_init_irn(res, irn_flags, in_reqs, n_res);
	ia32_attr_t *const attr = (ia32_attr_t*)get_irn_generic_attr(res);
	(void)attr; /* avoid potential warning */
	init_ia32_attributes(res, size);
	reg_out_info_t *const out_infos = be_get_info(res)->out_infos;
	out_infos[0].req = &arch_memory_requirement;
	out_infos[1].req = &arch_exec_requirement;
	out_infos[2].req = &arch_exec_requirement;

	verify_new_node(res);
	return optimize_node(res);
}


/**
 * Creates the ia32 specific Firm machine operations
 * needed for the assembler irgs.
 */
void ia32_create_opcodes(void)
{
	ir_op *op;
	int    cur_opcode = get_next_ir_opcodes(iro_ia32_last);

	ia32_opcode_start = cur_opcode;
	op = new_ir_op(cur_opcode + iro_ia32_Adc, "ia32_Adc", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_condcode_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_condcode_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Adc = op;
	op = new_ir_op(cur_opcode + iro_ia32_Add, "ia32_Add", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Add = op;
	op = new_ir_op(cur_opcode + iro_ia32_AddMem, "ia32_AddMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_AddMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_AddSP, "ia32_AddSP", op_pin_state_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_AddSP = op;
	op = new_ir_op(cur_opcode + iro_ia32_Adds, "ia32_Adds", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_Adds = op;
	op = new_ir_op(cur_opcode + iro_ia32_And, "ia32_And", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_And = op;
	op = new_ir_op(cur_opcode + iro_ia32_AndMem, "ia32_AndMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_AndMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_Andnp, "ia32_Andnp", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_Andnp = op;
	op = new_ir_op(cur_opcode + iro_ia32_Andp, "ia32_Andp", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_Andp = op;
	op = new_ir_op(cur_opcode + iro_ia32_Breakpoint, "ia32_Breakpoint", op_pin_state_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 0);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_Breakpoint = op;
	op = new_ir_op(cur_opcode + iro_ia32_Bsf, "ia32_Bsf", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Bsf = op;
	op = new_ir_op(cur_opcode + iro_ia32_Bsr, "ia32_Bsr", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Bsr = op;
	op = new_ir_op(cur_opcode + iro_ia32_Bswap, "ia32_Bswap", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Bswap = op;
	op = new_ir_op(cur_opcode + iro_ia32_Bswap16, "ia32_Bswap16", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Bswap16 = op;
	op = new_ir_op(cur_opcode + iro_ia32_Bt, "ia32_Bt", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Bt = op;
	op = new_ir_op(cur_opcode + iro_ia32_CMovcc, "ia32_CMovcc", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_condcode_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_condcode_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_CMovcc = op;
	op = new_ir_op(cur_opcode + iro_ia32_Call, "ia32_Call", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_call_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_call_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_Call = op;
	op = new_ir_op(cur_opcode + iro_ia32_ChangeCW, "ia32_ChangeCW", op_pin_state_pinned, irop_flag_constlike|irop_flag_dump_noblock, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_ChangeCW = op;
	op = new_ir_op(cur_opcode + iro_ia32_Cltd, "ia32_Cltd", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Cltd = op;
	op = new_ir_op(cur_opcode + iro_ia32_Cmc, "ia32_Cmc", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_condcode_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_condcode_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Cmc = op;
	op = new_ir_op(cur_opcode + iro_ia32_Cmp, "ia32_Cmp", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Cmp = op;
	op = new_ir_op(cur_opcode + iro_ia32_CmpXChgMem, "ia32_CmpXChgMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_CmpXChgMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_Const, "ia32_Const", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(ia32_immediate_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_immediate_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Const = op;
	op = new_ir_op(cur_opcode + iro_ia32_Conv_FP2FP, "ia32_Conv_FP2FP", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 8);
	op_ia32_Conv_FP2FP = op;
	op = new_ir_op(cur_opcode + iro_ia32_Conv_FP2I, "ia32_Conv_FP2I", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 10);
	op_ia32_Conv_FP2I = op;
	op = new_ir_op(cur_opcode + iro_ia32_Conv_I2FP, "ia32_Conv_I2FP", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 10);
	op_ia32_Conv_I2FP = op;
	op = new_ir_op(cur_opcode + iro_ia32_Conv_I2I, "ia32_Conv_I2I", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_Conv_I2I_mem);
	ir_op_set_fragile_indices(op, pn_ia32_Conv_I2I_X_regular, pn_ia32_Conv_I2I_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Conv_I2I = op;
	op = new_ir_op(cur_opcode + iro_ia32_CopyB, "ia32_CopyB", op_pin_state_floats, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_copyb_attr_t));
	ir_op_set_memory_index(op, 3);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_copyb_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 250);
	op_ia32_CopyB = op;
	op = new_ir_op(cur_opcode + iro_ia32_CopyB_i, "ia32_CopyB_i", op_pin_state_floats, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_copyb_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_copyb_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_CopyB_i = op;
	op = new_ir_op(cur_opcode + iro_ia32_CopyEbpEsp, "ia32_CopyEbpEsp", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_CopyEbpEsp = op;
	op = new_ir_op(cur_opcode + iro_ia32_CvtSI2SD, "ia32_CvtSI2SD", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_CvtSI2SD = op;
	op = new_ir_op(cur_opcode + iro_ia32_CvtSI2SS, "ia32_CvtSI2SS", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_CvtSI2SS = op;
	op = new_ir_op(cur_opcode + iro_ia32_Cwtl, "ia32_Cwtl", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Cwtl = op;
	op = new_ir_op(cur_opcode + iro_ia32_Dec, "ia32_Dec", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Dec = op;
	op = new_ir_op(cur_opcode + iro_ia32_DecMem, "ia32_DecMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_DecMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_Div, "ia32_Div", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_Div_mem);
	ir_op_set_fragile_indices(op, pn_ia32_Div_X_regular, pn_ia32_Div_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 25);
	op_ia32_Div = op;
	op = new_ir_op(cur_opcode + iro_ia32_Divs, "ia32_Divs", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 16);
	op_ia32_Divs = op;
	op = new_ir_op(cur_opcode + iro_ia32_Enter, "ia32_Enter", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 15);
	op_ia32_Enter = op;
	op = new_ir_op(cur_opcode + iro_ia32_FldCW, "ia32_FldCW", op_pin_state_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 5);
	op_ia32_FldCW = op;
	op = new_ir_op(cur_opcode + iro_ia32_FnstCW, "ia32_FnstCW", op_pin_state_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 5);
	op_ia32_FnstCW = op;
	op = new_ir_op(cur_opcode + iro_ia32_FnstCWNOP, "ia32_FnstCWNOP", op_pin_state_pinned, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_FnstCWNOP = op;
	op = new_ir_op(cur_opcode + iro_ia32_FtstFnstsw, "ia32_FtstFnstsw", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_FtstFnstsw = op;
	op = new_ir_op(cur_opcode + iro_ia32_FucomFnstsw, "ia32_FucomFnstsw", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_x87_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_x87_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_FucomFnstsw = op;
	op = new_ir_op(cur_opcode + iro_ia32_Fucomi, "ia32_Fucomi", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_x87_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_x87_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_Fucomi = op;
	op = new_ir_op(cur_opcode + iro_ia32_FucomppFnstsw, "ia32_FucomppFnstsw", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_x87_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_x87_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_FucomppFnstsw = op;
	op = new_ir_op(cur_opcode + iro_ia32_GetEIP, "ia32_GetEIP", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 5);
	op_ia32_GetEIP = op;
	op = new_ir_op(cur_opcode + iro_ia32_IDiv, "ia32_IDiv", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_IDiv_mem);
	ir_op_set_fragile_indices(op, pn_ia32_IDiv_X_regular, pn_ia32_IDiv_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 25);
	op_ia32_IDiv = op;
	op = new_ir_op(cur_opcode + iro_ia32_IJmp, "ia32_IJmp", op_pin_state_pinned, irop_flag_cfopcode|irop_flag_unknown_jump|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_IJmp = op;
	op = new_ir_op(cur_opcode + iro_ia32_IMul, "ia32_IMul", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 5);
	op_ia32_IMul = op;
	op = new_ir_op(cur_opcode + iro_ia32_IMul1OP, "ia32_IMul1OP", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 5);
	op_ia32_IMul1OP = op;
	op = new_ir_op(cur_opcode + iro_ia32_IMulImm, "ia32_IMulImm", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 5);
	op_ia32_IMulImm = op;
	op = new_ir_op(cur_opcode + iro_ia32_Immediate, "ia32_Immediate", op_pin_state_pinned, irop_flag_constlike, oparity_any, -1, sizeof(ia32_immediate_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_immediate_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_hash(op, ia32_hash_Immediate);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_Immediate = op;
	op = new_ir_op(cur_opcode + iro_ia32_Inc, "ia32_Inc", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Inc = op;
	op = new_ir_op(cur_opcode + iro_ia32_IncMem, "ia32_IncMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_IncMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_Inport, "ia32_Inport", op_pin_state_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 1);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Inport = op;
	op = new_ir_op(cur_opcode + iro_ia32_Jcc, "ia32_Jcc", op_pin_state_pinned, irop_flag_cfopcode|irop_flag_forking, oparity_any, -1, sizeof(ia32_condcode_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_condcode_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_Jcc = op;
	op = new_ir_op(cur_opcode + iro_ia32_Jmp, "ia32_Jmp", op_pin_state_pinned, irop_flag_cfopcode, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Jmp = op;
	op = new_ir_op(cur_opcode + iro_ia32_LdTls, "ia32_LdTls", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_LdTls = op;
	op = new_ir_op(cur_opcode + iro_ia32_Lea, "ia32_Lea", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_Lea = op;
	op = new_ir_op(cur_opcode + iro_ia32_Leave, "ia32_Leave", op_pin_state_floats, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 0);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_Leave = op;
	op = new_ir_op(cur_opcode + iro_ia32_Load, "ia32_Load", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_Load_mem);
	ir_op_set_fragile_indices(op, pn_ia32_Load_X_regular, pn_ia32_Load_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_Load = op;
	op = new_ir_op(cur_opcode + iro_ia32_Maxs, "ia32_Maxs", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_Maxs = op;
	op = new_ir_op(cur_opcode + iro_ia32_Mins, "ia32_Mins", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_Mins = op;
	op = new_ir_op(cur_opcode + iro_ia32_Minus64, "ia32_Minus64", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_Minus64 = op;
	op = new_ir_op(cur_opcode + iro_ia32_Movd, "ia32_Movd", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Movd = op;
	op = new_ir_op(cur_opcode + iro_ia32_Mul, "ia32_Mul", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 10);
	op_ia32_Mul = op;
	op = new_ir_op(cur_opcode + iro_ia32_Muls, "ia32_Muls", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_Muls = op;
	op = new_ir_op(cur_opcode + iro_ia32_Neg, "ia32_Neg", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Neg = op;
	op = new_ir_op(cur_opcode + iro_ia32_NegMem, "ia32_NegMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_NegMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_NoReg_FP, "ia32_NoReg_FP", op_pin_state_pinned, irop_flag_constlike|irop_flag_dump_noblock, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_NoReg_FP = op;
	op = new_ir_op(cur_opcode + iro_ia32_NoReg_GP, "ia32_NoReg_GP", op_pin_state_pinned, irop_flag_constlike|irop_flag_dump_noblock, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_NoReg_GP = op;
	op = new_ir_op(cur_opcode + iro_ia32_NoReg_XMM, "ia32_NoReg_XMM", op_pin_state_pinned, irop_flag_constlike|irop_flag_dump_noblock, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_NoReg_XMM = op;
	op = new_ir_op(cur_opcode + iro_ia32_Not, "ia32_Not", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Not = op;
	op = new_ir_op(cur_opcode + iro_ia32_NotMem, "ia32_NotMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_NotMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_Or, "ia32_Or", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Or = op;
	op = new_ir_op(cur_opcode + iro_ia32_OrMem, "ia32_OrMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_OrMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_Orp, "ia32_Orp", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_Orp = op;
	op = new_ir_op(cur_opcode + iro_ia32_Outport, "ia32_Outport", op_pin_state_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Outport = op;
	op = new_ir_op(cur_opcode + iro_ia32_Pop, "ia32_Pop", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 0);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_Pop = op;
	op = new_ir_op(cur_opcode + iro_ia32_PopMem, "ia32_PopMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_PopMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_Popcnt, "ia32_Popcnt", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Popcnt = op;
	op = new_ir_op(cur_opcode + iro_ia32_Prefetch, "ia32_Prefetch", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_Prefetch = op;
	op = new_ir_op(cur_opcode + iro_ia32_PrefetchNTA, "ia32_PrefetchNTA", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_PrefetchNTA = op;
	op = new_ir_op(cur_opcode + iro_ia32_PrefetchT0, "ia32_PrefetchT0", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_PrefetchT0 = op;
	op = new_ir_op(cur_opcode + iro_ia32_PrefetchT1, "ia32_PrefetchT1", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_PrefetchT1 = op;
	op = new_ir_op(cur_opcode + iro_ia32_PrefetchT2, "ia32_PrefetchT2", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_PrefetchT2 = op;
	op = new_ir_op(cur_opcode + iro_ia32_PrefetchW, "ia32_PrefetchW", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_PrefetchW = op;
	op = new_ir_op(cur_opcode + iro_ia32_Pslld, "ia32_Pslld", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_Pslld = op;
	op = new_ir_op(cur_opcode + iro_ia32_Psllq, "ia32_Psllq", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_Psllq = op;
	op = new_ir_op(cur_opcode + iro_ia32_Psrld, "ia32_Psrld", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Psrld = op;
	op = new_ir_op(cur_opcode + iro_ia32_Push, "ia32_Push", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_Push = op;
	op = new_ir_op(cur_opcode + iro_ia32_PushEax, "ia32_PushEax", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_PushEax = op;
	op = new_ir_op(cur_opcode + iro_ia32_Ret, "ia32_Ret", op_pin_state_pinned, irop_flag_cfopcode, oparity_any, -1, sizeof(ia32_return_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_return_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_Ret = op;
	op = new_ir_op(cur_opcode + iro_ia32_Rol, "ia32_Rol", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Rol = op;
	op = new_ir_op(cur_opcode + iro_ia32_RolMem, "ia32_RolMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_RolMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_Ror, "ia32_Ror", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Ror = op;
	op = new_ir_op(cur_opcode + iro_ia32_RorMem, "ia32_RorMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_RorMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_Sahf, "ia32_Sahf", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Sahf = op;
	op = new_ir_op(cur_opcode + iro_ia32_Sar, "ia32_Sar", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Sar = op;
	op = new_ir_op(cur_opcode + iro_ia32_SarMem, "ia32_SarMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_SarMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_Sbb, "ia32_Sbb", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_condcode_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_condcode_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Sbb = op;
	op = new_ir_op(cur_opcode + iro_ia32_Sbb0, "ia32_Sbb0", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_condcode_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_condcode_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Sbb0 = op;
	op = new_ir_op(cur_opcode + iro_ia32_Setcc, "ia32_Setcc", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_condcode_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_condcode_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Setcc = op;
	op = new_ir_op(cur_opcode + iro_ia32_SetccMem, "ia32_SetccMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_condcode_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_condcode_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_SetccMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_Shl, "ia32_Shl", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Shl = op;
	op = new_ir_op(cur_opcode + iro_ia32_ShlD, "ia32_ShlD", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 6);
	op_ia32_ShlD = op;
	op = new_ir_op(cur_opcode + iro_ia32_ShlMem, "ia32_ShlMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_ShlMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_Shr, "ia32_Shr", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Shr = op;
	op = new_ir_op(cur_opcode + iro_ia32_ShrD, "ia32_ShrD", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 6);
	op_ia32_ShrD = op;
	op = new_ir_op(cur_opcode + iro_ia32_ShrMem, "ia32_ShrMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_ShrMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_Stc, "ia32_Stc", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Stc = op;
	op = new_ir_op(cur_opcode + iro_ia32_Store, "ia32_Store", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_Store_mem);
	ir_op_set_fragile_indices(op, pn_ia32_Store_X_regular, pn_ia32_Store_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_Store = op;
	op = new_ir_op(cur_opcode + iro_ia32_Sub, "ia32_Sub", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Sub = op;
	op = new_ir_op(cur_opcode + iro_ia32_SubMem, "ia32_SubMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_SubMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_SubSP, "ia32_SubSP", op_pin_state_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_SubSP = op;
	op = new_ir_op(cur_opcode + iro_ia32_Subs, "ia32_Subs", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_Subs = op;
	op = new_ir_op(cur_opcode + iro_ia32_SwitchJmp, "ia32_SwitchJmp", op_pin_state_pinned, irop_flag_cfopcode|irop_flag_forking, oparity_any, -1, sizeof(ia32_switch_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_switch_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_SwitchJmp = op;
	op = new_ir_op(cur_opcode + iro_ia32_Test, "ia32_Test", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Test = op;
	op = new_ir_op(cur_opcode + iro_ia32_UD2, "ia32_UD2", op_pin_state_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 0);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_UD2 = op;
	op = new_ir_op(cur_opcode + iro_ia32_Ucomis, "ia32_Ucomis", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_Ucomis = op;
	op = new_ir_op(cur_opcode + iro_ia32_Xor, "ia32_Xor", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Xor = op;
	op = new_ir_op(cur_opcode + iro_ia32_Xor0, "ia32_Xor0", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_Xor0 = op;
	op = new_ir_op(cur_opcode + iro_ia32_XorHighLow, "ia32_XorHighLow", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_XorHighLow = op;
	op = new_ir_op(cur_opcode + iro_ia32_XorMem, "ia32_XorMem", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_XorMem = op;
	op = new_ir_op(cur_opcode + iro_ia32_Xorp, "ia32_Xorp", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_Xorp = op;
	op = new_ir_op(cur_opcode + iro_ia32_emms, "ia32_emms", op_pin_state_floats, irop_flag_keep, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, attrs_equal_false);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_emms = op;
	op = new_ir_op(cur_opcode + iro_ia32_fabs, "ia32_fabs", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_fabs = op;
	op = new_ir_op(cur_opcode + iro_ia32_fadd, "ia32_fadd", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_x87_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_x87_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_fadd = op;
	op = new_ir_op(cur_opcode + iro_ia32_fchs, "ia32_fchs", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_fchs = op;
	op = new_ir_op(cur_opcode + iro_ia32_fdiv, "ia32_fdiv", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_x87_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_x87_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 20);
	op_ia32_fdiv = op;
	op = new_ir_op(cur_opcode + iro_ia32_fdup, "ia32_fdup", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(ia32_x87_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, attrs_equal_false);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_fdup = op;
	op = new_ir_op(cur_opcode + iro_ia32_femms, "ia32_femms", op_pin_state_floats, irop_flag_keep, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, attrs_equal_false);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_femms = op;
	op = new_ir_op(cur_opcode + iro_ia32_ffreep, "ia32_ffreep", op_pin_state_floats, irop_flag_keep, oparity_any, -1, sizeof(ia32_x87_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, attrs_equal_false);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_ffreep = op;
	op = new_ir_op(cur_opcode + iro_ia32_fild, "ia32_fild", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_fild_mem);
	ir_op_set_fragile_indices(op, pn_ia32_fild_X_regular, pn_ia32_fild_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_fild = op;
	op = new_ir_op(cur_opcode + iro_ia32_fist, "ia32_fist", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_x87_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_x87_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_fist_mem);
	ir_op_set_fragile_indices(op, pn_ia32_fist_X_regular, pn_ia32_fist_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_fist = op;
	op = new_ir_op(cur_opcode + iro_ia32_fistp, "ia32_fistp", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_x87_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_x87_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_fistp_mem);
	ir_op_set_fragile_indices(op, pn_ia32_fistp_X_regular, pn_ia32_fistp_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_fistp = op;
	op = new_ir_op(cur_opcode + iro_ia32_fisttp, "ia32_fisttp", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_x87_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_x87_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_fisttp_mem);
	ir_op_set_fragile_indices(op, pn_ia32_fisttp_X_regular, pn_ia32_fisttp_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_fisttp = op;
	op = new_ir_op(cur_opcode + iro_ia32_fld, "ia32_fld", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_fld_mem);
	ir_op_set_fragile_indices(op, pn_ia32_fld_X_regular, pn_ia32_fld_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_fld = op;
	op = new_ir_op(cur_opcode + iro_ia32_fld1, "ia32_fld1", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_fld1 = op;
	op = new_ir_op(cur_opcode + iro_ia32_fldl2e, "ia32_fldl2e", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_fldl2e = op;
	op = new_ir_op(cur_opcode + iro_ia32_fldl2t, "ia32_fldl2t", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_fldl2t = op;
	op = new_ir_op(cur_opcode + iro_ia32_fldlg2, "ia32_fldlg2", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_fldlg2 = op;
	op = new_ir_op(cur_opcode + iro_ia32_fldln2, "ia32_fldln2", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_fldln2 = op;
	op = new_ir_op(cur_opcode + iro_ia32_fldpi, "ia32_fldpi", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_fldpi = op;
	op = new_ir_op(cur_opcode + iro_ia32_fldz, "ia32_fldz", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_fldz = op;
	op = new_ir_op(cur_opcode + iro_ia32_fmul, "ia32_fmul", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_x87_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_x87_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_fmul = op;
	op = new_ir_op(cur_opcode + iro_ia32_fpop, "ia32_fpop", op_pin_state_floats, irop_flag_keep, oparity_any, -1, sizeof(ia32_x87_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, attrs_equal_false);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_fpop = op;
	op = new_ir_op(cur_opcode + iro_ia32_fst, "ia32_fst", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_x87_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_x87_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_fst_mem);
	ir_op_set_fragile_indices(op, pn_ia32_fst_X_regular, pn_ia32_fst_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_fst = op;
	op = new_ir_op(cur_opcode + iro_ia32_fstp, "ia32_fstp", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_x87_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_x87_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_fstp_mem);
	ir_op_set_fragile_indices(op, pn_ia32_fstp_X_regular, pn_ia32_fstp_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 2);
	op_ia32_fstp = op;
	op = new_ir_op(cur_opcode + iro_ia32_fsub, "ia32_fsub", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_x87_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_x87_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 4);
	op_ia32_fsub = op;
	op = new_ir_op(cur_opcode + iro_ia32_fxch, "ia32_fxch", op_pin_state_floats, irop_flag_keep, oparity_any, -1, sizeof(ia32_x87_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, attrs_equal_false);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_fxch = op;
	op = new_ir_op(cur_opcode + iro_ia32_l_Adc, "ia32_l_Adc", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_l_Adc = op;
	op = new_ir_op(cur_opcode + iro_ia32_l_Add, "ia32_l_Add", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_l_Add = op;
	op = new_ir_op(cur_opcode + iro_ia32_l_FloattoLL, "ia32_l_FloattoLL", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_l_FloattoLL = op;
	op = new_ir_op(cur_opcode + iro_ia32_l_IMul, "ia32_l_IMul", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_l_IMul = op;
	op = new_ir_op(cur_opcode + iro_ia32_l_LLtoFloat, "ia32_l_LLtoFloat", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_l_LLtoFloat = op;
	op = new_ir_op(cur_opcode + iro_ia32_l_Minus64, "ia32_l_Minus64", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_l_Minus64 = op;
	op = new_ir_op(cur_opcode + iro_ia32_l_Mul, "ia32_l_Mul", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_l_Mul = op;
	op = new_ir_op(cur_opcode + iro_ia32_l_Sbb, "ia32_l_Sbb", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_l_Sbb = op;
	op = new_ir_op(cur_opcode + iro_ia32_l_Sub, "ia32_l_Sub", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	set_op_dump(op, NULL);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_l_Sub = op;
	op = new_ir_op(cur_opcode + iro_ia32_xAllOnes, "ia32_xAllOnes", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_xAllOnes = op;
	op = new_ir_op(cur_opcode + iro_ia32_xLoad, "ia32_xLoad", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_xLoad_mem);
	ir_op_set_fragile_indices(op, pn_ia32_xLoad_X_regular, pn_ia32_xLoad_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_xLoad = op;
	op = new_ir_op(cur_opcode + iro_ia32_xPzero, "ia32_xPzero", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_xPzero = op;
	op = new_ir_op(cur_opcode + iro_ia32_xStore, "ia32_xStore", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_xStore_mem);
	ir_op_set_fragile_indices(op, pn_ia32_xStore_X_regular, pn_ia32_xStore_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 0);
	op_ia32_xStore = op;
	op = new_ir_op(cur_opcode + iro_ia32_xZero, "ia32_xZero", op_pin_state_floats, irop_flag_constlike, oparity_any, -1, sizeof(ia32_attr_t));
	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 3);
	op_ia32_xZero = op;
	op = new_ir_op(cur_opcode + iro_ia32_xxLoad, "ia32_xxLoad", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_xxLoad_mem);
	ir_op_set_fragile_indices(op, pn_ia32_xxLoad_X_regular, pn_ia32_xxLoad_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_xxLoad = op;
	op = new_ir_op(cur_opcode + iro_ia32_xxStore, "ia32_xxStore", op_pin_state_exc_pinned, irop_flag_fragile|irop_flag_uses_memory, oparity_any, -1, sizeof(ia32_attr_t));
	ir_op_set_memory_index(op, 2);	set_op_dump(op, ia32_dump_node);
	set_op_attrs_equal(op, ia32_attrs_equal);
	set_op_copy_attr(op, be_copy_attr);
	ir_op_set_memory_index(op, n_ia32_xxStore_mem);
	ir_op_set_fragile_indices(op, pn_ia32_xxStore_X_regular, pn_ia32_xxStore_X_except);
	set_op_tag(op, ia32_op_tag);
	ia32_init_op(op, 1);
	op_ia32_xxStore = op;

}

void ia32_free_opcodes(void)
{
	free_ir_op(op_ia32_Adc); op_ia32_Adc = NULL;
	free_ir_op(op_ia32_Add); op_ia32_Add = NULL;
	free_ir_op(op_ia32_AddMem); op_ia32_AddMem = NULL;
	free_ir_op(op_ia32_AddSP); op_ia32_AddSP = NULL;
	free_ir_op(op_ia32_Adds); op_ia32_Adds = NULL;
	free_ir_op(op_ia32_And); op_ia32_And = NULL;
	free_ir_op(op_ia32_AndMem); op_ia32_AndMem = NULL;
	free_ir_op(op_ia32_Andnp); op_ia32_Andnp = NULL;
	free_ir_op(op_ia32_Andp); op_ia32_Andp = NULL;
	free_ir_op(op_ia32_Breakpoint); op_ia32_Breakpoint = NULL;
	free_ir_op(op_ia32_Bsf); op_ia32_Bsf = NULL;
	free_ir_op(op_ia32_Bsr); op_ia32_Bsr = NULL;
	free_ir_op(op_ia32_Bswap); op_ia32_Bswap = NULL;
	free_ir_op(op_ia32_Bswap16); op_ia32_Bswap16 = NULL;
	free_ir_op(op_ia32_Bt); op_ia32_Bt = NULL;
	free_ir_op(op_ia32_CMovcc); op_ia32_CMovcc = NULL;
	free_ir_op(op_ia32_Call); op_ia32_Call = NULL;
	free_ir_op(op_ia32_ChangeCW); op_ia32_ChangeCW = NULL;
	free_ir_op(op_ia32_Cltd); op_ia32_Cltd = NULL;
	free_ir_op(op_ia32_Cmc); op_ia32_Cmc = NULL;
	free_ir_op(op_ia32_Cmp); op_ia32_Cmp = NULL;
	free_ir_op(op_ia32_CmpXChgMem); op_ia32_CmpXChgMem = NULL;
	free_ir_op(op_ia32_Const); op_ia32_Const = NULL;
	free_ir_op(op_ia32_Conv_FP2FP); op_ia32_Conv_FP2FP = NULL;
	free_ir_op(op_ia32_Conv_FP2I); op_ia32_Conv_FP2I = NULL;
	free_ir_op(op_ia32_Conv_I2FP); op_ia32_Conv_I2FP = NULL;
	free_ir_op(op_ia32_Conv_I2I); op_ia32_Conv_I2I = NULL;
	free_ir_op(op_ia32_CopyB); op_ia32_CopyB = NULL;
	free_ir_op(op_ia32_CopyB_i); op_ia32_CopyB_i = NULL;
	free_ir_op(op_ia32_CopyEbpEsp); op_ia32_CopyEbpEsp = NULL;
	free_ir_op(op_ia32_CvtSI2SD); op_ia32_CvtSI2SD = NULL;
	free_ir_op(op_ia32_CvtSI2SS); op_ia32_CvtSI2SS = NULL;
	free_ir_op(op_ia32_Cwtl); op_ia32_Cwtl = NULL;
	free_ir_op(op_ia32_Dec); op_ia32_Dec = NULL;
	free_ir_op(op_ia32_DecMem); op_ia32_DecMem = NULL;
	free_ir_op(op_ia32_Div); op_ia32_Div = NULL;
	free_ir_op(op_ia32_Divs); op_ia32_Divs = NULL;
	free_ir_op(op_ia32_Enter); op_ia32_Enter = NULL;
	free_ir_op(op_ia32_FldCW); op_ia32_FldCW = NULL;
	free_ir_op(op_ia32_FnstCW); op_ia32_FnstCW = NULL;
	free_ir_op(op_ia32_FnstCWNOP); op_ia32_FnstCWNOP = NULL;
	free_ir_op(op_ia32_FtstFnstsw); op_ia32_FtstFnstsw = NULL;
	free_ir_op(op_ia32_FucomFnstsw); op_ia32_FucomFnstsw = NULL;
	free_ir_op(op_ia32_Fucomi); op_ia32_Fucomi = NULL;
	free_ir_op(op_ia32_FucomppFnstsw); op_ia32_FucomppFnstsw = NULL;
	free_ir_op(op_ia32_GetEIP); op_ia32_GetEIP = NULL;
	free_ir_op(op_ia32_IDiv); op_ia32_IDiv = NULL;
	free_ir_op(op_ia32_IJmp); op_ia32_IJmp = NULL;
	free_ir_op(op_ia32_IMul); op_ia32_IMul = NULL;
	free_ir_op(op_ia32_IMul1OP); op_ia32_IMul1OP = NULL;
	free_ir_op(op_ia32_IMulImm); op_ia32_IMulImm = NULL;
	free_ir_op(op_ia32_Immediate); op_ia32_Immediate = NULL;
	free_ir_op(op_ia32_Inc); op_ia32_Inc = NULL;
	free_ir_op(op_ia32_IncMem); op_ia32_IncMem = NULL;
	free_ir_op(op_ia32_Inport); op_ia32_Inport = NULL;
	free_ir_op(op_ia32_Jcc); op_ia32_Jcc = NULL;
	free_ir_op(op_ia32_Jmp); op_ia32_Jmp = NULL;
	free_ir_op(op_ia32_LdTls); op_ia32_LdTls = NULL;
	free_ir_op(op_ia32_Lea); op_ia32_Lea = NULL;
	free_ir_op(op_ia32_Leave); op_ia32_Leave = NULL;
	free_ir_op(op_ia32_Load); op_ia32_Load = NULL;
	free_ir_op(op_ia32_Maxs); op_ia32_Maxs = NULL;
	free_ir_op(op_ia32_Mins); op_ia32_Mins = NULL;
	free_ir_op(op_ia32_Minus64); op_ia32_Minus64 = NULL;
	free_ir_op(op_ia32_Movd); op_ia32_Movd = NULL;
	free_ir_op(op_ia32_Mul); op_ia32_Mul = NULL;
	free_ir_op(op_ia32_Muls); op_ia32_Muls = NULL;
	free_ir_op(op_ia32_Neg); op_ia32_Neg = NULL;
	free_ir_op(op_ia32_NegMem); op_ia32_NegMem = NULL;
	free_ir_op(op_ia32_NoReg_FP); op_ia32_NoReg_FP = NULL;
	free_ir_op(op_ia32_NoReg_GP); op_ia32_NoReg_GP = NULL;
	free_ir_op(op_ia32_NoReg_XMM); op_ia32_NoReg_XMM = NULL;
	free_ir_op(op_ia32_Not); op_ia32_Not = NULL;
	free_ir_op(op_ia32_NotMem); op_ia32_NotMem = NULL;
	free_ir_op(op_ia32_Or); op_ia32_Or = NULL;
	free_ir_op(op_ia32_OrMem); op_ia32_OrMem = NULL;
	free_ir_op(op_ia32_Orp); op_ia32_Orp = NULL;
	free_ir_op(op_ia32_Outport); op_ia32_Outport = NULL;
	free_ir_op(op_ia32_Pop); op_ia32_Pop = NULL;
	free_ir_op(op_ia32_PopMem); op_ia32_PopMem = NULL;
	free_ir_op(op_ia32_Popcnt); op_ia32_Popcnt = NULL;
	free_ir_op(op_ia32_Prefetch); op_ia32_Prefetch = NULL;
	free_ir_op(op_ia32_PrefetchNTA); op_ia32_PrefetchNTA = NULL;
	free_ir_op(op_ia32_PrefetchT0); op_ia32_PrefetchT0 = NULL;
	free_ir_op(op_ia32_PrefetchT1); op_ia32_PrefetchT1 = NULL;
	free_ir_op(op_ia32_PrefetchT2); op_ia32_PrefetchT2 = NULL;
	free_ir_op(op_ia32_PrefetchW); op_ia32_PrefetchW = NULL;
	free_ir_op(op_ia32_Pslld); op_ia32_Pslld = NULL;
	free_ir_op(op_ia32_Psllq); op_ia32_Psllq = NULL;
	free_ir_op(op_ia32_Psrld); op_ia32_Psrld = NULL;
	free_ir_op(op_ia32_Push); op_ia32_Push = NULL;
	free_ir_op(op_ia32_PushEax); op_ia32_PushEax = NULL;
	free_ir_op(op_ia32_Ret); op_ia32_Ret = NULL;
	free_ir_op(op_ia32_Rol); op_ia32_Rol = NULL;
	free_ir_op(op_ia32_RolMem); op_ia32_RolMem = NULL;
	free_ir_op(op_ia32_Ror); op_ia32_Ror = NULL;
	free_ir_op(op_ia32_RorMem); op_ia32_RorMem = NULL;
	free_ir_op(op_ia32_Sahf); op_ia32_Sahf = NULL;
	free_ir_op(op_ia32_Sar); op_ia32_Sar = NULL;
	free_ir_op(op_ia32_SarMem); op_ia32_SarMem = NULL;
	free_ir_op(op_ia32_Sbb); op_ia32_Sbb = NULL;
	free_ir_op(op_ia32_Sbb0); op_ia32_Sbb0 = NULL;
	free_ir_op(op_ia32_Setcc); op_ia32_Setcc = NULL;
	free_ir_op(op_ia32_SetccMem); op_ia32_SetccMem = NULL;
	free_ir_op(op_ia32_Shl); op_ia32_Shl = NULL;
	free_ir_op(op_ia32_ShlD); op_ia32_ShlD = NULL;
	free_ir_op(op_ia32_ShlMem); op_ia32_ShlMem = NULL;
	free_ir_op(op_ia32_Shr); op_ia32_Shr = NULL;
	free_ir_op(op_ia32_ShrD); op_ia32_ShrD = NULL;
	free_ir_op(op_ia32_ShrMem); op_ia32_ShrMem = NULL;
	free_ir_op(op_ia32_Stc); op_ia32_Stc = NULL;
	free_ir_op(op_ia32_Store); op_ia32_Store = NULL;
	free_ir_op(op_ia32_Sub); op_ia32_Sub = NULL;
	free_ir_op(op_ia32_SubMem); op_ia32_SubMem = NULL;
	free_ir_op(op_ia32_SubSP); op_ia32_SubSP = NULL;
	free_ir_op(op_ia32_Subs); op_ia32_Subs = NULL;
	free_ir_op(op_ia32_SwitchJmp); op_ia32_SwitchJmp = NULL;
	free_ir_op(op_ia32_Test); op_ia32_Test = NULL;
	free_ir_op(op_ia32_UD2); op_ia32_UD2 = NULL;
	free_ir_op(op_ia32_Ucomis); op_ia32_Ucomis = NULL;
	free_ir_op(op_ia32_Xor); op_ia32_Xor = NULL;
	free_ir_op(op_ia32_Xor0); op_ia32_Xor0 = NULL;
	free_ir_op(op_ia32_XorHighLow); op_ia32_XorHighLow = NULL;
	free_ir_op(op_ia32_XorMem); op_ia32_XorMem = NULL;
	free_ir_op(op_ia32_Xorp); op_ia32_Xorp = NULL;
	free_ir_op(op_ia32_emms); op_ia32_emms = NULL;
	free_ir_op(op_ia32_fabs); op_ia32_fabs = NULL;
	free_ir_op(op_ia32_fadd); op_ia32_fadd = NULL;
	free_ir_op(op_ia32_fchs); op_ia32_fchs = NULL;
	free_ir_op(op_ia32_fdiv); op_ia32_fdiv = NULL;
	free_ir_op(op_ia32_fdup); op_ia32_fdup = NULL;
	free_ir_op(op_ia32_femms); op_ia32_femms = NULL;
	free_ir_op(op_ia32_ffreep); op_ia32_ffreep = NULL;
	free_ir_op(op_ia32_fild); op_ia32_fild = NULL;
	free_ir_op(op_ia32_fist); op_ia32_fist = NULL;
	free_ir_op(op_ia32_fistp); op_ia32_fistp = NULL;
	free_ir_op(op_ia32_fisttp); op_ia32_fisttp = NULL;
	free_ir_op(op_ia32_fld); op_ia32_fld = NULL;
	free_ir_op(op_ia32_fld1); op_ia32_fld1 = NULL;
	free_ir_op(op_ia32_fldl2e); op_ia32_fldl2e = NULL;
	free_ir_op(op_ia32_fldl2t); op_ia32_fldl2t = NULL;
	free_ir_op(op_ia32_fldlg2); op_ia32_fldlg2 = NULL;
	free_ir_op(op_ia32_fldln2); op_ia32_fldln2 = NULL;
	free_ir_op(op_ia32_fldpi); op_ia32_fldpi = NULL;
	free_ir_op(op_ia32_fldz); op_ia32_fldz = NULL;
	free_ir_op(op_ia32_fmul); op_ia32_fmul = NULL;
	free_ir_op(op_ia32_fpop); op_ia32_fpop = NULL;
	free_ir_op(op_ia32_fst); op_ia32_fst = NULL;
	free_ir_op(op_ia32_fstp); op_ia32_fstp = NULL;
	free_ir_op(op_ia32_fsub); op_ia32_fsub = NULL;
	free_ir_op(op_ia32_fxch); op_ia32_fxch = NULL;
	free_ir_op(op_ia32_l_Adc); op_ia32_l_Adc = NULL;
	free_ir_op(op_ia32_l_Add); op_ia32_l_Add = NULL;
	free_ir_op(op_ia32_l_FloattoLL); op_ia32_l_FloattoLL = NULL;
	free_ir_op(op_ia32_l_IMul); op_ia32_l_IMul = NULL;
	free_ir_op(op_ia32_l_LLtoFloat); op_ia32_l_LLtoFloat = NULL;
	free_ir_op(op_ia32_l_Minus64); op_ia32_l_Minus64 = NULL;
	free_ir_op(op_ia32_l_Mul); op_ia32_l_Mul = NULL;
	free_ir_op(op_ia32_l_Sbb); op_ia32_l_Sbb = NULL;
	free_ir_op(op_ia32_l_Sub); op_ia32_l_Sub = NULL;
	free_ir_op(op_ia32_xAllOnes); op_ia32_xAllOnes = NULL;
	free_ir_op(op_ia32_xLoad); op_ia32_xLoad = NULL;
	free_ir_op(op_ia32_xPzero); op_ia32_xPzero = NULL;
	free_ir_op(op_ia32_xStore); op_ia32_xStore = NULL;
	free_ir_op(op_ia32_xZero); op_ia32_xZero = NULL;
	free_ir_op(op_ia32_xxLoad); op_ia32_xxLoad = NULL;
	free_ir_op(op_ia32_xxStore); op_ia32_xxStore = NULL;

}
