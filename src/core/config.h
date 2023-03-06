/*
 * config.h
 *
 * Defines preprocessor directives that control how the LizScript
 * engine is built.
 */

/*
 * Maximum recursion level allowed before error is thrown.
 * Make sure this number is small enough that reaching it
 * won't cause a stack overflow on your platform.
 */
#ifndef LS_MAX_RECURSION_DEPTH
    #define LS_MAX_RECURSION_DEPTH 128
#endif

/*
 * Define the size of the context stack.
 */
#ifndef LS_CTX_STACK_SIZE
    #define LS_CTX_STACK_SIZE 128
#endif

/*
 * Define the maximum number of characters for a symbol.
 */
#ifndef LS_MAX_SYM_LEN
    #define LS_MAX_SYM_LEN 15
#endif

/*
 * Define the maximum number of mapped names.
 * This also affects how many functions can be defined,
 * as functions map two names.
 */
#ifndef LS_MAX_NAMES
    #define LS_MAX_NAMES 64
#endif

/*
 * These two directives define what characters are allowable
 * as whitespace and in symbols.
 */
#ifndef LS_ALLOWED_WHITESPACE_CHARS
    #define LS_ALLOWED_WHITESPACE_CHARS " \t\n\r"
#endif

#ifndef LS_ALLOWED_SYMBOL_CHARS
    #define LS_ALLOWED_SYMBOL_CHARS "!#$%&*+,-./:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_abcdefghijklmnopqrstuvwxyz{|}~"
#endif
