#include "main.h"

/**
 * display_history - Shows the command history list with line numbers.
 * @data: Pointer to the structure containing potential arguments.
 *  Return: Always 0
 */
int display_history(info_t *data)
{
	print_list(data->history);
	return (0);
}

/**
 * remove_alias - Removes an alias based on the given string.
 * @data: Pointer to the structure containing potential arguments.
 * @str: The alias string to remove.
 * Return: 0 if successful, 1 otherwise.
 */
int remove_alias(info_t *data, char *str)
{
	char *delimiter_position, delimiter_char;
	int result;

	delimiter_position = _strchr(str, '=');
	if (!delimiter_position)
		return (1);
	delimiter_char = *delimiter_position;
	*delimiter_position = 0;
	result = delete_node_at_index(&(data->alias),
		get_node_index(data->alias, node_starts_with(data->alias, str, -1)));
	*delimiter_position = delimiter_char;
	return (result);
}
/**
 * create_alias - Sets a new alias based on the given string.
 * @data: Pointer to the structure containing potential arguments.
 * @str: The new alias string to set.
 * Return: 0 if successful, 1 otherwise.
 */
int create_alias(info_t *data, char *str)
{
	char *delimiter_position;

	delimiter_position = _strchr(str, '=');
	if (!delimiter_position)
		return (1);
	if (!*++delimiter_position)
		return (remove_alias(data, str));

	remove_alias(data, str);
	return (add_node_end(&(data->alias), str, 0) == NULL);
}
/**
 * display_alias - Prints the specified alias node.
 * @alias_node: The alias node to print.
 * Return: 0 if successful, 1 otherwise.
 */
int display_alias(list_t *alias_node)
{
	char *delim_position = NULL, *a_str = NULL;

	if (alias_node)
	{
		delimiter_position = _strchr(alias_node->str, '=');
		for (*a_str = alias_node->str; a_str <= delim_position; a_str++)
			_putchar(*a_str);
		_putchar('\'');
		_puts(delim_position + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - Handles the alias command.
 * @data: Pointer to the structure containing potential arguments.
 *  Return: Always 0
 */
int manage_alias(data_t *data)
{
	int arg_i = 0;
	char *delimiter_position = NULL;
	list_t *alias_node = NULL;

	if (data->argc == 1)
	{
		alias_node = data->alias;
		while (alias_node)
		{
			display_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}
	for (arg_i = 1; data->argv[arg_i]; arg_i++)
	{
		delimiter_position = _strchr(data->argv[arg_i], '=');
		if (delimiter_position)
			create_alias(data, data->argv[arg_i]);
		else
			display_alias(node_starts_with(data->alias, data->argv[arg_i], '='));
	}

	return (0);
}
