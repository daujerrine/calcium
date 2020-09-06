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
 * \file hashmap.h
 * \author Anamitra Ghorui
 * \brief Hashmap Implementation
 *
 * TODO: Implement entry relocation based on frequency of access
 */

#ifndef _CA_HASHMAP_H
#define _CA_HASHMAP_H

#include "types.h"
#include "debug.h"

#include <string.h>
#include <stdio.h>

 
/// Returns the offset of the hashtable array for a given letter. Returns -1 if
/// letter is out of bounds.
/// Refer to the implementation details for more information.
#define CA_HASH_KEY_INDEX(x) (((x) >= 'A' && (x) <= 'Z') ? ((x) - 'A') : \
                             ((x) >= 'a' && (x) <= 'z') ? ((x) - 'a') : \
                             ((x) == '_') ? (Ca_HASH_SIZE - 1) : -1)

/// The maximum size of a hashtable key.
#define CA_HASH_KEY_SIZE 31

/// The number of elements in the hash data structure, corresponding to the
/// number of capital and small letters together in the English language, plus
/// underscore.
#define CA_HASH_SIZE 53

/// Defines a hashmap/hashtable node. This is a linked-list based hashmap 
/// meant to store user variables.
typedef struct CaHashNode CaHashNode;

struct CaHashNode {
    void *data;
    CaHashNode *next;
    CaType type;
    CaHashKey key;
};

/// Defines a hashmap/hashtable
typedef CaHashNode **CaHash;

/**
 * \brief Initialises a hash table.
 */
CaHash ca_hash_init();

/**
 * \brief Frees a hash table.
 */
void ca_hash_free(CaHash map);

CaHashNode *ca_hash_node_init(CaHashKey key, CaSize size, CaType type,
                              void *data);
/// TODO document
void ca_hash_node_free(CaHashNode *h);

/**
 * \brief Enters a key-value pair into a hash table.
 * \param table The hash table.
 * \param key The key to enter.
 * \param value The pointer to the value the key must correspond to.
 * \return An error code.
 */
CaError ca_hash_set(CaHash map, CaHashKey key, CaSize size, CaType type,
                    void *data);

/**
 * \brief Get the value of a key from a hash table a hash table.
 * \param table The hash table.
 * \param key The key to enter.
 * \param value The pointer to to the value that may be returned.
 * \return An error code.
 */
CaError ca_hash_get(CaHash map, CaHashKey key, CaSize size, 
                    CaHashNode **h);

/**
 * \brief Prints all of the contents of the hash table to stdout.
 *        Meant for debugging purposes.
 * \param table The hash table.
 * \return An error code.
 */
CaError ca_hash_print(CaHash map);

#endif
