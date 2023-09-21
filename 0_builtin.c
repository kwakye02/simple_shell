#include "main.h"
/**
 * _myexit - Handles shell exit procedure.
 * @info: Holds arguments and other info for the function.
 * Return: Exits depending on the status. Returns (0) if command isn't "exit".
 */
int _myexit(info_t *info)
{
	int exit_status;

	if (info->argv[1])
	{
		exit_status = _erratoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_code = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_code = -1;
	return (-2);
}

/**
 * _mycd - Modifies the current working directory.
 * @info: Holds arguments and other info for the function.
 * Return: Always returns 0.
 */
int _mycd(info_t *info)
{
	char *current_dir, *dir, buffer_space[1024];
	int directory_change;

	current_dir = getcwd(buffer_space, 1024);
	if (!current_dir)
		_puts("Error: Failed to get current directory.\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			directory_change =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			directory_change = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		directory_change =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		directory_change = chdir(info->argv[1]);
	if (directory_change == -1)
	{
		print_error(info, "Failed to switch directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer_space, 1024));
	}
	return (0);
}

/**
 * _myhelp - Placeholder for a help function.
 * @info: Holds arguments and other info for the function.
 * Return: Always returns 0.
 */
int _myhelp(info_t *info)
{
	char **args;

	args = info->argv;
	_puts("Help function activated. Implementation pending.\n");
	if (0)
		_puts(*args);
	return (0);
}

