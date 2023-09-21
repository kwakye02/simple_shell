#include "main.h"
/**
*add_node - adds a node to a linked list
*@head_ptr: reference to the list's head
*@string: data to be added
*@i: index to be used
*Return: returns a pointer to a node
*/
list_t *add_node(list_t **head_ptr, const char *string, int i)
{
	list_t *new_node;

	if (!head_ptr)
		return (NULL);
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = i;
	if (string)
	{
		new_node->str = _strdup(string);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *head_ptr;
	*head_ptr = new_node;
	return (new_node);
}

/**
*add_node_end - adds node to the end of a list
*@head_ptr: reference to the list's head
*@string: data to be used
*@i: index to be used
*Return: pointer
*/
list_t *add_node_end(list_t **head_ptr, const char *string, int i)
{
	list_t *new_node, *current_node;

	if (!head_ptr)
		return (NULL);

	current_node = *head_ptr;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = i;
	if (string)
	{
		new_node->str = _strdup(string);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	else
		*head_ptr = new_node;
	return (new_node);
}

/**
*print_list_str - display string data from the linked list.
*@head: Starting node of the list.
*Return: Length of the list.
*/
size_t print_list_str(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
*delete_node_at_index - remove a node from the list at a specific index.
*@head_ptr: Reference to the head of the list.
*@i: Position to remove the node.
*Return: 1 for success, 0 for failure.
*/
int delete_node_at_index(list_t **head_ptr, unsigned int i)
{
	list_t *current_node, *previous_node;
	unsigned int count = 0;

	if (!head_ptr || !*head_ptr)
		return (0);

	if (!i)
	{
		current_node = *head_ptr;
		*head_ptr = (*head_ptr)->next;
		free(current_node->str);
		free(current_node);
		return (1);
	}
	current_node = *head_ptr;
	while (current_node)
	{
		if (count == i)
		{
			previous_node->next = current_node->next;
			free(current_node->str);
			free(current_node);
			return (1);
		}
		count++;
		previous_node = current_node;
		current_node = current_node->next;
	}
	return (0);
}

/**
 *free_list - Clear the linked list and free the memory.
 *@head_ref: Reference to the head of the list.
 *Return: void
 */
void free_list(list_t **head_ref)
{
	list_t *current_node, *temp_node;

	if (!head_ref || !*head_ref)
		return;
	current_node = *head_ref;
	while (current_node)
	{
		temp_node = current_node->next;
		free(current_node->str);
		free(current_node);
		current_node = temp_node;
	}
	*head_ref = NULL;
}

