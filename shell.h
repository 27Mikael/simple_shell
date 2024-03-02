#ifndef MAIN_H
#define MAIN_H

#define MAX_ARGS 10
#define MAX_PATH_LENGTH 512
#define MAX_LINE_LENGTH 512
#define EXIT_COMMAND "exit"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <bits/local_lim.h>

int parse_and_validate_command(char *input, char *args[]);
int parser(char **tokens, char *buffer, char *delimeter);
int non_interactive(const char *input_file_path);
int execute_command(char *input);
int main(int argc, char *argv[]);
void handle_user_input(void);
void print_prompt(void);
int shell(void);

#endif
