/*
 * This file is part of cparser.
 * Copyright (C) 2012 Matthias Braun <matze@braunis.de>
 */
#include "symbol_table_t.h"

#include "adt/hash_string.h"
#include "adt/obst.h"
#include "adt/strutil.h"
#include "position.h"
#include "symbol_t.h"

struct obstack symbol_obstack;

static inline
void init_symbol_table_entry(symbol_t *entry, const char *string)
{
	entry->string        = string;
	entry->ID            = T_IDENTIFIER;
	entry->pp_ID         = TP_NULL;
	entry->entity        = NULL;
	entry->pp_definition = NULL;
}

#define HashSet                    symbol_table_t
#define HashSetEntry               symbol_table_hash_entry_t
#define ValueType                  symbol_t*
#define NullValue                  NULL
#define DeletedValue               ((symbol_t*)-1)
#define KeyType                    const char *
#define ConstKeyType               const char *
#define GetKey(value)              (value)->string
#define InitData(this,value,key)   ((void)((value) = (ValueType)obstack_alloc(&symbol_obstack, sizeof(symbol_t)), init_symbol_table_entry((value), key)))
#define Hash(this, key)            hash_string(key)
#define KeysEqual(this,key1,key2)  (streq(key1, key2))
#define SetRangeEmpty(ptr,size)    memset(ptr, 0, (size) * sizeof(symbol_table_hash_entry_t))
#define SCALAR_RETURN

void symbol_table_init_(symbol_table_t *symbol_table);
#define hashset_init            symbol_table_init_
void symbol_table_destroy_(symbol_table_t *symbol_table);
#define hashset_destroy         symbol_table_destroy_
symbol_t *symbol_table_insert_(symbol_table_t *symbol_table, const char *key);
#define hashset_insert          symbol_table_insert_
void symbol_table_iterator_init_(symbol_table_iterator_t *iterator, const symbol_table_t *table);
#define hashset_iterator_init   symbol_table_iterator_init_
#define hashset_iterator_next   symbol_table_iterator_next

#include "adt/hashset.c.h"

static symbol_table_t  symbol_table;

symbol_t *sym_anonymous;

symbol_t *symbol_table_insert(const char *string)
{
	return symbol_table_insert_(&symbol_table, string);
}

void init_symbol_table(void)
{
	obstack_init(&symbol_obstack);
	symbol_table_init_(&symbol_table);
	sym_anonymous = symbol_table_insert("<anonymous>");
}

void exit_symbol_table(void)
{
	symbol_table_destroy_(&symbol_table);
	obstack_free(&symbol_obstack, NULL);
}

void symbol_table_iterator_init(symbol_table_iterator_t *iterator)
{
	symbol_table_iterator_init_(iterator, &symbol_table);
}
