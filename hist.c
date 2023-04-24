#include "shell.h"

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node;
	int i;

	for (node = info->history, i = 0; node; node = node->next, i++)
	{
		node->num = i;
	}
	info->histcount = i;
	return (i);
}

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string
 */

char *get_history_file(info_t *info)
{
	char *buff, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (str_length(dir) + str_length(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	str_concat(buff, "/");
	str_concat(buff, HIST_FILE);
	return (buff);
}
/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success otherwise -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *tmp = NULL;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	tmp = info->history;
	while (tmp)
	{
		_putsfd(tmp->str, fd);
		_putfd('\n', fd);
		tmp = tmp->next;
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * read_history - reads history
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, line = 0;
	ssize_t fd, rlen, size = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		size = st.st_size;
	if (size < 2)
		return (0);
	buf = malloc(sizeof(char) * (size + 1));
	if (!buf)
		return (0);
	rlen = read(fd, buf, size);
	buf[size] = 0;
	if (rlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < size; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, line++);
			last = i + 1;
		}
	}
	if (last != i)
		build_history_list(info, buf + last, line++);
	free(buf);
	info->histcount = line;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}
/**
 * build_history_list - adds to linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *tmp = NULL;

	if (info->history)
		tmp = info->history;
	add_node_end(&tmp, buf, linecount);

	if (!info->history)
		info->history = tmp;
	return (0);
}
