#ifndef OBJPARSER_H
#define OBJPARSER_H

#include "triangle.h"

struct mesh_data
{
    float* v;
    int* f;
    unsigned long num_of_v;
    unsigned long num_of_f;
    doge_vec3_t pos;
    doge_quat_t rot;
};

typedef struct mesh_data mesh_data_t;

void destroy_meshdata(mesh_data_t*);
mesh_data_t* read_mesh_obj(const char*);

#endif