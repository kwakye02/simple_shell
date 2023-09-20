#include "main.h"

/**
 * is_interactive_mode - checks if shell is in interactive mode
 * @data: structure containing shell information
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int is_interactive_mode(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->input_fd <= 2);
}
/**
 * is_separator - checks if a character is a specified separator
 * @ch: the character to inspect
 * @separator: the separator string
 * Return: 1 if true, 0 if false
 */
int is_separator(char ch, char *separator)
{
	while (*separator)
	{
		if (*separator++ == ch)
	{
		return (1);
	}
	}
	return (0);
}
/**
 * is_letter - checks if a character is alphabetic
 * @ch: the character to inspect
 * Return: 1 if ch is a letter, 0 otherwise
 */
int is_letter(int ch)
{
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}
/**
 * str_to_int - converts a string to an integer
 * @str: the string to convert
 * Return: 0 if no numbers in string, the converted integer otherwise
 */
int str_to_int(char *str)
{
	int index, multiplier = 1, stop = 0;
	unsigned int value = 0;

	for (index = 0; str[index] != '\0' && stop != 2; index++)
	{
		if (str[index] == '-')
		{
			multiplier *= -1;
		}

		if (str[index] >= '0' && str[index] <= '9')
		{
			stop = 1;
			value = value * 10 + (str[index] - '0');
		}
		else if (stop == 1)
		{
			stop = 2;
		}
	}
	return (multiplier == -1 ? -value : value);
}
