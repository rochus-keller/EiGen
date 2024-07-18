/**
 * @file
 * @brief Generated functions to emit code for assembler ir nodes.
 * @note  DO NOT EDIT THIS FILE, your changes will be lost.
 *         Edit ./ir/be/arm/arm_spec.pl instead.
 *         created by: ./ir/be/scripts/generate_emitter.pl ./ir/be/arm/arm_spec.pl build/gen/ir/be/arm
 * @date  Wed Jul 10 12:01:46 2024
 */
#include "gen_arm_emitter.h"

#include "beemithlp.h"
#include "gen_arm_new_nodes.h"
#include "arm_emitter.h"

static void emit_arm_AdC(ir_node const *const node)
{
	arm_emitf(node, "adc %D0, %S0, %O");
}

static void emit_arm_Add(ir_node const *const node)
{
	arm_emitf(node, "add %D0, %S0, %O");
}

static void emit_arm_AddS(ir_node const *const node)
{
	arm_emitf(node, "adds %D0, %S0, %O");
}

static void emit_arm_Adf(ir_node const *const node)
{
	arm_emitf(node, "adf%MA %D0, %S0, %S1");
}

static void emit_arm_And(ir_node const *const node)
{
	arm_emitf(node, "and %D0, %S0, %O");
}

static void emit_arm_Bic(ir_node const *const node)
{
	arm_emitf(node, "bic %D0, %S0, %O");
}

static void emit_arm_Bl(ir_node const *const node)
{
	arm_emitf(node, "bl %I");
}

static void emit_arm_Clz(ir_node const *const node)
{
	arm_emitf(node, "clz %D0, %S0");
}

static void emit_arm_Cmfe(ir_node const *const node)
{
	arm_emitf(node, "cmfe %S0, %S1");
}

static void emit_arm_Cmn(ir_node const *const node)
{
	arm_emitf(node, "cmn %S0, %O");
}

static void emit_arm_Cmp(ir_node const *const node)
{
	arm_emitf(node, "cmp %S0, %O");
}

static void emit_arm_Dvf(ir_node const *const node)
{
	arm_emitf(node, "dvf%MA %D0, %S0, %S1");
}

static void emit_arm_Eor(ir_node const *const node)
{
	arm_emitf(node, "eor %D0, %S0, %O");
}

static void emit_arm_Flt(ir_node const *const node)
{
	arm_emitf(node, "flt%MA %D0, %S0");
}

static void emit_arm_IJmp(ir_node const *const node)
{
	arm_emitf(node, "mov pc, %S0");
}

static void emit_arm_Ldf(ir_node const *const node)
{
	arm_emitf(node, "ldf%MF %D0, %A");
}

static void emit_arm_Ldr(ir_node const *const node)
{
	arm_emitf(node, "ldr%ML %D0, %A");
}

static void emit_arm_LinkLdrPC(ir_node const *const node)
{
	arm_emitf(node, "mov lr, pc\nldr pc, %O");
}

static void emit_arm_LinkMovPC(ir_node const *const node)
{
	arm_emitf(node, "mov lr, pc\nmov pc, %O");
}

static void emit_arm_Mla(ir_node const *const node)
{
	arm_emitf(node, "mla %D0, %S0, %S1, %S2");
}

static void emit_arm_Mls(ir_node const *const node)
{
	arm_emitf(node, "mls %D0, %S0, %S1, %S2");
}

static void emit_arm_Mov(ir_node const *const node)
{
	arm_emitf(node, "mov %D0, %O");
}

static void emit_arm_Muf(ir_node const *const node)
{
	arm_emitf(node, "muf%MA %D0, %S0, %S1");
}

static void emit_arm_Mul(ir_node const *const node)
{
	arm_emitf(node, "mul %D0, %S0, %S1");
}

static void emit_arm_Mvf(ir_node const *const node)
{
	arm_emitf(node, "mvf%MA %S0, %D0");
}

static void emit_arm_Mvn(ir_node const *const node)
{
	arm_emitf(node, "mvn %D0, %O");
}

static void emit_arm_Orr(ir_node const *const node)
{
	arm_emitf(node, "orr %D0, %S0, %O");
}

static void emit_arm_OrrPl(ir_node const *const node)
{
	arm_emitf(node, "orrpl %D0, %S2, %O");
}

static void emit_arm_Pkhbt(ir_node const *const node)
{
	arm_emitf(node, "pkhbt %D0, %S0, %O");
}

static void emit_arm_Pkhtb(ir_node const *const node)
{
	arm_emitf(node, "pkhtb %D0, %S0, %O");
}

static void emit_arm_Return(ir_node const *const node)
{
	arm_emitf(node, "bx lr");
}

static void emit_arm_RsC(ir_node const *const node)
{
	arm_emitf(node, "rsc %D0, %S0, %O");
}

static void emit_arm_Rsb(ir_node const *const node)
{
	arm_emitf(node, "rsb %D0, %S0, %O");
}

static void emit_arm_RsbS(ir_node const *const node)
{
	arm_emitf(node, "rsbs %D0, %S0, %O");
}

static void emit_arm_SMulL(ir_node const *const node)
{
	arm_emitf(node, "smull %D0, %D1, %S0, %S1");
}

static void emit_arm_SbC(ir_node const *const node)
{
	arm_emitf(node, "sbc %D0, %S0, %O");
}

static void emit_arm_Stf(ir_node const *const node)
{
	arm_emitf(node, "stf%MF %S1, %A");
}

static void emit_arm_Str(ir_node const *const node)
{
	arm_emitf(node, "str%MS %S1, %A");
}

static void emit_arm_Sub(ir_node const *const node)
{
	arm_emitf(node, "sub %D0, %S0, %O");
}

static void emit_arm_SubS(ir_node const *const node)
{
	arm_emitf(node, "subs %D0, %S0, %O");
}

static void emit_arm_Suf(ir_node const *const node)
{
	arm_emitf(node, "suf%MA %D0, %S0, %S1");
}

static void emit_arm_Tst(ir_node const *const node)
{
	arm_emitf(node, "tst %S0, %O");
}

static void emit_arm_UMulL(ir_node const *const node)
{
	arm_emitf(node, "umull %D0, %D1, %S0, %S1");
}



void arm_register_spec_emitters(void)
{
	be_set_emitter(op_arm_AdC, emit_arm_AdC);
	be_set_emitter(op_arm_Add, emit_arm_Add);
	be_set_emitter(op_arm_AddS, emit_arm_AddS);
	be_set_emitter(op_arm_Adf, emit_arm_Adf);
	be_set_emitter(op_arm_And, emit_arm_And);
	be_set_emitter(op_arm_Bic, emit_arm_Bic);
	be_set_emitter(op_arm_Bl, emit_arm_Bl);
	be_set_emitter(op_arm_Clz, emit_arm_Clz);
	be_set_emitter(op_arm_Cmfe, emit_arm_Cmfe);
	be_set_emitter(op_arm_Cmn, emit_arm_Cmn);
	be_set_emitter(op_arm_Cmp, emit_arm_Cmp);
	be_set_emitter(op_arm_Dvf, emit_arm_Dvf);
	be_set_emitter(op_arm_Eor, emit_arm_Eor);
	be_set_emitter(op_arm_Flt, emit_arm_Flt);
	be_set_emitter(op_arm_IJmp, emit_arm_IJmp);
	be_set_emitter(op_arm_Ldf, emit_arm_Ldf);
	be_set_emitter(op_arm_Ldr, emit_arm_Ldr);
	be_set_emitter(op_arm_LinkLdrPC, emit_arm_LinkLdrPC);
	be_set_emitter(op_arm_LinkMovPC, emit_arm_LinkMovPC);
	be_set_emitter(op_arm_Mla, emit_arm_Mla);
	be_set_emitter(op_arm_Mls, emit_arm_Mls);
	be_set_emitter(op_arm_Mov, emit_arm_Mov);
	be_set_emitter(op_arm_Muf, emit_arm_Muf);
	be_set_emitter(op_arm_Mul, emit_arm_Mul);
	be_set_emitter(op_arm_Mvf, emit_arm_Mvf);
	be_set_emitter(op_arm_Mvn, emit_arm_Mvn);
	be_set_emitter(op_arm_Orr, emit_arm_Orr);
	be_set_emitter(op_arm_OrrPl, emit_arm_OrrPl);
	be_set_emitter(op_arm_Pkhbt, emit_arm_Pkhbt);
	be_set_emitter(op_arm_Pkhtb, emit_arm_Pkhtb);
	be_set_emitter(op_arm_Return, emit_arm_Return);
	be_set_emitter(op_arm_RsC, emit_arm_RsC);
	be_set_emitter(op_arm_Rsb, emit_arm_Rsb);
	be_set_emitter(op_arm_RsbS, emit_arm_RsbS);
	be_set_emitter(op_arm_SMulL, emit_arm_SMulL);
	be_set_emitter(op_arm_SbC, emit_arm_SbC);
	be_set_emitter(op_arm_Stf, emit_arm_Stf);
	be_set_emitter(op_arm_Str, emit_arm_Str);
	be_set_emitter(op_arm_Sub, emit_arm_Sub);
	be_set_emitter(op_arm_SubS, emit_arm_SubS);
	be_set_emitter(op_arm_Suf, emit_arm_Suf);
	be_set_emitter(op_arm_Tst, emit_arm_Tst);
	be_set_emitter(op_arm_UMulL, emit_arm_UMulL);

}

void arm_register_spec_binary_emitters(void)
{

}
