#include "../include/objparser.h"
#include "../include/list.h"
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS

list_t* parse_file_float(char* arg)
{
    int* err_code = malloc(sizeof(int));
    list_t* float_list = list_new(err_code);
    char* curr = arg;
    char* ptr = ((void*)0);
    float num = (float)strtof(curr, &ptr);
    float* insert = &num;
    list_append(float_list, (float*)insert);
    size_t len = list_len(float_list);
    char* line = malloc(sizeof(char) * strlen(arg) + 1);
    /*strcpy(line, arg);
    static int i = 0;
    for(char* token = strtok(line, "f"); token; token = strtok(NULL, "f"))
    {
        if(i++ > 0)
        {

        }
    }*/
    return float_list;
}

list_t* parse_file_split_str(char* _arg, size_t len, mesh_v3_t* v3)
{
    if(len < 2)
        return NULL;

    int* err_code = malloc(sizeof(int));
    list_t* str_list = list_new(err_code);
    data_t* mesh = malloc(sizeof(data_t));
    char* ptr = malloc(sizeof(char) * strlen(_arg) + 1);
    strcpy(ptr, _arg);
    if(ptr[0] == 'v' && ptr[1] == ' ')
    {
        mesh->num_v++;
        float val = strtof(_arg, &ptr);
        list_append(str_list, (float*)ptr);
        printf("%s\n", ptr);
        return str_list;
    }
    return NULL;
}

int parse_file_vec3(char* line, size_t len, mesh_v3_t* v3)
{
    // get pointers to struct members
	float *vfields[3];
	vfields[0] = (float *)((void *)v3 + offsetof(mesh_v3_t, x));
	vfields[1] = (float *)((void *)v3 + offsetof(mesh_v3_t, y));
	vfields[2] = (float *)((void *)v3 + offsetof(mesh_v3_t, z));

	size_t field_index = 0;

	// ptr always points to the current split-part
	char *ptr = line;
	for(size_t i=0;i<len;i++)
	{
		if (isspace(line[i]) || i + 1 == len)
		{
			// strtof will set errno accordingly
			errno = 0;
			char *next_ptr = NULL;
			*vfields[field_index++] = strtof(ptr, &next_ptr);
			if (errno != 0 || ptr == next_ptr)
				return -1;

			ptr = next_ptr;

			// we have z !
			if (field_index > 2)
				break;
		}
	}
	return field_index == 3 ? 0 : -1;
}