#ifndef VECTOR3_H
#define VECTOR3_H

typedef struct doge_vec3
{
	float x;
	float y;
	float z;
}doge_vec3_t;

// const doge_vec3_t doge_vec3_zero 	= {0.0f, 0.0f, 0.0f};
// const doge_vec3_t doge_vec3_x 		= {1.0f, 0.0f, 0.0f};
// const doge_vec3_t doge_vec3_y 		= {0.0f, 1.0f, 0.0f};
// const doge_vec3_t doge_vec3_z 		= {0.0f, 0.0f, 1.0f};
// const doge_vec3_t doge_vec3_one 	= {1.0f, 1.0f, 1.0f};

doge_vec3_t doge_vec3_create(float, float, float);

doge_vec3_t doge_vec3_add(doge_vec3_t, doge_vec3_t);

doge_vec3_t doge_vec3_sub(doge_vec3_t, doge_vec3_t);

float doge_vec3_dot(doge_vec3_t, doge_vec3_t);

doge_vec3_t doge_vec3_cross(doge_vec3_t, doge_vec3_t);

doge_vec3_t doge_vec3_mul(doge_vec3_t, doge_vec3_t);

doge_vec3_t doge_vec3_scaled(doge_vec3_t, float);

float doge_vec3_len(doge_vec3_t);

float doge_vec3_len_sq(doge_vec3_t);

void doge_vec3_normalize(doge_vec3_t *);

doge_vec3_t doge_vec3_normalized(doge_vec3_t);

#endif