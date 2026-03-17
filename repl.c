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

typedef struct Statement {
    StatementType type;
} Statement;

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

MetaCommandResult do_meta_command(InputBuffer* inputBuffer) {
    if(strcmp(inputBuffer->buffer, ".exit")== 0 ) {
            exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNISED_COMMAND;
    }
}

PrepareResult  prepare_statement(InputBuffer* inputBuffer,Statement* statement) {
    if (strncmp(inputBuffer->buffer, "insert",6)== 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    } else if (strncmp(inputBuffer->buffer, "select", 6)==0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    } else  {
        return PREPARE_UNRECOGNISED_STATEMENT;
    }
}

void execute_statement(Statement* statement) {
    switch(statement->type) {
        case STATEMENT_INSERT: 
            printf("This is where we would do an insert.\n");
            break;
        case STATEMENT_SELECT: 
            printf("This is where we would do an select.\n");
            break;
    }
}

int main(int argc, char* argv[] ) {
    InputBuffer* inputBuffer = new_input_buffer();
    while(true) {
        print_prompt();
        read_input(inputBuffer);

        if(inputBuffer->buffer[0]=='.') {
            switch(do_meta_command(inputBuffer)) {
                case META_COMMAND_SUCCESS : 
                    continue;
                case META_COMMAND_UNRECOGNISED_COMMAND: 
                    printf("Unrecognised Command: %s\n ", inputBuffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch(prepare_statement(inputBuffer, &statement)) {
            case PREPARE_SUCCESS : 
                break;
            case PREPARE_UNRECOGNISED_STATEMENT : 
                printf("Unrecognised keyword at start of %s\n", inputBuffer->buffer);
                continue;
        }
        execute_statement(&statement);
        printf("Executed\n");
    }
}
