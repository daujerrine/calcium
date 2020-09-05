#include "calcium.h"
#include <stdio.h>

CaStack *ca_stack_init(size_t size)
{
    CaStack *s = malloc(sizeof(CaStack));
    s->data = malloc(size * sizeof(CaReal));
    s->top = 0;
    s->size = size;
    return s;
}

void ca_stack_free(CaStack *s)
{
    free(s->data);
    free(s);
}

CaError ca_stack_push(CaStack *s, CaReal value)
{
    if(s->top > s->size)
        return CA_ERROR_STACK_FULL;
    s->data[s->top] = value;
    (s->top)++;
    return CA_ERROR_OK;
}

CaError ca_stack_pop(CaStack *s, CaReal *value)
{
    if(s->top == 0)
        return CA_ERROR_STACK_EMPTY;
    *value = s->data[s->top - 1];
    (s->top)--;
    return CA_ERROR_OK;
}

void ca_stack_print(CaStack *s)
{
    printf("CaStack; addr = %lx top = %ld; size = %ld;\n", 
           (unsigned long) s, s->top, s->size);
    for(size_t i = 0; i < s->top; ++i)
        printf("[%ld] = %Lf\n", i,  s->data[i]);
}
