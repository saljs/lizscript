/*
 * eval.c
 */

#include "eval.h"
#include "config.h"
#include "namemap.h"
#include "ctxstack.h"
#include "builtins.h"
#include "util.h"

#define CHECK_DEPTH(DEPTH) if(DEPTH > LS_MAX_RECURSION_DEPTH)\
    { LSERR = EMAXRECURSION; return LS_PARSE_ERROR(input); }

#define CHECK_RESULT(RES) if(!RES.result.type) { return RES; }

char* skip_whitespace(char* input)
{
    int i;
    bool is_whitespace;
    do
    {
        is_whitespace = false;
        for (i = 0; LS_ALLOWED_WHITESPACE_CHARS[i] != '\0'; i++)
        {
            if (input[0] == LS_ALLOWED_WHITESPACE_CHARS[i])
            {
                input++;
                is_whitespace = true;
                break;
            }
        }
    } while(is_whitespace);

    return input;
}

char* up_level(char* input)
{
    int p_depth = 0;
    while (input[0] != '\0' && (p_depth > 0 || input[0] != ')'))
    {
        if (input[0] == '(')
        {
            p_depth++;
        }
        else if (input[0] == ')')
        {
            p_depth--;
        }
        input++;
    }
    return input;
}

LSParseResult parse(char* input, int depth);

LSParseResult parse_let(char* input, int depth)
{
    LSParseResult arg, apply;
    char sym[LS_MAX_SYM_LEN + 1];
    
    input = skip_whitespace(input);

    // copy symbol
    input = sym_copy(input, sym);
    input = skip_whitespace(input);

    // parse the argument
    arg = parse(input, depth + 1);
    CHECK_RESULT(arg);
    input = arg.stream;

    // add mapping to symbol mapper
    map_lizscript_obj(sym, arg.result);

    // parse the function to apply
    apply = parse(input, depth + 1);

    // pop mapping from the stack
    pop_lizscript_obj();

    if (arg.result.type == LS_FUNC_T)
    {
        pop_ctx();
    }

    return apply;    
}

LSParseResult parse_func(char* input, int depth)
{
    LSParseResult apply;
    LSData func;
    char sym[LS_MAX_SYM_LEN + 1];
    
    input = skip_whitespace(input);
    
    // copy symbol
    input = sym_copy(input, sym);
    input = skip_whitespace(input);
    
    // add func to symbol mapper
    func.type = LS_UFUNC_T;
    func.ufunc = input;
    map_lizscript_obj(sym, func);
            
    // skip over function body
    if (input[0] != '(')
    {
        LSERR = EUNEXPECTEDTOKEN;
        return LS_PARSE_ERROR(input);
    }
    input = up_level(input + 1);
    if (input[0] != ')')
    {
        LSERR = EUNEXPECTEDTOKEN;
        return LS_PARSE_ERROR(input);
    }

    // parse the function to apply
    apply = parse(input + 1, depth + 1);

    // pop mapping from the stack
    pop_lizscript_obj();

    return apply;    
}

LSParseResult parse_switch(char* input, int depth)
{
    LSParseResult cond, expr, def;

    // parse the default value
    def = parse(input, depth + 1);
    CHECK_RESULT(def);
    
    input = skip_whitespace(def.stream);

    // parse case tuples
    while (input[0] == '(')
    {
        input = skip_whitespace(input + 1);

        // parse the conditional
        cond = parse(input, depth + 1);
        CHECK_RESULT(cond);
        if (cond.result.type != LS_BOOL_T)
        {
            LSERR = EWRONGTYPE;
            return LS_PARSE_ERROR(input);
        }
        input = cond.stream;

        // if the condition is true, parse expression
        if (cond.result.bval)
        {
            expr = parse(input, depth + 1);
            CHECK_RESULT(expr);

            // skip to the end of the top level function and return
            input = up_level(expr.stream + 1);
            if (input[0] != ')')
            {
                LSERR = EUNEXPECTEDTOKEN;
                return LS_PARSE_ERROR(input);
            }
            expr.stream = input + 1;
            return expr;
        }
        else
        {
            // skip to end of the tuple
            input = up_level(input);
            if (input[0] != ')')
            {
                LSERR = EUNEXPECTEDTOKEN;
                return LS_PARSE_ERROR(input);
            }
            input = skip_whitespace(input + 1);
        }
    }
    
    // return the default value
    if (input[0] != ')')
    {
        LSERR = EUNEXPECTEDTOKEN;
        return LS_PARSE_ERROR(input);
    }

    def.stream = input + 1;
    return def;
}

LSParseResult parse_expr(char* input, int depth)
{
    LSParseResult func, arg, res;
    char sym[LS_MAX_SYM_LEN + 1];
    bool needs_pop = false;
    CHECK_DEPTH(depth);
    
    // the function can either be a symbol or an expression
    if (input[0] == '(')
    {
        func = parse_expr(input + 1, depth + 1);
        CHECK_RESULT(func);
        input = func.stream;
        needs_pop = true;
    }
    else
    {
        // read in symbol
        input = sym_copy(input, sym);

        //check for special cases
        if (sym[0] == 'l' && sym[1] == 'e' && sym[2] == 't' && sym[3] == '\0')
        {
            return parse_let(input, depth);
        }
        else if (sym[0] == 's' && sym[1] == 'w' && sym[2] == 'i' 
                 && sym[3] == 't' && sym[4] == 'c' && sym[5] == 'h'
                 && sym[6] == '\0')
        {
            return parse_switch(input, depth);
        }
        else if (sym[0] == 'f' && sym[1] == 'u' && sym[2] == 'n'
                 && sym[3] == 'c' && sym[4] == '\0')
        {
            return parse_func(input, depth);
        }
        
        // look up symbol
        func.result = get_lizscript_obj(sym);
        // clear any error set by get_lizscript_obj
        LSERR = NOERR;
    }

    arg = parse(input, depth + 1);
    CHECK_RESULT(arg);
    input = arg.stream;

    if (func.result.type == LS_FUNC_T)
    {
        // check types
        if (!(func.result.func.input & arg.result.type))
        {
            LSERR = EWRONGTYPE;
            return LS_PARSE_ERROR(input);
        }
        res.result = func.result.func.body(arg.result, func.result.func.ctx);
    }
    else if (func.result.type == LS_UFUNC_T)
    {
        map_lizscript_obj("#x", arg.result);
        res = parse(func.result.ufunc, depth + 1);
        pop_lizscript_obj();
    }
    else if (!func.result.type)
    {
        res.result = call_builtin(sym, arg.result);
    }
    res.stream = input; 
    CHECK_RESULT(res);

    input = skip_whitespace(input);
    if (input[0] != ')')
    {
        LSERR = EUNEXPECTEDTOKEN;
        return LS_PARSE_ERROR(input);
    }

    if (needs_pop)
    {
        pop_ctx();
    }
    
    res.stream = input + 1;    
    return res;
}

LSParseResult parse_char(char* input, int depth)
{
    LSParseResult res;
    CHECK_DEPTH(depth);
    
    res.result.type = LS_CHAR_T;
    res.result.cval = input[0];
    
    if(input[1] != '\'')
    {
        LSERR = EUNEXPECTEDTOKEN;
        return LS_PARSE_ERROR(input + 1);
    }

    res.stream = input + 2;
    return res;
}

LSParseResult parse_bool(char* input, int depth)
{
    LSParseResult res;
    CHECK_DEPTH(depth);
    
    res.result.type = LS_BOOL_T;
    res.result.bval = input[0] == 't';
    res.stream = input + 1;
    return res;
}

LSParseResult parse_number(char* input, int depth)
{
    LSParseResult res;
    int place = 10, sign = 1;
    CHECK_DEPTH(depth);

    res.result.type = LS_INT_T;
    res.result.ival = 0;
    if (input[0] == '-')
    {
        sign = -1;
        input++;
    }
    else if (input[0] == '+')
    {
        input++;
    }

    while (input[0] >= '0' && input[0] <= '9')
    {
        res.result.ival *= 10;
        res.result.ival += (input[0] - '0');
        input++;
    }
    if (input[0] == '.')
    {
        res.result.type = LS_FLOAT_T;
        res.result.fval = (float)res.result.ival;
        input++;
        while (input[0] >= '0' && input[0] <= '9')
        {
            res.result.fval += (input[0] - '0') / (float)place;
            place *= 10;
            input++;
        }
        res.result.fval *= sign;
    }
    else
    {
        res.result.ival *= sign;
    }
    
    res.stream = input;
    return res;
}

LSParseResult parse_symbol(char* input, int depth)
{
    LSParseResult res;
    char sym[LS_MAX_SYM_LEN + 1];
    CHECK_DEPTH(depth);
    
    // read in symbol
    input = sym_copy(input, sym);
    
    res.result = get_lizscript_obj(sym);
    res.stream = input;

    return res;
}

LSParseResult parse(char* input, int depth)
{
    CHECK_DEPTH(depth);
    
    input = skip_whitespace(input);
    if (input[0] == '\0')
    {
        LSERR = EUNEXPECTEDEOF;
        return LS_PARSE_ERROR(input);
    }
    else if (input[0] == '(')
    {
        return parse_expr(input + 1, depth + 1);
    }
    else if (input[0] == '\'')
    {
        return parse_char(input + 1, depth + 1);
    }
    else if (input[0] == '#' && (input[1] == 't' || input[1] == 'f'))
    {
        return parse_bool(input + 1, depth + 1);
    }
    else if ((input[0] >= '0' && input[0] <= '9')
        || ((input[0] == '-' || input[0] == '+' || input[0] == '.')
            && (input[1] >= '0' && input[1] <= '9'))
        || ((input[0] == '-' || input[0] == '+') && input[1] == '.'
            && (input[2] >= '0' && input[2] <= '9')))
    {
        //INTs match this regex:    [-+]?[0-9]+
        //FLOATS match this regex:  [-+]?[0-9]*\.[0-9]+
        return parse_number(input, depth + 1);
    }
    else
    {
        int i;
        for (i = 0; LS_ALLOWED_SYMBOL_CHARS[i] != '\0'; i++)
        {
            if (input[0] == LS_ALLOWED_SYMBOL_CHARS[i])
            {
                return parse_symbol(input, depth + 1);
            }
        }
    }

    LSERR = EUNEXPECTEDTOKEN;
    return LS_PARSE_ERROR(input);
}
 
LSParseResult parse_lizscript(char* input)
{
    LSParseResult res = parse(input, 0);
    if (res.result.type == LS_FUNC_T && res.result.func.ctx)
    {
        pop_ctx();
    }
    return res;
}
