
#include "../include/draw.h"

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