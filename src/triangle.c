#include "../include/quaternion.h"
#include "../include/triangle.h"
#include "../include/camera.h"
#include "../include/draw.h"
#include "../include/vector3.h"

static float fovy;

triangle_t triangle_create(doge_vec3_t a, doge_vec3_t b, doge_vec3_t c)
{
    triangle_t t;
    t.a = a;
    t.b = b;
    t.c = c;
    return t;
}

void project(triangle_t triangle, draw_context_t* context, camera_t* cam, doge_quat_t rotation, draw_color_t color)
{
    // fovy = cam->fov_y * (DOGE_PI / 180); // lol

    // doge_vec3_t ac = rotation * t.a - cam->position;
    // doge_vec3_t bc = rotation * t.b - cam->position;
    // doge_vec3_t cc = rotation * t.c - cam->position;

    // float yp1 = ac.y / (ac.z * tan(fovy / 2));
    // float xp1 = ac.x / (ac.z * tan(fovy / 2));

    // int nxp1 = (int)(xp1 * 300 + 300);
    // int nyp1 = (int)(-yp1 * 400 + 400);

    // float yp2 = bc.y / (bc.z * tan(fovy / 2));
    // float xp2 = bc.x / (bc.z * tan(fovy / 2));

    // int nxp2 = (int)(xp2 * 300 + 300);
    // int nyp2 = (int)(-yp2 * 400 + 400);

    // float yp3 = cc.y / (cc.z * tan(fovy / 2));
    // float xp3 = cc.x / (cc.z * tan(fovy / 2));

    // int nxp3 = (int)(xp3 * 300 + 300);
    // int nyp3 = (int)(-yp3 * 400 + 400);

    // draw_line_bresenham(context, nxp1, nyp1, nxp2, nyp2, color);
    // draw_line_bresenham(context, nxp2, nyp2, nxp3, nyp3, color);
    // draw_line_bresenham(context, nxp1, nyp1, nxp3, nyp3, color);
}

void project_triangle(triangle_t t, draw_context_t* context, camera_t* cam, draw_color_t color)
{
    fovy = cam->fov_y * (DOGE_PI / 180);

    float yp1 = t.a.y / (t.a.z * tan(fovy / 2));
    float xp1 = t.a.x / (t.a.z * tan(fovy / 2));

    draw_context_put_pixel(context, (xp1 * 400 + 400), (-yp1 * 300 + 300), color);

    float yp2 = t.b.y / (t.b.z * tan(fovy /2));
    float xp2 = t.b.y / (t.b.z * tan(fovy /2));

    draw_context_put_pixel(context, (xp2 * 400 + 400), (-yp2 * 300 + 300), color);

    float yp3 = t.c.y / (t.c.z * tan(fovy /2));
    float xp3 = t.c.y / (t.c.z * tan(fovy /2));

    draw_context_put_pixel(context, (xp3 * 400 + 400), (-yp3 * 300 + 300), color);
}

void draw_rectangle_wireframe(draw_context_t* context, triangle_t t, camera_t* cam, draw_color_t color)
{
    fovy = cam->fov_y * (DOGE_PI / 180);

    float yp1 = t.a.y / (t.a.z * tan(fovy / 2));
    float xp1 = t.a.x / (t.a.z * tan(fovy / 2));
    draw_context_put_pixel(context, (xp1 * 400 + 400), (-yp1 * 300 + 300), color);

    float yp2 = t.b.y / (t.b.z * tan(fovy /2));
    float xp2 = t.b.y / (t.b.z * tan(fovy /2));
    draw_context_put_pixel(context, (xp2 * 400 + 400), (-yp2 * 300 + 300), color);

    float yp3 = t.c.y / (t.c.z * tan(fovy /2));
    float xp3 = t.c.y / (t.c.z * tan(fovy /2));
    draw_context_put_pixel(context, (xp3 * 400 + 400), (-yp3 * 300 + 300), color);

    draw_line_bresenham(context, (xp1 * 400 + 400), (-yp1 * 300 + 300), (xp2 * 400 + 400), (-yp2 * 300 + 300), color);
    draw_line_bresenham(context, (xp2 * 400 + 400), (-yp2 * 300 + 300), (xp3 * 400 + 400), (-yp3 * 300 + 300), color);
    draw_line_bresenham(context, (xp3 * 400 + 400), (-yp3 * 300 + 300), (xp1 * 400 + 400), (-yp1 * 300 + 300), color);

}
