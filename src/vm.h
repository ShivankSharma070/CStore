#pragma once
#include "parser.h"

typedef enum {
    EXECUTE_TABLE_FULL,
    EXECUTE_SUCCESS,
    EXECUTE_FAILURE,
} ExecuteResult;

ExecuteResult execute_statement(Statement_t*, Table_t*);
