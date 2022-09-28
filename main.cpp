typedef int Elem_t;
#include "stack.h"

int main (void)
{
    struct Stack_t stk = {};

    StackCtor (&stk, 10);
    
    const char *testlog = "testlog.txt";

    
    Dump (&stk, testlog);
    StackPush (&stk, 1);
    Dump (&stk, testlog);
    StackPush (&stk, 2);
    Dump (&stk, testlog);
    StackPush (&stk, 3);
    Dump (&stk, testlog);

    int a = 0, b = 0, c = 0;

    StackPop(&stk, &a);
    Dump (&stk, testlog);
    StackPop(&stk, &b);
    Dump (&stk, testlog);
    StackPop(&stk, &c);
    Dump (&stk, testlog);
    printf ("%d, %d, %d", a, b, c);

    StackDtor (&stk);
    return 0;
}