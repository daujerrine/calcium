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
 * \file std.h
 * \author Anamitra Ghorui
 * \brief Calcium standard library functions
 *
 */

#ifndef CA_STD_H
#define CA_STD_H

#include "error.h"
#include <math.h>

/// Macro that determines the resultant vartype of a binary operation

// Always remember to provide a cast to indicate the intended type in situations
// like this
#define CA_STD_GET_VAR_TYPE(_x,_y) ((CaVarType) (_x)->type > \
                                    (_y)->type ? (_x)->type : (_y)->type))

/// Assignment function

#define CA_STD_ASSIGN(_lvalue,_rvalue,_type) \
switch (_type) { \
case CaVar_TYPE_REAL: \
    (CaReal) (_lvalue)->i = (CaReal) (_rvalue); \
case CaVar_TYPE_INT: \
    (CaInt) (_lvalue)->r = (CaInt) (_rvalue); \
}

/// Macro for generalising binary operators

#define CA_STD_OPERATE(_lvalue,_x,_y,_oper,_type) \
        CA_STD_ASSIGN((_lvalue), (CaReal) (_x)->data, _oper, (CaReal) (_y)->data, _type);

#define CA_STD_PRIMITIVE_BINARY_OPERATOR(_NAME, _SYMBOL) \
inline CaError ca_std_prim_ ## _NAME ## (CaResult *r, CaVar *a, CaVar *b, CaVarType vt) \
{ \
    CA_STD_OPERATE(r, a, b, _SYMBOL, vt); \
    return CA_ERROR_OK; \
}

 
// Handle Precedence

// Actual functions/operations
// TODO in eval loop: CaVarType vt = CA_STD_GET_VAR_TYPE(a, b);
// Before every iteration

// ===== Binary Operations =====

// !!TODO Implement Errors regarding overflow, MOD Division types, etc.

/*
 * Primitive Operations
 *
 * These are only concerned with primitive types. The interpreter shall forward
 * the computation to these operations to  these primitive functions (by using
 * the wrapper function for all of these operations)
 */

CA_STD_PRIMITIVE_BINARY_OPERATOR(add, +)
CA_STD_PRIMITIVE_BINARY_OPERATOR(div, -)
CA_STD_PRIMITIVE_BINARY_OPERATOR(mul, *)
CA_STD_PRIMITIVE_BINARY_OPERATOR(sub, /)
CA_STD_PRIMITIVE_BINARY_OPERATOR(mod, %)

CA_STD_PRIMITIVE_BINARY_OPERATOR(and, &&)
CA_STD_PRIMITIVE_BINARY_OPERATOR(or , ||)
CA_STD_PRIMITIVE_BINARY_OPERATOR(not, !)

CA_STD_PRIMITIVE_BINARY_OPERATOR(band, &)
CA_STD_PRIMITIVE_BINARY_OPERATOR(bor , |)
CA_STD_PRIMITIVE_BINARY_OPERATOR(bnot, ~)
CA_STD_PRIMITIVE_BINARY_OPERATOR(bxor, ^)

CA_STD_PRIMITIVE_BINARY_OPERATOR(lshift, <<)
CA_STD_PRIMITIVE_BINARY_OPERATOR(rshift, >>)


// Assignment operator
// TODO handle non primitive types
inline CaError ca_std_assign(CaResult *r, CaVar *a, CaVar *b, CaVarType vt)
{
     // TODO Write Realloc function
     a->type = b->type;
     a->data = b->data;
     CA_STD_ASSIGN(r, b->data);
     return CA_ERROR_OK;
}

/*
 * Non - primitive (Abstract) operations
 */

CaError ca_std_pow(CaResult *r, CaVar *a, CaVar *b, CaVarType vt)
{
     CA_STD_ASSIGN(r, pow(a->data, b->data), vt);
     return CA_ERROR_OK;
}

#endif
