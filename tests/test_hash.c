#include "../calcium.h"
#include "../debug.h"

#include <stdio.h>
#include <assert.h>

int main()
{
    int g = 3;
    ca_hash k = ca_hash_init();
    ca_hash_node *p;
    assert(k);
    assert(ca_hash_set(k, "aaa", 3, CA_TYPE_INT, &g) == CA_ERROR_HASH_NEW);
    assert(ca_hash_get(k, "aaa", 3, &p) == CA_ERROR_OK);
    assert((*((int *) p->data)) == 3);
    assert(ca_hash_get(k, "bbb", 3, &p) == CA_ERROR_HASH_NOTFOUND);
    ca_hash_print(k);
    ca_hash_free(k);
    printf("Test Passed.\n");

    return 0;
}
