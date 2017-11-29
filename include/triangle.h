#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "math.h"
#include "draw.h"
#include "camera.h"
#include "quaternion.h"
#include "vertex.h"

typedef struct triangle
{
    vec3_t a;
    vec3_t b;
    vec3_t c;
}triangle_t;

typedef struct triangle_vertex
{
    vertex_t a;
    vertex_t b;
    vertex_t c;
}triangle_vertex_t;

//triangle constructor
triangle_t triangle_create(vec3_t, vec3_t, vec3_t);

//triangle constructor with vertexes
triangle_t triangle_create_vert(vertex_t, vertex_t, vertex_t);

//wireframe rectangle
void draw_rectangle_wireframe(draw_context_t*, triangle_t, camera_t*, draw_color_t);

#endif