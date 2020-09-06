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
 * \file mem.h
 * \author Anamitra Ghorui
 * \brief Calcium memory allocation functions
 *
 */


#ifndef _CALCIUM_H
#define _CALCIUM_H

#include <stdlib.h>


/*
 * Upper bound of any integer type will be a power of 2 minus 1 (say upper bound
 * is 2 ** n - 1).
 * The largest multiplication possible is therefore X * Y where X 
 * 
 */
#define INT_MUL_OVERFLOW(a, b) \
{ \
    
}

void *ca_malloc(size_t size)
{
    return malloc(size);
}

void *ca_mallocz(size_t size)
{
    return calloc(size, 1);
}

void *ca_realloc_f(void *ptr, size_t size)
{
    void *ret;
    ret = realloc(ptr, size);
    if (!ret)
        free(ptr);
    return ret;
}

#endif
