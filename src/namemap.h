#ifndef NAMEMAP_H
#define NAMEMAP_H

#include "types.h"

#define LS_MAX_SYM_LEN 15
#define LS_MAX_NAMES 256

/*
 * Definition of a sym -> data mapping.
 */
typedef struct LSName
{
    char sym[LS_MAX_SYM_LEN + 1];
    LSData data;
} LSName;

/*
 * Retrieve a data object by name.
 */
LSData get_lizscript_obj(const char* name);

/*
 * Maps a name to a data element and adds it to the stack.
 */
void map_lizscript_obj(char* name, LSData data);

/*
 * Removes the top element from the stack.
 */
void pop_lizscript_obj();
#endif
