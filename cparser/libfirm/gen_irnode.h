/* Warning: Automatically generated file */
#ifndef IR_GEN_IRNODE_H
#define IR_GEN_IRNODE_H

#include <assert.h>



#define is_ASM(node) is_ASM_(node)
#define get_ASM_constraints(node) get_ASM_constraints_(node)
#define set_ASM_constraints(node, constraints) set_ASM_constraints_(node, constraints)
#define get_ASM_clobbers(node) get_ASM_clobbers_(node)
#define set_ASM_clobbers(node, clobbers) set_ASM_clobbers_(node, clobbers)
#define get_ASM_text(node) get_ASM_text_(node)
#define set_ASM_text(node, text) set_ASM_text_(node, text)
#define get_ASM_mem(node) get_ASM_mem_(node)
#define set_ASM_mem(node, mem) set_ASM_mem_(node, mem)
#define get_ASM_n_inputs(node) get_ASM_n_inputs_(node)
#define get_ASM_input(node, pos) get_ASM_input_(node, pos)
#define set_ASM_input(node, pos, input) set_ASM_input_(node, pos, input)
#define get_ASM_input_arr(node) get_ASM_input_arr_(node)

#define is_Add(node) is_Add_(node)
#define get_Add_left(node) get_Add_left_(node)
#define set_Add_left(node, left) set_Add_left_(node, left)
#define get_Add_right(node) get_Add_right_(node)
#define set_Add_right(node, right) set_Add_right_(node, right)

#define is_Address(node) is_Address_(node)
#define get_Address_entity(node) get_Address_entity_(node)
#define set_Address_entity(node, entity) set_Address_entity_(node, entity)

#define is_Align(node) is_Align_(node)
#define get_Align_type(node) get_Align_type_(node)
#define set_Align_type(node, type) set_Align_type_(node, type)

#define is_Alloc(node) is_Alloc_(node)
#define get_Alloc_alignment(node) get_Alloc_alignment_(node)
#define set_Alloc_alignment(node, alignment) set_Alloc_alignment_(node, alignment)
#define get_Alloc_mem(node) get_Alloc_mem_(node)
#define set_Alloc_mem(node, mem) set_Alloc_mem_(node, mem)
#define get_Alloc_size(node) get_Alloc_size_(node)
#define set_Alloc_size(node, size) set_Alloc_size_(node, size)

#define is_Anchor(node) is_Anchor_(node)
#define get_Anchor_end_block(node) get_Anchor_end_block_(node)
#define set_Anchor_end_block(node, end_block) set_Anchor_end_block_(node, end_block)
#define get_Anchor_start_block(node) get_Anchor_start_block_(node)
#define set_Anchor_start_block(node, start_block) set_Anchor_start_block_(node, start_block)
#define get_Anchor_end(node) get_Anchor_end_(node)
#define set_Anchor_end(node, end) set_Anchor_end_(node, end)
#define get_Anchor_start(node) get_Anchor_start_(node)
#define set_Anchor_start(node, start) set_Anchor_start_(node, start)
#define get_Anchor_frame(node) get_Anchor_frame_(node)
#define set_Anchor_frame(node, frame) set_Anchor_frame_(node, frame)
#define get_Anchor_initial_mem(node) get_Anchor_initial_mem_(node)
#define set_Anchor_initial_mem(node, initial_mem) set_Anchor_initial_mem_(node, initial_mem)
#define get_Anchor_args(node) get_Anchor_args_(node)
#define set_Anchor_args(node, args) set_Anchor_args_(node, args)
#define get_Anchor_no_mem(node) get_Anchor_no_mem_(node)
#define set_Anchor_no_mem(node, no_mem) set_Anchor_no_mem_(node, no_mem)

#define is_And(node) is_And_(node)
#define get_And_left(node) get_And_left_(node)
#define set_And_left(node, left) set_And_left_(node, left)
#define get_And_right(node) get_And_right_(node)
#define set_And_right(node, right) set_And_right_(node, right)

#define is_Bad(node) is_Bad_(node)

#define is_Bitcast(node) is_Bitcast_(node)
#define get_Bitcast_op(node) get_Bitcast_op_(node)
#define set_Bitcast_op(node, op) set_Bitcast_op_(node, op)

#define is_Block(node) is_Block_(node)
#define get_Block_entity(node) get_Block_entity_(node)
#define set_Block_entity(node, entity) set_Block_entity_(node, entity)
#define get_Block_n_cfgpreds(node) get_Block_n_cfgpreds_(node)
#define get_Block_cfgpred(node, pos) get_Block_cfgpred_(node, pos)
#define set_Block_cfgpred(node, pos, cfgpred) set_Block_cfgpred_(node, pos, cfgpred)
#define get_Block_cfgpred_arr(node) get_Block_cfgpred_arr_(node)

#define is_Builtin(node) is_Builtin_(node)
#define get_Builtin_kind(node) get_Builtin_kind_(node)
#define set_Builtin_kind(node, kind) set_Builtin_kind_(node, kind)
#define get_Builtin_type(node) get_Builtin_type_(node)
#define set_Builtin_type(node, type) set_Builtin_type_(node, type)
#define get_Builtin_mem(node) get_Builtin_mem_(node)
#define set_Builtin_mem(node, mem) set_Builtin_mem_(node, mem)
#define get_Builtin_n_params(node) get_Builtin_n_params_(node)
#define get_Builtin_param(node, pos) get_Builtin_param_(node, pos)
#define set_Builtin_param(node, pos, param) set_Builtin_param_(node, pos, param)
#define get_Builtin_param_arr(node) get_Builtin_param_arr_(node)

#define is_Call(node) is_Call_(node)
#define get_Call_type(node) get_Call_type_(node)
#define set_Call_type(node, type) set_Call_type_(node, type)
#define get_Call_mem(node) get_Call_mem_(node)
#define set_Call_mem(node, mem) set_Call_mem_(node, mem)
#define get_Call_ptr(node) get_Call_ptr_(node)
#define set_Call_ptr(node, ptr) set_Call_ptr_(node, ptr)
#define get_Call_n_params(node) get_Call_n_params_(node)
#define get_Call_param(node, pos) get_Call_param_(node, pos)
#define set_Call_param(node, pos, param) set_Call_param_(node, pos, param)
#define get_Call_param_arr(node) get_Call_param_arr_(node)

#define is_Cmp(node) is_Cmp_(node)
#define get_Cmp_relation(node) get_Cmp_relation_(node)
#define set_Cmp_relation(node, relation) set_Cmp_relation_(node, relation)
#define get_Cmp_left(node) get_Cmp_left_(node)
#define set_Cmp_left(node, left) set_Cmp_left_(node, left)
#define get_Cmp_right(node) get_Cmp_right_(node)
#define set_Cmp_right(node, right) set_Cmp_right_(node, right)

#define is_Cond(node) is_Cond_(node)
#define get_Cond_jmp_pred(node) get_Cond_jmp_pred_(node)
#define set_Cond_jmp_pred(node, jmp_pred) set_Cond_jmp_pred_(node, jmp_pred)
#define get_Cond_selector(node) get_Cond_selector_(node)
#define set_Cond_selector(node, selector) set_Cond_selector_(node, selector)

#define is_Confirm(node) is_Confirm_(node)
#define get_Confirm_relation(node) get_Confirm_relation_(node)
#define set_Confirm_relation(node, relation) set_Confirm_relation_(node, relation)
#define get_Confirm_value(node) get_Confirm_value_(node)
#define set_Confirm_value(node, value) set_Confirm_value_(node, value)
#define get_Confirm_bound(node) get_Confirm_bound_(node)
#define set_Confirm_bound(node, bound) set_Confirm_bound_(node, bound)

#define is_Const(node) is_Const_(node)
#define get_Const_tarval(node) get_Const_tarval_(node)
#define set_Const_tarval(node, tarval) set_Const_tarval_(node, tarval)

#define is_Conv(node) is_Conv_(node)
#define get_Conv_op(node) get_Conv_op_(node)
#define set_Conv_op(node, op) set_Conv_op_(node, op)

#define is_CopyB(node) is_CopyB_(node)
#define get_CopyB_type(node) get_CopyB_type_(node)
#define set_CopyB_type(node, type) set_CopyB_type_(node, type)
#define get_CopyB_volatility(node) get_CopyB_volatility_(node)
#define set_CopyB_volatility(node, volatility) set_CopyB_volatility_(node, volatility)
#define get_CopyB_mem(node) get_CopyB_mem_(node)
#define set_CopyB_mem(node, mem) set_CopyB_mem_(node, mem)
#define get_CopyB_dst(node) get_CopyB_dst_(node)
#define set_CopyB_dst(node, dst) set_CopyB_dst_(node, dst)
#define get_CopyB_src(node) get_CopyB_src_(node)
#define set_CopyB_src(node, src) set_CopyB_src_(node, src)

#define is_Deleted(node) is_Deleted_(node)

#define is_Div(node) is_Div_(node)
#define get_Div_resmode(node) get_Div_resmode_(node)
#define set_Div_resmode(node, resmode) set_Div_resmode_(node, resmode)
#define get_Div_no_remainder(node) get_Div_no_remainder_(node)
#define set_Div_no_remainder(node, no_remainder) set_Div_no_remainder_(node, no_remainder)
#define get_Div_mem(node) get_Div_mem_(node)
#define set_Div_mem(node, mem) set_Div_mem_(node, mem)
#define get_Div_left(node) get_Div_left_(node)
#define set_Div_left(node, left) set_Div_left_(node, left)
#define get_Div_right(node) get_Div_right_(node)
#define set_Div_right(node, right) set_Div_right_(node, right)

#define is_Dummy(node) is_Dummy_(node)

#define is_End(node) is_End_(node)
#define get_End_n_keepalives(node) get_End_n_keepalives_(node)
#define get_End_keepalive(node, pos) get_End_keepalive_(node, pos)
#define set_End_keepalive(node, pos, keepalive) set_End_keepalive_(node, pos, keepalive)
#define get_End_keepalive_arr(node) get_End_keepalive_arr_(node)

#define is_Eor(node) is_Eor_(node)
#define get_Eor_left(node) get_Eor_left_(node)
#define set_Eor_left(node, left) set_Eor_left_(node, left)
#define get_Eor_right(node) get_Eor_right_(node)
#define set_Eor_right(node, right) set_Eor_right_(node, right)

#define is_Free(node) is_Free_(node)
#define get_Free_mem(node) get_Free_mem_(node)
#define set_Free_mem(node, mem) set_Free_mem_(node, mem)
#define get_Free_ptr(node) get_Free_ptr_(node)
#define set_Free_ptr(node, ptr) set_Free_ptr_(node, ptr)

#define is_IJmp(node) is_IJmp_(node)
#define get_IJmp_target(node) get_IJmp_target_(node)
#define set_IJmp_target(node, target) set_IJmp_target_(node, target)

#define is_Id(node) is_Id_(node)
#define get_Id_pred(node) get_Id_pred_(node)
#define set_Id_pred(node, pred) set_Id_pred_(node, pred)

#define is_Jmp(node) is_Jmp_(node)

#define is_Load(node) is_Load_(node)
#define get_Load_mode(node) get_Load_mode_(node)
#define set_Load_mode(node, mode) set_Load_mode_(node, mode)
#define get_Load_type(node) get_Load_type_(node)
#define set_Load_type(node, type) set_Load_type_(node, type)
#define get_Load_volatility(node) get_Load_volatility_(node)
#define set_Load_volatility(node, volatility) set_Load_volatility_(node, volatility)
#define get_Load_unaligned(node) get_Load_unaligned_(node)
#define set_Load_unaligned(node, unaligned) set_Load_unaligned_(node, unaligned)
#define get_Load_mem(node) get_Load_mem_(node)
#define set_Load_mem(node, mem) set_Load_mem_(node, mem)
#define get_Load_ptr(node) get_Load_ptr_(node)
#define set_Load_ptr(node, ptr) set_Load_ptr_(node, ptr)

#define is_Member(node) is_Member_(node)
#define get_Member_entity(node) get_Member_entity_(node)
#define set_Member_entity(node, entity) set_Member_entity_(node, entity)
#define get_Member_ptr(node) get_Member_ptr_(node)
#define set_Member_ptr(node, ptr) set_Member_ptr_(node, ptr)

#define is_Minus(node) is_Minus_(node)
#define get_Minus_op(node) get_Minus_op_(node)
#define set_Minus_op(node, op) set_Minus_op_(node, op)

#define is_Mod(node) is_Mod_(node)
#define get_Mod_resmode(node) get_Mod_resmode_(node)
#define set_Mod_resmode(node, resmode) set_Mod_resmode_(node, resmode)
#define get_Mod_mem(node) get_Mod_mem_(node)
#define set_Mod_mem(node, mem) set_Mod_mem_(node, mem)
#define get_Mod_left(node) get_Mod_left_(node)
#define set_Mod_left(node, left) set_Mod_left_(node, left)
#define get_Mod_right(node) get_Mod_right_(node)
#define set_Mod_right(node, right) set_Mod_right_(node, right)

#define is_Mul(node) is_Mul_(node)
#define get_Mul_left(node) get_Mul_left_(node)
#define set_Mul_left(node, left) set_Mul_left_(node, left)
#define get_Mul_right(node) get_Mul_right_(node)
#define set_Mul_right(node, right) set_Mul_right_(node, right)

#define is_Mulh(node) is_Mulh_(node)
#define get_Mulh_left(node) get_Mulh_left_(node)
#define set_Mulh_left(node, left) set_Mulh_left_(node, left)
#define get_Mulh_right(node) get_Mulh_right_(node)
#define set_Mulh_right(node, right) set_Mulh_right_(node, right)

#define is_Mux(node) is_Mux_(node)
#define get_Mux_sel(node) get_Mux_sel_(node)
#define set_Mux_sel(node, sel) set_Mux_sel_(node, sel)
#define get_Mux_false(node) get_Mux_false_(node)
#define set_Mux_false(node, false_) set_Mux_false_(node, false_)
#define get_Mux_true(node) get_Mux_true_(node)
#define set_Mux_true(node, true_) set_Mux_true_(node, true_)

#define is_NoMem(node) is_NoMem_(node)

#define is_Not(node) is_Not_(node)
#define get_Not_op(node) get_Not_op_(node)
#define set_Not_op(node, op) set_Not_op_(node, op)

#define is_Offset(node) is_Offset_(node)
#define get_Offset_entity(node) get_Offset_entity_(node)
#define set_Offset_entity(node, entity) set_Offset_entity_(node, entity)

#define is_Or(node) is_Or_(node)
#define get_Or_left(node) get_Or_left_(node)
#define set_Or_left(node, left) set_Or_left_(node, left)
#define get_Or_right(node) get_Or_right_(node)
#define set_Or_right(node, right) set_Or_right_(node, right)

#define is_Phi(node) is_Phi_(node)
#define get_Phi_loop(node) get_Phi_loop_(node)
#define set_Phi_loop(node, loop) set_Phi_loop_(node, loop)
#define get_Phi_n_preds(node) get_Phi_n_preds_(node)
#define get_Phi_pred(node, pos) get_Phi_pred_(node, pos)
#define set_Phi_pred(node, pos, pred) set_Phi_pred_(node, pos, pred)
#define get_Phi_pred_arr(node) get_Phi_pred_arr_(node)

#define is_Pin(node) is_Pin_(node)
#define get_Pin_op(node) get_Pin_op_(node)
#define set_Pin_op(node, op) set_Pin_op_(node, op)

#define is_Proj(node) is_Proj_(node)
#define get_Proj_num(node) get_Proj_num_(node)
#define set_Proj_num(node, num) set_Proj_num_(node, num)
#define get_Proj_pred(node) get_Proj_pred_(node)
#define set_Proj_pred(node, pred) set_Proj_pred_(node, pred)

#define is_Raise(node) is_Raise_(node)
#define get_Raise_mem(node) get_Raise_mem_(node)
#define set_Raise_mem(node, mem) set_Raise_mem_(node, mem)
#define get_Raise_exo_ptr(node) get_Raise_exo_ptr_(node)
#define set_Raise_exo_ptr(node, exo_ptr) set_Raise_exo_ptr_(node, exo_ptr)

#define is_Return(node) is_Return_(node)
#define get_Return_mem(node) get_Return_mem_(node)
#define set_Return_mem(node, mem) set_Return_mem_(node, mem)
#define get_Return_n_ress(node) get_Return_n_ress_(node)
#define get_Return_res(node, pos) get_Return_res_(node, pos)
#define set_Return_res(node, pos, res) set_Return_res_(node, pos, res)
#define get_Return_res_arr(node) get_Return_res_arr_(node)

#define is_Sel(node) is_Sel_(node)
#define get_Sel_type(node) get_Sel_type_(node)
#define set_Sel_type(node, type) set_Sel_type_(node, type)
#define get_Sel_ptr(node) get_Sel_ptr_(node)
#define set_Sel_ptr(node, ptr) set_Sel_ptr_(node, ptr)
#define get_Sel_index(node) get_Sel_index_(node)
#define set_Sel_index(node, index) set_Sel_index_(node, index)

#define is_Shl(node) is_Shl_(node)
#define get_Shl_left(node) get_Shl_left_(node)
#define set_Shl_left(node, left) set_Shl_left_(node, left)
#define get_Shl_right(node) get_Shl_right_(node)
#define set_Shl_right(node, right) set_Shl_right_(node, right)

#define is_Shr(node) is_Shr_(node)
#define get_Shr_left(node) get_Shr_left_(node)
#define set_Shr_left(node, left) set_Shr_left_(node, left)
#define get_Shr_right(node) get_Shr_right_(node)
#define set_Shr_right(node, right) set_Shr_right_(node, right)

#define is_Shrs(node) is_Shrs_(node)
#define get_Shrs_left(node) get_Shrs_left_(node)
#define set_Shrs_left(node, left) set_Shrs_left_(node, left)
#define get_Shrs_right(node) get_Shrs_right_(node)
#define set_Shrs_right(node, right) set_Shrs_right_(node, right)

#define is_Size(node) is_Size_(node)
#define get_Size_type(node) get_Size_type_(node)
#define set_Size_type(node, type) set_Size_type_(node, type)

#define is_Start(node) is_Start_(node)

#define is_Store(node) is_Store_(node)
#define get_Store_type(node) get_Store_type_(node)
#define set_Store_type(node, type) set_Store_type_(node, type)
#define get_Store_volatility(node) get_Store_volatility_(node)
#define set_Store_volatility(node, volatility) set_Store_volatility_(node, volatility)
#define get_Store_unaligned(node) get_Store_unaligned_(node)
#define set_Store_unaligned(node, unaligned) set_Store_unaligned_(node, unaligned)
#define get_Store_mem(node) get_Store_mem_(node)
#define set_Store_mem(node, mem) set_Store_mem_(node, mem)
#define get_Store_ptr(node) get_Store_ptr_(node)
#define set_Store_ptr(node, ptr) set_Store_ptr_(node, ptr)
#define get_Store_value(node) get_Store_value_(node)
#define set_Store_value(node, value) set_Store_value_(node, value)

#define is_Sub(node) is_Sub_(node)
#define get_Sub_left(node) get_Sub_left_(node)
#define set_Sub_left(node, left) set_Sub_left_(node, left)
#define get_Sub_right(node) get_Sub_right_(node)
#define set_Sub_right(node, right) set_Sub_right_(node, right)

#define is_Switch(node) is_Switch_(node)
#define get_Switch_n_outs(node) get_Switch_n_outs_(node)
#define set_Switch_n_outs(node, n_outs) set_Switch_n_outs_(node, n_outs)
#define get_Switch_table(node) get_Switch_table_(node)
#define set_Switch_table(node, table) set_Switch_table_(node, table)
#define get_Switch_selector(node) get_Switch_selector_(node)
#define set_Switch_selector(node, selector) set_Switch_selector_(node, selector)

#define is_Sync(node) is_Sync_(node)
#define get_Sync_n_preds(node) get_Sync_n_preds_(node)
#define get_Sync_pred(node, pos) get_Sync_pred_(node, pos)
#define set_Sync_pred(node, pos, pred) set_Sync_pred_(node, pos, pred)
#define get_Sync_pred_arr(node) get_Sync_pred_arr_(node)

#define is_Tuple(node) is_Tuple_(node)
#define get_Tuple_n_preds(node) get_Tuple_n_preds_(node)
#define get_Tuple_pred(node, pos) get_Tuple_pred_(node, pos)
#define set_Tuple_pred(node, pos, pred) set_Tuple_pred_(node, pos, pred)
#define get_Tuple_pred_arr(node) get_Tuple_pred_arr_(node)

#define is_Unknown(node) is_Unknown_(node)


#define is_entconst(node) is_entconst_(node)
#define get_entconst_entity(node) get_entconst_entity_(node)
#define set_entconst_entity(node, entity) set_entconst_entity_(node, entity)
#define is_typeconst(node) is_typeconst_(node)
#define get_typeconst_type(node) get_typeconst_type_(node)
#define set_typeconst_type(node, type) set_typeconst_type_(node, type)
static inline int is_ASM_(const ir_node *node)
{
	return get_irn_op(node) == op_ASM;
}
static inline ir_node *get_ASM_mem_(const ir_node *node)
{
	assert(is_ASM(node));
	return get_irn_n(node, n_ASM_mem);
}

static inline void set_ASM_mem_(ir_node *node, ir_node *mem)
{
	assert(is_ASM(node));
	set_irn_n(node, n_ASM_mem, mem);
}

static inline int get_ASM_n_inputs_(ir_node const *node)
{
	assert(is_ASM(node));
	return get_irn_arity(node) - (n_ASM_max + 1);
}

static inline ir_node *get_ASM_input_(ir_node const *node, int pos)
{
	assert(0 <= pos && pos < get_ASM_n_inputs(node));
	return get_irn_n(node, pos + (n_ASM_max + 1));
}

static inline void set_ASM_input_(ir_node *node, int pos, ir_node *input)
{
	assert(0 <= pos && pos < get_ASM_n_inputs(node));
	set_irn_n(node, pos + (n_ASM_max + 1), input);
}

static inline ir_node **get_ASM_input_arr_(ir_node *node)
{
	assert(is_ASM(node));
	return get_irn_in(node) + (n_ASM_max + 1);
}

static inline int is_Add_(const ir_node *node)
{
	return get_irn_op(node) == op_Add;
}
static inline ir_node *get_Add_left_(const ir_node *node)
{
	assert(is_Add(node));
	return get_irn_n(node, n_Add_left);
}

static inline void set_Add_left_(ir_node *node, ir_node *left)
{
	assert(is_Add(node));
	set_irn_n(node, n_Add_left, left);
}

static inline ir_node *get_Add_right_(const ir_node *node)
{
	assert(is_Add(node));
	return get_irn_n(node, n_Add_right);
}

static inline void set_Add_right_(ir_node *node, ir_node *right)
{
	assert(is_Add(node));
	set_irn_n(node, n_Add_right, right);
}

static inline int is_Address_(const ir_node *node)
{
	return get_irn_op(node) == op_Address;
}
static inline int is_Align_(const ir_node *node)
{
	return get_irn_op(node) == op_Align;
}
static inline int is_Alloc_(const ir_node *node)
{
	return get_irn_op(node) == op_Alloc;
}
static inline ir_node *get_Alloc_mem_(const ir_node *node)
{
	assert(is_Alloc(node));
	return get_irn_n(node, n_Alloc_mem);
}

static inline void set_Alloc_mem_(ir_node *node, ir_node *mem)
{
	assert(is_Alloc(node));
	set_irn_n(node, n_Alloc_mem, mem);
}

static inline ir_node *get_Alloc_size_(const ir_node *node)
{
	assert(is_Alloc(node));
	return get_irn_n(node, n_Alloc_size);
}

static inline void set_Alloc_size_(ir_node *node, ir_node *size)
{
	assert(is_Alloc(node));
	set_irn_n(node, n_Alloc_size, size);
}

static inline int is_Anchor_(const ir_node *node)
{
	return get_irn_op(node) == op_Anchor;
}
static inline ir_node *get_Anchor_end_block_(const ir_node *node)
{
	assert(is_Anchor(node));
	return get_irn_n(node, n_Anchor_end_block);
}

static inline void set_Anchor_end_block_(ir_node *node, ir_node *end_block)
{
	assert(is_Anchor(node));
	set_irn_n(node, n_Anchor_end_block, end_block);
}

static inline ir_node *get_Anchor_start_block_(const ir_node *node)
{
	assert(is_Anchor(node));
	return get_irn_n(node, n_Anchor_start_block);
}

static inline void set_Anchor_start_block_(ir_node *node, ir_node *start_block)
{
	assert(is_Anchor(node));
	set_irn_n(node, n_Anchor_start_block, start_block);
}

static inline ir_node *get_Anchor_end_(const ir_node *node)
{
	assert(is_Anchor(node));
	return get_irn_n(node, n_Anchor_end);
}

static inline void set_Anchor_end_(ir_node *node, ir_node *end)
{
	assert(is_Anchor(node));
	set_irn_n(node, n_Anchor_end, end);
}

static inline ir_node *get_Anchor_start_(const ir_node *node)
{
	assert(is_Anchor(node));
	return get_irn_n(node, n_Anchor_start);
}

static inline void set_Anchor_start_(ir_node *node, ir_node *start)
{
	assert(is_Anchor(node));
	set_irn_n(node, n_Anchor_start, start);
}

static inline ir_node *get_Anchor_frame_(const ir_node *node)
{
	assert(is_Anchor(node));
	return get_irn_n(node, n_Anchor_frame);
}

static inline void set_Anchor_frame_(ir_node *node, ir_node *frame)
{
	assert(is_Anchor(node));
	set_irn_n(node, n_Anchor_frame, frame);
}

static inline ir_node *get_Anchor_initial_mem_(const ir_node *node)
{
	assert(is_Anchor(node));
	return get_irn_n(node, n_Anchor_initial_mem);
}

static inline void set_Anchor_initial_mem_(ir_node *node, ir_node *initial_mem)
{
	assert(is_Anchor(node));
	set_irn_n(node, n_Anchor_initial_mem, initial_mem);
}

static inline ir_node *get_Anchor_args_(const ir_node *node)
{
	assert(is_Anchor(node));
	return get_irn_n(node, n_Anchor_args);
}

static inline void set_Anchor_args_(ir_node *node, ir_node *args)
{
	assert(is_Anchor(node));
	set_irn_n(node, n_Anchor_args, args);
}

static inline ir_node *get_Anchor_no_mem_(const ir_node *node)
{
	assert(is_Anchor(node));
	return get_irn_n(node, n_Anchor_no_mem);
}

static inline void set_Anchor_no_mem_(ir_node *node, ir_node *no_mem)
{
	assert(is_Anchor(node));
	set_irn_n(node, n_Anchor_no_mem, no_mem);
}

static inline int is_And_(const ir_node *node)
{
	return get_irn_op(node) == op_And;
}
static inline ir_node *get_And_left_(const ir_node *node)
{
	assert(is_And(node));
	return get_irn_n(node, n_And_left);
}

static inline void set_And_left_(ir_node *node, ir_node *left)
{
	assert(is_And(node));
	set_irn_n(node, n_And_left, left);
}

static inline ir_node *get_And_right_(const ir_node *node)
{
	assert(is_And(node));
	return get_irn_n(node, n_And_right);
}

static inline void set_And_right_(ir_node *node, ir_node *right)
{
	assert(is_And(node));
	set_irn_n(node, n_And_right, right);
}

static inline int is_Bad_(const ir_node *node)
{
	return get_irn_op(node) == op_Bad;
}
static inline int is_Bitcast_(const ir_node *node)
{
	return get_irn_op(node) == op_Bitcast;
}
static inline ir_node *get_Bitcast_op_(const ir_node *node)
{
	assert(is_Bitcast(node));
	return get_irn_n(node, n_Bitcast_op);
}

static inline void set_Bitcast_op_(ir_node *node, ir_node *op)
{
	assert(is_Bitcast(node));
	set_irn_n(node, n_Bitcast_op, op);
}

static inline int is_Block_(const ir_node *node)
{
	return get_irn_op(node) == op_Block;
}
static inline int get_Block_n_cfgpreds_(ir_node const *node)
{
	assert(is_Block(node));
	return get_irn_arity(node);
}

static inline ir_node *get_Block_cfgpred_(ir_node const *node, int pos)
{
	assert(0 <= pos && pos < get_Block_n_cfgpreds(node));
	return get_irn_n(node, pos);
}

static inline void set_Block_cfgpred_(ir_node *node, int pos, ir_node *cfgpred)
{
	assert(0 <= pos && pos < get_Block_n_cfgpreds(node));
	set_irn_n(node, pos, cfgpred);
}

static inline ir_node **get_Block_cfgpred_arr_(ir_node *node)
{
	assert(is_Block(node));
	return get_irn_in(node);
}

static inline int is_Builtin_(const ir_node *node)
{
	return get_irn_op(node) == op_Builtin;
}
static inline ir_node *get_Builtin_mem_(const ir_node *node)
{
	assert(is_Builtin(node));
	return get_irn_n(node, n_Builtin_mem);
}

static inline void set_Builtin_mem_(ir_node *node, ir_node *mem)
{
	assert(is_Builtin(node));
	set_irn_n(node, n_Builtin_mem, mem);
}

static inline int get_Builtin_n_params_(ir_node const *node)
{
	assert(is_Builtin(node));
	return get_irn_arity(node) - (n_Builtin_max + 1);
}

static inline ir_node *get_Builtin_param_(ir_node const *node, int pos)
{
	assert(0 <= pos && pos < get_Builtin_n_params(node));
	return get_irn_n(node, pos + (n_Builtin_max + 1));
}

static inline void set_Builtin_param_(ir_node *node, int pos, ir_node *param)
{
	assert(0 <= pos && pos < get_Builtin_n_params(node));
	set_irn_n(node, pos + (n_Builtin_max + 1), param);
}

static inline ir_node **get_Builtin_param_arr_(ir_node *node)
{
	assert(is_Builtin(node));
	return get_irn_in(node) + (n_Builtin_max + 1);
}

static inline int is_Call_(const ir_node *node)
{
	return get_irn_op(node) == op_Call;
}
static inline ir_node *get_Call_mem_(const ir_node *node)
{
	assert(is_Call(node));
	return get_irn_n(node, n_Call_mem);
}

static inline void set_Call_mem_(ir_node *node, ir_node *mem)
{
	assert(is_Call(node));
	set_irn_n(node, n_Call_mem, mem);
}

static inline ir_node *get_Call_ptr_(const ir_node *node)
{
	assert(is_Call(node));
	return get_irn_n(node, n_Call_ptr);
}

static inline void set_Call_ptr_(ir_node *node, ir_node *ptr)
{
	assert(is_Call(node));
	set_irn_n(node, n_Call_ptr, ptr);
}

static inline int get_Call_n_params_(ir_node const *node)
{
	assert(is_Call(node));
	return get_irn_arity(node) - (n_Call_max + 1);
}

static inline ir_node *get_Call_param_(ir_node const *node, int pos)
{
	assert(0 <= pos && pos < get_Call_n_params(node));
	return get_irn_n(node, pos + (n_Call_max + 1));
}

static inline void set_Call_param_(ir_node *node, int pos, ir_node *param)
{
	assert(0 <= pos && pos < get_Call_n_params(node));
	set_irn_n(node, pos + (n_Call_max + 1), param);
}

static inline ir_node **get_Call_param_arr_(ir_node *node)
{
	assert(is_Call(node));
	return get_irn_in(node) + (n_Call_max + 1);
}

static inline int is_Cmp_(const ir_node *node)
{
	return get_irn_op(node) == op_Cmp;
}
static inline ir_node *get_Cmp_left_(const ir_node *node)
{
	assert(is_Cmp(node));
	return get_irn_n(node, n_Cmp_left);
}

static inline void set_Cmp_left_(ir_node *node, ir_node *left)
{
	assert(is_Cmp(node));
	set_irn_n(node, n_Cmp_left, left);
}

static inline ir_node *get_Cmp_right_(const ir_node *node)
{
	assert(is_Cmp(node));
	return get_irn_n(node, n_Cmp_right);
}

static inline void set_Cmp_right_(ir_node *node, ir_node *right)
{
	assert(is_Cmp(node));
	set_irn_n(node, n_Cmp_right, right);
}

static inline int is_Cond_(const ir_node *node)
{
	return get_irn_op(node) == op_Cond;
}
static inline ir_node *get_Cond_selector_(const ir_node *node)
{
	assert(is_Cond(node));
	return get_irn_n(node, n_Cond_selector);
}

static inline void set_Cond_selector_(ir_node *node, ir_node *selector)
{
	assert(is_Cond(node));
	set_irn_n(node, n_Cond_selector, selector);
}

static inline int is_Confirm_(const ir_node *node)
{
	return get_irn_op(node) == op_Confirm;
}
static inline ir_node *get_Confirm_value_(const ir_node *node)
{
	assert(is_Confirm(node));
	return get_irn_n(node, n_Confirm_value);
}

static inline void set_Confirm_value_(ir_node *node, ir_node *value)
{
	assert(is_Confirm(node));
	set_irn_n(node, n_Confirm_value, value);
}

static inline ir_node *get_Confirm_bound_(const ir_node *node)
{
	assert(is_Confirm(node));
	return get_irn_n(node, n_Confirm_bound);
}

static inline void set_Confirm_bound_(ir_node *node, ir_node *bound)
{
	assert(is_Confirm(node));
	set_irn_n(node, n_Confirm_bound, bound);
}

static inline int is_Const_(const ir_node *node)
{
	return get_irn_op(node) == op_Const;
}
static inline int is_Conv_(const ir_node *node)
{
	return get_irn_op(node) == op_Conv;
}
static inline ir_node *get_Conv_op_(const ir_node *node)
{
	assert(is_Conv(node));
	return get_irn_n(node, n_Conv_op);
}

static inline void set_Conv_op_(ir_node *node, ir_node *op)
{
	assert(is_Conv(node));
	set_irn_n(node, n_Conv_op, op);
}

static inline int is_CopyB_(const ir_node *node)
{
	return get_irn_op(node) == op_CopyB;
}
static inline ir_node *get_CopyB_mem_(const ir_node *node)
{
	assert(is_CopyB(node));
	return get_irn_n(node, n_CopyB_mem);
}

static inline void set_CopyB_mem_(ir_node *node, ir_node *mem)
{
	assert(is_CopyB(node));
	set_irn_n(node, n_CopyB_mem, mem);
}

static inline ir_node *get_CopyB_dst_(const ir_node *node)
{
	assert(is_CopyB(node));
	return get_irn_n(node, n_CopyB_dst);
}

static inline void set_CopyB_dst_(ir_node *node, ir_node *dst)
{
	assert(is_CopyB(node));
	set_irn_n(node, n_CopyB_dst, dst);
}

static inline ir_node *get_CopyB_src_(const ir_node *node)
{
	assert(is_CopyB(node));
	return get_irn_n(node, n_CopyB_src);
}

static inline void set_CopyB_src_(ir_node *node, ir_node *src)
{
	assert(is_CopyB(node));
	set_irn_n(node, n_CopyB_src, src);
}

static inline int is_Deleted_(const ir_node *node)
{
	return get_irn_op(node) == op_Deleted;
}
static inline int is_Div_(const ir_node *node)
{
	return get_irn_op(node) == op_Div;
}
static inline ir_node *get_Div_mem_(const ir_node *node)
{
	assert(is_Div(node));
	return get_irn_n(node, n_Div_mem);
}

static inline void set_Div_mem_(ir_node *node, ir_node *mem)
{
	assert(is_Div(node));
	set_irn_n(node, n_Div_mem, mem);
}

static inline ir_node *get_Div_left_(const ir_node *node)
{
	assert(is_Div(node));
	return get_irn_n(node, n_Div_left);
}

static inline void set_Div_left_(ir_node *node, ir_node *left)
{
	assert(is_Div(node));
	set_irn_n(node, n_Div_left, left);
}

static inline ir_node *get_Div_right_(const ir_node *node)
{
	assert(is_Div(node));
	return get_irn_n(node, n_Div_right);
}

static inline void set_Div_right_(ir_node *node, ir_node *right)
{
	assert(is_Div(node));
	set_irn_n(node, n_Div_right, right);
}

static inline int is_Dummy_(const ir_node *node)
{
	return get_irn_op(node) == op_Dummy;
}
static inline int is_End_(const ir_node *node)
{
	return get_irn_op(node) == op_End;
}
static inline int get_End_n_keepalives_(ir_node const *node)
{
	assert(is_End(node));
	return get_irn_arity(node);
}

static inline ir_node *get_End_keepalive_(ir_node const *node, int pos)
{
	assert(0 <= pos && pos < get_End_n_keepalives(node));
	return get_irn_n(node, pos);
}

static inline void set_End_keepalive_(ir_node *node, int pos, ir_node *keepalive)
{
	assert(0 <= pos && pos < get_End_n_keepalives(node));
	set_irn_n(node, pos, keepalive);
}

static inline ir_node **get_End_keepalive_arr_(ir_node *node)
{
	assert(is_End(node));
	return get_irn_in(node);
}

static inline int is_Eor_(const ir_node *node)
{
	return get_irn_op(node) == op_Eor;
}
static inline ir_node *get_Eor_left_(const ir_node *node)
{
	assert(is_Eor(node));
	return get_irn_n(node, n_Eor_left);
}

static inline void set_Eor_left_(ir_node *node, ir_node *left)
{
	assert(is_Eor(node));
	set_irn_n(node, n_Eor_left, left);
}

static inline ir_node *get_Eor_right_(const ir_node *node)
{
	assert(is_Eor(node));
	return get_irn_n(node, n_Eor_right);
}

static inline void set_Eor_right_(ir_node *node, ir_node *right)
{
	assert(is_Eor(node));
	set_irn_n(node, n_Eor_right, right);
}

static inline int is_Free_(const ir_node *node)
{
	return get_irn_op(node) == op_Free;
}
static inline ir_node *get_Free_mem_(const ir_node *node)
{
	assert(is_Free(node));
	return get_irn_n(node, n_Free_mem);
}

static inline void set_Free_mem_(ir_node *node, ir_node *mem)
{
	assert(is_Free(node));
	set_irn_n(node, n_Free_mem, mem);
}

static inline ir_node *get_Free_ptr_(const ir_node *node)
{
	assert(is_Free(node));
	return get_irn_n(node, n_Free_ptr);
}

static inline void set_Free_ptr_(ir_node *node, ir_node *ptr)
{
	assert(is_Free(node));
	set_irn_n(node, n_Free_ptr, ptr);
}

static inline int is_IJmp_(const ir_node *node)
{
	return get_irn_op(node) == op_IJmp;
}
static inline ir_node *get_IJmp_target_(const ir_node *node)
{
	assert(is_IJmp(node));
	return get_irn_n(node, n_IJmp_target);
}

static inline void set_IJmp_target_(ir_node *node, ir_node *target)
{
	assert(is_IJmp(node));
	set_irn_n(node, n_IJmp_target, target);
}

static inline int is_Id_(const ir_node *node)
{
	return get_irn_op(node) == op_Id;
}
static inline ir_node *get_Id_pred_(const ir_node *node)
{
	assert(is_Id(node));
	return get_irn_n(node, n_Id_pred);
}

static inline void set_Id_pred_(ir_node *node, ir_node *pred)
{
	assert(is_Id(node));
	set_irn_n(node, n_Id_pred, pred);
}

static inline int is_Jmp_(const ir_node *node)
{
	return get_irn_op(node) == op_Jmp;
}
static inline int is_Load_(const ir_node *node)
{
	return get_irn_op(node) == op_Load;
}
static inline ir_node *get_Load_mem_(const ir_node *node)
{
	assert(is_Load(node));
	return get_irn_n(node, n_Load_mem);
}

static inline void set_Load_mem_(ir_node *node, ir_node *mem)
{
	assert(is_Load(node));
	set_irn_n(node, n_Load_mem, mem);
}

static inline ir_node *get_Load_ptr_(const ir_node *node)
{
	assert(is_Load(node));
	return get_irn_n(node, n_Load_ptr);
}

static inline void set_Load_ptr_(ir_node *node, ir_node *ptr)
{
	assert(is_Load(node));
	set_irn_n(node, n_Load_ptr, ptr);
}

static inline int is_Member_(const ir_node *node)
{
	return get_irn_op(node) == op_Member;
}
static inline ir_node *get_Member_ptr_(const ir_node *node)
{
	assert(is_Member(node));
	return get_irn_n(node, n_Member_ptr);
}

static inline void set_Member_ptr_(ir_node *node, ir_node *ptr)
{
	assert(is_Member(node));
	set_irn_n(node, n_Member_ptr, ptr);
}

static inline int is_Minus_(const ir_node *node)
{
	return get_irn_op(node) == op_Minus;
}
static inline ir_node *get_Minus_op_(const ir_node *node)
{
	assert(is_Minus(node));
	return get_irn_n(node, n_Minus_op);
}

static inline void set_Minus_op_(ir_node *node, ir_node *op)
{
	assert(is_Minus(node));
	set_irn_n(node, n_Minus_op, op);
}

static inline int is_Mod_(const ir_node *node)
{
	return get_irn_op(node) == op_Mod;
}
static inline ir_node *get_Mod_mem_(const ir_node *node)
{
	assert(is_Mod(node));
	return get_irn_n(node, n_Mod_mem);
}

static inline void set_Mod_mem_(ir_node *node, ir_node *mem)
{
	assert(is_Mod(node));
	set_irn_n(node, n_Mod_mem, mem);
}

static inline ir_node *get_Mod_left_(const ir_node *node)
{
	assert(is_Mod(node));
	return get_irn_n(node, n_Mod_left);
}

static inline void set_Mod_left_(ir_node *node, ir_node *left)
{
	assert(is_Mod(node));
	set_irn_n(node, n_Mod_left, left);
}

static inline ir_node *get_Mod_right_(const ir_node *node)
{
	assert(is_Mod(node));
	return get_irn_n(node, n_Mod_right);
}

static inline void set_Mod_right_(ir_node *node, ir_node *right)
{
	assert(is_Mod(node));
	set_irn_n(node, n_Mod_right, right);
}

static inline int is_Mul_(const ir_node *node)
{
	return get_irn_op(node) == op_Mul;
}
static inline ir_node *get_Mul_left_(const ir_node *node)
{
	assert(is_Mul(node));
	return get_irn_n(node, n_Mul_left);
}

static inline void set_Mul_left_(ir_node *node, ir_node *left)
{
	assert(is_Mul(node));
	set_irn_n(node, n_Mul_left, left);
}

static inline ir_node *get_Mul_right_(const ir_node *node)
{
	assert(is_Mul(node));
	return get_irn_n(node, n_Mul_right);
}

static inline void set_Mul_right_(ir_node *node, ir_node *right)
{
	assert(is_Mul(node));
	set_irn_n(node, n_Mul_right, right);
}

static inline int is_Mulh_(const ir_node *node)
{
	return get_irn_op(node) == op_Mulh;
}
static inline ir_node *get_Mulh_left_(const ir_node *node)
{
	assert(is_Mulh(node));
	return get_irn_n(node, n_Mulh_left);
}

static inline void set_Mulh_left_(ir_node *node, ir_node *left)
{
	assert(is_Mulh(node));
	set_irn_n(node, n_Mulh_left, left);
}

static inline ir_node *get_Mulh_right_(const ir_node *node)
{
	assert(is_Mulh(node));
	return get_irn_n(node, n_Mulh_right);
}

static inline void set_Mulh_right_(ir_node *node, ir_node *right)
{
	assert(is_Mulh(node));
	set_irn_n(node, n_Mulh_right, right);
}

static inline int is_Mux_(const ir_node *node)
{
	return get_irn_op(node) == op_Mux;
}
static inline ir_node *get_Mux_sel_(const ir_node *node)
{
	assert(is_Mux(node));
	return get_irn_n(node, n_Mux_sel);
}

static inline void set_Mux_sel_(ir_node *node, ir_node *sel)
{
	assert(is_Mux(node));
	set_irn_n(node, n_Mux_sel, sel);
}

static inline ir_node *get_Mux_false_(const ir_node *node)
{
	assert(is_Mux(node));
	return get_irn_n(node, n_Mux_false);
}

static inline void set_Mux_false_(ir_node *node, ir_node *false_)
{
	assert(is_Mux(node));
	set_irn_n(node, n_Mux_false, false_);
}

static inline ir_node *get_Mux_true_(const ir_node *node)
{
	assert(is_Mux(node));
	return get_irn_n(node, n_Mux_true);
}

static inline void set_Mux_true_(ir_node *node, ir_node *true_)
{
	assert(is_Mux(node));
	set_irn_n(node, n_Mux_true, true_);
}

static inline int is_NoMem_(const ir_node *node)
{
	return get_irn_op(node) == op_NoMem;
}
static inline int is_Not_(const ir_node *node)
{
	return get_irn_op(node) == op_Not;
}
static inline ir_node *get_Not_op_(const ir_node *node)
{
	assert(is_Not(node));
	return get_irn_n(node, n_Not_op);
}

static inline void set_Not_op_(ir_node *node, ir_node *op)
{
	assert(is_Not(node));
	set_irn_n(node, n_Not_op, op);
}

static inline int is_Offset_(const ir_node *node)
{
	return get_irn_op(node) == op_Offset;
}
static inline int is_Or_(const ir_node *node)
{
	return get_irn_op(node) == op_Or;
}
static inline ir_node *get_Or_left_(const ir_node *node)
{
	assert(is_Or(node));
	return get_irn_n(node, n_Or_left);
}

static inline void set_Or_left_(ir_node *node, ir_node *left)
{
	assert(is_Or(node));
	set_irn_n(node, n_Or_left, left);
}

static inline ir_node *get_Or_right_(const ir_node *node)
{
	assert(is_Or(node));
	return get_irn_n(node, n_Or_right);
}

static inline void set_Or_right_(ir_node *node, ir_node *right)
{
	assert(is_Or(node));
	set_irn_n(node, n_Or_right, right);
}

static inline int is_Phi_(const ir_node *node)
{
	return get_irn_op(node) == op_Phi;
}
static inline int get_Phi_n_preds_(ir_node const *node)
{
	assert(is_Phi(node));
	return get_irn_arity(node);
}

static inline ir_node *get_Phi_pred_(ir_node const *node, int pos)
{
	assert(0 <= pos && pos < get_Phi_n_preds(node));
	return get_irn_n(node, pos);
}

static inline void set_Phi_pred_(ir_node *node, int pos, ir_node *pred)
{
	assert(0 <= pos && pos < get_Phi_n_preds(node));
	set_irn_n(node, pos, pred);
}

static inline ir_node **get_Phi_pred_arr_(ir_node *node)
{
	assert(is_Phi(node));
	return get_irn_in(node);
}

static inline int is_Pin_(const ir_node *node)
{
	return get_irn_op(node) == op_Pin;
}
static inline ir_node *get_Pin_op_(const ir_node *node)
{
	assert(is_Pin(node));
	return get_irn_n(node, n_Pin_op);
}

static inline void set_Pin_op_(ir_node *node, ir_node *op)
{
	assert(is_Pin(node));
	set_irn_n(node, n_Pin_op, op);
}

static inline int is_Proj_(const ir_node *node)
{
	return get_irn_op(node) == op_Proj;
}
static inline ir_node *get_Proj_pred_(const ir_node *node)
{
	assert(is_Proj(node));
	return get_irn_n(node, n_Proj_pred);
}

static inline void set_Proj_pred_(ir_node *node, ir_node *pred)
{
	assert(is_Proj(node));
	set_irn_n(node, n_Proj_pred, pred);
}

static inline int is_Raise_(const ir_node *node)
{
	return get_irn_op(node) == op_Raise;
}
static inline ir_node *get_Raise_mem_(const ir_node *node)
{
	assert(is_Raise(node));
	return get_irn_n(node, n_Raise_mem);
}

static inline void set_Raise_mem_(ir_node *node, ir_node *mem)
{
	assert(is_Raise(node));
	set_irn_n(node, n_Raise_mem, mem);
}

static inline ir_node *get_Raise_exo_ptr_(const ir_node *node)
{
	assert(is_Raise(node));
	return get_irn_n(node, n_Raise_exo_ptr);
}

static inline void set_Raise_exo_ptr_(ir_node *node, ir_node *exo_ptr)
{
	assert(is_Raise(node));
	set_irn_n(node, n_Raise_exo_ptr, exo_ptr);
}

static inline int is_Return_(const ir_node *node)
{
	return get_irn_op(node) == op_Return;
}
static inline ir_node *get_Return_mem_(const ir_node *node)
{
	assert(is_Return(node));
	return get_irn_n(node, n_Return_mem);
}

static inline void set_Return_mem_(ir_node *node, ir_node *mem)
{
	assert(is_Return(node));
	set_irn_n(node, n_Return_mem, mem);
}

static inline int get_Return_n_ress_(ir_node const *node)
{
	assert(is_Return(node));
	return get_irn_arity(node) - (n_Return_max + 1);
}

static inline ir_node *get_Return_res_(ir_node const *node, int pos)
{
	assert(0 <= pos && pos < get_Return_n_ress(node));
	return get_irn_n(node, pos + (n_Return_max + 1));
}

static inline void set_Return_res_(ir_node *node, int pos, ir_node *res)
{
	assert(0 <= pos && pos < get_Return_n_ress(node));
	set_irn_n(node, pos + (n_Return_max + 1), res);
}

static inline ir_node **get_Return_res_arr_(ir_node *node)
{
	assert(is_Return(node));
	return get_irn_in(node) + (n_Return_max + 1);
}

static inline int is_Sel_(const ir_node *node)
{
	return get_irn_op(node) == op_Sel;
}
static inline ir_node *get_Sel_ptr_(const ir_node *node)
{
	assert(is_Sel(node));
	return get_irn_n(node, n_Sel_ptr);
}

static inline void set_Sel_ptr_(ir_node *node, ir_node *ptr)
{
	assert(is_Sel(node));
	set_irn_n(node, n_Sel_ptr, ptr);
}

static inline ir_node *get_Sel_index_(const ir_node *node)
{
	assert(is_Sel(node));
	return get_irn_n(node, n_Sel_index);
}

static inline void set_Sel_index_(ir_node *node, ir_node *index)
{
	assert(is_Sel(node));
	set_irn_n(node, n_Sel_index, index);
}

static inline int is_Shl_(const ir_node *node)
{
	return get_irn_op(node) == op_Shl;
}
static inline ir_node *get_Shl_left_(const ir_node *node)
{
	assert(is_Shl(node));
	return get_irn_n(node, n_Shl_left);
}

static inline void set_Shl_left_(ir_node *node, ir_node *left)
{
	assert(is_Shl(node));
	set_irn_n(node, n_Shl_left, left);
}

static inline ir_node *get_Shl_right_(const ir_node *node)
{
	assert(is_Shl(node));
	return get_irn_n(node, n_Shl_right);
}

static inline void set_Shl_right_(ir_node *node, ir_node *right)
{
	assert(is_Shl(node));
	set_irn_n(node, n_Shl_right, right);
}

static inline int is_Shr_(const ir_node *node)
{
	return get_irn_op(node) == op_Shr;
}
static inline ir_node *get_Shr_left_(const ir_node *node)
{
	assert(is_Shr(node));
	return get_irn_n(node, n_Shr_left);
}

static inline void set_Shr_left_(ir_node *node, ir_node *left)
{
	assert(is_Shr(node));
	set_irn_n(node, n_Shr_left, left);
}

static inline ir_node *get_Shr_right_(const ir_node *node)
{
	assert(is_Shr(node));
	return get_irn_n(node, n_Shr_right);
}

static inline void set_Shr_right_(ir_node *node, ir_node *right)
{
	assert(is_Shr(node));
	set_irn_n(node, n_Shr_right, right);
}

static inline int is_Shrs_(const ir_node *node)
{
	return get_irn_op(node) == op_Shrs;
}
static inline ir_node *get_Shrs_left_(const ir_node *node)
{
	assert(is_Shrs(node));
	return get_irn_n(node, n_Shrs_left);
}

static inline void set_Shrs_left_(ir_node *node, ir_node *left)
{
	assert(is_Shrs(node));
	set_irn_n(node, n_Shrs_left, left);
}

static inline ir_node *get_Shrs_right_(const ir_node *node)
{
	assert(is_Shrs(node));
	return get_irn_n(node, n_Shrs_right);
}

static inline void set_Shrs_right_(ir_node *node, ir_node *right)
{
	assert(is_Shrs(node));
	set_irn_n(node, n_Shrs_right, right);
}

static inline int is_Size_(const ir_node *node)
{
	return get_irn_op(node) == op_Size;
}
static inline int is_Start_(const ir_node *node)
{
	return get_irn_op(node) == op_Start;
}
static inline int is_Store_(const ir_node *node)
{
	return get_irn_op(node) == op_Store;
}
static inline ir_node *get_Store_mem_(const ir_node *node)
{
	assert(is_Store(node));
	return get_irn_n(node, n_Store_mem);
}

static inline void set_Store_mem_(ir_node *node, ir_node *mem)
{
	assert(is_Store(node));
	set_irn_n(node, n_Store_mem, mem);
}

static inline ir_node *get_Store_ptr_(const ir_node *node)
{
	assert(is_Store(node));
	return get_irn_n(node, n_Store_ptr);
}

static inline void set_Store_ptr_(ir_node *node, ir_node *ptr)
{
	assert(is_Store(node));
	set_irn_n(node, n_Store_ptr, ptr);
}

static inline ir_node *get_Store_value_(const ir_node *node)
{
	assert(is_Store(node));
	return get_irn_n(node, n_Store_value);
}

static inline void set_Store_value_(ir_node *node, ir_node *value)
{
	assert(is_Store(node));
	set_irn_n(node, n_Store_value, value);
}

static inline int is_Sub_(const ir_node *node)
{
	return get_irn_op(node) == op_Sub;
}
static inline ir_node *get_Sub_left_(const ir_node *node)
{
	assert(is_Sub(node));
	return get_irn_n(node, n_Sub_left);
}

static inline void set_Sub_left_(ir_node *node, ir_node *left)
{
	assert(is_Sub(node));
	set_irn_n(node, n_Sub_left, left);
}

static inline ir_node *get_Sub_right_(const ir_node *node)
{
	assert(is_Sub(node));
	return get_irn_n(node, n_Sub_right);
}

static inline void set_Sub_right_(ir_node *node, ir_node *right)
{
	assert(is_Sub(node));
	set_irn_n(node, n_Sub_right, right);
}

static inline int is_Switch_(const ir_node *node)
{
	return get_irn_op(node) == op_Switch;
}
static inline ir_node *get_Switch_selector_(const ir_node *node)
{
	assert(is_Switch(node));
	return get_irn_n(node, n_Switch_selector);
}

static inline void set_Switch_selector_(ir_node *node, ir_node *selector)
{
	assert(is_Switch(node));
	set_irn_n(node, n_Switch_selector, selector);
}

static inline int is_Sync_(const ir_node *node)
{
	return get_irn_op(node) == op_Sync;
}
static inline int get_Sync_n_preds_(ir_node const *node)
{
	assert(is_Sync(node));
	return get_irn_arity(node);
}

static inline ir_node *get_Sync_pred_(ir_node const *node, int pos)
{
	assert(0 <= pos && pos < get_Sync_n_preds(node));
	return get_irn_n(node, pos);
}

static inline void set_Sync_pred_(ir_node *node, int pos, ir_node *pred)
{
	assert(0 <= pos && pos < get_Sync_n_preds(node));
	set_irn_n(node, pos, pred);
}

static inline ir_node **get_Sync_pred_arr_(ir_node *node)
{
	assert(is_Sync(node));
	return get_irn_in(node);
}

static inline int is_Tuple_(const ir_node *node)
{
	return get_irn_op(node) == op_Tuple;
}
static inline int get_Tuple_n_preds_(ir_node const *node)
{
	assert(is_Tuple(node));
	return get_irn_arity(node);
}

static inline ir_node *get_Tuple_pred_(ir_node const *node, int pos)
{
	assert(0 <= pos && pos < get_Tuple_n_preds(node));
	return get_irn_n(node, pos);
}

static inline void set_Tuple_pred_(ir_node *node, int pos, ir_node *pred)
{
	assert(0 <= pos && pos < get_Tuple_n_preds(node));
	set_irn_n(node, pos, pred);
}

static inline ir_node **get_Tuple_pred_arr_(ir_node *node)
{
	assert(is_Tuple(node));
	return get_irn_in(node);
}

static inline int is_Unknown_(const ir_node *node)
{
	return get_irn_op(node) == op_Unknown;
}
static inline int is_entconst_(const ir_node *node)
{
	return is_Address(node) || is_Offset(node);
}


static inline int is_typeconst_(const ir_node *node)
{
	return is_Align(node) || is_Size(node);
}


static inline ir_asm_constraint* get_ASM_constraints_(const ir_node *node)
{
	assert(is_ASM(node));
	return node->attr.assem.constraints;
}

static inline void set_ASM_constraints_(ir_node *node, ir_asm_constraint* constraints)
{
	assert(is_ASM(node));
	node->attr.assem.constraints = constraints;
}

static inline ident** get_ASM_clobbers_(const ir_node *node)
{
	assert(is_ASM(node));
	return node->attr.assem.clobbers;
}

static inline void set_ASM_clobbers_(ir_node *node, ident** clobbers)
{
	assert(is_ASM(node));
	node->attr.assem.clobbers = clobbers;
}

static inline ident* get_ASM_text_(const ir_node *node)
{
	assert(is_ASM(node));
	return node->attr.assem.text;
}

static inline void set_ASM_text_(ir_node *node, ident* text)
{
	assert(is_ASM(node));
	node->attr.assem.text = text;
}

static inline ir_entity* get_Address_entity_(const ir_node *node)
{
	assert(is_Address(node));
	return node->attr.entc.entity;
}

static inline void set_Address_entity_(ir_node *node, ir_entity* entity)
{
	assert(is_Address(node));
	node->attr.entc.entity = entity;
}

static inline ir_type* get_Align_type_(const ir_node *node)
{
	assert(is_Align(node));
	return node->attr.typec.type;
}

static inline void set_Align_type_(ir_node *node, ir_type* type)
{
	assert(is_Align(node));
	node->attr.typec.type = type;
}

static inline unsigned get_Alloc_alignment_(const ir_node *node)
{
	assert(is_Alloc(node));
	return node->attr.alloc.alignment;
}

static inline void set_Alloc_alignment_(ir_node *node, unsigned alignment)
{
	assert(is_Alloc(node));
	node->attr.alloc.alignment = alignment;
}

static inline ir_entity* get_Block_entity_(const ir_node *node)
{
	assert(is_Block(node));
	return node->attr.block.entity;
}

static inline void set_Block_entity_(ir_node *node, ir_entity* entity)
{
	assert(is_Block(node));
	node->attr.block.entity = entity;
}

static inline ir_builtin_kind get_Builtin_kind_(const ir_node *node)
{
	assert(is_Builtin(node));
	return node->attr.builtin.kind;
}

static inline void set_Builtin_kind_(ir_node *node, ir_builtin_kind kind)
{
	assert(is_Builtin(node));
	node->attr.builtin.kind = kind;
}

static inline ir_type* get_Builtin_type_(const ir_node *node)
{
	assert(is_Builtin(node));
	return node->attr.builtin.type;
}

static inline void set_Builtin_type_(ir_node *node, ir_type* type)
{
	assert(is_Builtin(node));
	node->attr.builtin.type = type;
}

static inline ir_type* get_Call_type_(const ir_node *node)
{
	assert(is_Call(node));
	return node->attr.call.type;
}

static inline void set_Call_type_(ir_node *node, ir_type* type)
{
	assert(is_Call(node));
	node->attr.call.type = type;
}

static inline ir_relation get_Cmp_relation_(const ir_node *node)
{
	assert(is_Cmp(node));
	return node->attr.cmp.relation;
}

static inline void set_Cmp_relation_(ir_node *node, ir_relation relation)
{
	assert(is_Cmp(node));
	node->attr.cmp.relation = relation;
}

static inline cond_jmp_predicate get_Cond_jmp_pred_(const ir_node *node)
{
	assert(is_Cond(node));
	return node->attr.cond.jmp_pred;
}

static inline void set_Cond_jmp_pred_(ir_node *node, cond_jmp_predicate jmp_pred)
{
	assert(is_Cond(node));
	node->attr.cond.jmp_pred = jmp_pred;
}

static inline ir_relation get_Confirm_relation_(const ir_node *node)
{
	assert(is_Confirm(node));
	return node->attr.confirm.relation;
}

static inline void set_Confirm_relation_(ir_node *node, ir_relation relation)
{
	assert(is_Confirm(node));
	node->attr.confirm.relation = relation;
}

static inline ir_tarval* get_Const_tarval_(const ir_node *node)
{
	assert(is_Const(node));
	return node->attr.con.tarval;
}

static inline void set_Const_tarval_(ir_node *node, ir_tarval* tarval)
{
	assert(is_Const(node));
	node->attr.con.tarval = tarval;
}

static inline ir_type* get_CopyB_type_(const ir_node *node)
{
	assert(is_CopyB(node));
	return node->attr.copyb.type;
}

static inline void set_CopyB_type_(ir_node *node, ir_type* type)
{
	assert(is_CopyB(node));
	node->attr.copyb.type = type;
}

static inline ir_volatility get_CopyB_volatility_(const ir_node *node)
{
	assert(is_CopyB(node));
	return node->attr.copyb.volatility;
}

static inline void set_CopyB_volatility_(ir_node *node, ir_volatility volatility)
{
	assert(is_CopyB(node));
	node->attr.copyb.volatility = volatility;
}

static inline ir_mode* get_Div_resmode_(const ir_node *node)
{
	assert(is_Div(node));
	return node->attr.div.resmode;
}

static inline void set_Div_resmode_(ir_node *node, ir_mode* resmode)
{
	assert(is_Div(node));
	node->attr.div.resmode = resmode;
}

static inline int get_Div_no_remainder_(const ir_node *node)
{
	assert(is_Div(node));
	return node->attr.div.no_remainder;
}

static inline void set_Div_no_remainder_(ir_node *node, int no_remainder)
{
	assert(is_Div(node));
	node->attr.div.no_remainder = no_remainder;
}

static inline ir_mode* get_Load_mode_(const ir_node *node)
{
	assert(is_Load(node));
	return node->attr.load.mode;
}

static inline void set_Load_mode_(ir_node *node, ir_mode* mode)
{
	assert(is_Load(node));
	node->attr.load.mode = mode;
}

static inline ir_type* get_Load_type_(const ir_node *node)
{
	assert(is_Load(node));
	return node->attr.load.type;
}

static inline void set_Load_type_(ir_node *node, ir_type* type)
{
	assert(is_Load(node));
	node->attr.load.type = type;
}

static inline ir_volatility get_Load_volatility_(const ir_node *node)
{
	assert(is_Load(node));
	return node->attr.load.volatility;
}

static inline void set_Load_volatility_(ir_node *node, ir_volatility volatility)
{
	assert(is_Load(node));
	node->attr.load.volatility = volatility;
}

static inline ir_align get_Load_unaligned_(const ir_node *node)
{
	assert(is_Load(node));
	return node->attr.load.unaligned;
}

static inline void set_Load_unaligned_(ir_node *node, ir_align unaligned)
{
	assert(is_Load(node));
	node->attr.load.unaligned = unaligned;
}

static inline ir_entity* get_Member_entity_(const ir_node *node)
{
	assert(is_Member(node));
	return node->attr.member.entity;
}

static inline void set_Member_entity_(ir_node *node, ir_entity* entity)
{
	assert(is_Member(node));
	node->attr.member.entity = entity;
}

static inline ir_mode* get_Mod_resmode_(const ir_node *node)
{
	assert(is_Mod(node));
	return node->attr.mod.resmode;
}

static inline void set_Mod_resmode_(ir_node *node, ir_mode* resmode)
{
	assert(is_Mod(node));
	node->attr.mod.resmode = resmode;
}

static inline ir_entity* get_Offset_entity_(const ir_node *node)
{
	assert(is_Offset(node));
	return node->attr.entc.entity;
}

static inline void set_Offset_entity_(ir_node *node, ir_entity* entity)
{
	assert(is_Offset(node));
	node->attr.entc.entity = entity;
}

static inline int get_Phi_loop_(const ir_node *node)
{
	assert(is_Phi(node));
	return node->attr.phi.loop;
}

static inline void set_Phi_loop_(ir_node *node, int loop)
{
	assert(is_Phi(node));
	node->attr.phi.loop = loop;
}

static inline unsigned get_Proj_num_(const ir_node *node)
{
	assert(is_Proj(node));
	return node->attr.proj.num;
}

static inline void set_Proj_num_(ir_node *node, unsigned num)
{
	assert(is_Proj(node));
	node->attr.proj.num = num;
}

static inline ir_type* get_Sel_type_(const ir_node *node)
{
	assert(is_Sel(node));
	return node->attr.sel.type;
}

static inline void set_Sel_type_(ir_node *node, ir_type* type)
{
	assert(is_Sel(node));
	node->attr.sel.type = type;
}

static inline ir_type* get_Size_type_(const ir_node *node)
{
	assert(is_Size(node));
	return node->attr.typec.type;
}

static inline void set_Size_type_(ir_node *node, ir_type* type)
{
	assert(is_Size(node));
	node->attr.typec.type = type;
}

static inline ir_type* get_Store_type_(const ir_node *node)
{
	assert(is_Store(node));
	return node->attr.store.type;
}

static inline void set_Store_type_(ir_node *node, ir_type* type)
{
	assert(is_Store(node));
	node->attr.store.type = type;
}

static inline ir_volatility get_Store_volatility_(const ir_node *node)
{
	assert(is_Store(node));
	return node->attr.store.volatility;
}

static inline void set_Store_volatility_(ir_node *node, ir_volatility volatility)
{
	assert(is_Store(node));
	node->attr.store.volatility = volatility;
}

static inline ir_align get_Store_unaligned_(const ir_node *node)
{
	assert(is_Store(node));
	return node->attr.store.unaligned;
}

static inline void set_Store_unaligned_(ir_node *node, ir_align unaligned)
{
	assert(is_Store(node));
	node->attr.store.unaligned = unaligned;
}

static inline unsigned get_Switch_n_outs_(const ir_node *node)
{
	assert(is_Switch(node));
	return node->attr.switcha.n_outs;
}

static inline void set_Switch_n_outs_(ir_node *node, unsigned n_outs)
{
	assert(is_Switch(node));
	node->attr.switcha.n_outs = n_outs;
}

static inline ir_switch_table* get_Switch_table_(const ir_node *node)
{
	assert(is_Switch(node));
	return node->attr.switcha.table;
}

static inline void set_Switch_table_(ir_node *node, ir_switch_table* table)
{
	assert(is_Switch(node));
	node->attr.switcha.table = table;
}

static inline ir_entity* get_entconst_entity_(const ir_node *node)
{
	assert(is_entconst(node));
	return node->attr.entc.entity;
}

static inline void set_entconst_entity_(ir_node *node, ir_entity* entity)
{
	assert(is_entconst(node));
	node->attr.entc.entity = entity;
}

static inline ir_type* get_typeconst_type_(const ir_node *node)
{
	assert(is_typeconst(node));
	return node->attr.typec.type;
}

static inline void set_typeconst_type_(ir_node *node, ir_type* type)
{
	assert(is_typeconst(node));
	node->attr.typec.type = type;
}
void ir_init_opcodes(void);
void ir_finish_opcodes(void);

#endif
