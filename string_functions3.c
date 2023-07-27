#include "shell.h"

/**
 **_strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @m: the amount of characters to be copied
 * Return: the concatenated string
*/
char *_strncpy(char *dest, char *src, int m)
{
	int e, k;
	char *z = dest;

	e = 0;
	while (src[e] != '\0' && e < m - 1)
	{
		dest[e] = src[e];
		e++;
	}
	if (e < m)
	{
		k = e;
		while (k < m)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (z);
}

/**
 **_strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @m: the amount of bytes to be maximally used
 * Return: the concatenated string
*/
char *_strncat(char *dest, char *src, int m)
{
	int e, k;
	char *z = dest;

	e = 0;
	k = 0;
	while (dest[e] != '\0')
		e++;
	while (src[k] != '\0' && k < m)
	{
		dest[e] = src[k];
		e++;
		k++;
	}
	if (k < m)
		dest[e] = '\0';
	return (z);
}

/**
 **_strchr - locates a character in a string
 * @z: the string to be parsed
 * @g: the character to look for
 * Return: (z) a pointer to the memory area z
*/
char *_strchr(char *z, char g)
{
	do {
		if (*z == g)
			return (z);
	} while (*z++ != '\0');

	return (NULL);
}
