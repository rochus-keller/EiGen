/*
 * This file is part of cparser.
 * Copyright (C) 2012 Matthias Braun <matze@braunis.de>
 */
/**
 * @file
 * Some notes about the AST printer:
 *  - This is a pretty printer, which prints spaces and newlines independent of
 *    the ones used in the original program.
 *  - The printer is used in case of semantic errors, so it must not attempt
 *    to print or rely on any semantic information in the AST. (e.g. print
 *    the original attribute sequences instead of the parsed declaration
 *    specifiers)
 *  - The AST should be printed as much as possible in its original form. So for
 *    example, hex literals should be printed as hex literals, not decimal
 *    literals, implicit casts added by the semantic checker should not be
 *    printed.
 *    Some aspects here are not perfect:
 *       - String literals appear concatenated.
 *       - Braces used for precedence are not preserved.
 *       - Declarations are not preserved, when a definition has been found.
 */
#include "ast_t.h"

#include <ctype.h>

#include "adt/panic.h"
#include "adt/separator_t.h"
#include "adt/util.h"
#include "constfold.h"
#include "dialect.h"
#include "driver/warning.h"
#include "printer.h"
#include "string_hash.h"
#include "symbol_t.h"
#include "type_hash.h"
#include "type_t.h"
#include "types.h"

struct obstack ast_obstack;
c_dialect_t    dialect;

static int indent;
static int case_indent;

bool print_implicit_casts = false;
bool print_parenthesis = false;

static void print_statement(const statement_t *statement);
static void print_expression_prec(const expression_t *expression, unsigned prec);

void change_indent(int delta)
{
	indent += delta;
	assert(indent >= 0);
}

void print_indent(void)
{
	for (int i = 0; i < indent; ++i)
		print_char('\t');
}

/**
 * Returns 1 if a given precedence level has right-to-left
 * associativity, else 0.
 *
 * @param precedence   the operator precedence
 */
static int right_to_left(unsigned precedence)
{
	switch (precedence) {
	case PREC_ASSIGNMENT:
	case PREC_CONDITIONAL:
	case PREC_UNARY:
		return 1;

	default:
		return 0;
	}
}

/**
 * Return the precedence of an expression given by its kind.
 *
 * @param kind   the expression kind
 */
static unsigned get_expression_precedence(expression_kind_t kind)
{
	static const unsigned prec[] = {
		[EXPR_ERROR]                      = PREC_PRIMARY,
		[EXPR_REFERENCE]                  = PREC_PRIMARY,
		[EXPR_ENUM_CONSTANT]              = PREC_PRIMARY,
		[EXPR_LITERAL_INTEGER]            = PREC_PRIMARY,
		[EXPR_LITERAL_FLOATINGPOINT]      = PREC_PRIMARY,
		[EXPR_LITERAL_CHARACTER]          = PREC_PRIMARY,
		[EXPR_LITERAL_MS_NOOP]            = PREC_PRIMARY,
		[EXPR_STRING_LITERAL]             = PREC_PRIMARY,
		[EXPR_COMPOUND_LITERAL]           = PREC_UNARY,
		[EXPR_CALL]                       = PREC_POSTFIX,
		[EXPR_CONDITIONAL]                = PREC_CONDITIONAL,
		[EXPR_SELECT]                     = PREC_POSTFIX,
		[EXPR_ARRAY_ACCESS]               = PREC_POSTFIX,
		[EXPR_SIZEOF]                     = PREC_UNARY,
		[EXPR_CLASSIFY_TYPE]              = PREC_UNARY,
		[EXPR_ALIGNOF]                    = PREC_UNARY,

		[EXPR_FUNCNAME]                   = PREC_PRIMARY,
		[EXPR_BUILTIN_CONSTANT_P]         = PREC_PRIMARY,
		[EXPR_BUILTIN_TYPES_COMPATIBLE_P] = PREC_PRIMARY,
		[EXPR_OFFSETOF]                   = PREC_PRIMARY,
		[EXPR_VA_START]                   = PREC_PRIMARY,
		[EXPR_VA_ARG]                     = PREC_PRIMARY,
		[EXPR_VA_COPY]                    = PREC_PRIMARY,
		[EXPR_STATEMENT]                  = PREC_PRIMARY,
		[EXPR_LABEL_ADDRESS]              = PREC_PRIMARY,

		[EXPR_UNARY_NEGATE]               = PREC_UNARY,
		[EXPR_UNARY_PLUS]                 = PREC_UNARY,
		[EXPR_UNARY_COMPLEMENT]           = PREC_UNARY,
		[EXPR_UNARY_NOT]                  = PREC_UNARY,
		[EXPR_UNARY_DEREFERENCE]          = PREC_UNARY,
		[EXPR_UNARY_TAKE_ADDRESS]         = PREC_UNARY,
		[EXPR_UNARY_POSTFIX_INCREMENT]    = PREC_POSTFIX,
		[EXPR_UNARY_POSTFIX_DECREMENT]    = PREC_POSTFIX,
		[EXPR_UNARY_PREFIX_INCREMENT]     = PREC_UNARY,
		[EXPR_UNARY_PREFIX_DECREMENT]     = PREC_UNARY,
		[EXPR_UNARY_CAST]                 = PREC_UNARY,
		[EXPR_UNARY_ASSUME]               = PREC_PRIMARY,
		[EXPR_UNARY_DELETE]               = PREC_UNARY,
		[EXPR_UNARY_DELETE_ARRAY]         = PREC_UNARY,
		[EXPR_UNARY_THROW]                = PREC_ASSIGNMENT,
		[EXPR_UNARY_IMAG]                 = PREC_UNARY,
		[EXPR_UNARY_REAL]                 = PREC_UNARY,

		[EXPR_BINARY_ADD]                 = PREC_ADDITIVE,
		[EXPR_BINARY_SUB]                 = PREC_ADDITIVE,
		[EXPR_BINARY_MUL]                 = PREC_MULTIPLICATIVE,
		[EXPR_BINARY_DIV]                 = PREC_MULTIPLICATIVE,
		[EXPR_BINARY_MOD]                 = PREC_MULTIPLICATIVE,
		[EXPR_BINARY_EQUAL]               = PREC_EQUALITY,
		[EXPR_BINARY_NOTEQUAL]            = PREC_EQUALITY,
		[EXPR_BINARY_LESS]                = PREC_RELATIONAL,
		[EXPR_BINARY_LESSEQUAL]           = PREC_RELATIONAL,
		[EXPR_BINARY_GREATER]             = PREC_RELATIONAL,
		[EXPR_BINARY_GREATEREQUAL]        = PREC_RELATIONAL,
		[EXPR_BINARY_BITWISE_AND]         = PREC_AND,
		[EXPR_BINARY_BITWISE_OR]          = PREC_OR,
		[EXPR_BINARY_BITWISE_XOR]         = PREC_XOR,
		[EXPR_BINARY_LOGICAL_AND]         = PREC_LOGICAL_AND,
		[EXPR_BINARY_LOGICAL_OR]          = PREC_LOGICAL_OR,
		[EXPR_BINARY_SHIFTLEFT]           = PREC_SHIFT,
		[EXPR_BINARY_SHIFTRIGHT]          = PREC_SHIFT,
		[EXPR_BINARY_ASSIGN]              = PREC_ASSIGNMENT,
		[EXPR_BINARY_MUL_ASSIGN]          = PREC_ASSIGNMENT,
		[EXPR_BINARY_DIV_ASSIGN]          = PREC_ASSIGNMENT,
		[EXPR_BINARY_MOD_ASSIGN]          = PREC_ASSIGNMENT,
		[EXPR_BINARY_ADD_ASSIGN]          = PREC_ASSIGNMENT,
		[EXPR_BINARY_SUB_ASSIGN]          = PREC_ASSIGNMENT,
		[EXPR_BINARY_SHIFTLEFT_ASSIGN]    = PREC_ASSIGNMENT,
		[EXPR_BINARY_SHIFTRIGHT_ASSIGN]   = PREC_ASSIGNMENT,
		[EXPR_BINARY_BITWISE_AND_ASSIGN]  = PREC_ASSIGNMENT,
		[EXPR_BINARY_BITWISE_XOR_ASSIGN]  = PREC_ASSIGNMENT,
		[EXPR_BINARY_BITWISE_OR_ASSIGN]   = PREC_ASSIGNMENT,
		[EXPR_BINARY_COMMA]               = PREC_EXPRESSION,

		[EXPR_BINARY_ISGREATER]           = PREC_PRIMARY,
		[EXPR_BINARY_ISGREATEREQUAL]      = PREC_PRIMARY,
		[EXPR_BINARY_ISLESS]              = PREC_PRIMARY,
		[EXPR_BINARY_ISLESSEQUAL]         = PREC_PRIMARY,
		[EXPR_BINARY_ISLESSGREATER]       = PREC_PRIMARY,
		[EXPR_BINARY_ISUNORDERED]         = PREC_PRIMARY
	};
	assert((size_t)kind < ARRAY_SIZE(prec));
	unsigned res = prec[kind];

	assert(res != PREC_BOTTOM);
	return res;
}

/**
 * Print a quoted string constant.
 *
 * @param string  the string constant
 * @param border  the border char
 */
static void print_quoted_string(const string_t *const string, char border)
{
	print_string(get_string_encoding_prefix(string->encoding));

	print_char(border);
	const char *end = string->begin + string->size;
	for (const char *c = string->begin; c != end; ++c) {
		const char tc = *c;
		if (tc == border) {
			print_char('\\');
		}
		switch (tc) {
		case '\\': print_string("\\\\"); break;
		case '\a': print_string("\\a"); break;
		case '\b': print_string("\\b"); break;
		case '\f': print_string("\\f"); break;
		case '\n': print_string("\\n"); break;
		case '\r': print_string("\\r"); break;
		case '\t': print_string("\\t"); break;
		case '\v': print_string("\\v"); break;
		case '\?': print_string("\\?"); break;
		case 27:
			if (dialect.gnu) {
				print_string("\\e"); break;
			}
			/* FALLTHROUGH */
		default:
			if ((unsigned)tc < 0x80 && !isprint((unsigned char)tc)) {
				int const width = '0' <= c[1] && c[1] < '8' ? 3 : 0;
				print_format("\\%0*o", width, (unsigned)tc);
			} else {
				print_char(tc);
			}
			break;
		}
	}
	print_char(border);
}

static void print_string_literal(string_literal_expression_t const *const literal, char const delimiter)
{
	print_quoted_string(literal->value, delimiter);
}

static void print_literal(const literal_expression_t *literal)
{
	switch (literal->base.kind) {
	case EXPR_LITERAL_MS_NOOP:
		print_string("__noop");
		return;

	case EXPR_LITERAL_BOOLEAN:
	case EXPR_LITERAL_FLOATINGPOINT:
	case EXPR_LITERAL_INTEGER:
		print_string(literal->value->begin);
		return;

	default:
		break;
	}
	print_string("INVALID LITERAL KIND");
}

/**
 * Prints a predefined symbol.
 */
static void print_funcname(const funcname_expression_t *funcname)
{
	const char *s = "";
	switch (funcname->kind) {
	case FUNCNAME_FUNCTION:        s = dialect.c99 ? "__func__" : "__FUNCTION__"; break;
	case FUNCNAME_PRETTY_FUNCTION: s = "__PRETTY_FUNCTION__"; break;
	case FUNCNAME_FUNCSIG:         s = "__FUNCSIG__"; break;
	case FUNCNAME_FUNCDNAME:       s = "__FUNCDNAME__"; break;
	}
	print_string(s);
}

static void print_compound_literal(
		const compound_literal_expression_t *expression)
{
	print_char('(');
	print_type(expression->type);
	print_char(')');
	print_initializer(expression->initializer);
}

static void print_assignment_expression(const expression_t *const expr)
{
	print_expression_prec(expr, PREC_ASSIGNMENT);
}

/**
 * Prints a call expression.
 *
 * @param call  the call expression
 */
static void print_call_expression(const call_expression_t *call)
{
	print_expression_prec(call->function, PREC_POSTFIX);
	print_char('(');
	separator_t sep = { "", ", " };
	for (call_argument_t const *arg = call->arguments; arg; arg = arg->next) {
		print_string(sep_next(&sep));
		print_assignment_expression(arg->expression);
	}
	print_char(')');
}

/**
 * Prints a binary expression.
 *
 * @param binexpr   the binary expression
 */
static void print_binary_expression(const binary_expression_t *binexpr)
{
	unsigned prec = get_expression_precedence(binexpr->base.kind);
	int      r2l  = right_to_left(prec);

	print_expression_prec(binexpr->left, prec + r2l);
	char const* op;
	switch (binexpr->base.kind) {
	case EXPR_BINARY_COMMA:              op = ", ";    break;
	case EXPR_BINARY_ASSIGN:             op = " = ";   break;
	case EXPR_BINARY_ADD:                op = " + ";   break;
	case EXPR_BINARY_SUB:                op = " - ";   break;
	case EXPR_BINARY_MUL:                op = " * ";   break;
	case EXPR_BINARY_MOD:                op = " % ";   break;
	case EXPR_BINARY_DIV:                op = " / ";   break;
	case EXPR_BINARY_BITWISE_OR:         op = " | ";   break;
	case EXPR_BINARY_BITWISE_AND:        op = " & ";   break;
	case EXPR_BINARY_BITWISE_XOR:        op = " ^ ";   break;
	case EXPR_BINARY_LOGICAL_OR:         op = " || ";  break;
	case EXPR_BINARY_LOGICAL_AND:        op = " && ";  break;
	case EXPR_BINARY_NOTEQUAL:           op = " != ";  break;
	case EXPR_BINARY_EQUAL:              op = " == ";  break;
	case EXPR_BINARY_LESS:               op = " < ";   break;
	case EXPR_BINARY_LESSEQUAL:          op = " <= ";  break;
	case EXPR_BINARY_GREATER:            op = " > ";   break;
	case EXPR_BINARY_GREATEREQUAL:       op = " >= ";  break;
	case EXPR_BINARY_SHIFTLEFT:          op = " << ";  break;
	case EXPR_BINARY_SHIFTRIGHT:         op = " >> ";  break;

	case EXPR_BINARY_ADD_ASSIGN:         op = " += ";  break;
	case EXPR_BINARY_SUB_ASSIGN:         op = " -= ";  break;
	case EXPR_BINARY_MUL_ASSIGN:         op = " *= ";  break;
	case EXPR_BINARY_MOD_ASSIGN:         op = " %= ";  break;
	case EXPR_BINARY_DIV_ASSIGN:         op = " /= ";  break;
	case EXPR_BINARY_BITWISE_OR_ASSIGN:  op = " |= ";  break;
	case EXPR_BINARY_BITWISE_AND_ASSIGN: op = " &= ";  break;
	case EXPR_BINARY_BITWISE_XOR_ASSIGN: op = " ^= ";  break;
	case EXPR_BINARY_SHIFTLEFT_ASSIGN:   op = " <<= "; break;
	case EXPR_BINARY_SHIFTRIGHT_ASSIGN:  op = " >>= "; break;
	default: panic("invalid binexpression found");
	}
	print_string(op);
	print_expression_prec(binexpr->right, prec + 1 - r2l);
}

/**
 * Prints a unary expression.
 *
 * @param unexpr   the unary expression
 */
static void print_unary_expression(const unary_expression_t *unexpr)
{
	unsigned prec = get_expression_precedence(unexpr->base.kind);
	switch (unexpr->base.kind) {
	case EXPR_UNARY_NEGATE:           print_char  ('-' );         break;
	case EXPR_UNARY_PLUS:             print_char  ('+' );         break;
	case EXPR_UNARY_NOT:              print_char  ('!' );         break;
	case EXPR_UNARY_COMPLEMENT:       print_char  ('~' );         break;
	case EXPR_UNARY_PREFIX_INCREMENT: print_string("++");         break;
	case EXPR_UNARY_PREFIX_DECREMENT: print_string("--");         break;
	case EXPR_UNARY_DEREFERENCE:      print_char  ('*' );         break;
	case EXPR_UNARY_TAKE_ADDRESS:     print_char  ('&' );         break;
	case EXPR_UNARY_DELETE:           print_string("delete ");    break;
	case EXPR_UNARY_DELETE_ARRAY:     print_string("delete [] "); break;
	case EXPR_UNARY_REAL:             print_string("__real__ ");  break;
	case EXPR_UNARY_IMAG:             print_string("__imag__ ");  break;

	case EXPR_UNARY_POSTFIX_INCREMENT:
		print_expression_prec(unexpr->value, prec);
		print_string("++");
		return;
	case EXPR_UNARY_POSTFIX_DECREMENT:
		print_expression_prec(unexpr->value, prec);
		print_string("--");
		return;
	case EXPR_UNARY_CAST:
		print_char('(');
		print_type(unexpr->base.type);
		print_char(')');
		break;
	case EXPR_UNARY_ASSUME:
		print_string("__assume(");
		print_assignment_expression(unexpr->value);
		print_char(')');
		return;
	case EXPR_UNARY_THROW:
		if (unexpr->value == NULL) {
			print_string("throw");
			return;
		}
		print_string("throw ");
		break;

	default:
		panic("invalid unary expression found");
	}
	print_expression_prec(unexpr->value, prec);
}

/**
 * Prints a reference expression.
 *
 * @param ref   the reference expression
 */
static void print_reference_expression(const reference_expression_t *ref)
{
	print_string(ref->entity->base.symbol->string);
}

/**
 * Prints a label address expression.
 *
 * @param ref   the reference expression
 */
static void print_label_address_expression(const label_address_expression_t *le)
{
	print_format("&&%s", le->label->base.symbol->string);
}

/**
 * Prints an array expression.
 *
 * @param expression   the array expression
 */
static void print_array_expression(const array_access_expression_t *expression)
{
	if (!expression->flipped) {
		print_expression_prec(expression->array_ref, PREC_POSTFIX);
		print_char('[');
		print_expression(expression->index);
		print_char(']');
	} else {
		print_expression_prec(expression->index, PREC_POSTFIX);
		print_char('[');
		print_expression(expression->array_ref);
		print_char(']');
	}
}

/**
 * Prints a typeproperty expression (sizeof or __alignof__).
 *
 * @param expression   the type property expression
 */
static void print_typeprop_expression(const typeprop_expression_t *expression)
{
	switch (expression->base.kind) {
	case EXPR_SIZEOF:  print_string("sizeof");                                   break;
	case EXPR_ALIGNOF: print_string(dialect.c11 ? "_Alignof" : "__alignof__"); break;
	default:           panic("invalid typeprop kind");
	}
	if (expression->tp_expression != NULL) {
		/* PREC_TOP: always print the '()' here, sizeof x is right but unusual */
		print_expression_prec(expression->tp_expression, PREC_TOP);
	} else {
		print_char('(');
		print_type(expression->type);
		print_char(')');
	}
}

/**
 * Prints a builtin constant expression.
 *
 * @param expression   the builtin constant expression
 */
static void print_builtin_constant(const builtin_constant_expression_t *expression)
{
	print_string("__builtin_constant_p(");
	print_assignment_expression(expression->value);
	print_char(')');
}

/**
 * Prints a builtin types compatible expression.
 *
 * @param expression   the builtin types compatible expression
 */
static void print_builtin_types_compatible(
		const builtin_types_compatible_expression_t *expression)
{
	print_string("__builtin_types_compatible_p(");
	print_type(expression->left);
	print_string(", ");
	print_type(expression->right);
	print_char(')');
}

/**
 * Prints a conditional expression.
 *
 * @param expression   the conditional expression
 */
static void print_conditional(const conditional_expression_t *expression)
{
	print_expression_prec(expression->condition, PREC_LOGICAL_OR);
	if (expression->true_expression != NULL) {
		print_string(" ? ");
		print_expression_prec(expression->true_expression, PREC_EXPRESSION);
		print_string(" : ");
	} else {
		print_string(" ?: ");
	}
	precedence_t prec = dialect.cpp ? PREC_ASSIGNMENT : PREC_CONDITIONAL;
	print_expression_prec(expression->false_expression, prec);
}

/**
 * Prints a va_start expression.
 *
 * @param expression   the va_start expression
 */
static void print_va_start(const va_start_expression_t *const expression)
{
	print_string("__builtin_va_start(");
	print_assignment_expression(expression->ap);
	print_string(", ");
	print_assignment_expression(expression->parameter);
	print_char(')');
}

/**
 * Prints a va_arg expression.
 *
 * @param expression   the va_arg expression
 */
static void print_va_arg(const va_arg_expression_t *expression)
{
	print_string("__builtin_va_arg(");
	print_assignment_expression(expression->ap);
	print_string(", ");
	print_type(expression->base.type);
	print_char(')');
}

/**
 * Prints a va_copy expression.
 *
 * @param expression   the va_copy expression
 */
static void print_va_copy(const va_copy_expression_t *expression)
{
	print_string("__builtin_va_copy(");
	print_assignment_expression(expression->dst);
	print_string(", ");
	print_assignment_expression(expression->src);
	print_char(')');
}

/**
 * Prints a select expression (. or ->).
 *
 * @param expression   the select expression
 */
static void print_select(const select_expression_t *expression)
{
	print_expression_prec(expression->compound, PREC_POSTFIX);
	/* do not print anything for anonymous struct/union selects
	 * FIXME: if the anonymous select was a '->' this will print '.'
	 */
	if (expression->compound_entry->base.symbol == NULL)
		return;

	if (is_type_pointer(skip_typeref(expression->compound->base.type))) {
		print_string("->");
	} else {
		print_char('.');
	}
	print_string(expression->compound_entry->base.symbol->string);
}

/**
 * Prints a type classify expression.
 *
 * @param expr   the type classify expression
 */
static void print_classify_type_expression(
	const classify_type_expression_t *const expr)
{
	print_string("__builtin_classify_type(");
	print_assignment_expression(expr->type_expression);
	print_char(')');
}

/**
 * Prints a designator.
 *
 * @param designator  the designator
 */
static void print_designator(const designator_t *designator)
{
	for ( ; designator != NULL; designator = designator->next) {
		if (designator->symbol == NULL) {
			print_char('[');
			print_expression(designator->array_index);
			if (designator->range_last) {
				print_string(" ... ");
				print_expression(designator->range_last);
			}
			print_char(']');
		} else {
			print_char('.');
			print_string(designator->symbol->string);
		}
	}
}

/**
 * Prints an offsetof expression.
 *
 * @param expression   the offset expression
 */
static void print_offsetof_expression(const offsetof_expression_t *expression)
{
	print_string("__builtin_offsetof(");
	print_type(expression->type);
	print_char(',');
	print_designator(expression->designator);
	print_char(')');
}

/**
 * Prints a statement expression.
 *
 * @param expression   the statement expression
 */
static void print_statement_expression(const statement_expression_t *expression)
{
	print_char('(');
	print_statement(expression->statement);
	print_char(')');
}

static bool needs_parentheses(expression_t const *const expr, unsigned const top_prec)
{
	if (expr->base.parenthesized)
		return true;

	if (top_prec > get_expression_precedence(expr->kind))
		return true;

	if (print_parenthesis && top_prec != PREC_BOTTOM) {
		switch (expr->kind) {
		case EXPR_ENUM_CONSTANT:
		case EXPR_FUNCNAME:
		case EXPR_LITERAL_CASES:
		case EXPR_LITERAL_CHARACTER:
		case EXPR_REFERENCE:
		case EXPR_STRING_LITERAL:
			/* Do not print () around subexpressions consisting of a single token. */
			return false;

		default:
			return true;
		}
	}

	return false;
}

/**
 * Prints an expression with parenthesis if needed.
 *
 * @param expression  the expression to print
 * @param top_prec    the precedence of the user of this expression.
 */
static void print_expression_prec(expression_t const *expr, unsigned const top_prec)
{
	if (expr->kind == EXPR_UNARY_CAST && expr->base.implicit && !print_implicit_casts) {
		expr = expr->unary.value;
	}

	bool const parenthesized = needs_parentheses(expr, top_prec);

	if (parenthesized)
		print_char('(');
	switch (expr->kind) {
	case EXPR_ALIGNOF:
	case EXPR_SIZEOF:                     print_typeprop_expression(     &expr->typeprop);                 break;
	case EXPR_ARRAY_ACCESS:               print_array_expression(        &expr->array_access);             break;
	case EXPR_BINARY_CASES:               print_binary_expression(       &expr->binary);                   break;
	case EXPR_BUILTIN_CONSTANT_P:         print_builtin_constant(        &expr->builtin_constant);         break;
	case EXPR_BUILTIN_TYPES_COMPATIBLE_P: print_builtin_types_compatible(&expr->builtin_types_compatible); break;
	case EXPR_CALL:                       print_call_expression(         &expr->call);                     break;
	case EXPR_CLASSIFY_TYPE:              print_classify_type_expression(&expr->classify_type);            break;
	case EXPR_COMPOUND_LITERAL:           print_compound_literal(        &expr->compound_literal);         break;
	case EXPR_CONDITIONAL:                print_conditional(             &expr->conditional);              break;
	case EXPR_ERROR:                      print_string("$error$");                                         break;
	case EXPR_FUNCNAME:                   print_funcname(                &expr->funcname);                 break;
	case EXPR_LABEL_ADDRESS:              print_label_address_expression(&expr->label_address);            break;
	case EXPR_LITERAL_CASES:              print_literal(                 &expr->literal);                  break;
	case EXPR_LITERAL_CHARACTER:          print_string_literal(          &expr->string_literal, '\'');     break;
	case EXPR_OFFSETOF:                   print_offsetof_expression(     &expr->offsetofe);                break;
	case EXPR_REFERENCE:
	case EXPR_ENUM_CONSTANT:              print_reference_expression(    &expr->reference);                break;
	case EXPR_SELECT:                     print_select(                  &expr->select);                   break;
	case EXPR_STATEMENT:                  print_statement_expression(    &expr->statement);                break;
	case EXPR_STRING_LITERAL:             print_string_literal(          &expr->string_literal, '"');      break;
	case EXPR_UNARY_CASES:                print_unary_expression(        &expr->unary);                    break;
	case EXPR_VA_ARG:                     print_va_arg(                  &expr->va_arge);                  break;
	case EXPR_VA_COPY:                    print_va_copy(                 &expr->va_copye);                 break;
	case EXPR_VA_START:                   print_va_start(                &expr->va_starte);                break;
	}
	if (parenthesized)
		print_char(')');
}

static void print_indented_statement(statement_t const *const stmt)
{
	switch (stmt->kind) {
	case STATEMENT_LABEL:
		break;

	case STATEMENT_CASE_LABEL:
		for (int i = 0; i != case_indent; ++i)
			print_char('\t');
		break;

	default:
		print_indent();
		break;
	}
	print_statement(stmt);
}

/**
 * Print an compound statement.
 *
 * @param block  the compound statement
 */
static void print_compound_statement(const compound_statement_t *block)
{
	print_string("{\n");
	++indent;

	for (statement_t const *stmt = block->statements; stmt; stmt = stmt->base.next) {
		print_indented_statement(stmt);
		print_char('\n');
	}

	--indent;
	print_indent();
	print_char('}');
}

/**
 * Print a return statement.
 *
 * @param statement  the return statement
 */
static void print_return_statement(const return_statement_t *statement)
{
	expression_t const *const val = statement->value;
	if (val != NULL) {
		print_string("return ");
		print_expression(val);
		print_char(';');
	} else {
		print_string("return;");
	}
}

/**
 * Print an expression statement.
 *
 * @param statement  the expression statement
 */
static void print_expression_statement(const expression_statement_t *statement)
{
	print_expression(statement->expression);
	print_char(';');
}

/**
 * Print a computed goto statement.
 *
 * @param statement  the computed goto statement
 */
static void print_computed_goto_statement(computed_goto_statement_t const *const stmt)
{
	print_string("goto *");
	print_expression(stmt->expression);
	print_char(';');
}

/**
 * Print a goto statement.
 *
 * @param statement  the goto statement
 */
static void print_goto_statement(const goto_statement_t *statement)
{
	print_string("goto ");
	print_string(statement->label->base.symbol->string);
	print_char(';');
}

/**
 * Print a label statement.
 *
 * @param statement  the label statement
 */
static void print_label_statement(const label_statement_t *statement)
{
	print_format("%s:\n", statement->label->base.symbol->string);
	print_indented_statement(statement->statement);
}

static void print_inner_statement(statement_t const *const stmt)
{
	if (stmt->kind == STATEMENT_COMPOUND) {
		print_char(' ');
		print_compound_statement(&stmt->compound);
	} else {
		print_char('\n');
		++indent;
		print_indented_statement(stmt);
		--indent;
	}
}

static void print_after_inner_statement(statement_t const *const stmt)
{
	if (stmt->kind == STATEMENT_COMPOUND) {
		print_char(' ');
	} else {
		print_char('\n');
		print_indent();
	}
}

/**
 * Print an if statement.
 *
 * @param statement  the if statement
 */
static void print_if_statement(const if_statement_t *statement)
{
	print_string("if (");
	print_expression(statement->condition);
	print_char(')');
	print_inner_statement(statement->true_statement);

	statement_t const *const f = statement->false_statement;
	if (f) {
		print_after_inner_statement(statement->true_statement);
		print_string("else");
		if (f->kind == STATEMENT_IF) {
			print_char(' ');
			print_if_statement(&f->ifs);
		} else {
			print_inner_statement(f);
		}
	}
}

/**
 * Print a switch statement.
 *
 * @param statement  the switch statement
 */
static void print_switch_statement(const switch_statement_t *statement)
{
	int const old_case_indent = case_indent;
	case_indent = indent;

	print_string("switch (");
	print_expression(statement->expression);
	print_char(')');
	print_inner_statement(statement->body);

	case_indent = old_case_indent;
}

/**
 * Print a case label (including the default label).
 *
 * @param statement  the case label statement
 */
static void print_case_label(const case_label_statement_t *statement)
{
	if (statement->expression == NULL) {
		print_string("default:\n");
	} else {
		print_string("case ");
		print_expression(statement->expression);
		if (statement->end_range != NULL) {
			print_string(" ... ");
			print_expression(statement->end_range);
		}
		print_string(":\n");
	}
	print_indented_statement(statement->statement);
}

/**
 * returns true if the entity is a compiler generated one and has no real
 * correspondence in the source file
 */
static bool is_generated_entity(const entity_t *entity)
{
	if (is_declaration(entity))
		return entity->declaration.implicit;

	return false;
}

/**
 * Print a declaration statement.
 *
 * @param statement   the statement
 */
static void print_declaration_statement(
		const declaration_statement_t *statement)
{
	bool first = true;
	entity_t *entity = statement->declarations_begin;
	if (entity == NULL) {
		print_string("/* empty declaration statement */");
		return;
	}

	entity_t *const end = statement->declarations_end->base.next;
	for (; entity != end; entity = entity->base.next) {
		if (entity->kind == ENTITY_ENUM_VALUE)
			continue;
		if (is_generated_entity(entity))
			continue;

		if (!first) {
			print_char('\n');
			print_indent();
		} else {
			first = false;
		}

		print_entity(entity);
	}
}

/**
 * Print a do-while statement.
 *
 * @param statement   the statement
 */
static void print_do_while_statement(const do_while_statement_t *statement)
{
	print_string("do");
	print_inner_statement(statement->body);
	print_after_inner_statement(statement->body);
	print_string("while (");
	print_expression(statement->condition);
	print_string(");");
}

static void print_declaration(entity_t const *entity);

/**
 * Print a for statement.
 *
 * @param statement   the statement
 */
static void print_for_statement(const for_statement_t *statement)
{
	if (statement->initialisation || statement->scope.first_entity
	 || !statement->condition || statement->step) {
		print_string("for (");
		if (statement->initialisation != NULL) {
			print_expression(statement->initialisation);
			print_char(';');
		} else {
			for (entity_t const *entity = statement->scope.first_entity;
			     entity != NULL; entity = entity->base.next) {
				if (is_generated_entity(entity))
					continue;
				/* FIXME display of multiple declarations is wrong */
				print_declaration(entity);
			}
		}
		if (statement->condition != NULL) {
			print_char(' ');
			print_expression(statement->condition);
		}
		print_char(';');
		if (statement->step != NULL) {
			print_char(' ');
			print_expression(statement->step);
		}
	} else {
		print_string("while (");
		print_expression(statement->condition);
	}
	print_char(')');
	print_inner_statement(statement->body);
}

/**
 * Print assembler arguments.
 *
 * @param arguments   the arguments
 */
static void print_asm_arguments(entity_t const *const arguments)
{
	print_string(" :");
	separator_t sep = { " ", ", " };
	for (entity_t const *i = arguments; i; i = i->base.next) {
		if (i->kind != ENTITY_ASM_ARGUMENT) {
			print_string("invalid");
			continue;
		}

		print_string(sep_next(&sep));
		symbol_t *symbol = i->base.symbol;
		if (symbol != NULL)
			print_format("[%s] ", symbol->string);
		print_quoted_string(i->asm_argument.constraints, '"');
		print_string(" (");
		print_expression(i->asm_argument.expression);
		print_char(')');
	}
}

/**
 * Print assembler clobbers.
 *
 * @param clobbers   the clobbers
 */
static void print_asm_clobbers(asm_clobber_t const *const clobbers)
{
	print_string(" :");
	separator_t sep = { " ", ", " };
	for (asm_clobber_t const *i = clobbers; i; i = i->next) {
		print_string(sep_next(&sep));
		print_quoted_string(i->clobber, '"');
	}
}

static void print_asm_labels(entity_t const *const labels)
{
	print_string(" :");
	separator_t sep = { " ", ", " };
	for (entity_t const *i = labels; i; i = i->base.next) {
		if (i->kind != ENTITY_ASM_LABEL) {
			print_string("invalid");
			continue;
		}

		print_string(sep_next(&sep));
		print_string(i->base.symbol->string);
	}
}

/**
 * Print an assembler statement.
 *
 * @param stmt   the statement
 */
static void print_asm_statement(asm_statement_t const *const stmt)
{
	print_string("asm");
	if (stmt->is_volatile) print_string(" volatile");
	if (stmt->labels)      print_string(" goto");
	print_char('(');
	print_quoted_string(stmt->asm_text, '"');

	unsigned const n =
		stmt->labels        ? 4 :
		stmt->clobbers      ? 3 :
		stmt->inputs        ? 2 :
		stmt->has_arguments ? 1 :
		0;
	if (n >= 1) print_asm_arguments(stmt->outputs);
	if (n >= 2) print_asm_arguments(stmt->inputs);
	if (n >= 3) print_asm_clobbers( stmt->clobbers);
	if (n >= 4) print_asm_labels(   stmt->labels);

	print_string(");");
}

/**
 * Print a statement.
 *
 * @param statement   the statement
 */
void print_statement(statement_t const *const stmt)
{
	switch (stmt->kind) {
	case STATEMENT_ASM:           print_asm_statement(          &stmt->asms);          break;
	case STATEMENT_BREAK:         print_string("break;");                              break;
	case STATEMENT_CASE_LABEL:    print_case_label(             &stmt->case_label);    break;
	case STATEMENT_COMPOUND:      print_compound_statement(     &stmt->compound);      break;
	case STATEMENT_COMPUTED_GOTO: print_computed_goto_statement(&stmt->computed_goto); break;
	case STATEMENT_CONTINUE:      print_string("continue;");                           break;
	case STATEMENT_DECLARATION:   print_declaration_statement(  &stmt->declaration);   break;
	case STATEMENT_DO_WHILE:      print_do_while_statement(     &stmt->do_while);      break;
	case STATEMENT_EMPTY:         print_char(';');                                     break;
	case STATEMENT_ERROR:         print_string("$error statement$");                   break;
	case STATEMENT_EXPRESSION:    print_expression_statement(   &stmt->expression);    break;
	case STATEMENT_FOR:           print_for_statement(          &stmt->fors);          break;
	case STATEMENT_GOTO:          print_goto_statement(         &stmt->gotos);         break;
	case STATEMENT_IF:            print_if_statement(           &stmt->ifs);           break;
	case STATEMENT_LABEL:         print_label_statement(        &stmt->label);         break;
	case STATEMENT_RETURN:        print_return_statement(       &stmt->returns);       break;
	case STATEMENT_SWITCH:        print_switch_statement(       &stmt->switchs);       break;
	}
}

/**
 * Print a storage class.
 *
 * @param storage_class   the storage class
 */
static void print_storage_class(storage_class_t storage_class)
{
	switch (storage_class) {
	case STORAGE_CLASS_NONE:     return;
	case STORAGE_CLASS_TYPEDEF:  print_string("typedef ");  return;
	case STORAGE_CLASS_EXTERN:   print_string("extern ");   return;
	case STORAGE_CLASS_STATIC:   print_string("static ");   return;
	case STORAGE_CLASS_AUTO:     print_string("auto ");     return;
	case STORAGE_CLASS_REGISTER: print_string("register "); return;
	}
	panic("invalid storage class");
}

/**
 * Print an initializer.
 *
 * @param initializer  the initializer
 */
void print_initializer(const initializer_t *initializer)
{
	if (initializer == NULL) {
		print_string("{}");
		return;
	}

	switch (initializer->kind) {
	case INITIALIZER_STRING:
	case INITIALIZER_VALUE:
		print_assignment_expression(initializer->value.value);
		return;

	case INITIALIZER_LIST: {
		print_string("{ ");
		const initializer_list_t *list = &initializer->list;

		for (size_t i = 0 ; i < list->len; ++i) {
			const initializer_t *sub_init = list->initializers[i];
			print_initializer(list->initializers[i]);
			if (i < list->len-1) {
				if (sub_init == NULL || sub_init->kind != INITIALIZER_DESIGNATOR)
					print_string(", ");
			}
		}
		print_string(" }");
		return;
	}

	case INITIALIZER_DESIGNATOR:
		print_designator(initializer->designator.designator);
		print_string(" = ");
		return;
	}

	panic("invalid initializer kind found");
}

#if 0
/**
 * Print microsoft extended declaration modifiers.
 */
static void print_ms_modifiers(const declaration_t *declaration)
{
	decl_modifiers_t modifiers = declaration->modifiers;

	separator_t sep = { "__declspec(", ", " };

	if (declaration->base.kind == ENTITY_VARIABLE) {
		variable_t *variable = (variable_t*)declaration;
		if (variable->alignment != 0
		    || variable->get_property_sym != NULL
		    || variable->put_property_sym != NULL) {
			if (variable->alignment != 0) {
				print_format("%salign(%u)", sep_next(&sep), variable->alignment);
			}
			if (variable->get_property_sym != NULL
			    || variable->put_property_sym != NULL) {
				char *comma = "";
				print_format("%sproperty(", sep_next(&sep));
				if (variable->get_property_sym != NULL) {
					print_format("get=%s", variable->get_property_sym->string);
					comma = ", ";
				}
				if (variable->put_property_sym != NULL)
					print_format("%sput=%s", comma, variable->put_property_sym->string);
				print_char(')');
			}
		}
	}

	/* DM_FORCEINLINE handled outside. */
	if ((modifiers & ~DM_FORCEINLINE) != 0) {
		if (modifiers & DM_DLLIMPORT) {
			print_format("%sdllimport", sep_next(&sep));
		}
		if (modifiers & DM_DLLEXPORT) {
			print_format("%sdllexport", sep_next(&sep));
		}
		if (modifiers & DM_THREAD) {
			print_format("%sthread", sep_next(&sep));
		}
		if (modifiers & DM_NAKED) {
			print_format("%snaked", sep_next(&sep));
		}
		if (modifiers & DM_THREAD) {
			print_format("%sthread", sep_next(&sep));
		}
		if (modifiers & DM_SELECTANY) {
			print_format("%sselectany", sep_next(&sep));
		}
		if (modifiers & DM_NOTHROW) {
			print_format("%snothrow", sep_next(&sep));
		}
		if (modifiers & DM_NORETURN) {
			print_format("%snoreturn", sep_next(&sep));
		}
		if (modifiers & DM_NOINLINE) {
			print_format("%snoinline", sep_next(&sep));
		}
		if (modifiers & DM_DEPRECATED) {
			print_format("%sdeprecated", sep_next(&sep));
			if (declaration->deprecated_string != NULL)
				print_format("(\"%s\")",
				        declaration->deprecated_string);
		}
		if (modifiers & DM_RESTRICT) {
			print_format("%srestrict", sep_next(&sep));
		}
		if (modifiers & DM_NOALIAS) {
			print_format("%snoalias", sep_next(&sep));
		}
	}

	if (!sep_at_first(&sep))
		print_string(") ");
}
#endif

static void print_scope(const scope_t *scope)
{
	for (entity_t const *entity = scope->first_entity; entity != NULL;
	     entity = entity->base.next) {
		print_indent();
		print_entity(entity);
		print_char('\n');
	}
}

static void print_namespace(const namespace_t *namespace)
{
	print_string("namespace ");
	if (namespace->base.symbol != NULL) {
		print_string(namespace->base.symbol->string);
		print_char(' ');
	}

	print_string("{\n");
	++indent;

	print_scope(&namespace->members);

	--indent;
	print_indent();
	print_string("}\n");
}

/**
 * Print a variable or function declaration
 */
static void print_declaration(entity_t const *const entity)
{
	assert(is_declaration(entity));
	const declaration_t *declaration = &entity->declaration;

	print_storage_class(declaration->declared_storage_class);
	if (entity->kind == ENTITY_FUNCTION) {
		function_t *function = (function_t*)declaration;
		if (function->is_inline) {
			if (declaration->modifiers & DM_FORCEINLINE) {
				print_string("__forceinline ");
			} else if (declaration->modifiers & DM_MICROSOFT_INLINE) {
				print_string("__inline ");
			} else {
				print_string("inline ");
			}
		}
	}
	//print_ms_modifiers(declaration);
	switch (entity->kind) {
		case ENTITY_FUNCTION:
			print_type_ext(entity->declaration.type, entity->base.symbol,
			               &entity->function.parameters);

			if (entity->function.body != NULL) {
				print_char('\n');
				print_indented_statement(entity->function.body);
				print_char('\n');
				return;
			}
			break;

		case ENTITY_VARIABLE:
			if (entity->variable.thread_local)
				print_string(dialect.c11 ? "_Thread_local " : "__thread ");
			print_type_ext(declaration->type, declaration->base.symbol, NULL);
			if (entity->variable.initializer != NULL) {
				print_string(" = ");
				print_initializer(entity->variable.initializer);
			}
			break;

		case ENTITY_COMPOUND_MEMBER:
			print_type_ext(declaration->type, declaration->base.symbol, NULL);
			if (entity->compound_member.bitfield) {
				print_format(" : %u", entity->compound_member.bit_size);
			}
			break;

		default:
			print_type_ext(declaration->type, declaration->base.symbol, NULL);
			break;
	}
	print_char(';');
}

/**
 * Prints an expression.
 *
 * @param expression  the expression
 */
void print_expression(const expression_t *expression)
{
	print_expression_prec(expression, PREC_BOTTOM);
}

/**
 * Print an entity.
 *
 * @param entity  the entity
 */
void print_entity(const entity_t *entity)
{
	if (entity->base.namespc != NAMESPACE_NORMAL && entity->base.symbol == NULL)
		return;

	switch (entity->kind) {
	case ENTITY_VARIABLE:
	case ENTITY_PARAMETER:
	case ENTITY_COMPOUND_MEMBER:
	case ENTITY_FUNCTION:
	case ENTITY_TYPEDEF:
		print_declaration(entity);
		return;

	case ENTITY_CLASS:
	case ENTITY_STRUCT:
	case ENTITY_UNION:
		print_string(get_entity_kind_name(entity->kind));
		print_char(' ');
		print_string(entity->base.symbol->string);
		if (entity->compound.complete) {
			print_char(' ');
			print_compound_definition(&entity->compound);
		}
		print_char(';');
		return;
	case ENTITY_ENUM:
		print_string("enum ");
		print_string(entity->base.symbol->string);
		print_char(' ');
		print_enum_definition(&entity->enume);
		print_char(';');
		return;
	case ENTITY_NAMESPACE:
		print_namespace(&entity->namespacee);
		return;
	case ENTITY_LOCAL_LABEL:
		print_string("__label__ ");
		print_string(entity->base.symbol->string);
		print_char(';');
		return;
	case ENTITY_ASM_ARGUMENT:
	case ENTITY_ASM_LABEL:
		print_string(entity->base.symbol->string);
		return;
	case ENTITY_LABEL:
	case ENTITY_ENUM_VALUE:
		panic("print_entity used on unexpected entity type");
	}
	panic("Invalid entity type encountered");
}

/**
 * Print the AST of a translation unit.
 *
 * @param unit   the translation unit
 */
void print_ast(const translation_unit_t *unit)
{
	for (entity_t const *entity = unit->scope.first_entity; entity != NULL;
	     entity = entity->base.next) {
		if (entity->kind == ENTITY_ENUM_VALUE)
			continue;
		if (entity->base.namespc != NAMESPACE_NORMAL
		    && entity->base.symbol == NULL)
			continue;
		if (is_generated_entity(entity))
			continue;

		print_indent();
		print_entity(entity);
		print_char('\n');
	}
}

expression_classification_t is_constant_initializer(const initializer_t *initializer)
{
	switch (initializer->kind) {
	case INITIALIZER_STRING:
	case INITIALIZER_DESIGNATOR:
		return EXPR_CLASS_CONSTANT;

	case INITIALIZER_VALUE:
		return is_linker_constant(initializer->value.value);

	case INITIALIZER_LIST: {
		expression_classification_t all = EXPR_CLASS_CONSTANT;
		for (size_t i = 0; i < initializer->list.len; ++i) {
			initializer_t *sub_initializer = initializer->list.initializers[i];
			expression_classification_t const cur = is_constant_initializer(sub_initializer);
			all = MIN(all, cur);
		}
		return all;
	}
	}
	panic("invalid initializer kind found");
}

/**
 * Checks if an expression references an object with a constant/known location
 * to the linker. Example:
 *  - "x", "*&x" with x being a global variable. The value of x need not be
 *         constant but the address of x is.
 *  - "a.b.c" when a has a constant/known location to the linker
 */
static expression_classification_t is_object_with_linker_constant_address(
	const expression_t *expression)
{
	switch (expression->kind) {
	case EXPR_UNARY_DEREFERENCE:
		return is_linker_constant(expression->unary.value);

	case EXPR_COMPOUND_LITERAL: {
		const compound_literal_expression_t *literal =
			&expression->compound_literal;
		type_t *type = skip_typeref(literal->type);
		return literal->global_scope ||
		      (type->base.qualifiers & TYPE_QUALIFIER_CONST
		       && is_constant_initializer(literal->initializer))
		     ? EXPR_CLASS_CONSTANT : EXPR_CLASS_VARIABLE;
	}

	case EXPR_SELECT: {
		type_t *base_type = skip_typeref(expression->select.compound->base.type);
		if (is_type_pointer(base_type)) {
			/* it's a -> */
			return is_linker_constant(expression->select.compound);
		} else {
			return is_object_with_linker_constant_address(expression->select.compound);
		}
	}

	case EXPR_ARRAY_ACCESS: {
		expression_classification_t const ref = is_linker_constant(expression->array_access.array_ref);
		expression_classification_t const idx = is_constant_expression(expression->array_access.index);
		return MIN(ref, idx);
	}

	case EXPR_REFERENCE: {
		entity_t *entity = expression->reference.entity;
		if (!is_declaration(entity))
			return EXPR_CLASS_VARIABLE;

		switch (entity->declaration.storage_class) {
		case STORAGE_CLASS_NONE:
		case STORAGE_CLASS_EXTERN:
		case STORAGE_CLASS_STATIC:
			return
				entity->kind != ENTITY_VARIABLE ||
				!entity->variable.thread_local ? EXPR_CLASS_CONSTANT :
				EXPR_CLASS_VARIABLE;

		case STORAGE_CLASS_REGISTER:
		case STORAGE_CLASS_TYPEDEF:
		case STORAGE_CLASS_AUTO:
			break;
		}
		return EXPR_CLASS_VARIABLE;
	}

	case EXPR_ERROR:
		return EXPR_CLASS_ERROR;

	default:
		return EXPR_CLASS_VARIABLE;
	}
}

expression_classification_t is_linker_constant(const expression_t *expression)
{
	switch (expression->kind) {
	case EXPR_STRING_LITERAL:
	case EXPR_FUNCNAME:
	case EXPR_LABEL_ADDRESS:
		return EXPR_CLASS_CONSTANT;

	case EXPR_COMPOUND_LITERAL: {
		const compound_literal_expression_t *literal =
			&expression->compound_literal;
		type_t *type = skip_typeref(literal->type);
		return literal->global_scope ||
		      (type->base.qualifiers & TYPE_QUALIFIER_CONST
		       && (is_type_compound(type) || is_type_array(type))
		       && is_constant_initializer(literal->initializer))
		     ? EXPR_CLASS_CONSTANT : EXPR_CLASS_VARIABLE;
	}

	case EXPR_UNARY_TAKE_ADDRESS:
		return is_object_with_linker_constant_address(expression->unary.value);

	case EXPR_UNARY_DEREFERENCE: {
		type_t *const type = skip_typeref(revert_automatic_type_conversion(expression->unary.value));
		/* dereferencing a function is a NOP */
		if (is_type_function(type))
			return is_linker_constant(expression->unary.value);
	}
		/* FALLTHROUGH */
	case EXPR_UNARY_CAST: {
		type_t *dest = skip_typeref(expression->base.type);
		if (!is_type_pointer(dest) &&
		    (dest->kind != TYPE_ATOMIC                                               ||
		     !(get_atomic_type_flags(dest->atomic.akind) & ATOMIC_TYPE_FLAG_INTEGER) ||
		     get_atomic_type_size(dest->atomic.akind) < get_ctype_size(type_void_ptr)
		    ))
			return is_constant_expression(expression);

		return is_linker_constant(expression->unary.value);
	}

	case EXPR_BINARY_ADD:
	case EXPR_BINARY_SUB: {
		expression_t *const left  = expression->binary.left;
		expression_t *const right = expression->binary.right;
		type_t       *const ltype = skip_typeref(left->base.type);
		type_t       *const rtype = skip_typeref(right->base.type);

		if (is_type_pointer(ltype)) {
			expression_classification_t const l = is_linker_constant(left);
			expression_classification_t const r = is_constant_expression(right);
			return MIN(l, r);
		} else if (is_type_pointer(rtype)) {
			expression_classification_t const l = is_constant_expression(left);
			expression_classification_t const r = is_linker_constant(right);
			return MIN(l, r);
		} else if (!is_type_valid(ltype) || !is_type_valid(rtype)) {
			return EXPR_CLASS_ERROR;
		} else {
			return is_constant_expression(expression);
		}
	}

	case EXPR_REFERENCE: {
		entity_t *entity = expression->reference.entity;
		if (!is_declaration(entity))
			return EXPR_CLASS_VARIABLE;

		type_t *type = skip_typeref(entity->declaration.type);
		if (is_type_function(type))
			return EXPR_CLASS_CONSTANT;
		if (is_type_array(type)) {
			return is_object_with_linker_constant_address(expression);
		}
		/* Prevent stray errors */
		if (!is_type_valid(type))
			return EXPR_CLASS_ERROR;
		return EXPR_CLASS_VARIABLE;
	}

	case EXPR_ARRAY_ACCESS: {
		type_t *const type =
			skip_typeref(revert_automatic_type_conversion(expression));
		if (!is_type_array(type))
			return EXPR_CLASS_VARIABLE;
		return is_linker_constant(expression->array_access.array_ref);
	}

	case EXPR_CONDITIONAL: {
		expression_t *const c = expression->conditional.condition;
		expression_classification_t const cclass = is_constant_expression(c);
		if (cclass < EXPR_CLASS_CONSTANT)
			return cclass;

		if (fold_expression_to_bool(c)) {
			expression_t const *const t = expression->conditional.true_expression;
			return is_linker_constant(t != NULL ? t : c);
		} else {
			return is_linker_constant(expression->conditional.false_expression);
		}
	}

	case EXPR_SELECT: {
		entity_t *entity = expression->select.compound_entry;
		if (!is_declaration(entity))
			return EXPR_CLASS_VARIABLE;
		type_t *type = skip_typeref(entity->declaration.type);
		if (is_type_array(type)) {
			/* arrays automatically convert to their address */
			expression_t *compound  = expression->select.compound;
			type_t       *base_type = skip_typeref(compound->base.type);
			if (is_type_pointer(base_type)) {
				/* it's a -> */
				return is_linker_constant(compound);
			} else {
				return is_object_with_linker_constant_address(compound);
			}
		}
		return EXPR_CLASS_VARIABLE;
	}

	default:
		return is_constant_expression(expression);
	}
}

/**
 * Check if the given expression is a call to a builtin function
 * returning a constant result.
 */
static expression_classification_t is_builtin_const_call(const expression_t *expression)
{
	expression_t *function = expression->call.function;
	if (function->kind != EXPR_REFERENCE)
		return EXPR_CLASS_VARIABLE;
	reference_expression_t *ref = &function->reference;
	if (ref->entity->kind != ENTITY_FUNCTION)
		return EXPR_CLASS_VARIABLE;

	switch (ref->entity->function.btk) {
	case BUILTIN_INF:
	case BUILTIN_NAN:
		return EXPR_CLASS_CONSTANT;
	default:
		return EXPR_CLASS_VARIABLE;
	}

}

static expression_classification_t is_constant_pointer(const expression_t *expression)
{
	expression_classification_t const expr_class = is_constant_expression(expression);
	if (expr_class != EXPR_CLASS_VARIABLE)
		return expr_class;

	if (expression->kind == EXPR_UNARY_CAST)
		return is_constant_pointer(expression->unary.value);
	return EXPR_CLASS_VARIABLE;
}

static expression_classification_t is_object_with_constant_address(const expression_t *expression)
{
	switch (expression->kind) {
	case EXPR_SELECT: {
		expression_t *compound      = expression->select.compound;
		type_t       *compound_type = compound->base.type;
		compound_type = skip_typeref(compound_type);
		if (is_type_pointer(compound_type)) {
			return is_constant_pointer(compound);
		} else {
			return is_object_with_constant_address(compound);
		}
	}

	case EXPR_ARRAY_ACCESS: {
		array_access_expression_t const* const array_access =
			&expression->array_access;
		expression_classification_t const idx_class = is_constant_expression(array_access->index);
		if (idx_class < EXPR_CLASS_CONSTANT)
			return idx_class;
		expression_classification_t const ref_addr = is_object_with_constant_address(array_access->array_ref);
		expression_classification_t const ref_ptr  = is_constant_pointer(array_access->array_ref);
		return MAX(ref_addr, ref_ptr);
	}

	case EXPR_UNARY_DEREFERENCE:
		return is_constant_pointer(expression->unary.value);

	case EXPR_ERROR:
		return EXPR_CLASS_ERROR;

	default:
		return EXPR_CLASS_VARIABLE;
	}
}

expression_classification_t is_constant_expression(const expression_t *expression)
{
	if (!is_type_valid(skip_typeref(expression->base.type)))
		return EXPR_CLASS_ERROR;

	switch (expression->kind) {
	case EXPR_LITERAL_CHARACTER:
	case EXPR_BUILTIN_TYPES_COMPATIBLE_P:
	case EXPR_LITERAL_BOOLEAN:
	case EXPR_LITERAL_MS_NOOP:
		return EXPR_CLASS_INTEGER_CONSTANT;

	{
		type_t *type;
	case EXPR_ALIGNOF:
		type = skip_typeref(expression->typeprop.type);
		goto check_type;

	case EXPR_CLASSIFY_TYPE:
		type = skip_typeref(expression->classify_type.type_expression->base.type);
		goto check_type;

	case EXPR_OFFSETOF:
		type = skip_typeref(expression->offsetofe.type);
		goto check_type;

	case EXPR_SIZEOF:
		type = skip_typeref(expression->typeprop.type);
		if (is_type_array(type) && type->array.is_vla)
			return EXPR_CLASS_VARIABLE;
		goto check_type;

check_type:
		return is_type_valid(type) ? EXPR_CLASS_INTEGER_CONSTANT : EXPR_CLASS_ERROR;
	}

	case EXPR_ENUM_CONSTANT:
		return expression->reference.entity->enum_value.enume->error
		       ? EXPR_CLASS_ERROR : EXPR_CLASS_INTEGER_CONSTANT;

	case EXPR_LITERAL_FLOATINGPOINT:
		return EXPR_CLASS_CONSTANT;

	case EXPR_LITERAL_INTEGER:
		return EXPR_CLASS_INTEGER_CONSTANT;

	case EXPR_BUILTIN_CONSTANT_P: {
		expression_classification_t const c = is_constant_expression(expression->builtin_constant.value);
		return c != EXPR_CLASS_ERROR ? EXPR_CLASS_INTEGER_CONSTANT : EXPR_CLASS_ERROR;
	}

	case EXPR_STRING_LITERAL:
	case EXPR_FUNCNAME:
	case EXPR_LABEL_ADDRESS:
	case EXPR_SELECT:
	case EXPR_VA_START:
	case EXPR_VA_ARG:
	case EXPR_VA_COPY:
	case EXPR_STATEMENT:
	case EXPR_UNARY_POSTFIX_INCREMENT:
	case EXPR_UNARY_POSTFIX_DECREMENT:
	case EXPR_UNARY_PREFIX_INCREMENT:
	case EXPR_UNARY_PREFIX_DECREMENT:
	case EXPR_UNARY_ASSUME: /* has VOID type */
	case EXPR_UNARY_DEREFERENCE:
	case EXPR_UNARY_DELETE:
	case EXPR_UNARY_DELETE_ARRAY:
	case EXPR_UNARY_THROW:
	case EXPR_BINARY_ASSIGN:
	case EXPR_BINARY_MUL_ASSIGN:
	case EXPR_BINARY_DIV_ASSIGN:
	case EXPR_BINARY_MOD_ASSIGN:
	case EXPR_BINARY_ADD_ASSIGN:
	case EXPR_BINARY_SUB_ASSIGN:
	case EXPR_BINARY_SHIFTLEFT_ASSIGN:
	case EXPR_BINARY_SHIFTRIGHT_ASSIGN:
	case EXPR_BINARY_BITWISE_AND_ASSIGN:
	case EXPR_BINARY_BITWISE_XOR_ASSIGN:
	case EXPR_BINARY_BITWISE_OR_ASSIGN:
	case EXPR_BINARY_COMMA:
	case EXPR_ARRAY_ACCESS:
	case EXPR_REFERENCE:
		return EXPR_CLASS_VARIABLE;

	case EXPR_UNARY_TAKE_ADDRESS:
		return is_object_with_constant_address(expression->unary.value);

	case EXPR_CALL:
		return is_builtin_const_call(expression);

	case EXPR_UNARY_NEGATE:
	case EXPR_UNARY_PLUS:
	case EXPR_UNARY_COMPLEMENT:
	case EXPR_UNARY_NOT:
		return is_constant_expression(expression->unary.value);

	case EXPR_UNARY_IMAG:
	case EXPR_UNARY_REAL:
		return is_constant_expression(expression->unary.value);

	case EXPR_UNARY_CAST: {
		type_t *const type = skip_typeref(expression->base.type);
		if (is_type_integer(type)) {
			expression_t *const val = expression->unary.value;
			if (is_type_arithmetic(skip_typeref(val->base.type))) {
				return val->kind == EXPR_LITERAL_FLOATINGPOINT
					? EXPR_CLASS_INTEGER_CONSTANT
					: is_constant_expression(val);
			}
		}
		if (is_type_scalar(type)) {
			expression_classification_t const cls
				= is_constant_expression(expression->unary.value);
			/* Can't be an integer constant anymore */
			return MIN(cls, EXPR_CLASS_CONSTANT);
		}
		if (!is_type_valid(type))
			return EXPR_CLASS_ERROR;
		return EXPR_CLASS_VARIABLE;
	}

	case EXPR_BINARY_DIV:
	case EXPR_BINARY_MOD: {
		expression_t const         *const right  = expression->binary.right;
		expression_classification_t const r      = is_constant_expression(right);
		type_t                     *const rtype  = skip_typeref(right->base.type);
		bool                        const iconst = is_type_integer(rtype) && r >= EXPR_CLASS_CONSTANT;
		if (iconst && tarval_is_null(fold_expression(right)))
			return EXPR_CLASS_VARIABLE;
		expression_classification_t const l = is_constant_expression(expression->binary.left);
		return MIN(l, r);
	}

	case EXPR_BINARY_ADD:
	case EXPR_BINARY_SUB:
	case EXPR_BINARY_MUL:
	case EXPR_BINARY_EQUAL:
	case EXPR_BINARY_NOTEQUAL:
	case EXPR_BINARY_LESS:
	case EXPR_BINARY_LESSEQUAL:
	case EXPR_BINARY_GREATER:
	case EXPR_BINARY_GREATEREQUAL:
	case EXPR_BINARY_BITWISE_AND:
	case EXPR_BINARY_BITWISE_OR:
	case EXPR_BINARY_BITWISE_XOR:
	case EXPR_BINARY_SHIFTLEFT:
	case EXPR_BINARY_SHIFTRIGHT:
	case EXPR_BINARY_ISGREATER:
	case EXPR_BINARY_ISGREATEREQUAL:
	case EXPR_BINARY_ISLESS:
	case EXPR_BINARY_ISLESSEQUAL:
	case EXPR_BINARY_ISLESSGREATER:
	case EXPR_BINARY_ISUNORDERED: {
		expression_classification_t const l = is_constant_expression(expression->binary.left);
		expression_classification_t const r = is_constant_expression(expression->binary.right);
		return MIN(l, r);
	}

	case EXPR_BINARY_LOGICAL_AND: {
		expression_t const         *const left = expression->binary.left;
		expression_classification_t const lcls = is_constant_expression(left);
		if (lcls < EXPR_CLASS_CONSTANT)
			return lcls;
		expression_classification_t const rcls = is_constant_expression(expression->binary.right);
		if (lcls == EXPR_CLASS_INTEGER_CONSTANT && rcls == EXPR_CLASS_INTEGER_CONSTANT)
			return EXPR_CLASS_INTEGER_CONSTANT;
		if (!fold_expression_to_bool(left))
			return EXPR_CLASS_CONSTANT;
		return MIN(rcls, EXPR_CLASS_CONSTANT);
	}

	case EXPR_BINARY_LOGICAL_OR: {
		expression_t const         *const left = expression->binary.left;
		expression_classification_t const lcls = is_constant_expression(left);
		if (lcls < EXPR_CLASS_CONSTANT)
			return lcls;
		expression_classification_t const rcls = is_constant_expression(expression->binary.right);
		if (lcls == EXPR_CLASS_INTEGER_CONSTANT && rcls == EXPR_CLASS_INTEGER_CONSTANT)
			return EXPR_CLASS_INTEGER_CONSTANT;
		if (fold_expression_to_bool(left))
			return EXPR_CLASS_CONSTANT;
		return MIN(rcls, EXPR_CLASS_CONSTANT);
	}

	case EXPR_COMPOUND_LITERAL: {
		type_t *skipped = skip_typeref(expression->compound_literal.type);
		if (is_type_scalar(skipped)) {
			expression_classification_t const cls = is_constant_initializer(expression->compound_literal.initializer);
			return MIN(cls, EXPR_CLASS_CONSTANT);
		} else if (is_type_valid(skipped)) {
			assert(is_type_array(skipped) || is_type_compound(skipped));
			/* arrays/compounds degrade automatically to pointers to the
			 * initializer contents (which is only a linktime constant) */
			return EXPR_CLASS_VARIABLE;
		} else {
			return EXPR_CLASS_ERROR;
		}
	}

	case EXPR_CONDITIONAL: {
		expression_t               *const cond = expression->conditional.condition;
		expression_classification_t const ccls = is_constant_expression(cond);
		if (ccls < EXPR_CLASS_CONSTANT)
			return ccls;
		expression_t         const *const t    = expression->conditional.true_expression;
		expression_classification_t const tcls = t == NULL ? ccls : is_constant_expression(t);
		expression_classification_t const fcls = is_constant_expression(expression->conditional.false_expression);
		if (ccls >= EXPR_CLASS_CONSTANT &&
		    tcls == EXPR_CLASS_INTEGER_CONSTANT &&
		    fcls == EXPR_CLASS_INTEGER_CONSTANT)
			return EXPR_CLASS_INTEGER_CONSTANT;
		expression_classification_t const cls = fold_expression_to_bool(cond) ? tcls : fcls;
		return MIN(cls, EXPR_CLASS_CONSTANT);
	}

	case EXPR_ERROR:
		return EXPR_CLASS_ERROR;
	}
	panic("invalid expression");
}

type_t *get_string_type(string_encoding_t const enc)
{
	bool const warn = is_warn_on(WARN_WRITE_STRINGS);
	switch (enc) {
	case STRING_ENCODING_CHAR:
	case STRING_ENCODING_UTF8:   return warn ? type_const_char_ptr     : type_char_ptr;
	case STRING_ENCODING_CHAR16: return warn ? type_char16_t_const_ptr : type_char16_t_ptr;
	case STRING_ENCODING_CHAR32: return warn ? type_char32_t_const_ptr : type_char32_t_ptr;
	case STRING_ENCODING_WIDE:   return warn ? type_const_wchar_t_ptr  : type_wchar_t_ptr;
	}
	panic("invalid string encoding");
}

type_t *revert_automatic_type_conversion(const expression_t *expression)
{
	switch (expression->kind) {
	case EXPR_REFERENCE: {
		entity_t *entity = expression->reference.entity;
		if (is_declaration(entity)) {
			return entity->declaration.type;
		} else if (entity->kind == ENTITY_ENUM_VALUE) {
			return type_int;
		} else {
			panic("no declaration or enum in reference");
		}
	}

	case EXPR_SELECT: {
		entity_t *entity = expression->select.compound_entry;
		assert(is_declaration(entity));
		type_t   *type   = entity->declaration.type;
		return get_qualified_type(type, expression->base.type->base.qualifiers);
	}

	case EXPR_UNARY_DEREFERENCE: {
		const expression_t *const value = expression->unary.value;
		type_t             *const type  = skip_typeref(value->base.type);
		if (!is_type_pointer(type))
			return type_error_type;
		return type->pointer.points_to;
	}

	case EXPR_ARRAY_ACCESS: {
		const expression_t *array_ref = expression->array_access.array_ref;
		type_t             *type_left = skip_typeref(array_ref->base.type);
		if (!is_type_pointer(type_left))
			return type_error_type;
		return type_left->pointer.points_to;
	}

	case EXPR_STRING_LITERAL: {
		size_t const len = get_string_len(expression->string_literal.value);
		string_encoding_t const encoding
			= expression->string_literal.value->encoding;
		type_t *const elem = get_string_type(encoding)->pointer.points_to;
		return make_array_type(elem, len+1, TYPE_QUALIFIER_NONE);
	}

	case EXPR_COMPOUND_LITERAL:
		return expression->compound_literal.type;

	default:
		break;
	}
	return expression->base.type;
}

bool function_is_inline_only(function_t const *const function)
{
	if (!function->all_decls_inline || (function->base.modifiers & DM_NOINLINE))
		return false;

	storage_class_t const storage_class = function->base.declared_storage_class;

	if (function->base.modifiers & DM_GNU_INLINE)
		goto gnu_c90_inline;

	if (dialect.c99) {
		/* C99 inline behaviour, see §6.7.4.6  */
		return storage_class == STORAGE_CLASS_NONE;
	} else {
gnu_c90_inline:
		/* GNU C90 inline behaviour */
		return storage_class == STORAGE_CLASS_EXTERN;
	}
}

void init_ast(void)
{
	obstack_init(&ast_obstack);
	init_typehash();
}

void init_ast_dialect(void)
{
	init_predefined_types();
	init_constfold();
}

void exit_ast(void)
{
	exit_types();
	exit_typehash();
	obstack_free(&ast_obstack, NULL);
}
