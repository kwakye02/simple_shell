#include "main.h"

/**
 * _strcpy - Transfers the content from source to destination string.
 * @dest: The destination buffer.
 * @src: The source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
{
	char *base = dest;

	if (dest == src || !src)
		return (dest);
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (base);
}

/**
 * _strdup - Creates a copy of a provided string.
 * @str: Input string to be duplicated.
 *
 * Return: Pointer to the new string or NULL if memory allocation fails.
 */
char *_strdup(const char *str)
{
	char *copy;
	int i, len = 0;

	if (!str)
		return (NULL);
	while (str[len])
		len++;
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	for (i = 0; i <= len; i++)
		copy[i] = str[i];

	return (copy);
}

/**
 * _puts - Outputs a string to the console.
 * @str: Input string to be displayed.
 * Return: None.
 */
void _puts(char *str)
{
	if (!str)
		return;
	while (*str)
	{
		_putchar(*str++);
	}
}

/**
 * _putchar - Writes a single character to stdout.
 * @c: Character to be written.
 * Return: 1 if successful, -1 if there's an error.
 */
int _putchar(char c)
{
	static int bufIndex;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || bufIndex >= WRITE_BUF_SIZE)
	{
		write(1, buffer, bufIndex);
		bufIndex = 0;
	}
	if (c != BUF_FLUSH)
		buffer[bufIndex++] = c;

	return (1);
}

