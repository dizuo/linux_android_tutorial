#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cyc-queue-app.h"

void cyc_queue_test();

int main(int argn, char* argv[])
{
	cyc_queue_test();

    printf("\n any key pressed to exit...\n");
    getchar();

    return 0;
}


// =========================================================
typedef struct item
{
	int num;
} item_t;

void dump_item(void* ptr)
{
	item_t* pitem = (item_t*)ptr;

	if (!pitem)
	{
		return;
	}

	printf("%d\t", pitem->num);

}

void cyc_queue_test()
{
	srand( time(NULL) );

	cyc_que_t* pque = cyc_queue_create(6);

	item_t item_arr[10];

	// push 
	for (int i = 0; i < 10; i++)
	{
		item_arr[i].num = i;
		cyc_queue_push_back(pque, item_arr + i);
	}

	// 删掉、然后插入几个元素
	for (int i = 0; i < 3; i++)
	{
		cyc_queue_pop_front(pque);

		item_arr[i].num = 124 + i;
		cyc_queue_push_back(pque, item_arr + i);
	}

	// 获取size
	int size = cyc_queue_size(pque);
	printf("queue size = %d\n", size);

	// 遍历队列
	cyc_queue_traverse(pque, dump_item);
	printf("\n");

	// 多次pop front
	item_t* pitem = cyc_queue_pop_front(pque);
	if (pitem)
	{
		printf("item [%d]\n", pitem->num);
	}

	for (int i = 0; i < 10; i++)
	{
		item_t* pitem = cyc_queue_pop_front(pque);
		if (pitem)
		{
			printf("item [%d]\n", pitem->num);
		}
	}

	cyc_queue_destroy(pque);

}