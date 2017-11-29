#include "../include/quaternion.h"
#include "../include/triangle.h"
#include "../include/camera.h"
#include "../include/draw.h"
#include "../include/vertex.h"

static float fovy;

static vertex_t a;
static vertex_t b;
static vertex_t c;

triangle_t triangle_create(vec3_t a, vec3_t b, vec3_t c)
{
    triangle_t t;
    t.a = a;
    t.b = b;
    t.c = c;
    return t;
}

triangle_t triangle_create_vert(vertex_t a, vertex_t b, vertex_t c)
{
    vertex_t v0,v1,v2;
    v0 = a;
    v1 = b;
    v2 = c;
    return triangle_create_vert(v0, v1, v2);
}

void draw_rectangle_wireframe(draw_context_t* context, triangle_t t, camera_t* cam, draw_color_t color)
{
    fovy = cam->fov_y * (DOGE_PI / 180);

    float yp1 = t.a.y / (t.a.z * tan(fovy / 2));
    float xp1 = t.a.x / (t.a.z * tan(fovy / 2));
    draw_context_put_pixel(context, (xp1 * context->half_width + context->half_width),
     (-yp1 * context->half_height + context->half_height), color);

    float yp2 = t.b.y / (t.b.z * tan(fovy /2));
    float xp2 = t.b.y / (t.b.z * tan(fovy /2));
    draw_context_put_pixel(context, (xp2 * context->half_width + context->half_width),
     (-yp2 * context->half_height + context->half_height), color);

    float yp3 = t.c.y / (t.c.z * tan(fovy /2));
    float xp3 = t.c.y / (t.c.z * tan(fovy /2));
    draw_context_put_pixel(context, (xp3 * context->half_width + context->half_width),
     (-yp3 * context->half_height + context->half_height), color);

    draw_line_bresenham(context, (xp1 * context->half_width + context->half_width),
     (-yp1 * context->half_height + context->half_height), (xp2 * 400 + 400),
      (-yp2 * context->half_height + context->half_height), color);

    draw_line_bresenham(context, (xp2 * context->half_width + context->half_width),
     (-yp2 * context->half_height + context->half_height), (xp3 * 400 + 400), 
     (-yp3 * context->half_height + context->half_height), color);

    draw_line_bresenham(context, (xp3 * context->half_width + context->half_width),
     (-yp3 * context->half_height + context->half_height), (xp1 * 400 + 400),
      (-yp1 * context->half_height + context->half_height), color);

}
