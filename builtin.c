#include "shell.h"

/**
 * builtin_env - A function that prints all environmental variables.
 * @env: The pointer to environmental variables.
 */
void builtin_env(char **env)
{
	size_t i = 0;

	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}


/**
 * shell_command - Execute a shell command
 * @buffer: The input command buffer
 * @av: The command-line arguments
 * @env: The environment variables
 * @cicles: Number of cycles (or any relevant parameter)
 *
 * This function tokenizes and executes a shell command based
 * on the input buffer.i
 */
void shell_command(char *buffer, char **av, char **env, int cicles)
{
	char **command = NULL;

	/*Remove the trailing newline character*/
	buffer[_strlen(buffer) - 1] = '\0';

	/*Tokenize the input buffer*/
	command = tokening(buffer, " \0");

	/*Free the dynamically allocated buffer*/
	free(buffer);

	if (command && command[0])
	{
		if (_strcmp(command[0], "exit") != 0)
			shell_exit(command);
		else if (_strcmp(command[0], "cd") != 0)
			change_dir(command[1]);
		else if (_strcmp(command[0], "env") != 0)
			builtin_env(env);
		else
		{
			create_child(command, av[0], env, cicles);
		}
	}
	else
	{
		/*Handle the case where the command is invalid*/
		free_dp(command);
	}
}
