#include "simple_shell.h"

/**
 **_memset - a function that fills memory with a constant byte
 *@s: pointer to the memory area
 *@b: byte to fill *s with
 *@n: amount of bytes to be filled
 *Return: s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int num;

	for (num = 0; num < n; num++)
		s[num] = b;
	return (s);
}

/**
 * ffree - a function that frees a string of strings
 * @pp: string to be free
 */

void ffree(char **pp)
{
	char **ptr = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(ptr);
}

/**
 * _realloc - a function that reallocates a block of memory
 * @ptr: a pointer to previous malloc'ated block
 * @old_size: the byte size of previous block
 * @new_size: the byte size of new block
 * Return: pointer.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pt;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pt = malloc(new_size);
	if (!pt)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pt[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pt);
}
