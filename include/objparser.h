#ifndef OBJPARSER_H
#define OBJPARSER_H

#include "triangle.h"
#include "list.h"
#include "databuffer.h"

typedef struct mesh
{
	data_buffer_f_t* v;
	data_buffer_f_t* uv;
	data_buffer_f_t* n;

	data_buffer_f_t* f;

	vec3_t position;
	doge_quat_t rot;

}mesh_t;

typedef struct mesh_vec3
{
	float x;
	float y;
	float z;
}mesh_vec3_t;

mesh_t* mesh_create();
mesh_t* mesh_destroy(mesh_t* mesh);
void mesh_init(mesh_t* mesh);
// void iterator_mesh(mesh_t *, triangle_t *, int *);
// mesh_t* parse_file_float(char*);
mesh_t* parse_obj(char*);

#endif