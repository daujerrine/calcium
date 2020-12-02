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
 * \file types.h
 * \author Anamitra Ghorui
 * \brief Typedefs and definitions
 *
 */

#ifndef _CA_TYPES_H
#define _CA_TYPES_H

#include <stdlib.h>
#include <stdint.h>

/// Default Charater Datatype (Non UTF-8)
typedef uint8_t CaChar;

/// Default integer datatype.
typedef int64_t CaInt;

/// Default unsigned integer datatype.
typedef uint64_t CaUint;

/// Datatype for all real numbers.
typedef long double CaReal;

/// Default datatupe for any sort of "size" quantity.
typedef size_t CaSize;

/// Default datatype for mutable objects
typedef void * CaObjPtr;

/// Datatype for hashtable keys.
typedef const uint8_t * CaHashKey;

/// Defines types that are used by the interpreter.
/// All types except for OBJ (classes) are directly handled by the system.
typedef enum CaType {
    CA_TYPE_UNKNOWN = 0,
    CA_TYPE_REAL,
    CA_TYPE_INT,
    CA_TYPE_STRING,
    CA_TYPE_DICT,
    CA_TYPE_SET,
    CA_TYPE_LIST,
    CA_TYPE_TUPLE,
    CA_TYPE_OBJ
} CaType;

typedef enum CaGuess {
    CA_GUESS_INT = 0,
    CA_GUESS_REAL,
    CA_GUESS_OPER,
    CA_GUESS_WORD
} CaVarGuess;

typedef union CaValue {
    CaInt i,
    CaChar c,
    CaReal f,
    CaObjPtr *p
} CaValue;

typedef struct CaVar {
    CaValue value;
    CaType type;
} CaVar;

typedef union CaResult {
    CaInt i;
    CaReal r;
} CaResult;


#define ca_t_str(a)   ((a).type == CA_TYPE_STRING)
#define ca_t_int(a)   ((a).type == CA_TYPE_INT)
#define ca_t_real(a)  ((a).type == CA_TYPE_REAL)
#define ca_t_dict(a)  ((a).type == CA_TYPE_DICT)
#define ca_t_set(a)   ((a).type == CA_TYPE_SET)
#define ca_t_list(a)  ((a).type == CA_TYPE_LIST)
#define ca_t_tuple(a) ((a).type == CA_TYPE_TUPLE)

// May change later
#define ca_t_obj(a)   ((a).type == CA_TYPE_OBJ)
#define ca_objtype(a) (((void *) (a).value)->type)
#endif
