#include "hash-app.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HASH_CHECK(table)	if (!table || !table->bucket) { return; }

hs_tb_t* hash_create(hash_key_ft keyfunc, hash_cmp_ft cmpfunc)
{
	hs_tb_t* tb = (hs_tb_t*)malloc( sizeof(hs_tb_t) );

	tb->count = 0;
	tb->bucket = 0;
	tb->key_func = keyfunc;
	tb->cmp_func = cmpfunc;

	return tb;
}

void hash_reverse(hs_tb_t* table, int count)
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
	table->bucket = (hs_nd_ptr_t)malloc( sizeof(hs_nd_t) * count);

	memset(table->bucket, 0, sizeof(hs_nd_t) * count);

}

void hash_insert(hs_tb_t* table, dat_t pkey, dat_t pvalue)
{
	HASH_CHECK(table);

	int hash = table->key_func(pkey) % table->count;

	if (HASH_NUL == table->bucket[hash].data)
	{
		table->bucket[hash].data = pvalue;
		return;
	}

	hs_nd_ptr_t curp, lastp;
	for (curp = table->bucket + hash; curp; lastp = curp, curp = curp->next)
		;

	lastp->next = (hs_nd_ptr_t)malloc(sizeof(hs_nd_t));
	lastp->next->data = pvalue;
	lastp->next->next = 0;
	
}

dat_t hash_query(hs_tb_t* table, dat_t pkey)
{
	if (!table || !table->bucket)
	{
		return 0;
	}

	int hash = table->key_func(pkey) % table->count;
	hs_nd_ptr_t curp = table->bucket + hash;

	printf("hash = %d\n", hash);

	while (curp && curp->data != HASH_NUL)
	{
		if (table->cmp_func(curp->data, pkey) == 0)
		{
			return curp->data;
		}

		curp = curp->next;
	}

	return 0;
}

void hash_print(hs_tb_t* table, hash_dump_ft dumpfunc)
{
	HASH_CHECK(table);

	int idx = 0;
	while (idx < table->count)
	{
		if (table->bucket[idx].data == HASH_NUL)
		{
			++idx;
			continue;
		}

		hs_nd_ptr_t curp = table->bucket + idx;

		printf("[%d] : ", idx);

		while (curp)
		{
			dumpfunc(curp->data);
			curp = curp->next;
		}

		printf("\n");
		++idx;
	}

}


void hash_destroy(hs_tb_t* table)
{
	HASH_CHECK(table);

	int idx = 0;

	while (idx < table->count)
	{
		hs_nd_ptr_t curp = table->bucket[idx].next;

		while (curp)
		{
			hs_nd_ptr_t tmp = curp;
			curp = curp->next;

			free(tmp);
		}

		++idx;
	}

	free(table->bucket);
	free(table);
}
