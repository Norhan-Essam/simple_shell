#include "shell.h"

/**
 * *_memset - fills memory with a constant byte
 * @z: the pointer to the memory area
 * @d: the byte to fill *z with
 * @m: the amount of bytes to be filled
 * Return: (z) a pointer to the memory area z
*/
char *_memset(char *z, char d, unsigned int m)
{
	unsigned int e;

	for (e = 0; e < m; e++)
		z[e] = d;
	return (z);
}

/**
 * free - frees a string of strings
 * @qq: string of strings
*/
void free(char **qq)
{
	char **x = qq;

	if (!qq)
		return;
	while (*qq)
		free(*qq++);
	free(x);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to pervious malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char q;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	q = malloc(new_size);
	if (!q)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		q[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (q);
}
