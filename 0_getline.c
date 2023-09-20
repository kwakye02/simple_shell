#include "main.h"

ssize_t input_buffering(info_t *info, char **buffer, size_t *buf_len)
{
	ssize_t bytes_read = 0;
	size_t temp_len = 0;

	if (!*buf_len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buffer, &temp_len, stdin);
#else
		bytes_read = fetch_line(info, buffer, &temp_len);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			if (_strchr(*buffer, ';'))
			{
				*buf_len = bytes_read;
				info->cmd_buf = buffer;
			}
		}
	}
	return (bytes_read);
}

ssize_t fetch_input(info_t *info)
{
	static char *chain_buf;
	static size_t pos = 0, next = 0, chain_len = 0;
	ssize_t bytes = 0;
	char **buf_ptr = &(info->arg), *cur_pos;

	_putchar(BUF_FLUSH);
	bytes = input_buffering(info, &chain_buf, &chain_len);
	if (bytes == -1)
		return (-1);
	if (chain_len)
	{
		next = pos;
		cur_pos = chain_buf + pos;

		check_chain(info, chain_buf, &next, pos, chain_len);
		while (next < chain_len)
		{
			if (is_chain(info, chain_buf, &next))
				break;
			next++;
		}

		pos = next + 1;
		if (pos >= chain_len)
		{
			pos = chain_len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_ptr = cur_pos;
		return (_strlen(cur_pos));
	}

	*buf_ptr = chain_buf;
	return (bytes);
}

ssize_t buffer_read(info_t *info, char *buf, size_t *idx)
{
	ssize_t bytes = 0;

	if (*idx)
		return (0);
	bytes = read(info->readfd, buf, READ_BUF_SIZE);
	if (bytes >= 0)
		*idx = bytes;
	return (bytes);
}

int fetch_line(info_t *info, char **line_ptr, size_t *line_length)
{
	static char local_buf[READ_BUF_SIZE];
	static size_t start = 0, total_len = 0;
	size_t end;
	ssize_t result = 0, cur_len = 0;
	char *temp_ptr = NULL, *new_ptr = NULL, *newline_pos;

	temp_ptr = *line_ptr;
	if (temp_ptr && line_length)
		cur_len = *line_length;
	if (start == total_len)
		start = total_len = 0;

	result = buffer_read(info, local_buf, &total_len);
	if (result == -1 || (result == 0 && total_len == 0))
		return (-1);

	newline_pos = _strchr(local_buf + start, '\n');
	end = newline_pos ? 1 + (unsigned int)(newline_pos - local_buf) : total_len;
	new_ptr = _realloc(temp_ptr, cur_len, cur_len ? cur_len + end : end + 1);
	if (!new_ptr)
		return (temp_ptr ? free(temp_ptr), -1 : -1);

	if (cur_len)
		_strncat(new_ptr, local_buf + start, end - start);
	else
		_strncpy(new_ptr, local_buf + start, end - start + 1);

	cur_len += end - start;
	start = end;
	temp_ptr = new_ptr;

	if (line_length)
		*line_length = cur_len;
	*line_ptr = temp_ptr;
	return (cur_len);
}

void ctrl_c_handler(int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

