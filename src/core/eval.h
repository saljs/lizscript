/*
 * eval.h
 * LizScript parser/interpreter
 */

#ifndef EVAL_H
#define EVAL_H

#include "types.h"
#include "errors.h"

/*
 * A parse results holds a data object with the result of parsing,
 * as well as a pointer to the current location in the input stream.
 */
typedef struct LSParseResult
{
    LSData result;
    char* stream;
} LSParseResult;

/*
 * Evaluates a stream of LizScript and returns the result.
 */
LSParseResult parse_lizscript(char* input);

#define LS_PARSE_ERROR(STREAM)\
    (LSParseResult) { .result = LS_DATA_ERROR, .stream = STREAM }

#endif
