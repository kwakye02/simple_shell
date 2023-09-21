#include "main.h"

/**
 * get_environ - Retrieves the current environment in string array format.
 * @info: Structure housing potential arguments and related information.
 * Return: Current environment in string array format.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ =  list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Deletes a specified environment variable.
 * @info: Contains potential arguments and other related data.
 * @var: Target environment variable for deletion.
 * Return: 1 if successful deletion, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *current_node = info->env;
	size_t i = 0;
	char *match_point;

	if (!current_node || !var)
		return (0);

	while (current_node)
	{
		match_point = starts_with(current_node->str, var);
		if (match_point && *match_point == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			current_node = info->env;
			continue;
		}
		current_node = current_node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Introduces or updates a given environment variable.
 * @info: Contains potential arguments and other relevant information.
 * @var: Target environment variable for addition or update.
 * @value: Value to set for the specified environment variable.
 * Return: 0 on success, 1 on failure.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *temp_str = NULL;
	list_t *current_node;
	char *match_point;

	if (!var || !value)
		return (0);

	temp_str = malloc(_strlen(var) + _strlen(value) + 2);
	if (!temp_str)
		return (1);
	_strcpy(temp_str, var);
	_strcat(temp_str, "=");
	_strcat(temp_str, value);

	current_node = info->env;
	while (current_node)
	{
		match_point = starts_with(current_node->str, var);
		if (match_point && *match_point == '=')
		{
			free(current_node->str);
			current_node->str = temp_str;
			info->env_changed = 1;
			return (0);
		}
		current_node = current_node->next;
	}
	add_node_end(&(info->env), temp_str, 0);
	free(temp_str);
	info->env_changed = 1;
	return (0);
}
