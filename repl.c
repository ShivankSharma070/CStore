#include "repl.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

const uint32_t ID_SIZE = size_of_attribute(Row_t, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row_t, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row_t, email);
const uint32_t ID_OFFSET = 0 ;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;
const uint32_t PAGE_SIZE = 4096; 
const uint32_t ROW_PER_PAGE = PAGE_SIZE/ ROW_SIZE;
const uint32_t TABLE_MAX_ROW = ROW_PER_PAGE * TABLE_MAX_PAGE;

void print_prompt() {
    printf("cstore > ");
}

void serialize_row(Row_t* source, void* destination){
    memcpy(destination+ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination+USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy(destination+EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void* source, Row_t* destination) {
    memcpy(&(destination->id),source+ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username),source+USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination->email),source+EMAIL_OFFSET, EMAIL_SIZE); 
}

void* row_slot(Table_t* table, uint32_t row_num) {
    uint32_t page_num = row_num / ROW_PER_PAGE;
    void* page =   table->pages[page_num];

    if(page==NULL) {
        // Alocate memory when needed
        page = table->pages[page_num] = malloc(PAGE_SIZE);
    }

    uint32_t row_offset = row_num % ROW_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;
    return page+byte_offset;
}

InputBuffer_t* new_input_buffer() {
    InputBuffer_t* inputBuffer = (InputBuffer_t*)malloc(sizeof(InputBuffer_t));
    inputBuffer->buffer = NULL;
    inputBuffer->buffer_lenght = 0;
    inputBuffer->input_lenght = 0;
    return inputBuffer;
}

void close_input_buffer(InputBuffer_t* inputBuffer){
    free(inputBuffer->buffer);
    free(inputBuffer);
}

void read_input(InputBuffer_t* inputBuffer) {
    int bytes_read = getline(&(inputBuffer->buffer), &(inputBuffer->buffer_lenght), stdin);

    if(bytes_read <= 0) {
        printf("Error Reading Input.\n");
        exit(EXIT_FAILURE);
    }

    // 1 less for the new line character
    inputBuffer->input_lenght = bytes_read-1;
    inputBuffer->buffer[bytes_read - 1] = 0;
}

MetaCommandResult do_meta_command(InputBuffer_t* inputBuffer) {
    if(strcmp(inputBuffer->buffer, ".exit")== 0 ) {
            exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNISED_COMMAND;
    }
}

PrepareResult  prepare_statement(InputBuffer_t* inputBuffer,Statement_t* statement) {
    if (strncmp(inputBuffer->buffer, "insert",6)== 0) {
        statement->type = STATEMENT_INSERT;
        int arg_assigned = sscanf(inputBuffer->buffer, "insert %d %s %s", &(statement->row_to_insert.id), statement->row_to_insert.username, statement->row_to_insert.email);
        if (arg_assigned < 3) {
            return PREPARE_SYNTAX_ERROR;
        }
        return PREPARE_SUCCESS;
    } else if (strncmp(inputBuffer->buffer, "select", 6)==0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    } else  {
        return PREPARE_UNRECOGNISED_STATEMENT;
    }
}

void execute_statement(Statement_t* statement) {
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
    InputBuffer_t* inputBuffer = new_input_buffer();
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

        Statement_t statement;
        switch(prepare_statement(inputBuffer, &statement)) {
            case PREPARE_SUCCESS : 
                break;
            case PREPARE_SYNTAX_ERROR: 
                continue;
            case PREPARE_UNRECOGNISED_STATEMENT : 
                printf("Unrecognised keyword at start of %s\n", inputBuffer->buffer);
                continue;
        }
        execute_statement(&statement);
        printf("Executed\n");
    }
}
