#include "shell.h"

/**
 * _fprintf - A custom function similar to fprintf
 * @stream: The output stream (e.g., stderr)
 * @format: The format string
 * @...: Variable number of arguments to be formatted and printed
 *
 * Description: This function mimics the behavior of fprintf by taking
 * a format string and a variable number of arguments and printing
 * the formatted output to the specified stream.
 */
void _fprintf(FILE *stream, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	vfprintf(stream, format, args);
	va_end(args);
}
/**
 * msgerror - A function that prints message not found.
 * @name: The name of the shell.
 * @cicles: Number of cicles.
 * @command: The pointer to tokenized command.
 * Return: Nothing.
 */
void msgerror(char *name, int cicles, char **command)
{
	char c;

	c = cicles + '0';
	write(STDOUT_FILENO, name, _strlen(name));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, &c, 1);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, command[0], _strlen(command[0]));
	write(STDOUT_FILENO, ": not found\n", 12);
}
