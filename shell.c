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
		token = strtok(line, " ");

		if (strcmp(line, "exit") == 0)
		{
			printf("Exiting shell!!!");
			exit(0);
        	}

		int status;
		char *args[2] = {token, NULL};
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
			execve(line, args, NULL);
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
