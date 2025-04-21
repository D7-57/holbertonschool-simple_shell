#include "shell.h"

/**
 * main - Entry point for the shell
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL, *full_cmd = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;
	int status;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		args = parse_line(line);
		if (args == NULL || args[0] == NULL)
		{
			free_tokens(args);
			continue;
		}

		full_cmd = find_path(args[0]);
		if (full_cmd == NULL)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", argv[0], args[0]);
			free_tokens(args);
			continue;
		}

		free(args[0]);
		args[0] = full_cmd;

		if (fork() == 0)
		{
			if (execve(args[0], args, environ) == -1)
			{
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}

		free_tokens(args);
	}

	free(line);
	return (0);
}
