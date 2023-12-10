#include "simple_shell.h"

/**
 * list_len - a function that determines length of linked list
 * @h: the pointer to first node
 * Return: the size of list
 */

size_t list_len(const list_t *h)
{
	size_t len = 0;

	while (h)
	{
		h = h->next;
		len++;
	}
	return (len);
}

/**
 * list_to_strings - a function that returns an array
 * of strings of the list->str
 * @head: a pointer to first node
 * Return: the array of strings
 */

char **list_to_strings(list_t *head)
{
	char **strs;
	list_t *node = head;
	char *str;
	size_t a = list_len(head);
	size_t b;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * print_list - a function that prints all elements of a list_t linked list
 * @h: the pointer to first node
 * Return: size of list
 */

size_t print_list(const list_t *h)
{
	size_t len = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		len++;
	}
	return (len);
}

/**
 * node_starts_with - a function that returns node
 * whose string starts with prefix
 * @node: the pointer to list head
 * @prefix: the string to match
 * @c: next character after prefix to match
 * Return: match node
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - a function that gets the index of a node
 * @head: the pointer to list head
 * @node: the pointer to the node
 * Return: -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t len = 0;

	while (head)
	{
		if (head == node)
			return (len);
		head = head->next;
		len++;
	}
	return (-1);
}
