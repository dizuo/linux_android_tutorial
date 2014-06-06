#ifndef CYC_QUEUE_APP_201405081732_H
#define CYC_QUEUE_APP_201405081732_H

// FIFO
// Elements are added at the rear end,
// Elements are deleted at front end of the queue.

// insert/delete O(1)

// Arrays Version

typedef void* dat_t;

typedef void (*cyc_queue_dump_ft)(dat_t);

typedef struct cyc_queue
{	
	dat_t* buffer;
	int size;
	int rear;
	int front;
	int count;	// 浪费一个存储位或者单独增加一个计数器，区分ringbuffer是否空／是否满 
} cyc_que_t;

cyc_que_t* cyc_queue_create(int max_size);

int cyc_queue_push_back(cyc_que_t* cyc_que, dat_t data);

dat_t cyc_queue_pop_front(cyc_que_t* cyc_que);

int cyc_queue_size(cyc_que_t* cyc_que);

void cyc_queue_destroy(cyc_que_t* cyc_que);

int cyc_queue_isfull(cyc_que_t* cyc_que);

void cyc_queue_traverse(cyc_que_t* cyc_que, cyc_queue_dump_ft ft);


#endif
