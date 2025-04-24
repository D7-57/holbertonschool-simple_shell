# simple_shell

A custom implementation of a simple UNIX command line interpreter.  
This project is part of the Holberton School curriculum and focuses on understanding the core concepts behind shell development, process management, and system calls in C.

---

## 📜 Description

`simple_shell` is a basic UNIX shell that mimics the behavior of `/bin/sh`. It reads user input, parses it, and executes commands using system calls such as `fork`, `execve`, and `wait`. It also supports handling built-in commands such as `exit` and `env`.

This shell operates in both **interactive** and **non-interactive** modes, making it flexible for terminal usage and script execution.

---

## 🧠 Learning Objectives

By completing this project, we learned to:

- Create, manage, and execute child processes with `fork` and `execve`

- Work with environment variables and the `PATH`

- Parse and tokenize input from standard input using `getline` and `strtok`

- Handle command errors, status codes, and memory management

- Implement basic shell built-ins

---

## ✅ Features
-Custom shell prompt: #cisfun$

-Execution of commands with or without absolute/relative paths

-Search and execution using the PATH environment variable

-Proper error handling and exit status codes

-Built-in support for:

   exit: exits the shell

   env: prints the current environment

-Interactive and non-interactive mode support

-Betty-compliant and Valgrind-clean

---

## 💡 Built-in Commands

-Built-in	Description

-exit	      Exits the shell

-env	  Prints the current environment

---

## 🧪 Usage Examples


Interactive mode:

$ ./hsh

#cisfun$ ls -l

#cisfun$ /bin/echo Hello

#cisfun$ env

#cisfun$ exit



Non-interactive mode:

$ echo "ls -l" | ./hsh

$ cat script.sh | ./hsh

---

## 🗂️ Project Structure
.
├── hsh                   # compiled output
├── main.c                # main loop and shell logic
├── parse_line.c          # tokenizes input into arguments
├── path.c                # handles PATH resolution
├── shell.h               # header file with all prototypes
├── utils.c               # helper functions (e.g. _strlen)
├── AUTHORS               # project contributors
├── README.md             # project documentation
├── man_1_simple_shell    # shell manual (man page)

---

## ⚙️ Allowed Functions & System Calls
access, chdir, close, closedir, execve, exit, _exit,
fflush, fork, free, getcwd, getline, getpid, isatty,
kill, malloc, open, opendir, perror, printf, read,
readdir, signal, stat, strtok, wait, waitpid, write

---

## 👨‍💻 Authors
- Abdulrahman Alfawzan , Meshari Alabdullah

