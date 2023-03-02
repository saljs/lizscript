#ifndef CTXSTACK_H
#define CTXSTACK_H

#include "types.h"

#define LS_CTX_STACK_SIZE 512

/*
 * Pushes an item to the stack, and returns it's location.
 */
LSData* push_ctx(LSData ctx);

/*
 * Pops the top item from the stack.
 */
void pop_ctx();

#endif
