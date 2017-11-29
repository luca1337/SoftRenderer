#include "../include/draw.h"
#include "../include/camera.h"
#include "../include/triangle.h"
#include "../include/objparser.h"

draw_color_t black = {0, 0, 0, 255};
draw_color_t red = {255, 0, 0, 255};
draw_color_t yellow = {255, 255, 0, 255};
draw_color_t green = {0, 255, 0, 255};

int main(int argc, char *argv[])
{
    draw_context_t *context = draw_context_new("rectangle", 800, 600);

    vec3_t p0 = create_vec3(0.0f, 0.0f, -0.5f);

    vec3_t p1 = create_vec3(0, 3, 10);
    vec3_t p2 = create_vec3(-2.5f, -1, 20);
    vec3_t p3 = create_vec3(2.5f, -4, 10);

    triangle_t triangle = triangle_create(p1, p2, p3);

    camera_t* cam = camera_create_new(p0, 80.0f);

    //mesh_data_t* mesh = read_mesh_obj("suzanne.obj");

    float angle = 0;

    for(;;)
    {
        float x = 400 + cos(angle) * 454;
        float y = 400 + sin(angle) * 160;

        draw_context_clear(context, black);

        draw_rectangle_wireframe(context, triangle, cam, red);

        draw_line_bresenham(context, 400, 300, x, y, yellow); //works

        angle += 0.01f;

        draw_context_blit(context);
    }
    draw_context_destroy(context);
}