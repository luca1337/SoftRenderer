#pragma once

#include <stdio.h>

typedef struct doge_vec2
{
	float x;
	float y;
}vec2_t;

typedef struct doge_vec3
{
	float x;
	float y;
	float z;
} vec3_t;

typedef union doge_vec
{
	vec2_t vec2;
	vec3_t vec3;
}doge_vec_t;


//float
float interpolate_float(float,float,float);

//vector 2
vec2_t sum_vec2(vec2_t, vec2_t);
vec2_t sub_vec2(vec2_t, vec2_t);
vec2_t scale_vec2(vec2_t, vec2_t);
float slow_len_vec2(vec2_t); //use this for precise misuration of distance
float fast_len_vec2(vec2_t); //use this for fast comparison 
float distance_vec2(vec2_t,vec2_t);
int normalize_vec2(vec2_t*); //normalize this vector (non alloc)
vec2_t create_vec2(float,float);
vec2_t interpolate_vec2(vec2_t,vec2_t, float );
vec2_t multiply_vec2(vec2_t, float );

//vector 3
vec3_t sum_vec3(vec3_t, vec3_t);
vec3_t sub_vec3(vec3_t, vec3_t);
vec3_t scale_vec3_float(vec3_t, float);
float slow_len_vec3( vec3_t);
float fast_len_vec3(vec3_t);
float distance_vec3(vec3_t, vec3_t);
int normalize_vec3(vec3_t*);
vec3_t multiply_vec3(vec3_t,float);
float dot_vec3(vec3_t , vec3_t );
vec3_t normalized_vec3(vec3_t);
vec3_t interpolate_vec3(vec3_t,vec3_t, float );
vec3_t reflect_vec3(vec3_t , vec3_t );
vec3_t vec3_cross(vec3_t, vec3_t);
vec3_t create_vec3(float, float, float);
vec3_t scale_vec3(vec3_t a, vec3_t b);