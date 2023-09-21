#include "main.h"

/**
*is_chain - Verify if current char in buffer is a command delimiter
* @info: the parameter structure
* @buf: the char buffer
* @p: current position in buf
* Return: 1 or 0
*/
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t pos = *p;

	if (buf[pos] == '|' && buf[pos + 1] == '|')
	{
		buf[pos] = 0;
		pos++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[pos] == '&' && buf[pos + 1] == '&')
	{
		buf[pos] = 0;
		pos++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[pos] == ';')
	{
		buf[pos] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = pos;
	return (1);
}
/**
* check_chain - Decide if chaining should continue based on last status
* @info: the parameter structure
* @buf: the char buffer
* @p: current position in buf
* @i: starting position in buf
* @len: length of buf
* Return: void
*/
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t pos = *p;

	if (info->cmd_buf_type == CMD_AND && info->status)
	{
		buf[i] = 0;
		pos = len;
	}
	if (info->cmd_buf_type == CMD_OR && !info->status)
	{
		buf[i] = 0;
		pos = len;
	}
	*p = pos;
}
/**
* replace_alias - Substitute aliases in the tokenized string
* @info: the parameter structure
* Return: 1 or 0
*/
int replace_alias(info_t *info)
{
	int count;
	list_t *entry;
	char *alias_val;

	for (count = 0; count < 10; count++)
	{
		entry = node_starts_with(info->alias, info->argv[0], '=');
		if (!entry)
			return (0);
		free(info->argv[0]);
		alias_val = _strchr(entry->str, '=');
		if (!alias_val)
			return (0);
		alias_val = _strdup(alias_val + 1);
		if (!alias_val)
			return (0);
		info->argv[0] = alias_val;
	}
	return (1);
}
/**
* replace_vars - Substitute variables in the tokenized string
* @info: the parameter structure
* Return: 1 or 0
*/
int replace_vars(info_t *info)
{
	int x;
	list_t *entry;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			replace_string(&(info->argv[x]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		entry = node_starts_with(info->env, &info->argv[x][1], '=');
		if (entry)
		{
			replace_string(&(info->argv[x]),
				_strdup(_strchr(entry->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], _strdup(""));
	}
	return (0);
}
/**
* replace_string - Swap the old string with a new one
* @old: address of old string
* @new: new string to replace with
* Return: 1 or 0
*/
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
