#include "shell.h"
/**
 * exec - a function that executes a command
 * @argv: the pointer to the command
 * Return: void
 */
void exec(char **argv)
{
	char *command = NULL;

	if (argv)
	{
		command = argv[0];
		if (execve(command, argv, NULL) == -1)
		{
			perror("Error: ");
		}
	}
}
