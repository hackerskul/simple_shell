#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define MAX_CMD_LEN 128
#define MAX_ARGS 10

void parse_cmd(char* cmd, char** args) {
    int i = 0;
    args[i] = strtok(cmd, " ");
    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " ");
    }
}

int main() {
    char cmd[MAX_CMD_LEN];
    char* args[MAX_ARGS];
    char* path = getenv("PATH");
    int status;

    while (1) {
	pid_t pid;
        printf("$ ");
        fgets(cmd, MAX_CMD_LEN, stdin);
	if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
	{
		exit(0);
	}
        cmd[strlen(cmd) - 1] = '\0';

        if (strcmp(cmd, "exit") == 0) {
            exit(0);
        } else if (strcmp(cmd, "env") == 0) {
            printf("%s\n", path);
            continue;
        }

        parse_cmd(cmd, args);

        pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("Error");
            exit(1);
        } else if (pid > 0) {
            wait(&status);
        } else {
            perror("Error");
            exit(1);
        }
    }

    return 0;
}

