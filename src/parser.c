#include "parser.h"
#include "storage.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

PrepareResult prepare_insert(InputBuffer_t* inputBuffer, Statement_t* statement){
    statement->type = STATEMENT_INSERT;

    char* keyword = strtok(inputBuffer->buffer, " ");
    char* id_string = strtok(NULL, " ");
    char* username = strtok(NULL, " ");
    char* email = strtok(NULL, " ");

    if (id_string == NULL || username == NULL || email ==NULL) {
        return PREPARE_SYNTAX_ERROR;
    }

    int id = atoi(id_string);
    if (id < 0) {
       return PREPARE_NEGATIVE_ID;
    }

    if(strlen(username) > COLUMN_USERNAME_SIZE ) {
        return PREPARE_STRING_TOO_LONG;
    }
    if(strlen(email) > COLUMN_EMAIL_SIZE ) {
        return PREPARE_STRING_TOO_LONG;
    }

    statement->row_to_insert.id = id;
    strcpy(statement->row_to_insert.username, username);
    strcpy(statement->row_to_insert.email, email);
    return PREPARE_SUCCESS;
}

PrepareResult  prepare_statement(InputBuffer_t* inputBuffer,Statement_t* statement) {
    if (strncmp(inputBuffer->buffer, "insert",6)== 0) {
        return prepare_insert(inputBuffer, statement);
    } else if (strncmp(inputBuffer->buffer, "select", 6)==0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    } else  {
        return PREPARE_UNRECOGNISED_STATEMENT;
    }
}
