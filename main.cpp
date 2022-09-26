typedef int Elem_t;
#include "stack.h"

int main (void)
{
    struct Stack_t stk = {};

    StackCtor (&stk, 1);

    StackPush (&stk, 1);
    StackDump (&stk, __PRETTY_FUNCTION__, __FILE__, __LINE__);
    StackPush (&stk, 2);
    StackDump (&stk, __PRETTY_FUNCTION__, __FILE__, __LINE__);
    StackPush (&stk, 3);
    StackDump (&stk, __PRETTY_FUNCTION__, __FILE__, __LINE__);

    int a = 0, b = 0, c = 0;

    StackPop(&stk, &a);
    StackDump (&stk, __PRETTY_FUNCTION__, __FILE__, __LINE__);
    StackPop(&stk, &b);
    StackDump (&stk, __PRETTY_FUNCTION__, __FILE__, __LINE__);
    StackPop(&stk, &c);
    StackDump (&stk, __PRETTY_FUNCTION__, __FILE__, __LINE__);
    printf ("%d, %d, %d", a, b, c);

    StackDtor (&stk);
    return 0;
}