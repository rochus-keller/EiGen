/*
 * This file is part of libFirm.
 * Copyright (C) 2012 University of Karlsruhe.
 */

/**
 * @file
 * @brief    The main eigen backend driver file.
 */
#include "eigen_emitter.h"
#include "eigen_new_nodes.h"
#include "eigen_transform.h"
#include "be_t.h"
#include "beirg.h"
#include "bemodule.h"
#include "benode.h"
#include "bera.h"
#include "besched.h"
#include "bestack.h"
#include "debug.h"
#include "eigen_regalloc_if.h"
#include "iredges_t.h"
#include "irprog_t.h"
#include "isas.h"
#include "lower_builtins.h"
#include "lower_calls.h"
#include "panic.h"
#include "target_t.h"

/**
 * Transforms the standard firm graph into a eigen firm graph
 */
static void eigen_select_instructions(ir_graph *irg)
{
	/* transform nodes into assembler instructions */
	be_timer_push(T_CODEGEN);
    eigen_transform_graph(irg);
	be_timer_pop(T_CODEGEN);
	be_dump(DUMP_BE, irg, "code-selection");
}

static ir_node *eigen_new_spill(ir_node *value, ir_node *after)
{
	(void)value;
	(void)after;
	panic("spilling not implemented yet");
}

static ir_node *eigen_new_reload(ir_node *value, ir_node *spill,
                                    ir_node *before)
{
	(void)value;
	(void)spill;
	(void)before;
	panic("reload not implemented yet");
}

static const regalloc_if_t eigen_regalloc_if = {
	.spill_cost  = 7,
	.reload_cost = 5,
    .new_spill   = eigen_new_spill,
    .new_reload  = eigen_new_reload,
};

static void introduce_prologue(ir_graph *const irg)
{
	ir_node  *const start      = get_irg_start(irg);
	ir_node  *const block      = get_nodes_block(start);
    ir_node  *const initial_sp = be_get_Start_proj(irg, &eigen_registers[REG_Sp]);
	ir_type  *const frame_type = get_irg_frame_type(irg);
	unsigned  const frame_size = get_type_size(frame_type);
	ir_node  *const incsp      = be_new_IncSP(block, initial_sp, frame_size, false);
	edges_reroute_except(initial_sp, incsp, incsp);
	sched_add_after(start, incsp);
}

static void eigen_generate_code(FILE *output, const char *cup_name)
{
	be_begin(output, cup_name);
    unsigned *const sp_is_non_ssa = rbitset_alloca(N_eigen_REGISTERS);
    rbitset_set(sp_is_non_ssa, REG_Sp);

	foreach_irp_irg(i, irg) {
		if (!be_step_first(irg))
			continue;

		be_birg_from_irg(irg)->non_ssa_regs = sp_is_non_ssa;
        eigen_select_instructions(irg);

		be_step_schedule(irg);

        be_step_regalloc(irg, &eigen_regalloc_if);

		introduce_prologue(irg);

        be_fix_stack_nodes(irg, &eigen_registers[REG_Sp]);
		be_birg_from_irg(irg)->non_ssa_regs = NULL;

        eigen_emit_function(irg);

		be_step_last(irg);
	}

	be_finish();
}

static void eigen_init(void)
{
    eigen_register_init();
    eigen_create_opcodes();

	ir_target.experimental
        = "The eigen backend is just a demo for writing backends";
	ir_target.float_int_overflow = ir_overflow_min_max;
}

static void eigen_finish(void)
{
    eigen_free_opcodes();
}

static void eigen_lower_for_target(void)
{
	lower_builtins(0, NULL, NULL);
	be_after_irp_transform("lower-builtins");

	/* lower compound param handling */
	lower_calls_with_compounds(LF_RETURN_HIDDEN,
				   lower_aggregates_as_pointers, NULL,
				   lower_aggregates_as_pointers, NULL,
				   reset_stateless_abi);
	be_after_irp_transform("lower-calls");
}

static unsigned eigen_get_op_estimated_cost(const ir_node *node)
{
    if (is_eigen_Load(node))
		return 5;
    if (is_eigen_Store(node))
		return 7;
	return 1;
}

arch_isa_if_t const eigen_isa_if = {
    .name                  = "eigen",
	.pointer_size          = 4,
	.modulo_shift          = 32,
	.big_endian            = false,
	.po2_biggest_alignment = 3,
	.pic_supported         = false,
    .n_registers           = N_eigen_REGISTERS,
    .registers             = eigen_registers,
    .n_register_classes    = N_eigen_CLASSES,
    .register_classes      = eigen_reg_classes,
    .init                  = eigen_init,
    .finish                = eigen_finish,
    .generate_code         = eigen_generate_code,
    .lower_for_target      = eigen_lower_for_target,
    .get_op_estimated_cost = eigen_get_op_estimated_cost,
};

BE_REGISTER_MODULE_CONSTRUCTOR(be_init_arch_eigen)
void be_init_arch_eigen(void)
{
    eigen_init_transform();
}
