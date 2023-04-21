#include "shell.h"

/**
 * _mygetenv - prints the current environmental variables
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _mygetenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environmental variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *tmp = info->env;
	char *ptr;

	while (tmp)
	{
		ptr = starts_with(tmp->str, name);
		if (ptr && *ptr)
			return (ptr);
		tmp = tmp->next;
	}
	return (NULL);
}
/**
 * _mysetenv - set a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc < 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - deletes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */

int _myunsetenv(info_t *info)
{
	int i = 1;

	if (info->argc < 2)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	while (info->argv[i])
	{
		_unsetenv(info, info->argv[i]);
		i++;
	}
	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *tmp = NULL;
	size_t i = 0;

	while (environ[i] != NULL)
	{
		add_node_end(&tmp, environ[i], 0);
		i++;
	}
	info->env = tmp;
	return (0);
}
