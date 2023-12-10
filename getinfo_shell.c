#include "simple_shell.h"

/**
 * clear_info - a function that initializes info_t struct
 * @info: the struct
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->path = NULL;
	info->argv = NULL;
	info->argc = 0;
}

/**
 * set_info - a function that initializes info_t struct
 * @info: struct
 * @av: argument vec
 */

void set_info(info_t *info, char **av)
{
	int num;

	num = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (num = 0; info->argv && info->argv[num]; num++)
			;
		info->argc = num;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - a function that frees info_t struct fields
 * @info: struct
 * @all: all
 */

void free_info(info_t *info, int all)
{
	info->argv = NULL;
	info->path = NULL;
	ffree(info->argv);
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
