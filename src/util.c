/*
 * util.c
 * Utility functions for LizScript core
 */

#include "util.h"
#include "namemap.h"
#include "lizscript.h"

char* sym_copy(char* sym, char* buffer)
{
    int i, j;
    for(i = 0; i < LS_MAX_SYM_LEN; i++)
    {
        for(j = 0; ALLOWED_SYMBOL_CHARS[j] != '\0'; j++)
        {
            if (sym[0] == ALLOWED_SYMBOL_CHARS[j])
            {
                buffer[i] = sym[0];
                sym++;
                break;
            }
            else
            {
                buffer[i] = '\0';
            }
        }
    }
    buffer[i] = '\0';
    return sym;
}
