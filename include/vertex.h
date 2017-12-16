#ifndef VERTEX_H
#define VERTEX_H

#include "quaternion.h"
#include "math.h"
#include "camera.h"

typedef struct vertex{
    vec3_t pos; 
    vec3_t normal;
    vec2_t uv;
    vec3_t world_pos;
    vec3_t world_view_pos;
    vec3_t world_normal;
    vec2_t world_proj_pos;
}vertex_t;

void proj(camera_t, vertex_t*, vec3_t, doge_quat_t, vec3_t);

vertex_t create_vertex( vec3_t ,vec3_t ,vec2_t );

#endif