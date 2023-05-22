#include "shell.h"

/**
 * main - Entry point of the shell program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 * @envp: Array of environment variables
 * Return: Exit status of the shell program
 */
int main(int argc, char **argv, char **envp)
{
	char *command = NULL;
	char **command_args = NULL;
	int path_count = 0;
	int exit_status = 0;
	(void)argc;

	while (1)
	{
		command = getline_cmd();
		if (command)
		{
			path_count++;
			command_args = get_token(command);
			if (!command_args)
			{
				free(command);
				continue;
			}

			if (!strcmp(command_args[0], "exit") && command_args[1] == NULL)
				ext_func(command_args, command, exit_status);
			else if (!strcmp(command_args[0], "env"))
				get_envi(envp);
			else
			{
				int path_result = path_sepetator(&command_args[0], envp);
				exit_status = fork_func(command_args, argv, envp, command, path_count, path_result);
				if (path_result == 0)
					free(command_args[0]);
			}

			free(command_args);
		}
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(exit_status);
		}

		free(command);
	}

	return (exit_status);
}
