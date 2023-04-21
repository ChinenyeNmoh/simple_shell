#include "shell.h"

/**
 * set_alias - sets alias
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * unset_alias - sets alias
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *ptr, s;
	int r;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	s = *ptr;
	*ptr = 0;
	r = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*ptr = s;
	return (r);
}

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *ptr = NULL, *al = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		al = node->str;
		while (al <= ptr)
		{
			_putchar(*al);
			al++;
		}
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - customized alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *ptr = NULL;
	list_t *tmp = NULL;

	if (info->argc == 1)
	{
		tmp = info->alias;
		while (tmp)
		{
			print_alias(tmp);
			tmp = tmp->next;
		}
		return (0);
	}
	i = 1;
	while (info->argv[i])
	{
		ptr = _strchr(info->argv[i], '=');
		if (ptr)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
		i++;
	}
	return (0);
}
