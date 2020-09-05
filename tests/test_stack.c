#include "../calcium.h"
#include <stdio.h>
#include <sys/time.h>
#include <assert.h>
#define TESTSIZE 100

int main()
{
    CaStack *a = Ca_StackInit(TESTSIZE);
    CaReal dummy;
    
    for(size_t i = 0; i < 100; ++i)
        ca_stack_push(a, i);

    assert(ca_stack_push(a, 1) == CA_ERROR_STACK_FULL);

    for(size_t i = 0; i < 100; ++i)
        ca_stack_pop(a, &dummy);
    
    assert(ca_stack_pop(a, &dummy) == CA_ERROR_STACK_EMPTY);

    ca_stack_free(a);
    printf("Test Passed.\n");

    return 0;
}
