/*
 * lizscript.h
 *
 * Provides an interface to lizscript interpreter
 */

#ifndef LIZSCRIPT_H
#define LIZSCRIPT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "core/eval.h"
#include "core/types.h"
#include "core/errors.h"

/*
 * Parses lizscript and returns an integer value.
 * This function will attempt to convert other types,
 * such as 'char' and 'bool' to an integer. If unable to
 * convert the underlying type, the function returns 0.
 */
int lizscript_int(const char* input);

/*
 * Parses lizscript and returns a floating point value.
 * This function will attempt to convert other types,
 * such as 'int' and 'char' to a floating point. If unable
 * to convert the underlying type, the function returns 0.0.
 */
float lizscript_float(const char* input);

/*
 * Parses lizscript and returns a LSParseResult.
 */
LSParseResult lizscript_eval(const char* input);

/*
 * Adds a global value to the name mapper. This can be used to
 * set enviornment variables, as well as to define custom functions.
 */
void lizscript_global(const char* name, LSData value);

#ifdef __cplusplus
}
#endif

#endif
