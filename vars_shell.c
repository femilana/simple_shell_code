#include "simple_shell.h"

/**
 * is_chain - a function to test if current char in buffer is a chain delimeter
 * @info: parameter struct
 * @buf: char buffer
 * @p: the address of current position in buf
 * Return: 1 or 0
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t ptr = *p;

	if (buf[ptr] == '|' && buf[ptr + 1] == '|')
	{
		buf[ptr] = 0;
		ptr++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[ptr] == '&' && buf[ptr + 1] == '&')
	{
		buf[ptr] = 0;
		ptr++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[ptr] == ';')
	{
		buf[ptr] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*p = ptr;
	return (1);
}

/**
 * check_chain - funtion that checks we should
 * continue chaining based on last status
 * @info: parameter struct
 * @buf: char buffer
 * @p: the address of current position in buf
 * @i: the starting position in buf
 * @len: the length of buf
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t ptr = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			ptr = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			ptr = len;
		}
	}

	*p = ptr;
}

/**
 * replace_alias - the fuction that replaces an aliases in the tokenized string
 * @info: parameter struct
 * Return: 1 or 0
 */

int replace_alias(info_t *info)
{
	int num;
	list_t *node;
	char *ptr;

	for (num = 0; num < 10; num++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * replace_vars - a function that replaces vars in the tokenized string
 * @info: parameter struct
 * Return: 1 or 0
 */

int replace_vars(info_t *info)
{
	int num = 0;
	list_t *node;

	for (num = 0; info->argv[num]; num++)
	{
		if (info->argv[num][0] != '$' || !info->argv[num][1])
			continue;

		if (!_strcmp(info->argv[num], "$?"))
		{
			replace_string(&(info->argv[num]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[num], "$$"))
		{
			replace_string(&(info->argv[num]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[num][1], '=');
		if (node)
		{
			replace_string(&(info->argv[num]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[num], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - a function that replaces string
 * @old: the address of old string
 * @new: the new string
 * Return: 1 or 0
 */

int replace_string(char **old, char *new)
{
	free(*old);

	*old = new;

	return (1);
}
