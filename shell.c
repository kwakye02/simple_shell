#include "main.h"

/**
 *hsh - Primary shell loop
 * @data: Shell datarmation structure
 * @argument_vector: argument vector from main()
 * Return: 0 if successful, 1 if error, or specific error code
 */
int hsh(info_t *data, char **argument_vector)
{
	int builtin_results = 0;
	ssize_t read_val = 0;

	while (read_val != -1 && builtin_results != -2)
	{
		clear_info(data);
		if (is_interactive_mode(data))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		read_val = get_input(data);
		if (read_val != -1)
		{
			set_info(data, argument_vector);
			builtin_results = find_builtin(data);
			if (builtin_results == -1)
				find_cmd(data);
		}
		else if (is_interactive_mode(data))
			_putchar('\n');
		free_info(data, 0);
	}
	write_history(data);
	free_info(data, 1);
	if (!is_interactive_mode(data) && data->status)
		exit(data->status);
	if (builtin_results == -2)
	{
		if (data->err_code == -1)
			exit(data->status);
		exit(data->err_code);
	}
	return (builtin_results);
}

/**
 * find_builtin - Finds a builtin command
 * @data: Shell information structure
 *
 * Return: -1 if no builtin found,
 * 0 if successful execution of builtin,
 * 1 if builtin found but had an issue,
 * 2 if builtin signals an exit
 */
int find_builtin(info_t *data)
{
	int x, builtin_results = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[x].type; x++)
		if (_strcmp(data->argv[0], builtintbl[x].type) == 0)
		{
			data->line_count++;
			builtin_results = builtintbl[x].func(data);
			break;
		}
	return (builtin_results);
}

/**
 * find_cmd - Identifies a command in PATH
 * @data: Shell information structure
* Return: void
 */
void find_cmd(info_t *data)
{
	char *cmd_path = NULL;
	int i, char_count;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->err_line_count++;
		data->linecount_flag = 0;
	}
	for (char_count = 0, i = 0; data->arg[i]; i++)
		if (!is_delim(data->arg[i], " \t\n"))
			char_count++;
	if (!char_count)
		return;

	cmd_path = find_path(data, _getenv(data, "PATH="), data->argv[0]);
	if (cmd_path)
	{
		data->path = path;
		fork_cmd(data);
	}
	else
	{
		if ((is_interactive_mode(data) || _getenv(data, "PATH=")
					|| data->argv[0][0] == '/') && is_cmd(data, data->argv[0]))
			fork_cmd(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
 * fork_cmd - Forks and runs the command
 * @data: Shell information structure
 * Return: returns void
 */
void fork_cmd(info_t *data)
{
	pid_t proc_id;

	proc_id = fork();

	if (proc_id == -1)
	{
		perror("Error:");
		return;
	}
	if (proc_id == 0)
	{
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}
