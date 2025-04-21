#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

char **parse_line(char *line);
void free_tokens(char **tokens);
char *find_path(char *command);
int _strlen(const char *s);

#endif
