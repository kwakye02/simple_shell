#include "main.h"

/**
 * _myhistory - Show command history with line numbers.
 * @info: Arguments structure.
 * Return: Always returns 0.
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
/**
 * unset_alias - Removes a specified alias.
 * @info: Arguments structure.
 * @str: Alias string.
 * Return: 0 if successful, otherwise 1.
 */
int unset_alias(info_t *info, char *str)
{
	char *divider, saved_char;
	int result;

	divider = _strchr(str, '=');
	if (!divider)
		return (1);
	saved_char = *divider;
	*divider = 0;

	result = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*divider = saved_char;
	return (result);
}
/**
 * set_alias - Define a new alias.
 * @info: Arguments structure.
 * @str: Alias string.
 * Return: 0 if successful, otherwise 1.
 */
int set_alias(info_t *info, char *str)
{
	char *divider;

	divider = _strchr(str, '=');
	if (!divider)
		return (1);
	if (!*(divider + 1))
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias - Output an alias.
 * @node: The node containing the alias.
 * Return: 0 or 1
 */
int print_alias(list_t *node)
{
	char *d = NULL, *alias_start = NULL;

	if (node)
	{
		d = _strchr(node->str, '=');
		for (alias_start = node->str; alias_start <= d; alias_start++)
		_putchar(*alias_start);
		_putchar('\'');
		_puts(d + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myalias - Replicates the functionality of the alias command.
 * @info: Arguments structure.
 * Return: Always returns 0.
 */
int _myalias(info_t *info)
{
	int c = 0;
	char *d = NULL;
	list_t *current_node = NULL;

	if (info->argc == 1)
	{
		current_node = info->alias;
		while (current_node)
		{
			print_alias(current_node);
			current_node = current_node->next;
		}
		return (0);
	}
	for (c = 1; info->argv[c]; c++)
	{
		d = _strchr(info->argv[c], '=');
		if (d)
			set_alias(info, info->argv[c]);
		else
			print_alias(node_starts_with(info->alias, info->argv[c], '='));
	}
	return (0);
}

