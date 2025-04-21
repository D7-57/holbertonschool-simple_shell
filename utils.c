#include "shell.h"

/**
 * _strlen - Returns the length of a string
 * @s: The string
 *
 * Return: Length
 */
int _strlen(const char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

