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

#ifndef _CA_OPER_H
#define _CA_OPER_H

#include "std.h"
#include "types.h"

#include <stdint.h>

#define CA_MAX_OPER_LEN 3

typedef enum CaOperatorProperties {
    CA_ASSOC_LEFT = 0,
    CA_ASSOC_RIGHT,
    
    CA_ASSIGNMENT = 0x1000
    CA_CONDITIONAL,  /// Not implemented yet.
    CA_ADDITIVE,
    CA_MULTIPLICATIVE,
    CA_BITWISE,
    CA_EXPONENTIAL  /// Not implemented yet.
}

/// Describes an operator
typedef struct CaOperator {
    char symbol[CA_MAX_OPER_LEN]; /// Symbol string of ooperator
    uint8_t assoc;  /// Associavity of operator
    uint16_t prec;  /// Precedence of the operator. Higher the number, higher
                    /// the priority.
    CaError (*func)(ca_result *r, ca_var *a, ca_var *b, CaVar_TYPE vt);
} CaOperator;

// Char arrays are used to prevent null chars
CaOperator ca_oper_list[] {
    {{'='}, CA_ASSOC_RIGHT, CA_ASSIGNMENT, &ca_std_assign},
    
    {{'+'}, CA_ASSOC_LEFT, CA_ADDITIVE, &ca_std_add},
    {{'-'}, CA_ASSOC_LEFT, CA_ADDITIVE, &ca_std_sub},

    {{'*'}, CA_ASSOC_LEFT, CA_MULTIPLICATIVE, &ca_std_mul},
    {{'/'}, CA_ASSOC_LEFT, CA_MULTIPLICATIVE, &ca_std_div},
    {{'%'}, CA_ASSOC_LEFT, CA_MULTIPLICATIVE, &ca_std_mod},

   // {{'*', '*'}, CA_ASSOC_LEFT, CA_EXPONENTIAL}, Not implemented yet
}

#endif
