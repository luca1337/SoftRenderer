#include "../include/quaternion.h"
#include <math.h>

doge_quat_t doge_quat_create(float x, float y, float z, float w)
{
    doge_quat_t q;
    q.v = doge_vec3_create(x, y, z);
    q.w = w;
    return q;
}

doge_quat_t doge_quat_from_axis_angle(float ax, float ay, float az, float angle)
{
    doge_quat_t q;
    float s = sin(angle/2);
    q.v = doge_vec3_create(ax * s, ay * s, az * s);
    q.w = cos(angle/2);
    return q;
}

doge_quat_t doge_quat_conjugated(doge_quat_t q)
{
    q.v = doge_vec3_scaled(q.v, -1);
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
    q.w = q1.w * q2.w - doge_vec3_dot(q1.v, q2.v);
    q.v = doge_vec3_add(doge_vec3_add(doge_vec3_scaled(q1.v, q2.w), doge_vec3_scaled(q2.v, q1.w)), doge_vec3_cross(q1.v, q2.v));
    return q;
}

doge_vec3_t doge_quat_rotated_vec(doge_vec3_t v, doge_quat_t q)
{
    doge_quat_t v_quat;
    v_quat.w = 0;
    v_quat.v = q.v;

    doge_vec3_t cross = doge_vec3_cross(q.v, v);

    return doge_vec3_add(doge_vec3_add(doge_vec3_scaled(cross, q.w * 2), v), doge_vec3_scaled(doge_vec3_cross(q.v, cross), 2));
}