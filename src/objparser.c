#include "../include/objparser.h"
#include "../include/list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

#define LINE_SIZE 1024

void destroy_meshdata(mesh_data_t* mesh)
{
    free(mesh->f);
    free(mesh->v);
    free(mesh);
}

mesh_data_t* read_mesh_obj(const char *file_name)
{
    mesh_data_t *mesh = malloc(sizeof(mesh_data_t));
    memset(mesh, 0, sizeof(mesh_data_t));
    mesh->v = NULL;
    mesh->f = NULL;
    mesh->num_of_v = 0;
    mesh->num_of_f = 0;
    mesh->pos = create_vec3(0, 0, 0);
    mesh->rot = doge_quat_create(0, 0, 0, 1);
    mesh->scale = create_vec3(1, 1, 1);

    int* list_count = malloc(1000);

    FILE* file = fopen(file_name, "r");
    char* line = malloc(128);
    int buff_size = 128;
    aiv_list_t* mesh_list_all = aiv_list_new(list_count);

    if(!file)
    {
        fprintf(stderr, "Couldn't open file: %s\n", file_name);
        destroy_meshdata(mesh);
        return NULL;
    }

    static int is_v = 0;
    static int is_f = 0;

    static int count = 0;
    static int count2 = 0;

    char* item;

    aiv_list_t* float_v = aiv_list_new(list_count);
    aiv_list_t* normal = aiv_list_new(list_count);
    aiv_list_t* uv = aiv_list_new(list_count);
    aiv_list_t* vec = aiv_list_new(list_count);

    while(!feof(file))
    {
        if(!fgets(line, buff_size, file))
            break;

        fscanf(file, "%s", line);

        if(strcmp("f", line) == 0)
        {
            char* line_cpy = malloc((unsigned long)(line) - 1);

            int i = 0;
            for(item = strtok(line_cpy, " "); item; item = strtok(NULL, " "))
            {
                if(i > 0)
                {
                    fprintf(stdout, "%d", i);
                    
                    float* value = malloc(sizeof(float)); 
                    *value = (float)atof(item);
                    aiv_list_append(float_v,value);
                }
            }
        }
        // else if(strcmp("v", line) == 0)
        // {
        //     count2++;
        // }
        // free(item);
    }

    fprintf(stdout, "float for f: %lu\n", mesh->num_of_f);
    fprintf(stdout, "float for v: %d\n", count2);

    fclose(file);
    
    return mesh;
}

char* load_file(char *file_name)
{
    FILE* file = NULL;
    char* buffer = NULL;
    long len = 0;

    file = fopen(file_name, "r");
    if(!file)
        return NULL;

    fseek(file, 0, SEEK_END);
    len = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = malloc(len);

    if(!buffer)
    {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, len, file);

    fclose(file);
    return buffer;
}