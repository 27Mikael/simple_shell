#include "shell.h"

/**
 * print_prompt - prints the username, hostname, cwd
 * Return: exits once ctrl + d is input
*/
void print_prompt(void)
{
	char cwd[PATH_MAX], username[LOGIN_NAME_MAX], hostname[HOST_NAME_MAX];

	getcwd(cwd, sizeof(cwd));
	getlogin_r(username, sizeof(username));
	gethostname(hostname, sizeof(hostname));

	write(STDOUT_FILENO, username, strlen(username));
	write(STDOUT_FILENO, "@", 1);
	write(STDOUT_FILENO, hostname, strlen(hostname));
	write(STDOUT_FILENO, ":", 1);
	write(STDOUT_FILENO, cwd, strlen(cwd));
	write(STDOUT_FILENO, "$ ", 2);
	fflush(stdout);
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
