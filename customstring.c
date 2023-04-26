#include "shell.h"

/**
 * str_length - returns the length of a string.
 * @string: pointer to string.
 * Return: length of string.
 */
int str_length(const char *string)
{
	int length = 0;

	if (string == NULL)
		return (0);

	while (string[length] != '\0')
	{
		length++;
	}
	return (length);
}

/**
 * _strcmp - performs  comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2,
 * zero if str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
	int i;

	for (i = 0; str1[i] && str2[i]; i++)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	}
	if (str1[str_length(str1) - 1] == str2[str_length(str2) - 1])
		return (0);
	else
		return (str1[str_length(str1) - 1] < str2[str_length(str2) - 1] ? -1 : 1);
}
/**
 * starts_with - checks if str2 starts with str1
 * @str2: string to search
 * @str1: the substring to find
 *
 * Return: address of next char of str1 or NULL
 */
char *starts_with(const char *str1, const char *str2)
{
	while (*str2)
		if (*str2++ != *str1++)
			return (NULL);
	return ((char *)str1);
}

/**
 * str_concat - concatenates two strings.
 * @dest: String to be concatenated
 * @src: String to be concatenated
 *
 * Return: pointer to the array
 */
char *str_concat(char *dest, char *src)
{
	char *ret = dest;
	int i, dest_len = str_length(dest);

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[dest_len + i] = src[i];
	}
	dest[dest_len + str_length(src)] = '\0';
	return (ret);
}
