#ifndef _DATABUFFER_H
#define _DATABUFFER_H

#include <stdint.h>

typedef struct data_buffer_f
{
    float* element;
    int64_t count;
    int64_t size;
}data_buffer_f_t;

data_buffer_f_t* data_buffer_float_new(DWORD);
void data_buffer_float_destroy(data_buffer_f_t*);
int data_buffer_add_element(data_buffer_f_t*, float);

#endif //!_DATABUFFER_H