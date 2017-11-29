#include "../include/camera.h"

camera_t* camera_create_new(vec3_t position, float fov)
{
    camera_t* cam = malloc(sizeof(camera_t));
    cam->position = position;
    cam->fov_y = fov;
    return cam;
}

void camera_destroy(camera_t* camera)
{
    free(camera);
}