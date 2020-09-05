#include "eval.h"

ca_expr *ca_tokenize(const char *data)
{
    ca_expr *e = calloc(1, sizeof(ca_expr));
    if(!e)
        return NULL;
    e->data = data;
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
CaError ca_next_token(ca_expr *expr, CaType *guess, CaSize *start, 
                      CaSize *end)
{
    char loop = 1;
    guess = CA_TYPE_
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
    c->env  = Ca_HashInit();
    c->oper = ca_stack_init(CA_STACK_SIZE);
    c->expr = ca_stack_init(CA_STACK_SIZE);
}

/**
 * \brief Evaluates a given expression.
 * \param c The context.
 * \param s The expression.
 * \return An error code.
 */
CaError ca_eval(ca_context *c)
{
    
}
