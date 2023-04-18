#include "shell.h"
/**
 * main - Entry point
 *
 * Description: a UNIX command line interpreter that mimics the shell.
 *
 * Return: Return 0 if successful.
*/
int main(void)
{
	char input[1024], *args[64];
	pid_t pid;
	int status, i = 0;

	setenv("PATH", "/bin:/usr/bin", 1); /* set path env variable */
	while (1) /* infinite loop promptimg the user for input */
	{
		printf("simple_shell>$ ");
		if (fgets(input, 1024, stdin) == NULL) /* read input using fgets function */
		{
			printf("\n");
			break;
		}
		args[i] = strtok(input, " \n"); /* strtok splits string int word arrays*/
		while (args[i] != NULL && i < 63)
		{
			i++;
			args[i] = strtok(NULL, " \n");
		}
		args[i] = NULL;
		if (args[0] == NULL) /* if first token is null prompts the user for input */
			continue;
		if (args[0] && strcmp(args[0], "exit") == 0) /* handles exit usage */
			break; /* exit the loop and terminate the shell */
		pid = fork();/* the program forks a new process using the fork system call.*/
		if (pid == -1)
		{
			perror(args[0]); /* handles errors */
			exit(EXIT_FAILURE);
		} else if (pid == 0)
		{
			execvp(args[0], args);/* executes the command using the execvp function */
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
		else
			waitpid(pid, &status, 0);
		i = 0;
	}
	return (0);
}
