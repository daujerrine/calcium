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
 * \file error.h
 * \author Anamitra Ghorui
 * \brief Calcium error codes
 *
 */

#ifndef CA_ERROR_H
#define CA_ERROR_H

/*
 * Actual errors always will have a less than 0 value
 * Success is always 0
 * Private errors range from 0x1 to 0xFFF
 * Info errors start from 0x1000.
 */

/// Datatype for error codes.
typedef enum CaError {
    /* Actual Errors */
    CA_ERROR_HASH_INVALID_KEY = -0x1000,
    CA_ERROR_HASH_NOTFOUND,
    CA_ERROR_STACK_FULL,
    CA_ERROR_STACK_EMPTY,
    CA_ERROR_EVAL,
    CA_ERROR_EVAL_SYNTAX_NO_OPENING_PARANTHESIS,
    CA_ERROR_EVAL_SYNTAX_NO_CLOSING_PARANTHESIS,
    
    CA_ERROR_OK = 0,

    /* Info Errors */
    CA_ERROR_HASH_NEW = 0x1000,
    CA_ERROR_HASH_EXISTING,
} CaError;

#define ERRKEY(_code, _str) [_code + 0x1000] = _str

char *ca_error_strings[] = {
    ERRKEY(CA_ERROR_HASH_INVALID_KEY, "Erroneous hash key: %s"),
    ERRKEY(CA_ERROR_HASH_NOTFOUND, "Key not found in table: %s"),
    ERRKEY(CA_ERROR_STACK_FULL, "Stack Overflow"),
    ERRKEY(CA_ERROR_STACK_EMPTY, "Stack Underflow"),
    ERRKEY(CA_ERROR_EVAL, "Evaluation Error")
};

#endif
