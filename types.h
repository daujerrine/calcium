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

/// Default integer datatype.
typedef int64_t CaInt;

/// Default unsigned integer datatype.
typedef uint64_t CaUint;

/// Datatype for all real numbers.
typedef long double CaReal;

/// Default datatupe for any sort of "size" quantity.
typedef size_t CaSize;

/// Datatype for hashtable keys.
typedef const uint8_t * CaHashKey;

/// Defines types that are used by the interpreter.
typedef enum CaType {
    CA_TYPE_UNKNOWN = 0,
    CA_TYPE_REAL,
    CA_TYPE_INT,
    CA_TYPE_WORD,
    CA_TYPE_KEY,
    CA_TYPE_OPER
} CaType;

typedef enum CaVarType {
    CA_VAR_TYPE_INT = 0,
    CA_VAR_TYPE_REAL,
    CA_VAR_TYPE_FUNC
} CaVarTYPE

typedef struct CaVar {
    void *data;
    CaType type;
} CaVar;

typedef union CaResult {
    CaInt i;
    CaReal r;
} CaResult;

#endif
