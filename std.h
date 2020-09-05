/**
 * \file std.h
 * \author Anamitra Ghorui
 * \brief Calcium standard library functions
 *
 */

#ifndef _CA_STD_H
#define _CA_STD_H

#include "error.h"
#include <math.h>

/// Macro that determines the resultant vartype of a binary operation
// Always remember to provide a cast to indicate the intended type in situations
// like this
#define CA_STD_GET_VAR_TYPE(_x,_y) ((CaVar_TYPE) (_x)->type > \
                                    (_y)->type ? (_x)->type : (_y)->type))

/// Assignment function
#define CA_STD_ASSIGN(_lvalue, _rvalue, _type) \
switch (_type) { \
    case CaVar_TYPE_REAL: \
        (CaReal) (_lvalue)->i = (CaReal) (_rvalue); \
    case CaVar_TYPE_INT: \
        (CA_INT) (_lvalue)->r = (CA_INT) (_rvalue); \
}

/// Macro for generalising binary operators
#define CA_STD_OPERATE(_lvalue,_x,_y,_oper,_type) \
        CA_STD_ASSIGN((_lvalue), (CaReal) (_x)->data, _oper, (CaReal) (_y)->data, _type);

#define CA_STD_BINARY_OPERATOR(_NAME, _SYMBOL) \
inline CaError ca_std_add(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt) \
{                                                                              \
    CA_STD_OPERATE(r, a, b, +, vt);                                            \
    return CA_ERROR_OK;                                                        \
}

 
// Handle Precedence

// Actual functions/operations
// TODO in eval loop: CaVar_TYPE vt = CA_STD_GET_VAR_TYPE(a, b);
// Before every iteration

// ===== Binary Operations =====

// !!TODO Implement Errors regarding overflow, MOD Division types, etc.

// Primitive

inline CaError ca_std_add(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)
{
    CA_STD_OPERATE(r, a, b, +, vt);
    return CA_ERROR_OK;
}

inline CaError ca_std_sub(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)
{
    CA_STD_OPERATE(r, a, b, -, vt);
    return CA_ERROR_OK;
}

inline CaError ca_std_mul(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)
{
    CA_STD_OPERATE(r, a, b, *, vt);
    return CA_ERROR_OK;
}

inline CaError ca_std_div(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)

    CA_STD_OPERATE(r, a, b, /, vt);
    return CA_ERROR_OK;
}

inline CaError ca_std_mod(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)
{
    CA_STD_OPERATE(r, a, b, %, vt);
    return CA_ERROR_OK;
}

inline CaError ca_std_and(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)
{
    CA_STD_OPERATE(r, a, b, &&, vt);
    return CA_ERROR_OK;
}

inline CaError ca_std_or(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)
{
    CA_STD_OPERATE(r, a, b, ||, vt);
    return CA_ERROR_OK;
}

inline CaError ca_std_not(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)
{
    CA_STD_OPERATE(r, a, b, !, vt);
    return CA_ERROR_OK;
}

inline CaError ca_std_band(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)
{
    CA_STD_OPERATE(r, a, b, &, vt);
    return CA_ERROR_OK;
}

inline CaError ca_std_bor(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)
{
    CA_STD_OPERATE(r, a, b, |, vt);
    return CA_ERROR_OK;
}

inline CaError ca_std_bnot(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)
{
    CA_STD_OPERATE(r, a, b, ~, vt);
    return CA_ERROR_OK;
}

inline CaError ca_std_lshift(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)
{
    CA_STD_OPERATE(r, a, b, <<, vt);
    return CA_ERROR_OK;
}

inline CaError ca_std_rshift(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)
{
    CA_STD_OPERATE(r, a, b, >>, vt);
    return CA_ERROR_OK;
}

// Assignment operator !TODO Check Lvalue and Rvalue
inline CaError ca_std_assign(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)
{
     // TODO Write Realloc function
     a->type = b->type;
     a->data = b->data;
     CA_STD_ASSIGN(r, b->data);
     return CA_ERROR_OK;
}

// Non - primitive (Abstract) operations

inline CaError ca_std_pow(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt)
{
     CA_STD_ASSIGN(r, pow(a->data, b->data), vt);
     return CA_ERROR_OK;
}

#endif
