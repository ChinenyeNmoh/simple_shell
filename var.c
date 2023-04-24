#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t t = *p;

	if (buf[t] == '|' && buf[t + 1] == '|')
	{
		buf[t] = 0;
		t++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[t] == '&' && buf[t + 1] == '&')
	{
		buf[t] = 0;
		t++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[t] == ';')
	{
		buf[t] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = t;
	return (1);
}

/**
 * replace_string - replaces string
 * @old: old string
 * @new: new string
 *
 * Return: 1 on success, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * replace_vars - replaces vars
 * @info: the parameter struct
 *
 * Return: 1 on success, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *tmp;

	while (info->argv[i])
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
		{
			i++;
			continue;
		}
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					str_duplicate(convert_number(info->status, 10, 0)));
		}
		else if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					str_duplicate(convert_number(getpid(), 10, 0)));
		}
		else
		{
			tmp = node_starts_with(info->env, &info->argv[i][1], '=');
			if (tmp)
			{
				replace_string(&(info->argv[i]),
						str_duplicate(_strchr(tmp->str, '=') + 1));
			}
			else
			{
				replace_string(&info->argv[i], str_duplicate(""));
			}
		}
		i++;
	}
	return (0);
}
/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: current position
 * @i: starting position
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t t = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			t = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			t = len;
		}
	}

	*p = t;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i = 0;
	list_t *tmp;
	char *ptr;

	while (i < 10)
	{
		tmp = node_starts_with(info->alias, info->argv[0], '=');
		if (!tmp)
		{
			return (0);
		}
		free(info->argv[0]);
		ptr = _strchr(tmp->str, '=');
		if (!ptr)
		{
			return (0);
		}
		ptr = str_duplicate(ptr + 1);
		if (!ptr)
		{
			return (0);
		}
		info->argv[0] = ptr;
		i++;
	}
	return (1);
}
