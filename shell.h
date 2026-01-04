/*
 * File: shell.h
 * Auth: Alexander
 * Desc: Header file for simple UNIX command line interpreter
 */

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void execute_command(char *command, char *argv[], int line_count);

#endif
