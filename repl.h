#pragma once

typedef struct InputBuffer InputBuffer;

InputBuffer* new_input_buffer();
void close_input_buffer(InputBuffer*);
void read_input(InputBuffer*);


