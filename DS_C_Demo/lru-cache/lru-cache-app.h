#ifndef LRU_CACHE_APP_201405091023_H
#define LRU_CACHE_APP_201405091023_H

// storage data structure: double linked list / cycle buffer.
// query data structure: hash

#include "../dlist/dlist-app.h"
#include "../hash/hash-app.h"

// typedef void* dat_t;

typedef struct lru_cache_node
{
	dlst_nd_t* 		_dlist;
	hs_nd_ptr_t		_hash;
	int 	_max_size;
	int 	_count;
} lru_cache_nd_t;

typedef lru_cache_nd_t* lru_cache_nd_pt;

lru_cache_nd_pt lru_cache_create(int maxsize, hash_key_ft keyfunc, hash_cmp_ft cmpfunc);

dat_t lru_cache_insert(lru_cache_nd_pt pcache, dat_t pval);

int lru_cache_contains(lru_cache_nd_pt pcache, dat_t pval);

void lru_cache_destroy(lru_cache_nd_pt pcache);

void lru_cache_print(lru_cache_nd_t pcache, dlst_tra_ft pfunc);

dat_t lru_cache_evict_and_insert(lru_cache_nd_pt pcache, dat_t pval);

// evict

#endif
