#include "../include/vector3.h"
#include <math.h>

doge_vec3_t doge_vec3_create(float x, float y, float z)
{
    doge_vec3_t result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

doge_vec3_t doge_vec3_add(doge_vec3_t v1, doge_vec3_t v2)
{
    return doge_vec3_create(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

doge_vec3_t doge_vec3_sub(doge_vec3_t v1, doge_vec3_t v2)
{
    return doge_vec3_create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

float doge_vec3_dot(doge_vec3_t v1, doge_vec3_t v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

doge_vec3_t doge_vec3_cross(doge_vec3_t v1, doge_vec3_t v2)
{
    float x = v1.y * v2.z - v1.z * v2.y;
    float y = v1.z * v2.x - v1.x * v2.z;
    float z = v1.x * v2.y - v1.y * v2.x;

    return doge_vec3_create(x, y, z);
}

doge_vec3_t doge_vec3_mul(doge_vec3_t v1, doge_vec3_t v2)
{
    return doge_vec3_create(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

doge_vec3_t doge_vec3_scaled(doge_vec3_t v, float s)
{
    return doge_vec3_create(v.x * s, v.y * s, v.z * s);
}

float doge_vec3_len(doge_vec3_t v)
{
    return sqrt(doge_vec3_len_sq(v));
}

float doge_vec3_len_sq(doge_vec3_t v)
{
    return doge_vec3_dot(v, v);
}

void doge_vec3_normalize(doge_vec3_t *v)
{
    doge_vec3_t temp = doge_vec3_create(v->x, v->y, v->z);
    float len = doge_vec3_len(temp);

    if(len == 0)
        return;

    v->x /= len;
    v->y /= len;
    v->z /= len;
}

doge_vec3_t doge_vec3_normalized(doge_vec3_t v)
{
    float len = doge_vec3_len(v);

    if(len == 0)
        return v;
    
    return doge_vec3_create(v.x / len, v.y / len, v.z / len);
}