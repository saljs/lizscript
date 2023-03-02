/*
 * namemap.c
 */

#include "namemap.h"
#include "errors.h"
#include "util.h"

LSName namestack[LS_MAX_NAMES];
int namestack_ptr = 0;

/*******************************************************************************
 * Public functions
 ******************************************************************************/
LSData get_lizscript_obj(const char* name)
{
    int i, index = namestack_ptr - 1;
    while (index >= 0)
    {
        for(i = 0; i < LS_MAX_SYM_LEN; i++)
        {
            if (namestack[index].sym[i] == '\0' || name[i] == '\0'
                || namestack[index].sym[i] != name[i])
            {
                break;
            }
        }
        if(namestack[index].sym[i] == '\0' && name[i] == '\0')
        {
            return namestack[index].data;
        }
        index--;
    }
    LSERR = ENOTFOUND;
    return LS_DATA_ERROR;
}

void map_lizscript_obj(char* name, LSData data)
{
    sym_copy(name, namestack[namestack_ptr].sym);
    namestack[namestack_ptr].data = data;
    namestack_ptr++;
}

void pop_lizscript_obj()
{
    namestack_ptr--;
}
