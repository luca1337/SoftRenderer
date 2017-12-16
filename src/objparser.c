#include "../include/objparser.h"
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include "../include/databuffer.h"
#include "../include/triangle.h"
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

#define SIZE 4

#ifdef __cplusplus
  #include <cstring>
  #define STD(x) std::x
  namespace std {
#else
  #include <string.h>
  #define STD(x) x
#endif

char* strsep( char** stringp, const char* delim )
{
char* result;

if ((stringp == NULL) || (*stringp == NULL)) return NULL;

result = *stringp;

while (**stringp && !STD(strchr)( delim, **stringp )) ++*stringp;

if (**stringp) *(*stringp)++ = '\0';
else             *stringp    = NULL;

return result;
}

list_t* create_list()
{
    list_t* list = malloc(sizeof(list_t));
    if(!list)
        return NULL;
    list = memset(list,0,sizeof(list_t));
    return list;
}
list_item_t* create_list_item(void* data) //take data
{
    list_item_t* item = malloc(sizeof(list_item_t));
    if(!item)
        return NULL;
    item->item = data; 
    return item;
}
void list_append2(list_t* list, void* item)
{
    list_item_t* _item = create_list_item(item);
    if (list->head == NULL) //list is empty
    {
        list->head = _item;
        list->tail = _item;
    }
    else
    {
        list->tail->next = _item;
        _item->prev = list->tail;
        list->tail = _item;
    }
}
list_item_t* get_item_at_index(list_t* list,int index)
{
    list_item_t* item = list->head;
    int counter = 0;
    while(item)
    {
        if(counter == index)
            return item;
        item = item->next;
        counter++;
    }
    // free(item);
    return NULL;
}
int list_len2(list_t list)
{
    list_item_t* item = list.head;
    int counter = 0;
    while(item)
    {
        counter++;
        item = item->next;
    }
    return counter;
}
int mesh_triangles_count(mesh_t mesh)
{
    triangle_t* t = mesh.head;
    int counter = 0;
    while(t)
    {
        counter++;
        t = t->next;
    }
    return counter;
}

mesh_t* mesh_create()
{
    mesh_t* mesh = malloc(sizeof(mesh_t));
    return mesh;
}

mesh_t* mesh_destroy(mesh_t* mesh)
{
    if(mesh->v)     free(mesh->v);
    if(mesh->uv)    free(mesh->uv);
    if(mesh->n)     free(mesh->n);
    if(mesh->f)     free(mesh->f);
    if(mesh)        free(mesh);
}

void mesh_init(mesh_t* mesh)
{
    mesh->v = NULL;
    mesh->uv = NULL;
    mesh->n = NULL;
    mesh->f = NULL;
    mesh->position = create_vec3(0, 0, 0);
    mesh->scale = create_vec3(0.2, 0.2, 0.2);
    mesh->rot = doge_quat_create(0, 0, 0, 1);
}

mesh_t* parse_obj(char* _arg)
{
    //to return
    mesh_t* my_mesh = malloc(sizeof(mesh_t));
    memset(my_mesh,0,sizeof(mesh_t));


    FILE* file;
    file=fopen(_arg,"rb");
    char* line = malloc(128);
    int buffer_size = 128;
    list_t* all_points_of_mesh = create_list(); 
    list_t* all_normals_of_mesh = create_list();
    list_t* all_uv_of_mesh = create_list();

    while(file)
    {
        if(!fgets(line,buffer_size,file))
            break;
        
        char *original_line = line;
        char** token = &original_line;
        char* item;

        int is_f = 0;
        int is_v = 0;
        int is_vn = 0;
        int is_vt = 0; //uv coords

        list_t* float_for_vector = create_list();
        list_t* list_3_vec_index = create_list(); //int
        //new list floatindex normal (3)
        list_t* list_3_normal_index = create_list();
        //new list floatindex uv (2)
        list_t* list_3_uv_index = create_list();

        static int added = 0;
        while(1)
        {
            item = strtok(token, " ");
            item = strtok(NULL, " ");
            if(!strcmp("f",item)) //is the start of an f line (next 3 elements must be splitted for "/" and the first may be taked)
            {
                is_f = 1;
                is_v = 0;
                is_vn = 0;
                is_vt = 0;
                continue;                    
            }
            else if(!strcmp("v", item)) //is the start of an v line (next 3 elements are float of vector)
            {
                is_v = 1;
                is_f = 0;
                is_vn = 0;
                is_vt = 0;
                continue;                    
            }
            else if(!strcmp("vn",item))
            {
                is_v = 0;
                is_f = 0;
                is_vn = 1;
                is_vt = 1;
            }
            else if(!strcmp("vt", item))
            {
                is_v = 0;
                is_f = 0;
                is_vn = 0;
                is_vt = 1;
            }
            else
            {
                if(is_v)
                {
                    float* value = malloc(sizeof(float)); 
                    *value = (float)atof(item); //transform string into floating point number
                    // fprintf(stdout,"added point %f when item is %s\n",*value, item);
                    list_append(float_for_vector,value); //add to my list
                }
                if(is_vn)
                {
                    float* value = malloc(sizeof(float)); 
                    // fprintf(stdout,"%s \n",item);
                    *value = (float)atof(item); //transform string into floating point number
                    // fprintf(stdout,"added point %f when item is %s\n",*value, item);
                    list_append(float_for_vector,value); //add to my normal list
                }
                if(is_vt)
                {
                    float* value = malloc(sizeof(float)); 
                    *value = (float)atof(item); //transform string into floating point number
                    // fprintf(stdout,"added point %f when item is %s\n",*value, item);
                    list_append(float_for_vector,value); //add to my normal list
                }
                if(is_f)
                {
                    char** line_copy = &item;
                    // fprintf(stdout,"line copied \n");
                    char* index_vertex = strsep(line_copy,"/");  //get first element
                    // fprintf(stdout,"line splited and return value %s \n",index);
                    int* n_index_vertex = malloc(sizeof(int));
                    *n_index_vertex = (atoi(index_vertex)); //convert to integer 
                    // fprintf(stdout,"transformed in value %d \n",*n_index);

                    char* index_uv = strsep(line_copy,"/");
                    int* n_index_uv = malloc(sizeof(int));
                    *n_index_uv = (atoi(index_uv));


                    char* index_normal = strsep(line_copy,"/");
                    int* n_index_normal = malloc(sizeof(int));
                    *n_index_normal = (atoi(index_normal));
                    
                    list_append(list_3_vec_index,n_index_vertex); //add to list
                    list_append(list_3_uv_index,n_index_uv);
                    list_append(list_3_normal_index,n_index_normal);
                }
            }
        }
        //create vector and add to point list
        if(is_v)
        {
            static int counter;
            
            struct doge_vec3* v = malloc(sizeof(struct doge_vec3)); 
            if(!v) return NULL;
            *v = create_vec3(*((float*)float_for_vector->head->item),*((float*)float_for_vector->head->next->item),*((float*) float_for_vector->head->next->next->item)*-1);     
            list_append(all_points_of_mesh,v);
            fprintf(stdout,"normal %d = %f %f %f\n",++counter,*((float*)float_for_vector->head->item),*((float*)float_for_vector->head->next->item),*((float*) float_for_vector->head->next->next->item)*-1);   
            
        }
        if(is_vn)
        {
            static int counter;
            struct doge_vec3* v = malloc(sizeof(struct doge_vec3)); 
            if(!v) return NULL;
            *v = create_vec3(*((float*)float_for_vector->head->item),*((float*)float_for_vector->head->next->item),*((float*) float_for_vector->head->next->next->item)*-1);     
            list_append(all_normals_of_mesh,v);     
            // fprintf(stdout,"normal %d = %f %f %f\n",++counter,v->x,v->y,v->z);   
        }
        if(is_vt)
        {
            struct doge_vec2* v = malloc(sizeof(struct doge_vec2)); 
            if(!v) return NULL;
            *v = create_vec2(*((float*)float_for_vector->head->item),*((float*)float_for_vector->head->next->item));     
            list_append(all_uv_of_mesh,v);  
        }
        if(is_f)
        {
            //create triangle 
            int first_index = *(int*)get_item_at_index(list_3_vec_index,0)->item;
            int second_index = *(int*)get_item_at_index(list_3_vec_index,1)->item;
            int third_index = *(int*)get_item_at_index(list_3_vec_index,2)->item;
            
            vec3_t v1_pos = *(struct doge_vec3*)(get_item_at_index(all_points_of_mesh,first_index-1)->item); //p1 point
            vec3_t v2_pos = *(struct doge_vec3*)(get_item_at_index(all_points_of_mesh,second_index-1)->item); //p2 point
            vec3_t v3_pos = *(struct doge_vec3*)(get_item_at_index(all_points_of_mesh,third_index-1)->item);

            vec3_t v1_norm = *(struct doge_vec3*)(get_item_at_index(all_normals_of_mesh,first_index-1)->item);
            vec3_t v2_norm = *(struct doge_vec3*)(get_item_at_index(all_normals_of_mesh,second_index-1)->item);
            vec3_t v3_norm = *(struct doge_vec3*)(get_item_at_index(all_normals_of_mesh,third_index-1)->item);
            
            vec2_t v1_uv = *(vec2_t*)(get_item_at_index(all_uv_of_mesh,first_index-1)->item);
            vec2_t v2_uv = *(vec2_t*)(get_item_at_index(all_uv_of_mesh,second_index-1)->item);
            vec2_t v3_uv = *(vec2_t*)(get_item_at_index(all_uv_of_mesh,third_index-1)->item);

            triangle_t* t = triangle_create(create_vertex(v1_pos,v1_norm,v1_uv), create_vertex(v2_pos,v2_norm,v2_uv), create_vertex(v3_pos,v3_norm,v3_uv));
            
            //use meshaddtriangle
            mesh_add_triangle(my_mesh,t);
            // fprintf(stdout," triangle added to mesh  %f/%f/%f %f/%f/%f %f/%f/%f\n",t.a.x,t.a.y,t.a.z,t.b.x,t.b.y,t.b.z,t.c.x,t.c.y,t.c.z);
            
        }
        
        free(float_for_vector);
        free(list_3_vec_index);
        free(list_3_normal_index);
        free(list_3_uv_index);
        
    }
    //free all_points_of_mesh
    fclose(file);
    return my_mesh;
}