#include "parser.h"
#include <string.h>
#include <stdio.h>


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
