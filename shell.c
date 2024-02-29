#include "shell.h"

/**
 *shell - runs shell in interactive or non-interactive mode
 * 
 *  
*/
int shell()
{
	if (isatty(STDIN_FILENO))
	{
	/*shell runs in interactive mode*/
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	char *username = getlogin();
	char hostname[1024];
	gethostname(hostname, sizeof(hostname));
	printf("%s@%s:%s", username, hostname, cwd);
	}

	else
	{
	/*shell runs in non-interactive mode*/
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcdw() error");
		return -1;
	}
	char username[LOGIN_NAME_MAX];
	if (getlogin_r(username, sizeof(username)) != 0)
	{
		perror("getlogin_r() error");
		return -1;
	}
	char hostname[HOST_NAME_MAX];
	if (gethostname(hostname, sizeof(hostname)) != 0)
	{
		perror ("gethostname() error");
		return -1;
	}
	printf("%s@%s:%s$ ", username, hostname, cwd);
	return 0;
	}

}

int main()
{
	char input[256];
	if (fgets(input, sizeof(input), stdin) == NULL)
	{
		if (feof(stdin))
		{
			printf("\n"); // Output newline for Ctrl+D
			return 1; // End of file (Ctrl+D) encountered
		}
		else
		{
			perror("fgets() error");
			return -1;
		}
	}
	
	input[strcspn(input, "\n")] = '\0'; /*Remove trailing newline*/
	
	if (strcmp(input, EXIT_COMMAND) == 0)
		return 1; /*Exit command received*/
	
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork() error");
		return -1;
	}

	else if (pid == 0)
	{
		/* Child process */
		if (execlp(input, input, NULL) == -1)
		{
			perror("execlp() error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/*Parent process*/
		int status;
		waitpid(pid, &status, 0);
	}
	
	return 0;
}
