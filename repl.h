#pragma once
#include <stddef.h>
#include <stdint.h>

// (Struct*)0 -> is a null pointer
#define size_of_attribute(Struct,attribute)  sizeof(((Struct*)0)->attribute) 
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 256
#define TABLE_MAX_PAGE 100

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNISED_COMMAND,
} MetaCommandResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNISED_STATEMENT
} PrepareResult;

typedef enum {
    STATEMENT_SELECT,
    STATEMENT_INSERT,
} StatementType;

typedef enum {
    EXECUTE_TABLE_FULL,
    EXECUTE_SUCCESS,
} ExecuteResult;


typedef struct InputBuffer {
    char* buffer;
    size_t buffer_lenght;
    size_t input_lenght; 
} InputBuffer_t;

typedef struct Row {
    uint32_t id;    
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row_t;

typedef struct Statement {
    StatementType type;
    Row_t row_to_insert;
} Statement_t; 

typedef struct Table {
    uint32_t num_rows;
    void* pages[TABLE_MAX_PAGE];
} Table_t;

extern const uint32_t ID_SIZE;
extern const uint32_t USERNAME_SIZE;
extern const uint32_t EMAIL_SIZE;
extern const uint32_t ROW_SIZE;
extern const uint32_t ID_OFFSET;
extern const uint32_t USERNAME_OFFSET;
extern const uint32_t EMAIL_OFFSET;
extern const uint32_t PAGE_SIZE;
extern const uint32_t ROW_PER_PAGE;
extern const uint32_t TABLE_MAX_ROW;

void close_input_buffer(InputBuffer_t*);
void read_input(InputBuffer_t*);
MetaCommandResult do_meta_command(InputBuffer_t*, Table_t*);
PrepareResult prepare_statement(InputBuffer_t*, Statement_t*);
ExecuteResult execute_statement(Statement_t*, Table_t*);
void serialize_row(Row_t* source, void* destination); 
void deserialize_row(void* source, Row_t* destination);
void* row_slot(Table_t* table, uint32_t row_num);
