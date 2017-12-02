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

    vec3_t p0 = create_vec3(-10.0f, 0.0f, -10.5f);

    vec3_t p1 = create_vec3(200, 100, 10);
    vec3_t p2 = create_vec3(50, 300, 20);
    vec3_t p3 = create_vec3(50, 50, 10);

    triangle_t triangle = triangle_create(p1, p2, p3);

    doge_quat_t rott = doge_quat_create(0, 0, 0, 1);

    camera_t* cam = camera_create_new(p0, 120.0f);

    // mesh_t* mesh = read_mesh_obj("suzanne.obj");

    mesh_t* mesh = parse_obj("suzanne.obj");

    fprintf(stdout, "\nv: %i\nvn: %i\nvt: %i\nf: %i\n", mesh->v_count, mesh->vn_count, mesh->vt_count, mesh->f_count);

    //triangle_vertex_t* vert = malloc(sizeof(triangle_vertex_t));

    //something();

    /*test(test_parse_float_green_light);
    fprintf(stdout, "%d tests executed\n", tests_counter);*/

    float angle = 0;

    for(;;)
    {
        float x = 400 + cos(angle) * 800;
        float y = 400 + sin(angle) * 1;

        draw_context_clear(context, black);

        draw_rectangle_wireframe(context, triangle, cam, red);

        //test methods

        RasterizationBoundingBox(p1, p2, p3, context, red);

        draw_line_bresenham(context, 400, 300, x, y, yellow); //works

        angle += 0.01f;

        draw_context_blit(context);
    }
    draw_context_destroy(context);
}