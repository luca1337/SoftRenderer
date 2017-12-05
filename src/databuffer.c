#include "../include/databuffer.h"
#include <windows.h>
#include <stdio.h>

data_buffer_f_t* data_buffer_new_f(size_t dwSize)
{
    data_buffer_f_t* buffer = malloc(sizeof(data_buffer_f_t));

    if(!buffer)
    {
        fprintf(stderr, "error, couldn't alloate memory for buffer");
        return ((void*)0);
    }

    memset(buffer, 0, sizeof(data_buffer_f_t));

    if(dwSize)
    {
        buffer->size = dwSize;
        buffer->element = malloc(sizeof(float) * buffer->size);

        if(!buffer->element)
        {
            fprintf(stderr, "error, couldn't allocate memory for dataBuffer");
            free(buffer);
            return ((void*)0);
        }

        memset(buffer->element, 0, sizeof(float) * buffer->size);
    }
    return buffer;
}

data_buffer_i_t* data_buffer_new_i(size_t dwSize)
{
    data_buffer_i_t* buffer = malloc(sizeof(data_buffer_i_t));

    if(!buffer)
    {
        fprintf(stderr, "error, couldn't alloate memory for buffer");
        return ((void*)0);
    }

    memset(buffer, 0, sizeof(data_buffer_i_t));

    if(dwSize)
    {
        buffer->size = dwSize;
        buffer->element = malloc(sizeof(int32_t) * buffer->size);

        if(!buffer->element)
        {
            fprintf(stderr, "error, couldn't allocate memory for dataBuffer");
            free(buffer);
            return ((void*)0);
        }
        memset(buffer->element, 0, sizeof(int32_t) * buffer->size);
    }
    return buffer;
}

void data_buffer_destroy_f(data_buffer_f_t* buffer)
{
    if(buffer->element) free(buffer->element);
    free(buffer);
}

void data_buffer_destroy_i(data_buffer_i_t* buffer)
{
    if(buffer->element) free(buffer->element);
    free(buffer);
}

int data_buffer_add_element_f(data_buffer_f_t* buffer, float value)
{
    if(buffer->size == 0)
    {
        buffer->size = 4;
        buffer->element = malloc(sizeof(float) * buffer->size);

        if (!buffer->element)
        {
            return -1;
        }

        memset(buffer->element, 0, sizeof(float) * buffer->size);
    }
    else if(buffer->count == buffer->size)
    {
        uint64_t old_size = buffer->size;
        buffer->size *= 4;
        float *new_data = realloc(buffer->element, sizeof(float) * buffer->size);
        if (!new_data)
        {
            return -1;
        }
        buffer->element = new_data;
        uint64_t remains = (sizeof(float) * buffer->size) - (sizeof(float) * old_size);
        memset(buffer->element + old_size, 0, remains);
    }

    buffer->element[buffer->count++] = value;
    return 0;
}

int data_buffer_add_element_i(data_buffer_i_t* buffer, int32_t value)
{
    
    if(buffer->size == 0)
    {
        buffer->size = 4;
        buffer->element = malloc(sizeof(int32_t) * buffer->size);
        if (!buffer->element)
        {
            return -1;
        }
        memset(buffer->element, 0, sizeof(int32_t) * buffer->size);
    }
    
    
    else if(buffer->count == buffer->size)
    {
        fprintf(stdout, "asdsd\n");
        uint64_t old_size = buffer->size;
        buffer->size *= 4;
        int32_t *new_data = realloc(buffer->element, sizeof(int32_t) * buffer->size);
        if (!new_data)
        {
            return -1;
        }
        buffer->element = new_data;
        uint64_t remains = (sizeof(int32_t) * buffer->size) - (sizeof(int32_t) * old_size);
        memset(buffer->element + old_size, 0, remains);

    }

    buffer->element[buffer->count++] = value;
    return 0;
}