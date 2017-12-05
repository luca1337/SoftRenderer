#include "../include/objparser.h"
#include "../include/list.h"
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include "../include/databuffer.h"

#define _CRT_SECURE_NO_WARNINGS

#define SIZE 4

mesh_t* mesh_create()
{
    mesh_t* mesh = malloc(sizeof(mesh_t));
    return mesh;
}

mesh_t* mesh_destroy(mesh_t* mesh)
{
    if(mesh->v)     free(mesh->v);
    if(mesh->uv)    free(mesh->uv);
    if(mesh->n)     free(mesh->n);
    if(mesh->f)     free(mesh->f);
    if(mesh)        free(mesh);
}

void mesh_init(mesh_t* mesh)
{
    mesh->v = NULL;
    mesh->uv = NULL;
    mesh->n = NULL;
    mesh->f = NULL;
    mesh->position = create_vec3(0, 0, 0);
    mesh->rot = doge_quat_create(0, 0, 0, 1);
}

mesh_t* parse_obj(char* _arg)
{
    //open and allocate memory for file
    FILE* file = fopen(_arg, "rb");
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

    mesh->v = data_buffer_new_f(0x0);
    mesh->uv = data_buffer_new_f(0x0);
    mesh->n = data_buffer_new_f(0x0);
    mesh->f = data_buffer_new_i(0x0);

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
                    float value = atof(token);
                    data_buffer_add_element_f(mesh->v, value);
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
                    float value = atof(token);
                    data_buffer_add_element_f(mesh->n, value);
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
                    float value = atof(token);
                    data_buffer_add_element_f(mesh->uv, value);
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
                        data_buffer_add_element_i(mesh->f, atoi(token) - 1);
                        // int a = atoi(token);
                        // fprintf(stdout, "\n%i\n", a);
                    }
                }
            }

            free(cpy_line);
        }
    }
    fprintf(stdout, "\nf: %i\nv: %i\nuv: %i\nn: %i\n", mesh->f->count, mesh->v->count, mesh->uv->count, mesh->n->count);
    free(lines);
    free((void*)file);

    return mesh;
}

void iterator_mesh(mesh_t *mesh, triangle_vertex_t *triangle, int *face)
{
    // int i = *face;
    // int fv1 = mesh->f->element[i];
    // int fn1 = mesh->f->element[i + 1];
    // int fuv1 = mesh->f->element[i + 2];

    // int fv2 = mesh->f->element[i + 3];
    // int fn2 = mesh->f->element[i + 4];
    // int fuv2 = mesh->f->element[i + 5];

    // int fv3 = mesh->f->element[i + 6];
    // int fn3 = mesh->f->element[i + 7];
    // int fuv3 = mesh->f->element[i + 8];

    // triangle->v[0].v = vec3_create(mesh->v->element[3 * fv1], mesh->v->element[3 * fv1 + 1], mesh->v->element[3 * fv1 + 2]);
    // triangle->v[0].n = vec3_create(mesh->n->element[3 * fn1], mesh->n->element[3 * fn1 + 1], mesh->n->element[3 * fn1 + 2]);
    // triangle->v[0].uv = vec2_create(mesh->uv->element[2 * fuv1], mesh->uv->element[2 * fuv1 + 1]);

    // triangle->v[1].v = vec3_create(mesh->v->element[3 * fv2], mesh->v->element[3 * fv2 + 1], mesh->v->element[3 * fv2 + 2]);
    // triangle->v[1].n = vec3_create(mesh->n->element[3 * fn2], mesh->n->element[3 * fn2 + 1], mesh->n->element[3 * fn2 + 2]);
    // triangle->v[1].uv = vec2_create(mesh->uv->element[2 * fuv2], mesh->uv->element[fuv2 + 1]);

    // triangle->v[2].v = vec3_create(mesh->v->element[3 * fv3], mesh->v->element[3 * fv3 + 1], mesh->v->element[3 * fv3 + 2]);
    // triangle->v[2].n = vec3_create(mesh->n->element[3 * fn3], mesh->n->element[3 * fn3 + 1], mesh->n->element[3 * fn3 + 2]);
    // triangle->v[2].uv = vec2_create(mesh->uv->element[2 * fuv1], mesh->uv->element[2 * fuv1 + 1]);

    // *face += 9;
}