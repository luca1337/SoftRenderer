#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"

struct camera
{
    doge_vec3_t position;
    float fov_y;
};

typedef struct camera camera_t;

camera_t* camera_create_new(doge_vec3_t, float);
void camera_destroy(camera_t*);

#endif