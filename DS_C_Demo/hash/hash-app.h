#ifndef HASH_APP_201405061621_H
#define HASH_APP_201405061621_H

// 多级散列表

// value 和 key 都采用void*范型设计
// 配套都key_make，key_cmp函数参数都是void*，支持任何类型。

typedef void* hs_dat_t;

typedef struct hash_node
{
	hs_dat_t pkey;
	hs_dat_t pval;
	struct hash_node* next;
} hs_nd_t;

typedef hs_nd_t* hs_nd_ptr_t;

typedef void (*hash_dump_ft)(hs_dat_t);
typedef int (*hash_key_ft)(hs_dat_t);
typedef int (*hash_cmp_ft)(hs_dat_t, hs_dat_t);

typedef struct hash_table
{
	hs_nd_ptr_t* bucket;
	int count;
	hash_key_ft key_func;
	hash_cmp_ft cmp_func;
} hs_tb_t;


hs_tb_t* hash_create(hash_key_ft keyfunc, hash_cmp_ft cmpfunc);

void hash_reserve(hs_tb_t* table, int count);

void hash_insert(hs_tb_t* table, hs_dat_t pkey, hs_dat_t pvalue);

hs_dat_t hash_erase(hs_tb_t* table, hs_dat_t pkey);

hs_dat_t hash_query(hs_tb_t* table, hs_dat_t pkey);

void hash_print(hs_tb_t* table, hash_dump_ft dumpfunc);

void hash_destroy(hs_tb_t* table);

#endif

