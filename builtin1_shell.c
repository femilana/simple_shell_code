#include "simple_shell.h"

/**
 * myhistory - displays the history list
 * @info: Struct containing the potential arguments
 *  Return: 0
 */

int myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets an alias to string
 * @info: the parameter struct
 * @str: string alias
 * Return: 0
 */

int unset_alias(info_t *info, char *str)
{
	char *ptr;
	char c;
	int num;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	num = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*ptr = c;
	return (num);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: string alias
 * Return: Always 0 on success, 1 on error
 */

int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - function that print an alias string
 * @node: alias node
 * Return: 0 on success, 1 on error
 */

int print_alias(list_t *node)
{
	char *ptr = NULL;
	char *a = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (a = node->str; a <= ptr; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias -function that mimics the alias builtin
 * @info: Struct containing potential arguments.
 *  Return: 0
 */

int _myalias(info_t *info)
{
	int num = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (num = 1; info->argv[num]; num++)
	{
		p = _strchr(info->argv[num], '=');
		if (p)
			set_alias(info, info->argv[num]);
		else
			print_alias(node_starts_with(info->alias, info->argv[num], '='));
	}

	return (0);
}
