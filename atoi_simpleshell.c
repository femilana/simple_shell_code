#include "simple_shell.h"

/**
 * interactive - it returns true if shell is in interactive mode
 * @info: a struct address
 * Return: returns 1 if interactive mode, 0 otherwise
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - to checks if character is a delimeter
 * @c: the char
 * @delim: delimeter string
 * Return: return 1 if true, 0 if false
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - to checks for alphabetic character
 *@c: character to input
 *Return: return 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *atoi_simpleshell - to converts a string to an integer
 *@s: string to be converted
 *Return: returns 0 if no numbers in string, converted number otherwise
 */

int atoi_simpleshell(char *s)
{
	int num;
	int sign = 1;
	int hint = 0;
	int output;
	unsigned int result = 0;

	for (num = 0;  s[num] != '\0' && hint != 2; num++)
	{
		if (s[num] == '-')
			sign *= -1;

		if (s[num] >= '0' && s[num] <= '9')
		{
			hint = 1;
			result *= 10;
			result += (s[num] - '0');
		}
		else if (hint == 1)
			hint = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
