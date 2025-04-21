#include "shell.h"

int main(int argc, char **argv)
{
    char *line = NULL;
    char **args = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t pid;
    int status;

    (void)argc;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "#cisfun$ ", 9);

        read = getline(&line, &len, stdin);

        if (read == -1)  /* Ctrl+D (EOF) */
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        if (line[read - 1] == '\n')  /* remove newline */
            line[read - 1] = '\0';

        args = parse_line(line);
        if (args == NULL || args[0] == NULL)
            continue;

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

        free(args);
    }

    free(line);
    return 0;
}
