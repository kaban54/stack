typedef int Elem_t;
#include "stack.h"



int StackConstructor (struct Stack_t *stk, size_t capacity, const char *name, const char *func_name, const char *file_name, int line)
{
    //assert 

    stk -> info.     name =      name;
    stk -> info.func_name = func_name;
    stk -> info.file_name = file_name;
    stk -> info.     line =      line;

    stk -> capacity = capacity;
    stk -> size = 0;

    stk -> data = (Elem_t*) calloc (capacity, sizeof (Elem_t));
    
    for (size_t index = 0; index < capacity; index++)
        stk -> data[index] = POISON_ELEM;

    AssertOK(stk);

    return 0;
}

int StackDtor (struct Stack_t *stk)
{
    AssertOK(stk);
    free (stk -> data);

    /* ???
    stk -> info ->      name = NULL;
    stk -> info -> func_name = NULL;
    stk -> info -> file_name = NULL;
    stk -> info ->      line =    0;
    */
 
    stk -> capacity = POISON_SIZE;
    stk -> size     = POISON_SIZE;

    stk -> data = (Elem_t*) POISON_PTR;    
    
    return 0;
}

int StackPush (struct Stack_t *stk, Elem_t value)
{
    AssertOK(stk);

    int err = 0;

    if (stk -> size >= stk -> capacity) err = StackResize (stk, stk -> capacity * 2);
    
    if (!err) (stk -> data)[(stk -> size)++] = value;

    AssertOK(stk);

    return 0;
}


int StackPop (struct Stack_t *stk, Elem_t *value)
{
    AssertOK(stk);

    if (stk -> size <= 0) return SIZE_ERROR;

    stk -> size--;
    *value = (stk -> data) [stk -> size];
    stk -> data [stk -> size] = POISON_ELEM;

    if (stk -> size * 4 <= (stk -> capacity) && stk -> size > 0) StackResize (stk, stk -> size * 2);

    AssertOK(stk);

    return 0;
}

int StackResize (struct Stack_t *stk, size_t capacity)
{
    AssertOK(stk);

    stk -> data = (Elem_t *) Recalloc ((void *) (stk -> data), capacity, sizeof (stk -> data [0]), stk -> capacity);

    if (capacity > stk -> capacity)
    {
        for (size_t index = stk -> capacity; index < capacity; index ++)
            stk -> data[index] = POISON_ELEM;
    }

    stk -> capacity = capacity; 

    AssertOK(stk);

    return 0;
}

int StackError (struct Stack_t *stk)
{
    if (stk == NULL) return ACCESS_ERROR;

    if (stk -> data == NULL || stk -> data == POISON_PTR)
        stk -> error |= ACCESS_ERROR;

    if (stk -> size > stk -> capacity || stk -> size == POISON_SIZE || stk -> capacity == POISON_SIZE)
        stk -> error |=   SIZE_ERROR;

    if (stk -> info.     name == NULL || stk -> info.     name == POISON_PTR ||
        stk -> info.func_name == NULL || stk -> info.func_name == POISON_PTR ||
        stk -> info.file_name == NULL || stk -> info.file_name == POISON_PTR ||
        stk -> info.     line <= 0)
        stk -> error |=   INFO_ERROR;

    return stk -> error;
}

void StackDump (struct Stack_t *stk, const char *func_name, const char *file_name, int line)
{
    FILE *log = fopen (LOG_FILE_NAME, "a");
    if (log == NULL) return;

    if (func_name == NULL) func_name = "NULL";
    if (file_name == NULL) file_name = "NULL";

    fprintf (log, "%s at %s(%d):\n", func_name, file_name, line);
    
    if (stk == NULL)
    {
        fprintf (log, "stack [NULL] <-- ACCESS ERROR\n");
        return;
    }
    
    if (stk -> error & INFO_ERROR)
    {
        fprintf (log, "unknown stack [%p] <-- INFO_ERROR:", stk);
        return;
    }

    fprintf (log, "stack [%p] \"%s\" at %s at %s(%d)\n{\n", stk,
                                                            stk -> info.     name,
                                                            stk -> info.func_name,
                                                            stk -> info.file_name,
                                                            stk -> info.     line);


    if (stk -> size == POISON_SIZE)             fprintf (log, "\tsize     = POISON"               );
    else                                        fprintf (log, "\tsize     = %d", stk -> size      );

    if (stk -> error & SIZE_ERROR)              fprintf (log, " <-- SIZE ERROR");
    fprintf (log, "\n");

    if (stk -> size == POISON_SIZE)             fprintf (log, "\tcapacity = POISON\n"             );
    else                                        fprintf (log, "\tcapacity = %d\n", stk -> capacity);

    if (stk -> error & ACCESS_ERROR)
    {
        if (stk -> data == POISON_PTR)          fprintf (log, "\tdata [POISON] <-- ACCESS ERROR\n");
        else                                    fprintf (log, "\tdata [%p] <-- ACCESS ERROR\n", stk -> data);
        fprintf (log, "}\n\n");
        return;
    }
    else                                        fprintf (log, "\tdata [%p]\n\t{\n", stk -> data);

    for (size_t index = 0; index < stk -> capacity; index++)
    {
        fprintf (log, index < stk -> size ? "\t\t*" : "\t\t ");
        if (stk -> data [index] == POISON_ELEM) fprintf (log, "[%d] = POISON\n", index);
        else                                    fprintf (log, "[%d] = %d\n", index, stk -> data [index]); // ??        
    }

    fprintf (log, "\t}\n}\n\n");
    fclose (log);
}

void *Recalloc (void *memptr, size_t num, size_t size, size_t old_num) //?
{
    memptr = realloc (memptr, num * size);
    if (memptr == NULL) return NULL;

    if (num > old_num) memset ((void *) ((char *) memptr + old_num * size), 0, (num - old_num) * size);

    return memptr;
}