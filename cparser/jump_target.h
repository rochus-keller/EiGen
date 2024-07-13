/*
 * This file is part of cparser.
 * Copyright (C) 2012 Christoph Mallon <christoph.mallon@gmx.de>
 */
#ifndef JUMP_TARGET_H
#define JUMP_TARGET_H

#include <libfirm/firm.h>
#include <stdbool.h>

typedef struct jump_target {
	ir_node *block;
	bool     first;
} jump_target;

static inline jump_target init_jump_target(ir_node *const block)
{
	return (jump_target){block, false};
}

void jump_from_block_to_target(jump_target *tgt, ir_node *block);

void jump_to_target(jump_target *tgt);

void add_pred_to_jump_target(jump_target *tgt, ir_node *pred);

ir_node *enter_jump_target(jump_target *tgt);

void enter_immature_jump_target(jump_target *tgt);

#endif
