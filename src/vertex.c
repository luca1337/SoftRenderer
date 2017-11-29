#include "../include/vertex.h"
#include "../include/quaternion.h"
#include "../include/camera.h"
#include "../include/math.h"

void proj(camera_t* cam, vertex_t* vertex, vec3_t pos, doge_quat_t rot, float scale)
{
    float half_w = 400/2;
    float half_h = 300/2;

    vertex->world_pos = (sum_vec3(scale_vec3(vertex->pos, scale), vertex->pos));
    vertex->world_normal = normalized_vec3(vertex->normal);
    vertex->world_view_pos = sub_vec3(vertex->world_pos, cam->position);

    float yp = vertex->world_view_pos.y / (vertex->world_view_pos.z * (float)tan(cam->fov_y / 2));
    float xp = vertex->world_view_pos.x / (vertex->world_view_pos.z * (float)tan(cam->fov_y / 2));

    int nxp = (int)(xp * half_w + half_w);
    int nyp = (int)(-yp * half_h + half_h);

    vertex->world_proj_pos = create_vec2(nxp,nyp);
}