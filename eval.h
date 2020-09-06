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
 * along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * \file eval.h
 * \author Anamitra Ghorui
 * \brief Calcium expression evaluation
 *
 */

#ifndef _CA_EVAL_H
#define _CA_EVAL_H

#include "stack.h"
#include "hash.h"

#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

/// Contains the expression and the current location on the expression.
typedef struct CaExpr CaExpr;

struct CaExpr {
    CaSize pos;
    const char *data;
};

/// The "context" the evaluator runs on.
typedef struct CaContext {
    uint8_t flags;
    CaHash env;
    CaStack *oper;
    CaStack *expr;
} CaContext;

/**
 * \brief Takes a string and readies it for tokenisation.
 * \param data The string
 * \return Pointer to a ca_expr struct
 */
CaExpr *ca_tokenize(const char *data);

/**
* \brief Gets the next token, and the type from the expression.
* \param expr The expression to read.
* \param type The type to write back.
* \param start The start of the token.
* \param end The end of the token.
* \return An error code.
*/
CaError ca_next_token(CaExpr *expr, CaType *guess, CaSize *start, 
                      CaSize *end);


/**
 * \brief Initialises a context.
 * \return A pointer to the context.
 */
CaContext *ca_context_init();

/**
 * \brief Evaluates a given expression.
 * \param c The context.
 * \param s The expression.
 * \return An error code.
 */
CaError ca_eval(CaContext c, CaExpr s);

#endif
