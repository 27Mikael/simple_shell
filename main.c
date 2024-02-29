#include "shell.h"

/**
 * handle_user_input - handles input from user
 * Return: exits once ctrl + d is input
*/
void handle_user_input(void)
{
	char input[256];

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			if (feof(stdin))
			{
				printf("\n"); /*Output newline for Ctrl+D*/
				return; /*End of file (Ctrl+D) encountered*/
			}
			else
			{
				perror("fgets() error");
				exit(EXIT_FAILURE);
			}
		}

		input[strcspn(input, "\n")] = '\0'; /*Remove trailing newline*/

		if (strcmp(input, EXIT_COMMAND) == 0)
			exit(EXIT_SUCCESS); /*Exit command received*/

		/*Parse and execute the command*/
		execute_command(input);
	}
}

/**
 * parse_and_validate_command - takes user commands and validates it
 * @input: user input
 * @args: arguments in input
 * Return: successful comman validation
*/
int parse_and_validate_command(char *input, char *args[])
{
	int numTokens = parser(args, input, " ");

	if (numTokens == 0)
		return (0); /*No tokens found*/

	/*Validate the command format or perform additional validation if needed*/

	return (1); /*Command validated successfully*/
}

/**
 * execute_command - executes user commands
 * @input: user input
*/
void execute_command(char *input)
{
	char *args[MAX_ARGS + 1];
	pid_t pid;

	if (!parse_and_validate_command(input, args))
	{
		printf("Invalid command format\n");
		return;
	}

	/*Execute the command*/
	pid = fork();
	if (pid == -1)
	{
		perror("fork() error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/*Child process*/
		execvp(args[0], args);
		/*execvp() returns only if an error occurs*/
		perror("execvp() error");
		exit(EXIT_FAILURE);
	}
	else
	{
		/*Parent process*/
		int status;

		waitpid(pid, &status, 0);
	}
}

/**
 * main - entrance point of code
 * Return: 0 on success
*/
int main(void)
{
	handle_user_input();
	return (0);
}
