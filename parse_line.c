#include "shell.h"

/**
 * parse_line - Splits a line into tokens (arguments)
 * @line: Input line to parse
 *
 * Return: Array of strings (tokens), or NULL on failure
 */
char **parse_line(char *line)
{
	char **tokens;
	char *token;
	int i = 0, bufsize = 64;

	tokens = malloc(sizeof(char *) * bufsize);
	if (tokens == NULL)
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
			if (tokens == NULL)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
 * free_tokens - Frees memory allocated for tokens array
 * @tokens: Null-terminated array of strings
 */
void free_tokens(char **tokens)
{
	free(tokens);
}
