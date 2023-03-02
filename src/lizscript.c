/*
 * lizscript.c
 */

#include "lizscript.h"
#include "namemap.h"

int lizscript_int(char* input)
{
    LSParseResult res = eval_lizscript(input);
    if (res.result.type & (LS_INT_T | LS_CHAR_T | LS_BOOL_T))
    {
        return res.result.ival;
    }
    else if (res.result.type == LS_FLOAT_T)
    {
        return (int)res.result.fval;
    }
    return 0;
}   

float lizscript_float(char* input)
{
    LSParseResult res = eval_lizscript(input);
    if (res.result.type & (LS_INT_T | LS_CHAR_T | LS_BOOL_T))
    {
        return (float)res.result.ival;
    }
    else if (res.result.type == LS_FLOAT_T)
    {
        return res.result.fval;
    }
    return 0.0;
}   

/*
 * Adds a global value to the name mapper. This can be used to
 * set enviornment variables, as well as to define custom functions.
 */
void lizscript_global(const char* name, LSData value)
{
    map_lizscript_obj((char *)name, value);
}
