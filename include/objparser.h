#ifndef OBJPARSER_H
#define OBJPARSER_H

#include "triangle.h"

typedef struct mesh_vec3
{
    float x;
    float y;
    float z;
}mesh_vec3_t;

typedef struct mesh_uv
{
    float u;
    float v;
}mesh_uv_t;

typedef struct mesh_vertex
{
    size_t v_idx;
    size_t vt_idx;
    size_t vn_idx;
}mesh_vertex_t;

typedef struct mesh_face
{
	mesh_vertex_t v1;
	mesh_vertex_t v2;
	mesh_vertex_t v3;
} mesh_face_t;

typedef struct mesh_ctx
{
	mesh_vec3_t *v;
	mesh_vec3_t *vn;
	mesh_vec3_t *vt;
	mesh_face_t *faces;
	size_t v_cnt;
	size_t vn_cnt;
	size_t vt_cnt;
	size_t faces_cnt;
} mesh_ctx_t;

int mesh_parse_vec3(char*, size_t, mesh_vec3_t*);
void mesh_parse_init(mesh_ctx_t*);
void mesh_parse_destroy(mesh_ctx_t*);

char* strsep2(char**, const char*);


#endif