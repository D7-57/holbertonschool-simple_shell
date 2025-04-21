#include "shell.h"

/**
 * main - Entry point for the shell
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Exit status of the last command
 */
int main(int argc, char **argv)
{
	char *line = NULL, *full_cmd = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;
	int status = 0;

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

		if (strcmp(args[0], "exit") == 0)
		{
			free_tokens(args);
			free(line);
			exit(status); /* ✅ Handle the built-in exit command */
		}

		full_cmd = find_path(args[0]);
		if (full_cmd == NULL)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", argv[0], args[0]);
			free_tokens(args);
			status = 127;
			continue;
		}

		if (fork() == 0)
		{
			if (execve(full_cmd, args, environ) == -1)
			{
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}

		free(full_cmd);
		free_tokens(args);
	}

	free(line);
	return (status);
}

