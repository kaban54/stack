#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define StackCtor(stk, capacity) StackConstructor (stk, capacity, #stk, __PRETTY_FUNCTION__, __FILE__, __LINE__);

#define AssertOK(stk) if (StackError (stk)) {StackDump (stk, __PRETTY_FUNCTION__, __FILE__, __LINE__); \
                                             return stk -> error;}


//typedef int Elem_t;

const char *const LOG_FILE_NAME = "stacklog.txt";

const Elem_t POISON_ELEM = (Elem_t) 7 - 1000;
const size_t POISON_SIZE = -73;
void *const  POISON_PTR  = (void *) 3;


struct StackInfo_t
{
    const char*      name;
    const char* func_name;
    const char* file_name;
    int              line;
};

struct Stack_t
{
    struct StackInfo_t info;

    Elem_t *data;
    size_t  size;
    size_t capacity;
    
    int error;
};

int StackConstructor (struct Stack_t *stk, size_t capacity, const char *name, const char *func_name, const char *file_name, int line);

int StackDtor (struct Stack_t *stk);

int StackPush (struct Stack_t *stk, Elem_t elem);

int StackPop (struct Stack_t *stk, Elem_t *value);

int StackResize (struct Stack_t *stk, size_t capacity);

int StackError (struct Stack_t *stk);

void StackDump (struct Stack_t *stk, const char *func_name, const char *file_name, int line);

void* Recalloc(void *memptr, size_t num, size_t size, size_t old_num);

enum STACKERRORS
{
    ACCESS_ERROR = 1,
      SIZE_ERROR = 2,
      INFO_ERROR = 4,
};


#endif