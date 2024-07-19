/*
 * This file is part of libFirm.
 * Copyright (C) 2012 University of Karlsruhe.
 */

/**
 * @file
 * @brief   Function prototypes for the assembler ir node constructors.
 */

/**
 * @file
 * @brief Function prototypes for the new opcode functions.
 */

#ifndef FIRM_BE_eigen_eigen_NEW_NODES_H
#define FIRM_BE_eigen_eigen_NEW_NODES_H

#include "eigen_nodes_attr.h"
#include "be_types.h"
#include "irnode_t.h"

/**
 * Returns the attributes of an eigen node.
 */
eigen_attr_t *get_eigen_attr(ir_node *node);

const eigen_attr_t *get_eigen_attr_const(const ir_node *node);

typedef enum eigen_opcodes {
    iro_eigen_Add,
    iro_eigen_And,
    iro_eigen_Const,
    iro_eigen_Jmp,
    iro_eigen_Load,
    iro_eigen_Minus,
    iro_eigen_Mul,
    iro_eigen_Not,
    iro_eigen_Or,
    iro_eigen_Return,
    iro_eigen_Shl,
    iro_eigen_Shr,
    iro_eigen_Store,
    iro_eigen_Sub,
    iro_eigen_Xor,
    iro_eigen_fAdd,
    iro_eigen_fConst,
    iro_eigen_fDiv,
    iro_eigen_fLoad,
    iro_eigen_fMinus,
    iro_eigen_fMul,
    iro_eigen_fStore,
    iro_eigen_fSub,
    iro_eigen_last
} eigen_opcodes;


int is_eigen_irn(const ir_node *node);
int is_eigen_op(const ir_op *op);

int get_eigen_irn_opcode(const ir_node *node);
void eigen_create_opcodes(void);
void eigen_free_opcodes(void);

extern ir_op *op_eigen_Add;

static inline bool is_eigen_Add(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_Add;
}

/**
 * construct Add node
 */
ir_node *new_bd_eigen_Add(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1);

extern ir_op *op_eigen_And;

static inline bool is_eigen_And(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_And;
}

/**
 * construct And node
 */
ir_node *new_bd_eigen_And(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1);

extern ir_op *op_eigen_Const;

static inline bool is_eigen_Const(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_Const;
}

/**
 * construct Const node
 */
ir_node *new_bd_eigen_Const(dbg_info *dbgi, ir_node *block, ir_entity *entity, ir_tarval *value);

extern ir_op *op_eigen_Jmp;

static inline bool is_eigen_Jmp(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_Jmp;
}

/**
 * construct Jmp node
 */
ir_node *new_bd_eigen_Jmp(dbg_info *dbgi, ir_node *block);

extern ir_op *op_eigen_Load;

static inline bool is_eigen_Load(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_Load;
}

/**
 * construct Load node
 */
ir_node *new_bd_eigen_Load(dbg_info *dbgi, ir_node *block, ir_node *mem, ir_node *ptr);

extern ir_op *op_eigen_Minus;

static inline bool is_eigen_Minus(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_Minus;
}

/**
 * construct Minus node
 */
ir_node *new_bd_eigen_Minus(dbg_info *dbgi, ir_node *block, ir_node *op0);

extern ir_op *op_eigen_Mul;

static inline bool is_eigen_Mul(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_Mul;
}

/**
 * construct Mul node
 */
ir_node *new_bd_eigen_Mul(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1);

extern ir_op *op_eigen_Not;

static inline bool is_eigen_Not(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_Not;
}

/**
 * construct Not node
 */
ir_node *new_bd_eigen_Not(dbg_info *dbgi, ir_node *block, ir_node *op0);

extern ir_op *op_eigen_Or;

static inline bool is_eigen_Or(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_Or;
}

/**
 * construct Or node
 */
ir_node *new_bd_eigen_Or(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1);

extern ir_op *op_eigen_Return;

static inline bool is_eigen_Return(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_Return;
}

/**
 * construct Return node
 */
ir_node *new_bd_eigen_Return(dbg_info *dbgi, ir_node *block, int const arity, ir_node *const *const in, arch_register_req_t const **const in_reqs);

extern ir_op *op_eigen_Shl;

static inline bool is_eigen_Shl(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_Shl;
}

/**
 * construct Shl node
 */
ir_node *new_bd_eigen_Shl(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1);

extern ir_op *op_eigen_Shr;

static inline bool is_eigen_Shr(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_Shr;
}

/**
 * construct Shr node
 */
ir_node *new_bd_eigen_Shr(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1);

extern ir_op *op_eigen_Store;

static inline bool is_eigen_Store(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_Store;
}

/**
 * construct Store node
 */
ir_node *new_bd_eigen_Store(dbg_info *dbgi, ir_node *block, ir_node *mem, ir_node *ptr, ir_node *val);

extern ir_op *op_eigen_Sub;

static inline bool is_eigen_Sub(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_Sub;
}

/**
 * construct Sub node
 */
ir_node *new_bd_eigen_Sub(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1);

extern ir_op *op_eigen_Xor;

static inline bool is_eigen_Xor(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_Xor;
}

/**
 * construct Xor node
 */
ir_node *new_bd_eigen_Xor(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1);

extern ir_op *op_eigen_fAdd;

static inline bool is_eigen_fAdd(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_fAdd;
}

/**
 * construct fAdd node
 */
ir_node *new_bd_eigen_fAdd(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1);

extern ir_op *op_eigen_fConst;

static inline bool is_eigen_fConst(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_fConst;
}

/**
 * construct fConst node
 */
ir_node *new_bd_eigen_fConst(dbg_info *dbgi, ir_node *block);

extern ir_op *op_eigen_fDiv;

static inline bool is_eigen_fDiv(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_fDiv;
}

/**
 * construct fDiv node
 */
ir_node *new_bd_eigen_fDiv(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1);

extern ir_op *op_eigen_fLoad;

static inline bool is_eigen_fLoad(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_fLoad;
}

/**
 * construct fLoad node
 */
ir_node *new_bd_eigen_fLoad(dbg_info *dbgi, ir_node *block, ir_node *mem, ir_node *ptr);

extern ir_op *op_eigen_fMinus;

static inline bool is_eigen_fMinus(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_fMinus;
}

/**
 * construct fMinus node
 */
ir_node *new_bd_eigen_fMinus(dbg_info *dbgi, ir_node *block, ir_node *op0);

extern ir_op *op_eigen_fMul;

static inline bool is_eigen_fMul(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_fMul;
}

/**
 * construct fMul node
 */
ir_node *new_bd_eigen_fMul(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1);

extern ir_op *op_eigen_fStore;

static inline bool is_eigen_fStore(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_fStore;
}

/**
 * construct fStore node
 */
ir_node *new_bd_eigen_fStore(dbg_info *dbgi, ir_node *block, ir_node *mem, ir_node *ptr, ir_node *val);

extern ir_op *op_eigen_fSub;

static inline bool is_eigen_fSub(ir_node const *const n)
{
    return get_irn_op(n) == op_eigen_fSub;
}

/**
 * construct fSub node
 */
ir_node *new_bd_eigen_fSub(dbg_info *dbgi, ir_node *block, ir_node *op0, ir_node *op1);


typedef enum pn_eigen_Load {
    pn_eigen_Load_res = 0,
    pn_eigen_Load_M = 1,
} pn_eigen_Load;

typedef enum n_eigen_Load {
    n_eigen_Load_mem = 0,
    n_eigen_Load_ptr = 1,
} n_eigen_Load;

typedef enum pn_eigen_Return {
    pn_eigen_Return_X = 0,
} pn_eigen_Return;

typedef enum n_eigen_Return {
    n_eigen_Return_mem = 0,
    n_eigen_Return_stack = 1,
    n_eigen_Return_first_result = 2,
} n_eigen_Return;

typedef enum pn_eigen_Store {
    pn_eigen_Store_M = 0,
} pn_eigen_Store;

typedef enum n_eigen_Store {
    n_eigen_Store_mem = 0,
    n_eigen_Store_ptr = 1,
    n_eigen_Store_val = 2,
} n_eigen_Store;

typedef enum pn_eigen_fLoad {
    pn_eigen_fLoad_res = 0,
    pn_eigen_fLoad_M = 1,
} pn_eigen_fLoad;

typedef enum n_eigen_fLoad {
    n_eigen_fLoad_mem = 0,
    n_eigen_fLoad_ptr = 1,
} n_eigen_fLoad;

typedef enum pn_eigen_fStore {
    pn_eigen_fStore_M = 0,
} pn_eigen_fStore;

typedef enum n_eigen_fStore {
    n_eigen_fStore_mem = 0,
    n_eigen_fStore_ptr = 1,
    n_eigen_fStore_val = 2,
} n_eigen_fStore;


#endif
