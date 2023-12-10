#include "simple_shell.h"

/**
 * _strcpy - a function that copies a string
 * @dest: destination
 * @src: source
 * Return: dest
 */

char *_strcpy(char *dest, char *src)
{
	int num = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[num])
	{
		dest[num] = src[num];
		num++;
	}
	dest[num] = 0;
	return (dest);
}

/**
 * _strdup - a function duplicates a string
 * @str: string to duplicate
 * Return: len
 */

char *_strdup(const char *str)
{
	int length = 0;
	char *len;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	len = malloc(sizeof(char) * (length + 1));
	if (!len)
		return (NULL);
	for (length++; length--;)
		len[length] = *--str;
	return (len);
}

/**
 *_puts - a function that prints an input string
 *@str:  string to be printed
 */

void _puts(char *str)
{
	int num = 0;

	if (!str)
		return;
	while (str[num] != '\0')
	{
		_putchar(str[num]);
		num++;
	}
}

/**
 * _putchar - function that writes the character c to stdout
 * @c: character to print
 * Return: 1
 */

int _putchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int num;

	if (c == BUF_FLUSH || num >= WRITE_BUF_SIZE)
	{
		write(1, buf, num);
		num = 0;
	}
	if (c != BUF_FLUSH)
		buf[num++] = c;
	return (1);
}
