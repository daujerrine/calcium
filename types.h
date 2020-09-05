/**
 * \file types.h
 * \author Anamitra Ghorui
 * \brief Typedefs and definitions
 *
 */
#ifndef _CA_TYPES_H
#define _CS_TYPES_H

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
    CaType_UNKNOWN = 0,
    CaType_REAL,
    CaType_INT,
    CaType_WORD,
    CaType_KEY,
    CaType_OPER
} CaType;

typedef enum CaVar_TYPE {
    CaVar_TYPE_INT = 0,
    CaVar_TYPE_REAL,
    CaVar_TYPE_FUNC
} CaVar_TYPE

typedef struct ca_var {
    void *data;
    CaType type;
} ca_var;

typedef union ca_result {
    CA_INT i;
    CaReal r;
}

#endif
