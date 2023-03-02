/* builtins.c
 *
 * A set of functions that comprise LizScript core.
 */

#include "builtins.h"
#include "errors.h"
#include "ctxstack.h"

/*
 * '+'
 */
LSData add_inner_func (LSData inp, LSData* ctx)
{
    LSData ret;
    if (inp.type == LS_INT_T && ctx->type == LS_INT_T)
    {
        ret.type = LS_INT_T;
        ret.ival = inp.ival + ctx->ival;
    }
    else if (inp.type == LS_FLOAT_T && ctx->type == LS_INT_T)
    {
        ret.type = LS_FLOAT_T;
        ret.fval = inp.fval + ctx->ival;
    }
    else if (inp.type == LS_INT_T && ctx->type == LS_FLOAT_T)
    {
        ret.type = LS_FLOAT_T;
        ret.fval = inp.ival + ctx->fval;
    }
    else
    {
        ret.type = LS_FLOAT_T;
        ret.fval = inp.fval + ctx->fval;
    }
    return ret;
}

LSData add_func (LSData inp)
{
    LSData ret;
    ret.type = LS_FUNC_T;
    ret.func.input = LS_NUMERIC_T;
    ret.func.output = LS_NUMERIC_T;
    ret.func.body = add_inner_func;
    ret.func.ctx = push_ctx(inp);
    if (LSERR)
    {
        return LS_DATA_ERROR;
    }
    return ret;
}

/*
 * '-'
 */
LSData sub_inner_func (LSData inp, LSData* ctx)
{
    LSData ret;
    if (inp.type == LS_INT_T && ctx->type == LS_INT_T)
    {
        ret.type = LS_INT_T;
        ret.ival = inp.ival - ctx->ival;
    }
    else if (inp.type == LS_FLOAT_T && ctx->type == LS_INT_T)
    {
        ret.type = LS_FLOAT_T;
        ret.fval = inp.fval - ctx->ival;
    }
    else if (inp.type == LS_INT_T && ctx->type == LS_FLOAT_T)
    {
        ret.type = LS_FLOAT_T;
        ret.fval = inp.ival - ctx->fval;
    }
    else
    {
        ret.type = LS_FLOAT_T;
        ret.fval = inp.fval - ctx->fval;
    }
    return ret;
}

LSData sub_func (LSData inp)
{
    LSData ret;
    ret.type = LS_FUNC_T;
    ret.func.input = LS_NUMERIC_T;
    ret.func.output = LS_NUMERIC_T;
    ret.func.body = sub_inner_func;
    ret.func.ctx = push_ctx(inp);
    if (LSERR)
    {
        return LS_DATA_ERROR;
    }
    return ret;
}

/*
 * '*'
 */
LSData mul_inner_func (LSData inp, LSData* ctx)
{
    LSData ret;
    if (inp.type == LS_INT_T && ctx->type == LS_INT_T)
    {
        ret.type = LS_INT_T;
        ret.ival = inp.ival * ctx->ival;
    }
    else if (inp.type == LS_FLOAT_T && ctx->type == LS_INT_T)
    {
        ret.type = LS_FLOAT_T;
        ret.fval = inp.fval * ctx->ival;
    }
    else if (inp.type == LS_INT_T && ctx->type == LS_FLOAT_T)
    {
        ret.type = LS_FLOAT_T;
        ret.fval = inp.ival * ctx->fval;
    }
    else
    {
        ret.type = LS_FLOAT_T;
        ret.fval = inp.fval * ctx->fval;
    }
    return ret;
}

LSData mul_func (LSData inp)
{
    LSData ret;
    ret.type = LS_FUNC_T;
    ret.func.input = LS_NUMERIC_T;
    ret.func.output = LS_NUMERIC_T;
    ret.func.body = mul_inner_func;
    ret.func.ctx = push_ctx(inp);
    if (LSERR)
    {
        return LS_DATA_ERROR;
    }
    return ret;
}

/*
 * '/'
 */
LSData div_inner_func (LSData inp, LSData* ctx)
{
    LSData ret;
    if (ctx->ival == 0)
    {
        LSERR = EDIVZERO;
        return LS_DATA_ERROR;
    }
    
    if (inp.type == LS_INT_T && ctx->type == LS_INT_T)
    {
        ret.type = LS_INT_T;
        ret.ival = inp.ival / ctx->ival;
    }
    else if (inp.type == LS_FLOAT_T && ctx->type == LS_INT_T)
    {
        ret.type = LS_FLOAT_T;
        ret.fval = inp.fval / ctx->ival;
    }
    else if (inp.type == LS_INT_T && ctx->type == LS_FLOAT_T)
    {
        ret.type = LS_FLOAT_T;
        ret.fval = inp.ival / ctx->fval;
    }
    else
    {
        ret.type = LS_FLOAT_T;
        ret.fval = inp.fval / ctx->fval;
    }
    return ret;
}

LSData div_func (LSData inp)
{
    LSData ret;
    ret.type = LS_FUNC_T;
    ret.func.input = LS_NUMERIC_T;
    ret.func.output = LS_NUMERIC_T;
    ret.func.body = div_inner_func;
    ret.func.ctx = push_ctx(inp);
    if (LSERR)
    {
        return LS_DATA_ERROR;
    }
    return ret;
}

/*
 * '%'
 */
LSData mod_inner_func (LSData inp, LSData* ctx)
{
    LSData ret;
    if (ctx->ival == 0)
    {
        LSERR = EDIVZERO;
        return LS_DATA_ERROR;
    }
    ret.type = LS_INT_T;
    ret.ival = inp.ival % ctx->ival;
    return ret;
}

LSData mod_func (LSData inp)
{
    LSData ret;
    ret.type = LS_FUNC_T;
    ret.func.input = LS_INT_T;
    ret.func.output = LS_INT_T;
    ret.func.body = mod_inner_func;
    ret.func.ctx = push_ctx(inp);
    if (LSERR)
    {
        return LS_DATA_ERROR;
    }
    return ret;
}

/*
 * 'floor'
 */
LSData floor_func (LSData inp)
{
    LSData ret;
    ret.type = LS_INT_T;
    ret.ival = (int)inp.fval;
    return ret;
}

/*
 * 'ceil'
 */
LSData ceil_func (LSData inp)
{
    LSData ret;
    int x = (int)inp.fval;
    ret.type = LS_INT_T;
    ret.ival = inp.fval == x ? x : x + 1;
    return ret;
}

/*
 * '='
 */
LSData eq_inner_func (LSData inp, LSData* ctx)
{
    LSData ret;
    ret.type = LS_BOOL_T;
    ret.bval = false;
    if(inp.type == ctx->type)
    {
        switch(inp.type)
        {
            case LS_INT_T:
                ret.bval = inp.ival == ctx->ival;
                break;
            case LS_FLOAT_T:
                ret.bval = inp.fval == ctx->fval;
                break;
            case LS_BOOL_T:
                ret.bval = inp.bval == ctx->bval;
                break;
            case LS_CHAR_T:
                ret.bval = inp.cval == ctx->cval;
                break;
        }
    }
    // numeric comparisions
    else if (inp.type == LS_FLOAT_T && ctx->type == LS_INT_T)
    {
        ret.bval = inp.fval == ctx->ival;
    }
    else if (inp.type == LS_INT_T && ctx->type == LS_FLOAT_T)
    {
        ret.bval = inp.ival == ctx->fval;
    }
    return ret;
}

LSData eq_func (LSData inp)
{
    LSData ret;
    ret.type = LS_FUNC_T;
    ret.func.input = LS_INT_T | LS_FLOAT_T | LS_BOOL_T | LS_CHAR_T;
    ret.func.output = LS_BOOL_T;
    ret.func.body = eq_inner_func;
    ret.func.ctx = push_ctx(inp);
    if (LSERR)
    {
        return LS_DATA_ERROR;
    }
    return ret;
}

/*
 * '<'
 */
LSData lt_inner_func (LSData inp, LSData* ctx)
{
    LSData ret;
    ret.type = LS_BOOL_T;
    if(inp.type == LS_INT_T && ctx->type == LS_INT_T)
    {
        ret.bval = inp.ival < ctx->ival;
    }
    else if (inp.type == LS_FLOAT_T && ctx->type == LS_INT_T)
    {
        ret.bval = inp.fval < ctx->ival;
    }
    else if (inp.type == LS_INT_T && ctx->type == LS_FLOAT_T)
    {
        ret.bval = inp.ival < ctx->fval;
    }
    else
    {
        ret.bval = inp.fval < ctx->fval;
    }
    return ret;
}

LSData lt_func (LSData inp)
{
    LSData ret;
    ret.type = LS_FUNC_T;
    ret.func.input = LS_NUMERIC_T;
    ret.func.output = LS_BOOL_T;
    ret.func.body = lt_inner_func;
    ret.func.ctx = push_ctx(inp);
    if (LSERR)
    {
        return LS_DATA_ERROR;
    }
    return ret;
}

/*
 * '>'
 */
LSData gt_inner_func (LSData inp, LSData* ctx)
{
    LSData ret;
    ret.type = LS_BOOL_T;
    if(inp.type == LS_INT_T && ctx->type == LS_INT_T)
    {
        ret.bval = inp.ival > ctx->ival;
    }
    else if (inp.type == LS_FLOAT_T && ctx->type == LS_INT_T)
    {
        ret.bval = inp.fval > ctx->ival;
    }
    else if (inp.type == LS_INT_T && ctx->type == LS_FLOAT_T)
    {
        ret.bval = inp.ival > ctx->fval;
    }
    else
    {
        ret.bval = inp.fval > ctx->fval;
    }
    return ret;
}

LSData gt_func (LSData inp)
{
    LSData ret;
    ret.type = LS_FUNC_T;
    ret.func.input = LS_NUMERIC_T;
    ret.func.output = LS_BOOL_T;
    ret.func.body = gt_inner_func;
    ret.func.ctx = push_ctx(inp);
    if (LSERR)
    {
        return LS_DATA_ERROR;
    }
    return ret;
}

/*
 * 'and'
 */
LSData and_inner_func (LSData inp, LSData* ctx)
{
    LSData ret;
    ret.type = LS_BOOL_T;
    ret.bval = inp.bval && ctx->bval;
    return ret;
}

LSData and_func (LSData inp)
{
    LSData ret;
    ret.type = LS_FUNC_T;
    ret.func.input = LS_BOOL_T;
    ret.func.output = LS_BOOL_T;
    ret.func.body = and_inner_func;
    ret.func.ctx = push_ctx(inp);
    if (LSERR)
    {
        return LS_DATA_ERROR;
    }
    return ret;
}

/*
 * 'or'
 */
LSData or_inner_func (LSData inp, LSData* ctx)
{
    LSData ret;
    ret.type = LS_BOOL_T;
    ret.bval = inp.bval || ctx->bval;
    return ret;
}

LSData or_func (LSData inp)
{
    LSData ret;
    ret.type = LS_FUNC_T;
    ret.func.input = LS_BOOL_T;
    ret.func.output = LS_BOOL_T;
    ret.func.body = or_inner_func;
    ret.func.ctx = push_ctx(inp);
    if (LSERR)
    {
        return LS_DATA_ERROR;
    }
    return ret;
}

/*
 * 'not'
 */
LSData not_func (LSData inp)
{
    LSData ret;
    ret.type = LS_BOOL_T;
    ret.bval = !inp.bval;
    return ret;
}


/*******************************************************************************
 * LSData definitions
 ******************************************************************************/

static LSData (*builtin_table[])(LSData) = {
    add_func,
    sub_func,
    mul_func,
    div_func,
    mod_func,
    floor_func,
    ceil_func,
    eq_func,
    lt_func,
    gt_func,
    and_func,
    or_func,
    not_func,
};

static LSType builtin_input_types[] = {
    LS_NUMERIC_T,                    // '+'
    LS_NUMERIC_T,                    // '-'
    LS_NUMERIC_T,                    // '*'
    LS_NUMERIC_T,                    // '/'
    LS_INT_T,                        // '%'
    LS_FLOAT_T,                      // 'floor'
    LS_FLOAT_T,                      // 'ceil'
    LS_INT_T | LS_FLOAT_T | LS_BOOL_T | LS_CHAR_T,  // '='
    LS_NUMERIC_T,                    // '<'
    LS_NUMERIC_T,                    // '>'
    LS_BOOL_T,                       // 'and'
    LS_BOOL_T,                       // 'or'
    LS_BOOL_T,                       // 'not'
};

static char* builtin_names[] = {
    "+",
    "-",
    "*",
    "/",
    "%",
    "floor",
    "ceil",
    "=",
    "<",
    ">",
    "and",
    "or",
    "not",
};


/*******************************************************************************
 * Public functions
 ******************************************************************************/

LSData call_builtin(const char* name, LSData inp)
{
    int i, j;
    for (i = 0; i < sizeof(builtin_names) / sizeof(char*); i++)
    {
        for (j = 0; name[j] != '\0'; j++)
        {
            if (builtin_names[i][j] == '\0' || builtin_names[i][j] != name[j])
            {
                break;
            }
        }
        if (name[j] == '\0' && builtin_names[i][j] == '\0')
        {
            if (inp.type & builtin_input_types[i])
            {
                return (*builtin_table[i])(inp);
            }
            
            LSERR = EWRONGTYPE;
            return LS_DATA_ERROR;
        }
    }

    LSERR = ENOTFOUND;
    return LS_DATA_ERROR;
}
