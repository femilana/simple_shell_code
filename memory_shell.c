#include "simple_shell.h"

/**
 * bfree - function that frees a pointer and NULLs the address
 * @ptr: the address of the pointer to free
 * Return: return 1 if freed, otherwise 0.
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
