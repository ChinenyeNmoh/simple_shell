#include "shell.h"

/**
 * bfree - frees a pointer
 * @ptr: pointer to be freed
 *
 * Return: returns 1 on success and 0 on failure
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

