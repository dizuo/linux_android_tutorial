#ifndef DLIST_APP_201405091003_H
#define DLIST_APP_201405091003_H

// outline 
// double linked cycle list.

typedef void* dat_t;

typedef struct dlist_node
{
	dat_t data;
	struct dlist_node* next;
	struct dlist_node* prev;
} dlst_nd_t;

typedef dlst_nd_t* dlst_nd_pt;
typedef void (*dlst_tra_ft)(dlst_nd_pt);

dlst_nd_pt dlist_create(dat_t pval);

void dlist_traverse(dlst_nd_pt pdlist, dlst_tra_ft trav_func);

void dlist_destroy(dlst_nd_pt pdlist);

int dlist_push_back(dlst_nd_pt pdlist, dat_t pval);

dat_t dlist_pop_back(dlst_nd_pt pdlist);

int dlist_push_front(dlst_nd_pt pdlist, dat_t pval);

dat_t dlist_pop_front(dlst_nd_pt pdlist);

dlst_nd_pt dlist_front(dlst_nd_pt pdlist);

dlst_nd_pt dlist_back(dlst_nd_pt pdlist);

// 移除pnode指向的结点，并不负责free pnode
dat_t dlist_erase_node(dlst_nd_pt pdlist, dlst_nd_pt pnode);

// 将newp结点插入到curp的下一个位置
void dlist_insert_node(dlst_nd_pt pdlist, dlst_nd_pt curp, dlst_nd_pt newp);

#endif
