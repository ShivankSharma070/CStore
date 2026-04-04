#include "vm.h"
#include "storage.h"
#include <stdlib.h>

ExecuteResult execute_insert(Statement_t* statement, Table_t* table){
    if(table->num_rows >= TABLE_MAX_ROW) {
        return EXECUTE_TABLE_FULL;
    }

    Row_t* row_to_insert = &(statement->row_to_insert);
    Cursor_t* cursor = table_end(table);
    serialize_row(row_to_insert,cursor_value(cursor));
    table->num_rows+=1;

    free(cursor);

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement_t* statement, Table_t* table){
    Cursor_t* cursor = table_start(table);
    Row_t row;
    while(!cursor->end_of_table) {
        deserialize_row(cursor_value(cursor), &row);
        print_row(&row);
        cursor_advance(cursor);
    }

    free(cursor);
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement_t* statement, Table_t* table) {
    switch(statement->type) {
        case STATEMENT_INSERT: 
            return execute_insert(statement ,table);
        case STATEMENT_SELECT: 
            return execute_select(statement ,table);
        default: 
            return EXECUTE_FAILURE;
    }
}
