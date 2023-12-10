#include "simple_shell.h"

/**
 * _strlen - function that returns the length of a string
 * @s: the string length to check
 * Return: length of string
 */

int _strlen(char *s)
{
	int num = 0;

	if (!s)
		return (0);

	while (*s++)
		num++;
	return (num);
}

/**
 * _strcmp - a function that performs lexicogarphic comparison of two strings.
 * @s1: first string
 * @s2: second string
 * Return: 1
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - function that checks if needle starts with haystack
 * @haystack: the string to search
 * @needle: substring to find
 * Return: address of next char of haystack
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);

	return ((char *)haystack);
}

/**
 * _strcat - a function that concatenates two strings
 * @dest: destination buffer
 * @src: source buffer
 * Return: len
 */

char *_strcat(char *dest, char *src)
{
	char *len = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (len);
}
