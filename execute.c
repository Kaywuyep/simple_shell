#include "shell.h"

/**
 * execute - A function that executes a command.
 * @command: The pointer to tokienized command
 * @name: The name of the shell.
 * @env: The pointer to the enviromental variables.
 * @cicles: Number of executed cicles.
 * Return: Nothing.
 */
void execute(char **command, char *name, char **env, int cicles)
{
	struct stat st;

	(void)name, (void)cicles;

	if (_strcmp(command[0], "env") != 0)
		print_env(env);
	if (command[0][0] == '/' || command[0][0] == '.')
	{
		if (stat(command[0], &st) == 0)
		{
			if (execve(command[0], command, env) < 0)
			{
				perror(name);  /*Print permission-related error*/
				free_exit(command);
			}
		}
		else
		{
			perror(name);  /*Print other errors*/
			free_exit(command);
		}
	}
	else
	{
		findAndExecuteCommand(env, command, name, cicles);
	}
}


/**
 * findAndExecuteCommand - Find and execute a command
 * in the given environment paths.
 *
 * This function searches for a command in the directories specified in the
 * environment paths and executes it if found.
 *
 * @env: The environment variables.
 * @command: The command to be executed.
 * @name: the program name
 * @cicles: number of times it circles to find a command
 */
void findAndExecuteCommand(char **env, char **command, char *name, int cicles)
{
	char **pathways;
	int i = 0;
	struct stat st;
	char *full_path = NULL;

	pathways = _getPATH(env, command);
	while (pathways[i])
	{
		full_path = _strcat(pathways[i], "/");
		full_path = _strcat(full_path, command[0]); /* Create full path */
		i++;

		if (stat(full_path, &st) == 0)
		{
			if (execve(full_path, command, env) < 0)
			{
				perror(name); /* Print permission-related error */
				free_dp(pathways);
				free_exit(command);
			}
			return;
		}
	}

	msgerror(name, cicles, command);
	free_dp(pathways);
}

/**
 * print_env - A function that prints all enviromental variables.
 * @env: The pointer to enviromental variables.
 * Return: Nothing.
 */
void print_env(char **env)
{
	size_t i = 0, len = 0;

	while (env[i])
	{
		len = _strlen(env[i]);
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
/**
 * getpid -  a function that gets the process id
 * Return: process id
 */
pid_t getpid(void)
{
	pid_t pid = getpid();

	return (pid);
}

/**
 * _getPATH - A function to gets the full value from.
 * enviromental variable PATH.
 * @env: The pointer to enviromental variables.
 * @command: user input.
 * Return: All tokenized pathways for commands.
 */
char **_getPATH(char **env, char **command)
{
	char *pathvalue = NULL, **pathways = NULL;
	unsigned int i = 0;
	int len;

	pid_t pid = 1;/*get process id*/

	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			pathvalue = env[i] + 5;

			/*Check if PATH is empty*/
			if (pathvalue[0] == '\0')
			{
				_fprintf(stderr, "./hsh: %d: %s: not found\n", pid, command[0]);
				exit(127);
			}

			/*Remove leading and trailing colons if present*/
			while (pathvalue[0] == ':')
				pathvalue++;

			len = _strlen(pathvalue);
			while (len > 0 && pathvalue[len - 1] == ':')
			{
				pathvalue[len - 1] = '\0';
				len--;
			}

			/*Tokenize the cleaned PATH*/
			pathways = tokening(pathvalue, ":");
			return (pathways);
		}
		i++;
	}

	/*Handle the case where PATH is not found or is empty*/
	_fprintf(stderr, "./hsh: %d: %s: not found\n", pid, command[0]);
	exit(127);
}
