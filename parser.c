#include "shell.h"

/**
 * parser - parses user input
 * @token: user input
 * @delimeter: 
 * @buffer: 
 * 
 * Return: 1 on success
*/
int parser(char** tokens, char *buffer, char *delimiter)
{
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
	return (counter);
}
