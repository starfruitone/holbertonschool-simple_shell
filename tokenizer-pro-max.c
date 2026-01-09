/**
 * tokenizer-pro-max.c - Tokenizer functions for simple shell
 */
#include "shell.h"

/**
 * count_tokens - count number of tokens in a string
 * @line: the input line
 *
 * Return: number of tokens
 */
int count_tokens(char *line)
{
	char *line_copy;
	char *token;
	int count = 0;

	line_copy = malloc(strlen(line) + 1);
	if (line_copy == NULL)
		return (-1);
	strcpy(line_copy, line);
	token = strtok(line_copy, " ");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " ");
	}
	free(line_copy);
	return (count);
}

/**
 * fill_tokens - fill token array with tokens
 * @tokens: array to fill
 * @line: the input line
 *
 * Return: 0 on success, -1 on failure
 */
int fill_tokens(char **tokens, char *line)
{
	char *line_copy;
	char *token;
	int i = 0;

	line_copy = malloc(strlen(line) + 1);
	if (line_copy == NULL)
		return (-1);
	strcpy(line_copy, line);
	token = strtok(line_copy, " ");
	while (token != NULL)
	{
		tokens[i] = malloc(strlen(token) + 1);
		if (tokens[i] == NULL)
		{
			free(line_copy);
			return (-1);
		}
		strcpy(tokens[i], token);
		i++;
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	free(line_copy);
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
	int count;

	count = count_tokens(line);
	if (count == -1)
		return (NULL);
	tokens = malloc((count + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	if (fill_tokens(tokens, line) == -1)
	{
		free_tokens(tokens);
		return (NULL);
	}
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
