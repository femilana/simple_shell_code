#include "simple_shell.h"

/**
 * get_history_file - a function that gets the history file
 * @info: the parameter struct
 * Return: the allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buffer;
	char *directory;

	directory = _getenv(info, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - function that creates a file, or appends to an existing file
 * @info: parameter struct
 * Return: 1
 */

int write_history(info_t *info)
{
	char *filename = get_history_file(info);
	list_t *node = NULL;
	ssize_t fed;

	if (!filename)
		return (-1);

	fed = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fed == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fed);
		_putfd('\n', fed);
	}
	_putfd(BUF_FLUSH, fed);
	close(fed);
	return (1);
}

/**
 * read_history - a function that reads history from file
 * @info: parameter struct
 * Return: histcount on success
 */

int read_history(info_t *info)
{
	ssize_t fed, rdlen, fsize = 0;
	struct stat st;
	int num, last = 0, linecount = 0;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fed = open(filename, O_RDONLY);
	free(filename);
	if (fed == -1)
		return (0);
	if (!fstat(fed, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fed, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fed);
	for (num = 0; num < fsize; num++)
		if (buf[num] == '\n')
		{
			buf[num] = 0;
			build_history_list(info, buf + last, linecount++);
			last = num + 1;
		}
	if (last != num)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - a function that adds entry to a history linked list
 * @info: Structure containing potential arguments.
 * @buf: the buffer
 * @linecount: the history linecount
 * Return: 0
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * renumber_history - a function that renumbers
 * the history linked list after changes
 * @info: Structure containing potential arguments
 * Return: a new histcount
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int num = 0;

	while (node)
	{
		node->num = num++;
		node = node->next;
	}
	return (info->histcount = num);
}
