#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
*/
char *_strcpy(char *dest, char *src)
{
	int e = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[e])
	{
		dest[e] = src[e];
		e++;
	}
	dest[e] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
*/
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
*/
void _puts(char *str)
{
	int e = 0;

	if (!str)
		return;
	while (str[e] != '\0')
	{
		_putchar(str[e]);
		e++;
	}
}

/**
 * _putchar - writes the character g to stdout
 * @g: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
*/
int _putchar(char g)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (g == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(1, buf, e);
		e = 0;
	}
	if (g != BUF_FLUSH)
		buf[e++] = g;
	return (1);
}
