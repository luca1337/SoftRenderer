#ifndef _DATABUFFER_H
#define _DATABUFFER_H

#include <stdint.h>
#include <windows.h>

typedef struct data_buffer_f
{
    float* element;
    size_t count;
    size_t size;
}data_buffer_f_t;

typedef struct data_buffer_i
{
    int64_t* element;
    size_t count;
    size_t size;
}data_buffer_i_t;

data_buffer_f_t* data_buffer_new_f(size_t);
void data_buffer_destroy_f(data_buffer_f_t*);
int data_buffer_add_element_f(data_buffer_f_t*, float);

data_buffer_i_t* data_buffer_new_i(size_t);
void data_buffer_destroy_i(data_buffer_i_t*);
int data_buffer_add_element_i(data_buffer_i_t*, int32_t);

#endif //!_DATABUFFER_H