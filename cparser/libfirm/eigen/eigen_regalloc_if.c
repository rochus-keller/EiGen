/**
 * @file
 * @brief  The interface for the register allocator.
 *          Contains register classes and types and register constraints
 *          for all nodes where constraints were given in spec.
 * $date    Wed Jul 10 12:02:01 2024
 */
#include "eigen_regalloc_if.h"

#include "eigen_bearch_t.h"

const arch_register_req_t eigen_class_reg_req_sp = {
    .cls   = &eigen_reg_classes[CLASS_eigen_sp],
	.width = 1,
};
static const unsigned eigen_limited_sp_res[] = { (1U << REG_SP_Res) };
const arch_register_req_t eigen_single_reg_req_sp_res = {
    .cls     = &eigen_reg_classes[CLASS_eigen_sp],
    .limited = eigen_limited_sp_res,
	.width   = 1,
};
static const unsigned eigen_limited_sp_sp[] = { (1U << REG_SP_Sp) };
const arch_register_req_t eigen_single_reg_req_sp_sp = {
    .cls     = &eigen_reg_classes[CLASS_eigen_sp],
    .limited = eigen_limited_sp_sp,
	.width   = 1,
};
static const unsigned eigen_limited_sp_fp[] = { (1U << REG_SP_Fp) };
const arch_register_req_t eigen_single_reg_req_sp_fp = {
    .cls     = &eigen_reg_classes[CLASS_eigen_sp],
    .limited = eigen_limited_sp_fp,
	.width   = 1,
};
static const unsigned eigen_limited_sp_lnk[] = { (1U << REG_SP_Lnk) };
const arch_register_req_t eigen_single_reg_req_sp_lnk = {
    .cls     = &eigen_reg_classes[CLASS_eigen_sp],
    .limited = eigen_limited_sp_lnk,
	.width   = 1,
};
const arch_register_req_t eigen_class_reg_req_gp = {
    .cls   = &eigen_reg_classes[CLASS_eigen_gp],
	.width = 1,
};
static const unsigned eigen_limited_gp_r0[] = { (1U << REG_GP_R0) };
const arch_register_req_t eigen_single_reg_req_gp_r0 = {
    .cls     = &eigen_reg_classes[CLASS_eigen_gp],
    .limited = eigen_limited_gp_r0,
	.width   = 1,
};
static const unsigned eigen_limited_gp_r1[] = { (1U << REG_GP_R1) };
const arch_register_req_t eigen_single_reg_req_gp_r1 = {
    .cls     = &eigen_reg_classes[CLASS_eigen_gp],
    .limited = eigen_limited_gp_r1,
	.width   = 1,
};
static const unsigned eigen_limited_gp_r2[] = { (1U << REG_GP_R2) };
const arch_register_req_t eigen_single_reg_req_gp_r2 = {
    .cls     = &eigen_reg_classes[CLASS_eigen_gp],
    .limited = eigen_limited_gp_r2,
	.width   = 1,
};
static const unsigned eigen_limited_gp_r3[] = { (1U << REG_GP_R3) };
const arch_register_req_t eigen_single_reg_req_gp_r3 = {
    .cls     = &eigen_reg_classes[CLASS_eigen_gp],
    .limited = eigen_limited_gp_r3,
	.width   = 1,
};
static const unsigned eigen_limited_gp_r4[] = { (1U << REG_GP_R4) };
const arch_register_req_t eigen_single_reg_req_gp_r4 = {
    .cls     = &eigen_reg_classes[CLASS_eigen_gp],
    .limited = eigen_limited_gp_r4,
	.width   = 1,
};
static const unsigned eigen_limited_gp_r5[] = { (1U << REG_GP_R5) };
const arch_register_req_t eigen_single_reg_req_gp_r5 = {
    .cls     = &eigen_reg_classes[CLASS_eigen_gp],
    .limited = eigen_limited_gp_r5,
	.width   = 1,
};
static const unsigned eigen_limited_gp_r6[] = { (1U << REG_GP_R6) };
const arch_register_req_t eigen_single_reg_req_gp_r6 = {
    .cls     = &eigen_reg_classes[CLASS_eigen_gp],
    .limited = eigen_limited_gp_r6,
	.width   = 1,
};
static const unsigned eigen_limited_gp_r7[] = { (1U << REG_GP_R7) };
const arch_register_req_t eigen_single_reg_req_gp_r7 = {
    .cls     = &eigen_reg_classes[CLASS_eigen_gp],
    .limited = eigen_limited_gp_r7,
	.width   = 1,
};


arch_register_class_t eigen_reg_classes[] = {
	{
        .name      = "eigen_gp",
		.mode      = NULL,
        .regs      = &eigen_registers[REG_R0],
        .class_req = &eigen_class_reg_req_gp,
        .index     = CLASS_eigen_gp,
        .n_regs    = N_eigen_gp_REGS,
	},
    {
        .name      = "eigen_sp",
        .mode      = NULL,
        .regs      = &eigen_registers[REG_Sp],
        .class_req = &eigen_class_reg_req_sp,
        .index     = CLASS_eigen_sp,
        .n_regs    = N_eigen_sp_REGS,
    },

};

/** The array of all registers in the eigen architecture, sorted by its global index.*/
const arch_register_t eigen_registers[] = {
	{
        .name         = "$0",
        .cls          = &eigen_reg_classes[CLASS_eigen_gp],
        .single_req   = &eigen_single_reg_req_gp_r0,
		.index        = REG_GP_R0,
		.global_index = REG_R0,
		.dwarf_number = 0,
		.encoding     = REG_GP_R0,
		.is_virtual   = false,
	},
	{
        .name         = "$1",
        .cls          = &eigen_reg_classes[CLASS_eigen_gp],
        .single_req   = &eigen_single_reg_req_gp_r1,
		.index        = REG_GP_R1,
		.global_index = REG_R1,
		.dwarf_number = 0,
		.encoding     = REG_GP_R1,
		.is_virtual   = false,
	},
	{
        .name         = "$2",
        .cls          = &eigen_reg_classes[CLASS_eigen_gp],
        .single_req   = &eigen_single_reg_req_gp_r2,
		.index        = REG_GP_R2,
		.global_index = REG_R2,
		.dwarf_number = 0,
		.encoding     = REG_GP_R2,
		.is_virtual   = false,
	},
	{
        .name         = "$3",
        .cls          = &eigen_reg_classes[CLASS_eigen_gp],
        .single_req   = &eigen_single_reg_req_gp_r3,
		.index        = REG_GP_R3,
		.global_index = REG_R3,
		.dwarf_number = 0,
		.encoding     = REG_GP_R3,
		.is_virtual   = false,
	},
	{
        .name         = "$4",
        .cls          = &eigen_reg_classes[CLASS_eigen_gp],
        .single_req   = &eigen_single_reg_req_gp_r4,
		.index        = REG_GP_R4,
		.global_index = REG_R4,
		.dwarf_number = 0,
		.encoding     = REG_GP_R4,
		.is_virtual   = false,
	},
	{
        .name         = "$5",
        .cls          = &eigen_reg_classes[CLASS_eigen_gp],
        .single_req   = &eigen_single_reg_req_gp_r5,
		.index        = REG_GP_R5,
		.global_index = REG_R5,
		.dwarf_number = 0,
		.encoding     = REG_GP_R5,
		.is_virtual   = false,
	},
	{
        .name         = "$6",
        .cls          = &eigen_reg_classes[CLASS_eigen_gp],
        .single_req   = &eigen_single_reg_req_gp_r6,
		.index        = REG_GP_R6,
		.global_index = REG_R6,
		.dwarf_number = 0,
		.encoding     = REG_GP_R6,
		.is_virtual   = false,
	},
	{
        .name         = "$7",
        .cls          = &eigen_reg_classes[CLASS_eigen_gp],
        .single_req   = &eigen_single_reg_req_gp_r7,
		.index        = REG_GP_R7,
		.global_index = REG_R7,
		.dwarf_number = 0,
		.encoding     = REG_GP_R7,
		.is_virtual   = false,
	},
    {
        .name         = "$Sp",
        .cls          = &eigen_reg_classes[CLASS_eigen_sp],
        .single_req   = &eigen_single_reg_req_sp_sp,
        .index        = REG_SP_Sp,
        .global_index = REG_Sp,
        .dwarf_number = 0,
        .encoding     = REG_SP_Sp,
        .is_virtual   = false,
    },
    {
        .name         = "$Fp",
        .cls          = &eigen_reg_classes[CLASS_eigen_sp],
        .single_req   = &eigen_single_reg_req_sp_fp,
        .index        = REG_SP_Fp,
        .global_index = REG_Fp,
        .dwarf_number = 0,
        .encoding     = REG_SP_Fp,
        .is_virtual   = false,
    },
    {
        .name         = "$Lnk",
        .cls          = &eigen_reg_classes[CLASS_eigen_sp],
        .single_req   = &eigen_single_reg_req_sp_lnk,
        .index        = REG_SP_Lnk,
        .global_index = REG_Lnk,
        .dwarf_number = 0,
        .encoding     = REG_SP_Lnk,
        .is_virtual   = false,
    },
    {
        .name         = "$Res",
        .cls          = &eigen_reg_classes[CLASS_eigen_sp],
        .single_req   = &eigen_single_reg_req_sp_res,
        .index        = REG_SP_Res,
        .global_index = REG_Res,
        .dwarf_number = 0,
        .encoding     = REG_SP_Res,
        .is_virtual   = false,
    }

};

/**
 * Initializes eigen register classes.
 */
void eigen_register_init(void)
{
    eigen_reg_classes[CLASS_eigen_sp].mode = mode_ANY;
    eigen_reg_classes[CLASS_eigen_gp].mode = mode_ANY;

}
