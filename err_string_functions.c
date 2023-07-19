#include "shell.h"

/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
*/
void _eputs(char *str)
{
	int e = 0;

	if (!str)
		return;
	while (str[e] != '\0')
	{
		_eputchar(str[e]);
		e++;
	}
}

/**
 * _eputchar - writes the character u to stderr
 * @u: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
*/
int _eputchar(char u)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (u == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(2, buf, e);
		e = 0;
	}
	if (u != BUF_FLUSH)
		buf[e++] = u;
	return (1);
}

/**
 * _putfd - writes the character u to given fd
 * @u: The character to print
 * @fd: The filedescroptor to write to
 *
 * Return: On success 1.
*/
int _putfd(char u, int fd)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (u == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(fd, buf, e);
		e = 0;
	}
	if (u != BUF_FLUSH)
		buf[e++] = u;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 * Return: the number of chars put
*/
int _putsfd(char *str, int fd)
{
	int e = 0;

	if (!str)
		return (0);
	while (*str)
	{
		e += _putfd(*str++, fd);
	}
	return (e);
}
