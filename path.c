#include "main.h"

/**
 * is_cmd - Check if a file is a runnable command.
 * @details: Information structure.
 * @filepath: Path to the potential command
 * Return: 1 if it's a command, 0 otherwise.
 */
int is_cmd(info_t *details, char *filepath)
{
	struct stat st;

	(void)details;
	if (!filepath || stat(filepath, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Make a copy of specific characters.
 * @path_data: The PATH data string.
 * @begin: Start index.
 * @end: End index.
 * Return: Pointer to the copied characters.
 */
char *dup_chars(char *path_data, int begin, int end)
{
	static char buffer[1024];
	int index = 0, iterator = 0;

	for (iterator = 0, index = begin; index < end; index++)
		if (path_data[index] != ':')
			buffer[iterator++] = path_data[index];
	buffer[iterator] = 0;
	return (buffer);
}

/**
 * find_path- Search for a command in the PATH data.
 * @details: Information structure.
 * @path_data: The PATH data string.
 * @command: The command to locate.
 * Return: Full path of the command if found, NULL otherwise.
 */
char *find_path(info_t *details, char *path_data, char *command)
{
	int index = 0, pos = 0;
	char *path_segment;

	if (!path_data)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_cmd(details, command))
			return (command);
	}
	while (1)
	{
		if (!path_data[index] || path_data[index] == ':')
		{
			path_segment = dup_chars(path_data, pos, index);
			if (!*path_segment)
				_strcat(path_segment, command);
			else
			{
				_strcat(path_segment, "/");
				_strcat(path_segment, command);
			}
			if (is_cmd(details, path_segment))
				return (path_segment);
			if (!path_data[index])
				break;
			pos = index;
		}
		index++;
	}
	return (NULL);
}

