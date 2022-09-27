#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#ifdef CANARY_PROT
#undef CANARY_PROT
#endif
#ifdef   HASH_PROT
#undef   HASH_PROT
#endif 

#ifdef CAN
    #define CANARY_PROT 1
#else
    #define CANARY_PROT 0
#endif

#ifdef HASH
    #define   HASH_PROT 2
#else
    #define   HASH_PROT 0
#endif


#define StackCtor(stk, capacity) StackConstructor (stk, capacity, #stk, __PRETTY_FUNCTION__, __FILE__, __LINE__);

#define AssertOK(stk) if (StackError (stk)) {Dump(stk); return stk -> error;}

#define Dump(stk) StackDump (stk, __PRETTY_FUNCTION__, __FILE__, __LINE__);


//typedef int Elem_t;

typedef unsigned long long Canary_t;

const char *const LOG_FILE_NAME = "stacklog.txt";

const Canary_t CANARY = 0xEEE228ABCDEF1234;

const Elem_t       POISON_ELEM = (Elem_t) 7 - 1000;
const size_t       POISON_SIZE = -73;
const void *const  POISON_PTR  = (void *) 3;


struct StackInfo_t
{
    const char*      name;
    const char* func_name;
    const char* file_name;
    int              line;
};

struct Stack_t
{
    Canary_t leftcan;

    int struct_hash;
    int   data_hash;

    int status;

    struct StackInfo_t info;

    Elem_t *data;
    size_t  size;
    size_t capacity;
    
    int error;

    Canary_t rightcan;
};

int StackConstructor (struct Stack_t *stk, size_t capacity, const char *name, const char *func_name, const char *file_name, int line);

int StackDtor (struct Stack_t *stk);

int StackPush (struct Stack_t *stk, Elem_t elem);

int StackPop (struct Stack_t *stk, Elem_t *value);

int StackResize (struct Stack_t *stk, size_t capacity, int param);

int StackError (struct Stack_t *stk);

void StackDump (struct Stack_t *stk, const char *func_name, const char *file_name, int line);

void* Recalloc(void *memptr, size_t num, size_t size, size_t old_num);

int GetHash (char *ptr, size_t len);

void SetHash (struct Stack_t *stk);

int CorrectStructHash (struct Stack_t *stk);

int CorrectDataHash (struct Stack_t *stk);

enum STACKERRORS
{
    ACCESS_ERROR =  1,
      SIZE_ERROR =  2,
      INFO_ERROR =  4,
      DATA_ERROR =  8,
    STRUCT_ERROR = 16,
    STATUS_ERROR = 32,
};

enum STACKSTATUS
{
    NEW            = 0, 
    CONSTRUCTED    = 1, 
    DECONSTRUCTED  = 2,
};

enum RESIZE_PARAMS
{
    NOT_SET_HASH = 0,
        SET_HASH = 1,
};

#endif