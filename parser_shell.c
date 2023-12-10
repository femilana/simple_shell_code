#include "simple_shell.h"

/**
 * is_cmd - a function that determines if a file is an executable command
 * @info: info struct
 * @path: the path to the file
 * Return: returns 1 if true, 0 otherwise
 */

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 * dup_chars - a function that duplicates characters
 * @pathstr: path string
 * @start: the starting index
 * @stop: the stopping index
 * Return: apointer to new buffer
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buf[b++] = pathstr[a];
	buf[b] = 0;
	return (buf);
}

/**
 * find_path - a function that finds this cmd in the PATH string
 * @info: info struct
 * @pathstr: path string
 * @cmd: cmd to find
 * Return: returns full path of cmd if found or NULL
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int num = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[num] || pathstr[num] == ':')
		{
			path = dup_chars(pathstr, curr_pos, num);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[num])
				break;
			curr_pos = num;
		}
		num++;
	}
	return (NULL);
}
