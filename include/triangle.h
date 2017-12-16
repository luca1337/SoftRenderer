#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "math.h"
#include "draw.h"
#include "camera.h"
#include "quaternion.h"
#include "vertex.h"
#include "objparser.h"
#include "triangle.h"

typedef struct triangle
{
    vertex_t a;
    vertex_t b;
    vertex_t c;

    struct triangle* next;
    struct triangle* prev;

    void* owner;
}triangle_t;

typedef struct triangle_vertex
{
    vertex_t a;
    vertex_t b;
    vertex_t c;
}triangle_vertex_t;

typedef struct triangle_vrtx
{
    vec3_t v;
    vec3_t n;
    vec2_t uv;
}triangle_vrtx_t;

typedef struct triangle_vrtx_2
{
    struct triangle_vrtx v[3];
}triangle_vrtx_2_t;

//triangle constructor
triangle_t* triangle_create(vertex_t, vertex_t, vertex_t);

//triangle constructor with vertexes
triangle_t* triangle_create_vert(vertex_t, vertex_t, vertex_t);

//wireframe rectangle
void draw_rectangle_wireframe(draw_context_t*, triangle_t, camera_t*, draw_color_t);

//draw for mesh
void mesh_draw(camera_t, triangle_t, draw_context_t*, vec3_t, doge_quat_t, vec3_t, draw_color_t);

void Scanline(draw_context_t*, int y, vertex_t, vertex_t, vertex_t, vertex_t, draw_color_t);

void iterator_mesh(struct mesh*, triangle_vrtx_2_t*, int*);

void draw_context_mesh_draw(draw_context_t*, struct mesh*, camera_t, draw_color_t);

void mesh_add_triangle(struct mesh*, triangle_t*);

#endif