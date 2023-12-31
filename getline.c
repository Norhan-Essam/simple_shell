#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
*/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t w = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		w = getline(buf, &len_p, stdin);
#else
		w = _getline(info, buf, &len_p);
#endif
		if (w > 0)
		{
			if ((*buf)[w - 1] == '\n')
			{
				(*buf)[w - 1] = '\0'; /* remove trailing newline */
				w--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = w;
				info->cmd_buf = buf;
			}
		}
	}
	return (w);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
*/
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t e, k, len;
	ssize_t w = 0;
	char **buf_p = &(info->arg), *q;

	_putchar(BUF_FLUSH);
	w = input_buf(info, &buf, &len);
	if (w == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		k = e; /* init new iterator to current buf position */
		q = buf + e;  /* get pointer for return */

		check_chain(info, buf, &k, e, len);
		while (k < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &k))
				break;
			k++;
		}

		e = k + 1; /* increment past nulled ';'' */
		if (e >= len) /* reached end of buffer? */
		{
			e = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = q; /* pass back pointer to current command position */
		return (_strlen(q)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from_getline() */
	return (w); /* return length of buffer from_getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @e: size
 *
 * Return: n
*/
ssize_t read_buf(info_t *info, char *buf, size_t *e)
{
	ssize_t n = 0;

	if (*e)
		return (0);
	n =  read(info->readfd, buf, READ_BUF_SIZE);
	if (n >= 0)
		*e = n;
	return (n);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: addresss of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: z
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t e, len;
	size_t t;
	ssize_t w = 0, z = 0;
	char *q = NULL, *new_p = NULL, *u;

	q = *ptr;
	if (q && length)
		z = *length;
	if (e == len)
		e = len = 0;

	w = read_buf(info, buf, &len);
	if (w == -1 || (w == 0 && len == 0))
		return (-1);

	u = _strchr(buf + e, '\n');
	t = u ? 1 + (unsigned int)(u - buf) : len;
	new_p = _realloc(q, z, z ? z + t : t + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (q ? free(q), -1 : 1);

	if (z)
		_strncat(new_p, buf + e, t - e);
	else
		_strncpy(new_p, buf + e, t - e + 1);

	z += t - e;
	e = t;
	q = new_p;

	if (length)
		*length = z;
	*ptr = q;
	return (z);
}

/**
 * sigintHandler - blocks ctrl-c
 * @sig_num: the signal number
 *
 * Return: void
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
