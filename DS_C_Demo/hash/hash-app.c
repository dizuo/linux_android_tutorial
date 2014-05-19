#include "hash-app.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// History 
// 20140517 增加hash_erase, change hs_nd_t: remove data filed, add pkey and pval.

// 20140519 hash_erase Need Refactor...


#define HASH_CHECK(table, flag)	if (!table || !table->bucket) { return flag; }
 
hs_tb_t* hash_create(hash_key_ft keyfunc, hash_cmp_ft cmpfunc)
{
	hs_tb_t* tb = (hs_tb_t*)malloc( sizeof(hs_tb_t) );

	tb->count = 0;
	tb->bucket = 0;
	tb->key_func = keyfunc;
	tb->cmp_func = cmpfunc;

	return tb;
}

void hash_reserve(hs_tb_t* table, int count)
{
	if (!table)
	{
		return;
	}

	if (table->bucket)
	{
		free(table->bucket);
	}

	table->count = count;
	table->bucket = (hs_nd_ptr_t*)malloc( sizeof(hs_nd_ptr_t) * count);

	memset(table->bucket, 0, sizeof(hs_nd_ptr_t) * count);

}

void hash_insert(hs_tb_t* table, hs_dat_t pkey, hs_dat_t pvalue)
{
	HASH_CHECK(table, );

	int hash = table->key_func(pkey) % table->count;

	if (NULL == table->bucket[hash])    // list is empty.
	{
        table->bucket[hash] = (hs_nd_ptr_t)malloc(sizeof(hs_nd_t));
        table->bucket[hash]->next = 0;
		table->bucket[hash]->pkey = pkey;
		table->bucket[hash]->pval = pvalue;

		return;
	}

	hs_nd_ptr_t curp, lastp;
	for (curp = table->bucket[hash]; curp; lastp = curp, curp = curp->next)
		;

	lastp->next = (hs_nd_ptr_t)malloc(sizeof(hs_nd_t));
	lastp->next->pkey = pkey;
	lastp->next->pval = pvalue;
	lastp->next->next = 0;
	
}

hs_dat_t hash_query(hs_tb_t* table, hs_dat_t pkey)
{
	HASH_CHECK(table, 0);

	int hash = table->key_func(pkey) % table->count;
	hs_nd_ptr_t curp = table->bucket[hash];

	while (curp && table->cmp_func(curp->pkey, pkey) == 0)
	{
		curp = curp->next;
	}

	return curp ? curp->pval : 0;
}

void hash_print(hs_tb_t* table, hash_dump_ft dumpfunc)
{
	HASH_CHECK(table, );

	int idx = 0;
	while (idx < table->count)
	{
		if (!table->bucket[idx])
		{
			++idx;
			continue;
		}

		hs_nd_ptr_t curp = table->bucket[idx];

		printf("[%d] : ", idx);

		while (curp)
		{
			dumpfunc(curp->pkey);
			curp = curp->next;
		}

		printf("\n");
		++idx;
	}

}

hs_dat_t hash_erase(hs_tb_t* table, hs_dat_t pkey)
{
	HASH_CHECK(table, 0);

	int hash = table->key_func(pkey) % table->count;
	hs_nd_ptr_t curp = table->bucket[hash];
    
	hs_nd_ptr_t lastp = 0;

	while (curp && table->cmp_func(curp->pkey, pkey) != 0)
	{
		lastp = curp;
		curp = curp->next;
	}

	if (!curp)
	{
		return 0;
	}

	hs_dat_t pold_val = curp->pval;

	if (lastp)
	{
		lastp->next = curp->next;
	}
	else
	{	
		table->bucket[hash] = curp->next;
	}
    
    free(curp);
    
	return pold_val;
}

void hash_destroy(hs_tb_t* table)
{
	HASH_CHECK(table, );

	int idx = 0;

	while (idx < table->count)
	{
		hs_nd_ptr_t curp = table->bucket[idx];

		while (curp)
		{
			hs_nd_ptr_t tmp = curp;
			curp = curp->next;

			free(tmp);
		}

		++idx;
	}

	free(table->bucket);
    table->bucket = NULL;
    
	free(table);
}
