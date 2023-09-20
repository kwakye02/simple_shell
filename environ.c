#include "main.h"
/**
 * _myenv - Display the current environment variables.
 * @current_info: Pointer to the structure with stored
 *arguments and other relevant info.
 * Return: 0 on success.
 */
int _myenv(info_t *current_info)
{
	print_list_str(current_info->env);
	return (0);
}
/**
 * _getenv - Retrieve the value associated with an environment variable.
 * @current_info: Pointer to the structure with stored arguments.
 * @variable_name: Name of the environment variable to be retrieved.
 * Return: Value of the environment variable, or NULL if not found.
 */
char *_getenv(info_t *current_info, const char *variable_name)
{
	list_t *current_node = current_info->env;
	char *match_str;

	while (current_node)
	{
		match_str = starts_with(current_node->str, variable_name);
		if (match_str && *match_str)
			return (match_str);
		current_node = current_node->next;
	}
	return (NULL);
}
/**
 * _mysetenv - Set or update the value of an environment variable.
 * @current_info: Pointer to the structure with stored arguments.
 * Return: 0 if environ variable is set or updated and 1 otherwise.
 */
int _mysetenv(info_t *current_info)
{
	if (current_info->argc != 3)
	{
		_eputs("Invalid argument count.\n");
		return (1);
	}
	if (_setenv(current_info, current_info->argv[1], current_info->argv[2]))
		return (0);
	return (1);
}
/**
 * _myunsetenv - Remove a specified environment variable.
 * @current_info: Pointer to the structure with stored arguments.
 * Return: 0 on success, 1 otherwise.
 */
int _myunsetenv(info_t *current_info)
{
	int x;

	if (current_info->argc == 1)
	{
		_eputs("Insufficient arguments provided.\n");
		return (1);
	}
	for (idx = 1; idx <= current_info->argc; x++)
		_unsetenv(current_info, current_info->argv[x]);

	return (0);
}
/**
 * populate_env_list - Populate a list with the current environment variables.
 * @current_info: Pointer to the structure with stored arguments
 * Return: 0 on success.
 */

int populate_env_list(info_t *current_info)
{
	list_t *temp_node = NULL;
	size_t count;

	for (count = 0; environ[count]; count++)
		add_node_end(&temp_node, environ[count], 0);
	current_info->env = temp_node;
	return (0);
}

