#include "../include/objparser.h"
#include "../include/list.h"
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS

#define SIZE 4

mesh_t* mesh_create()
{
    mesh_t* mesh = malloc(sizeof(mesh_t));
    return mesh;
}

mesh_t* mesh_destroy(mesh_t* mesh)
{
    if(mesh->u)     free(mesh->u);
    if(mesh->v)     free(mesh->v);
    if(mesh->vn)    free(mesh->vn);
    if(mesh->vt)    free(mesh->vt);
    if(mesh->f)     free(mesh->f);
    if(mesh)        free(mesh);
}

void mesh_init(mesh_t* mesh)
{
    mesh->u = NULL;
    mesh->v = NULL;
    mesh->f = NULL;
    mesh->vn = NULL;
    mesh->vt = NULL;
    mesh->f_count = 0;
    mesh->u_count = 0;
    mesh->v_count = 0;
    mesh->vn_count = 0;
    mesh->vt_count = 0;
    mesh->position = create_vec3(0, 0, 0);
    mesh->rot = doge_quat_create(0, 0, 0, 1);
}

mesh_t* parse_obj(char* _arg)
{
    //open and allocate memory for file
    FILE* file = fopen(_arg, "r");
    char* lines = malloc(sizeof(char) * 1000);

    //create mesh to store all values and init it
    mesh_t* mesh = mesh_create();
    mesh_init(mesh);

    //create data structure to store all values
    mesh_vec3_t* v = malloc(sizeof(mesh_vec3_t));

    if(!file)
    {
        fprintf(stderr, "could not open file: %s", _arg);
        mesh_destroy(mesh);
        free(lines);
        return NULL;
    }

    mesh->u = malloc(sizeof(float*) * 50000);
    mesh->v = malloc(sizeof(float*) * 50000);
    mesh->f = malloc(sizeof(float*) * 50000);
    mesh->vt = malloc(sizeof(float*) * 50000);
    mesh->vn = malloc(sizeof(float*) * 50000);

    //enter in the loop and start parsing the file
    while(!feof(file))
    {
        //while file reading also add the stream inside a buffer to get the lines
        if(!fgets(lines, 1024, file))
            break;
        
        //start parsing file
        if(lines[0] == 'v' && lines[1] == ' ')
        {
            int i = 0;
            for(char* token = strtok(lines, " "); token; token = strtok(((void*)0), " "))
            {
                if(i++ > 0)
                {
                    //Implement buffer to hold all the data
                }
            }
        }
        else if(lines[1] == 'n')
        {
            int i = 0;
            for(char* token = strtok(lines, " "); token; token = strtok(((void*)0), " "))
            {
                if(i++ > 0)
                {
                    
                }
            }
        }
        else if(lines[1] == 't')
        {
            int i = 0;
            for(char* token = strtok(lines, " "); token; token = strtok(((void*)0), " "))
            {
                if(i++ > 0) 
                {
                    //Implement buffer to hold all the data
                }
            }
        }

        //parse f
        if(lines[0] == 'f')
        {
            char* cpy_line = malloc(sizeof(char) * strlen(lines) + 1);

            static int i = 0;
            for(char* token = strtok(lines, " "); token; token = strtok(((void*)0), " "))
            {
                if(i++ > 0)
                {
                    strcpy(cpy_line, token);
                }
            }

            for(i = 1; i < SIZE; i++)
            {
                int j = 0;
                for(char *token = strtok(cpy_line, "/"); token; token = strtok(((void*)0), "/"))
                {
                    if(j++ < 3)
                    {
                       //Implement buffer to hold all the data
                    }
                }
            }

            free(cpy_line);
        }
    }
    //fprintf(stdout, "\nv: %i\nvn: %i\nvt: %i\nf: %i\n", mesh->v_count, mesh->vn_count, mesh->vt_count, mesh->f_count);
    free(lines);
    free((void*)file);

    return mesh;
}