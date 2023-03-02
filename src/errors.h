/*
 * errors.h
 *
 * LizScript error definitions
 */

#ifndef ERRORS_H
#define ERRORS_H

#include "types.h"

/*
 * Definition of differnt errors.
 */
enum LSError
{
    NOERR,              //No error
    ESTACKOVERFLOW,     //Stack overflow
    ESTACKEMPTY,        //Stack empty
    EWRONGTYPE,         //Expected a differnt type
    ENOTFOUND,          //Symbol not found
    EDIVZERO,           //Attempt to divide by zero
    EMAXRECURSION,      //Maximum recursion level reached
    EUNEXPECTEDTOKEN,   //Unexpected token during parse
    EUNEXPECTEDEOF,     //Unecpected end of input during parse
};

/*
 * Global error register.
 */
extern enum LSError LSERR;

/*
 * Returns a string representation of the error code.
 */
const char* ls_err_desc();

/*
 * Macro to return invalid data object.
 */
#define LS_DATA_ERROR (LSData) {.type = LS_INVALID_T }

#endif
