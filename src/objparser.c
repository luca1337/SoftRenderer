#include "../include/objparser.h"
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

mesh_data_t* read_mesh_obj(const char* file_name)
{
    mesh_data_t* mesh = malloc(sizeof(mesh_data_t));

    mesh->f = NULL;
    mesh->v = NULL;
    mesh->num_of_f = 0;
    mesh->num_of_v = 0;
    mesh->pos = doge_vec3_create(0.0f, 0.0f, 0.0f);
    mesh->rot = doge_quat_create(0.0f, 0.0f, 0.0f, 0.0f);

    FILE* file;
    file = fopen(file_name, "r");

    mesh->num_of_f = malloc(sizeof(float)*500000);
    mesh->num_of_v = malloc(sizeof(float)*500000);

    char* buffer[100];

    if(!file)
    {
        fprintf(stderr, "couldn't open file: %s", file_name);
        destroy_meshdata(mesh);
        return 0;
    }

    while(!feof(file))
    {
        char* curr_line = fgets(buffer, 100, file);
        char* next_line = strchr(curr_line, '\n');

        if(curr_line[0] == 'v' && curr_line[1] == ' ')
        {
            char* line_cpy = malloc((unsigned long)(next_line - curr_line) + 1);
            memcpy(line_cpy, curr_line, (unsigned long)(next_line - curr_line));
            line_cpy[next_line - curr_line + 1] = (char)0;

            int i = 0;
            for(char *token = strtok(line_cpy, " "); token; token = strtok(NULL, " "))
            {
                if(i++ > 0)
                {                
                    mesh->v[mesh->num_of_v++] = atof(token);
                }                
            }
            free(line_cpy);
        }
    }

    fclose(file);
    return mesh;
}