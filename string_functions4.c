#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @b: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
*/

char **strtow(char *str, char *b)
{
	int e, k, t, p, numwords = 0;
	char **z;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!b)
		b = " ";
	for (e = 0; str[e] != '\0'; e++)
		if (!is_delim(str[e], b) && (is_delim(str[e + 1], b) || !str[e + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	z = malloc((1 + numwords) * sizeof(char *));
	if (!z)
		return (NULL);
	for (e = 0, k = 0; k < numwords; k++)
	{
		while (is_delim(str[e], b))
			e++;
		t = 0;
		while (!is_delim(str[e + t], b) && str[e + t])
			t++;
		t = 0;
		z[k] = malloc((t + 1) * sizeof(char));
		if (!z[k])
		{
			for (t = 0; t < k; t++)
				free(z[t]);
			free(z);
			return (NULL);
		}
		for (p = 0; p < t; p++)
			z[k][p] = str[e++];
		z[k][p] = 0;
	}
	z[k] = NULL;
	return (z);
}

/**
 * **strtow2 - splits a string innto words
 * @str: the input string
 * @b: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
*/
char **strtow2(char *str, char b)
{
	int e, k, t, p, numwords = 0;
	char **z;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (e = 0; str[e] != '\0'; e++)
		if ((str[e] != b && str[e + 1] == b) ||
				(str[e] != b && !str[e + 1]) || str[e + 1] == b)
			numwords++;
	if (numwords == 0)
		return (NULL);
	z = malloc((1 + numwords) * sizeof(char *));
	if (!z)
		return (NULL);
	for (e = 0; k = 0; k < numwords; k++)
	{
		while (str[e] == b && str[e] != b)
			e++;
		t = 0;
		while (str[e + t] != b && str[e + t] && str[e + t] != b)
			t++;
		z[k] = malloc((t + 1) * sizeof(char));
		if (!z[k])
		{
			for (t = 0; t < k; t++)
				free(z[t]);
			free(z);
			return (NULL);
		}
		for (p = 0; p < t; p++)
			z[k][p] = str[e++];
		z[k][p] = 0;
	}
	z[k] = NULL;
	return (z);
}
