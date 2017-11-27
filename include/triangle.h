#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector3.h"
#include "draw.h"
#include "camera.h"
#include "quaternion.h"

struct triangle
{
    doge_vec3_t a;
    doge_vec3_t b;
    doge_vec3_t c;
};

typedef struct triangle triangle_t;

//triangle constructor
triangle_t triangle_create(doge_vec3_t, doge_vec3_t, doge_vec3_t);

//projection for meshes
void project(triangle_t, draw_context_t*, camera_t*, doge_quat_t, draw_color_t);

//projection for triangles
void project_triangle(triangle_t, draw_context_t*, camera_t*, draw_color_t);

//wireframe rectangle
void draw_rectangle_wireframe(draw_context_t*, triangle_t, camera_t*, draw_color_t);

#endif