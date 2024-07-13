/* Warning: Automatically generated file */
#include <assert.h>

#include "irnode_t.h"
#include "irop_t.h"
#include "irverify_t.h"
#include "iropt_t.h"
#include "ircons_t.h"
#include "irgraph_t.h"
#include "irbackedge_t.h"
#include "irgopt.h"
#include "util.h"





ir_node *new_rd_ASM(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, int arity, ir_node *const * in, ident* text, size_t n_constraints, ir_asm_constraint* constraints, size_t n_clobbers, ident** clobbers, ir_cons_flags flags)
{
	
	ir_graph *irg = get_irn_irg(block);

	int r_arity = arity + 1;
	ir_node **r_in= ALLOCAN(ir_node*, r_arity);
	r_in[0] = irn_mem;
	MEMCPY(&r_in[1], in, arity);
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_ASM, mode_T, r_arity, r_in);
	asm_attr *attr = &res->attr.assem;
	attr->constraints = NULL;
	attr->clobbers = NULL;
	attr->text = text;
	attr->exc.pinned = flags & cons_floats ? op_pin_state_floats : op_pin_state_pinned;
	attr->exc.throws_exception = (flags & cons_throws_exception) != 0;
    struct obstack *const obst = get_irg_obstack(irg);
    attr->constraints = NEW_ARR_D(ir_asm_constraint, obst, n_constraints);
    attr->clobbers    = NEW_ARR_D(ident*,            obst, n_clobbers);

    MEMCPY(attr->constraints, constraints, n_constraints);
    MEMCPY(attr->clobbers,    clobbers,    n_clobbers);
    
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_ASM(ir_node *block, ir_node * irn_mem, int arity, ir_node *const * in, ident* text, size_t n_constraints, ir_asm_constraint* constraints, size_t n_clobbers, ident** clobbers, ir_cons_flags flags)
{
	return new_rd_ASM(NULL, block, irn_mem, arity, in, text, n_constraints, constraints, n_clobbers, clobbers, flags);
}

ir_node *new_d_ASM(dbg_info *dbgi, ir_node * irn_mem, int arity, ir_node *const * in, ident* text, size_t n_constraints, ir_asm_constraint* constraints, size_t n_clobbers, ident** clobbers, ir_cons_flags flags)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_ASM(dbgi, get_cur_block(), irn_mem, arity, in, text, n_constraints, constraints, n_clobbers, clobbers, flags);
	return res;
}

ir_node *new_ASM(ir_node * irn_mem, int arity, ir_node *const * in, ident* text, size_t n_constraints, ir_asm_constraint* constraints, size_t n_clobbers, ident** clobbers, ir_cons_flags flags)
{
	return new_d_ASM(NULL, irn_mem, arity, in, text, n_constraints, constraints, n_clobbers, clobbers, flags);
}

ir_node *(get_ASM_mem)(const ir_node *node)
{
	return get_ASM_mem(node);
}

void (set_ASM_mem)(ir_node *node, ir_node *mem)
{
	set_ASM_mem_(node, mem);
}

int (get_ASM_n_inputs)(ir_node const *node)
{
	return get_ASM_n_inputs_(node);
}

ir_node *(get_ASM_input)(ir_node const *node, int pos)
{
	return get_ASM_input_(node, pos);
}

void (set_ASM_input)(ir_node *node, int pos, ir_node *input)
{
	set_ASM_input_(node, pos, input);
}

ir_node **(get_ASM_input_arr)(ir_node *node)
{
	return get_ASM_input_arr_(node);
}
ir_op *op_ASM;
ir_op *get_op_ASM(void)
{
	return op_ASM;
}

ir_node *new_rd_Add(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_left;
	in[1] = irn_right;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Add, get_irn_mode(mode_is_reference(get_irn_mode(irn_right)) ? irn_right : irn_left), 2, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Add(ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	return new_rd_Add(NULL, block, irn_left, irn_right);
}

ir_node *new_d_Add(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Add(dbgi, get_cur_block(), irn_left, irn_right);
	return res;
}

ir_node *new_Add(ir_node * irn_left, ir_node * irn_right)
{
	return new_d_Add(NULL, irn_left, irn_right);
}

ir_node *(get_Add_left)(const ir_node *node)
{
	return get_Add_left(node);
}

void (set_Add_left)(ir_node *node, ir_node *left)
{
	set_Add_left_(node, left);
}

ir_node *(get_Add_right)(const ir_node *node)
{
	return get_Add_right(node);
}

void (set_Add_right)(ir_node *node, ir_node *right)
{
	set_Add_right_(node, right);
}
ir_op *op_Add;
ir_op *get_op_Add(void)
{
	return op_Add;
}

ir_node *new_rd_Address(dbg_info *dbgi, ir_graph *irg, ir_entity* entity)
{
	ir_node *block = get_irg_start_block(irg);
	
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Address, mode_P, 0, NULL);
	entconst_attr *attr = &res->attr.entc;
	attr->entity = entity;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Address(ir_graph *irg, ir_entity* entity)
{
	return new_rd_Address(NULL, irg, entity);
}

ir_node *new_d_Address(dbg_info *dbgi, ir_entity* entity)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Address(dbgi, current_ir_graph, entity);
	return res;
}

ir_node *new_Address(ir_entity* entity)
{
	return new_d_Address(NULL, entity);
}
ir_op *op_Address;
ir_op *get_op_Address(void)
{
	return op_Address;
}

ir_node *new_rd_Align(dbg_info *dbgi, ir_graph *irg, ir_mode * mode, ir_type* type)
{
	ir_node *block = get_irg_start_block(irg);
	
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Align, mode, 0, NULL);
	typeconst_attr *attr = &res->attr.typec;
	attr->type = type;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Align(ir_graph *irg, ir_mode * mode, ir_type* type)
{
	return new_rd_Align(NULL, irg, mode, type);
}

ir_node *new_d_Align(dbg_info *dbgi, ir_mode * mode, ir_type* type)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Align(dbgi, current_ir_graph, mode, type);
	return res;
}

ir_node *new_Align(ir_mode * mode, ir_type* type)
{
	return new_d_Align(NULL, mode, type);
}
ir_op *op_Align;
ir_op *get_op_Align(void)
{
	return op_Align;
}

ir_node *new_rd_Alloc(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_size, unsigned alignment)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_mem;
	in[1] = irn_size;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Alloc, mode_T, 2, in);
	alloc_attr *attr = &res->attr.alloc;
	attr->alignment = alignment;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Alloc(ir_node *block, ir_node * irn_mem, ir_node * irn_size, unsigned alignment)
{
	return new_rd_Alloc(NULL, block, irn_mem, irn_size, alignment);
}

ir_node *new_d_Alloc(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_size, unsigned alignment)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Alloc(dbgi, get_cur_block(), irn_mem, irn_size, alignment);
	return res;
}

ir_node *new_Alloc(ir_node * irn_mem, ir_node * irn_size, unsigned alignment)
{
	return new_d_Alloc(NULL, irn_mem, irn_size, alignment);
}

ir_node *(get_Alloc_mem)(const ir_node *node)
{
	return get_Alloc_mem(node);
}

void (set_Alloc_mem)(ir_node *node, ir_node *mem)
{
	set_Alloc_mem_(node, mem);
}

ir_node *(get_Alloc_size)(const ir_node *node)
{
	return get_Alloc_size(node);
}

void (set_Alloc_size)(ir_node *node, ir_node *size)
{
	set_Alloc_size_(node, size);
}
ir_op *op_Alloc;
ir_op *get_op_Alloc(void)
{
	return op_Alloc;
}

ir_node *(get_Anchor_end_block)(const ir_node *node)
{
	return get_Anchor_end_block(node);
}

void (set_Anchor_end_block)(ir_node *node, ir_node *end_block)
{
	set_Anchor_end_block_(node, end_block);
}

ir_node *(get_Anchor_start_block)(const ir_node *node)
{
	return get_Anchor_start_block(node);
}

void (set_Anchor_start_block)(ir_node *node, ir_node *start_block)
{
	set_Anchor_start_block_(node, start_block);
}

ir_node *(get_Anchor_end)(const ir_node *node)
{
	return get_Anchor_end(node);
}

void (set_Anchor_end)(ir_node *node, ir_node *end)
{
	set_Anchor_end_(node, end);
}

ir_node *(get_Anchor_start)(const ir_node *node)
{
	return get_Anchor_start(node);
}

void (set_Anchor_start)(ir_node *node, ir_node *start)
{
	set_Anchor_start_(node, start);
}

ir_node *(get_Anchor_frame)(const ir_node *node)
{
	return get_Anchor_frame(node);
}

void (set_Anchor_frame)(ir_node *node, ir_node *frame)
{
	set_Anchor_frame_(node, frame);
}

ir_node *(get_Anchor_initial_mem)(const ir_node *node)
{
	return get_Anchor_initial_mem(node);
}

void (set_Anchor_initial_mem)(ir_node *node, ir_node *initial_mem)
{
	set_Anchor_initial_mem_(node, initial_mem);
}

ir_node *(get_Anchor_args)(const ir_node *node)
{
	return get_Anchor_args(node);
}

void (set_Anchor_args)(ir_node *node, ir_node *args)
{
	set_Anchor_args_(node, args);
}

ir_node *(get_Anchor_no_mem)(const ir_node *node)
{
	return get_Anchor_no_mem(node);
}

void (set_Anchor_no_mem)(ir_node *node, ir_node *no_mem)
{
	set_Anchor_no_mem_(node, no_mem);
}
ir_op *op_Anchor;
ir_op *get_op_Anchor(void)
{
	return op_Anchor;
}

ir_node *new_rd_And(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_left;
	in[1] = irn_right;

	ir_node *res = new_ir_node(dbgi, irg, block, op_And, get_irn_mode(irn_left), 2, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_And(ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	return new_rd_And(NULL, block, irn_left, irn_right);
}

ir_node *new_d_And(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_And(dbgi, get_cur_block(), irn_left, irn_right);
	return res;
}

ir_node *new_And(ir_node * irn_left, ir_node * irn_right)
{
	return new_d_And(NULL, irn_left, irn_right);
}

ir_node *(get_And_left)(const ir_node *node)
{
	return get_And_left(node);
}

void (set_And_left)(ir_node *node, ir_node *left)
{
	set_And_left_(node, left);
}

ir_node *(get_And_right)(const ir_node *node)
{
	return get_And_right(node);
}

void (set_And_right)(ir_node *node, ir_node *right)
{
	set_And_right_(node, right);
}
ir_op *op_And;
ir_op *get_op_And(void)
{
	return op_And;
}

ir_node *new_rd_Bad(dbg_info *dbgi, ir_graph *irg, ir_mode * mode)
{
	ir_node *block = get_irg_start_block(irg);
	
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Bad, mode, 0, NULL);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Bad(ir_graph *irg, ir_mode * mode)
{
	return new_rd_Bad(NULL, irg, mode);
}

ir_node *new_d_Bad(dbg_info *dbgi, ir_mode * mode)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Bad(dbgi, current_ir_graph, mode);
	return res;
}

ir_node *new_Bad(ir_mode * mode)
{
	return new_d_Bad(NULL, mode);
}
ir_op *op_Bad;
ir_op *get_op_Bad(void)
{
	return op_Bad;
}

ir_node *new_rd_Bitcast(dbg_info *dbgi, ir_node *block, ir_node * irn_op, ir_mode * mode)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[1];
	in[0] = irn_op;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Bitcast, mode, 1, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Bitcast(ir_node *block, ir_node * irn_op, ir_mode * mode)
{
	return new_rd_Bitcast(NULL, block, irn_op, mode);
}

ir_node *new_d_Bitcast(dbg_info *dbgi, ir_node * irn_op, ir_mode * mode)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Bitcast(dbgi, get_cur_block(), irn_op, mode);
	return res;
}

ir_node *new_Bitcast(ir_node * irn_op, ir_mode * mode)
{
	return new_d_Bitcast(NULL, irn_op, mode);
}

ir_node *(get_Bitcast_op)(const ir_node *node)
{
	return get_Bitcast_op(node);
}

void (set_Bitcast_op)(ir_node *node, ir_node *op)
{
	set_Bitcast_op_(node, op);
}
ir_op *op_Bitcast;
ir_op *get_op_Bitcast(void)
{
	return op_Bitcast;
}

ir_node *new_rd_Block(dbg_info *dbgi, ir_graph *irg, int arity, ir_node *const * in)
{
	ir_node *block = NULL;
	
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Block, mode_BB, arity, in);
	block_attr *attr = &res->attr.block;
	attr->entity = NULL;
    res->attr.block.backedge = new_backedge_arr(get_irg_obstack(irg), arity);
    set_Block_matured(res, 1);

    /* Create and initialize array for Phi-node construction. */
    if (irg_is_constrained(irg, IR_GRAPH_CONSTRAINT_CONSTRUCTION)) {
        res->attr.block.graph_arr = NEW_ARR_DZ(ir_node*, get_irg_obstack(irg), irg->n_loc);
    }
    
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Block(ir_graph *irg, int arity, ir_node *const * in)
{
	return new_rd_Block(NULL, irg, arity, in);
}

ir_node *new_d_Block(dbg_info *dbgi, int arity, ir_node *const * in)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Block(dbgi, current_ir_graph, arity, in);
	return res;
}

ir_node *new_Block(int arity, ir_node *const * in)
{
	return new_d_Block(NULL, arity, in);
}

int (get_Block_n_cfgpreds)(ir_node const *node)
{
	return get_Block_n_cfgpreds_(node);
}

ir_node *(get_Block_cfgpred)(ir_node const *node, int pos)
{
	return get_Block_cfgpred_(node, pos);
}

void (set_Block_cfgpred)(ir_node *node, int pos, ir_node *cfgpred)
{
	set_Block_cfgpred_(node, pos, cfgpred);
}

ir_node **(get_Block_cfgpred_arr)(ir_node *node)
{
	return get_Block_cfgpred_arr_(node);
}
ir_op *op_Block;
ir_op *get_op_Block(void)
{
	return op_Block;
}

ir_node *new_rd_Builtin(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, int arity, ir_node *const * in, ir_builtin_kind kind, ir_type* type)
{
	
	ir_graph *irg = get_irn_irg(block);

	int r_arity = arity + 1;
	ir_node **r_in= ALLOCAN(ir_node*, r_arity);
	r_in[0] = irn_mem;
	MEMCPY(&r_in[1], in, arity);
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Builtin, mode_T, r_arity, r_in);
	builtin_attr *attr = &res->attr.builtin;
	attr->kind = kind;
	attr->type = type;
	attr->exc.pinned = op_pin_state_pinned;
    assert((get_unknown_type() == type) || is_Method_type(type));
    
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Builtin(ir_node *block, ir_node * irn_mem, int arity, ir_node *const * in, ir_builtin_kind kind, ir_type* type)
{
	return new_rd_Builtin(NULL, block, irn_mem, arity, in, kind, type);
}

ir_node *new_d_Builtin(dbg_info *dbgi, ir_node * irn_mem, int arity, ir_node *const * in, ir_builtin_kind kind, ir_type* type)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Builtin(dbgi, get_cur_block(), irn_mem, arity, in, kind, type);
	return res;
}

ir_node *new_Builtin(ir_node * irn_mem, int arity, ir_node *const * in, ir_builtin_kind kind, ir_type* type)
{
	return new_d_Builtin(NULL, irn_mem, arity, in, kind, type);
}

ir_node *(get_Builtin_mem)(const ir_node *node)
{
	return get_Builtin_mem(node);
}

void (set_Builtin_mem)(ir_node *node, ir_node *mem)
{
	set_Builtin_mem_(node, mem);
}

int (get_Builtin_n_params)(ir_node const *node)
{
	return get_Builtin_n_params_(node);
}

ir_node *(get_Builtin_param)(ir_node const *node, int pos)
{
	return get_Builtin_param_(node, pos);
}

void (set_Builtin_param)(ir_node *node, int pos, ir_node *param)
{
	set_Builtin_param_(node, pos, param);
}

ir_node **(get_Builtin_param_arr)(ir_node *node)
{
	return get_Builtin_param_arr_(node);
}
ir_op *op_Builtin;
ir_op *get_op_Builtin(void)
{
	return op_Builtin;
}

ir_node *new_rd_Call(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_ptr, int arity, ir_node *const * in, ir_type* type)
{
	
	ir_graph *irg = get_irn_irg(block);

	int r_arity = arity + 2;
	ir_node **r_in= ALLOCAN(ir_node*, r_arity);
	r_in[0] = irn_mem;
	r_in[1] = irn_ptr;
	MEMCPY(&r_in[2], in, arity);
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Call, mode_T, r_arity, r_in);
	call_attr *attr = &res->attr.call;
	attr->type = type;
	attr->exc.pinned = op_pin_state_pinned;
	attr->exc.throws_exception = false;
    assert((get_unknown_type() == type) || is_Method_type(type));
    
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Call(ir_node *block, ir_node * irn_mem, ir_node * irn_ptr, int arity, ir_node *const * in, ir_type* type)
{
	return new_rd_Call(NULL, block, irn_mem, irn_ptr, arity, in, type);
}

ir_node *new_d_Call(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_ptr, int arity, ir_node *const * in, ir_type* type)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Call(dbgi, get_cur_block(), irn_mem, irn_ptr, arity, in, type);
	return res;
}

ir_node *new_Call(ir_node * irn_mem, ir_node * irn_ptr, int arity, ir_node *const * in, ir_type* type)
{
	return new_d_Call(NULL, irn_mem, irn_ptr, arity, in, type);
}

ir_node *(get_Call_mem)(const ir_node *node)
{
	return get_Call_mem(node);
}

void (set_Call_mem)(ir_node *node, ir_node *mem)
{
	set_Call_mem_(node, mem);
}

ir_node *(get_Call_ptr)(const ir_node *node)
{
	return get_Call_ptr(node);
}

void (set_Call_ptr)(ir_node *node, ir_node *ptr)
{
	set_Call_ptr_(node, ptr);
}

int (get_Call_n_params)(ir_node const *node)
{
	return get_Call_n_params_(node);
}

ir_node *(get_Call_param)(ir_node const *node, int pos)
{
	return get_Call_param_(node, pos);
}

void (set_Call_param)(ir_node *node, int pos, ir_node *param)
{
	set_Call_param_(node, pos, param);
}

ir_node **(get_Call_param_arr)(ir_node *node)
{
	return get_Call_param_arr_(node);
}
ir_op *op_Call;
ir_op *get_op_Call(void)
{
	return op_Call;
}

ir_node *new_rd_Cmp(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right, ir_relation relation)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_left;
	in[1] = irn_right;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Cmp, mode_b, 2, in);
	cmp_attr *attr = &res->attr.cmp;
	attr->relation = relation;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Cmp(ir_node *block, ir_node * irn_left, ir_node * irn_right, ir_relation relation)
{
	return new_rd_Cmp(NULL, block, irn_left, irn_right, relation);
}

ir_node *new_d_Cmp(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right, ir_relation relation)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Cmp(dbgi, get_cur_block(), irn_left, irn_right, relation);
	return res;
}

ir_node *new_Cmp(ir_node * irn_left, ir_node * irn_right, ir_relation relation)
{
	return new_d_Cmp(NULL, irn_left, irn_right, relation);
}

ir_node *(get_Cmp_left)(const ir_node *node)
{
	return get_Cmp_left(node);
}

void (set_Cmp_left)(ir_node *node, ir_node *left)
{
	set_Cmp_left_(node, left);
}

ir_node *(get_Cmp_right)(const ir_node *node)
{
	return get_Cmp_right(node);
}

void (set_Cmp_right)(ir_node *node, ir_node *right)
{
	set_Cmp_right_(node, right);
}
ir_op *op_Cmp;
ir_op *get_op_Cmp(void)
{
	return op_Cmp;
}

ir_node *new_rd_Cond(dbg_info *dbgi, ir_node *block, ir_node * irn_selector)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[1];
	in[0] = irn_selector;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Cond, mode_T, 1, in);
	cond_attr *attr = &res->attr.cond;
	attr->jmp_pred = COND_JMP_PRED_NONE;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Cond(ir_node *block, ir_node * irn_selector)
{
	return new_rd_Cond(NULL, block, irn_selector);
}

ir_node *new_d_Cond(dbg_info *dbgi, ir_node * irn_selector)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Cond(dbgi, get_cur_block(), irn_selector);
	return res;
}

ir_node *new_Cond(ir_node * irn_selector)
{
	return new_d_Cond(NULL, irn_selector);
}

ir_node *(get_Cond_selector)(const ir_node *node)
{
	return get_Cond_selector(node);
}

void (set_Cond_selector)(ir_node *node, ir_node *selector)
{
	set_Cond_selector_(node, selector);
}
ir_op *op_Cond;
ir_op *get_op_Cond(void)
{
	return op_Cond;
}

ir_node *new_rd_Confirm(dbg_info *dbgi, ir_node *block, ir_node * irn_value, ir_node * irn_bound, ir_relation relation)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_value;
	in[1] = irn_bound;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Confirm, get_irn_mode(irn_value), 2, in);
	confirm_attr *attr = &res->attr.confirm;
	attr->relation = relation;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Confirm(ir_node *block, ir_node * irn_value, ir_node * irn_bound, ir_relation relation)
{
	return new_rd_Confirm(NULL, block, irn_value, irn_bound, relation);
}

ir_node *new_d_Confirm(dbg_info *dbgi, ir_node * irn_value, ir_node * irn_bound, ir_relation relation)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Confirm(dbgi, get_cur_block(), irn_value, irn_bound, relation);
	return res;
}

ir_node *new_Confirm(ir_node * irn_value, ir_node * irn_bound, ir_relation relation)
{
	return new_d_Confirm(NULL, irn_value, irn_bound, relation);
}

ir_node *(get_Confirm_value)(const ir_node *node)
{
	return get_Confirm_value(node);
}

void (set_Confirm_value)(ir_node *node, ir_node *value)
{
	set_Confirm_value_(node, value);
}

ir_node *(get_Confirm_bound)(const ir_node *node)
{
	return get_Confirm_bound(node);
}

void (set_Confirm_bound)(ir_node *node, ir_node *bound)
{
	set_Confirm_bound_(node, bound);
}
ir_op *op_Confirm;
ir_op *get_op_Confirm(void)
{
	return op_Confirm;
}

ir_node *new_rd_Const(dbg_info *dbgi, ir_graph *irg, ir_tarval* tarval)
{
	ir_node *block = get_irg_start_block(irg);
	
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Const, get_tarval_mode(tarval), 0, NULL);
	const_attr *attr = &res->attr.con;
	attr->tarval = tarval;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Const(ir_graph *irg, ir_tarval* tarval)
{
	return new_rd_Const(NULL, irg, tarval);
}

ir_node *new_d_Const(dbg_info *dbgi, ir_tarval* tarval)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Const(dbgi, current_ir_graph, tarval);
	return res;
}

ir_node *new_Const(ir_tarval* tarval)
{
	return new_d_Const(NULL, tarval);
}
ir_op *op_Const;
ir_op *get_op_Const(void)
{
	return op_Const;
}

ir_node *new_rd_Conv(dbg_info *dbgi, ir_node *block, ir_node * irn_op, ir_mode * mode)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[1];
	in[0] = irn_op;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Conv, mode, 1, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Conv(ir_node *block, ir_node * irn_op, ir_mode * mode)
{
	return new_rd_Conv(NULL, block, irn_op, mode);
}

ir_node *new_d_Conv(dbg_info *dbgi, ir_node * irn_op, ir_mode * mode)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Conv(dbgi, get_cur_block(), irn_op, mode);
	return res;
}

ir_node *new_Conv(ir_node * irn_op, ir_mode * mode)
{
	return new_d_Conv(NULL, irn_op, mode);
}

ir_node *(get_Conv_op)(const ir_node *node)
{
	return get_Conv_op(node);
}

void (set_Conv_op)(ir_node *node, ir_node *op)
{
	set_Conv_op_(node, op);
}
ir_op *op_Conv;
ir_op *get_op_Conv(void)
{
	return op_Conv;
}

ir_node *new_rd_CopyB(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_dst, ir_node * irn_src, ir_type* type, ir_cons_flags flags)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[3];
	in[0] = irn_mem;
	in[1] = irn_dst;
	in[2] = irn_src;

	ir_node *res = new_ir_node(dbgi, irg, block, op_CopyB, mode_M, 3, in);
	copyb_attr *attr = &res->attr.copyb;
	attr->type = type;
	attr->volatility = flags & cons_volatile ? volatility_is_volatile : volatility_non_volatile;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_CopyB(ir_node *block, ir_node * irn_mem, ir_node * irn_dst, ir_node * irn_src, ir_type* type, ir_cons_flags flags)
{
	return new_rd_CopyB(NULL, block, irn_mem, irn_dst, irn_src, type, flags);
}

ir_node *new_d_CopyB(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_dst, ir_node * irn_src, ir_type* type, ir_cons_flags flags)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_CopyB(dbgi, get_cur_block(), irn_mem, irn_dst, irn_src, type, flags);
	return res;
}

ir_node *new_CopyB(ir_node * irn_mem, ir_node * irn_dst, ir_node * irn_src, ir_type* type, ir_cons_flags flags)
{
	return new_d_CopyB(NULL, irn_mem, irn_dst, irn_src, type, flags);
}

ir_node *(get_CopyB_mem)(const ir_node *node)
{
	return get_CopyB_mem(node);
}

void (set_CopyB_mem)(ir_node *node, ir_node *mem)
{
	set_CopyB_mem_(node, mem);
}

ir_node *(get_CopyB_dst)(const ir_node *node)
{
	return get_CopyB_dst(node);
}

void (set_CopyB_dst)(ir_node *node, ir_node *dst)
{
	set_CopyB_dst_(node, dst);
}

ir_node *(get_CopyB_src)(const ir_node *node)
{
	return get_CopyB_src(node);
}

void (set_CopyB_src)(ir_node *node, ir_node *src)
{
	set_CopyB_src_(node, src);
}
ir_op *op_CopyB;
ir_op *get_op_CopyB(void)
{
	return op_CopyB;
}
ir_op *op_Deleted;
ir_op *get_op_Deleted(void)
{
	return op_Deleted;
}

ir_node *new_rd_Div(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[3];
	in[0] = irn_mem;
	in[1] = irn_left;
	in[2] = irn_right;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Div, mode_T, 3, in);
	div_attr *attr = &res->attr.div;
	attr->resmode = get_irn_mode(irn_left);
	attr->no_remainder = 0;
	attr->exc.pinned = pinned;
	attr->exc.throws_exception = false;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Div(ir_node *block, ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned)
{
	return new_rd_Div(NULL, block, irn_mem, irn_left, irn_right, pinned);
}

ir_node *new_d_Div(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Div(dbgi, get_cur_block(), irn_mem, irn_left, irn_right, pinned);
	return res;
}

ir_node *new_Div(ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned)
{
	return new_d_Div(NULL, irn_mem, irn_left, irn_right, pinned);
}

ir_node *(get_Div_mem)(const ir_node *node)
{
	return get_Div_mem(node);
}

void (set_Div_mem)(ir_node *node, ir_node *mem)
{
	set_Div_mem_(node, mem);
}

ir_node *(get_Div_left)(const ir_node *node)
{
	return get_Div_left(node);
}

void (set_Div_left)(ir_node *node, ir_node *left)
{
	set_Div_left_(node, left);
}

ir_node *(get_Div_right)(const ir_node *node)
{
	return get_Div_right(node);
}

void (set_Div_right)(ir_node *node, ir_node *right)
{
	set_Div_right_(node, right);
}
ir_op *op_Div;
ir_op *get_op_Div(void)
{
	return op_Div;
}

ir_node *new_rd_Dummy(dbg_info *dbgi, ir_graph *irg, ir_mode * mode)
{
	ir_node *block = get_irg_start_block(irg);
	
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Dummy, mode, 0, NULL);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Dummy(ir_graph *irg, ir_mode * mode)
{
	return new_rd_Dummy(NULL, irg, mode);
}

ir_node *new_d_Dummy(dbg_info *dbgi, ir_mode * mode)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Dummy(dbgi, current_ir_graph, mode);
	return res;
}

ir_node *new_Dummy(ir_mode * mode)
{
	return new_d_Dummy(NULL, mode);
}
ir_op *op_Dummy;
ir_op *get_op_Dummy(void)
{
	return op_Dummy;
}

ir_node *new_rd_End(dbg_info *dbgi, ir_graph *irg, int arity, ir_node *const * in)
{
	ir_node *block = get_irg_end_block(irg);
	
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_End, mode_X, arity, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_End(ir_graph *irg, int arity, ir_node *const * in)
{
	return new_rd_End(NULL, irg, arity, in);
}

ir_node *new_d_End(dbg_info *dbgi, int arity, ir_node *const * in)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_End(dbgi, current_ir_graph, arity, in);
	return res;
}

ir_node *new_End(int arity, ir_node *const * in)
{
	return new_d_End(NULL, arity, in);
}

int (get_End_n_keepalives)(ir_node const *node)
{
	return get_End_n_keepalives_(node);
}

ir_node *(get_End_keepalive)(ir_node const *node, int pos)
{
	return get_End_keepalive_(node, pos);
}

void (set_End_keepalive)(ir_node *node, int pos, ir_node *keepalive)
{
	set_End_keepalive_(node, pos, keepalive);
}

ir_node **(get_End_keepalive_arr)(ir_node *node)
{
	return get_End_keepalive_arr_(node);
}
ir_op *op_End;
ir_op *get_op_End(void)
{
	return op_End;
}

ir_node *new_rd_Eor(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_left;
	in[1] = irn_right;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Eor, get_irn_mode(irn_left), 2, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Eor(ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	return new_rd_Eor(NULL, block, irn_left, irn_right);
}

ir_node *new_d_Eor(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Eor(dbgi, get_cur_block(), irn_left, irn_right);
	return res;
}

ir_node *new_Eor(ir_node * irn_left, ir_node * irn_right)
{
	return new_d_Eor(NULL, irn_left, irn_right);
}

ir_node *(get_Eor_left)(const ir_node *node)
{
	return get_Eor_left(node);
}

void (set_Eor_left)(ir_node *node, ir_node *left)
{
	set_Eor_left_(node, left);
}

ir_node *(get_Eor_right)(const ir_node *node)
{
	return get_Eor_right(node);
}

void (set_Eor_right)(ir_node *node, ir_node *right)
{
	set_Eor_right_(node, right);
}
ir_op *op_Eor;
ir_op *get_op_Eor(void)
{
	return op_Eor;
}

ir_node *new_rd_Free(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_ptr)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_mem;
	in[1] = irn_ptr;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Free, mode_M, 2, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Free(ir_node *block, ir_node * irn_mem, ir_node * irn_ptr)
{
	return new_rd_Free(NULL, block, irn_mem, irn_ptr);
}

ir_node *new_d_Free(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_ptr)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Free(dbgi, get_cur_block(), irn_mem, irn_ptr);
	return res;
}

ir_node *new_Free(ir_node * irn_mem, ir_node * irn_ptr)
{
	return new_d_Free(NULL, irn_mem, irn_ptr);
}

ir_node *(get_Free_mem)(const ir_node *node)
{
	return get_Free_mem(node);
}

void (set_Free_mem)(ir_node *node, ir_node *mem)
{
	set_Free_mem_(node, mem);
}

ir_node *(get_Free_ptr)(const ir_node *node)
{
	return get_Free_ptr(node);
}

void (set_Free_ptr)(ir_node *node, ir_node *ptr)
{
	set_Free_ptr_(node, ptr);
}
ir_op *op_Free;
ir_op *get_op_Free(void)
{
	return op_Free;
}

ir_node *new_rd_IJmp(dbg_info *dbgi, ir_node *block, ir_node * irn_target)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[1];
	in[0] = irn_target;

	ir_node *res = new_ir_node(dbgi, irg, block, op_IJmp, mode_X, 1, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_IJmp(ir_node *block, ir_node * irn_target)
{
	return new_rd_IJmp(NULL, block, irn_target);
}

ir_node *new_d_IJmp(dbg_info *dbgi, ir_node * irn_target)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_IJmp(dbgi, get_cur_block(), irn_target);
	return res;
}

ir_node *new_IJmp(ir_node * irn_target)
{
	return new_d_IJmp(NULL, irn_target);
}

ir_node *(get_IJmp_target)(const ir_node *node)
{
	return get_IJmp_target(node);
}

void (set_IJmp_target)(ir_node *node, ir_node *target)
{
	set_IJmp_target_(node, target);
}
ir_op *op_IJmp;
ir_op *get_op_IJmp(void)
{
	return op_IJmp;
}

ir_node *(get_Id_pred)(const ir_node *node)
{
	return get_Id_pred(node);
}

void (set_Id_pred)(ir_node *node, ir_node *pred)
{
	set_Id_pred_(node, pred);
}
ir_op *op_Id;
ir_op *get_op_Id(void)
{
	return op_Id;
}

ir_node *new_rd_Jmp(dbg_info *dbgi, ir_node *block)
{
	
	ir_graph *irg = get_irn_irg(block);

	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Jmp, mode_X, 0, NULL);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Jmp(ir_node *block)
{
	return new_rd_Jmp(NULL, block);
}

ir_node *new_d_Jmp(dbg_info *dbgi)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Jmp(dbgi, get_cur_block());
	return res;
}

ir_node *new_Jmp(void)
{
	return new_d_Jmp(NULL);
}
ir_op *op_Jmp;
ir_op *get_op_Jmp(void)
{
	return op_Jmp;
}

ir_node *new_rd_Load(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_ptr, ir_mode* mode, ir_type* type, ir_cons_flags flags)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_mem;
	in[1] = irn_ptr;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Load, mode_T, 2, in);
	load_attr *attr = &res->attr.load;
	attr->mode = mode;
	attr->type = type;
	attr->volatility = flags & cons_volatile ? volatility_is_volatile : volatility_non_volatile;
	attr->unaligned = flags & cons_unaligned ? align_non_aligned : align_is_aligned;
	attr->exc.pinned = flags & cons_floats ? op_pin_state_floats : op_pin_state_pinned;
	attr->exc.throws_exception = (flags & cons_throws_exception) != 0;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Load(ir_node *block, ir_node * irn_mem, ir_node * irn_ptr, ir_mode* mode, ir_type* type, ir_cons_flags flags)
{
	return new_rd_Load(NULL, block, irn_mem, irn_ptr, mode, type, flags);
}

ir_node *new_d_Load(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_ptr, ir_mode* mode, ir_type* type, ir_cons_flags flags)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Load(dbgi, get_cur_block(), irn_mem, irn_ptr, mode, type, flags);
	return res;
}

ir_node *new_Load(ir_node * irn_mem, ir_node * irn_ptr, ir_mode* mode, ir_type* type, ir_cons_flags flags)
{
	return new_d_Load(NULL, irn_mem, irn_ptr, mode, type, flags);
}

ir_node *(get_Load_mem)(const ir_node *node)
{
	return get_Load_mem(node);
}

void (set_Load_mem)(ir_node *node, ir_node *mem)
{
	set_Load_mem_(node, mem);
}

ir_node *(get_Load_ptr)(const ir_node *node)
{
	return get_Load_ptr(node);
}

void (set_Load_ptr)(ir_node *node, ir_node *ptr)
{
	set_Load_ptr_(node, ptr);
}
ir_op *op_Load;
ir_op *get_op_Load(void)
{
	return op_Load;
}

ir_node *new_rd_Member(dbg_info *dbgi, ir_node *block, ir_node * irn_ptr, ir_entity* entity)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[1];
	in[0] = irn_ptr;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Member, mode_P, 1, in);
	member_attr *attr = &res->attr.member;
	attr->entity = entity;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Member(ir_node *block, ir_node * irn_ptr, ir_entity* entity)
{
	return new_rd_Member(NULL, block, irn_ptr, entity);
}

ir_node *new_d_Member(dbg_info *dbgi, ir_node * irn_ptr, ir_entity* entity)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Member(dbgi, get_cur_block(), irn_ptr, entity);
	return res;
}

ir_node *new_Member(ir_node * irn_ptr, ir_entity* entity)
{
	return new_d_Member(NULL, irn_ptr, entity);
}

ir_node *(get_Member_ptr)(const ir_node *node)
{
	return get_Member_ptr(node);
}

void (set_Member_ptr)(ir_node *node, ir_node *ptr)
{
	set_Member_ptr_(node, ptr);
}
ir_op *op_Member;
ir_op *get_op_Member(void)
{
	return op_Member;
}

ir_node *new_rd_Minus(dbg_info *dbgi, ir_node *block, ir_node * irn_op)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[1];
	in[0] = irn_op;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Minus, get_irn_mode(irn_op), 1, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Minus(ir_node *block, ir_node * irn_op)
{
	return new_rd_Minus(NULL, block, irn_op);
}

ir_node *new_d_Minus(dbg_info *dbgi, ir_node * irn_op)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Minus(dbgi, get_cur_block(), irn_op);
	return res;
}

ir_node *new_Minus(ir_node * irn_op)
{
	return new_d_Minus(NULL, irn_op);
}

ir_node *(get_Minus_op)(const ir_node *node)
{
	return get_Minus_op(node);
}

void (set_Minus_op)(ir_node *node, ir_node *op)
{
	set_Minus_op_(node, op);
}
ir_op *op_Minus;
ir_op *get_op_Minus(void)
{
	return op_Minus;
}

ir_node *new_rd_Mod(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[3];
	in[0] = irn_mem;
	in[1] = irn_left;
	in[2] = irn_right;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Mod, mode_T, 3, in);
	mod_attr *attr = &res->attr.mod;
	attr->resmode = get_irn_mode(irn_left);
	attr->exc.pinned = pinned;
	attr->exc.throws_exception = false;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Mod(ir_node *block, ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned)
{
	return new_rd_Mod(NULL, block, irn_mem, irn_left, irn_right, pinned);
}

ir_node *new_d_Mod(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Mod(dbgi, get_cur_block(), irn_mem, irn_left, irn_right, pinned);
	return res;
}

ir_node *new_Mod(ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned)
{
	return new_d_Mod(NULL, irn_mem, irn_left, irn_right, pinned);
}

ir_node *(get_Mod_mem)(const ir_node *node)
{
	return get_Mod_mem(node);
}

void (set_Mod_mem)(ir_node *node, ir_node *mem)
{
	set_Mod_mem_(node, mem);
}

ir_node *(get_Mod_left)(const ir_node *node)
{
	return get_Mod_left(node);
}

void (set_Mod_left)(ir_node *node, ir_node *left)
{
	set_Mod_left_(node, left);
}

ir_node *(get_Mod_right)(const ir_node *node)
{
	return get_Mod_right(node);
}

void (set_Mod_right)(ir_node *node, ir_node *right)
{
	set_Mod_right_(node, right);
}
ir_op *op_Mod;
ir_op *get_op_Mod(void)
{
	return op_Mod;
}

ir_node *new_rd_Mul(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_left;
	in[1] = irn_right;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Mul, get_irn_mode(irn_left), 2, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Mul(ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	return new_rd_Mul(NULL, block, irn_left, irn_right);
}

ir_node *new_d_Mul(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Mul(dbgi, get_cur_block(), irn_left, irn_right);
	return res;
}

ir_node *new_Mul(ir_node * irn_left, ir_node * irn_right)
{
	return new_d_Mul(NULL, irn_left, irn_right);
}

ir_node *(get_Mul_left)(const ir_node *node)
{
	return get_Mul_left(node);
}

void (set_Mul_left)(ir_node *node, ir_node *left)
{
	set_Mul_left_(node, left);
}

ir_node *(get_Mul_right)(const ir_node *node)
{
	return get_Mul_right(node);
}

void (set_Mul_right)(ir_node *node, ir_node *right)
{
	set_Mul_right_(node, right);
}
ir_op *op_Mul;
ir_op *get_op_Mul(void)
{
	return op_Mul;
}

ir_node *new_rd_Mulh(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_left;
	in[1] = irn_right;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Mulh, get_irn_mode(irn_left), 2, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Mulh(ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	return new_rd_Mulh(NULL, block, irn_left, irn_right);
}

ir_node *new_d_Mulh(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Mulh(dbgi, get_cur_block(), irn_left, irn_right);
	return res;
}

ir_node *new_Mulh(ir_node * irn_left, ir_node * irn_right)
{
	return new_d_Mulh(NULL, irn_left, irn_right);
}

ir_node *(get_Mulh_left)(const ir_node *node)
{
	return get_Mulh_left(node);
}

void (set_Mulh_left)(ir_node *node, ir_node *left)
{
	set_Mulh_left_(node, left);
}

ir_node *(get_Mulh_right)(const ir_node *node)
{
	return get_Mulh_right(node);
}

void (set_Mulh_right)(ir_node *node, ir_node *right)
{
	set_Mulh_right_(node, right);
}
ir_op *op_Mulh;
ir_op *get_op_Mulh(void)
{
	return op_Mulh;
}

ir_node *new_rd_Mux(dbg_info *dbgi, ir_node *block, ir_node * irn_sel, ir_node * irn_false, ir_node * irn_true)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[3];
	in[0] = irn_sel;
	in[1] = irn_false;
	in[2] = irn_true;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Mux, get_irn_mode(irn_false), 3, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Mux(ir_node *block, ir_node * irn_sel, ir_node * irn_false, ir_node * irn_true)
{
	return new_rd_Mux(NULL, block, irn_sel, irn_false, irn_true);
}

ir_node *new_d_Mux(dbg_info *dbgi, ir_node * irn_sel, ir_node * irn_false, ir_node * irn_true)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Mux(dbgi, get_cur_block(), irn_sel, irn_false, irn_true);
	return res;
}

ir_node *new_Mux(ir_node * irn_sel, ir_node * irn_false, ir_node * irn_true)
{
	return new_d_Mux(NULL, irn_sel, irn_false, irn_true);
}

ir_node *(get_Mux_sel)(const ir_node *node)
{
	return get_Mux_sel(node);
}

void (set_Mux_sel)(ir_node *node, ir_node *sel)
{
	set_Mux_sel_(node, sel);
}

ir_node *(get_Mux_false)(const ir_node *node)
{
	return get_Mux_false(node);
}

void (set_Mux_false)(ir_node *node, ir_node *false_)
{
	set_Mux_false_(node, false_);
}

ir_node *(get_Mux_true)(const ir_node *node)
{
	return get_Mux_true(node);
}

void (set_Mux_true)(ir_node *node, ir_node *true_)
{
	set_Mux_true_(node, true_);
}
ir_op *op_Mux;
ir_op *get_op_Mux(void)
{
	return op_Mux;
}

ir_node *new_rd_NoMem(dbg_info *dbgi, ir_graph *irg)
{
	ir_node *block = get_irg_start_block(irg);
	
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_NoMem, mode_M, 0, NULL);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_NoMem(ir_graph *irg)
{
	return new_rd_NoMem(NULL, irg);
}

ir_node *new_d_NoMem(dbg_info *dbgi)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_NoMem(dbgi, current_ir_graph);
	return res;
}

ir_node *new_NoMem(void)
{
	return new_d_NoMem(NULL);
}
ir_op *op_NoMem;
ir_op *get_op_NoMem(void)
{
	return op_NoMem;
}

ir_node *new_rd_Not(dbg_info *dbgi, ir_node *block, ir_node * irn_op)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[1];
	in[0] = irn_op;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Not, get_irn_mode(irn_op), 1, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Not(ir_node *block, ir_node * irn_op)
{
	return new_rd_Not(NULL, block, irn_op);
}

ir_node *new_d_Not(dbg_info *dbgi, ir_node * irn_op)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Not(dbgi, get_cur_block(), irn_op);
	return res;
}

ir_node *new_Not(ir_node * irn_op)
{
	return new_d_Not(NULL, irn_op);
}

ir_node *(get_Not_op)(const ir_node *node)
{
	return get_Not_op(node);
}

void (set_Not_op)(ir_node *node, ir_node *op)
{
	set_Not_op_(node, op);
}
ir_op *op_Not;
ir_op *get_op_Not(void)
{
	return op_Not;
}

ir_node *new_rd_Offset(dbg_info *dbgi, ir_graph *irg, ir_mode * mode, ir_entity* entity)
{
	ir_node *block = get_irg_start_block(irg);
	
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Offset, mode, 0, NULL);
	entconst_attr *attr = &res->attr.entc;
	attr->entity = entity;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Offset(ir_graph *irg, ir_mode * mode, ir_entity* entity)
{
	return new_rd_Offset(NULL, irg, mode, entity);
}

ir_node *new_d_Offset(dbg_info *dbgi, ir_mode * mode, ir_entity* entity)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Offset(dbgi, current_ir_graph, mode, entity);
	return res;
}

ir_node *new_Offset(ir_mode * mode, ir_entity* entity)
{
	return new_d_Offset(NULL, mode, entity);
}
ir_op *op_Offset;
ir_op *get_op_Offset(void)
{
	return op_Offset;
}

ir_node *new_rd_Or(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_left;
	in[1] = irn_right;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Or, get_irn_mode(irn_left), 2, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Or(ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	return new_rd_Or(NULL, block, irn_left, irn_right);
}

ir_node *new_d_Or(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Or(dbgi, get_cur_block(), irn_left, irn_right);
	return res;
}

ir_node *new_Or(ir_node * irn_left, ir_node * irn_right)
{
	return new_d_Or(NULL, irn_left, irn_right);
}

ir_node *(get_Or_left)(const ir_node *node)
{
	return get_Or_left(node);
}

void (set_Or_left)(ir_node *node, ir_node *left)
{
	set_Or_left_(node, left);
}

ir_node *(get_Or_right)(const ir_node *node)
{
	return get_Or_right(node);
}

void (set_Or_right)(ir_node *node, ir_node *right)
{
	set_Or_right_(node, right);
}
ir_op *op_Or;
ir_op *get_op_Or(void)
{
	return op_Or;
}

ir_node *new_rd_Phi(dbg_info *dbgi, ir_node *block, int arity, ir_node *const * in, ir_mode * mode)
{
	
	ir_graph *irg = get_irn_irg(block);

	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Phi, mode, arity, in);
	phi_attr *attr = &res->attr.phi;
	attr->loop = 0;
    res->attr.phi.u.backedge = new_backedge_arr(get_irg_obstack(irg), arity);
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Phi(ir_node *block, int arity, ir_node *const * in, ir_mode * mode)
{
	return new_rd_Phi(NULL, block, arity, in, mode);
}

ir_node *new_d_Phi(dbg_info *dbgi, int arity, ir_node *const * in, ir_mode * mode)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Phi(dbgi, get_cur_block(), arity, in, mode);
	return res;
}

ir_node *new_Phi(int arity, ir_node *const * in, ir_mode * mode)
{
	return new_d_Phi(NULL, arity, in, mode);
}

int (get_Phi_n_preds)(ir_node const *node)
{
	return get_Phi_n_preds_(node);
}

ir_node *(get_Phi_pred)(ir_node const *node, int pos)
{
	return get_Phi_pred_(node, pos);
}

void (set_Phi_pred)(ir_node *node, int pos, ir_node *pred)
{
	set_Phi_pred_(node, pos, pred);
}

ir_node **(get_Phi_pred_arr)(ir_node *node)
{
	return get_Phi_pred_arr_(node);
}
ir_op *op_Phi;
ir_op *get_op_Phi(void)
{
	return op_Phi;
}

ir_node *new_rd_Pin(dbg_info *dbgi, ir_node *block, ir_node * irn_op)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[1];
	in[0] = irn_op;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Pin, get_irn_mode(irn_op), 1, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Pin(ir_node *block, ir_node * irn_op)
{
	return new_rd_Pin(NULL, block, irn_op);
}

ir_node *new_d_Pin(dbg_info *dbgi, ir_node * irn_op)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Pin(dbgi, get_cur_block(), irn_op);
	return res;
}

ir_node *new_Pin(ir_node * irn_op)
{
	return new_d_Pin(NULL, irn_op);
}

ir_node *(get_Pin_op)(const ir_node *node)
{
	return get_Pin_op(node);
}

void (set_Pin_op)(ir_node *node, ir_node *op)
{
	set_Pin_op_(node, op);
}
ir_op *op_Pin;
ir_op *get_op_Pin(void)
{
	return op_Pin;
}

ir_node *new_rd_Proj(dbg_info *dbgi, ir_node * irn_pred, ir_mode * mode, unsigned num)
{
	ir_node *block = get_nodes_block(irn_pred);
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[1];
	in[0] = irn_pred;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Proj, mode, 1, in);
	proj_attr *attr = &res->attr.proj;
	attr->num = num;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Proj(ir_node * irn_pred, ir_mode * mode, unsigned num)
{
	return new_rd_Proj(NULL, irn_pred, mode, num);
}

ir_node *new_d_Proj(dbg_info *dbgi, ir_node * irn_pred, ir_mode * mode, unsigned num)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Proj(dbgi, irn_pred, mode, num);
	return res;
}

ir_node *new_Proj(ir_node * irn_pred, ir_mode * mode, unsigned num)
{
	return new_d_Proj(NULL, irn_pred, mode, num);
}

ir_node *(get_Proj_pred)(const ir_node *node)
{
	return get_Proj_pred(node);
}

void (set_Proj_pred)(ir_node *node, ir_node *pred)
{
	set_Proj_pred_(node, pred);
}
ir_op *op_Proj;
ir_op *get_op_Proj(void)
{
	return op_Proj;
}

ir_node *new_rd_Raise(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_exo_ptr)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_mem;
	in[1] = irn_exo_ptr;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Raise, mode_T, 2, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Raise(ir_node *block, ir_node * irn_mem, ir_node * irn_exo_ptr)
{
	return new_rd_Raise(NULL, block, irn_mem, irn_exo_ptr);
}

ir_node *new_d_Raise(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_exo_ptr)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Raise(dbgi, get_cur_block(), irn_mem, irn_exo_ptr);
	return res;
}

ir_node *new_Raise(ir_node * irn_mem, ir_node * irn_exo_ptr)
{
	return new_d_Raise(NULL, irn_mem, irn_exo_ptr);
}

ir_node *(get_Raise_mem)(const ir_node *node)
{
	return get_Raise_mem(node);
}

void (set_Raise_mem)(ir_node *node, ir_node *mem)
{
	set_Raise_mem_(node, mem);
}

ir_node *(get_Raise_exo_ptr)(const ir_node *node)
{
	return get_Raise_exo_ptr(node);
}

void (set_Raise_exo_ptr)(ir_node *node, ir_node *exo_ptr)
{
	set_Raise_exo_ptr_(node, exo_ptr);
}
ir_op *op_Raise;
ir_op *get_op_Raise(void)
{
	return op_Raise;
}

ir_node *new_rd_Return(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, int arity, ir_node *const * in)
{
	
	ir_graph *irg = get_irn_irg(block);

	int r_arity = arity + 1;
	ir_node **r_in= ALLOCAN(ir_node*, r_arity);
	r_in[0] = irn_mem;
	MEMCPY(&r_in[1], in, arity);
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Return, mode_X, r_arity, r_in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Return(ir_node *block, ir_node * irn_mem, int arity, ir_node *const * in)
{
	return new_rd_Return(NULL, block, irn_mem, arity, in);
}

ir_node *new_d_Return(dbg_info *dbgi, ir_node * irn_mem, int arity, ir_node *const * in)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Return(dbgi, get_cur_block(), irn_mem, arity, in);
	return res;
}

ir_node *new_Return(ir_node * irn_mem, int arity, ir_node *const * in)
{
	return new_d_Return(NULL, irn_mem, arity, in);
}

ir_node *(get_Return_mem)(const ir_node *node)
{
	return get_Return_mem(node);
}

void (set_Return_mem)(ir_node *node, ir_node *mem)
{
	set_Return_mem_(node, mem);
}

int (get_Return_n_ress)(ir_node const *node)
{
	return get_Return_n_ress_(node);
}

ir_node *(get_Return_res)(ir_node const *node, int pos)
{
	return get_Return_res_(node, pos);
}

void (set_Return_res)(ir_node *node, int pos, ir_node *res)
{
	set_Return_res_(node, pos, res);
}

ir_node **(get_Return_res_arr)(ir_node *node)
{
	return get_Return_res_arr_(node);
}
ir_op *op_Return;
ir_op *get_op_Return(void)
{
	return op_Return;
}

ir_node *new_rd_Sel(dbg_info *dbgi, ir_node *block, ir_node * irn_ptr, ir_node * irn_index, ir_type* type)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_ptr;
	in[1] = irn_index;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Sel, mode_P, 2, in);
	sel_attr *attr = &res->attr.sel;
	attr->type = type;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Sel(ir_node *block, ir_node * irn_ptr, ir_node * irn_index, ir_type* type)
{
	return new_rd_Sel(NULL, block, irn_ptr, irn_index, type);
}

ir_node *new_d_Sel(dbg_info *dbgi, ir_node * irn_ptr, ir_node * irn_index, ir_type* type)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Sel(dbgi, get_cur_block(), irn_ptr, irn_index, type);
	return res;
}

ir_node *new_Sel(ir_node * irn_ptr, ir_node * irn_index, ir_type* type)
{
	return new_d_Sel(NULL, irn_ptr, irn_index, type);
}

ir_node *(get_Sel_ptr)(const ir_node *node)
{
	return get_Sel_ptr(node);
}

void (set_Sel_ptr)(ir_node *node, ir_node *ptr)
{
	set_Sel_ptr_(node, ptr);
}

ir_node *(get_Sel_index)(const ir_node *node)
{
	return get_Sel_index(node);
}

void (set_Sel_index)(ir_node *node, ir_node *index)
{
	set_Sel_index_(node, index);
}
ir_op *op_Sel;
ir_op *get_op_Sel(void)
{
	return op_Sel;
}

ir_node *new_rd_Shl(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_left;
	in[1] = irn_right;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Shl, get_irn_mode(irn_left), 2, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Shl(ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	return new_rd_Shl(NULL, block, irn_left, irn_right);
}

ir_node *new_d_Shl(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Shl(dbgi, get_cur_block(), irn_left, irn_right);
	return res;
}

ir_node *new_Shl(ir_node * irn_left, ir_node * irn_right)
{
	return new_d_Shl(NULL, irn_left, irn_right);
}

ir_node *(get_Shl_left)(const ir_node *node)
{
	return get_Shl_left(node);
}

void (set_Shl_left)(ir_node *node, ir_node *left)
{
	set_Shl_left_(node, left);
}

ir_node *(get_Shl_right)(const ir_node *node)
{
	return get_Shl_right(node);
}

void (set_Shl_right)(ir_node *node, ir_node *right)
{
	set_Shl_right_(node, right);
}
ir_op *op_Shl;
ir_op *get_op_Shl(void)
{
	return op_Shl;
}

ir_node *new_rd_Shr(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_left;
	in[1] = irn_right;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Shr, get_irn_mode(irn_left), 2, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Shr(ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	return new_rd_Shr(NULL, block, irn_left, irn_right);
}

ir_node *new_d_Shr(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Shr(dbgi, get_cur_block(), irn_left, irn_right);
	return res;
}

ir_node *new_Shr(ir_node * irn_left, ir_node * irn_right)
{
	return new_d_Shr(NULL, irn_left, irn_right);
}

ir_node *(get_Shr_left)(const ir_node *node)
{
	return get_Shr_left(node);
}

void (set_Shr_left)(ir_node *node, ir_node *left)
{
	set_Shr_left_(node, left);
}

ir_node *(get_Shr_right)(const ir_node *node)
{
	return get_Shr_right(node);
}

void (set_Shr_right)(ir_node *node, ir_node *right)
{
	set_Shr_right_(node, right);
}
ir_op *op_Shr;
ir_op *get_op_Shr(void)
{
	return op_Shr;
}

ir_node *new_rd_Shrs(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_left;
	in[1] = irn_right;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Shrs, get_irn_mode(irn_left), 2, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Shrs(ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	return new_rd_Shrs(NULL, block, irn_left, irn_right);
}

ir_node *new_d_Shrs(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Shrs(dbgi, get_cur_block(), irn_left, irn_right);
	return res;
}

ir_node *new_Shrs(ir_node * irn_left, ir_node * irn_right)
{
	return new_d_Shrs(NULL, irn_left, irn_right);
}

ir_node *(get_Shrs_left)(const ir_node *node)
{
	return get_Shrs_left(node);
}

void (set_Shrs_left)(ir_node *node, ir_node *left)
{
	set_Shrs_left_(node, left);
}

ir_node *(get_Shrs_right)(const ir_node *node)
{
	return get_Shrs_right(node);
}

void (set_Shrs_right)(ir_node *node, ir_node *right)
{
	set_Shrs_right_(node, right);
}
ir_op *op_Shrs;
ir_op *get_op_Shrs(void)
{
	return op_Shrs;
}

ir_node *new_rd_Size(dbg_info *dbgi, ir_graph *irg, ir_mode * mode, ir_type* type)
{
	ir_node *block = get_irg_start_block(irg);
	
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Size, mode, 0, NULL);
	typeconst_attr *attr = &res->attr.typec;
	attr->type = type;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Size(ir_graph *irg, ir_mode * mode, ir_type* type)
{
	return new_rd_Size(NULL, irg, mode, type);
}

ir_node *new_d_Size(dbg_info *dbgi, ir_mode * mode, ir_type* type)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Size(dbgi, current_ir_graph, mode, type);
	return res;
}

ir_node *new_Size(ir_mode * mode, ir_type* type)
{
	return new_d_Size(NULL, mode, type);
}
ir_op *op_Size;
ir_op *get_op_Size(void)
{
	return op_Size;
}

ir_node *new_rd_Start(dbg_info *dbgi, ir_graph *irg)
{
	ir_node *block = get_irg_start_block(irg);
	
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Start, mode_T, 0, NULL);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Start(ir_graph *irg)
{
	return new_rd_Start(NULL, irg);
}

ir_node *new_d_Start(dbg_info *dbgi)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Start(dbgi, current_ir_graph);
	return res;
}

ir_node *new_Start(void)
{
	return new_d_Start(NULL);
}
ir_op *op_Start;
ir_op *get_op_Start(void)
{
	return op_Start;
}

ir_node *new_rd_Store(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_ptr, ir_node * irn_value, ir_type* type, ir_cons_flags flags)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[3];
	in[0] = irn_mem;
	in[1] = irn_ptr;
	in[2] = irn_value;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Store, mode_T, 3, in);
	store_attr *attr = &res->attr.store;
	attr->type = type;
	attr->volatility = flags & cons_volatile ? volatility_is_volatile : volatility_non_volatile;
	attr->unaligned = flags & cons_unaligned ? align_non_aligned : align_is_aligned;
	attr->exc.pinned = flags & cons_floats ? op_pin_state_floats : op_pin_state_pinned;
	attr->exc.throws_exception = (flags & cons_throws_exception) != 0;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Store(ir_node *block, ir_node * irn_mem, ir_node * irn_ptr, ir_node * irn_value, ir_type* type, ir_cons_flags flags)
{
	return new_rd_Store(NULL, block, irn_mem, irn_ptr, irn_value, type, flags);
}

ir_node *new_d_Store(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_ptr, ir_node * irn_value, ir_type* type, ir_cons_flags flags)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Store(dbgi, get_cur_block(), irn_mem, irn_ptr, irn_value, type, flags);
	return res;
}

ir_node *new_Store(ir_node * irn_mem, ir_node * irn_ptr, ir_node * irn_value, ir_type* type, ir_cons_flags flags)
{
	return new_d_Store(NULL, irn_mem, irn_ptr, irn_value, type, flags);
}

ir_node *(get_Store_mem)(const ir_node *node)
{
	return get_Store_mem(node);
}

void (set_Store_mem)(ir_node *node, ir_node *mem)
{
	set_Store_mem_(node, mem);
}

ir_node *(get_Store_ptr)(const ir_node *node)
{
	return get_Store_ptr(node);
}

void (set_Store_ptr)(ir_node *node, ir_node *ptr)
{
	set_Store_ptr_(node, ptr);
}

ir_node *(get_Store_value)(const ir_node *node)
{
	return get_Store_value(node);
}

void (set_Store_value)(ir_node *node, ir_node *value)
{
	set_Store_value_(node, value);
}
ir_op *op_Store;
ir_op *get_op_Store(void)
{
	return op_Store;
}

ir_node *new_rd_Sub(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[2];
	in[0] = irn_left;
	in[1] = irn_right;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Sub, mode_is_reference(get_irn_mode(irn_right)) ? get_reference_offset_mode(get_irn_mode(irn_left)) : get_irn_mode(irn_left), 2, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Sub(ir_node *block, ir_node * irn_left, ir_node * irn_right)
{
	return new_rd_Sub(NULL, block, irn_left, irn_right);
}

ir_node *new_d_Sub(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Sub(dbgi, get_cur_block(), irn_left, irn_right);
	return res;
}

ir_node *new_Sub(ir_node * irn_left, ir_node * irn_right)
{
	return new_d_Sub(NULL, irn_left, irn_right);
}

ir_node *(get_Sub_left)(const ir_node *node)
{
	return get_Sub_left(node);
}

void (set_Sub_left)(ir_node *node, ir_node *left)
{
	set_Sub_left_(node, left);
}

ir_node *(get_Sub_right)(const ir_node *node)
{
	return get_Sub_right(node);
}

void (set_Sub_right)(ir_node *node, ir_node *right)
{
	set_Sub_right_(node, right);
}
ir_op *op_Sub;
ir_op *get_op_Sub(void)
{
	return op_Sub;
}

ir_node *new_rd_Switch(dbg_info *dbgi, ir_node *block, ir_node * irn_selector, unsigned n_outs, ir_switch_table* table)
{
	
	ir_graph *irg = get_irn_irg(block);

	ir_node *in[1];
	in[0] = irn_selector;

	ir_node *res = new_ir_node(dbgi, irg, block, op_Switch, mode_T, 1, in);
	switch_attr *attr = &res->attr.switcha;
	attr->n_outs = n_outs;
	attr->table = table;
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Switch(ir_node *block, ir_node * irn_selector, unsigned n_outs, ir_switch_table* table)
{
	return new_rd_Switch(NULL, block, irn_selector, n_outs, table);
}

ir_node *new_d_Switch(dbg_info *dbgi, ir_node * irn_selector, unsigned n_outs, ir_switch_table* table)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Switch(dbgi, get_cur_block(), irn_selector, n_outs, table);
	return res;
}

ir_node *new_Switch(ir_node * irn_selector, unsigned n_outs, ir_switch_table* table)
{
	return new_d_Switch(NULL, irn_selector, n_outs, table);
}

ir_node *(get_Switch_selector)(const ir_node *node)
{
	return get_Switch_selector(node);
}

void (set_Switch_selector)(ir_node *node, ir_node *selector)
{
	set_Switch_selector_(node, selector);
}
ir_op *op_Switch;
ir_op *get_op_Switch(void)
{
	return op_Switch;
}

ir_node *new_rd_Sync(dbg_info *dbgi, ir_node *block, int arity, ir_node *const * in)
{
	
	ir_graph *irg = get_irn_irg(block);

	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Sync, mode_M, arity, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Sync(ir_node *block, int arity, ir_node *const * in)
{
	return new_rd_Sync(NULL, block, arity, in);
}

ir_node *new_d_Sync(dbg_info *dbgi, int arity, ir_node *const * in)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Sync(dbgi, get_cur_block(), arity, in);
	return res;
}

ir_node *new_Sync(int arity, ir_node *const * in)
{
	return new_d_Sync(NULL, arity, in);
}

int (get_Sync_n_preds)(ir_node const *node)
{
	return get_Sync_n_preds_(node);
}

ir_node *(get_Sync_pred)(ir_node const *node, int pos)
{
	return get_Sync_pred_(node, pos);
}

void (set_Sync_pred)(ir_node *node, int pos, ir_node *pred)
{
	set_Sync_pred_(node, pos, pred);
}

ir_node **(get_Sync_pred_arr)(ir_node *node)
{
	return get_Sync_pred_arr_(node);
}
ir_op *op_Sync;
ir_op *get_op_Sync(void)
{
	return op_Sync;
}

ir_node *new_rd_Tuple(dbg_info *dbgi, ir_node *block, int arity, ir_node *const * in)
{
	
	ir_graph *irg = get_irn_irg(block);

	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Tuple, mode_T, arity, in);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Tuple(ir_node *block, int arity, ir_node *const * in)
{
	return new_rd_Tuple(NULL, block, arity, in);
}

ir_node *new_d_Tuple(dbg_info *dbgi, int arity, ir_node *const * in)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Tuple(dbgi, get_cur_block(), arity, in);
	return res;
}

ir_node *new_Tuple(int arity, ir_node *const * in)
{
	return new_d_Tuple(NULL, arity, in);
}

int (get_Tuple_n_preds)(ir_node const *node)
{
	return get_Tuple_n_preds_(node);
}

ir_node *(get_Tuple_pred)(ir_node const *node, int pos)
{
	return get_Tuple_pred_(node, pos);
}

void (set_Tuple_pred)(ir_node *node, int pos, ir_node *pred)
{
	set_Tuple_pred_(node, pos, pred);
}

ir_node **(get_Tuple_pred_arr)(ir_node *node)
{
	return get_Tuple_pred_arr_(node);
}
ir_op *op_Tuple;
ir_op *get_op_Tuple(void)
{
	return op_Tuple;
}

ir_node *new_rd_Unknown(dbg_info *dbgi, ir_graph *irg, ir_mode * mode)
{
	ir_node *block = get_irg_start_block(irg);
	
	

	ir_node *res = new_ir_node(dbgi, irg, block, op_Unknown, mode, 0, NULL);
	
	verify_new_node(res);
	res = optimize_node(res);
	return res;
}

ir_node *new_r_Unknown(ir_graph *irg, ir_mode * mode)
{
	return new_rd_Unknown(NULL, irg, mode);
}

ir_node *new_d_Unknown(dbg_info *dbgi, ir_mode * mode)
{
	assert(irg_is_constrained(current_ir_graph, IR_GRAPH_CONSTRAINT_CONSTRUCTION));
	ir_node *res = new_rd_Unknown(dbgi, current_ir_graph, mode);
	return res;
}

ir_node *new_Unknown(ir_mode * mode)
{
	return new_d_Unknown(NULL, mode);
}
ir_op *op_Unknown;
ir_op *get_op_Unknown(void)
{
	return op_Unknown;
}


int (is_ASM)(const ir_node *node)
{
	return is_ASM_(node);
}

ir_asm_constraint* (get_ASM_constraints)(const ir_node *node)
{
	return get_ASM_constraints_(node);
}

void (set_ASM_constraints)(ir_node *node, ir_asm_constraint* constraints)
{
	set_ASM_constraints_(node, constraints);
}

ident** (get_ASM_clobbers)(const ir_node *node)
{
	return get_ASM_clobbers_(node);
}

void (set_ASM_clobbers)(ir_node *node, ident** clobbers)
{
	set_ASM_clobbers_(node, clobbers);
}

ident* (get_ASM_text)(const ir_node *node)
{
	return get_ASM_text_(node);
}

void (set_ASM_text)(ir_node *node, ident* text)
{
	set_ASM_text_(node, text);
}

int (is_Add)(const ir_node *node)
{
	return is_Add_(node);
}

int (is_Address)(const ir_node *node)
{
	return is_Address_(node);
}

ir_entity* (get_Address_entity)(const ir_node *node)
{
	return get_Address_entity_(node);
}

void (set_Address_entity)(ir_node *node, ir_entity* entity)
{
	set_Address_entity_(node, entity);
}

int (is_Align)(const ir_node *node)
{
	return is_Align_(node);
}

ir_type* (get_Align_type)(const ir_node *node)
{
	return get_Align_type_(node);
}

void (set_Align_type)(ir_node *node, ir_type* type)
{
	set_Align_type_(node, type);
}

int (is_Alloc)(const ir_node *node)
{
	return is_Alloc_(node);
}

unsigned (get_Alloc_alignment)(const ir_node *node)
{
	return get_Alloc_alignment_(node);
}

void (set_Alloc_alignment)(ir_node *node, unsigned alignment)
{
	set_Alloc_alignment_(node, alignment);
}

int (is_Anchor)(const ir_node *node)
{
	return is_Anchor_(node);
}

int (is_And)(const ir_node *node)
{
	return is_And_(node);
}

int (is_Bad)(const ir_node *node)
{
	return is_Bad_(node);
}

int (is_Bitcast)(const ir_node *node)
{
	return is_Bitcast_(node);
}

int (is_Block)(const ir_node *node)
{
	return is_Block_(node);
}

ir_entity* (get_Block_entity)(const ir_node *node)
{
	return get_Block_entity_(node);
}

void (set_Block_entity)(ir_node *node, ir_entity* entity)
{
	set_Block_entity_(node, entity);
}

int (is_Builtin)(const ir_node *node)
{
	return is_Builtin_(node);
}

ir_builtin_kind (get_Builtin_kind)(const ir_node *node)
{
	return get_Builtin_kind_(node);
}

void (set_Builtin_kind)(ir_node *node, ir_builtin_kind kind)
{
	set_Builtin_kind_(node, kind);
}

ir_type* (get_Builtin_type)(const ir_node *node)
{
	return get_Builtin_type_(node);
}

void (set_Builtin_type)(ir_node *node, ir_type* type)
{
	set_Builtin_type_(node, type);
}

int (is_Call)(const ir_node *node)
{
	return is_Call_(node);
}

ir_type* (get_Call_type)(const ir_node *node)
{
	return get_Call_type_(node);
}

void (set_Call_type)(ir_node *node, ir_type* type)
{
	set_Call_type_(node, type);
}

int (is_Cmp)(const ir_node *node)
{
	return is_Cmp_(node);
}

ir_relation (get_Cmp_relation)(const ir_node *node)
{
	return get_Cmp_relation_(node);
}

void (set_Cmp_relation)(ir_node *node, ir_relation relation)
{
	set_Cmp_relation_(node, relation);
}

int (is_Cond)(const ir_node *node)
{
	return is_Cond_(node);
}

cond_jmp_predicate (get_Cond_jmp_pred)(const ir_node *node)
{
	return get_Cond_jmp_pred_(node);
}

void (set_Cond_jmp_pred)(ir_node *node, cond_jmp_predicate jmp_pred)
{
	set_Cond_jmp_pred_(node, jmp_pred);
}

int (is_Confirm)(const ir_node *node)
{
	return is_Confirm_(node);
}

ir_relation (get_Confirm_relation)(const ir_node *node)
{
	return get_Confirm_relation_(node);
}

void (set_Confirm_relation)(ir_node *node, ir_relation relation)
{
	set_Confirm_relation_(node, relation);
}

int (is_Const)(const ir_node *node)
{
	return is_Const_(node);
}

ir_tarval* (get_Const_tarval)(const ir_node *node)
{
	return get_Const_tarval_(node);
}

void (set_Const_tarval)(ir_node *node, ir_tarval* tarval)
{
	set_Const_tarval_(node, tarval);
}

int (is_Conv)(const ir_node *node)
{
	return is_Conv_(node);
}

int (is_CopyB)(const ir_node *node)
{
	return is_CopyB_(node);
}

ir_type* (get_CopyB_type)(const ir_node *node)
{
	return get_CopyB_type_(node);
}

void (set_CopyB_type)(ir_node *node, ir_type* type)
{
	set_CopyB_type_(node, type);
}

ir_volatility (get_CopyB_volatility)(const ir_node *node)
{
	return get_CopyB_volatility_(node);
}

void (set_CopyB_volatility)(ir_node *node, ir_volatility volatility)
{
	set_CopyB_volatility_(node, volatility);
}

int (is_Deleted)(const ir_node *node)
{
	return is_Deleted_(node);
}

int (is_Div)(const ir_node *node)
{
	return is_Div_(node);
}

ir_mode* (get_Div_resmode)(const ir_node *node)
{
	return get_Div_resmode_(node);
}

void (set_Div_resmode)(ir_node *node, ir_mode* resmode)
{
	set_Div_resmode_(node, resmode);
}

int (get_Div_no_remainder)(const ir_node *node)
{
	return get_Div_no_remainder_(node);
}

void (set_Div_no_remainder)(ir_node *node, int no_remainder)
{
	set_Div_no_remainder_(node, no_remainder);
}

int (is_Dummy)(const ir_node *node)
{
	return is_Dummy_(node);
}

int (is_End)(const ir_node *node)
{
	return is_End_(node);
}

int (is_Eor)(const ir_node *node)
{
	return is_Eor_(node);
}

int (is_Free)(const ir_node *node)
{
	return is_Free_(node);
}

int (is_IJmp)(const ir_node *node)
{
	return is_IJmp_(node);
}

int (is_Id)(const ir_node *node)
{
	return is_Id_(node);
}

int (is_Jmp)(const ir_node *node)
{
	return is_Jmp_(node);
}

int (is_Load)(const ir_node *node)
{
	return is_Load_(node);
}

ir_mode* (get_Load_mode)(const ir_node *node)
{
	return get_Load_mode_(node);
}

void (set_Load_mode)(ir_node *node, ir_mode* mode)
{
	set_Load_mode_(node, mode);
}

ir_type* (get_Load_type)(const ir_node *node)
{
	return get_Load_type_(node);
}

void (set_Load_type)(ir_node *node, ir_type* type)
{
	set_Load_type_(node, type);
}

ir_volatility (get_Load_volatility)(const ir_node *node)
{
	return get_Load_volatility_(node);
}

void (set_Load_volatility)(ir_node *node, ir_volatility volatility)
{
	set_Load_volatility_(node, volatility);
}

ir_align (get_Load_unaligned)(const ir_node *node)
{
	return get_Load_unaligned_(node);
}

void (set_Load_unaligned)(ir_node *node, ir_align unaligned)
{
	set_Load_unaligned_(node, unaligned);
}

int (is_Member)(const ir_node *node)
{
	return is_Member_(node);
}

ir_entity* (get_Member_entity)(const ir_node *node)
{
	return get_Member_entity_(node);
}

void (set_Member_entity)(ir_node *node, ir_entity* entity)
{
	set_Member_entity_(node, entity);
}

int (is_Minus)(const ir_node *node)
{
	return is_Minus_(node);
}

int (is_Mod)(const ir_node *node)
{
	return is_Mod_(node);
}

ir_mode* (get_Mod_resmode)(const ir_node *node)
{
	return get_Mod_resmode_(node);
}

void (set_Mod_resmode)(ir_node *node, ir_mode* resmode)
{
	set_Mod_resmode_(node, resmode);
}

int (is_Mul)(const ir_node *node)
{
	return is_Mul_(node);
}

int (is_Mulh)(const ir_node *node)
{
	return is_Mulh_(node);
}

int (is_Mux)(const ir_node *node)
{
	return is_Mux_(node);
}

int (is_NoMem)(const ir_node *node)
{
	return is_NoMem_(node);
}

int (is_Not)(const ir_node *node)
{
	return is_Not_(node);
}

int (is_Offset)(const ir_node *node)
{
	return is_Offset_(node);
}

ir_entity* (get_Offset_entity)(const ir_node *node)
{
	return get_Offset_entity_(node);
}

void (set_Offset_entity)(ir_node *node, ir_entity* entity)
{
	set_Offset_entity_(node, entity);
}

int (is_Or)(const ir_node *node)
{
	return is_Or_(node);
}

int (is_Phi)(const ir_node *node)
{
	return is_Phi_(node);
}

int (get_Phi_loop)(const ir_node *node)
{
	return get_Phi_loop_(node);
}

void (set_Phi_loop)(ir_node *node, int loop)
{
	set_Phi_loop_(node, loop);
}

int (is_Pin)(const ir_node *node)
{
	return is_Pin_(node);
}

int (is_Proj)(const ir_node *node)
{
	return is_Proj_(node);
}

unsigned (get_Proj_num)(const ir_node *node)
{
	return get_Proj_num_(node);
}

void (set_Proj_num)(ir_node *node, unsigned num)
{
	set_Proj_num_(node, num);
}

int (is_Raise)(const ir_node *node)
{
	return is_Raise_(node);
}

int (is_Return)(const ir_node *node)
{
	return is_Return_(node);
}

int (is_Sel)(const ir_node *node)
{
	return is_Sel_(node);
}

ir_type* (get_Sel_type)(const ir_node *node)
{
	return get_Sel_type_(node);
}

void (set_Sel_type)(ir_node *node, ir_type* type)
{
	set_Sel_type_(node, type);
}

int (is_Shl)(const ir_node *node)
{
	return is_Shl_(node);
}

int (is_Shr)(const ir_node *node)
{
	return is_Shr_(node);
}

int (is_Shrs)(const ir_node *node)
{
	return is_Shrs_(node);
}

int (is_Size)(const ir_node *node)
{
	return is_Size_(node);
}

ir_type* (get_Size_type)(const ir_node *node)
{
	return get_Size_type_(node);
}

void (set_Size_type)(ir_node *node, ir_type* type)
{
	set_Size_type_(node, type);
}

int (is_Start)(const ir_node *node)
{
	return is_Start_(node);
}

int (is_Store)(const ir_node *node)
{
	return is_Store_(node);
}

ir_type* (get_Store_type)(const ir_node *node)
{
	return get_Store_type_(node);
}

void (set_Store_type)(ir_node *node, ir_type* type)
{
	set_Store_type_(node, type);
}

ir_volatility (get_Store_volatility)(const ir_node *node)
{
	return get_Store_volatility_(node);
}

void (set_Store_volatility)(ir_node *node, ir_volatility volatility)
{
	set_Store_volatility_(node, volatility);
}

ir_align (get_Store_unaligned)(const ir_node *node)
{
	return get_Store_unaligned_(node);
}

void (set_Store_unaligned)(ir_node *node, ir_align unaligned)
{
	set_Store_unaligned_(node, unaligned);
}

int (is_Sub)(const ir_node *node)
{
	return is_Sub_(node);
}

int (is_Switch)(const ir_node *node)
{
	return is_Switch_(node);
}

unsigned (get_Switch_n_outs)(const ir_node *node)
{
	return get_Switch_n_outs_(node);
}

void (set_Switch_n_outs)(ir_node *node, unsigned n_outs)
{
	set_Switch_n_outs_(node, n_outs);
}

ir_switch_table* (get_Switch_table)(const ir_node *node)
{
	return get_Switch_table_(node);
}

void (set_Switch_table)(ir_node *node, ir_switch_table* table)
{
	set_Switch_table_(node, table);
}

int (is_Sync)(const ir_node *node)
{
	return is_Sync_(node);
}

int (is_Tuple)(const ir_node *node)
{
	return is_Tuple_(node);
}

int (is_Unknown)(const ir_node *node)
{
	return is_Unknown_(node);
}

int (is_binop)(const ir_node *node)
{
	return is_binop_(node);
}

int (is_entconst)(const ir_node *node)
{
	return is_entconst_(node);
}

ir_entity* (get_entconst_entity)(const ir_node *node)
{
	return get_entconst_entity_(node);
}

void (set_entconst_entity)(ir_node *node, ir_entity* entity)
{
	set_entconst_entity_(node, entity);
}

int (is_typeconst)(const ir_node *node)
{
	return is_typeconst_(node);
}

ir_type* (get_typeconst_type)(const ir_node *node)
{
	return get_typeconst_type_(node);
}

void (set_typeconst_type)(ir_node *node, ir_type* type)
{
	set_typeconst_type_(node, type);
}

void ir_init_opcodes(void)
{
	op_ASM = new_ir_op(iro_ASM, "ASM", op_pin_state_exc_pinned, irop_flag_fragile | irop_flag_keep | irop_flag_uses_memory, oparity_any, -1, sizeof(asm_attr));
	ir_op_set_memory_index(op_ASM, n_ASM_mem);
	ir_op_set_fragile_indices(op_ASM, pn_ASM_X_regular, (unsigned)-1);
	op_Add = new_ir_op(iro_Add, "Add", op_pin_state_floats, irop_flag_commutative, oparity_binary, 0, 0);
	op_Address = new_ir_op(iro_Address, "Address", op_pin_state_floats, irop_flag_constlike | irop_flag_start_block, oparity_any, -1, sizeof(entconst_attr));
	op_Align = new_ir_op(iro_Align, "Align", op_pin_state_floats, irop_flag_constlike | irop_flag_start_block, oparity_any, -1, sizeof(typeconst_attr));
	op_Alloc = new_ir_op(iro_Alloc, "Alloc", op_pin_state_pinned, irop_flag_uses_memory | irop_flag_const_memory, oparity_any, -1, sizeof(alloc_attr));
	ir_op_set_memory_index(op_Alloc, n_Alloc_mem);
	op_Anchor = new_ir_op(iro_Anchor, "Anchor", op_pin_state_pinned, irop_flag_dump_noblock, oparity_any, -1, 0);
	op_And = new_ir_op(iro_And, "And", op_pin_state_floats, irop_flag_commutative, oparity_binary, 0, 0);
	op_Bad = new_ir_op(iro_Bad, "Bad", op_pin_state_pinned, irop_flag_start_block | irop_flag_dump_noblock, oparity_any, -1, 0);
	op_Bitcast = new_ir_op(iro_Bitcast, "Bitcast", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	op_Block = new_ir_op(iro_Block, "Block", op_pin_state_pinned, irop_flag_none, oparity_any, -1, sizeof(block_attr));
	op_Builtin = new_ir_op(iro_Builtin, "Builtin", op_pin_state_exc_pinned, irop_flag_uses_memory, oparity_any, -1, sizeof(builtin_attr));
	ir_op_set_memory_index(op_Builtin, n_Builtin_mem);
	op_Call = new_ir_op(iro_Call, "Call", op_pin_state_exc_pinned, irop_flag_fragile | irop_flag_uses_memory, oparity_any, -1, sizeof(call_attr));
	ir_op_set_memory_index(op_Call, n_Call_mem);
	ir_op_set_fragile_indices(op_Call, pn_Call_X_regular, pn_Call_X_except);
	op_Cmp = new_ir_op(iro_Cmp, "Cmp", op_pin_state_floats, irop_flag_none, oparity_binary, 0, sizeof(cmp_attr));
	op_Cond = new_ir_op(iro_Cond, "Cond", op_pin_state_pinned, irop_flag_cfopcode | irop_flag_forking, oparity_any, -1, sizeof(cond_attr));
	op_Confirm = new_ir_op(iro_Confirm, "Confirm", op_pin_state_pinned, irop_flag_none, oparity_any, -1, sizeof(confirm_attr));
	op_Const = new_ir_op(iro_Const, "Const", op_pin_state_floats, irop_flag_constlike | irop_flag_start_block, oparity_any, -1, sizeof(const_attr));
	op_Conv = new_ir_op(iro_Conv, "Conv", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	op_CopyB = new_ir_op(iro_CopyB, "CopyB", op_pin_state_floats, irop_flag_uses_memory, oparity_any, -1, sizeof(copyb_attr));
	ir_op_set_memory_index(op_CopyB, n_CopyB_mem);
	op_Deleted = new_ir_op(iro_Deleted, "Deleted", op_pin_state_pinned, irop_flag_none, oparity_any, -1, 0);
	op_Div = new_ir_op(iro_Div, "Div", op_pin_state_exc_pinned, irop_flag_fragile | irop_flag_uses_memory | irop_flag_const_memory, oparity_binary, 1, sizeof(div_attr));
	ir_op_set_memory_index(op_Div, n_Div_mem);
	ir_op_set_fragile_indices(op_Div, pn_Div_X_regular, pn_Div_X_except);
	op_Dummy = new_ir_op(iro_Dummy, "Dummy", op_pin_state_pinned, irop_flag_cfopcode | irop_flag_start_block | irop_flag_constlike | irop_flag_dump_noblock, oparity_any, -1, 0);
	op_End = new_ir_op(iro_End, "End", op_pin_state_pinned, irop_flag_cfopcode, oparity_dynamic, -1, 0);
	op_Eor = new_ir_op(iro_Eor, "Eor", op_pin_state_floats, irop_flag_commutative, oparity_binary, 0, 0);
	op_Free = new_ir_op(iro_Free, "Free", op_pin_state_pinned, irop_flag_uses_memory | irop_flag_const_memory, oparity_any, -1, 0);
	ir_op_set_memory_index(op_Free, n_Free_mem);
	op_IJmp = new_ir_op(iro_IJmp, "IJmp", op_pin_state_pinned, irop_flag_cfopcode | irop_flag_forking | irop_flag_keep | irop_flag_unknown_jump, oparity_any, -1, 0);
	op_Id = new_ir_op(iro_Id, "Id", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	op_Jmp = new_ir_op(iro_Jmp, "Jmp", op_pin_state_pinned, irop_flag_cfopcode, oparity_any, -1, 0);
	op_Load = new_ir_op(iro_Load, "Load", op_pin_state_exc_pinned, irop_flag_fragile | irop_flag_uses_memory | irop_flag_const_memory, oparity_any, -1, sizeof(load_attr));
	ir_op_set_memory_index(op_Load, n_Load_mem);
	ir_op_set_fragile_indices(op_Load, pn_Load_X_regular, pn_Load_X_except);
	op_Member = new_ir_op(iro_Member, "Member", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(member_attr));
	op_Minus = new_ir_op(iro_Minus, "Minus", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	op_Mod = new_ir_op(iro_Mod, "Mod", op_pin_state_exc_pinned, irop_flag_fragile | irop_flag_uses_memory | irop_flag_const_memory, oparity_binary, 1, sizeof(mod_attr));
	ir_op_set_memory_index(op_Mod, n_Mod_mem);
	ir_op_set_fragile_indices(op_Mod, pn_Mod_X_regular, pn_Mod_X_except);
	op_Mul = new_ir_op(iro_Mul, "Mul", op_pin_state_floats, irop_flag_commutative, oparity_binary, 0, 0);
	op_Mulh = new_ir_op(iro_Mulh, "Mulh", op_pin_state_floats, irop_flag_commutative, oparity_binary, 0, 0);
	op_Mux = new_ir_op(iro_Mux, "Mux", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	op_NoMem = new_ir_op(iro_NoMem, "NoMem", op_pin_state_pinned, irop_flag_dump_noblock | irop_flag_start_block, oparity_any, -1, 0);
	op_Not = new_ir_op(iro_Not, "Not", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	op_Offset = new_ir_op(iro_Offset, "Offset", op_pin_state_floats, irop_flag_constlike | irop_flag_start_block, oparity_any, -1, sizeof(entconst_attr));
	op_Or = new_ir_op(iro_Or, "Or", op_pin_state_floats, irop_flag_commutative, oparity_binary, 0, 0);
	op_Phi = new_ir_op(iro_Phi, "Phi", op_pin_state_pinned, irop_flag_none, oparity_any, -1, sizeof(phi_attr));
	op_Pin = new_ir_op(iro_Pin, "Pin", op_pin_state_pinned, irop_flag_none, oparity_any, -1, 0);
	op_Proj = new_ir_op(iro_Proj, "Proj", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(proj_attr));
	op_Raise = new_ir_op(iro_Raise, "Raise", op_pin_state_pinned, irop_flag_cfopcode, oparity_any, -1, 0);
	op_Return = new_ir_op(iro_Return, "Return", op_pin_state_pinned, irop_flag_cfopcode, oparity_any, -1, 0);
	op_Sel = new_ir_op(iro_Sel, "Sel", op_pin_state_floats, irop_flag_none, oparity_any, -1, sizeof(sel_attr));
	op_Shl = new_ir_op(iro_Shl, "Shl", op_pin_state_floats, irop_flag_none, oparity_binary, 0, 0);
	op_Shr = new_ir_op(iro_Shr, "Shr", op_pin_state_floats, irop_flag_none, oparity_binary, 0, 0);
	op_Shrs = new_ir_op(iro_Shrs, "Shrs", op_pin_state_floats, irop_flag_none, oparity_binary, 0, 0);
	op_Size = new_ir_op(iro_Size, "Size", op_pin_state_floats, irop_flag_constlike | irop_flag_start_block, oparity_any, -1, sizeof(typeconst_attr));
	op_Start = new_ir_op(iro_Start, "Start", op_pin_state_pinned, irop_flag_start_block, oparity_any, -1, 0);
	op_Store = new_ir_op(iro_Store, "Store", op_pin_state_exc_pinned, irop_flag_fragile | irop_flag_uses_memory, oparity_any, -1, sizeof(store_attr));
	ir_op_set_memory_index(op_Store, n_Store_mem);
	ir_op_set_fragile_indices(op_Store, pn_Store_X_regular, pn_Store_X_except);
	op_Sub = new_ir_op(iro_Sub, "Sub", op_pin_state_floats, irop_flag_none, oparity_binary, 0, 0);
	op_Switch = new_ir_op(iro_Switch, "Switch", op_pin_state_pinned, irop_flag_cfopcode | irop_flag_forking, oparity_any, -1, sizeof(switch_attr));
	op_Sync = new_ir_op(iro_Sync, "Sync", op_pin_state_floats, irop_flag_none, oparity_dynamic, -1, 0);
	op_Tuple = new_ir_op(iro_Tuple, "Tuple", op_pin_state_floats, irop_flag_none, oparity_any, -1, 0);
	op_Unknown = new_ir_op(iro_Unknown, "Unknown", op_pin_state_pinned, irop_flag_start_block | irop_flag_constlike | irop_flag_dump_noblock, oparity_any, -1, 0);
}

void ir_finish_opcodes(void)
{
	free_ir_op(op_ASM); op_ASM = NULL;
	free_ir_op(op_Add); op_Add = NULL;
	free_ir_op(op_Address); op_Address = NULL;
	free_ir_op(op_Align); op_Align = NULL;
	free_ir_op(op_Alloc); op_Alloc = NULL;
	free_ir_op(op_Anchor); op_Anchor = NULL;
	free_ir_op(op_And); op_And = NULL;
	free_ir_op(op_Bad); op_Bad = NULL;
	free_ir_op(op_Bitcast); op_Bitcast = NULL;
	free_ir_op(op_Block); op_Block = NULL;
	free_ir_op(op_Builtin); op_Builtin = NULL;
	free_ir_op(op_Call); op_Call = NULL;
	free_ir_op(op_Cmp); op_Cmp = NULL;
	free_ir_op(op_Cond); op_Cond = NULL;
	free_ir_op(op_Confirm); op_Confirm = NULL;
	free_ir_op(op_Const); op_Const = NULL;
	free_ir_op(op_Conv); op_Conv = NULL;
	free_ir_op(op_CopyB); op_CopyB = NULL;
	free_ir_op(op_Deleted); op_Deleted = NULL;
	free_ir_op(op_Div); op_Div = NULL;
	free_ir_op(op_Dummy); op_Dummy = NULL;
	free_ir_op(op_End); op_End = NULL;
	free_ir_op(op_Eor); op_Eor = NULL;
	free_ir_op(op_Free); op_Free = NULL;
	free_ir_op(op_IJmp); op_IJmp = NULL;
	free_ir_op(op_Id); op_Id = NULL;
	free_ir_op(op_Jmp); op_Jmp = NULL;
	free_ir_op(op_Load); op_Load = NULL;
	free_ir_op(op_Member); op_Member = NULL;
	free_ir_op(op_Minus); op_Minus = NULL;
	free_ir_op(op_Mod); op_Mod = NULL;
	free_ir_op(op_Mul); op_Mul = NULL;
	free_ir_op(op_Mulh); op_Mulh = NULL;
	free_ir_op(op_Mux); op_Mux = NULL;
	free_ir_op(op_NoMem); op_NoMem = NULL;
	free_ir_op(op_Not); op_Not = NULL;
	free_ir_op(op_Offset); op_Offset = NULL;
	free_ir_op(op_Or); op_Or = NULL;
	free_ir_op(op_Phi); op_Phi = NULL;
	free_ir_op(op_Pin); op_Pin = NULL;
	free_ir_op(op_Proj); op_Proj = NULL;
	free_ir_op(op_Raise); op_Raise = NULL;
	free_ir_op(op_Return); op_Return = NULL;
	free_ir_op(op_Sel); op_Sel = NULL;
	free_ir_op(op_Shl); op_Shl = NULL;
	free_ir_op(op_Shr); op_Shr = NULL;
	free_ir_op(op_Shrs); op_Shrs = NULL;
	free_ir_op(op_Size); op_Size = NULL;
	free_ir_op(op_Start); op_Start = NULL;
	free_ir_op(op_Store); op_Store = NULL;
	free_ir_op(op_Sub); op_Sub = NULL;
	free_ir_op(op_Switch); op_Switch = NULL;
	free_ir_op(op_Sync); op_Sync = NULL;
	free_ir_op(op_Tuple); op_Tuple = NULL;
	free_ir_op(op_Unknown); op_Unknown = NULL;
}
