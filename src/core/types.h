/* types.h
 *
 * Type system for LizScript
 */

#ifndef TYPES_H
#define TYPES_H

typedef enum
{
    LS_INVALID_T = 0,
    LS_INT_T = 1,
    LS_FLOAT_T = 2,
    LS_BOOL_T = 4,
    LS_CHAR_T = 8,
    LS_FUNC_T = 16,
    LS_UFUNC_T = 32,
} LSType;

#ifndef __bool_true_false_are_defined
typedef enum {false, true} bool;
#endif

typedef struct LSData LSData;

typedef struct LSFunc
{
    LSType input;
    LSType output;
    LSData (*body)(LSData, LSData*);
    LSData *ctx;
} LSFunc;

struct LSData
{
    LSType type;
    union
    {
        int ival;
        float fval;
        bool bval;
        char cval;
        char* ufunc;
        LSFunc func;
    };
};

#define LS_NUMERIC_T LS_INT_T | LS_FLOAT_T
#define LS_ANY_T LS_INT_T | LS_FLOAT_T | LS_BOOL_T | LS_CHAR_T | LS_FUNC_T | LS_UFUNC_T

#endif
