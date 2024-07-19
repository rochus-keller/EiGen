#ifndef FIRM_BE_eigen_GEN_eigen_REGALLOC_IF_H
#define FIRM_BE_eigen_GEN_eigen_REGALLOC_IF_H

/**
 * @file
 * @brief  The interface for the register allocator.
 *          Contains register classes and types and register constraints
 *          for all nodes where constraints were given in spec.
 * $date    Wed Jul 10 12:02:01 2024
 */

#include "bearch.h"

/** global register indices for eigen registers */
enum reg_indices {
	REG_R0,
	REG_R1,
	REG_R2,
	REG_R3,
	REG_R4,
	REG_R5,
	REG_R6,
	REG_R7,
    REG_Sp,
    REG_Fp,
    REG_Lnk,
    REG_Res,

	N_eigen_REGISTERS
};

/** local register indices for eigen registers */
enum {
    REG_SP_Sp,
    REG_SP_Fp,
    REG_SP_Lnk,
    REG_SP_Res,
};

enum {
	REG_GP_R0,
	REG_GP_R1,
	REG_GP_R2,
	REG_GP_R3,
	REG_GP_R4,
	REG_GP_R5,
	REG_GP_R6,
    REG_GP_R7
};


/** number of registers in eigen register classes. */
enum {
    N_eigen_gp_REGS = 8,
    N_eigen_sp_REGS = 4,
};

enum {
    CLASS_eigen_gp, // general purpose registers
    CLASS_eigen_sp, // special purpose registers
    N_eigen_CLASSES = 2
};

extern const arch_register_req_t eigen_class_reg_req_sp;
extern const arch_register_req_t eigen_single_reg_req_sp_sp;
extern const arch_register_req_t eigen_single_reg_req_sp_fp;
extern const arch_register_req_t eigen_single_reg_req_sp_lnk;
extern const arch_register_req_t eigen_single_reg_req_sp_res;
extern const arch_register_req_t eigen_class_reg_req_gp;
extern const arch_register_req_t eigen_single_reg_req_gp_r0;
extern const arch_register_req_t eigen_single_reg_req_gp_r1;
extern const arch_register_req_t eigen_single_reg_req_gp_r2;
extern const arch_register_req_t eigen_single_reg_req_gp_r3;
extern const arch_register_req_t eigen_single_reg_req_gp_r4;
extern const arch_register_req_t eigen_single_reg_req_gp_r5;
extern const arch_register_req_t eigen_single_reg_req_gp_r6;
extern const arch_register_req_t eigen_single_reg_req_gp_r7;


extern const arch_register_t eigen_registers[N_eigen_REGISTERS];

extern arch_register_class_t eigen_reg_classes[N_eigen_CLASSES];

void eigen_register_init(void);

#endif
