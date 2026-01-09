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
			write(STDOUT_FILENO, ":) ", 3);

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
 * tokenize - split a string into tokens
 * @line: the input line to tokenize
 *
 * Return: array of tokens, or NULL on failure
 */
char **tokenize(char *line)
{
	char **tokens;
	char *token;
	char *line_copy;
	int count = 0;
	int i = 0;

	line_copy = malloc(strlen(line) + 1);
	if (line_copy == NULL)
		return (NULL);
	strcpy(line_copy, line);

	token = strtok(line_copy, " ");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " ");
	}

	free(line_copy);

	tokens = malloc((count + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);

	line_copy = malloc(strlen(line) + 1);
	if (line_copy == NULL)
	{
		free(tokens);
		return (NULL);
	}
	strcpy(line_copy, line);

	token = strtok(line_copy, " ");
	while (token != NULL)
	{
		tokens[i] = malloc(strlen(token) + 1);
		if (tokens[i] == NULL)
		{
			free(line_copy);
			free_tokens(tokens);
			return (NULL);
		}
		strcpy(tokens[i], token);
		i++;
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;

	free(line_copy);
	return (tokens);
}

/**
 * free_tokens - free an array of tokens
 * @tokens: the token array to free
 */
void free_tokens(char **tokens)
{
	int i = 0;

	if (tokens == NULL)
		return;

	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

/**
 * find_command - search for command in PATH
 * @command: the command to find
 *
 * Return: full path to command, or NULL if not found
 */
char *find_command(char *command)
{
	char *path_env;
	char *path_copy;
	char *dir;
	char full_path[1024];
	char *result;
	struct stat st;

	if (command == NULL)
		return (NULL);

	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}

	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);

	path_copy = malloc(strlen(path_env) + 1);
	if (path_copy == NULL)
		return (NULL);
	strcpy(path_copy, path_env);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (stat(full_path, &st) == 0)
		{
			result = malloc(strlen(full_path) + 1);
			if (result != NULL)
				strcpy(result, full_path);
			free(path_copy);
			return (result);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * malloc_and_copy - allocate memory and copy a string
 * @str: the string to copy
 *
 * Return: pointer to new string
 */
char *malloc_and_copy(char *str)
{
	char *copy;

	copy = malloc(strlen(str) + 1);
	if (copy == NULL)
		return (NULL);
	strcpy(copy, str);
	return (copy);
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
	char **args;
	char *cmd_path;
	int is_allocated;

	args = tokenize(command);
	if (args == NULL)
	{
		perror("tokenize");
		return;
	}

	if (strcmp(args[0], "exit") == 0)
	{
		free_tokens(args);
		exit(0);
	}

	cmd_path = find_command(args[0]);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			argv[0], line_count, args[0]);
		free_tokens(args);
		return;
	}

	is_allocated = (cmd_path != args[0]);

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free_tokens(args);
		if (is_allocated)
			free(cmd_path);
		return;
	}

	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				argv[0], line_count, args[0]);
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}

	free_tokens(args);
	if (is_allocated)
		free(cmd_path);
}
