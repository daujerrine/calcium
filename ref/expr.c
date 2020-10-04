#include <stdio.h>

#define MAXBUF 4096

#define CIN_RANGE(x, l, h) (((x) >= (l)) && ((x) <= (h)))
#define CIS_ALPHA(x)  (CIN_RANGE(x, 0x41, 0x5A) || \
                      CIN_RANGE(x, 0x61, 0x7A))
#define CIS_NUMBER(x) (CIN_RANGE(x, 0x30, 0x39)) 
#define CIS_SYMBOL(x) (CIN_RANGE(x, 0x21, 0x2F) || \
                      CIN_RANGE(x, 0x3A, 0x40) || \
                      CIN_RANGE(x, 0x5B, 0x60) || \
                      CIN_RANGE(x, 0x7B, 0x7E)) \

typedef enum CGuess {
    GUESS_UNKNOWN = 0,
    GUESS_ERROR,
    GUESS_NEED_MORE_DATA,
    GUESS_NUMBER,
    GUESS_OPERATOR,
    GUESS_NOUN,
    GUESS_STRING
} CGuess;

char *guess_strings[] = {
    [GUESS_UNKNOWN]        = "unknown",
    [GUESS_ERROR]          = "error",
    [GUESS_NEED_MORE_DATA] = "incomplete",
    [GUESS_NUMBER]         = "num",
    [GUESS_OPERATOR]       = "oper",
    [GUESS_NOUN]           = "noun",
    [GUESS_STRING]         = "string"
};

char *nextchunk(char *c, int *size, CGuess *guess)
{
    *guess = GUESS_UNKNOWN;
    char *start = NULL;
    int delimited_chunk = 0;

    while (*c) {
        switch (*c) {
        case ' ': case '\n': case '\t':
            if (*guess)
                goto end;
            goto next;

        case '"':
            start = c;
            while ((*++c) && *c != '"');
            if (*c != '"') {
                *guess = GUESS_ERROR;
                goto end;
            } else {
                *guess = GUESS_STRING;
                c++;
                goto end;
            }
        }

        if (CIS_SYMBOL(*c)) {
            if (*guess && *guess != GUESS_OPERATOR)
                goto end;
            else if (!*guess)
                start = c;
            *guess = GUESS_OPERATOR;
        } else if (CIS_ALPHA(*c)) {
            if (*guess && *guess != GUESS_NOUN)
                goto end;
            else if (!*guess)
                start = c;
            *guess = GUESS_NOUN;
        } else if (CIS_NUMBER(*c)) {
            if (*guess && *guess != GUESS_NUMBER)
                goto end;
            else if (!*guess)
                start = c;
            *guess = GUESS_NUMBER;
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
        printf("%d\t%d\t%s\t", (int) (start - buf),\
                               (int) (start - buf) + size,\
                               guess_strings[guess]);
        fwrite(start, 1, size, f_out);
        printf("\n");
        curr = start + size;
    }
    return 0;
}
