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

typedef enum Precedence {
    PRECEDENCE_POSTFIX_UNARY,
    PRECEDENCE_PREFIX_UNARY,
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

Precedence oper_prec[][5] = {
    ['('] = { 0 },
    [')'] = { 0 },
    ['['] = { 0 },
    [']'] = { 0 },
    ['+'] = { '+', '=', 0 },
    ['-'] = { '-', '=', 0 },
    ['*'] = { '*', '=', 0 },
    ['/'] = { '/', '=', 0 },
    ['>'] = { '=', '>', 0 },
    ['<'] = { '=', '<', 0 },
    ['='] = { '=', 0 },
    ['%'] = { '=', 0 }
};

/*
 * The precedence values correspond 1:1 with the above char values
 */

Precedence oper_prec[][5] = {
    ['('] = { 0 },
    [')'] = { 0 },
    ['['] = { 0 },
    [']'] = { 0 },
    ['+'] = { '+', '=', 0 },
    ['-'] = { '-', '=', 0 },
    ['*'] = { '*', '=', 0 },
    ['/'] = { '/', '=', 0 },
    ['>'] = { '=', '>', 0 },
    ['<'] = { '=', '<', 0 },
    ['='] = { '=', 0 },
    ['%'] = { '=', 0 }
};


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
                float_hint = 1; // If so, store this "hinting"
            } else if (*guess && *guess == GUESS_OPERATOR) {
                for (i = 0; oper_strings[curr_oper][i]; i++)
                    if (oper_strings[curr_oper][i] == *c) {
                        c++;
                        goto end;
                    }
                if (!oper_strings[curr_oper][i])
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

int main(int argc, char **argv)
{
    FILE *f_in  = stdin;
    FILE *f_out = stdout;
    char buf[MAXBUF];
    char *start, *curr = buf;

    CGuess guess;
    int size;
    fgets(buf, MAXBUF, f_in);

    printf("START\tEND\tGUESS\tVALUE\n");
    while ((start = nextchunk(curr, &size, &guess)) != NULL) {
        printf("%d\t%d\t%s\t", (int) (start - buf),
                               (int) (start - buf) + size,
                               guess_strings[guess]);
        fwrite(start, 1, size, f_out);
        printf("\n");
        curr = start + size;
    }
    return 0;
}
