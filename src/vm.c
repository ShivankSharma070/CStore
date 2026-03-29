#include "vm.h"
#include "storage.h"

ExecuteResult execute_insert(Statement_t* statement, Table_t* table){
    if(table->num_rows > TABLE_MAX_ROW) {
        return EXECUTE_TABLE_FULL;
    }

    Row_t* row_to_insert = &(statement->row_to_insert);
    serialize_row(row_to_insert,row_slot(table, table->num_rows));
    table->num_rows+=1;

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement_t* statement, Table_t* table){
    Row_t row;
    for(uint32_t i = 0; i < table->num_rows; i++) {
        deserialize_row(row_slot(table, i), &row);
        print_row(&row);
    }
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
