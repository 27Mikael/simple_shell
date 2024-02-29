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
