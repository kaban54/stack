typedef int Elem_t;
#include "stack.h"

int main (void)
{
    struct Stack_t stk = {};

    StackCtor (&stk, 10);

    StackPush (&stk, 1);
    StackPush (&stk, 2);
    StackPush (&stk, 3);

    int a = 0, b = 0, c = 0;

    StackPop(&stk, &a);
    StackPop(&stk, &b);
    StackPop(&stk, &c);
    printf ("%d, %d, %d", a, b, c);

    StackDtor (&stk);

    return 0;
}