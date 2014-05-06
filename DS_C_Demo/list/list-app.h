#ifndef LIST_APP_201405061520_H
#define LIST_APP_201405061520_H

typedef int dat_t;

typedef struct list_node
{
	dat_t data;
	struct list_node* next;
} node_t;

typedef node_t* node_ptr_t;

typedef void (*list_trav_ft)(node_ptr_t);
typedef int (*list_cmp_ft)(dat_t, dat_t);

node_ptr_t list_create(dat_t d);

void list_insert(node_ptr_t head, dat_t d);

void list_insert_sort(node_ptr_t head, dat_t d, list_cmp_ft pfunc);

void list_traverse(node_ptr_t head, list_trav_ft pfunc);

void list_reverse(node_ptr_t head);

void list_destroy(node_ptr_t* head);

#endif
