#include "main.h"
/**
 * input_buf - Manages input commands.
 * @info: Struct containing parameters.
 * @buf: Pointer to buffer.
 * @len: Address of length variable.
 * Return: Number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t buffer_len = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buf, &buffer_len, stdin);
#else
		bytes_read = _getline(info, buf, &buffer_len);
#endif
		if (bytes_read > 0)
		{
			if ((*buf)[bytes_read - 1] == '\n')
			{
				(*buf)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			*len = bytes_read;
			info->cmd_buf = buf;
		}
	}
	return (bytes_read);
}

/**
 * get_input - Fetches an input line excluding the newline.
 * @info: Struct containing parameters.
 * Return: Number of bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t start, end, buffer_len;
	ssize_t bytes_read = 0;
	char **buffer_ptr = &(info->arg), *buf_pos;

	_putchar(BUF_FLUSH);
	bytes_read = input_buf(info, &buffer, &buffer_len);
	if (bytes_read == -1)
		return (-1);
	if (buffer_len)
	{
		end = start;
		buf_pos = buffer + start;
		check_chain(info, buffer, &end, start, buffer_len);
		while (end < buffer_len)
		{
			if (is_chain(info, buffer, &end))
				break;
			end++;
		}
		start = end + 1;
		if (start >= buffer_len)
		{
			start = buffer_len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buffer_ptr = buf_pos;
		return (_strlen(buf_pos));
	}
	*buffer_ptr = buffer;
	return (bytes_read);
}

/**
 * read_buf - Reads from a buffer.
 * @info: Struct containing parameters.
 * @buf: Pointer to buffer.
 * @i: Size.
 * Return: r.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t result = 0;

	if (*i)
		return (0);
	result = read(info->readfd, buf, READ_BUF_SIZE);
	if (result >= 0)
		*i = result;
	return (result);
}

/**
 * _getline - Gets the subsequent input line from STDIN.
 * @info: Struct containing parameters.
 * @ptr: Address of buffer pointer (preallocated or NULL).
 * @length: Size of buffer if it's not NULL.
 * Return: size
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char local_buf[READ_BUF_SIZE];
	static size_t pos, loc_len;
	size_t c;
	ssize_t read_val = 0, buf_size = 0;
	char *temp_ptr = NULL, *new_ptr = NULL, *newline_pos;

	temp_ptr = *ptr;
	if (temp_ptr && length)
		buf_size = *length;
	if (pos == loc_len)
		pos = loc_len = 0;

	read_val = read_buf(info, local_buf, &loc_len);
	if (read_val == -1 || (read_val == 0 && loc_len == 0))
		return (-1);

	newline_pos = _strchr(local_buf + pos, '\n');
	c = newline_pos ? 1 + (unsigned int)(newline_pos - local_buf) : loc_len;
	new_ptr = _realloc(temp_ptr, buf_size, buf_size ? buf_size + c : c + 1);
	if (!new_ptr)
		return (temp_ptr ? free(temp_ptr), -1 : -1);

	if (buf_size)
		_strncat(new_ptr, local_buf + pos, c - pos);
	else
		_strncpy(new_ptr, local_buf + pos, c - pos + 1);

	buf_size += c - pos;
	pos = c;
	temp_ptr = new_ptr;

	if (length)
		*length = buf_size;
	*ptr = temp_ptr;
	return (buf_size);
}

/**
 * sigintHandler - Handles the SIGINT signal.
 * @sig_num: Signal number.
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
