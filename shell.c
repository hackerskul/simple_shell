#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

extern char **environ;

void handleExitCommand() {
    printf("Exiting shell!!!\n");
    exit(0);
}

void handleEnvCommand() {
    char **env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
}

int main(void) {
    char *line = NULL;
    size_t line_length = 0;

    while (1) {
	char *token;
        printf("$Shell> ");
        fflush(stdout);

        if (getline(&line, &line_length, stdin) == -1) {
            perror("Error reading input");
            exit(1);
        }

        token = strtok(line, " \n");

        if (token == NULL) {
            continue;
        }

        if (strcmp(token, "exit") == 0) {
            handleExitCommand();
        } else if (strcmp(token, "env") == 0) {
            handleEnvCommand();
        } else {
            int status;
            char *args[MAX_INPUT_LENGTH];
            int arg_count = 0;
            pid_t pid;

            while (token != NULL) {
                args[arg_count] = token;
                token = strtok(NULL, " \n");
                arg_count++;
            }

            args[arg_count] = NULL;

            pid = fork();

            if (pid == -1) {
                perror("Error creating process");
                free(line);
                exit(48);
            }

            if (pid == 0) {
                /*Attempt to execute the command from the PATH*/
                execvp(args[0], args);

                /*If execvp fails, the command does not exist*/
                perror("Command not found");
                free(line);
                exit(42);
            } else {
                wait(&status);
            }
        }
    }

    free(line);
    return 0;
}

