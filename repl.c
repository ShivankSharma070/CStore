#include "repl.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct InputBuffer {
    char* buffer;
    size_t buffer_lenght;
    ssize_t input_lenght;
} InputBuffer;

void print_prompt() {
    printf("cstore > ");
}

InputBuffer* new_input_buffer() {
    InputBuffer* inputBuffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    inputBuffer->buffer = NULL;
    inputBuffer->buffer_lenght = 0;
    inputBuffer->input_lenght = 0;
    return inputBuffer;
}

void close_input_buffer(InputBuffer* inputBuffer){
    free(inputBuffer->buffer);
    free(inputBuffer);
}

void read_input(InputBuffer* inputBuffer) {
    int bytes_read = getline(&(inputBuffer->buffer), &(inputBuffer->buffer_lenght), stdin);

    if(bytes_read <= 0) {
        printf("Error Reading Input.\n");
        exit(EXIT_FAILURE);
    }

    // 1 less for the new line character
    inputBuffer->input_lenght = bytes_read-1;
    inputBuffer->buffer[bytes_read - 1] = 0;
}

int main(int argc, char* argv[] ) {
    InputBuffer* inputBuffer = new_input_buffer();
    while(true) {
        print_prompt();
        read_input(inputBuffer);

        if(strcmp(inputBuffer->buffer,".exit") == 0) {
            close_input_buffer(inputBuffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command '%s'.\n", inputBuffer->buffer);
        }
    }
}
