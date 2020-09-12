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

#include "hashmap.h"

/**
 * The hash map is simply an array of linked lists, which are the entries for
 * several key-value pairs.
 * 
 * \code
 * A -> k1 -> k2 -> NULL
 * B -> ...
 * C -> NULL
 * ...
 * x ...
 * y ...
 * z ...
 * _ ...
 *
 * On getting a hit, the hit is put at the start of the linked list.
 */

CaHash ca_hash_init()
{
    CaHash h = ca_mallocarray(CA_HASH_SIZE, sizeof(CaHashNode *));
    return h;
}

CaHashNode *ca_hash_node_init(CaHashKey key, CaSize size, CaType type, 
                              void *data)
{
    // TODO Type management
    size = size > CA_HASH_KEY_SIZE ? CA_HASH_KEY_SIZE : size;
    CaHashNode *h = malloc(sizeof(CaHashNode));
    char *nkey = malloc(size + 1);
    strncpy(nkey, key, size + 1);
    h->key  = nkey;
    h->data = data;
    h->next = NULL;
    h->type = type;
    return h;
}

void ca_hash_node_free(CaHashNode *h)
{
    ca_freep((&((char *) h->key));
    // TODO Deallocate data.
    ca_freep(&h);
}

void ca_hash_free(CaHash map)
{
    CaHashNode *k1, *k2;
    for (int i = 0; i < CA_HASH_SIZE; ++i) {
        for (k1 = map[i]; k1 != NULL;) {
            k2 = k1->next;
            ca_hash_node_free(k1);
            k1 = k2;
        }
    }
    free(map);
}

CaError ca_hash_set(CaHash map, CaHashKey key, CaSize size, CaType type,
                    void *data)
{
    CaSize index = CA_HASH_KEY_INDEX(key[0]);
    CaHashNode *k = map[index];
    
    if (size <= 0 || CA_HASH_KEY_INDEX(key[0]) < 0)
        return CA_ERROR_HASH_INVALID_KEY;

    if (map[index] == NULL) {
        map[index] = ca_hash_node_init(key, size, type, data);
        return CA_ERROR_HASH_NEW;
    }

    while (k->next != NULL) {
        if (strncmp(key, k->key, CA_HASH_KEY_SIZE) == 0) {
            k->data = data;
            k->type = type;
            return CA_ERROR_HASH_EXISTING;
        }   
        k = k->next;
    }

    if (strcmp(key, k->key) == 0) {
        k->data = data;
        k->type = type;
        return CA_ERROR_HASH_EXISTING;
    }

    k->next = ca_hash_node_init(key, size, type, data);
    return CA_ERROR_HASH_NEW;
}

CaError ca_hash_get(CaHash map, CaHashKey key, CaSize size, CaHashNode **h)
{
    CaSize index = CA_HASH_KEY_INDEX(key[0]);
    size = size > CA_HASH_KEY_SIZE ? CA_HASH_KEY_SIZE : size;
    *h =  map[index];
    
    if ((size <= 0) || CA_HASH_KEY_INDEX(key[0]) < 0) {
        return CA_ERROR_HASH_INVALID_KEY;
    }
    CA_DBG_PLN
    while (*h != NULL) {
        CA_DBG_PLN
        if (strncmp(key, (*h)->key, CA_HASH_KEY_SIZE) == 0) {
            return CA_ERROR_OK;
        }
        CA_DBG_PLN
        *h = (*h)->next;
    }
    CA_DBG_PLN
    return CA_ERROR_HASH_NOTFOUND;
}

CaError ca_hash_print(CaHash map)
{
    for (char i = 0; i < CA_HASH_SIZE; ++i) {
        for (CaHashNode *h = map[i]; h != NULL; h = h->next) {
            printf("%s: %d, ", h->key,  *((int *) h->data));
        }
    }
    printf("\n");
}
