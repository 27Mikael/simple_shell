#include "shell.h"

/**
 * parser - parses user input
 * @token: user input
 * @delimeter: 
 * @buffer: 
 * 
 * Return: 1 on success
*/
#define MAX_ARGS 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10
#define MAX_PATH_LENGTH 256

int parser(char** tokens, char *buffer, char *delimiter) {
	int counter = 0;
	char* token;

	token = strtok(buffer, delimiter);
	while (token != NULL && counter < MAX_ARGS)
	{
		tokens[counter] = strdup(token);
		token = strtok(NULL, delimiter);
		counter++;
	}
	tokens[counter] = NULL;
	return counter;
}

int main() {
	char input[256];
	char* args[MAX_ARGS + 1];

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = '\0';

		int numTokens = parser(args, input, " ");

		if (numTokens == 0)
			continue;

		/*Check if the command exists in the PATH*/
		char* path = getenv("PATH");
		char* path_copy = strdup(path);
		char* path_token = strtok(path_copy, ":");
		int command_found = 0;

		while (path_token != NULL)
		{
			char command_path[MAX_PATH_LENGTH];
			snprintf(command_path, sizeof(command_path), "%s/%s", path_token, args[0]);
			if (access(command_path, X_OK) == 0)
			{
				command_found = 1;
				break;
			}
			path_token = strtok(NULL, ":");
		}
		free(path_copy);

		if (!command_found)
		{
			printf("Command not found: %s\n", args[0]);
			continue;
		}

		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork() error");
			return 1;
		}
		
		else if (pid == 0)
		{
			// Execute command
			/*Execute command*/
			execvp(args[0], args);
			perror("execvp() error"); // execvp() returns only if an error occurs
			exit(EXIT_FAILURE);
		}
		
		else
		{
			/*Parent process*/
			int status;
			waitpid(pid, &status, 0);
		}
	}

	return 0;
}
