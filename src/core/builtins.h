#ifndef BUILTINS_H
#define BUILTINS_H

#include "types.h"

/*
 * Calls a builtin function by looking up it's name.
 */
LSData call_builtin(const char* name, LSData inp);

#endif
