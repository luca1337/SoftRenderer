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

/*mesh_data_t* read_mesh_obj(const char* file_name)
{
    mesh_data_t* mesh = malloc(sizeof(mesh_data_t));

    mesh->f = NULL;
    mesh->v = NULL;
    mesh->num_of_f = 0;
    mesh->num_of_v = 0;
    mesh->pos = doge_vec3_create(0.0f, 0.0f, 0.0f);
    mesh->rot = doge_quat_create(0.0f, 0.0f, 0.0f, 1.0f);

    char* file = read_file(file_name);

    mesh->num_of_f = malloc(sizeof(float)*500000);
    mesh->num_of_v = malloc(sizeof(float)*500000);

    if(!file)
    {
        fprintf(stderr, "couldn't open file: %s", file_name);
        destroy_meshdata(mesh);
        return 0;
    }

    while(!feof(file))
    {
        if(strchr(file, '\n'))
        {
            fprintf(stdout, "awdawd");
        }
    }

    fclose(file);
    return mesh;
}*/

mesh_data_t* read_mesh_obj(const char *file_name)
{
    mesh_data_t *mesh = malloc(sizeof(mesh_data_t));
    mesh->v = NULL;
    mesh->f = NULL;
    mesh->num_of_v = 0;
    mesh->num_of_f = 0;
    mesh->pos = create_vec3(0, 0, 0);
    mesh->rot = doge_quat_create(0, 0, 0, 1);
    mesh->scale = create_vec3(1, 1, 1);

    const char *file = read_file(file_name);
    if(!file)
    {
        fprintf(stderr, "Couldn't open file: %s\n", file_name);
        destroy_meshdata(mesh);
        return NULL;
    }

    unsigned long v_size = 500000;
    unsigned long f_size = 500000;

    mesh->v = malloc(sizeof(float) * v_size);
    mesh->f = malloc(sizeof(int) * f_size);
    
    const char *cur_line = file;

    while(cur_line)
    {
        char *next_line = strchr(cur_line, '\n');

        if(cur_line[0] == 'v' && cur_line[1] == ' ')
        {
            char *line_cpy = malloc((unsigned long)(next_line - cur_line) + 1);
            memcpy(line_cpy, cur_line, (unsigned long)(next_line - cur_line));
            line_cpy[next_line - cur_line + 1] = (char)0;
            
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
        else if(cur_line[0] == 'f')
        {
            char *line_cpy = malloc(next_line - cur_line + 1);
            memcpy(line_cpy, cur_line, next_line - cur_line);
            line_cpy[next_line - cur_line + 1] = (char)0;

            char tokens[6][1000];

            int i = 0;
            for(char *token = strtok(line_cpy, " "); token; token = strtok(NULL, " "))
            {
                memcpy(&(tokens[i][0]), token, strlen(token));
                tokens[i][strlen(token) + 1] = (char)0;
                i++;
            }

            for(i = 1; i < 5; i++)
            {
                int j = 0;
                for(char *token = strtok(&(tokens[i][0]), "/"); token; token = strtok(NULL, "/"))
                {
                    if(!j++)
                    {
                        mesh->f[mesh->num_of_f++] = atoi(token) - 1;
                    }
                }
            }
            free(line_cpy);
        }

        cur_line = next_line ? (next_line + 1) : NULL;
    }
    free((void *)file);
    return mesh;
}

void* read_file(char *file_name)
{
    FILE* stream = NULL;
    const void* buffer = NULL;
    long flen = 0;

    stream = fopen(file_name, "r");
    if(!stream)
    {
        fprintf(stderr, "Couldn't open file: %s\n", file_name);
        fclose(stream);
        return NULL;
    }

    fseek(stream, 0, SEEK_END);
    flen = ftell(stream);
    fseek(stream, 0, SEEK_SET);

    buffer = malloc(flen);

    if(!buffer)
    {
        fprintf(stderr, "Couldn't allocate memory for the buffer");
        fclose(stream);
        return NULL;
    }
    else
    {
        fread((void*)buffer, 1, flen, stream);
    }

    fclose(stream);
    return buffer;
}