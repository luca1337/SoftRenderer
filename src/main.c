#include "../include/draw.h"
#include "../include/camera.h"
#include "../include/triangle.h"
#include "../include/objparser.h"

draw_color_t black = {0, 0, 0, 255};
draw_color_t red = {255, 0, 0, 255};
draw_color_t yellow = {255, 255, 0, 255};
draw_color_t green = {0, 255, 0, 255};

int test_v3(mesh_vec3_t v, float x, float y, float z);

static int tests_counter = 0;

#define test(f) tests_counter++;\
fprintf(stdout, "running " #f "...\n");\
if (f())\
{\
	fprintf(stderr, "test " #f " failed !\n");\
	exit(1);\
}

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

    triangle_vertex_t* vert = malloc(sizeof(triangle_vertex_t));


    float angle = 0;

    for(;;)
    {
        float x = 400 + cos(angle) * 400;
        float y = 400 + sin(angle) * 400;

        draw_context_clear(context, black);

        draw_rectangle_wireframe(context, triangle, cam, red);

        test(test_green_light_v3_mesh);
        fprintf(stdout, "%d tests executed\n", tests_counter);

        draw_line_bresenham(context, 400, 300, x, y, yellow); //works

        angle += 0.01f;

        draw_context_blit(context);
    }
    draw_context_destroy(context);
}

int test_v3(mesh_vec3_t v, float x, float y, float z) 
{
	if (v.x == x && v.y == y && v.z == z)
		return 0;
	return -1;
}

int test_green_light_v3_mesh()
{
    mesh_vec3_t v3;
	if (mesh_parse_vec3("1 2 3", 3, &v3))
		return -1;
	return test_v3(v3, 1, 2, 3);
}

