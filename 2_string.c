
#include "main.h"

/**
 * strtow - Splits an input string based on delimiters into multiple words.
 * @str: The string to be split.
 * @d: Delimiter string used for splitting.
 * Return: Returns an array of split strings or NULL if there's an error.
 */
char **strtow(char *str, char *d)
{
	int x, i, j, k, wordCount = 0;
	char **words;

	if (!str || !str[0])
		return (NULL);
	d = d ? d : " ";
	for (x = 0; str[x]; x++)
		if (!is_delim(str[x], d) && (is_delim(str[x + 1], d) || !str[x + 1]))
			wordCount++;

	if (wordCount == 0)
		return (NULL);

	words = malloc((wordCount + 1) * sizeof(char *));
	if (!words)
		return (NULL);

	for (x = 0, i = 0; i < wordCount; i++)
	{
		while (is_delim(str[x], d))
			x++;
		j = 0;
		while (!is_delim(str[x + j], d) && str[x + j])
			j++;

		words[i] = malloc((j + 1) * sizeof(char));
		if (!words[i])
		{
			for (k = 0; k < i; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (k = 0; k < j; k++)
			words[i][k] = str[x++];
		words[i][k] = '\0';
	}
	words[i] = NULL;
	return (words);
}

/**
 * strtow2 - Breaks a string into segments based on a delimiter.
 * @str: The string to be segmented.
 * @d: Character delimiter for splitting.
 * Return: Array of segmented strings or NULL in case of an error.
 */
char **strtow2(char *str, char d)
{
	int x, i, j, k, wordCount = 0;
	char **words;

	if (!str || !str[0])
		return (NULL);

	for (x = 0; str[x]; x++)
		if (str[x] != d && (str[x + 1] == d || !str[x + 1]))
			wordCount++;

	if (wordCount == 0)
		return (NULL);

	words = malloc((wordCount + 1) * sizeof(char *));
	if (!words)
		return (NULL);

	for (x = 0, i = 0; i < wordCount; i++)
	{
		while (str[x] == d)
			x++;
		j = 0;
		while (str[x + j] != d && str[x + j])
			j++;

		words[i] = malloc((j + 1) * sizeof(char));
		if (!words[i])
		{
			for (k = 0; k < i; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (k = 0; k < j; k++)
			words[i][k] = str[x++];
		words[i][k] = '\0';
	}
	words[i] = NULL;
	return (words);
}

