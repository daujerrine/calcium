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
 * \file error.h
 * \author Anamitra Ghorui
 * \brief Calcium error codes
 *
 */

#ifndef _CA_ERROR_H
#define _CA_ERROR_H

/*
 * Actual errors always will have a less than 0 value
 * Success is always 0
 * Private errors range from 0x1 to 0xFFF
 * Info errors start from 0x1000
 */

/// Datatype for error codes.
typedef enum CaError {
    /* Actual Errors */
    CA_ERROR_HASH_INVALID_KEY = -0x1000,
    CA_ERROR_HASH_NOTFOUND,
    CA_ERROR_STACK_FULL,
    CA_ERROR_STACK_EMPTY,
    
    CA_ERROR_OK = 0,

    /* Info Errors */
    CA_ERROR_HASH_NEW = 0x1000,
    CA_ERROR_HASH_EXISTING,
} CaError;

#endif
