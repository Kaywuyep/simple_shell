#include "shell.h"

/**
 * create_child - A function that creates a sub process.
 * @command: The pointer to tokenized command
 * @name: The pointer to the name of shell.
 * @env: The pointer to the enviromental variables.
 * @cicles: Number of executed cicles.
 * Return: Nothing.
 */
void create_child(char **command, char *name, char **env, int cicles)
{
	int pid = 0;
	int status = 0;
	int wait_error = 0;
	int exit_status;
	int exec_status;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
		free_exit(command);
	}
	else if (pid == 0)
	{
		exec_status = execute(command, name, env, cicles);
                exit(exec_status);
                /*free_dp(command);*/
	}
	else
	{
		wait_error = waitpid(pid, &status, 0);
		if (wait_error < 0)
		{
			free_exit(command);
		}
		else if (WIFEXITED(status))
		{
			/*Get the exit status of the child process*/
			exit_status = WEXITSTATUS(status);
			free_dp(command);

			if (exit_status != 0)
			{
				/*Child process returned a non-zero exit status*/
				exit(exit_status);
			}
		}
	}
}


