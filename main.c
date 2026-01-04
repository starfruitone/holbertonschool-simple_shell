/*
 * File: main.c
 * Auth: Alexander
 * Desc: Entry point for a simple UNIX command line interpreter
 */

#include "shell.h"

/**
 * main - entry point for simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int line_count = 0;
	int interactive = isatty(STDIN_FILENO);

	(void)argc;

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		line_count++;

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (strlen(line) > 0)
			execute_command(line, argv, line_count);
	}

	free(line);
	return (0);
}

/**
 * execute_command - fork and execute a command
 * @command: the command to execute
 * @argv: program arguments for error messages
 * @line_count: the current line number
 */
void execute_command(char *command, char *argv[], int line_count)
{
	pid_t pid;
	int status;
	char *args[2];

	args[0] = command;
	args[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		if (execve(command, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				argv[0], line_count, command);
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}
}
