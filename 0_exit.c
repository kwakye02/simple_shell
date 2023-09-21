#include "main.h"
/**
 * _strncpy - Copies a number of characters from one string to another.
 * @dest: Destination string.
 * @src: Source string.
 * @n: Number of characters to copy.
 * Return: Pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;
	char *initialDest = dest;

	for (i = 0; src[i] && i < n; i++)
	{
		dest[i] = src[i];
	}
	for (; i < n; i++)
	{
		dest[i] = '\0';
	}
	return (initialDest);
}

/**
 * _strncat - Concatenates two strings up to a given number of characters.
 * @dest: Target string.
 * @src: String to concatenate.
 * @n: Maximum number of characters to concatenate.
 * Return: Pointer to the destination string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0;
	int x = 0;
	char *initialDest = dest;

	while (dest[i])
	{
		i++;
	}
	while (src[x] && x < n)
	{
		dest[i] = src[x];
		i++;
		x++;
	}
	if (x < n)
	{
		dest[i] = '\0';
	}
	return (initialDest);
}

/**
 * _strchr - Finds the first occurrence of a character in a string.
 * @s: String to search.
 * @c: Character to find.
 * Return: Pointer to the found character or NULL if not found.
 */
char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}
	if (c == '\0')
	{
		return (s);
	}
	return (NULL);
}
