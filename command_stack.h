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
 * \file command_stack.c
 * \author Anamitra Ghorui
 * \brief Internal subsystem instruction opcodes
 */

/*
 * Opcodes define how data is processed and in what order. Two separate stacks
 * are kept, one for data, and one for commands on the data.
 */

typedef enum CaOpcode {
    CA_OPCODE_EXT_CALL,
    CA_OPCODE_
} CaOpcode;
