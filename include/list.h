#pragma once

#include <string.h>
#include <stdlib.h>

typedef struct list_item
{
    struct list_item *prev;
    struct list_item *next;
    void *data;
}list_item_t;

typedef struct list
{
    struct list_item *head;
    struct list_item *tail;
    int is_iterating;
    unsigned int count;
}list_t;

// create a new list
list_t *list_new(int *);

void list_destroy(list_t *);
// append a new element to the list

int list_append(list_t *, void *);
// append a new element to the list (unique version)

int list_append_uniq(list_t *, void *);
// remove the specified element from the list

int list_remove(list_t *, void *);
// remove the element at the specified index

int list_remove_index(list_t *, unsigned int);
// insert an element in the specified position

int list_insert(list_t *, unsigned int, void *);
// insert an element in the specified position (unique version)

int list_insert_uniq(list_t *, unsigned int, void *);
// iterator pattern

list_item_t *list_iter(list_t *, list_item_t **);
// check if the list contains the item

int list_contains(list_t *, void *);
// check if the list contains the specified item at the specified index

int list_contains_at(list_t *, void *, unsigned int);
// get the length of the list (optimized version)

int list_len(list_t *);
// get the length of the list (slow version)

int list_slow_len(list_t *);
// shuffle the list

void list_shuffle(list_t *);
// sort the list (if the sort func is NULL order by the address of the element)

// the sort function returns 0 on equality, -1 if the left arg wins, 1 for the second one
void list_sort(list_t *, int (*)(void *, void *));

// reverse the list
void list_reverse(list_t *);

// return a new list (copy) with the item starting from the specified item
list_t *list_sublist(list_t *, unsigned int, int *);

int list_init(list_t *, int *);

void **list_to_array(list_t *, int *);