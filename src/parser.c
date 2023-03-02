/*
 * parser.c
 *
 * Implements a simple LizScript parser
 */

#include "lizscript.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <readline/readline.h>

int eval_file(const char* path);
void handle_result(LSData result);
void print_error(LSParseResult error, char* stream);
char* get_cmd();

void show_version()
{
    printf("LizScript version 1.01\n"
           "Copyright 2023 Salvatore Skare.\n"
           "Press Ctrl-D to exit.\n");
}

int main(int argc, char** argv)
{
    char* cmd = NULL;
    LSParseResult parsed;

    if (argc == 2)
    {
        // Read input from file
        if (0 != eval_file(argv[1]))
        {
            fprintf(stderr, "Error: cannot read from %s.\n", argv[1]);
            return 1;
        }
    }
    else if (argc == 1)
    {
        // REPL
        show_version();
        cmd = get_cmd();
        while (cmd)
        {
            if (*cmd)
            {
                parsed = eval_lizscript(cmd);
                if (!parsed.result.type)
                {
                    print_error(parsed, cmd);
                }
                else
                {
                    handle_result(parsed.result);
                }
            }
            free(cmd);
            cmd = get_cmd();
        }
    }
    else
    {
        fprintf(stderr, "Error: incorrect number of arguments.\n"
                "Usage: %s [file]\n", argv[0]);
        return -1;
    }
    return 0;
}

int eval_file(const char* path)
{
    char* file;
    struct stat file_info;
    LSParseResult parsed;
    int fd = open(path, O_RDONLY);
    
    if (!fd)
    {
        return fd;
    }
    if (0 != fstat(fd, &file_info))
    {
        return -1;
    }

    file = mmap(NULL, file_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    parsed = eval_lizscript(file);
    if (!parsed.result.type)
    {
        print_error(parsed, file);
    }
    else
    {
        handle_result(parsed.result);
    }

    munmap(file, file_info.st_size);
    close(fd);
    return 0;
}

void handle_result(LSData result)
{
    switch (result.type)
    {
        case LS_INT_T:
            printf("%d\n", result.ival);
            break;
        case LS_FLOAT_T:
            printf("%f\n", result.fval);
            break;
        case LS_CHAR_T:
            printf("%c\n", result.cval);
            break;
        case LS_BOOL_T:
            printf("%s\n", result.bval ? "#t" : "#f");
            break;
        case LS_FUNC_T:
            printf("<Func>\n");
            break;
        case LS_UFUNC_T:
            printf("<Func>\n");
            break;
    }
}

void print_error(LSParseResult error, char* stream)
{
    int i, line_num = 1;
    char* line_start = stream;
    char* stream_ptr = stream;
    while (stream_ptr < error.stream)
    {
        if (*stream_ptr == '\n')
        {
            line_num++;
            line_start = stream_ptr + 1;
        }
        stream_ptr++;
    }

    printf("Error on line %d: %s (%d)\n", line_num, ls_err_desc(), LSERR);
    stream_ptr = line_start;
    while (*stream_ptr != '\n' && *stream_ptr != '\0')
    {
        putchar(*stream_ptr);
        stream_ptr++;
    }
    putchar('\n');
    for (i = 0; i < error.stream - line_start; i++)
    {
        putchar(' ');
    }
    printf("^\n");
}

char* get_cmd()
{
    char *line, *ptr, *cmd = NULL;
    int paren_depth = 0;

    line = readline("ls> ");
    while (line)
    {
        ptr = line;
        while (ptr && *ptr)
        {
            if (*ptr == '(')
            {
                paren_depth++;
            }
            else if (*ptr == ')')
            {
                paren_depth--;
            }
            ptr++;
        }

        if (cmd)
        {
            ssize_t bufflen = strlen(cmd) + strlen(line) + 1;
            cmd = realloc(cmd, bufflen);
            strcat(cmd, "\n");
            strcat(cmd, line);
        }
        else
        {
            cmd = line;
        }

        if (paren_depth == 0)
        {
            break;
        }
        line = readline("... ");
    }

    return cmd;
}
