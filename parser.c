#include "shell.h"

/**
 * parser - parses user input
 * @tokens: user input
 * @delimiter: used to seperate tokens
 * @buffer: buffer for input
 * Return: 1 on success
*/
int parser(char **tokens, char *buffer, char *delimiter)
{
	int counter = 0;
	char *token;
	int i;

	token = strtok(buffer, delimiter);
	while (token != NULL && counter < MAX_ARGS)
	{
		tokens[counter] = strdup(token);
		token = strtok(NULL, delimiter);
		counter++;
	}
	tokens[counter] = NULL;

	for (i = 0; i < counter; i++)
	{
	free(tokens[i]);
	}

	return (counter);
}
