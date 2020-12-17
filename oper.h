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

#ifndef CA_OPER_H
#define CA_OPER_H

#include "std.h"
#include "types.h"

#include <stdint.h>

#define CA_MAX_OPER_LEN 3


/*
 * Only the following symbols ca be used in operator expressions:
 * '+' '-' '*' '/' '>' '<' '.' '!' '@' '#' '$' '%' '^' '&' '|' '~'
 */

typedef enum CaOperPrec {
    PRECEDENCE_INVALID = -1,
    PRECEDENCE_UNKNOWN = 0,
    PRECEDENCE_UNARY = 1,
    PRECEDENCE_EXPONENTIAL,
    PRECEDENCE_MULTIPLICATIVE,
    PRECEDENCE_ADDITIVE,
    PRECEDENCE_SHIFT,
    PRECEDENCE_COMPARISON,
    PRECEDENCE_EQUALITY,
    PRECEDENCE_B_AND,
    PRECEDENCE_B_XOR,
    PRECEDENCE_B_OR,
    PRECEDENCE_AND,
    PRECEDENCE_OR,
    PRECEDENCE_ASSIGNMENT
} CaOperPrec;

typedef enum CaOperID {
    OPER_ID_INCREMENT = 0,
    OPER_ID_DECREMENT,
    OPER_ID_B_NOT,
    OPER_ID_POWER,
    OPER_ID_MULTIPLICATION,
    OPER_ID_DIVISION,
    OPER_ID_REMAINDER,
    OPER_ID_ADDITION,
    OPER_ID_SUBTRACTION,
    OPER_ID_LSHIFT,
    OPER_ID_RSHIFT,
    OPER_ID_LT,
    OPER_ID_LTEQ,
    OPER_ID_GT,
    OPER_ID_GTEQ,
    OPER_ID_EQ,
    OPER_ID_NEQ,
    OPER_ID_B_AND,
    OPER_ID_B_XOR,
    OPER_ID_B_OR,
    OPER_ID_AND,
    OPER_ID_OR,
    OPER_ID_ASSIGN,
    OPER_ID_ADDITION_ASSIGN,
    OPER_ID_SUBTRACTION_ASSIGN,
    OPER_ID_MULTIPLICATION_ASSIGN,
    OPER_ID_DIVISION_ASSIGN,
    OPER_ID_REMAINDER_ASSIGN,
    OPER_ID_NEST,
    OPER_ID_NEST_CLOSE
} CaOperID;


/* TODO Rearrange extra symbol to end */

typedef struct CaOperator {
    char extra_symbol;
    CaOperID id;
    CaOperPrec prec;
} Operator;


CaOperator oper_list[][5] = {
    /*    OPER  OPER_ID                        PRECEDENCE                     */
    ['('] =
    {
        { '\0', OPER_ID_NEST,                  PRECEDENCE_INVALID        },
        { 0 }
    },
    [')'] = {
        { '\0', OPER_ID_NEST_CLOSE,            PRECEDENCE_INVALID        },
        { 0 }
    },

    ['['] = { { '\0' }, { 0 } },
    [']'] = { { '\0' }, { 0 } },

    ['+'] =
    {
        { '\0', OPER_ID_ADDITION,              PRECEDENCE_ADDITIVE       },
        { '+',  OPER_ID_INCREMENT,             PRECEDENCE_UNARY          },
        { '=',  OPER_ID_ADDITION_ASSIGN,       PRECEDENCE_ASSIGNMENT     },
        { 0 }                                  
    },                                         
    ['-'] =                                    
    {                                          
        { '\0', OPER_ID_SUBTRACTION,           PRECEDENCE_ADDITIVE       },
        { '-',  OPER_ID_DECREMENT,             PRECEDENCE_UNARY          },
        { '=',  OPER_ID_SUBTRACTION_ASSIGN,    PRECEDENCE_ASSIGNMENT     },
        { 0 }
    },
    ['*'] =
    {
        { '\0', OPER_ID_MULTIPLICATION,        PRECEDENCE_MULTIPLICATIVE },
        { '*',  OPER_ID_POWER,                 PRECEDENCE_EXPONENTIAL    },
        { '=',  OPER_ID_MULTIPLICATION_ASSIGN, PRECEDENCE_ASSIGNMENT     },
        { 0 }
    },
    ['/'] =
    {
        { '\0', OPER_ID_DIVISION,              PRECEDENCE_MULTIPLICATIVE },
        { '/',  OPER_ID_DIVISION,              PRECEDENCE_MULTIPLICATIVE },
        { '=',  OPER_ID_DIVISION_ASSIGN,       PRECEDENCE_ASSIGNMENT     },
        { 0 }
    },
    ['>'] =
    {
        { '\0', OPER_ID_GT,                    PRECEDENCE_COMPARISON     },
        { '=',  OPER_ID_GTEQ,                  PRECEDENCE_COMPARISON     },
        { '>',  OPER_ID_RSHIFT,                PRECEDENCE_SHIFT          },
        { 0 }
    },
    ['<'] =
    {
        { '\0', OPER_ID_LT,                    PRECEDENCE_COMPARISON     },
        { '=',  OPER_ID_LTEQ,                  PRECEDENCE_COMPARISON     },
        { '<',  OPER_ID_LSHIFT,                PRECEDENCE_SHIFT          },
        { 0 }
    },
    ['='] =
    {
        { '\0', OPER_ID_ASSIGN,                PRECEDENCE_ASSIGNMENT     },
        { '=',  OPER_ID_EQ,                    PRECEDENCE_EQUALITY       },
        { 0 }
    },
    ['%'] =
    {
        { '\0', OPER_ID_REMAINDER,             PRECEDENCE_MULTIPLICATIVE },
        { '=',  OPER_ID_REMAINDER_ASSIGN,      PRECEDENCE_ASSIGNMENT     },
        { 0 }
    },
};
#endif
