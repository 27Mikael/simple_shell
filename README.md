# Simple Shell

Simple Shell is a basic Unix shell implementation written in C language.

## Description

This shell supports basic shell functionalities, such as executing commands, handling built-in commands, and managing processes.

## Features

- Executes external commands
- Supports built-in commands (e.g., `cd`, `exit`)
- Handles process management (fork, exec, waitpid)
- Supports PATH resolution for external commands
- Basic error handling

## Usage

To compile the shell, run:

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o shell

