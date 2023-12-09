#include "simple_shell.h"

/**
 * _myenv - function that prints the current environment
 * @info: Struct conaining potential argument
 * Return: 0
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - function to gets the value of an environ variable
 * @info: Struct containing potential arguments
 * @name: the env var name
 * Return: value
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - function that Initialize a new environment variable,
 * or modify an existing one on ground
 * @info: Structure containing potential arguments
 *  Return: 0
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - a funcion that remove an environment variable
 * @info: Structure containing potential arguments
 *  Return: 0
 */

int _myunsetenv(info_t *info)
{
	int num;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (num = 1; num <= info->argc; num++)
		_unsetenv(info, info->argv[num]);

	return (0);
}

/**
 * populate_env_list - a function that populates env linked list
 * @info: Structure containing potential arguments
 * Return: 0
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t num;

	for (num = 0; environ[num]; num++)
		add_node_end(&node, environ[num], 0);
	info->env = node;
	return (0);
}
