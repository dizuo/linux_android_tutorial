#include <stdio.h>
#include <stdlib.h>

#include "list-app.h"

node_ptr_t list_create(dat_t d)
{
	node_ptr_t n = (node_ptr_t)malloc(sizeof(node_t));
	n->next = 0;
	n->data = d;
	return n;
}

void list_destroy(node_ptr_t* head)
{
	while (*head)
	{
		node_ptr_t n = *head;
		free(n);
		n = 0;

		*head = (*head)->next;
	}
}

void list_traverse(node_ptr_t head, list_trav_ft pfunc)
{
	while (head)
	{
		pfunc(head);
		head = head->next;
	}
}

void list_insert(node_ptr_t head, dat_t d)
{
	if (!head)
	{
		return;
	}

	node_ptr_t last_node = 0;
	while (head)
	{
		last_node = head;
		head = head->next;
	}

	last_node->next = list_create(d);
}

void list_insert_sort(node_ptr_t head, dat_t d, list_cmp_ft pfunc)
{
	node_ptr_t curp = 0;

	while (head && pfunc(head->data,d) < 0)
	{
		curp = head;
		head = head->next;
	}

	node_ptr_t n = list_create(d);
	curp->next = n;
	n->next = head;
}

void list_reverse(node_ptr_t head)
{
	// empty, only head node, only one useful node.
	if (!head || !head->next || !head->next->next)
	{
		return;
	}

	node_ptr_t curp = head->next->next;
	head->next->next = 0;

	while (curp)
	{
		node_ptr_t tmp = curp->next;

		curp->next = head->next;
		head->next = curp;

		curp = tmp;
	}

}

