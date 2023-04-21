#include "shell.h"

/**
 * **strtow2 - splits a string
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i = 0, j = 0, k = 0, l = 0, words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != d && str[i + 1] == d) ||
				(str[i] != d && !str[i + 1]) || str[i + 1] == d)
		{
			words++;
		}
	}
	if (words == 0)
		return (NULL);
	s = malloc((1 + words) * sizeof(char *));
	if (!s)
		return (NULL);
	while (j < words)
	{
		while (str[i] == d && str[i] != d)
			i++;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (l = 0; l < k; l++)
			s[j][l] = str[i++];
		s[j][l] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: input string
 * @d: delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i, j, k, l, words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	i = 0;
	while (str[i] != '\0')
	{
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			words++;
		i++;
	}
	if (words == 0)
		return (NULL);
	s = malloc((1 + words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < words; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (l = 0; l < k; l++)
			s[j][l] = str[i++];
		s[j][l] = 0;
	}
	s[j] = NULL;
	return (s);
}
