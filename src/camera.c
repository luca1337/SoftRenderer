#include "../include/camera.h"

camera_t* camera_create_new(doge_vec3_t position, float fov)
{
    camera_t* cam = malloc(sizeof(camera_t));

    if(!cam)
        return 0;

    cam->position.x = position.x;
    cam->position.y = position.y;
    cam->position.z = position.z;
    cam->fov_y = fov;
    return cam;
}

void camera_destroy(camera_t* camera)
{
    free(camera);
}