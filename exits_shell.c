#include "simple_shell.h"

/**
 **_strncpy - a function that copies a string
 *@dest: the destination string
 *@src: source string
 *@n: amount of characters to be copied
 *Return: concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int a;
	int b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 **_strncat - a function that concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: amount of bytes to be maximally used
 *Return: concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int a;
	int b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (s);
}

/**
 **_strchr - a function that locates character in a string
 *@s: string to be parsed
 *@c: character to look for
 *Return: pointer to the memory area
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
