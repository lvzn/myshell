#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


//Param 1: /bin/ls/

//todo add /usr/bin/ to PATH

int execute(char** command) {
    int rc_wait;
    int rc = fork();
    char* PATH = (char*)malloc(sizeof(char*) * 5 + sizeof(char*) * strlen(command[0]));
    strcpy(PATH, "/bin/");
    strcat(PATH, command[0]);
    //strcat(dir, command[0]);
    if (rc < 0) {
        fprintf(stderr, "Fork failed.\n");
    } else if (rc == 0) {
        //child
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
        rc_wait = wait(NULL);
    }
    free(PATH);
    return 1;
}

int parseCommand(char* line) {
    int i = 0, status = 1;
    char* token = NULL;
    char* delim = " ";
    char** command = (char**)malloc(strlen(line) * sizeof(char*));
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
    printf("wish> ");
    while (getline(&line, &length, stdin) != -1) {
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
    if (argc == 2) {
        //todo batch mode
    } else {
        listen();
    }
    return 0;
}