#include "main.h"
/**
 * get_history_file - Retrieves the path for the history file
 * @info: Information structure
 * Return: dynamically allocated string specifying history file path
 */
char *get_history_file(info_t *info)
{
	char *path_buffer, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);

	path_buffer = malloc((_strlen(dir) + _strlen(HIST_FILE) + 2) * sizeof(char));
	if (!path_buffer)
		return (NULL);

	path_buffer[0] = '\0';
	_strcpy(path_buffer, dir);
	_strcat(path_buffer, "/");
	_strcat(path_buffer, HIST_FILE);

	return (path_buffer);
}

/**
* write_history - Saves or updates history to a file
* @info: Information structure
* Return: 1 if operation is successful, otherwise -1
*/
int write_history(info_t *info)
{
	ssize_t file_descriptor;
	char *file_name = get_history_file(info);
	list_t *current_n = NULL;

	if (!file_name)
		return (-1);

	file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (file_descriptor == -1)
		return (-1);

	for (current_n = info->history; current_n; current_n = current_n->next)
	{
		_putsfd(current_n->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}
	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);

	return (1);
}
/**
* read_history - reads the history from a file
* @info: info structure
* Return: history count or 0
*/
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}
/**
 * build_history_list - Inserts a new entry into the history list
 * @info: Information structure
 * @data_buffer: Buffer containing history entry
 * @total_entries: Total number of history entries
 * Return: Always 0
 */
int build_history_list(info_t *info, char *data_buffer, int total_entries)
{
	list_t *current_node = NULL;

	if (info->history)
		current_node = info->history;

	add_node_end(&current_node, data_buffer, total_entries);

	if (!info->history)
		info->history = current_node;

	return (0);
}

/**
 * renumber_history - Resets line numbers in history list
 * @info: Information structure
 *
 * Return: New count of history lines
 */
int renumber_history(info_t *info)
{
	list_t *current_node = info->history;
	int counter = 0;

	while (current_node)
	{
		current_node->num = counter++;
		current_node = current_node->next;
	}

	return (info->histcount = counter);
}

