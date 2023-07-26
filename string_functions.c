#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @z: the string whose length to check
 *
 * Return: integer length of string
*/
int _strlen(char *z)
{
	int e = 0;

	if (!z)
		return (0);

	while (*z++)
		e++;
	return (e);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @z1: the first strang
 * @z2: the second strang
 *
 * Return: negative if z1 < z2, positive if z1 > z2, zero if z1 ==  z2
*/
int _strcmp(char *z1, char *z2)
{
	while (*z1 && *z2)
	{
		if (*z1 != *z2)
			return (*z1 - *z2);
		z1++;
		z2++;
	}
	if (*z1 == *z2)
		return (0);
	else
		return (*z1 < *z2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: adderess of next char of haystack or NULL
*/
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _stract - concatenates two strings
 * @dest: the destiation buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
*/
char *_stract(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
