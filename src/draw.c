
#include "../include/draw.h"
#include "../include/quaternion.h"
#include "../include/math.h"
#include "../include/camera.h"
#include "../include/triangle.h"
#include "../include/objparser.h"

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

draw_context_t *draw_context_new(const char *title, unsigned int width, unsigned int height)
{
    draw_context_t *context = malloc(sizeof(draw_context_t));
    if (!context)
        return NULL;

    SDL_Init(SDL_INIT_VIDEO); 

    context->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    if(!context->window)
    {
        SDL_Quit();
        free(context);
        return NULL;
    }

    context->renderer = SDL_CreateRenderer(context->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!context->renderer)
    {
        SDL_DestroyWindow(context->window);
        SDL_Quit();
        free(context);
        return NULL;
    }

    context->delta_time      = 0;
    context->width           = width;
    context->height          = height;
    context->half_width      = width / 2.0f;
    context->half_height     = height / 2.0f;
    context->aspect_ratio    = (float)width / (float)height;
    context->last = SDL_GetPerformanceCounter();

    return context;
}

void draw_context_destroy(draw_context_t *context)
{
    SDL_DestroyRenderer(context->renderer);
   
    SDL_DestroyWindow(context->window);

    SDL_Quit();

    free(context);
}

void draw_context_blit(draw_context_t *context)
{
    SDL_RenderPresent(context->renderer);
    unsigned long long now = SDL_GetPerformanceCounter();
    context->delta_time = (float)(now - context->last) / SDL_GetPerformanceFrequency();
    context->last = now;
}

void draw_context_clear(draw_context_t *context, draw_color_t color)
{
    SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(context->renderer);
}

void draw_context_put_pixel(draw_context_t *context, int x, int y, draw_color_t color)
{
    SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(context->renderer, x, y);
}

void draw_line_bresenham(draw_context_t* context, int x1, int y1, int x2, int y2, draw_color_t color)
{
    int sx;
    int sy;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    if(x1 < x2)
        sx = 1;
    else
        sx = -1;

    if(y1 < y2)
        sy = 1;
    else
        sy = -1;

    int err = dx - dy;

    for(;;)
    {
        draw_context_put_pixel(context, x1, y1, color);

        if(x1 == x2 && y1 == y2)
            break;
        
        int err2 = err * 2;
        if(err2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if(err2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

float Sign(vec3_t p1, vec3_t p2, vec3_t p3)
{
    return (p1.x - p3.x)*(p2.y - p3.y) - (p2.x - p3.x ) * (p1.y - p3.y);
}

int PointInTriangle(vec3_t pt, vec3_t v1, vec3_t v2, vec3_t v3)
{
    float b1, b2, b3;

    b1 = Sign(pt, v1, v2) < 0;
    b2 = Sign(pt, v2, v3) < 0;
    b3 = Sign(pt, v3, v1) < 0;

    if((b1 == b2) && (b2 == b3))
        return 0;

    return -1;
}

void RasterizationBoundingBox(vec3_t v1, vec3_t v2, vec3_t v3, draw_context_t* context, draw_color_t color)
{
    int maxX = (int)MAX(v1.x, MAX(v2.x, v3.x));
    int minX = (int)MIN(v1.x, MIN(v2.x, v3.x));
    int maxY = (int)MAX(v1.y, MAX(v2.y, v3.y));
    int minY = (int)MIN(v1.y, MIN(v2.y, v3.y));

    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            vec3_t point =  create_vec3(x, y, 0);

            if (!PointInTriangle(point, v1, v2, v3))
            {
                draw_context_put_pixel(context, (int)x, (int)y, color);
            }
        }
    }
}