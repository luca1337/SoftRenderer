#ifndef OBJPARSER_H
#define OBJPARSER_H

#include "databuffer.h"
#include "quaternion.h"
#include "triangle.h"

typedef struct mesh
{
	data_buffer_f_t* v;
	data_buffer_f_t* uv;
	data_buffer_f_t* n;

	data_buffer_f_t* f;

	vec3_t position;
	doge_quat_t rot;
	vec3_t scale;

	struct triangle* head;
    struct triangle* tail;

}mesh_t;

typedef struct list_item
{
    void* item;
    struct list_item* next;
    struct list_item* prev;
    
} list_item_t;
typedef struct list
{
    list_item_t* head;
    list_item_t* tail;
} list_t;

mesh_t* mesh_create();
mesh_t* mesh_destroy(mesh_t*);
void mesh_init(mesh_t*);
mesh_t* parse_obj(char*);

list_t* create_list();
list_item_t* get_item_at_index(list_t*,int);
list_item_t* create_list_item(void*); //take data
void list_append2(list_t*, void*);
int list_len2(list_t);

#endif