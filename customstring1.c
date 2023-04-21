#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination string
 * @src: the source string
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest,  char *src)
{
	int i;

	if (dest == src || src == 0)
		return (dest);

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[str_length(src)] = '\0';
	return (dest);
}

/**
 * str_duplicate - duplicates an string
 * @string: String to be copied
 * Return: pointer to the array
 */
char *str_duplicate(const char *string)
{
	char *result;
	int length, i;

	if (string == NULL)
		return (NULL);

	length = str_length(string) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
		return (NULL);
	for (i = 0; i < length ; i++)
	{
		result[i] = string[i];
	}

	return (result);
}
/**
 * _putchar - prints the character to stdout
 * @c: The character to be printed
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int i;

	if (!str)
		return;

	for (i = 0; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
}
