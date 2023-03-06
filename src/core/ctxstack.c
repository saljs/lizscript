#include "ctxstack.h"
#include "config.h"
#include "errors.h"
#include <stddef.h>

LSData ctx_stack[LS_CTX_STACK_SIZE];
unsigned int ctx_stack_ptr = 0;

/*
 * Pushes an item to the stack, and returns it's location.
 */
LSData* push_ctx(LSData ctx)
{
    if (ctx_stack_ptr >= LS_CTX_STACK_SIZE - 1)
    {
        LSERR = ESTACKOVERFLOW;
        return NULL;
    }

    ctx_stack[ctx_stack_ptr] = ctx;
    return &(ctx_stack[ctx_stack_ptr++]);
}

/*
 * Removes the top item from the.
 */
void pop_ctx()
{
    if (ctx_stack_ptr > 0)
    {
        ctx_stack_ptr--;
    }
}
