#ifndef MAIN_H
#define MAIN_H

#define MAX_ARGS 10
#define MAX_PATH_LENGTH 256
#define EXIT_COMMAND "exit"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <bits/local_lim.h>

int parser(char **tokens, char *buffer, char *delimeter);
void execute_command(char *input);
int parse_and_validate_command(char *input, char *args[]);
void handle_user_input(void);
int shell(void);
int main(void);

#endif
