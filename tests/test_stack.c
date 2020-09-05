#include "../calcium.h"
#include <stdio.h>
#include <sys/time.h>
#include <assert.h>
#define TESTSIZE 100

int main()
{
    ca_stack *a = Ca_StackInit(TESTSIZE);
    CA_REAL dummy;
    
    for(size_t i = 0; i < 100; ++i)
        Ca_StackPush(a, i);

    assert(Ca_StackPush(a, 1) == CA_ERROR_STACK_FULL);

    for(size_t i = 0; i < 100; ++i)
        Ca_StackPop(a, &dummy);
    
    assert(Ca_StackPop(a, &dummy) == CA_ERROR_STACK_EMPTY);

    Ca_StackFree(a);
    printf("Test Passed.\n");

    return 0;
}
