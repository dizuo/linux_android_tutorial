#include "lru-cache-app.h"

#include <stdlib.h>

#define LRU_CACHE_CHECK(pcache, flag) if (!pcache || pcache->_max_size==0 || !pcache->_dlist || !pcache->_hash) \
	{ return flag; }

// 哈希 函数的定义， key可以用存储的dat_t内容，value是双向列表的结点 
lru_cache_nd_pt lru_cache_create(int maxsize, hash_key_ft keyfunc, hash_cmp_ft cmpfunc)
{
	lru_cache_nd_pt pnode = (lru_cache_nd_pt)malloc(sizeof(lru_cache_nd_t));
	pnode->_max_size = maxsize;
	pnode->_count = 0;
	pnode->_dlist = dlist_create(0);
	pnode->_hash = hash_create(keyfunc, cmpfunc);
	hash_reserve(pnode->_hash, maxsize);

    return pnode;
}

dat_t lru_cache_insert(lru_cache_nd_pt pcache, dat_t pval)
{
	LRU_CACHE_CHECK(pcache, 0);

	dat_t p_oldval = 0;

	// if cycle queue is full, evict one item,
	if (pcache->_count == pcache->_max_size)
	{
		return lru_cache_evict_node(pcache, pval);
	}

	// insert
	dlist_push_back(pcache->_dlist, pval);
	dlst_nd_pt pnode = dlist_back(pcache->_dlist);
	hash_insert(pcache->_hash, pval, pnode);

	return p_oldval;
}

int lru_cache_contains(lru_cache_nd_pt pcache, dat_t pval)
{
	// touch node...
    LRU_CACHE_CHECK(pcache, -1);
    
    return hash_query(pcache->_hash, pval) == 0 ? -1 : 0;
}

void lru_cache_destroy(lru_cache_nd_pt pcache)
{
    LRU_CACHE_CHECK(pcache, );
    
    dlist_destroy(pcache->_dlist);
    hash_destroy(pcache->_hash);
    
    pcache->_count = 0;
    pcache->_max_size = 0;
    free(pcache);
}

void lru_cache_print(lru_cache_nd_t pcache, dlst_tra_ft pfunc)
{
    // LRU_CACHE_CHECK(pcache, );
    
    // dlist_traverse(pcache->_dlist, pfunc);
}

// 哈希 中存储结点指针。。。

// 复用结点，更新内部的pval，同时touch_node
dat_t lru_cache_evict_and_insert(lru_cache_nd_pt pcache, dat_t pval)
{
	LRU_CACHE_CHECK(pcache, 0);

	// remove from hash table.
    hs_dat_t pres = hash_query(pcache->_hash, pval);
    if (!pres)
    {
        return 0;
    }
    
    dlst_nd_pt pnode = (dlst_nd_pt)hash_erase(pcache->_hash, pval);
	dat_t p_oldval = dlist_erase_node(pcache->_dlist, pnode);
    
    pnode->data = pval;     // Reuse dlist node.
    
    dlist_insert_node(pcache->_dlist, dlist_back(pcache->_dlist), pnode);
    hash_insert(pcache->_dlist, pval, pnode);

	return p_oldval;
}