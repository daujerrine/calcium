/*
 * Copyright (c) 2020 Anamitra Ghorui
 * This file is part of Calcium. See Calcium's licensing information for
 * details.
 */

/*
 * Infix expression processor with precedence
 * Note: token and chunk are used interchangably over here.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXBUF 4096

#define CIN_RANGE(x, l, h) (((x) >= (l)) && ((x) <= (h)))
#define CIS_ALPHA(x)  (CIN_RANGE((x), 0x41, 0x5A) || \
                       CIN_RANGE((x), 0x61, 0x7A) || \
                       ((x) == '_'))
#define CIS_NUMBER(x) (CIN_RANGE((x), 0x30, 0x39)) 
#define CIS_SYMBOL(x) (CIN_RANGE((x), 0x21, 0x2F) || \
                       CIN_RANGE((x), 0x3A, 0x40) || \
                       CIN_RANGE((x), 0x5B, 0x5E) || \
                       CIN_RANGE((x), 0x7B, 0x7E)) \

typedef enum CGuess {
    GUESS_UNKNOWN = 0,
    GUESS_ERROR,
    GUESS_NEED_MORE_DATA,
    GUESS_INTEGER,
    GUESS_FLOAT,
    GUESS_OPERATOR,
    GUESS_NOUN,
    GUESS_STRING
} CGuess;

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

typedef enum Precedence {
    PRECEDENCE_UNKNOWN = 0,
    PRECEDENCE_UNARY = 1,
    PRECEDENCE_EXPONENTIAL,
    PRECEDENCE_MULTIPLICATIVE,
    PRECEDENCE_ADDITIVE,
    PRECEDENCE_SHIFT,
    PRECEDENCE_COMPARISON,
    PRECEDENCE_EQUALITY,
    PRECEDENCE_B_AND,
    PRECEDENCE_B_XOR,
    PRECEDENCE_B_OR,
    PRECEDENCE_AND,
    PRECEDENCE_OR,
    PRECEDENCE_ASSIGNMENT
} Precedence;

typedef enum OperID {
    OPER_ID_INCREMENT = 0,
    OPER_ID_DECREMENT,
    OPER_ID_B_NOT,
    OPER_ID_POWER,
    OPER_ID_MULTIPLICATION,
    OPER_ID_DIVISION,
    OPER_ID_REMAINDER,
    OPER_ID_ADDITION,
    OPER_ID_SUBTRACTION,
    OPER_ID_LSHIFT,
    OPER_ID_RSHIFT,
    OPER_ID_LT,
    OPER_ID_LTEQ,
    OPER_ID_GT,
    OPER_ID_GTEQ,
    OPER_ID_EQ,
    OPER_ID_NEQ,
    OPER_ID_B_AND,
    OPER_ID_B_XOR,
    OPER_ID_B_OR,
    OPER_ID_AND,
    OPER_ID_OR,
    OPER_ID_ASSIGN,
    OPER_ID_ADDITION_ASSIGN,
    OPER_ID_SUBTRACTION_ASSIGN,
    OPER_ID_MULTIPLICATION_ASSIGN,
    OPER_ID_DIVISION_ASSIGN,
    OPER_ID_REMAINDER_ASSIGN,
    OPER_ID_NEST,
    OPER_ID_NEST_CLOSE
} OperID;


/* TODO Rearrange extra symbol to end */

typedef struct Operator {
    char extra_symbol;
    OperID id;
    Precedence prec;
} Operator;


Operator oper_list[][5] = {
    ['('] = { { '\0' }, { 0 } },
    [')'] = { { '\0' }, { 0 } },
    ['['] = { { '\0' }, { 0 } },
    [']'] = { { '\0' }, { 0 } },
    /*    OPER  OPER_ID                        PRECEDENCE                     */
    ['+'] =
    {
        { '\0', OPER_ID_ADDITION,              PRECEDENCE_ADDITIVE       },
        { '+',  OPER_ID_INCREMENT,             PRECEDENCE_UNARY          },
        { '=',  OPER_ID_ADDITION_ASSIGN,       PRECEDENCE_ASSIGNMENT     },
        { 0 }                                  
    },                                         
    ['-'] =                                    
    {                                          
        { '\0', OPER_ID_SUBTRACTION,           PRECEDENCE_ADDITIVE       },
        { '-',  OPER_ID_DECREMENT,             PRECEDENCE_UNARY          },
        { '=',  OPER_ID_SUBTRACTION_ASSIGN,    PRECEDENCE_ASSIGNMENT     },
        { 0 }
    },
    ['*'] =
    {
        { '\0', OPER_ID_MULTIPLICATION,        PRECEDENCE_MULTIPLICATIVE },
        { '*',  OPER_ID_POWER,                 PRECEDENCE_EXPONENTIAL    },
        { '=',  OPER_ID_MULTIPLICATION_ASSIGN, PRECEDENCE_ASSIGNMENT     },
        { 0 }
    },
    ['/'] =
    {
        { '\0', OPER_ID_DIVISION,              PRECEDENCE_MULTIPLICATIVE },
        { '/',  OPER_ID_DIVISION,              PRECEDENCE_MULTIPLICATIVE },
        { '=',  OPER_ID_DIVISION_ASSIGN,       PRECEDENCE_ASSIGNMENT     },
        { 0 }
    },
    ['>'] =
    {
        { '\0', OPER_ID_GT,                    PRECEDENCE_COMPARISON     },
        { '=',  OPER_ID_GTEQ,                  PRECEDENCE_COMPARISON     },
        { '>',  OPER_ID_RSHIFT,                PRECEDENCE_SHIFT          },
        { 0 }
    },
    ['<'] =
    {
        { '\0', OPER_ID_LT,                    PRECEDENCE_COMPARISON     },
        { '=',  OPER_ID_LTEQ,                  PRECEDENCE_COMPARISON     },
        { '<',  OPER_ID_LSHIFT,                PRECEDENCE_SHIFT          },
        { 0 }
    },
    ['='] =
    {
        { '\0', OPER_ID_ASSIGN,                PRECEDENCE_ASSIGNMENT     },
        { '=',  OPER_ID_EQ,                    PRECEDENCE_EQUALITY       },
        { 0 }
    },
    ['%'] =
    {
        { '\0', OPER_ID_REMAINDER,             PRECEDENCE_MULTIPLICATIVE },
        { '=',  OPER_ID_REMAINDER_ASSIGN,      PRECEDENCE_ASSIGNMENT     },
        { 0 }
    },
};

#define OPERATOR_ISUNARY(oper) ((oepr).prec == PRECEDENCE_UNARY)

typedef struct Stack {
    void *data;
    int elem_size;
    int nelem;
    int top;
} Stack;

static void stack_init(Stack *s, int elem_size, int nelem)
{
    s->data = malloc((unsigned long) elem_size * nelem);
    s->elem_size = elem_size;
    s->nelem = nelem;
    s->top = 0;
}

static inline int stack_pop(Stack *s, void **value)
{
    if (s->top == 0)
        return -1;
    *value = (s->data + s->nelem * (--s->top));

    return 0;
}

static inline int stack_peek(Stack *s, void **value)
{
    if (s->top == 0)
        return -1;
    *value = (s->data + s->nelem * (s->top - 1));
    return 0;
}

static inline int stack_push(Stack *s, void *value)
{
    if (s->top == MAXBUF + 1)
        return -1;
    *(s->data + s->nelem * (s->top++)) = value;

    return 0;
}

static inline int stack_empty(Stack *s)
{
    return s->top == 0;
}

static inline int stack_size(Stack *s)
{
    return s->top;
}

typedef struct EvalContext {
    int active;
    int scope_offset;
    Stack operstack;
    Stack numstack;
    FILE *f_out;
    FILE *f_in;
} EvalContext;

void eval_init(EvalContext *e, FILE *f_in, FILE *f_out)
{
    e->active = 1;
    e->scope_offset = 0;
    e->f_in   = f_in;
    e->f_out  = f_out;
    stack_init(&e->ns, sizeof(int), MAXBUF);
    stack_init(&e->os, sizeof(Operator *), MAXBUF);
}

char *next_token(char *c, int *size, CGuess *guess, Operator *oper)
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
                printf("enter");
                for (i = 1; oper_list[curr_oper][i].extra_symbol; i++) {
                    if (oper_list[curr_oper][i].extra_symbol == *c) {
                        c++;
                        printf("ending second\n");
                        *oper = oper_list[curr_oper][i];
                        goto end;
                    }
                    printf("iter\n");
                }
                printf("ending first\n");
                *oper = oper_list[curr_oper][0];
                goto end;

            } else if (*guess && *guess != GUESS_OPERATOR) { // Did we just read an entire chunk?
                printf("enter 2\n");
                goto end;
            } else if (!*guess) { // Is this the continuation or the start of a chunk?
                printf("enter else\n");
                start = c;
                curr_oper = *c;
                /*
                 * If this is only char, this is most definitely the operator
                 * intended
                 */
                *oper = oper_list[curr_oper][0]; 
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

/*
 * if number
 *     push to numstack
 * else if operator
 *     if prev oper has higher precedence
 *         operate prev oper
 *         push current to operstack
 *     else
 *         eval curr oper
 * else if bracket open
 *     push and continue
 * else if bracket close
 *     operate upto bracket open
 *
 *
 */
inline int operate_internal(EvalContext *e, Operator *oper)
{
    Operator *oper;
    int a, b, ret;

    if (OPERATOR_ISUNARY(oper))
        stack_pop(&e->ns, &a);
    else {
        stack_pop(&e->ns, &a);
        stack_pop(&e->ns, &b);
    }

    switch (oper->id) {
    case OPER_ID_INCREMENT:
        ret = a++;
        break;
    case OPER_ID_DECREMENT:
        ret = a--;
        break;
    case OPER_ID_B_NOT:
        ret = ~a;
        break;
    case OPER_ID_POWER:
        ret = pow(a, b)
        break;
    case OPER_ID_MULTIPLICATION:
        ret = a * b;
        break;
    case OPER_ID_DIVISION:
        ret = a / b;
        break;
    case OPER_ID_REMAINDER:
        ret = a % b;
        break;
    case OPER_ID_ADDITION:
        ret = a + b;
        break;
    case OPER_ID_SUBTRACTION:
        ret = a - b;
        break;
    case OPER_ID_LSHIFT:
        ret = a << b;
        break;
    case OPER_ID_RSHIFT:
        ret = a >> b;
        break;
    case OPER_ID_LT:
        ret = a < b;
        break;
    case OPER_ID_LTEQ:
        ret = a <= b;
        break;
    case OPER_ID_GT:
        ret = a > b;
        break;
    case OPER_ID_GTEQ:
        ret = a >= b;
        break;
    case OPER_ID_EQ:
        ret = a == b;
        break;
    case OPER_ID_NEQ:
        ret = a != b;
        break;
    case OPER_ID_B_AND:
        ret = a & b;
        break;
    case OPER_ID_B_XOR:
        ret = a ^ b;
        break;
    case OPER_ID_B_OR:
        ret = a | b;
        break;
    case OPER_ID_AND:
        ret = a && b;
        break;
    case OPER_ID_OR:
        ret = a || b;
        break;
    
    default:
        fprintf(stderr, "operator not implemented.\n");
    }

    stack_pop(&e->ns, ret);
}

// Number of operators in current scope
inline int oper_scope_size(EvalContext *e) {
    return stack_size(e->os) - scope_offset;
}

inline int num_scope_size(EvalContext *e) {
    return stack_size(e->ns) - scope_offset;
}

int operate(EvalContext *e, Operator *oper)
{
    Operator *prev_oper;
    int push_operator = 1;

    if (!oper) {
        // End condition. Perform all operations left.
        while (!stack_empty(e->os)) {
            stack_pop(e->os, &oper);
            operate_internal(e, oper);
        }
        return 0;
    }

    if (oper->id == OPER_ID_NEST_CLOSE){
        // End condition of nested expression. Perform all operations left.
        while (!stack_empty(e->os)) {
            stack_pop(e->os, &oper);
            operate_internal(e, oper);
        }
        return 0;
    }

         

    if (oper->id == OPER_ID_NEST) {
        stack_push(e->os, oper);
        return 0;
    }

    if (oper_scope_size(e))
        stack_peek(e->os, &prev_oper);

    switch (oper_scope_size(e)) {
    case 0:
        if (num_scope_size(e) > 1)
            return -1; // You cannot have an expression like `1 2`
        stack_push(e->os, &oper);
        break;

    default:
        if (num_scope_size(e) > 1)
            return -1; // You cannot have an expression like `1 2`
        if (prev_oper->prec <= oper->prec) { // is the expression something like `1 * 2 +` ?
            operate_internal(e, prev_oper);
        }
        stack_push(e->os, &oper);
    }
    
    return 0;
}

void eval(EvalContext *e, char *buf)
{
    char *start, *curr = buf;
    CGuess guess;
    Operator oper;
    int size;

    int numi;
    double numf;

    while ((start = next_token(curr, &size, &guess, &oper)) != NULL) {
        fprintf(e->f_out, "%d\t%d\t%s\t", (int) (start - buf),
                                          (int) (start - buf) + size,
                                          guess_strings[guess]);
        fwrite(start, 1, size, e->f_out);
        fprintf(e->f_out, "\n");
        curr = start + size;


        switch (guess) {
        case GUESS_NOUN:
        case GUESS_STRING:
            fprintf(stderr, "%s not implemented\n", guess_strings[guess]);
            return;

        case GUESS_OPERATOR:
            printf("operator found: 0x%x id: %d prec: %d\n", oper.extra_symbol,
                   oper.id, oper.prec);
            stack_push(
            switch (operate(e, &oper)) {
            case -1:
                fprintf(stderr, "stack underflow\n");
                break;

            case -2:
                fprintf(stderr, "unrecognised operand\n");
                break;
            }
            break;

        case GUESS_INTEGER:
            numi = atoi(start);
            //if (stack_push(&e->s, numi) < 0)
            //    fprintf(stderr, "stack overflow\n");
            break;

        case GUESS_FLOAT:
            numf = atof(start);
            //if (stack_push(&e->s, (int) numf) < 0)
            //    fprintf(stderr, "stack overflow\n");
            break;

        default:
            fprintf(stderr, "erroneous input\n");
        }
    }
}

int main(int argc, char **argv)
{
    FILE *f_in  = stdin;
    FILE *f_out = stdout;
    char buf[MAXBUF];
    char *start, *curr = buf;
    EvalContext e;
    int size;

    eval_init(&e, f_in, f_out);

    printf("Calculator\n"
           "Enter an expression. Press CTRL + D to exit.\n\n");
    while (e.active) {
        printf("?> ");
        if (!fgets(buf, MAXBUF, e.f_in)) {
            printf("EOF\n");
            break;
        }
        eval(&e, buf);
    }
    return 0;
}
