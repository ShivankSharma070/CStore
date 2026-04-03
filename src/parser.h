#pragma once
#include "repl.h"

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_NEGATIVE_ID,
    PREPARE_STRING_TOO_LONG,
    PREPARE_UNRECOGNISED_STATEMENT
} PrepareResult;

typedef enum {
    STATEMENT_SELECT,
    STATEMENT_INSERT,
} StatementType;


typedef struct Statement {
    StatementType type;
    Row_t row_to_insert;
} Statement_t; 


PrepareResult prepare_insert(InputBuffer_t*, Statement_t*);
PrepareResult prepare_statement(InputBuffer_t*, Statement_t*);
