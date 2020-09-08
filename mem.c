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
 * \file mem.c
 * \author Anamitra Ghorui
 * \brief Calcium memory allocation functions
 */

void *ca_malloc(size_t size)
{
    return malloc(size);
}

void *ca_mallocarray(size_t elem_size, size_t nelem)
{
    size_t mul =  elem_size * size;
    if (CHECK_INT_MUL_OVERFLOW(elem_size, size, mul))
        return NULL
    else
        return malloc(mul);
}

void *ca_mallocz(size_t size)
{
    return calloc(size, 1);
}

void *ca_malloczarray(size_t elem_size, size_t nelem)
{
    return calloc(size, elem_size);
}

void *ca_realloc_f(void *ptr, size_t size)
{
    void *ret;
    ret = realloc(ptr, size);
    if (!ret)
        free(ptr);
    return ret;
}

void *ca_reallocarray_f(void *ptr, size_t size)
{
    void *ret;
    size_t mul =  elem_size * size;
    if (CHECK_INT_MUL_OVERFLOW(elem_size, size, mul))
        ret = NULL;
    else
        ret = realloc(ptr, mul);
    if (!ret)
        free(ptr);
    return ret;
}

void ca_freep(void **ptr)
{
    if (*ptr)
        return;
    free(*ptr);
    *ptr = NULL;
}
