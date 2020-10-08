/*
 * Copyright (c) 2020 Anamitra Ghorui
 * This file is part of Calcium. See Calcium's licensing information for
 * details.
 */

/*
 * Reverse polish expression calculator
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXBUF 4096

#define CIN_RANGE(x, l, h) (((x) >= (l)) && ((x) <= (h)))
#define CIS_ALPHA(x)  (CIN_RANGE((x), 0x41, 0x5A) || \
                       CIN_RANGE((x), 0x61, 0x7A) || \
                       ((x) == '_'))
#define CIS_NUMBER(x) (CIN_RANGE((x), 0x30, 0x39)) 
#define CIS_SYMBOL(x) (CIN_RANGE((x), 0x21, 0x2F) || \
                       CIN_RANGE((x), 0x3A, 0x40) || \
                       CIN_RANGE((x), 0x5B, 0x5E) || \
                       CIN_RANGE((x), 0x7B, 0x7E))

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


typedef struct Stack {
    int data[MAXBUF];
    int top;
} Stack;

static inline int stack_pop(Stack *s, int *value)
{
    if (s->top == 0)
        return -1;
    *value = s->data[--s->top];

    return 0;
}

static inline int stack_push(Stack *s, int value)
{
    if (s->top == MAXBUF + 1)
        return -1;
    s->data[s->top++] = value;

    return 0;
}


typedef struct EvalContext {
    int active;
    Stack s;
    FILE *f_out;
    FILE *f_in;
} EvalContext;

typedef struct Function {
    char *id;
    void (*func)(EvalContext *e);
} Function;

/*
void func_peek(EvalContext *e)
{
    printf("%d\n", e->s.data[e->s.top]);
}

Function func_list[] = {
    { "peek", func_peek }
};
*/

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

char oper_chars[][5] = {
    ['('] = { 0 },
    [')'] = { 0 },
    ['['] = { 0 },
    [']'] = { 0 },
    ['+'] = { '+', 0 },
    ['-'] = { '-', 0 },
    ['*'] = { 0 },
    ['/'] = { 0 },
    ['>'] = { 0 },
    ['<'] = { 0 },
    ['='] = { 0 },
    ['%'] = { 0 }
};

int operate(Stack *s, char *oper)
{
    int result;
    int a, b;

    if (stack_pop(s, &a) < 0)
        return -1; // Stack underflow

    if (stack_pop(s, &b) < 0) {
        stack_push(s, a); // Push back operand
        return -1; // Stack underflow
    }
    
    switch (oper[0]) {
    case '+':
        result = a + b;
        break;

    case '-':
        result = a - b;
        break;

    case '*':
        result = a * b;
        break;

    case '/':
        result = a / b;
        break;

    case '>':
        result = a > b;
        break;

    case '<':
        result = a < b;
        break;
    
    default:
        return -1;
    }

    stack_push(s, result);
    return 0;
}

char *nextchunk(char *c, int *size, CGuess *guess)
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
                float_hint = 1; // If so, store this "hinting."
            } else if (*guess && *guess == GUESS_OPERATOR) {
                for (i = 0; oper_chars[curr_oper][i]; i++)
                    if (oper_chars[curr_oper][i] == *c) {
                        c++;
                        goto end;
                    }
                if (!oper_chars[curr_oper][i])
                    goto end;
            } else if (*guess && *guess != GUESS_OPERATOR) { // Did we just read an entire chunk?
                goto end;
            } else if (!*guess) { // Is this the continuation or the start of a chunk?
                start = c;
                curr_oper = *c;
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

void eval_init(EvalContext *e, FILE *f_in, FILE *f_out)
{
    e->active = 1;
    e->f_in   = f_in;
    e->f_out  = f_out;
    e->s.top  = 0;
}

void eval(EvalContext *e, char *buf)
{
    char *start, *curr = buf;
    CGuess guess;
    int size;

    int numi;
    double numf;

    while ((start = nextchunk(curr, &size, &guess)) != NULL) {
        printf("%d\t%d\t%s\t", (int) (start - buf),
                               (int) (start - buf) + size,
                               guess_strings[guess]);
        fwrite(start, 1, size, e->f_out);
        printf("\n");
        curr = start + size;


        switch (guess) {
            case GUESS_NOUN:
            case GUESS_STRING:
                printf("%s not implemented\n", guess_strings[guess]);
                return;

            case GUESS_OPERATOR:
                if (operate(&e->s, start) < 0)
                    printf("stack underflow\n");
                break;

            case GUESS_INTEGER:
                numi = atoi(start);
                if (stack_push(&e->s, numi) < 0)
                    printf("stack overflow\n");
                break;

            case GUESS_FLOAT:
                numf = atof(start);
                if (stack_push(&e->s, (int) numf) < 0)
                    printf("stack overflow\n");
                break;

            default:
                printf("erroneous input\n");
        }
    }
}

int main(int argc, char **argv)
{
    FILE *f_in  = stdin;
    FILE *f_out = stdout;
    EvalContext e;
    char buf[MAXBUF];
    
    eval_init(&e, f_in, f_out);

    printf("Reverse Polish Expression Calculator\n"
           "Enter an expression. Press CTRL + D to exit.\n\n");
    while (e.active) {
        printf("?> ");
        if (!fgets(buf, MAXBUF, e.f_in)) {
            printf("EOF\n");
            break;
        }
        eval(&e, buf);
        if (!e.s.top) {
            printf("<empty stack>\n");
        } else {
            for (int i = 0; i < e.s.top; i++)
                printf("%d ", e.s.data[i]);
            printf("\n");
        }
    }
    return 0;
}
