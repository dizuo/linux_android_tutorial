#include "cyc-queue-app.h"

#include <stdlib.h>

#define CYC_QUEUE_CHECK(pque, flag) if (!pque || !pque->buffer || !pque->size) { return flag; }

cyc_que_t* cyc_queue_create(int max_size)
{
	cyc_que_t* pque = (cyc_que_t*)malloc(sizeof(cyc_que_t));
	pque->buffer = (dat_t*)malloc(max_size * sizeof(dat_t));

	pque->size = max_size;
	pque->rear = pque->front = 0;

	return pque;
}

int cyc_queue_push_back(cyc_que_t* cyc_que, dat_t data)
{
	CYC_QUEUE_CHECK(cyc_que, -1);

	if (cyc_queue_isfull(cyc_que))
	{
		return -1;
	}

	cyc_que->buffer[cyc_que->rear] = data;
	cyc_que->rear = (cyc_que->rear + 1) % cyc_que->size;
	++cyc_que->count;

	return 0;
}

dat_t cyc_queue_pop_front(cyc_que_t* cyc_que)
{
	CYC_QUEUE_CHECK(cyc_que, 0);

	if (cyc_que->count == 0)
	{
		return 0;
	}

	dat_t val = cyc_que->buffer[cyc_que->front];
	cyc_que->front = (cyc_que->front + 1) % cyc_que->size;
	--cyc_que->count;

	return val;
}

void cyc_queue_traverse(cyc_que_t* cyc_que, cyc_queue_dump_ft dumpft)
{
	CYC_QUEUE_CHECK(cyc_que, );

	int pos = cyc_que->front;
	int count = 0;
	while (count < cyc_que->count)
	{
		dumpft(cyc_que->buffer[pos]);
		pos = (pos + 1) % cyc_que->size;

		++count;
	}
}

int cyc_queue_size(cyc_que_t* cyc_que)
{
	CYC_QUEUE_CHECK(cyc_que, 0);

	return cyc_que->count;
}

void cyc_queue_destroy(cyc_que_t* cyc_que)
{
	CYC_QUEUE_CHECK(cyc_que, );		// return nothing.

}

int cyc_queue_isfull(cyc_que_t* cyc_que)
{
	CYC_QUEUE_CHECK(cyc_que, 0);

	if ( cyc_que->count == cyc_que->size )
	{
		return 1;
	}

	return 0;
}