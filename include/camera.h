#ifndef CAMERA_H
#define CAMERA_H

#include "math.h"

struct camera
{
    vec3_t position;
    float fov_y;
};

typedef struct camera camera_t;

camera_t* camera_create_new(vec3_t, float);
void camera_destroy(camera_t*);

#endif