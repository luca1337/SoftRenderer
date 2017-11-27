#ifndef DRAW_H
#define DRAW_H

#define SDL_MAIN_HANDLED 1

#include <string.h>
#include <stdlib.h>
#include "SDL/SDL.h"

struct draw_context
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    unsigned int width;
    unsigned int height;
    float delta_time;
    float aspect_ratio;
    unsigned long long last;
    unsigned int half_width;
    unsigned int half_height;
};

typedef struct draw_context draw_context_t;

struct draw_color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

typedef struct draw_color draw_color_t;

draw_context_t *draw_context_new(const char *, unsigned int, unsigned int);
void draw_context_destroy(draw_context_t *);
void draw_context_blit(draw_context_t *);
void draw_context_clear(draw_context_t *, draw_color_t);
void draw_context_put_pixel(draw_context_t *, int, int, draw_color_t);
void draw_line_bresenham(draw_context_t*, int, int, int, int, draw_color_t);

#endif