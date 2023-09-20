#include "main.h"

/**
 * shell_exit - exits the shell
 * @data: Structure containing potential arguments.
 * Return: exits with a given exit status
 * (0) if data.argv[0] != "exit"
 */
int shell_exit(info_t *data)
{
	int status_check;

	if (data->argv[1])
	{
		status_check = error_atoi(data->argv[1]);
		if (status_check == -1)
		{
			data->status = 2;
			display_error(data, "Invalid number: ");
			error_puts(data->argv[1]);
			error_putchar('\n');
			return (1);
		}
		data->error_num = error_atoi(data->argv[1]);
		return (-2);
	}
	data->error_num = -1;
	return (-2);
}

/**
 * shell_cd - changes the current directory of the process
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int shell_cd(info_t *data)
{
	char *current_path, *dir, buffer[1024];
	int cd_result;

	current_path = getcwd(buffer, 1024);
	if (!current_path)
		_puts("Error: Failed to get current directory.\n");
	if (!data->argv[1])
	{
		dir = get_env(data, "HOME=");
		if (!dir)
			cd_result = chdir((dir = get_env(data, "PWD=")) ? dir : "/");
		else
			cd_result = chdir(target_dir);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!get_env(data, "OLDPWD="))
		{
			_puts(current_path);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(data, "OLDPWD=")), _putchar('\n');
		cd_result = chdir((dir = get_env(data, "OLDPWD=")) ? dir : "/");
	}
	else
		cd_result = chdir(shell_data->argv[1]);
	if (cd_result == -1)
	{
		display_error(data, "Unable to cd to ");
		error_puts(data->argv[1]), error_putchar('\n');
	}
	else
	{
		set_env(data, "OLDPWD", get_env(data, "PWD="));
		set_env(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * shell_help - provides help information
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int shell_help(info_t *data)
{
	char **args_list;

	args_list = data->argv;
	_puts("Help function called. Implementation pending. \n");
	if (0)
		_puts(*args_list);
	return (0);
}
