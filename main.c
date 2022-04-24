#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


//Param 1: /bin/ls/


int execute(char** command) {
    int rc_wait;
    //fork the shell, creating a subprocess for the command that will be run
    int rc = fork();
    //Dynamically allocation memory for the path
    char* PATH = (char*)malloc(sizeof(char*) * 5 + sizeof(char*) * strlen(command[0]));
    strcpy(PATH, "/bin/");
    strcat(PATH, command[0]);
    if (rc < 0) {
        //the case where the fork fails
        fprintf(stderr, "Fork failed.\n");
    } else if (rc == 0) {
        //the path the child process will head to
        //Checking whether the command is able to be executed
        if (access(PATH, X_OK) == 0) {
            execv(PATH, command);
        } else {
            //TODO /usr/bin
            if (access(PATH, X_OK) == 0) {
                execv(PATH, command);

            } else {
                fprintf(stderr, "Unknown command.");
            }
        }
    } else {
        //the path the parent (shell) heads to, during the fork
        rc_wait = wait(NULL);
    }
    free(PATH); //free the memory allocated at the beginning
    return 1;
}

int parseCommand(char* line) {
    int i = 0, status = 1;
    char* token = NULL;
    char* delim = " ";
    char** command = (char**)malloc(strlen(line) * sizeof(char*));
    //Splitting the command to words by space and adding to the list
    while ((token = strtok_r(line, delim, &line)) != NULL) {
        command[i] = strdup(token);
        i++;
    }
    command[i + 1] = NULL;
    status = execute(command);
    for (int j = 0; j < i + 1; j++) {
        free(command[j]);
    }
    free(command);
    if (status == 0)
        return 0;
    return 1;
}

void listen() {
    int status = 1;
    size_t length = 0;
    char* line = NULL;
    //Printing the shell prompt
    printf("wish> ");
    while (getline(&line, &length, stdin) != -1) {
        //Excluding the newline character from the line
        line[strlen(line) - 1] = '\0';
        status = parseCommand(line);
        if (status == 0)
            break;
        printf("\nwish> ");

    }
    free(line);
    return;
}

int main(int argc, char** argv) {
    listen();
    return 0;
}