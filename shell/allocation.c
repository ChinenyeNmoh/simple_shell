#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: memory area pointer
 *@b: the byte to fill memory area with
 *@n: the amount of bytes
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}
	return (s);
}
/**
 * ffree - frees a string
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **s = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(s);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous memory allocated
 * @old_size: size of previous memory
 * @new_size: size of new memory
 *
 * Return: pointer to old block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *rep;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	rep = malloc(new_size);
	if (!rep)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		rep[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (rep);
}

