#include "../include/quaternion.h"
#include "../include/triangle.h"
#include "../include/camera.h"
#include "../include/draw.h"
#include "../include/vertex.h"
#include "../include/math.h"
#include "../include/objparser.h"

static float fovy;

static vertex_t a;
static vertex_t b;
static vertex_t c;

triangle_t* triangle_create(vertex_t a, vertex_t b, vertex_t c)
{
    triangle_t* t = malloc(sizeof(triangle_t));
    if(!t)return NULL;
    t->a = a;
    t->b = b;
    t->c = c;
    return t;
}

triangle_t* triangle_create_vert(vertex_t a, vertex_t b, vertex_t c)
{
    triangle_vertex_t* t = malloc(sizeof(triangle_vertex_t));
    if(!t)return NULL;
    t->a = a;
    t->b = b;
    t->c = c;
    return t;
}

void draw_rectangle_wireframe(draw_context_t* context, triangle_t t, camera_t* cam, draw_color_t color)
{
    // fovy = cam->fov_y * (DOGE_PI / 180);

    // float yp1 = t.a.y / (t.a.z * tan(fovy / 2));
    // float xp1 = t.a.x / (t.a.z * tan(fovy / 2));
    // draw_context_put_pixel(context, (xp1 * context->half_width + context->half_width),
    //  (-yp1 * context->half_height + context->half_height), color);

    // float yp2 = t.b.y / (t.b.z * tan(fovy /2));
    // float xp2 = t.b.y / (t.b.z * tan(fovy /2));
    // draw_context_put_pixel(context, (xp2 * context->half_width + context->half_width),
    //  (-yp2 * context->half_height + context->half_height), color);

    // float yp3 = t.c.y / (t.c.z * tan(fovy /2));
    // float xp3 = t.c.y / (t.c.z * tan(fovy /2));
    // draw_context_put_pixel(context, (xp3 * context->half_width + context->half_width),
    //  (-yp3 * context->half_height + context->half_height), color);

    // draw_line_bresenham(context, (xp1 * context->half_width + context->half_width),
    //  (-yp1 * context->half_height + context->half_height), (xp2 * 400 + 400),
    //   (-yp2 * context->half_height + context->half_height), color);

    // draw_line_bresenham(context, (xp2 * context->half_width + context->half_width),
    //  (-yp2 * context->half_height + context->half_height), (xp3 * 400 + 400), 
    //  (-yp3 * context->half_height + context->half_height), color);

    // draw_line_bresenham(context, (xp3 * context->half_width + context->half_width),
    //  (-yp3 * context->half_height + context->half_height), (xp1 * 400 + 400),
    //   (-yp1 * context->half_height + context->half_height), color);

}

void draw_context_mesh_draw(draw_context_t* context, struct mesh* meshs, camera_t cam, draw_color_t color)
{
    static int i = 0;
    while(i < meshs->f->count)
    {
        i++;
        // mesh_draw(cam, t, context, meshs->position, meshs->rot, meshs->scale, color);
    }
}

//triangle_vertex_t it's a triangle with inside 3 vertex so it's the updated version of triangle_t
void mesh_draw(camera_t cam, triangle_t vertex, draw_context_t* context, vec3_t position, doge_quat_t rotation, vec3_t scale, draw_color_t color)
{
    proj(cam, &vertex.a, position, rotation, scale);
    proj(cam, &vertex.b, position, rotation, scale);
    proj(cam, &vertex.c, position, rotation, scale);

    vertex_t p1 = vertex.a;
    vertex_t p2 = vertex.b;
    vertex_t p3 = vertex.c;

    if (p2.world_proj_pos.y < p1.world_proj_pos.y)
    {
        vertex_t tmp = p1;
        p1 = p2;
        p2 = tmp;
    }

    if (p3.world_proj_pos.y < p2.world_proj_pos.y)
    {
        vertex_t tmp = p2;
        p2 = p3;
        p3 = tmp;
    }

    if (p2.world_proj_pos.y < p1.world_proj_pos.y)
    {
        vertex_t tmp = p1;
        p1 = p2;
        p2 = tmp;
    }

    float iSlopeP1P2 = (p2.world_proj_pos.x - p1.world_proj_pos.x) / (p2.world_proj_pos.y - p1.world_proj_pos.y);
    float iSlopeP1P3 = (p3.world_proj_pos.x - p1.world_proj_pos.x) / (p3.world_proj_pos.y - p1.world_proj_pos.y);

    if (iSlopeP1P2 < iSlopeP1P3)
    {
        for (int y = (int)p1.world_proj_pos.y; y <= (int)p3.world_proj_pos.y; y++)
        {
            if (y < p2.world_proj_pos.y)
            {
                Scanline(context, y, p1, p2, p1, p3, color);
            }
            else
            {
                Scanline(context, y, p2, p3, p1, p3, color);
            }
        }
    }
    else
    {
        for (int y = (int)p1.world_proj_pos.y; y <= (int)p3.world_proj_pos.y; y++)
        {
            if (y < p2.world_proj_pos.y)
            {
                Scanline(context, y, p1, p3, p1, p2, color);
            }
            else
            {
                Scanline(context, y, p1, p3, p2, p3, color);
            }
        }
    }
}

void Scanline(draw_context_t* context, int y, vertex_t leftA, vertex_t leftB, vertex_t rightA, vertex_t rightB, draw_color_t color)
{
    float leftGradient = (y - leftA.world_proj_pos.y) / (leftB.world_proj_pos.y - leftA.world_proj_pos.y);
    float rightGradient = (y - rightA.world_proj_pos.y) / (rightB.world_proj_pos.y - rightA.world_proj_pos.y);

    // singularity 
    if (leftA.world_proj_pos.y == leftB.world_proj_pos.y)
        leftGradient = 1;

    if (rightA.world_proj_pos.y == rightB.world_proj_pos.y)
        rightGradient = 1;

    // compute left pixel and right pixel using gradient
    float leftX = interpolate_float(leftA.world_proj_pos.x, leftB.world_proj_pos.x, leftGradient);
    float rightX = interpolate_float(rightA.world_proj_pos.x, rightB.world_proj_pos.x, rightGradient);

    // compute the z for the DepthBuffer
    float leftZ = interpolate_float(leftA.world_view_pos.z, leftB.world_view_pos.z, leftGradient);
    float rightZ = interpolate_float(rightA.world_view_pos.z, rightB.world_view_pos.z, rightGradient);

    // pixel world position
    vec3_t leftWorld = interpolate_vec3(leftA.world_pos, leftB.world_pos, leftGradient);
    vec3_t rightWorld = interpolate_vec3(rightA.world_pos, rightB.world_pos, rightGradient);

    // pixel normal
    vec3_t leftNormal = interpolate_vec3(leftA.world_normal, leftB.world_normal, leftGradient);
    vec3_t rightNormal = interpolate_vec3(rightA.world_normal, rightB.world_normal, rightGradient);

    // compute pixel UV
    // vec3_t uvLeft = interpolate_vec3(leftA.uv, leftB.uv, leftGradient);
    // vec3_t uvRight = interpolate_vec3(rightA.uv, rightB.uv, rightGradient);

    // compute pixel in camera/eye space
    vec3_t leftWorldEye = interpolate_vec3(leftA.world_view_pos, leftB.world_view_pos, leftGradient);
    vec3_t rightWorldEye = interpolate_vec3(rightA.world_view_pos, rightB.world_view_pos, rightGradient);

    // fill pixels managing light

    for (int x = (int)leftX; x < (int)rightX; x++)
    {
        float xGradient = (x - leftX) / (float)(rightX - leftX);

        vec3_t pixel_world = interpolate_vec3(leftWorld, rightWorld, xGradient);
        vec3_t pixel_world_eye = interpolate_vec3(leftWorldEye, rightWorldEye, xGradient);
        vec3_t pixel_normal = interpolate_vec3(leftNormal, rightNormal, xGradient);

        draw_context_put_pixel(context, x, y, color);
    }
}

void iterator_mesh(struct mesh* mesh, triangle_vrtx_2_t* triangle, int* face)
{
    int i = *face;
    int fv1 = mesh->f->element[i];
    int fn1 = mesh->f->element[i + 1];
    int fuv1 = mesh->f->element[i + 2];

    int fv2 = mesh->f->element[i + 3];
    int fn2 = mesh->f->element[i + 4];
    int fuv2 = mesh->f->element[i + 5];

    int fv3 = mesh->f->element[i + 6];
    int fn3 = mesh->f->element[i + 7];
    int fuv3 = mesh->f->element[i + 8];

    triangle->v[0].v = create_vec3(mesh->v->element[3 * fv1], mesh->v->element[3 * fv1 + 1], mesh->v->element[3 * fv1 + 2]);
    triangle->v[0].n = create_vec3(mesh->n->element[3 * fn1], mesh->n->element[3 * fn1 + 1], mesh->n->element[3 * fn1 + 2]);
    triangle->v[0].uv = create_vec2(mesh->uv->element[2 * fuv1], mesh->uv->element[2 * fuv1 + 1]);

    triangle->v[1].v = create_vec3(mesh->v->element[3 * fv2], mesh->v->element[3 * fv2 + 1], mesh->v->element[3 * fv2 + 2]);
    triangle->v[1].n = create_vec3(mesh->n->element[3 * fn2], mesh->n->element[3 * fn2 + 1], mesh->n->element[3 * fn2 + 2]);
    triangle->v[1].uv = create_vec2(mesh->uv->element[2 * fuv2], mesh->uv->element[fuv2 + 1]);

    triangle->v[2].v = create_vec3(mesh->v->element[3 * fv3], mesh->v->element[3 * fv3 + 1], mesh->v->element[3 * fv3 + 2]);
    triangle->v[2].n = create_vec3(mesh->n->element[3 * fn3], mesh->n->element[3 * fn3 + 1], mesh->n->element[3 * fn3 + 2]);
    triangle->v[2].uv = create_vec2(mesh->uv->element[2 * fuv1], mesh->uv->element[2 * fuv1 + 1]);

    *face += 9;
}

void mesh_add_triangle(struct mesh* mesh,triangle_t* t)
{
    if (mesh->head == NULL)
    {
        mesh->head = t;
        mesh->tail = t;
    }
    else
    {
        mesh->tail->next = t;
        t->prev = mesh->tail;
        mesh->tail = t;
    }
    t->owner = mesh;
}