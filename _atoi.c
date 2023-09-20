#include "main.h"

/**
 * interactive_mode - Check if the shell is in interactive mode
 * @data: pointer to the info struct
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int interactive_mode(info_t *data)
{
	return ((isatty(STDIN_FILENO) && data->readfd <= 2) ? 1 : 0);
}

/**
 * check_delim - Verify if a character is a delimiter
 * @ch: character to verify
 * @delim: delimiter string
 *
 * Return: 1 if it's a delimiter, 0 otherwise
 */
int check_delim(char ch, char *delim)
{
	while (*delim)
	{
		if (*delim++ == ch)
			return (1);
	}
	return (0);
}

/**
 * is_alpha - Determine if a character is alphabetic
 * @c: character to check
 *
 * Return: 1 if alphabetic, 0 otherwise
 */
int is_alpha(int c)
{
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0);
}

/**
 * _atoi - Convert a string to an integer
 * @str: string to convert
 *
 * Return: the integer representation of the string
 */
int _atoi(char *str)
{
	int x, sign_flag = 1, state = 0;
	unsigned int num = 0;

	for (x = 0; str[x] && state != 2; x++)
	{
		if (str[x] == '-')
			sign_flag *= -1;

		if (str[x] >= '0' && str[x] <= '9')
		{
			state = 1;
			num = num * 10 + (str[x] - '0');
		}
		else if (state == 1)
			state = 2;
	}
	if (sign_flag == -1)
		num = -num;
	return (num);
}
