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
 * \file stack.h
 * \author Anamitra Ghorui
 * \brief Stack Implementation
 *
 */

#ifndef _CA_STACK_H
#define _CA_STACK_H
 
/// The maximum size of a stack.
#define CA_STACK_SIZE 4096

/// Structure defining a stack.
typedef struct CaStack {
    CaSize top; /// This is top of the stack, plus one.
    CaSize size;
    CaVar *data;
} CaStack;

/**
 * \brief Initialises a stack.
 * \param size Size of the stack
 */
CaStack *ca_stack_init(size_t size);

/**
 * \brief Frees a stack.
 * \param s the stack pointer
 */
void ca_stack_free(CaStack *s);

/**
 * \brief Enters a key-value pair into a hash table.
 * \param s The hash table.
 * \param value The pointer to the value the key must correspond to.
 * \return An error code.
 */
CaError ca_stack_push(CaStack *s, CaReal value);

/**
 * \brief Get the value of a key from a Stack table a Stack table.
 * \param s The stack.
 * \param value The pointer to to the value that may be returned.
 * \return An error code.
 */
CaError ca_stack_pop(CaStack *s, CaReal *value);

/**
 * \brief Prints all of the contents of the Stack table to stdout. Useful for 
 *        debugging.
 * \param s the stack
 * \return Nothing.
 */
void Ca_StackPrint(CaStack *s);

#endif
