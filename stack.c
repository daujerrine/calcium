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
