#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH "/bin"

void execute(char** command) {
    //todo
}

void parseCommand(char* line) {
    int i = 0;
    char* token = NULL;
    char** command = (char**)malloc(sizeof(char));
    while ((token = strtok_r(line, " ", &line)) != NULL) {
        command[i] = strdup(token);
        i++;
    }
    execute(command);
}

void listen() {
    size_t length = 0;
    char* line = NULL;
    printf("wish> ");
    while (getline(&line, &length, stdin) != -1) {
        parseCommand(line);
        printf("wish> ");
    }
    free(line);
}

int main(int argc, char** argv) {
    if (argc == 2) {
        //todo batch mode
    } else {
        listen();
    }
}