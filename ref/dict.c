/*
 * Copyright (c) 2020 Anamitra Ghorui
 * This file is part of Calcium. See Calcium's licensing information for
 * details.
 */

/*
 * Dictionary implementation
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

typedef struct DictEntry {
    char key[32];
    char occupied;
    int value;
} DictEntry;

typedef struct Dictionary {
    DictEntry *data;
    size_t size;
    size_t entries_left;
} Dictionary;


void flush_input()
{
    char c;
    while ((c = getchar()) != EOF && c != '\n');
}

int hash(Dictionary *dict, char *key)
{
    unsigned int ret = 0;
    for (;*key != '\0'; key++) {
        // printf("key = %d, ret = %u\n", *key, ret);
        ret = (ret * 25 + (*key) + 1);
    }
    ret %= dict->size;

    return ret;
}

void dict_init(Dictionary *dict)
{
    dict->data = calloc(7, sizeof(*dict->data));
    dict->entries_left = dict->size = 7;
    
}

// Naive implementation. Replace later.

int is_prime(int p)
{
    if (p % 2 == 0)
        return 0;

    // TODO  Manage overflow
    for (int i = 3; i <= sqrt(p); i += 2) {
        if (p % i == 0)
            return 0;
    }

    return 1;
}

int next_prime(int p)
{
    int mult = p / 6;
    int ret;

    if (!is_prime(p)) {
        // check 6n + 1
        ret = mult * 6 + 1;
        if (is_prime(ret))
            return ret;

        ret += 4;
        if (is_prime(ret))
            return ret;
    }

    mult++;
    ret = mult * 6;

    while (1) {

        ret++;

        if (is_prime(ret))
            return ret;

        ret += 4;

        if (is_prime(ret))
            return ret;

        ret++;
    }
    
}

int set(Dictionary *dict, char *key, int value);

void dict_close(Dictionary *dict)
{
    free(dict->data);
    dict->data = NULL;
    dict->size = 0;
}

void dict_grow(Dictionary *dict)
{
    DictEntry *ptr;
    Dictionary old_dict;

    memcpy(&old_dict, dict, sizeof(old_dict));

    size_t next_size = next_prime(dict->size * 2);
    ptr = reallocarray(NULL, next_size, sizeof(*ptr));

    if (!ptr) {
        free(dict->data);
        assert(ptr /* Could not allocate data */);
    }

    dict->data = ptr;
    dict->size = next_size;
    dict->entries_left = next_size;
    memset(dict->data, 0, dict->size * sizeof(*dict->data));

    for (int i = 0; i < old_dict.size; i++) {
        if (old_dict.data[i].occupied)
            set(dict, old_dict.data[i].key, old_dict.data[i].value);
    }

    dict_close(&old_dict);
}

int set(Dictionary *dict, char *key, int value)
{
    int index;
    int init_index;

    printf("left: %ld\n", dict->entries_left);

    if (dict->entries_left == 0) {
        printf("growing\n");
        dict_grow(dict);
    }

    index = hash(dict, key);
    init_index = index;

    if (dict->data[index].occupied) // if not same key, go to next
        if (strcmp(key, dict->data[index].key))
            index = (index + 1) % dict->size;
        else
            goto key_exists_end;
    else
        goto end;

    while (index != init_index &&
           dict->data[index].occupied &&
           strcmp(key, dict->data[index].key)) {
        index = (index + 1) % dict->size;
        printf("%d\n", index);
    }

    if (index == init_index)
        return -1;

end:
    strncpy(dict->data[index].key, key, 31);
    dict->entries_left--;

key_exists_end:
    dict->data[index].occupied = 1;
    dict->data[index].value = value;

    return 0;
}

DictEntry *get(Dictionary *dict, char *key)
{
    int index = hash(dict, key);
    int init_index = index;

    if (dict->data[index].occupied)
        if (strcmp(key, dict->data[index].key))
            index = (index + 1) % dict->size;
        else
            goto end;
    else
        return NULL;

    while (index != init_index) {
        if (dict->data[index].occupied)
            if (strcmp(key, dict->data[index].key))
                index = (index + 1) % dict->size;
            else
                goto end;
        else
            return NULL;
        printf("%d\n", index);
    }

    if (index == init_index)
        return NULL;

end:
    return &dict->data[index];
}

int unset(Dictionary *dict, char *key)
{
    int index = hash(dict, key);
    int init_index = index;

    if (dict->data[index].occupied)
        if (strcmp(key, dict->data[index].key))
            index = (index + 1) % dict->size;
        else
            goto end;
    else
        return -1;

    while (index != init_index) {
        if (dict->data[index].occupied)
            if (strcmp(key, dict->data[index].key))
                index = (index + 1) % dict->size;
            else
                goto end;
        else
            return -1;
        printf("%d\n", index);
    }

    if (index == init_index)
        return -1;

end:
    dict->data[index].occupied = 0;
    return 0;
}

void print(Dictionary *dict)
{
    printf("KEY\tVAL\n");
    for (int i = 0; i < dict->size; i++)
        if (dict->data[i].occupied)
            printf("%s\t%d\n", dict->data[i].key, dict->data[i].value);
}


int main()
{
    char ch;
    char key[32];
    int loop = 1, val, index;
    Dictionary dict;
    DictEntry *item;
    dict_init(&dict);
    while (loop) {
        printf("?> ");
        if (scanf("%c", &ch) == EOF)
            break;
        switch (ch) {
        case 'i':
            scanf("%s", key);
            scanf("%d", &val);
            if (set(&dict, key, val) < 0)
                printf("set failed\n");
            break;

        case 'r':
            scanf("%s", key);
            if (unset(&dict, key) < 0)
                printf("unset failed\n");
            break;

        case 'p':
            print(&dict);
            break;

        case 'g':
            scanf("%s", key);
            item = get(&dict, key);
            if (!item)
                printf("%s -> nil\n", key);
            else
                printf("%s -> %d\n", key, item->value);
            break;
            
        case 'e':
            loop = 0;
            break;

        default:
            printf("?\n");
        }
        flush_input();
    }
    dict_close(&dict);
    return 0;
}
