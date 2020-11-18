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

typedef struct DictEntry {
    char key[32];
    char occupied;
    int value;
} DictEntry;

typedef struct Dictionary {
    DictEntry *data;
    int size;
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
    dict->data = calloc(29, sizeof(*dict->data));
    dict->size = 29;
}

void dict_close(Dictionary *dict)
{
    free(dict->data);
    dict->data = NULL;
    dict->size = 0;
}

int set(Dictionary *dict, char *key, int value)
{
    int index = hash(dict, key);
    int init_index = index;
    // printf(".%d\n", index);
    if (strcmp(key, dict->data[index].key))
        index = (index + 1) % dict->size;
    // The above condition prevents us from entering the loop in case of a hit
    while (index != init_index &&
           dict->data[index].occupied &&
           strcmp(key, dict->data[index].key)) {
        index = (index + 1) % dict->size;
        // printf("%d\n", index);
    }
    if (index == init_index)
        return -1;

    dict->data[index].occupied = 1;
    dict->data[index].value = value;
    strncpy(dict->data[index].key, key, 31);

    return 0;
}

DictEntry *get(Dictionary *dict, char *key)
{
    int index = hash(dict, key);
    int init_index = index;
    while (index != init_index &&
           dict->data[index].occupied &&
           strcmp(key, dict->data[index].key)) {
        index = (index + 1) % dict->size;
        // printf("%d\n", index);
    }
    if (index == init_index)
        return NULL;
    return &dict->data[index];
}

int unset(Dictionary *dict, char *key)
{
    int index = hash(dict, key);
    int init_index = index;
    while (index != init_index &&
           dict->data[index].occupied &&
           strcmp(key, dict->data[index].key)) {
        index = (index + 1) % dict->size;
        // printf("%d\n", index);
    }
    if (index == init_index)
        return -1;

    dict->data[index].occupied = 0;
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
            unset(&dict, key);
            break;

        case 'p':
            print(&dict);
            break;

        case 'g':
            scanf("%s", key);
            item = get(&dict, key);
            if (!item)
                printf("nil\n");
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
