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


char *guess_strings[] = {
    [GUESS_UNKNOWN]        = "unknown",
    [GUESS_ERROR]          = "error",
    [GUESS_NEED_MORE_DATA] = "incomplete",
    [GUESS_INTEGER]        = "int",
    [GUESS_FLOAT]          = "float",
    [GUESS_OPERATOR]       = "oper",
    [GUESS_NOUN]           = "noun",
    [GUESS_STRING]         = "string"
};

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
CaError *ca_next_token(CaExpr *expr, int *size, CaGuess *guess, CaOperator **oper)
{
    *guess         = GUESS_UNKNOWN;
    char *start    = NULL;
    int float_hint = 0;
    char delimiter = '\0';
    char curr_oper = '\0';
    int i;

    while (*c) {
        switch (*c) {
        case ' ': case '\n': case '\t':
            if (*guess)
                goto end;
            goto next;

        case '"':
        case '\'':
            delimiter = *c;
            start = c;
            while ((*++c) && *c != delimiter);
            if (*c != delimiter) {
                *guess = GUESS_ERROR;
                goto end;
            } else {
                *guess = GUESS_STRING;
                c++;
                goto end;
            }
        }

        if (CIS_SYMBOL(*c)) { // non-alphanumeric
            if (*c == '.' && *guess == GUESS_INTEGER) { // Is this possibly a float?
                float_hint = 1; // If so, store this "hinting"
            } else if (*guess && *guess == GUESS_OPERATOR) {
                // printf("enter");
                for (i = 1; oper_list[curr_oper][i].extra_symbol; i++) {
                    if (oper_list[curr_oper][i].extra_symbol == *c) {
                        c++;
                        // printf("ending second\n");
                        *oper = &oper_list[curr_oper][i];
                        goto end;
                    }
                    // printf("iter\n");
                }
                // printf("ending first\n");
                *oper = &oper_list[curr_oper][0];
                goto end;

            } else if (*guess && *guess != GUESS_OPERATOR) { // Did we just read an entire chunk?
                // printf("enter 2\n");
                goto end;
            } else if (!*guess) { // Is this the continuation or the start of a chunk?
                // printf("enter else\n");
                start = c;
                curr_oper = *c;
                /*
                 * If this is only char, this is most definitely the operator
                 * intended
                 */
                *oper = &oper_list[curr_oper][0]; 
                *guess = GUESS_OPERATOR;
            }
        } else if (CIS_ALPHA(*c)) { // alphabetical
            if (*guess && *guess != GUESS_NOUN)
                goto end;
            else if (!*guess)
                start = c;
            *guess = GUESS_NOUN;
        } else if (CIS_NUMBER(*c)) {  // numeric
            if (float_hint && *guess == GUESS_INTEGER) { // were we hinted about a float?
                *guess = GUESS_FLOAT; // yeah, this is most likely a float
            } else if (*guess && (*guess != GUESS_INTEGER && *guess != GUESS_FLOAT)) {
                goto end;
            } else if (*guess == GUESS_UNKNOWN) {
                start = c;
                *guess = GUESS_INTEGER;
            }
        }
next:
        c++;
    }

end:
    *size = (int) (c - start);
    return start;
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
 * \brief Evaluates a given tokenised expression.
 * \param c The context.
 * \param s The expression.
 * \return An error code.
 */
int operate(EvalContext *e, Operator *oper)
{
    Operator *prev_oper;
    int push_operator = 1;

    if (!oper) {
        printf("oper end\n");
        // End condition. Perform all operations left.
        while (!stack_empty(e->os)) {
            printf("oper top: %d\n", e->os.top);
            stack_pop(&e->os, &oper);
            operate_internal(e, oper);
        }
        printf("exiting\n");
        return 0;
    } else {
        printf("oper enter: %d\n", oper->id);
    }

    // Closing Bracket?
    if (oper->id == OPER_ID_NEST_CLOSE) {
        printf("oper nest close\n");
        // End condition of nested expression. Perform all operations left.
        while (!stack_empty(e->os)) {
            stack_pop(&e->os, &oper);
            if (oper->id == OPER_ID_NEST) {
                printf("bracket processed\n");
                return 0;
            }
            operate_internal(e, oper);
        }
    }

    // Opening Bracket?
    if (oper->id == OPER_ID_NEST) {
        int v = stack_push(&e->os, &oper);
        printf("oper nest open\n");
        stack_push(&e->oper_scope_offset, &e->os.top);
        printf("oper top = %d\n",e->os.top);
        stack_push(&e->num_scope_offset, &v);
        return 0;
    }

    // Is there a previous operator?
    if (oper_scope_size(e)) {
        stack_peek(&e->os, &prev_oper);
        printf("oper scope > 1 prev_oper = %d\n", prev_oper->id);
    }

    switch (oper_scope_size(e)) {
    // Push the operator. We need to look for the next operator before dealing
    // with this one.
    case 0:
        printf("oper scope == 0\n");
        stack_push(&e->os, &oper);
        break;

    default:
        printf("oper scope > 0\n");
        // Does previous operator have a higher precendence? If so, operate it
        // first
        if (prev_oper->prec <= oper->prec) { // is the expression something like `1 * 2 +` ?
            printf("prev_oper prec >= curr prec with oper_id = %d\n", prev_oper->id);
            operate_internal(e, prev_oper);
            stack_pop(&e->os, &prev_oper);
        }
        // Push the current operator
        stack_push(&e->os, &oper);
    }
    
    return 0;
}
