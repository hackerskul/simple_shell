#include "main.h"

/**
 * main - main function
 * read_line - gets user input
 * status: exit status
 * pid: child_process
 * args: command arguments
 * Return: return value
 */

int main(void)
{
	while (1)
	{
		printf("$Shell> ");
		fflush(stdout);

		read_line();

		char *token = strtok(line, " ");

		int status;
		char *args[] = {token, NULL};
		pid_t pid;

		pid = fork();

		if (pid == -1)
		{
			printf("Error creating process");
			free(line);
			exit(48);
		}
		if (pid == 0)
		{
			execve(token, args, NULL);
			perror("");
			free(line);
			exit(42);
		}
		else
		{
			wait(&status);
		}

	}
}
