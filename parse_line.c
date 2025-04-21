#include "shell.h"

/**
 * parse_line - splits a line into arguments
 * @line: the input line
 *
 * Return: an array of strings (arguments)
 */
char **parse_line(char *line)
{
    char **tokens = NULL;
    char *token;
    int i = 0;
    int bufsize = 64;

    tokens = malloc(sizeof(char *) * bufsize);
    if (!tokens)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n");
    while (token != NULL)
    {
        tokens[i++] = token;

        if (i >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, sizeof(char *) * bufsize);
            if (!tokens)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n");
    }

    tokens[i] = NULL;
    return tokens;
}
