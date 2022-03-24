#include <stdio.h>
#include <stdlib.h>

void listen() {
    size_t length = 0;
    char* line = NULL;
    printf("wish> ");
    while (getline(&line, &length, stdin) != -1) {
        puts("works");
        printf("wish> ");
    }
    free(line);
}

int main(int argc, char** argv) {
    while (1) {
        listen();
    }

}