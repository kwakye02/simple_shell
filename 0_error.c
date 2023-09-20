#include "main.h"

/**
 * _eputs - Display a string.
 * @str: The input string.
 * Return: None.
 */
void _eputs(char *str)
{
	int index = 0;

	if (str == NULL)
		return;

	while (str[index])
	{
		_eputchar(str[index]);
		index++;
	}
}

/**
 * _eputchar - Output a character to stderr.
 * @c: The character to display.
 * Return: 1 on success, -1 on error.
 */
int _eputchar(char c)
{
	static int count;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || count >= WRITE_BUF_SIZE)
	{
		write(2, buffer, count);
		count = 0;
	}
	if (c != BUF_FLUSH)
		buffer[count++] = c;

	return (1);
}

/**
 * _putfd - Send a character to a given fd.
 * @c: Character to display.
 * @fd: File descriptor.
 * Return: 1 on success, -1 on error.
 */
int _putfd(char c, int fd)
{
	static int count;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || count >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, count);
		count = 0;
	}
	if (c != BUF_FLUSH)
		buffer[count++] = c;

	return (1);
}

/**
 * _putsfd - Display a string to a given fd.
 * @str: Input string.
 * @fd: File descriptor.
 * Return: Number of characters displayed.
 */
int _putsfd(char *str, int fd)
{
	int count = 0;

	if (str == NULL)
		return (0);

	while (*str)
	{
		count += _putfd(*str, fd);
		str++;
	}
	return (count);
}

