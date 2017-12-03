#ifndef OBJPARSER_H
#define OBJPARSER_H

#include "triangle.h"
#include "list.h"

typedef struct mesh
{
	float* u;
	float* v;
	float* vn;
	float* vt;
	float* f;
	int u_count;
	int v_count;
	int vn_count;
	int vt_count;
	int f_count;
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
// mesh_t* parse_file_float(char*);
mesh_t* parse_obj(char*);

#endif