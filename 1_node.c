#include "main.h"

/**
*list_len - computes the number of nodes in the list
*@h: reference to the initial node
*Return: the count of nodes
*/
size_t list_len(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}
	return (count);
}

/**
* list_to_strings - generates an array of strings from the list->str
* @head: reference to the initial node
* Return: the array of string representations
*/
char **list_to_strings(list_t *head)
{
	list_t *current_node = head;
	size_t total = list_len(head), index;
	char **array_of_strings;
	char *current_str;

	if (!head || !total)
		return (NULL);

	array_of_strings = malloc(sizeof(char *) * (total + 1));
	if (!array_of_strings)
		return (NULL);

	for (total = 0; current_node; current_node = current_node->next, total++)
	{
		current_str = malloc(_strlen(current_node->str) + 1);
		if (!current_str)
		{
			for (index = 0; index < total; index++)
				free(array_of_strings[index]);
			free(array_of_strings);
			return (NULL);
		}

		current_str = _strcpy(current_str, current_node->str);
		array_of_strings[total] = current_str;
	}
	array_of_strings[total] = NULL;
	return (array_of_strings);
}

/**
* print_list - displays every element in a list_t linked list
* @h: reference to the initial node
* Return: the count of nodes
*/
size_t print_list(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}
	return (count);
}

/**
* node_starts_with - identifies the nodes
* @node: reference to the list's beginning
* @prefix: string to be matched
* @c: succeeding character after prefix for matching
* Return: the node that matches or NULL
*/
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *match = NULL;

	while (node)
	{
		match = starts_with(node->str, prefix);
		if (match && ((c == -1) || (*match == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
* get_node_index - determines the position of a given node
* @head: reference to the list's beginning
* @node: reference to the specific node
* Return: position of the node or -1 if not found
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t position = 0;

	while (head)
	{
		if (head == node)
			return (position);
		head = head->next;
		position++;
	}
	return (-1);
}
