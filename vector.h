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
 * \file vector.h
 * \author Anamitra Ghorui
 * \brief Vector array implementation
 */

#ifndef _CA_VECTOR_H
#define _CA_VECTOR_H

#include "mem.h"

/*
 * The size of a vector increases by two everytime size limit is reached.
 */

typedef struct CaVector {
    size_t elem_size;
    size_t size;
    size_t top;
    void *buf;
} CaVector;

CaVector *ca_vector_init(size_t elem_size, size_t size);

void ca_vector_free(CaVector *v);

CaVector *ca_vector_grow(CaVector *v, size_t increment);

CaVector *ca_vector_shrink(CaVector *v, size_t new_size);

inline void *ca_vector_get(CaVector *v, size_t index)
{
    return *(((uint8_t *) v->buf) + v->elem_size * index)
}

inline void ca_vector_set(CaVector *v, size_t index, void *ptr)
{
    memcpy((((uint8_t *) v->buf) + v->elem_size * index), ptr, v->elem_size);
}

inline void ca_vector_push(CaVector *v, void *ptr)
{
    if (v->top + 1  == v->size) {
        
    }
}

#define VGET(v, i) ca_vector_get((v), (i));
#define VSET(v, i, p) ca_vector_get((v), (i), (p));

#endif
