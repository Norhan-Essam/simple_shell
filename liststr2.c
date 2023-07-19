#include "shell.h"

/**
 * list_len - determines length of linked list
 * @d: pointer to first node
 *
 * Return: size of list
*/
size_t list_len(const list_t *d)
{
	size_t e = 0;

	while (d)
	{
		d = d->next;
		e++;
	}
	return (e);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
*/
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t e = list_len(head), g;
	char **str;
	char *str;

	if (!head || !e)
		return (NULL);
	strs = malloc(sizeof(char *) * (e + 1));
	if (!strs)
		return (NULL);
	for (e = 0; node; node = node->next, e++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (g = 0; g < e; g++)
				free(strs[g]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[e] = str;
	}
	strs[e] = NULL;
	return (strs);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @d: pointer to first node
 *
 * Return: size of list
*/
size_t print_list(const list_t *d)
{
	size_t e = 0;

	while (d)
	{
		_puts(convert_number(d->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(d->str ? d->str : "(nil)");
		_puts("\n");
		d = d->next;
		e++;
	}
	return (e);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @u: the next character after prefix to match
 *
 * Return: match node or null
*/
list_t *node_starts_with(list_t *node, char *prefix, char u)
{
	char *f = NULL;

	while (node)
	{
		f = starts_with(node->str, prefix);
		if (f && ((u == -1) || (*f == u)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t e = 0;

	while (head)
	{
		if (head == node)
			return (e);
		head = head->next;
		e++;
	}
	return (-1);
}
