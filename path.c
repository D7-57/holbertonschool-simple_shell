#include "shell.h"
#include <sys/stat.h>

/**
 * find_path - Finds the full path of a command using PATH
 * @command: The command to search for
 *
 * Return: Full path string (malloc'd), or NULL if not found
 */
char *find_path(char *command)
{
	char *path_env, *path_copy, *dir, *full_path;
	int len;
	struct stat st;

	if (command == NULL)
		return (NULL);

	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0)
			return (strdup(command));
		else
			return (NULL);
	}

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		len = strlen(dir) + strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
