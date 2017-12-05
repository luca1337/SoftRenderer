#include "../include/databuffer.h"

data_buffer_f_t* data_buffer_float_new(DWORD dwSize)
{
    data_buffer_f_t* buffer = calloc(sizeof(data_buffer_f_t));

    if(!buffer)
    {
        fprintf(sterr, "error, couldn't alloate memory for buffer");
        return ((void*)0);
    }

    if(dwSize)
    {
        buffer->size = dwSize;
        buffer->element = calloc(sizeof(float) * buffer->size);

        if(!buffer->element)
        {
            fprintf(stderr, "error, couldn't allocate memory for dataBuffer");
            free(buffer);
            return ((void*)0);
        }
    }

    return buffer
}