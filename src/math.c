#include <stdlib.h>
#include "../include/math.h"


//VECTOR 2
vec2_t sum_vec2(vec2_t a, vec2_t b)
{
    vec2_t v;
    v.x = a.x+b.x;
    v.y = a.y+b.y;
    return v;
}
vec2_t sub_vec2(vec2_t a, vec2_t b)
{
    vec2_t v;
    v.x = a.x-b.x;
    v.y = a.y-b.y;
    return v;
}
vec2_t scale_vec2(vec2_t a, vec2_t b)
{
    vec2_t v;
    v.x = a.x*b.x;
    v.y = a.y*b.y;
    return v;
}
float slow_len_vec2( vec2_t a)
{
   return (float)sqrt(pow(a.x,2)+pow(a.y,2));
}
float fast_len_vec2(vec2_t a)
{
   return (pow(a.x,2)+pow(a.y,2));
}
float distance_vec2(vec2_t a,vec2_t b)
{
    vec2_t c = sub_vec2(a,b);
    return slow_len_vec2(c);
}
int normalize_vec2(vec2_t* a)
{
    float a_len = slow_len_vec2(*a);
    a->x = a->x / a_len;
    a->y = a->y / a_len;
    return 0;
}
vec2_t create_vec2(float x,float y)
{
    vec2_t v;
    v.x = x;
    v.y = y;
    return v;
}
vec2_t multiply_vec2(vec2_t v, float n)
{
    vec2_t new_v;
    new_v.x = v.x*n;
    new_v.y = v.y*n;
    return new_v;    
}

vec2_t interpolate_vec2(vec2_t a,vec2_t b, float gradient)
{
    return sum_vec2(a,multiply_vec2(sub_vec2(b,a),gradient));
}

vec3_t create_vec3(float x,float y, float z)
{
    vec3_t v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

//VECTOR 3
vec3_t sum_vec3(vec3_t a, vec3_t b)
{
    vec3_t v;
    v.x = a.x+b.x;
    v.y = a.y+b.y;
    v.z = a.z+b.z;
    return v;
}
vec3_t sub_vec3(vec3_t a, vec3_t b)
{
    vec3_t v;
    v.x = a.x-b.x;
    v.y = a.y-b.y;
    v.z = a.z-b.z;
    return v;
}
vec3_t scale_vec3_float(vec3_t v, float s)
{
    return create_vec3(v.x * s, v.y * s, v.z * s);
}
vec3_t scale_vec3(vec3_t a, vec3_t b)
{
    vec3_t v;
    v.x = a.x*b.x;
    v.y = a.y*b.y;
    v.z = a.z*b.z;
    return v;
}
float slow_len_vec3( vec3_t a)
{
   return (float)sqrt(pow(a.x,2)+pow(a.y,2)+pow(a.z,2));
}
float fast_len_vec3(vec3_t a)
{
   return (pow(a.x,2)+pow(a.y,2)+pow(a.z,2));
}
float distance_vec3(vec3_t a, vec3_t b)
{
    vec3_t c = sub_vec3(a,b);
    return slow_len_vec3(c);
}
int normalize_vec3(vec3_t* a)
{
    float a_len = slow_len_vec3(*a);
    a->x = a->x / a_len;
    a->y = a->y / a_len;
    a->z = a->z / a_len;
    return 0;
}
vec3_t multiply_vec3(vec3_t v,float n)
{
    vec3_t new_v;
    new_v.x = new_v.x * n;
    new_v.y = new_v.y * n;
    new_v.z = new_v.z * n;
    return new_v;
}
float dot_vec3(vec3_t v1, vec3_t v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3_t normalized_vec3(vec3_t v)
{
    float len = slow_len_vec3(v);
    vec3_t new_v;
    new_v.x = v.x/len;
    new_v.y = v.y/len;
    new_v.z = v.z/len;
    
}
vec3_t Reflect(vec3_t v1, vec3_t v2)
{
    float dot = dot_vec3(v1,v2);
    return sub_vec3(v1,multiply_vec3(v2,2*dot)); 
    // return v - 2f * Vector3.Dot(v, n) * n;
}
vec3_t interpolate_vec3(vec3_t a,vec3_t b, float gradient)
{
    return sum_vec3(a,multiply_vec3(sub_vec3(b,a),gradient));
}

vec3_t vec3_cross(vec3_t v1, vec3_t v2)
{
    float x = v1.y * v2.z - v1.z * v2.y;
    float y = v1.z * v2.x - v1.x * v2.z;
    float z = v1.x * v2.y - v1.y * v2.x;

    return create_vec3(x, y, z);
}

//float
float interpolate_float(float a,float b,float gradient)
{
    return a + (b - a) * gradient;
}
