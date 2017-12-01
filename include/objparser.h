#ifndef OBJPARSER_H
#define OBJPARSER_H

#include "triangle.h"
#include "list.h"


typedef struct mesh_v3
{
	float x;
	float y;
	float z;
}mesh_v3_t;

typedef struct mesh_uv
{
	float u;
	float v;
}mesh_uv_t;

typedef struct data
{
	mesh_v3_t* v;
	float* f;
	int num_v;
	int num_f;
}data_t;

list_t* parse_file_float(char*);
list_t* parse_file_split_str(char*, size_t, mesh_v3_t*);
int parse_file_vec3(char*, size_t, mesh_v3_t*);

#endif