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
 * \file vector.c
 * \author Anamitra Ghorui
 * \brief Vector array implementation
 *
 */


CaVector *ca_vector_init(size_t elem_size, size_t nelem)
{
    CaVector *ret = ca_malloc(sizeof(*ret));
    ret->elem_size = elem_size;
    ret->size = size;
    ret->top = 0;
    ret->buf = ca_mallocarray(elem_size, nelem);
}

void ca_vector_free(CaVector *v)
{
    ca_freep(&v->buf);
    ca_freep(&v);
}

CaVector *ca_vector_grow(CaVector *v, size_t increment)
{
    // TODO manage freeing
    return ca_reallocarray_f(v->buf, v->elem_size, CLAMP(v->size + increment));
}

CaVector *ca_vector_shrink(CaVector *v, size_t new_size)
{
    v->size = new_size;
    return ca_realloc_f(v->buf, v->elem_size, new_size);
}
}
