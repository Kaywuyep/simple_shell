#include "shell.h"
/**
 * is_delim - Helper function to check if a character is a delimiter
 * @c: character value
 * @delim: delimiter
 * Return: delim
 */
int is_delim(char c, const char *delim)
{
	return (strchr(delim, c) != NULL);
}
/**
 * find_token -Helper function to find the next non-delimiter character
 * @str: string to be used
 * @delim: delimiters
 * Return: string
 */
char *find_token(char *str, const char *delim)
{
	while (*str && is_delim(*str, delim))
	{
		str++;
	}
	return (str);
}
/**
 * _strtok - a custom strtok function
 * @str: the string to be parse
 * @delim: specifies a set of bytes that delimit the
 * tokens in the parsed string
 * Return: start token
 */
char *_strtok(char *str, const char *delim)
{
	static char *end; /*Stores the last position*/
	char *start;

	if (str)
	{
		end = str;
	}
	else
	{
		if (!end)
		{
			return (NULL); /*No more tokens left*/
		}
		str = end;
	}
	str = find_token(str, delim);

	if (*str == '\0')
	{
		end = NULL;
		return (NULL); /*No more tokens left*/
	}
	start = str;
	while (*str && !is_delim(*str, delim))
	{
		str++;
	}

	if (*str)
	{
		*str = '\0';
		end = str + 1;
	}
	else
	{
		end = NULL;
	}
	return (start);
}
