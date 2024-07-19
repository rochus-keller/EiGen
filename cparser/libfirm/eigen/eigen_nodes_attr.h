/*
 * This file is part of libFirm.
 * Copyright (C) 2012 University of Karlsruhe.
 */

/**
 * @file
 * @brief   attributes attached to all eigen nodes
 */
#ifndef FIRM_BE_eigen_eigen_NODES_ATTR_H
#define FIRM_BE_eigen_eigen_NODES_ATTR_H

#include "firm_types.h"

typedef struct eigen_attr_t eigen_attr_t;

struct eigen_attr_t
{
	ir_tarval *value;
	ir_entity *entity;
};

#endif
