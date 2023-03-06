/*
 * lizscript.c
 */

#include "lizscript.h"
#include "core/namemap.h"

int lizscript_int(const char* input)
{
    LSParseResult res = parse_lizscript((char*)input);
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

float lizscript_float(const char* input)
{
    LSParseResult res = parse_lizscript((char*)input);
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

LSParseResult lizscript_eval(const char* input)
{
    return parse_lizscript((char*) input);
}

void lizscript_global(const char* name, LSData value)
{
    map_lizscript_obj((char *)name, value);
}
