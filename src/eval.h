/*
 * eval.h
 * LizScript parser/interpreter
 */

#ifndef EVAL_H
#define EVAL_H

#include "types.h"
#include "errors.h"

#define MAX_RECURSION_DEPTH 512
#define ALLOWED_WHITESPACE_CHARS " \t\n\r"
#define ALLOWED_SYMBOL_CHARS "!#$%&*+,-./:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_abcdefghijklmnopqrstuvwxyz{|}~"

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
LSParseResult eval_lizscript(char* input);

#define LS_PARSE_ERROR(STREAM)\
    (LSParseResult) { .result = LS_DATA_ERROR, .stream = STREAM }

#endif
