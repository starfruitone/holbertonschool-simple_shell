/**
 * shell.h - Header file for simple shell
 */
#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

void execute_command(char *command, char *argv[], int line_count);
char **tokenize(char *line);
void free_tokens(char **tokens);
char *find_command(char *command);
char *_getenv(char *name);

#endif
