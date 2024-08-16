/*
 * This file is part of cparser.
 * Copyright (C) 2012 Matthias Braun <matze@braunis.de>
 */
#ifndef AST2FIRM_H
#define AST2FIRM_H

//#include <libfirm/firm.h>

#include "type_t.h"
#include "entity_t.h"
#include "ast_t.h"

void translation_unit_to_ir(translation_unit_t *unit, FILE *cod_out, const char *source_file);

void exit_ast2ir(void);

#endif
