#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH "/bin"

int execute(char** command) {
    if (strcmp(command[0], "exit\n") == 0) {
        return 0;
    }
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
    status = execute(command);
    for (int j = 0; j < i; j++) {
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
        status = parseCommand(line);
        if (status == 0)
            break;
        printf("wish> ");
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