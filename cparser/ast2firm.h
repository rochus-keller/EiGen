/*
 * This file is part of cparser.
 * Copyright (C) 2012 Matthias Braun <matze@braunis.de>
 */
#ifndef AST2FIRM_H
#define AST2FIRM_H

#include <libfirm/firm.h>

#include "ast/ast.h"
#include "ast/type.h"

void translation_unit_to_firm(translation_unit_t *unit);

void exit_ast2firm(void);

#endif
