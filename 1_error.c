#include "main.h"

/**
 * _erratoi - Converts a string to an integer.
 * @s: The string for conversion.
 * Return: 0 or -1
 */
int _erratoi(char *s)
{
	int index = 0;
	unsigned long int value = 0;

	if (*s == '+')
		s++;

	while (s[index])
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			value = value * 10 + (s[index] - '0');
			if (value > INT_MAX)
				return (-1);
		}
		else
			return (-1);

		index++;
	}
	return (value);
}

/**
 * print_error - Outputs an error message.
 * @info: Information struct.
 * @estr: Error type in string form.
 * Return: None.
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->err_line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Outputs a decimal number.
 * @input: The number to display.
 * @fd: File descriptor.
 * Return: Number of characters displayed.
 */
int print_d(int input, int fd)
{
	int (*chosen_putchar)(char) = _putchar;
	int digit, output_count = 0;
	unsigned int abs_value, current_value;

	if (fd == STDERR_FILENO)
		chosen_putchar = _eputchar;

	if (input < 0)
	{
		abs_value = -input;
		chosen_putchar('-');
		output_count++;
	}
	else
		abs_value = input;

	current_value = abs_value;
	for (digit = 1000000000; digit > 1; digit /= 10)
	{
		if (abs_value / digit)
		{
			chosen_putchar('0' + current_value / digit);
			output_count++;
		}
		current_value %= digit;
	}
	chosen_putchar('0' + current_value);
	output_count++;
	return (output_count);
}
/**
 * convert_number - Converts a number to string.
 * @num: The number for conversion.
 * @base: The base for conversion.
 * @flags: Argument flags.
 * Return: The converted string.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *d;
	static char result[50];
	char is_negative = 0;
	char *end = &result[49];
	unsigned long val = num;

	*end = '\0';
	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		val = -num;
		is_negative = '-';
	}
	d = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";

	do {
		*--end = d[val % base];
		val /= base;
	} while (val != 0);

	if (is_negative)
		*--end = is_negative;

	return (end);
}
/**
 * remove_comments - Removes comments from a string.
 * @buf: The string to process.
 * Return: None.
 */
void remove_comments(char *buf)
{
	int index;

	for (index = 0; buf[index]; index++)
	{
		if (buf[index] == '#' && (index == 0 || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
	}
}
