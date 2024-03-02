#include "shell.h"

/**
 * print_prompt - prints the username, hostname, cwd
 * Return: exits once ctrl + d is input
*/
void print_prompt(void)
{
    write(STDOUT_FILENO, "($)", 3);
    fflush(stdout);
}


/**
 * execute_command - parses non_interactive mode commands
 * @command: command to be parsed
 * Return: EXIT_SUCCESS upon success
*/
int execute_command(const char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execlp(command, command, NULL) == -1)
		{
			perror("execlp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * non_interactive - the main loop for non interactive mode
 * @input_file_path: path to the file
 * Return: EXIT_SUCCESS upon success
*/
int non_interactive(const char *input_file_path)
{
	FILE *input_file = fopen(input_file_path, "r");
	char line[MAX_LINE_LENGTH];

	if (!input_file)
	{
		perror("fopen");
		return (EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), input_file))
	{
		line[strcspn(line, "\n")] = '\0';

		if (execute_command(line) == EXIT_FAILURE)
		{
			fclose(input_file);
			return (EXIT_FAILURE);
		}
	}
	fclose(input_file);

	return (EXIT_SUCCESS);
}

/**
 * main - entrance point of code
 * @argc: number of commands passed
 * @argv: list of commands passed
 * Return: 0 on success
*/
int main(int argc, char *argv[])
{
	if (argc == 2)
		non_interactive(argv[1]);
	else
		handle_user_input();

	return (0);
}
