#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
 *status: var
 */

int status;
pid_t pid;
char *line = NULL;
size_t len;

int read_line(void)
{
	ssize_t read;
	read = getline(&line, &len, stdin);

	if (line == NULL)
		return ( -1);
	if (read == - 1)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(1);
		}
	}
	if (line[read - 1] == '\n')
	{
		line[read - 1] = '\0';
	}

	/*char *token = strtok(line, " ");*/

}

#endif
