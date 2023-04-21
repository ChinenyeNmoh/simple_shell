#include "shell.h"

/**
 * list_len - deduce length of linked list
 * @h: first node pointer
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t count = 0;

	for (; h != NULL; h = h->next)
	{
		count++;
	}
	return (count);
}

/**
 * get_node_index - gets the index of a node
 * @head: list head pointer
 * @node: pointer to the node of interest
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i;

	for (i = 0; head != NULL; head = head->next, i++)
	{
		if (head == node)
		{
			return (i);
		}
	}
	return (-1);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: list head pointer
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
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
 * print_list - prints all elements of a list_t linked list
 * @h: first node pointer
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i;

	for (i = 0; h != NULL; h = h->next, i++)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: first node pointer
 *
 * Return: array of strings
 */

char **list_to_strings(list_t *head)
{
	size_t i = list_len(head), k;
	char **string;
	char *str;
	list_t *tmp = head;

	if (!head || !i)
		return (NULL);
	string = malloc(sizeof(char *) * (i + 1));
	if (!string)
		return (NULL);
	i = 0;
	while (tmp != NULL)
	{
		str = malloc(str_length(tmp->str) + 1);
		if (!str)
		{
			for (k = 0; k < i; k++)
				free(string[k]);
			free(string);
			return (NULL);
		}
		str = _strcpy(str, tmp->str);
		string[i] = str;
		tmp = tmp->next;
		i++;
	}
	string[i] = NULL;
	return (string);
}
