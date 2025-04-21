#include "shell.h"

/**
 * display_prompt - Displays shell prompt if interactive
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
 * handle_input - Reads input from stdin
 * @line: Pointer to buffer
 * @len: Pointer to length
 *
 * Return: Read size or -1 on EOF
 */
ssize_t handle_input(char **line, size_t *len)
{
	ssize_t read;

	read = getline(line, len, stdin);
	if (read == -1 && isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	if (read > 0 && (*line)[read - 1] == '\n')
		(*line)[read - 1] = '\0';
	return (read);
}

/**
 * execute_command - Forks and executes a command
 * @args: Tokenized command arguments
 * @argv: Argument vector for error messages
 */
void execute_command(char **args, char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		wait(&status);
	}
	else
	{
		perror("fork");
	}
}

/**
 * main - Entry point for the shell
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;

	(void)argc;

	while (1)
	{
		display_prompt();
		read = handle_input(&line, &len);
		if (read == -1)
			break;

		args = parse_line(line);
		if (args == NULL || args[0] == NULL)
		{
			free_tokens(args);
			continue;
		}

		execute_command(args, argv);
		free_tokens(args);
	}

	free(line);
	return (0);
}
