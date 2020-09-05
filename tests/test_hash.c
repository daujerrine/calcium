#include "../calcium.h"
#include "../debug.h"

#include <stdio.h>
#include <assert.h>

int main()
{
    int g = 3;
    ca_hash k = Ca_HashInit();
    ca_hash_node *p;
    assert(k);
    assert(Ca_HashSet(k, "aaa", 3, CA_TYPE_INT, &g) == CA_ERROR_HASH_NEW);
    assert(Ca_HashGet(k, "aaa", 3, &p) == CA_ERROR_OK);
    assert((*((int *) p->data)) == 3);
    assert(Ca_HashGet(k, "bbb", 3, &p) == CA_ERROR_HASH_NOTFOUND);
    Ca_HashPrint(k);
    Ca_HashFree(k);
    printf("Test Passed.\n");

    return 0;
}
