/*
 * This file is part of libFirm.
 * Copyright (C) 2016 Matthias Braun
 */

/**
 * @file
 * @brief   Internal declarations used by gen_new_nodes.c
 */
#ifndef FIRM_BE_eigen_eigen_NEW_NODES_T_H
#define FIRM_BE_eigen_eigen_NEW_NODES_T_H

#include "eigen_new_nodes.h"

void eigen_dump_node(FILE *F, const ir_node *n, dump_reason_t reason);

void set_eigen_value(ir_node *const node, ir_entity *const entity,
                        ir_tarval *const value);

int eigen_attrs_equal(const ir_node *a, const ir_node *b);

#endif
