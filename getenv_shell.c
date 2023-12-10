#include "simple_shell.h"

/**
 * get_environ - a function that returns the string array copy of our environ
 * @info: Structure containing potential arguments
 * Return: 0
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - a function that remove an environment variable
 * @info: Structure containing potential arguments
 * Return: 1
 * @var: the string
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;

	size_t a;

	a = 0;

	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), a);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * _setenv - function that Initialize a new environment variable
 * @info: Strut containing potential arguments
 * @var: the string env
 * @value: the value
 *  Return: 0
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *ptr;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
