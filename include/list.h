#pragma once

#include <string.h>
#include <stdlib.h>

typedef struct aiv_list_item
{
    struct aiv_list_item *prev;
    struct aiv_list_item *next;
    void *data;
}aiv_list_item_t;

typedef struct aiv_list
{
    struct aiv_list_item *head;
    struct aiv_list_item *tail;
    int is_iterating;
    unsigned int count;
}aiv_list_t;

// create a new list
aiv_list_t *aiv_list_new(int *);

void aiv_list_destroy(aiv_list_t *);
// append a new element to the list

int aiv_list_append(aiv_list_t *, void *);
// append a new element to the list (unique version)

int aiv_list_append_uniq(aiv_list_t *, void *);
// remove the specified element from the list

int aiv_list_remove(aiv_list_t *, void *);
// remove the element at the specified index

int aiv_list_remove_index(aiv_list_t *, unsigned int);
// insert an element in the specified position

int aiv_list_insert(aiv_list_t *, unsigned int, void *);
// insert an element in the specified position (unique version)

int aiv_list_insert_uniq(aiv_list_t *, unsigned int, void *);
// iterator pattern

aiv_list_item_t *aiv_list_iter(aiv_list_t *, aiv_list_item_t **);
// check if the list contains the item

int aiv_list_contains(aiv_list_t *, void *);
// check if the list contains the specified item at the specified index

int aiv_list_contains_at(aiv_list_t *, void *, unsigned int);
// get the length of the list (optimized version)

int aiv_list_len(aiv_list_t *);
// get the length of the list (slow version)

int aiv_list_slow_len(aiv_list_t *);
// shuffle the list

void aiv_list_shuffle(aiv_list_t *);
// sort the list (if the sort func is NULL order by the address of the element)

// the sort function returns 0 on equality, -1 if the left arg wins, 1 for the second one
void aiv_list_sort(aiv_list_t *, int (*)(void *, void *));

// reverse the list
void aiv_list_reverse(aiv_list_t *);

// return a new list (copy) with the item starting from the specified item
aiv_list_t *aiv_list_sublist(aiv_list_t *, unsigned int, int *);

int aiv_list_init(aiv_list_t *, int *);

void **aiv_list_to_array(aiv_list_t *, int *);