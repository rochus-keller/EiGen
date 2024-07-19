/*
 * This file is part of libFirm.
 * Copyright (C) 2012 University of Karlsruhe.
 */

/**
 * @file
 * @brief   emit assembler for a backend graph
 */
#include "eigen_emitter.h"

#include "eigen_new_nodes.h"
#include "bearch.h"
#include "beblocksched.h"
#include "beemithlp.h"
#include "beemitter.h"
#include "begnuas.h"
#include "benode.h"
#include "besched.h"
#include "irgwalk.h"
#include "panic.h"
#include "util.h"

static void eigen_emit_immediate(const ir_node *node)
{
    eigen_attr_t const *const attr = get_eigen_attr_const(node);
	ir_entity             *const ent  = attr->entity;
	ir_tarval             *const val  = attr->value;
	if (ent) {
		be_emit_irprintf("&%s", get_entity_ld_name(ent));
		if (val)
			be_emit_char('+');
	}
	if (val)
		be_emit_irprintf("%T", val);
}

static void emit_register(const arch_register_t *reg)
{
	be_emit_string(reg->name);
}

static void eigen_emit_source_register(const ir_node *node, int pos)
{
	const arch_register_t *reg = arch_get_irn_register_in(node, pos);
	emit_register(reg);
}

static void eigen_emit_dest_register(const ir_node *node, int pos)
{
	const arch_register_t *reg = arch_get_irn_register_out(node, pos);
	emit_register(reg);
}

void eigen_emitf(const ir_node *node, const char *format, ...)
{
	BE_EMITF(node, format, ap, false) {
		switch (*format++) {
		case 'S': {
			if (!is_digit(*format))
				goto unknown;
			unsigned const pos = *format++ - '0';
            eigen_emit_source_register(node, pos);
			break;
		}

		case 'D': {
			if (!is_digit(*format))
				goto unknown;
			unsigned const pos = *format++ - '0';
            eigen_emit_dest_register(node, pos);
			break;
		}

		case 'I':
            eigen_emit_immediate(node);
			break;

		case 'X': {
			int num = va_arg(ap, int);
			be_emit_irprintf("%X", num);
			break;
		}

		default:
unknown:
			panic("unknown format conversion");
		}
	}
}

/**
 * Emits code for a unconditional jump.
 */
static void emit_eigen_Jmp(const ir_node *node)
{
    eigen_emitf(node, "jmp %L", node);
}

static void emit_be_IncSP(const ir_node *node)
{
	int offset = be_get_IncSP_offset(node);
	if (offset == 0)
		return;

	/* downwards growing stack */
	const char *op = "add";
	if (offset < 0) {
		op = "sub";
		offset = -offset;
	}

    eigen_emitf(node, "%s %S0, %d, %D0", op, offset);
}

static void emit_Return(const ir_node *node)
{
	ir_graph *irg        = get_irn_irg(node);
	ir_type  *frame_type = get_irg_frame_type(irg);
	unsigned  size       = get_type_size(frame_type);

	/* emit function epilog here */

	/* deallocate stackframe */
	if (size > 0) {
        eigen_emitf(node, "add %%sp, %u, %%sp", size);
	}

	/* return */
    unsigned    const n_res = get_irn_arity(node) - n_eigen_Return_first_result;
	char const *const fmt   =
		n_res == 0 ? "ret" :
		n_res == 1 ? "ret %S2" :
		"ret %S2, ...";
    eigen_emitf(node, fmt);
}

/**
 * Enters the emitter functions for handled nodes into the generic
 * pointer of an opcode.
 */
static void eigen_register_emitters(void)
{
	be_init_emitters();

	/* register all emitter functions defined in spec */
    eigen_register_spec_emitters();

	/* custom emitters not provided by the spec */
    be_set_emitter(op_eigen_Jmp,    emit_eigen_Jmp);
    be_set_emitter(op_eigen_Return, emit_Return);
	be_set_emitter(op_be_IncSP,        emit_be_IncSP);
}

/**
 * Walks over the nodes in a block connected by scheduling edges
 * and emits code for each node.
 */
static void eigen_emit_block(ir_node *block)
{
	be_gas_begin_block(block);

	sched_foreach(block, node) {
		be_emit_node(node);
	}
}

void eigen_emit_function(ir_graph *irg)
{
	/* register all emitter functions */
    eigen_register_emitters();

	/* create the block schedule */
	ir_node **block_schedule = be_create_block_schedule(irg);

	/* emit assembler prolog */
	ir_entity *entity = get_irg_entity(irg);
	be_gas_emit_function_prolog(entity, 4, NULL);

	/* populate jump link fields with their destinations */
	ir_reserve_resources(irg, IR_RESOURCE_IRN_LINK);

	be_emit_init_cf_links(block_schedule);

	for (size_t i = 0, n = ARR_LEN(block_schedule); i < n; ++i) {
		ir_node *block = block_schedule[i];
        eigen_emit_block(block);
	}
	ir_free_resources(irg, IR_RESOURCE_IRN_LINK);

	be_gas_emit_function_epilog(entity);
}

static void emit_eigen_Add(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = add %S0, %S1");
}

static void emit_eigen_And(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = and %S0, %S1");
}

static void emit_eigen_Const(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = const %I");
}

static void emit_eigen_Load(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = load (%S1)");
}

static void emit_eigen_Minus(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = minus %S0");
}

static void emit_eigen_Mul(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = mul %S0, %S1");
}

static void emit_eigen_Not(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = not %S0");
}

static void emit_eigen_Or(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = or %S0, %S1");
}

static void emit_eigen_Shl(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = shl %S0, %S1");
}

static void emit_eigen_Shr(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = shr %S0, %S1");
}

static void emit_eigen_Store(ir_node const *const node)
{
    eigen_emitf(node, "(%S1) = store %S2");
}

static void emit_eigen_Sub(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = sub %S0, %S1");
}

static void emit_eigen_Xor(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = xor %S0, %S1");
}

static void emit_eigen_fAdd(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = fadd %S0, %S1");
}

static void emit_eigen_fConst(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = fconst %I");
}

static void emit_eigen_fDiv(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = fdiv %S0, %S1");
}

static void emit_eigen_fLoad(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = fload (%S1)");
}

static void emit_eigen_fMinus(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = fneg %S0");
}

static void emit_eigen_fMul(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = fmul %S0, %S1");
}

static void emit_eigen_fStore(ir_node const *const node)
{
    eigen_emitf(node, "(%S1) = fstore %S2");
}

static void emit_eigen_fSub(ir_node const *const node)
{
    eigen_emitf(node, "%D0 = fsub %S0, %S1");
}



void eigen_register_spec_emitters(void)
{
    be_set_emitter(op_eigen_Add, emit_eigen_Add);
    be_set_emitter(op_eigen_And, emit_eigen_And);
    be_set_emitter(op_eigen_Const, emit_eigen_Const);
    be_set_emitter(op_eigen_Load, emit_eigen_Load);
    be_set_emitter(op_eigen_Minus, emit_eigen_Minus);
    be_set_emitter(op_eigen_Mul, emit_eigen_Mul);
    be_set_emitter(op_eigen_Not, emit_eigen_Not);
    be_set_emitter(op_eigen_Or, emit_eigen_Or);
    be_set_emitter(op_eigen_Shl, emit_eigen_Shl);
    be_set_emitter(op_eigen_Shr, emit_eigen_Shr);
    be_set_emitter(op_eigen_Store, emit_eigen_Store);
    be_set_emitter(op_eigen_Sub, emit_eigen_Sub);
    be_set_emitter(op_eigen_Xor, emit_eigen_Xor);
    be_set_emitter(op_eigen_fAdd, emit_eigen_fAdd);
    be_set_emitter(op_eigen_fConst, emit_eigen_fConst);
    be_set_emitter(op_eigen_fDiv, emit_eigen_fDiv);
    be_set_emitter(op_eigen_fLoad, emit_eigen_fLoad);
    be_set_emitter(op_eigen_fMinus, emit_eigen_fMinus);
    be_set_emitter(op_eigen_fMul, emit_eigen_fMul);
    be_set_emitter(op_eigen_fStore, emit_eigen_fStore);
    be_set_emitter(op_eigen_fSub, emit_eigen_fSub);

}

void eigen_register_spec_binary_emitters(void)
{

}
