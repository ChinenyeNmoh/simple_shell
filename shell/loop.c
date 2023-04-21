#include "shell.h"
/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t t = 0;
	int builtinret = 0;

	while (t != -1 && builtinret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		t = get_input(info);
		if (t != -1)
		{
			set_info(info, av);
			builtinret = find_builtin(info);
			if (builtinret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtinret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtinret);
}
/**
 * fork_cmd - forks a process
 * @info: the parameter & return info struct
 *
 * Return: nothing
 */
void fork_cmd(info_t *info)
{
	pid_t child;

	child = fork();
	if (child == -1)
	{
		perror("Error:");
		return;
	}
	if (child == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

/**
 * find_cmd - finds a command
 * @info: the parameter & return info struct
 *
 * Return: nothing
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i = 0, j = 0;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	while (info->arg[i])
	{
		if (!is_delim(info->arg[i], " \t\n"))
		{
			j++;
		}
		i++;
	}
	if (!j)
	{
		return;
	}
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
		{
			fork_cmd(info);
		}
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i = 0, built_in = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _mygetenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	while (builtintbl[i].type != NULL)
	{
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in = builtintbl[i].func(info);
			break;
		}
		i++;
	}
	return (built_in);
}
