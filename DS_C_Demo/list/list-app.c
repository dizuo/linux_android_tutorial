#include <stdio.h>
#include <stdlib.h>

#include "list-app.h"

// 去掉哨兵头结点
// 20140519 *head 和 head 混淆编译能通过，但是结果就。

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
    *head = NULL;
}

void list_traverse(node_ptr_t* head, list_trav_ft pfunc)
{
    node_ptr_t curp = *head;
	while (curp)
	{
		pfunc(curp);
		curp = curp->next;
	}
}

void list_insert(node_ptr_t* head, dat_t d)
{
	if (!(*head))
	{
        *head = list_create(d);
		return;
	}

	node_ptr_t last_node = 0;
    node_ptr_t curp = *head;
    
	while (curp)
	{
		last_node = curp;
		curp = curp->next;
	}

	last_node->next = list_create(d);
}

void list_insert_sort(node_ptr_t* head, dat_t d, list_cmp_ft pfcmp)
{
	node_ptr_t lastp = 0;
    node_ptr_t curp = *head;
    
	while (curp && pfcmp(curp->data,d) < 0)
	{
		lastp = curp;
        curp = curp->next;
	}

	node_ptr_t n = list_create(d);
	n->next = curp;
    
    if (lastp)
    {
        lastp->next = n;
    }
    else
    {
        *head = n;
    }
}

// ================================================================================
// ================================================================================

int list_erase_node(node_ptr_t* head, dat_t pval, list_cmp_ft pfcmp)
{
    if (!(*head) || !pval)
    {
        return -1;
    }
    
    node_ptr_t lastp = 0, curp = *head;
    while (curp && pfcmp(curp->data,pval) != 0)
    {
        lastp = curp;
        curp = curp->next;
    }
    
    if (!curp)
    {
        return -2;
    }
    
    if (lastp)
    {
        lastp->next = curp->next;
    }
    else
    {
        *head = curp->next;
    }
    
    free(curp);
    
    return 0;
}

void list_reverse(node_ptr_t* head)
{
	// empty, only head node.
	if (!*head || !(*head)->next)
	{
		return;
	}
    
    // 链表打成 前后两部分！
    node_ptr_t curp = (*head)->next;
    (*head)->next = 0;
    
    while (curp)
    {
        node_ptr_t locp = curp->next;
        
        curp->next = (*head);
        (*head) = curp;
        
        curp = locp;
    }

}

