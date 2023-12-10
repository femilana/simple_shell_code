#include "simple_shell.h"

/**
 * input_buf - a function that buffers chained commands
 * @info: the parameter struct
 * @buf: the address of buffer
 * @len: the address of len var
 * Return: byte
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;

	size_t lens;

	lens = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(buf, &lens, stdin);
#else
		s = _getline(info, buf, &lens);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0';
				s--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * get_input - a functio that gets a line minus the newline
 * @info: the parameter struct
 * Return: bytes
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *ptr;
	static size_t a, b, len;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		b = a;
		ptr = buf + a;

		check_chain(info, buf, &b, a, len);
		while (b < len)
		{
			if (is_chain(info, buf, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= len)
		{
			a = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = ptr;
		return (_strlen(ptr));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - a function that reads a buffer
 * @info: the parameter struct
 * @buf: the buffer
 * @i: the size
 * Return: len
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t len = 0;

	if (*i)
		return (0);
	len = read(info->readfd, buf, READ_BUF_SIZE);
	if (len >= 0)
		*i = len;
	return (len);
}

/**
 * _getline - a function that gets the next line of input from STDIN
 * @info: the parameter struct
 * @ptr: the address of pointer to buffer, preallocated or NULL
 * @length: the size of preallocated ptr buffer if not NULL
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t num;
	static size_t len;
	size_t k;
	ssize_t a = 0, b = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		b = *length;
	if (num == len)
		num = len = 0;

	a = read_buf(info, buf, &len);
	if (a == -1 || (a == 0 && len == 0))
		return (-1);

	c = _strchr(buf + num, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, b, b ? b + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (b)
		_strncat(new_p, buf + num, k - num);
	else
		_strncpy(new_p, buf + num, k - num + 1);

	b += k - num;
	num = k;
	p = new_p;

	if (length)
		*length = b;
	*ptr = p;
	return (b);
}

/**
 * sigintHandler - a function that blocks ctrl-C
 * @sig_num: signal number
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
