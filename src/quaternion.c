#include "../include/quaternion.h"
#include <math.h>

doge_quat_t doge_quat_create(float x, float y, float z, float w)
{
    doge_quat_t q;
    q.v = create_vec3(x, y, z);
    q.w = w;
    return q;
}

doge_quat_t doge_quat_from_axis_angle(float ax, float ay, float az, float angle)
{
    doge_quat_t q;
    float s = sin(angle/2);
    q.v = create_vec3(ax * s, ay * s, az * s);
    q.w = cos(angle/2);
    return q;
}

doge_quat_t doge_quat_conjugated(doge_quat_t q)
{
    q.v = scale_vec3(q.v, -1);
    return q;
}

void doge_quat_conjugate(doge_quat_t * q)
{
    q->v.x *= -1;
    q->v.x *= -1;
    q->v.z *= -1;
}

doge_quat_t doge_quat_mul(doge_quat_t q1, doge_quat_t q2)
{
    doge_quat_t q;
    q.w = q1.w * q2.w - dot_vec3(q1.v, q2.v);
    q.v = sum_vec3(sum_vec3(scale_vec3(q1.v, q2.w), scale_vec3(q2.v, q1.w)), vec3_cross(q1.v, q2.v));
    return q;
}

vec3_t doge_quat_rotated_vec(vec3_t v, doge_quat_t q)
{
    doge_quat_t v_quat;
    v_quat.w = 0;
    v_quat.v = q.v;

    vec3_t cross = vec3_cross(q.v, v);

    return sum_vec3(sum_vec3(scale_vec3(cross, q.w * 2), v), scale_vec3(vec3_cross(q.v, cross), 2));
}