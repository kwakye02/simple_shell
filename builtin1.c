#include "main.h"
/**
 * show_history - displays the history list
 * one command per line with line numbers starting at 0.
 * @shell_data: Structure containing potential arguments.
 * Return: Always 0
 */
int show_history(info_t *shell_data)
{
	display_list(shell_data->history);
	return (0);
}
/**
 * remove_alias - removes an alias based on a string.
 * @data: parameter structure.
 * @str: the alias string.
 * Return: 0 on success, 1 on error.
 */
int remove_alias(info_t *data, char *str)
{
	char *alias_part, delimiter;
	int outcome;

	alias_part = find_char(str, '=');
	if (!alias_part)
		return (1);
	delimiter = *alias_part;
	*alias_part = 0;
	outcome = delete_node(&(data->alias),
		get_node(data->alias, match_node_start(data->alias, str, -1)));
	*alias_part = delimiter;
	return (outcome);
}
/**
 * create_alias - sets alias based on a string.
 * @data: parameter structure.
 * @str: the alias string.
 * Return: 0 on success, 1 on error.
 */
int create_alias(info_t *data, char *str)
{
	char *alias_part;

	alias_part = find_char(str, '=');
	if (!alias_part)
		return (1);
	if (!*++alias_part)
		return (remove_alias(data, str));

	remove_alias(data, str);
	return (append_node_to_end(&(data->alias), str, 0) == NULL);
}

/**
 * display_alias - prints an alias string.
 * @alias_node: the alias node.
 * Return: 0 on success, 1 on error.
 */
int display_alias(list_t *alias_node)
{
	char *delimiter = NULL, *ptr = NULL;

	if (alias_node)
	{
		delimiter = find_char(alias_node->str, '=');
		for (ptr = alias_node->str; alias_ptr <= delimiter; ptr++)
			putchar_to_output(*ptr);
		print_string("'");
		print_string(delimiter + 1);
		print_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - manages aliases similar to the alias builtin.
 * @data: Structure containing potential arguments.
 * Return: Always 0.
 */
int manage_alias(info_t *data)
{
	int x = 0;
	char *delimiter = NULL;
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
	for (x = 1; data->argv[x]; idx++)
	{
		delimiter = find_char(data->argv[x], '=');
		if (delimiter)
			create_alias(data, shell_data->argv[x]);
		else
			display_alias(match_node(data->alias, data->argv[x], '='));
	}

	return (0);
}
