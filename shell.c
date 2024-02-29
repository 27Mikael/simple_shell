#include "shell.h"

/**
 *shell - runs shell in interactive or non-interactive mode
 *
 *Return: 0 on success
*/
int shell(void)
{
	char cwd[PATH_MAX];
	char username[LOGIN_NAME_MAX];
	char hostname[HOST_NAME_MAX];

	if (isatty(STDIN_FILENO))
	{
	/*shell runs in interactive mode*/
	getcwd(cwd, sizeof(cwd));
	getlogin_r(username, sizeof(username));
	gethostname(hostname, sizeof(hostname));

	printf("%s@%s:%s", username, hostname, cwd);
	}

	else
	{
	/*shell runs in non-interactive mode*/
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return (-1);
	}

	if (getlogin_r(username, sizeof(username)) != 0)
	{
		perror("getlogin_r() error");
		return (-1);
	}

	if (gethostname(hostname, sizeof(hostname)) != 0)
	{
		perror("gethostname() error");
		return (-1);
	}
	printf("%s@%s:%s$ ", username, hostname, cwd);
	}
	return (0);
}