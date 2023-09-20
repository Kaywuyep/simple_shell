#include "shell.h"
/**
 * _strncmp - compares two strings up to specified number of cases
 * @s1: ...
 * @s2: ....
 * @n: ....
 * Return: ...
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (*s1 - *s2);
}
