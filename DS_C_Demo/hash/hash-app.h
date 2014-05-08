#ifndef HASH_APP_201405061621_H
#define HASH_APP_201405061621_H

// 多级散列表

// value 和 key 都采用void*范型设计
// 配套都key_make，key_cmp函数参数都是void*，支持任何类型。

typedef void* dat_t;

typedef struct hash_node
{
	dat_t data;
	struct hash_node* next;
} hs_nd_t;

typedef hs_nd_t* hs_nd_ptr_t;

typedef void (*hash_dump_ft)(dat_t);
typedef int (*hash_key_ft)(dat_t);
typedef int (*hash_cmp_ft)(dat_t, dat_t);

#define HASH_NUL (0)

typedef struct hash_table
{
	hs_nd_ptr_t bucket;
	int count;
	hash_key_ft key_func;
	hash_cmp_ft cmp_func;
} hs_tb_t;


hs_tb_t* hash_create(hash_key_ft keyfunc, hash_cmp_ft cmpfunc);

void hash_reverse(hs_tb_t* table, int count);

void hash_insert(hs_tb_t* table, dat_t pkey, dat_t pvalue);

dat_t hash_query(hs_tb_t* table, dat_t pkey);

void hash_print(hs_tb_t* table, hash_dump_ft dumpfunc);

void hash_destroy(hs_tb_t* table);

#endif

