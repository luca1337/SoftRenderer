#include "../include/objparser.h"
#include "../include/list.h"
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS

int mesh_parse_vec3(char* line, size_t size, mesh_vec3_t* v3)
{
    float *vfields[3];
	vfields[0] = (float *)((void *)v3 + offsetof(mesh_vec3_t, x));
	vfields[1] = (float *)((void *)v3 + offsetof(mesh_vec3_t, y));
	vfields[2] = (float *)((void *)v3 + offsetof(mesh_vec3_t, z));

    size_t findx = 0;

    char* ptrline = line;
    for(size_t i = 0; i < size; i++)
    {
        if(isspace(line[i] || i + 1 == size))
        {
            errno = 0;
            char *next_ptr = NULL;
            *vfields[findx++] = strtof(ptrline, &next_ptr);

            if (errno != 0 || ptrline == next_ptr)
                return -1;

            ptrline = next_ptr;

            if (findx > 2)
                break;
        }
    }
    return findx == 3 ? 0 : -1;
}

void mesh_parse_init(mesh_ctx_t* mesh)
{
    memset(mesh, 0, sizeof(mesh_ctx_t));
}

void mesh_parse_destroy(mesh_ctx_t* mesh)
{
    if(mesh->faces) free(mesh->faces);
    if(mesh->v) free(mesh->v);
    if(mesh->vn) free(mesh->vn);
    if(mesh->vt) free(mesh->vt);
    free(mesh);
}