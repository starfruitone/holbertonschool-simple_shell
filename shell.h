#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void print_prompt(void);
char *read_input(void);
void execute_command(char *command, char *argv[]);
void print_error(char *prog_name, int line_num, char *command);

#endif
