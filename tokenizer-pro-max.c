/**
 * tokenizer-pro-max.c - Tokenizer functions for simple shell
 */
#include "shell.h"

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
