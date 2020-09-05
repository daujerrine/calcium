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
