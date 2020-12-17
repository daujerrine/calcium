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
 * \file interpreter.h
 * \author Anamitra Ghorui
 * \brief Calcium interpreter program
 */

#ifndef CA_INTERPRETER_H
#define CA_INTERPRETER_H

#include "eval.h"
#include "calcium.h"

#define CA_INTERACTIVE_PROMPT_STR ":"
#define CA_INTERACTIVE_BLOCK_STR "::"

/**
 * \brief Brings up an interactive interpreter
 * \param f_in File Object used for input data
 * \param f_out File Object used for output data
 * \param f_err File Object used for error output
 */
void ca_start_interactive(FILE *f_in, FILE *f_out, FILE *f_err);

/**
 * \brief Brings up an interpreter
 * \param f_in File Object used for input data
 * \param f_out File Object used for output data
 * \param f_err File Object used for error output
 */
void ca_start_interpreter(FILE *f_in, FILE *f_out, FILE *f_err);

#endif
