/*
 * Copyright (c) 2020 Anamitra Ghorui
 * This file is part of Calcium. See Calcium's licensing information for
 * details.
 */

/*
 * Dictionary implementation
 *
 */

typedef struct DictEntry {
    char key[32];
    char occupied;
    int value;
} DictEntry;

typedef struct Dictionary {
    DictEntry *data;
    int size;
} Dictionary;


int hash(Dictionary *dict, char *key)
{
    ret = 0;
    for (*key != '\0'; key++)
        ret = (ret * 25 + (*key) + 1);
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
    dict->data = NULL:
    dict->size = 0;
}

int insert(Dictionary *dict, char *key, int value)
{
    int index = hash(key);
    while (dict->data[index].occupied &&
           strcmp(key, dict->data[index].key) &&
           index < dict->size)
        index++;
    if (index >= dict->size)
        return -1;

    dict->data[index].occupied = 1;
    dict->data[index].value = value;
    strncpy(dict->data[index].key, key, 31);

    return 0;
}

int remove(Dictionary *dict, char *key)
{
    int index = hash(key);
    while (dict->data[index].occupied &&
           strcmp(key, dict->data[index].key) &&
           index < dict->size)
        index++;
    if (index >= dict->size)
        return -1;

    dict->data[index].occupied = 0;
}


int main()
{
    return 0;
}
