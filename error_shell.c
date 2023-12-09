#include "simple_shell.h"

/**
 *_eputs - a function that prints an input string
 * @str: string to be printed
 */

void _eputs(char *str)
{
	int num = 0;

	if (!str)
		return;
	while (str[num] != '\0')
	{
		_eputchar(str[num]);
		num++;
	}
}

/**
 * _eputchar - a function that writes the character c to stderr
 * @c: character to print
 * Return: 1
 */

int _eputchar(char c)
{
	static int num;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || num >= WRITE_BUF_SIZE)
	{
		write(2, buf, num);
		num = 0;
	}
	if (c != BUF_FLUSH)
		buf[num++] = c;
	return (1);
}

/**
 * _putfd - a function that writes the character c to given fd
 * @c: character to print
 * @fd: filedescriptor
 * Return: 1
 */

int _putfd(char c, int fd)
{
	static int num;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || num >= WRITE_BUF_SIZE)
	{
		write(fd, buf, num);
		num = 0;
	}
	if (c != BUF_FLUSH)
		buf[num++] = c;
	return (1);
}

/**
 *_putsfd - a function that prints an input string
 * @str: string to be printed
 * @fd: filedescriptor
 * Return: number of chars put
 */

int _putsfd(char *str, int fd)
{
	int num;

	num = 0;

	if (!str)
		return (0);
	while (*str)
	{
		num += _putfd(*str++, fd);
	}
	return (num);
}
