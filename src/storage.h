#pragma once
#include <stdint.h>

// (Struct*)0 -> is a null pointer
#define size_of_attribute(Struct,attribute)  sizeof(((Struct*)0)->attribute) 
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 256
#define TABLE_MAX_PAGE 100

typedef struct Row {
    uint32_t id;    
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row_t;

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
void print_row(Row_t* row); 
void serialize_row(Row_t* source, void* destination); 
void deserialize_row(void* source, Row_t* destination);
void* row_slot(Table_t* table, uint32_t row_num);
Table_t* new_table(); 
void free_table(Table_t* table);
