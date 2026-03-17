#pragma once

typedef struct InputBuffer InputBuffer;

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNISED_COMMAND,
} MetaCommandResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNISED_STATEMENT
} PrepareResult;

typedef enum {
    STATEMENT_SELECT,
    STATEMENT_INSERT,
} StatementType;

typedef struct Statement Statement; 


void close_input_buffer(InputBuffer*);
void read_input(InputBuffer*);
MetaCommandResult do_meta_command(InputBuffer*);
PrepareResult prepare_statement(InputBuffer*, Statement*);
void execute_statement(Statement*);

