#include "shell.h"

int main() {
	char input[256];
	char *args[MAX_ARGS + 1];
	pid_t pid;
	int numTokens;
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *path_token = strtok(path_copy, ":");
	int command_found = 0;

	while (1) {
		printf("$ ");
		fflush(stdout);

		if (fgets(input, sizeof(input), stdin) == NULL) {
			if (feof(stdin)) {
				/* Output newline for Ctrl+D */
				printf("\n");
				/* End of file (Ctrl+D) encountered */
				return 1;
			} else {
				perror("fgets() error");
				return -1;
			}
		}

		input[strcspn(input, "\n")] = '\0'; /* Remove trailing newline */

		if (strcmp(input, EXIT_COMMAND) == 0)
			return 1; /* Exit command received */

		numTokens = parser(args, input, " ");
		if (numTokens == 0)
			continue;

		/* Check if the command exists in the PATH */
		while (path_token != NULL) {
			char command_path[MAX_PATH_LENGTH];
			snprintf(command_path, sizeof(command_path), "%s/%s", path_token, args[0]);
			if (access(command_path, X_OK) == 0) {
				command_found = 1;
				break;
			}
			path_token = strtok(NULL, ":");
		}
		free(path_copy);

		if (!command_found) {
			printf("Command not found: %s\n", args[0]);
			continue;
		}

		pid = fork();
		if (pid == -1) {
			perror("fork() error");
			return 1;
		} else if (pid == 0) {
			/* Child process */
			execvp(args[0], args);
			/* execvp() returns only if an error occurs */
			perror("execvp() error");
			exit(EXIT_FAILURE);
		} else {
			/* Parent process */
			int status;
			waitpid(pid, &status, 0);
		}
	}

	return 0;
}
