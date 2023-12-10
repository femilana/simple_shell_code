#include "simple_shell.h"

/**
 * **strtow - a function that splits a string into words.
 * @str: input string
 * @d: delimeter string
 * Return: len
 */

char **strtow(char *str, char *d)
{
	int num = 0;
	int k, m, i, j;
	char **len;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			num++;

	if (num == 0)
		return (NULL);
	len = malloc((1 + num) * sizeof(char *));
	if (!len)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		len[j] = malloc((k + 1) * sizeof(char));
		if (!len[j])
		{
			for (k = 0; k < j; k++)
				free(len[k]);
			free(len);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			len[j][m] = str[i++];
		len[j][m] = 0;
	}
	len[j] = NULL;
	return (len);
}

/**
 * **strtow2 - a function that splits a string into words
 * @str: input string
 * @d: delimeter
 * Return: len
 */

char **strtow2(char *str, char d)
{
	int k, i, j, m;
	int num = 0;
	char **len;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			num++;
	if (num == 0)
		return (NULL);
	len = malloc((1 + num) * sizeof(char *));
	if (!len)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		len[j] = malloc((k + 1) * sizeof(char));
		if (!len[j])
		{
			for (k = 0; k < j; k++)
				free(len[k]);
			free(len);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			len[j][m] = str[i++];
		len[j][m] = 0;
	}
	len[j] = NULL;
	return (len);
}
