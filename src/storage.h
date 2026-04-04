#pragma once
#include <stdint.h>
#include <stdbool.h>

// (Struct*)0 -> is a null pointer
#define size_of_attribute(Struct,attribute)  sizeof(((Struct*)0)->attribute) 
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
#define TABLE_MAX_PAGE 100

typedef struct Row {
    uint32_t id;    
    char username[COLUMN_USERNAME_SIZE+1];
    char email[COLUMN_EMAIL_SIZE+1];
} Row_t;

typedef struct Pager {
    int file_discriptor;
    uint32_t file_length;
    void* pages[TABLE_MAX_PAGE];
} Pager_t;

typedef struct Table {
    uint32_t num_rows;
    Pager_t* pager;
} Table_t;

typedef struct Cursor {
    Table_t* table;
    uint32_t row_num;
    bool end_of_table;
} Cursor_t;

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
void serialize_row(Row_t* source, void* destination); 
void deserialize_row(void* source, Row_t* destination);

void print_row(Row_t* row);

/*
 * cursor_value returns a 'void*' to the start of row where cursor is currently at.
*/
void* cursor_value(Cursor_t* cursor);

/* 
 * cursor_advance increments the row the cursor points to
*/
void cursor_advance(Cursor_t* cursor);
Pager_t* pager_open(const char* filename);
void pager_flush(Pager_t* pager, uint32_t page_num, uint32_t size);
Table_t* db_open(const char*); 
void db_close(Table_t*);


/*
* table_end creates and returns a new 'Cursor' object pointing to the first row of the table
*/
Cursor_t* table_start(Table_t* table);

/*
* table_end creates and returns a new 'Cursor' object pointing to the last row of the table
*/
Cursor_t* table_end(Table_t* table);
