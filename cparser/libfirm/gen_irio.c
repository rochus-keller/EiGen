/* Warning: Automatically generated file */

#include "irio_t.h"
static ir_node *read_Add(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_left = read_node_ref(env);
	ir_node *irn_right = read_node_ref(env);
	ir_node *res = new_r_Add(block, irn_left, irn_right);
	return res;
}

static ir_node *read_Address(read_env_t *env)
{
	ir_entity* entity = read_entity_ref(env);
	ir_node *res = new_r_Address(env->irg, entity);
	return res;
}

static ir_node *read_Align(read_env_t *env)
{
	ir_mode *mode = read_mode_ref(env);
	ir_type* type = read_type_ref(env);
	ir_node *res = new_r_Align(env->irg, mode, type);
	return res;
}

static ir_node *read_Alloc(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_mem = read_node_ref(env);
	ir_node *irn_size = read_node_ref(env);
	unsigned alignment = read_unsigned(env);
	ir_node *res = new_r_Alloc(block, irn_mem, irn_size, alignment);
	return res;
}

static ir_node *read_And(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_left = read_node_ref(env);
	ir_node *irn_right = read_node_ref(env);
	ir_node *res = new_r_And(block, irn_left, irn_right);
	return res;
}

static ir_node *read_Bad(read_env_t *env)
{
	ir_mode *mode = read_mode_ref(env);
	ir_node *res = new_r_Bad(env->irg, mode);
	return res;
}

static ir_node *read_Bitcast(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_op = read_node_ref(env);
	ir_mode *mode = read_mode_ref(env);
	ir_node *res = new_r_Bitcast(block, irn_op, mode);
	return res;
}

static ir_node *read_Builtin(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_mem = read_node_ref(env);
	ir_builtin_kind kind = read_builtin_kind(env);
	ir_type* type = read_type_ref(env);
	int pinned = read_pinned(env);
	int arity = read_preds(env);
	ir_node **in = (ir_node**)obstack_finish(&env->preds_obst);
	ir_node *res = new_r_Builtin(block, irn_mem, arity, in, kind, type);
	obstack_free(&env->preds_obst, in);
	set_irn_pinned(res, pinned);
	return res;
}

static ir_node *read_Call(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_mem = read_node_ref(env);
	ir_node *irn_ptr = read_node_ref(env);
	ir_type* type = read_type_ref(env);
	int pinned = read_pinned(env);
	bool throws = read_throws(env);
	int arity = read_preds(env);
	ir_node **in = (ir_node**)obstack_finish(&env->preds_obst);
	ir_node *res = new_r_Call(block, irn_mem, irn_ptr, arity, in, type);
	obstack_free(&env->preds_obst, in);
	set_irn_pinned(res, pinned);
	ir_set_throws_exception(res, throws);
	return res;
}

static ir_node *read_Cmp(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_left = read_node_ref(env);
	ir_node *irn_right = read_node_ref(env);
	ir_relation relation = read_relation(env);
	ir_node *res = new_r_Cmp(block, irn_left, irn_right, relation);
	return res;
}

static ir_node *read_Cond(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_selector = read_node_ref(env);
	cond_jmp_predicate jmp_pred = read_cond_jmp_predicate(env);
	ir_node *res = new_r_Cond(block, irn_selector);
	set_Cond_jmp_pred(res, jmp_pred);
	return res;
}

static ir_node *read_Confirm(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_value = read_node_ref(env);
	ir_node *irn_bound = read_node_ref(env);
	ir_relation relation = read_relation(env);
	ir_node *res = new_r_Confirm(block, irn_value, irn_bound, relation);
	return res;
}

static ir_node *read_Const(read_env_t *env)
{
	ir_tarval* tarval = read_tarval_ref(env);
	ir_node *res = new_r_Const(env->irg, tarval);
	return res;
}

static ir_node *read_Conv(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_op = read_node_ref(env);
	ir_mode *mode = read_mode_ref(env);
	ir_node *res = new_r_Conv(block, irn_op, mode);
	return res;
}

static ir_node *read_CopyB(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_mem = read_node_ref(env);
	ir_node *irn_dst = read_node_ref(env);
	ir_node *irn_src = read_node_ref(env);
	ir_type* type = read_type_ref(env);
	ir_volatility volatility = read_volatility(env);
	ir_cons_flags flags = cons_none
		| (volatility == volatility_is_volatile ? cons_volatile : cons_none);
	ir_node *res = new_r_CopyB(block, irn_mem, irn_dst, irn_src, type, flags);
	set_CopyB_volatility(res, volatility);
	return res;
}

static ir_node *read_Div(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_mem = read_node_ref(env);
	ir_node *irn_left = read_node_ref(env);
	ir_node *irn_right = read_node_ref(env);
	ir_mode* resmode = read_mode_ref(env);
	int no_remainder = read_int(env);
	int pinned = read_pinned(env);
	bool throws = read_throws(env);
	ir_node *res = new_r_Div(block, irn_mem, irn_left, irn_right, pinned);
	set_Div_resmode(res, resmode);
	set_Div_no_remainder(res, no_remainder);
	set_irn_pinned(res, pinned);
	ir_set_throws_exception(res, throws);
	return res;
}

static ir_node *read_Dummy(read_env_t *env)
{
	ir_mode *mode = read_mode_ref(env);
	ir_node *res = new_r_Dummy(env->irg, mode);
	return res;
}

static ir_node *read_End(read_env_t *env)
{
	int arity = read_preds(env);
	ir_node **in = (ir_node**)obstack_finish(&env->preds_obst);
	ir_node *res = new_r_End(env->irg, arity, in);
	obstack_free(&env->preds_obst, in);
	return res;
}

static ir_node *read_Eor(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_left = read_node_ref(env);
	ir_node *irn_right = read_node_ref(env);
	ir_node *res = new_r_Eor(block, irn_left, irn_right);
	return res;
}

static ir_node *read_Free(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_mem = read_node_ref(env);
	ir_node *irn_ptr = read_node_ref(env);
	ir_node *res = new_r_Free(block, irn_mem, irn_ptr);
	return res;
}

static ir_node *read_IJmp(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_target = read_node_ref(env);
	ir_node *res = new_r_IJmp(block, irn_target);
	return res;
}

static ir_node *read_Jmp(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *res = new_r_Jmp(block);
	return res;
}

static ir_node *read_Load(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_mem = read_node_ref(env);
	ir_node *irn_ptr = read_node_ref(env);
	ir_mode* mode = read_mode_ref(env);
	ir_type* type = read_type_ref(env);
	ir_volatility volatility = read_volatility(env);
	ir_align unaligned = read_align(env);
	int pinned = read_pinned(env);
	bool throws = read_throws(env);
	ir_cons_flags flags = cons_none
		| (volatility == volatility_is_volatile ? cons_volatile : cons_none)
		| (unaligned == align_non_aligned ? cons_unaligned : cons_none)
		| (pinned == 0 ? cons_floats : cons_none)
		| (throws ? cons_throws_exception : cons_none);
	ir_node *res = new_r_Load(block, irn_mem, irn_ptr, mode, type, flags);
	set_Load_volatility(res, volatility);
	set_Load_unaligned(res, unaligned);
	set_irn_pinned(res, pinned);
	ir_set_throws_exception(res, throws);
	return res;
}

static ir_node *read_Member(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_ptr = read_node_ref(env);
	ir_entity* entity = read_entity_ref(env);
	ir_node *res = new_r_Member(block, irn_ptr, entity);
	return res;
}

static ir_node *read_Minus(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_op = read_node_ref(env);
	ir_node *res = new_r_Minus(block, irn_op);
	return res;
}

static ir_node *read_Mod(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_mem = read_node_ref(env);
	ir_node *irn_left = read_node_ref(env);
	ir_node *irn_right = read_node_ref(env);
	ir_mode* resmode = read_mode_ref(env);
	int pinned = read_pinned(env);
	bool throws = read_throws(env);
	ir_node *res = new_r_Mod(block, irn_mem, irn_left, irn_right, pinned);
	set_Mod_resmode(res, resmode);
	set_irn_pinned(res, pinned);
	ir_set_throws_exception(res, throws);
	return res;
}

static ir_node *read_Mul(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_left = read_node_ref(env);
	ir_node *irn_right = read_node_ref(env);
	ir_node *res = new_r_Mul(block, irn_left, irn_right);
	return res;
}

static ir_node *read_Mulh(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_left = read_node_ref(env);
	ir_node *irn_right = read_node_ref(env);
	ir_node *res = new_r_Mulh(block, irn_left, irn_right);
	return res;
}

static ir_node *read_Mux(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_sel = read_node_ref(env);
	ir_node *irn_false = read_node_ref(env);
	ir_node *irn_true = read_node_ref(env);
	ir_node *res = new_r_Mux(block, irn_sel, irn_false, irn_true);
	return res;
}

static ir_node *read_NoMem(read_env_t *env)
{
	ir_node *res = new_r_NoMem(env->irg);
	return res;
}

static ir_node *read_Not(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_op = read_node_ref(env);
	ir_node *res = new_r_Not(block, irn_op);
	return res;
}

static ir_node *read_Offset(read_env_t *env)
{
	ir_mode *mode = read_mode_ref(env);
	ir_entity* entity = read_entity_ref(env);
	ir_node *res = new_r_Offset(env->irg, mode, entity);
	return res;
}

static ir_node *read_Or(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_left = read_node_ref(env);
	ir_node *irn_right = read_node_ref(env);
	ir_node *res = new_r_Or(block, irn_left, irn_right);
	return res;
}

static ir_node *read_Pin(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_op = read_node_ref(env);
	ir_node *res = new_r_Pin(block, irn_op);
	return res;
}

static ir_node *read_Proj(read_env_t *env)
{
	ir_node *irn_pred = read_node_ref(env);
	ir_mode *mode = read_mode_ref(env);
	unsigned num = read_unsigned(env);
	ir_node *res = new_r_Proj(irn_pred, mode, num);
	return res;
}

static ir_node *read_Raise(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_mem = read_node_ref(env);
	ir_node *irn_exo_ptr = read_node_ref(env);
	ir_node *res = new_r_Raise(block, irn_mem, irn_exo_ptr);
	return res;
}

static ir_node *read_Return(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_mem = read_node_ref(env);
	int arity = read_preds(env);
	ir_node **in = (ir_node**)obstack_finish(&env->preds_obst);
	ir_node *res = new_r_Return(block, irn_mem, arity, in);
	obstack_free(&env->preds_obst, in);
	return res;
}

static ir_node *read_Sel(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_ptr = read_node_ref(env);
	ir_node *irn_index = read_node_ref(env);
	ir_type* type = read_type_ref(env);
	ir_node *res = new_r_Sel(block, irn_ptr, irn_index, type);
	return res;
}

static ir_node *read_Shl(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_left = read_node_ref(env);
	ir_node *irn_right = read_node_ref(env);
	ir_node *res = new_r_Shl(block, irn_left, irn_right);
	return res;
}

static ir_node *read_Shr(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_left = read_node_ref(env);
	ir_node *irn_right = read_node_ref(env);
	ir_node *res = new_r_Shr(block, irn_left, irn_right);
	return res;
}

static ir_node *read_Shrs(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_left = read_node_ref(env);
	ir_node *irn_right = read_node_ref(env);
	ir_node *res = new_r_Shrs(block, irn_left, irn_right);
	return res;
}

static ir_node *read_Size(read_env_t *env)
{
	ir_mode *mode = read_mode_ref(env);
	ir_type* type = read_type_ref(env);
	ir_node *res = new_r_Size(env->irg, mode, type);
	return res;
}

static ir_node *read_Start(read_env_t *env)
{
	ir_node *res = new_r_Start(env->irg);
	return res;
}

static ir_node *read_Store(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_mem = read_node_ref(env);
	ir_node *irn_ptr = read_node_ref(env);
	ir_node *irn_value = read_node_ref(env);
	ir_type* type = read_type_ref(env);
	ir_volatility volatility = read_volatility(env);
	ir_align unaligned = read_align(env);
	int pinned = read_pinned(env);
	bool throws = read_throws(env);
	ir_cons_flags flags = cons_none
		| (volatility == volatility_is_volatile ? cons_volatile : cons_none)
		| (unaligned == align_non_aligned ? cons_unaligned : cons_none)
		| (pinned == 0 ? cons_floats : cons_none)
		| (throws ? cons_throws_exception : cons_none);
	ir_node *res = new_r_Store(block, irn_mem, irn_ptr, irn_value, type, flags);
	set_Store_volatility(res, volatility);
	set_Store_unaligned(res, unaligned);
	set_irn_pinned(res, pinned);
	ir_set_throws_exception(res, throws);
	return res;
}

static ir_node *read_Sub(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_left = read_node_ref(env);
	ir_node *irn_right = read_node_ref(env);
	ir_node *res = new_r_Sub(block, irn_left, irn_right);
	return res;
}

static ir_node *read_Switch(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	ir_node *irn_selector = read_node_ref(env);
	unsigned n_outs = read_unsigned(env);
	ir_switch_table* table = read_switch_table_ref(env);
	ir_node *res = new_r_Switch(block, irn_selector, n_outs, table);
	return res;
}

static ir_node *read_Sync(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	int arity = read_preds(env);
	ir_node **in = (ir_node**)obstack_finish(&env->preds_obst);
	ir_node *res = new_r_Sync(block, arity, in);
	obstack_free(&env->preds_obst, in);
	return res;
}

static ir_node *read_Tuple(read_env_t *env)
{
	ir_node *block = read_node_ref(env);
	int arity = read_preds(env);
	ir_node **in = (ir_node**)obstack_finish(&env->preds_obst);
	ir_node *res = new_r_Tuple(block, arity, in);
	obstack_free(&env->preds_obst, in);
	return res;
}

static ir_node *read_Unknown(read_env_t *env)
{
	ir_mode *mode = read_mode_ref(env);
	ir_node *res = new_r_Unknown(env->irg, mode);
	return res;
}

static void write_Add(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Add");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Add_left(node));
	write_node_ref(env, get_Add_right(node));
}

static void write_Address(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Address");
	write_node_nr(env, node);
	write_entity_ref(env, get_Address_entity(node));
}

static void write_Align(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Align");
	write_node_nr(env, node);
	write_mode_ref(env, get_irn_mode(node));
	write_type_ref(env, get_Align_type(node));
}

static void write_Alloc(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Alloc");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Alloc_mem(node));
	write_node_ref(env, get_Alloc_size(node));
	write_unsigned(env, get_Alloc_alignment(node));
}

static void write_And(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "And");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_And_left(node));
	write_node_ref(env, get_And_right(node));
}

static void write_Bad(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Bad");
	write_node_nr(env, node);
	write_mode_ref(env, get_irn_mode(node));
}

static void write_Bitcast(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Bitcast");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Bitcast_op(node));
	write_mode_ref(env, get_irn_mode(node));
}

static void write_Builtin(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Builtin");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Builtin_mem(node));
	write_builtin_kind(env, get_Builtin_kind(node));
	write_type_ref(env, get_Builtin_type(node));
	write_pin_state(env, get_irn_pinned(node));
	write_pred_refs(env, node, n_Builtin_max+1);
}

static void write_Call(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Call");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Call_mem(node));
	write_node_ref(env, get_Call_ptr(node));
	write_type_ref(env, get_Call_type(node));
	write_pin_state(env, get_irn_pinned(node));
	write_throws(env, ir_throws_exception(node));
	write_pred_refs(env, node, n_Call_max+1);
}

static void write_Cmp(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Cmp");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Cmp_left(node));
	write_node_ref(env, get_Cmp_right(node));
	write_relation(env, get_Cmp_relation(node));
}

static void write_Cond(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Cond");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Cond_selector(node));
	write_cond_jmp_predicate(env, get_Cond_jmp_pred(node));
}

static void write_Confirm(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Confirm");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Confirm_value(node));
	write_node_ref(env, get_Confirm_bound(node));
	write_relation(env, get_Confirm_relation(node));
}

static void write_Const(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Const");
	write_node_nr(env, node);
	write_tarval_ref(env, get_Const_tarval(node));
}

static void write_Conv(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Conv");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Conv_op(node));
	write_mode_ref(env, get_irn_mode(node));
}

static void write_CopyB(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "CopyB");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_CopyB_mem(node));
	write_node_ref(env, get_CopyB_dst(node));
	write_node_ref(env, get_CopyB_src(node));
	write_type_ref(env, get_CopyB_type(node));
	write_volatility(env, get_CopyB_volatility(node));
}

static void write_Div(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Div");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Div_mem(node));
	write_node_ref(env, get_Div_left(node));
	write_node_ref(env, get_Div_right(node));
	write_mode_ref(env, get_Div_resmode(node));
	write_int(env, get_Div_no_remainder(node));
	write_pin_state(env, get_irn_pinned(node));
	write_throws(env, ir_throws_exception(node));
}

static void write_Dummy(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Dummy");
	write_node_nr(env, node);
	write_mode_ref(env, get_irn_mode(node));
}

static void write_End(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "End");
	write_node_nr(env, node);
	write_pred_refs(env, node, 0);
}

static void write_Eor(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Eor");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Eor_left(node));
	write_node_ref(env, get_Eor_right(node));
}

static void write_Free(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Free");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Free_mem(node));
	write_node_ref(env, get_Free_ptr(node));
}

static void write_IJmp(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "IJmp");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_IJmp_target(node));
}

static void write_Jmp(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Jmp");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
}

static void write_Load(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Load");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Load_mem(node));
	write_node_ref(env, get_Load_ptr(node));
	write_mode_ref(env, get_Load_mode(node));
	write_type_ref(env, get_Load_type(node));
	write_volatility(env, get_Load_volatility(node));
	write_align(env, get_Load_unaligned(node));
	write_pin_state(env, get_irn_pinned(node));
	write_throws(env, ir_throws_exception(node));
}

static void write_Member(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Member");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Member_ptr(node));
	write_entity_ref(env, get_Member_entity(node));
}

static void write_Minus(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Minus");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Minus_op(node));
}

static void write_Mod(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Mod");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Mod_mem(node));
	write_node_ref(env, get_Mod_left(node));
	write_node_ref(env, get_Mod_right(node));
	write_mode_ref(env, get_Mod_resmode(node));
	write_pin_state(env, get_irn_pinned(node));
	write_throws(env, ir_throws_exception(node));
}

static void write_Mul(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Mul");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Mul_left(node));
	write_node_ref(env, get_Mul_right(node));
}

static void write_Mulh(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Mulh");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Mulh_left(node));
	write_node_ref(env, get_Mulh_right(node));
}

static void write_Mux(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Mux");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Mux_sel(node));
	write_node_ref(env, get_Mux_false(node));
	write_node_ref(env, get_Mux_true(node));
}

static void write_NoMem(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "NoMem");
	write_node_nr(env, node);
}

static void write_Not(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Not");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Not_op(node));
}

static void write_Offset(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Offset");
	write_node_nr(env, node);
	write_mode_ref(env, get_irn_mode(node));
	write_entity_ref(env, get_Offset_entity(node));
}

static void write_Or(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Or");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Or_left(node));
	write_node_ref(env, get_Or_right(node));
}

static void write_Pin(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Pin");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Pin_op(node));
}

static void write_Proj(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Proj");
	write_node_nr(env, node);
	write_node_ref(env, get_Proj_pred(node));
	write_mode_ref(env, get_irn_mode(node));
	write_unsigned(env, get_Proj_num(node));
}

static void write_Raise(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Raise");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Raise_mem(node));
	write_node_ref(env, get_Raise_exo_ptr(node));
}

static void write_Return(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Return");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Return_mem(node));
	write_pred_refs(env, node, n_Return_max+1);
}

static void write_Sel(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Sel");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Sel_ptr(node));
	write_node_ref(env, get_Sel_index(node));
	write_type_ref(env, get_Sel_type(node));
}

static void write_Shl(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Shl");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Shl_left(node));
	write_node_ref(env, get_Shl_right(node));
}

static void write_Shr(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Shr");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Shr_left(node));
	write_node_ref(env, get_Shr_right(node));
}

static void write_Shrs(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Shrs");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Shrs_left(node));
	write_node_ref(env, get_Shrs_right(node));
}

static void write_Size(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Size");
	write_node_nr(env, node);
	write_mode_ref(env, get_irn_mode(node));
	write_type_ref(env, get_Size_type(node));
}

static void write_Start(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Start");
	write_node_nr(env, node);
}

static void write_Store(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Store");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Store_mem(node));
	write_node_ref(env, get_Store_ptr(node));
	write_node_ref(env, get_Store_value(node));
	write_type_ref(env, get_Store_type(node));
	write_volatility(env, get_Store_volatility(node));
	write_align(env, get_Store_unaligned(node));
	write_pin_state(env, get_irn_pinned(node));
	write_throws(env, ir_throws_exception(node));
}

static void write_Sub(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Sub");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Sub_left(node));
	write_node_ref(env, get_Sub_right(node));
}

static void write_Switch(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Switch");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_node_ref(env, get_Switch_selector(node));
	write_unsigned(env, get_Switch_n_outs(node));
	write_switch_table_ref(env, get_Switch_table(node));
}

static void write_Sync(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Sync");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_pred_refs(env, node, 0);
}

static void write_Tuple(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Tuple");
	write_node_nr(env, node);
	write_node_ref(env, get_nodes_block(node));
	write_pred_refs(env, node, 0);
}

static void write_Unknown(write_env_t *env, const ir_node *node)
{
	write_symbol(env, "Unknown");
	write_node_nr(env, node);
	write_mode_ref(env, get_irn_mode(node));
}


void register_generated_node_readers(void)
{
	register_node_reader("Add", read_Add);
	register_node_reader("Address", read_Address);
	register_node_reader("Align", read_Align);
	register_node_reader("Alloc", read_Alloc);
	register_node_reader("And", read_And);
	register_node_reader("Bad", read_Bad);
	register_node_reader("Bitcast", read_Bitcast);
	register_node_reader("Builtin", read_Builtin);
	register_node_reader("Call", read_Call);
	register_node_reader("Cmp", read_Cmp);
	register_node_reader("Cond", read_Cond);
	register_node_reader("Confirm", read_Confirm);
	register_node_reader("Const", read_Const);
	register_node_reader("Conv", read_Conv);
	register_node_reader("CopyB", read_CopyB);
	register_node_reader("Div", read_Div);
	register_node_reader("Dummy", read_Dummy);
	register_node_reader("End", read_End);
	register_node_reader("Eor", read_Eor);
	register_node_reader("Free", read_Free);
	register_node_reader("IJmp", read_IJmp);
	register_node_reader("Jmp", read_Jmp);
	register_node_reader("Load", read_Load);
	register_node_reader("Member", read_Member);
	register_node_reader("Minus", read_Minus);
	register_node_reader("Mod", read_Mod);
	register_node_reader("Mul", read_Mul);
	register_node_reader("Mulh", read_Mulh);
	register_node_reader("Mux", read_Mux);
	register_node_reader("NoMem", read_NoMem);
	register_node_reader("Not", read_Not);
	register_node_reader("Offset", read_Offset);
	register_node_reader("Or", read_Or);
	register_node_reader("Pin", read_Pin);
	register_node_reader("Proj", read_Proj);
	register_node_reader("Raise", read_Raise);
	register_node_reader("Return", read_Return);
	register_node_reader("Sel", read_Sel);
	register_node_reader("Shl", read_Shl);
	register_node_reader("Shr", read_Shr);
	register_node_reader("Shrs", read_Shrs);
	register_node_reader("Size", read_Size);
	register_node_reader("Start", read_Start);
	register_node_reader("Store", read_Store);
	register_node_reader("Sub", read_Sub);
	register_node_reader("Switch", read_Switch);
	register_node_reader("Sync", read_Sync);
	register_node_reader("Tuple", read_Tuple);
	register_node_reader("Unknown", read_Unknown);
}

void register_generated_node_writers(void)
{
	register_node_writer(op_Add, write_Add);
	register_node_writer(op_Address, write_Address);
	register_node_writer(op_Align, write_Align);
	register_node_writer(op_Alloc, write_Alloc);
	register_node_writer(op_And, write_And);
	register_node_writer(op_Bad, write_Bad);
	register_node_writer(op_Bitcast, write_Bitcast);
	register_node_writer(op_Builtin, write_Builtin);
	register_node_writer(op_Call, write_Call);
	register_node_writer(op_Cmp, write_Cmp);
	register_node_writer(op_Cond, write_Cond);
	register_node_writer(op_Confirm, write_Confirm);
	register_node_writer(op_Const, write_Const);
	register_node_writer(op_Conv, write_Conv);
	register_node_writer(op_CopyB, write_CopyB);
	register_node_writer(op_Div, write_Div);
	register_node_writer(op_Dummy, write_Dummy);
	register_node_writer(op_End, write_End);
	register_node_writer(op_Eor, write_Eor);
	register_node_writer(op_Free, write_Free);
	register_node_writer(op_IJmp, write_IJmp);
	register_node_writer(op_Jmp, write_Jmp);
	register_node_writer(op_Load, write_Load);
	register_node_writer(op_Member, write_Member);
	register_node_writer(op_Minus, write_Minus);
	register_node_writer(op_Mod, write_Mod);
	register_node_writer(op_Mul, write_Mul);
	register_node_writer(op_Mulh, write_Mulh);
	register_node_writer(op_Mux, write_Mux);
	register_node_writer(op_NoMem, write_NoMem);
	register_node_writer(op_Not, write_Not);
	register_node_writer(op_Offset, write_Offset);
	register_node_writer(op_Or, write_Or);
	register_node_writer(op_Pin, write_Pin);
	register_node_writer(op_Proj, write_Proj);
	register_node_writer(op_Raise, write_Raise);
	register_node_writer(op_Return, write_Return);
	register_node_writer(op_Sel, write_Sel);
	register_node_writer(op_Shl, write_Shl);
	register_node_writer(op_Shr, write_Shr);
	register_node_writer(op_Shrs, write_Shrs);
	register_node_writer(op_Size, write_Size);
	register_node_writer(op_Start, write_Start);
	register_node_writer(op_Store, write_Store);
	register_node_writer(op_Sub, write_Sub);
	register_node_writer(op_Switch, write_Switch);
	register_node_writer(op_Sync, write_Sync);
	register_node_writer(op_Tuple, write_Tuple);
	register_node_writer(op_Unknown, write_Unknown);
}
