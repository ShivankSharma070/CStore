#pragma once
#include "storage.h"
#include <stddef.h>
#include <stdint.h>

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNISED_COMMAND,
} MetaCommandResult;

typedef struct InputBuffer {
    char* buffer;
    size_t buffer_lenght;
    size_t input_lenght; 
} InputBuffer_t;

InputBuffer_t* new_input_buffer(); 
void close_input_buffer(InputBuffer_t*);
void read_input(InputBuffer_t*);
MetaCommandResult do_meta_command(InputBuffer_t*, Table_t*);
void startREPL(int, Table_t* );
