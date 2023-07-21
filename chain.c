#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @q: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
*/
int is_chain(info_t *info,  char *buf, size_t *q)
{
	size_t k = *q;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = k;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @q: address of current position in buf
 * @e: starting position in buf
 * @len: length of buf
 *
 * Return: Void
*/
void check_chain(info_t *info, char *buf, size_t *q, size_t e, size_t len)
{
	size_t k = *q;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[e] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[e] = 0;
			k = len;
		}
	}

	*q = k;
}

/**
 * replace_alias - replaces an aliases in the tokensized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
*/
int replace_alias(info_t *info)
{
	int e;
	list_t *node;
	char *q;

	for (e = 0; e < 10; e++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		q = _strchr(node->str, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		info->argv[0] = q;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
*/
int replace_vars(info_t *info)
{
	int e = 0;
	list_t *node;

	for (e = 0; info->argv[e]; e++)
	{
		if (info->argv[e][0] != '$' || !info->argv[e][1])
			continue;

		if (!_strcmp(info->argv[e], "$?"))
		{
			replace_string(&(info->argv[e]),
					strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[e], "$$"))
		{
			replace_string(&(info->argv[e]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[e][1], '=');
		if (node)
		{
			replace_string(&(info->argv[e]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[e], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
*/
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return  (1);
}
