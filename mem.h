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
 * Upper bound of any unsigned integer type will be a power of 2 minus 1
 * (say upper bound is 2 ** n - 1).
 * The largest multiplication possible is therefore X * Y where:
 * 1. either X or Y shouldn't be >= 2 ^ (n / 2).
 * 2. If above is true then at least one of the operands should not be greater
 *    than 2.
 * 3. The multiplication should not be lossy, if both the above conditions are
 *    true.
 * 
 */
#define CHECK_INT_MUL_OVERFLOW(a, b, m) \
( \
    ((a | b) >= (1 << (sizeof(a) / 2))) &&
    a && b &&  ((m / b) != b)
)

/**
* \brief Allocates a block of data of size bytes.
* \return Pointer to allocated data on success, NULL on failure.
*/
void *ca_malloc(size_t size);

/**
* \brief Allocates a block of data of nelem elements of elem_size bytes.
* \return Pointer to allocated data on success, NULL on failure.
*/
void *ca_mallocarray(size_t elem_size, size_t nelem);

/**
* \brief Allocates a block of data of size bytes and zero initialises whole block.
* \return Pointer to allocated data on success, NULL on failure.
*/
void *ca_mallocz(size_t size);

/**
* \brief Allocates a block of data of nelem elements of elem_size bytes and zero
*        initialises the whole block.
* \return Pointer to allocated data on success, NULL on failure.
*/
void *ca_malloczarray(size_t elem_size, size_t nelem);

/**
* \brief Allocates, Frees or Resizes a block of memory. If the function fails to
*        allocate memory, the initial block is freed.
* \return Pointer to allocated data on success, NULL on failure.
*/
void *ca_realloc_f(void *ptr, size_t size);

/**
* \brief Allocates, Frees or Resizes a block of memory to nelem elements of
*        elem_size bytes. If the function fails to allocate memory, the initial
*        block is freed.
* \return Pointer to allocated data on success, NULL on failure.
*/
void *ca_reallocarray_f(void *ptr, size_t elem_size, size_t nelem);

/**
* \brief Frees a pointer pointed to by the argument, and then set the pointer
*        pointed to to NULL.
* \return Nothing
*/
void ca_freep(void **ptr);

#endif
