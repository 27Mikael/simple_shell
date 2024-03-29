# Simple Shell

Simple Shell is a basic Unix shell implementation written in C language. It supports basic shell functionalities, such as executing commands, handling built-in commands, and managing processes.

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
```

To run the shell, execute the compiled binary:

bash

./shell

Once the shell is running, you can enter commands just like you would in a standard shell.
Examples

bash

$ ls
file1.txt  file2.txt  directory1  directory2

$ pwd
/home/user/Documents

$ cd directory1

$ ./executable_file
Output from executable_file

$ exit

# Contributing
Mikael Kanku

# License

This project is licensed under the MIT License.



This combined `README.md` provides a concise overview of the Simple Shell project, including its features, usage instructions, examples, contribution guidelines, and license information.

