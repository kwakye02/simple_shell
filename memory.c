#include "main.h"

/**
 * bfree - Release the memory of a pointer and set it to NULL.
 * @address: The address of the pointer to be released.
 *
 * Return: 1 if successfully freed, 0 otherwise.
 */
int bfree(void **address)
{
	if (address && *address)
	{
		free(*address);
		*address = NULL;
		return (1);
	}
	return (0);
}

/**
 * _memset - Set a specific memory area with a given byte.
 * @mem: The memory area pointer.
 * @byte: The byte to set in the memory area.
 * @count: The number of bytes to set.
 * Return: Pointer to the memory area.
 */
char *_memset(char *mem, char byte, unsigned int count)
{
	unsigned int iterator;

	for (iterator = 0; iterator < count; iterator++)
		mem[iterator] = byte;
	return (mem);
}

/**
 * ffree - Release a set of strings from memory.
 * @str_set: Set of strings.
 */
void ffree(char **str_set)
{
	char **temp = str_set;

	if (!str_set)
		return;
	while (*str_set)
		free(*str_set++);
	free(temp);
}

/**
 * _realloc - Adjust a memory block to a new size.
 * @mem: Pointer to the original memory block.
 * @prev_size: Size of the original memory block.
 * @updated_size: Size of the new memory block.
 *
 * Return: Pointer to the adjusted memory block.
 */
void *_realloc(void *mem, unsigned int prev_size, unsigned int updated_size)
{
	char *new_mem;

	if (!mem)
		return (malloc(updated_size));
	if (!updated_size)
		return (free(mem), NULL);
	if (updated_size == prev_size)
		return (mem);

	new_mem = malloc(updated_size);
	if (!new_mem)
		return (NULL);

	prev_size = prev_size < updated_size ? prev_size : updated_size;
	while (prev_size--)
		new_mem[prev_size] = ((char *)mem)[prev_size];
	free(mem);
	return (new_mem);
}

