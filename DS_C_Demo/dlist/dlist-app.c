#include "dlist-app.h"

#include <stdlib.h>

#define DLIST_CHECH(pnd, flag) 	if (!pnd) { return flag; }

#define REUSE

// 双向循环链表：
// 使用哨兵结点，code非常工整！
// 插入一个结点 需要修改四个指针域，两个外在的和两个自己的。
// 删掉一个结点需要修改两个 外在的指针域。

dlst_nd_pt dlist_create(dat_t pval)
{
	dlst_nd_pt pnd = (dlst_nd_pt)malloc(sizeof(dlst_nd_t));
	pnd->next = pnd;
	pnd->prev = pnd;
	pnd->data = pval;

	return pnd;
}

void dlist_traverse(dlst_nd_pt pdlist, dlst_tra_ft trav_func)
{
	DLIST_CHECH(pdlist, );

	dlst_nd_pt curp = pdlist->next;
	
	trav_func(pdlist);
	
	while (curp != pdlist)
	{
		trav_func(curp);
		curp = curp->next;
	}

}

void dlist_destroy(dlst_nd_pt pdlist)
{
	DLIST_CHECH(pdlist, );

	dlst_nd_pt curp = pdlist->next;

	while (curp != pdlist)
	{
		dlst_nd_pt temp = curp;
		free(temp);

		curp = curp->next;
	}
	
	pdlist->next = pdlist->prev = 0;
	free(pdlist);
}

int dlist_push_back(dlst_nd_pt pdlist, dat_t pval)
{
	DLIST_CHECH(pdlist, -1);

	dlst_nd_pt ptr = (dlst_nd_pt)malloc(sizeof(dlst_nd_t));
	ptr->data = pval;

#ifndef REUSE
	ptr->next = pdlist;
	ptr->prev = pdlist->prev;
	
	pdlist->prev->next = ptr;
	pdlist->prev = ptr;
#else
	dlist_insert_node(pdlist, pdlist->prev, ptr);
#endif

	return 0;
}

dat_t dlist_pop_back(dlst_nd_pt pdlist)
{
	DLIST_CHECH(pdlist, 0);

	if (pdlist->prev == pdlist)
	{
		// empty.
		return 0;
	}

	dlst_nd_pt ptear = pdlist->prev;

#ifndef REUSE
	ptear->prev->next = pdlist;
	pdlist->prev = ptear->prev;
#else
	dlist_erase_node(pdlist, ptear);
#endif	

	dat_t pval = ptear->data;

	free(ptear);

	return pval;
}

int dlist_push_front(dlst_nd_pt pdlist, dat_t pval)
{
	DLIST_CHECH(pdlist, -1);

	dlst_nd_pt ptr = (dlst_nd_pt)malloc(sizeof(dlst_nd_t));
	ptr->data = pval;

#ifndef REUSE
	ptr->next = pdlist->next;
	ptr->prev = pdlist;

	pdlist->next->prev = ptr;
	pdlist->next = ptr;
#else
	dlist_insert_node(pdlist, pdlist, ptr);
#endif

	return 0;
}

dat_t dlist_pop_front(dlst_nd_pt pdlist)
{
	DLIST_CHECH(pdlist, 0);

	if (pdlist->next == pdlist)
	{
		// empty
		return 0;
	}

	dlst_nd_pt phead = pdlist->next;

#ifndef REUSE
	pdlist->next = phead->next;
	phead->next->prev = phead->prev;
#else
	dlist_erase_node(pdlist, phead);
#endif

	dat_t pval = phead->data;
	free(phead);

	return pval;
}

// remember to free pnode.
dat_t dlist_erase_node(dlst_nd_pt pdlist, dlst_nd_pt pnode)
{
	DLIST_CHECH(pdlist, 0);
	DLIST_CHECH(pnode, 0);

	// 至少一个结点
	if (pdlist == pnode)
	{
		return 0;
	}

	pnode->prev->next = pnode->next;
	pnode->next->prev = pnode->prev;	
	
	pnode->next = pnode->prev = 0;

	return pnode->data;
}

void dlist_insert_node(dlst_nd_pt pdlist, dlst_nd_pt curp, dlst_nd_pt newp)
{
	DLIST_CHECH(pdlist, );

	if (!curp || !newp)
	{
		return;
	}

	newp->next = curp->next;
	newp->prev = curp;

	curp->next->prev = newp;
	curp->next = newp;
}

dlst_nd_pt dlist_front(dlst_nd_pt pdlist)
{
	DLIST_CHECH(pdlist, 0);

	return pdlist->next;
}

dlst_nd_pt dlist_back(dlst_nd_pt pdlist)
{
	DLIST_CHECH(pdlist, 0);

	return pdlist->prev;
}




