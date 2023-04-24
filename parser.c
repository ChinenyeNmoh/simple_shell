#include "shell.h"

/**
 * is_cmd - checks if a file is executable
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat ex;

	(void)info;
	if (!path || stat(path, &ex))
		return (0);

	if (ex.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: PATH string
 * @start: index to start
 * @stop: index to stop
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int i = start, j = 0;

	while (i < stop && pathstr[i] != ':')
	{
		buff[j++] = pathstr[i++];
	}
	buff[j] = '\0';

	return (buff);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int pos = 0, i;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((str_length(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	for (i = 0; pathstr[i] != '\0'; i++)
	{
		if (pathstr[i] == ':')
		{
			path = dup_chars(pathstr, pos, i);
			if (!*path)
				str_concat(path, cmd);
			else
			{
				str_concat(path, "/");
				str_concat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			pos = i + 1;
		}
	}
	path = dup_chars(pathstr, pos, str_length(pathstr));
	if (!*path)
		str_concat(path, cmd);
	else
	{
		str_concat(path, "/");
		str_concat(path, cmd);
	}
	if (is_cmd(info, path))
		return (path);
	return (NULL);
}
