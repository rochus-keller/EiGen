/*
 * This file is part of cparser.
 * Copyright (C) 2012 Matthias Braun <matze@braunis.de>
 */
#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "entity_t.h"
#include "type.h"

/**
 * Initialize parser. Should be called once when the program starts
 */
void init_parser(void);

/**
 * Frees resources occupied by parser. Should be called once before the program
 * exits.
 */
void exit_parser(void);

/**
 * Start parsing a new compilation unit
 */
void start_parsing(void);

/**
 * Parse input. The source of the input is determined by the lexer module
 */
void parse(void);

/**
 * Finish parsing a complete compilation unit and return the AST.
 */
translation_unit_t *finish_parsing(void);

/** set default elf visbility */
void set_default_visibility(elf_visibility_t visibility);

/**
 * Performs automatic type cast as described in §6.3.2.1.
 *
 * @param orig_type  the original type
 */
type_t *automatic_type_conversion(type_t *orig_type, bool type_of_param);

#endif
