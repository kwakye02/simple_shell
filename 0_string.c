#include "main.h"

/**
 * _strlen - Computes the size of the given string.
 * @s: The input string.
 * Return: The length of the string.
 */
int _strlen(char *s)
{
	int len = 0;

	if (!s)
		return (0);
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

/**
 * _strcmp - Compares two strings lexicographically.
 * @s1: First string.
 * @s2: Second string.
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if equal.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * starts_with - Verifies if a string starts with a given substring.
 * @haystack: Main string.
 * @needle: Substring to check.
 * Return: Address after the substring if found, otherwise NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle && *haystack == *needle)
	{
		haystack++;
		needle++;
	}
	return (*needle == '\0' ? (char *)haystack : NULL);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: Destination string.
 * @src: Source string.
 * Return: Pointer to the concatenated string.
 */
char *_strcat(char *dest, char *src)
{
	char *base = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';

	return (base);
}
