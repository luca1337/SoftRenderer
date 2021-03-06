#include<stdlib.h>
#include<stdio.h>
#include "../include/list.h"
#include "../include/error.h"


list_t *list_new(int *err_code)
{
    if (err_code)
        *err_code = AIV_OK;
    list_t *list = malloc(sizeof(list_t));
    if (!list) 
    {
        if (err_code)
            *err_code = AIV_NO_MEM;
        return NULL;
    }
    memset(list, 0, sizeof(list_t));
    return list;
}

int list_init(list_t *list, int *err_code)
{
    if (err_code)
        *err_code = AIV_OK;
    memset(list, 0, sizeof(list_t));
    return 0;
}

int list_append(list_t *list, void *element)
{
    list_item_t *list_item = malloc(sizeof(list_item_t));
    if (!list_item)
    {
        return AIV_NO_MEM;
    }
    list_item->prev = list->tail;
    list_item->next = NULL;
    list_item->data = element;

    if (list_item->prev)
    {
        list_item->prev->next = list_item;
    }

    if (!list->head)
    {
        list->head = list_item;
    }

    list->tail = list_item;

    list->count++;

    return AIV_OK;
}

void list_destroy(list_t *list)
{
    list_item_t *item = list->head;
    while(item)
    {
        list_item_t *next = item->next;
        free(item);
        item = next; 
    }
    free(list);
}

int list_remove(list_t *list, void *element)
{
    list_item_t *item = list->head;
    while(item)
    {
        if(element == item->data)
        {
            if(item == list->head)
            {
                list->head = item->next;
            }

            if(item == list->tail)
            {
                list->tail = item->prev;
            }

            if(item->prev)
            {
                item->prev->next = item->next;
            }

            if(item->next)
            {
                item->next->prev = item->prev;
            }

            free(item);

            list->count--;

            return AIV_OK;
        }
        item = item->next;
         
    }
    return AIV_NOT_FOUND;
}

int list_remove_index(list_t *list, unsigned int index)
{
    unsigned int counter = 0;
    list_item_t *item = list->head;
    while(item)
    {
        if(counter == index)
        {
            if(item == list->head)
            {
                list->head = item->next;
            }

            if(item == list->tail)
            {
                list->tail = item->prev;
            }

            if(item->prev)
            {
                item->prev->next = item->next;
            }

            if(item->next)
            {
                item->next->prev = item->prev;
            }

            free(item);

            list->count--;
            
            return AIV_OK;
        }
        counter++;
        item = item->next;
    }
    return AIV_NOT_FOUND;
}

list_item_t *list_iter(list_t *list, list_item_t **context)
{
    if (list->is_iterating && !*context) {
        list->is_iterating = 0;
        return NULL;
    }
    
    if (!*context) {
        list->is_iterating = 1;
        *context = list->head;
        return *context;
    }

    *context = (*context)->next;
    return *context;
}

int list_append_uniq(list_t *list, void *element)
{
    list_item_t *current = list->head;
    while(current)
    {
        if(current->data == element)
        {
            return AIV_NOT_UNIQUE;
        }
        current = current->next;
    }

    list_item_t *list_item = malloc(sizeof(list_item_t));
    if (!list_item)
        return AIV_NO_MEM;

    list_item->prev = list->tail;
    list_item->next = NULL;
    list_item->data = element;

    if (list_item->prev)
    {
        list_item->prev->next = list_item;
    }

    if (!list->head)
    {
        list->head = list_item;
    }

    list->tail = list_item;

    list->count++;
    
    return AIV_OK;

}

int list_insert(list_t *list, unsigned int index, void *element)
{
    unsigned int len = list_len(list);

    if(index > len)
        return AIV_NOT_FOUND;

    if(index == len)
        return list_append(list, element);

    list_item_t *new_item = malloc(sizeof(list_item_t));
    if(!new_item)
        return AIV_NO_MEM;

    new_item->data = element;

    list_item_t **item = &list->head;
    unsigned int counter = 0;

    while(*item)
    {
        if(counter++ == index)
        {
            new_item->next = *item;
            new_item->prev = (*item)->prev;

            if((*item)->prev)
                (*item)->prev->next = new_item;

            (*item)->prev = new_item;
            *item = new_item;

            list->count++;

            return AIV_OK;
        }

        item = &(*item)->next;
    }
    return 0;
}

int list_insert_uniq(list_t *list, unsigned int index, void *element)
{
    int len = list_len(list);

    if(index > len)
        return AIV_NOT_FOUND;
    
    if(index == len)
        return list_append_uniq(list, element);

    list_item_t *new_item = malloc(sizeof(list_item_t));
    if(!new_item)
        return AIV_NO_MEM;

    new_item->data = element;

    list_item_t *item = list->head;
    list_item_t **item_found = NULL;
    unsigned int counter = 0;

    while(item)
    {
        if(item->data == element)
        {
            free(new_item);
            return AIV_NOT_UNIQUE;
        }
        if(counter++ == index)
        {
            item_found = &item;
        }
        item = item->next;
    }

    new_item->next = *item_found;
    new_item->prev = (*item_found)->prev;

    if((*item_found)->prev)
        (*item_found)->prev->next = new_item;

    (*item_found)->prev = new_item;
    *item_found = new_item;

    list->count++;

    return AIV_OK;
}

int list_contains(list_t *list, void *element)
{
    list_item_t *item = list->head;

    while(item)
    {
        if(item->data == element)
            return AIV_OK;

        item = item->next;
    }

    return AIV_NOT_FOUND;
}

int list_contains_at(list_t *list, void *element, unsigned int index)
{
    if(index >= list_len(list))
        return AIV_NOT_FOUND;

    list_item_t *item = list->head;
    unsigned int counter = 0;

    while(item)
    {
        if(index == counter++ && item->data == element)
            return AIV_OK; 

        item = item->next;
    }

    return AIV_NOT_FOUND;
}

int list_len(list_t *list)
{
    return list->count;
}

int list_slow_len(list_t *list)
{
    unsigned int len = 0;

    for(list_item_t *list_item = list->head; list_item; list_item = list_item->next) len++;

    return len;

}

void list_shuffle(list_t *list)
{
    unsigned int len = list_len(list);
    if(len <= 1)
        return;
        
    list_item_t *item  = list->head;
    list_item_t *start = item;

    unsigned int random = (unsigned int)(((double)rand() / RAND_MAX) * len);
    unsigned int i = 0;
    unsigned int j = 0;
    
    while(item)
    {
        if(i++ + j == random)
        {
            j++;
            void *current_data = item->data;
            item->data         = start->data;
            start->data        = current_data;
            start = start->next;
            item = start;
            random = j + (unsigned int)(((double)rand() / RAND_MAX) * (len - j));
            i = 0;
        }
        else
        {
            item = item->next;
        }
    }
}

static int deafult_comparer(void *left, void *right)
{
    //equal
    if(left == right)
        return 0;
    //left must come first
    if(left < right)
        return -1;
    //right must come first
    if(left > right)
        return 1;

    return 0;
}

void list_sort(list_t *list, int (*comparer)(void *, void *))
{
    unsigned int len = list_len(list);
    if(len <= 1)
        return;
        
    list_item_t *item = list->head;

    if(!comparer)
        comparer = deafult_comparer;

    while(len-- > 0)
    {
        for(unsigned int i = 0; i < len; i++)
        {
            if(!item->next)
                break;

            int compare = comparer(item->data, item->next->data);
            if(compare == 1)
            {
                void *current_data = item->data;
                item->data = item->next->data;
                item->next->data = current_data;
            }
            item = item->next;
        }
        item = list->head;
    }
}

void list_reverse(list_t *list)
{
    unsigned int len = list_len(list);

    if(len <= 1)
        return;

    list_item_t *head = list->head;
    list_item_t *tail = list->tail;
    
    while(tail != head)
    {
        void *tail_data = tail->data;
        tail->data = head->data;
        head->data = tail_data;
        
        if(tail->prev == head)
            break;

        tail = tail->prev;
        head = head->next;
    }
}

list_t *list_sublist(list_t *list, unsigned int index, int *err_code)
{
    if(index >= list_len(list))
    {
        if(err_code)
            *err_code = AIV_NOT_FOUND;

        return NULL;
    }

    list_t *sub = list_new(NULL);

    if(!sub)
    {
        if(err_code)
            *err_code = AIV_NO_MEM;

        return NULL;
    }
    
    unsigned int i = 0;

    for(list_item_t *item = list->head; item; item = item->next)
    {
        if(i++ >= index)
        {
            list_append(sub, item->data);
        }
    }

    return sub;
}

void **list_to_array(list_t *list, int *err_code)
{
    if (err_code)
        *err_code = AIV_OK;

    unsigned int len = list_len(list);

    void **array = malloc(sizeof(void *) * len);
    if (!array) 
    {
        if (err_code)
            *err_code = AIV_NO_MEM;
        return NULL;
    }

    unsigned int i = 0;
    list_item_t *copy  = list->head; 

    while(copy)
    {
        array[i++] = copy->data;
        copy = copy->next;
    }

    return array;
}



