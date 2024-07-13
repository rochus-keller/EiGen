/**
 * @file
 * @brief Generated functions to emit code for assembler ir nodes.
 * @note  DO NOT EDIT THIS FILE, your changes will be lost.
 *         Edit ./ir/be/TEMPLATE/TEMPLATE_spec.pl instead.
 *         created by: ./ir/be/scripts/generate_emitter.pl ./ir/be/TEMPLATE/TEMPLATE_spec.pl build/gen/ir/be/TEMPLATE
 * @date  Wed Jul 10 12:02:01 2024
 */
#include "gen_TEMPLATE_emitter.h"

#include "beemithlp.h"
#include "gen_TEMPLATE_new_nodes.h"
#include "TEMPLATE_emitter.h"

static void emit_TEMPLATE_Add(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = add %S0, %S1");
}

static void emit_TEMPLATE_And(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = and %S0, %S1");
}

static void emit_TEMPLATE_Const(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = const %I");
}

static void emit_TEMPLATE_Load(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = load (%S1)");
}

static void emit_TEMPLATE_Minus(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = minus %S0");
}

static void emit_TEMPLATE_Mul(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = mul %S0, %S1");
}

static void emit_TEMPLATE_Not(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = not %S0");
}

static void emit_TEMPLATE_Or(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = or %S0, %S1");
}

static void emit_TEMPLATE_Shl(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = shl %S0, %S1");
}

static void emit_TEMPLATE_Shr(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = shr %S0, %S1");
}

static void emit_TEMPLATE_Store(ir_node const *const node)
{
	TEMPLATE_emitf(node, "(%S1) = store %S2");
}

static void emit_TEMPLATE_Sub(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = sub %S0, %S1");
}

static void emit_TEMPLATE_Xor(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = xor %S0, %S1");
}

static void emit_TEMPLATE_fAdd(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = fadd %S0, %S1");
}

static void emit_TEMPLATE_fConst(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = fconst %I");
}

static void emit_TEMPLATE_fDiv(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = fdiv %S0, %S1");
}

static void emit_TEMPLATE_fLoad(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = fload (%S1)");
}

static void emit_TEMPLATE_fMinus(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = fneg %S0");
}

static void emit_TEMPLATE_fMul(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = fmul %S0, %S1");
}

static void emit_TEMPLATE_fStore(ir_node const *const node)
{
	TEMPLATE_emitf(node, "(%S1) = fstore %S2");
}

static void emit_TEMPLATE_fSub(ir_node const *const node)
{
	TEMPLATE_emitf(node, "%D0 = fsub %S0, %S1");
}



void TEMPLATE_register_spec_emitters(void)
{
	be_set_emitter(op_TEMPLATE_Add, emit_TEMPLATE_Add);
	be_set_emitter(op_TEMPLATE_And, emit_TEMPLATE_And);
	be_set_emitter(op_TEMPLATE_Const, emit_TEMPLATE_Const);
	be_set_emitter(op_TEMPLATE_Load, emit_TEMPLATE_Load);
	be_set_emitter(op_TEMPLATE_Minus, emit_TEMPLATE_Minus);
	be_set_emitter(op_TEMPLATE_Mul, emit_TEMPLATE_Mul);
	be_set_emitter(op_TEMPLATE_Not, emit_TEMPLATE_Not);
	be_set_emitter(op_TEMPLATE_Or, emit_TEMPLATE_Or);
	be_set_emitter(op_TEMPLATE_Shl, emit_TEMPLATE_Shl);
	be_set_emitter(op_TEMPLATE_Shr, emit_TEMPLATE_Shr);
	be_set_emitter(op_TEMPLATE_Store, emit_TEMPLATE_Store);
	be_set_emitter(op_TEMPLATE_Sub, emit_TEMPLATE_Sub);
	be_set_emitter(op_TEMPLATE_Xor, emit_TEMPLATE_Xor);
	be_set_emitter(op_TEMPLATE_fAdd, emit_TEMPLATE_fAdd);
	be_set_emitter(op_TEMPLATE_fConst, emit_TEMPLATE_fConst);
	be_set_emitter(op_TEMPLATE_fDiv, emit_TEMPLATE_fDiv);
	be_set_emitter(op_TEMPLATE_fLoad, emit_TEMPLATE_fLoad);
	be_set_emitter(op_TEMPLATE_fMinus, emit_TEMPLATE_fMinus);
	be_set_emitter(op_TEMPLATE_fMul, emit_TEMPLATE_fMul);
	be_set_emitter(op_TEMPLATE_fStore, emit_TEMPLATE_fStore);
	be_set_emitter(op_TEMPLATE_fSub, emit_TEMPLATE_fSub);

}

void TEMPLATE_register_spec_binary_emitters(void)
{

}
