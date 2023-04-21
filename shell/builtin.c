#include "shell.h"

/**
 * _mycd - change the current directory
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *ch, *directory, buff[1024];
	int chdir_ret;

	ch = getcwd(buff, 1024);
	if (!ch)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		directory = _getenv(info, "HOME=");
		if (!directory)
			chdir_ret =
				chdir((directory = _getenv(info, "PWD=")) ? directory : "/");
		else
			chdir_ret = chdir(directory);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(ch);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((directory = _getenv(info, "OLDPWD=")) ? directory : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}
/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int checkexit;

	if (info->argv[1])
	{
		checkexit = _erratoi(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * _myhelp - changes the current directory
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **argu_array;

	argu_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argu_array);
	return (0);
}

