/*
 * Copyright (c) 2020 Anamitra Ghorui
 * This file is part of Calcium.
 *
 * Calcium is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Calcium is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Calcium.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "eval.h"

#define IN_RANGE(x, l, h) (((x) >= (l)) && ((x) <= (h)))
#define IS_ALPHA(x)  (IN_RANGE((x), 0x41, 0x5A) ||
                      IN_RANGE((x), 0x61, 0x7A))
#define IS_NUMBER(x) (IN_RANGE((x), 0x30, 0x39))
#define IS_SYMBOL(x) (IN_RANGE((x), 0x21, 0x2F) ||
                      IN_RANGE((x), 0x3A, 0x40) ||
                      IN_RANGE((x), 0x5B, 0x60) ||
                      IN_RANGE((x), 0x7B, 0x7E))


CaExpr *ca_tokenize(const char *data)
{
    ca_expr *e = calloc(1, sizeof(ca_expr));
    if (!e)
        return NULL;
    e->buf = data;
    e->pos = 0;
}

/**
* \brief Gets the next token, and the type from the expression.
* \param expr The expression to read.
* \param guess The type of the given token guessed by the compiler
* \param start The start of the token. (inclusive)
* \param end The end of the token. (inclusive)
* \return An error code.
*/
CaError ca_next_token(CaExpr *expr, CaType *guess, CaSize *start, 
                      CaSize *length)
{
    char loop = 1;
    guess = CA_TYPE_UNKNOWN;
    while (loop) {
        (expr->data[expr->pos])
    }
}


/**
 * \brief Initialises a context.
 * \return A pointer to the context.
 */
ca_context *ca_context_init()
{
    ca_context *c = malloc(sizeof(ca_context));
    c->flags = 0;
    c->env  = ca_hash_init();
    c->oper = ca_stack_init(CA_STACK_SIZE);
    c->expr = ca_stack_init(CA_STACK_SIZE);
    return c;
}

/**
 * \brief Evaluates a given expression.
 * \param c The context.
 * \param s The expression.
 * \return An error code.
 */
CaError ca_eval(CaContext *c, char *buf, int buf_size)
{
    buf
    for (int i = 0; i < buf_size; i++) {
        switch (buf) {
        case ' ':
        case '\t':
        case '\n':
            if (c->scope != CA_SCOPE_STRING)
                continue;

        case ')':
            if (!c->level)
                return CA_ERROR_EVAL_NO_OPENING_PARANTHESIS;

        case '('
            c->level++;
        }
    }

    if (c->level)
        return CA_ERROR_EVAL_NO_CLOSING_PARANTHESIS;
}
