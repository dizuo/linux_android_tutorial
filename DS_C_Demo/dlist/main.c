#include "dlist-app.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dlist_test(int size);

int main(int argn, char* argv[])
{
	dlist_test(0);

	printf("\n any key pressed to exit...\n");

	getchar();

	return 0;
}

// ==========================

void dump_node(dlst_nd_pt pnd)
{
	if (!pnd)
	{
		return;
	}

	printf("%p-[%p,", pnd, pnd->prev);

	if (pnd->data)
	{
		printf(" %d ", *(int*)(pnd->data));
	}

	printf(",%p]\n", pnd->next);

}

void dlist_test(int size)
{
	size = 10;

	int* pitems = (int*)malloc(sizeof(int)*size);

	// create.
	dlst_nd_pt pdlst = dlist_create(0);

	// push back, pop back
	for (int i = 0; i < size; i++)
	{
		*(pitems + i) = i;
		dlist_push_back(pdlst, pitems + i);
	}

	dlist_traverse(pdlst, dump_node);
	printf("\n");

	const int stackoverflow_times = 5;

	for (int i = 0; i < size + stackoverflow_times; i++)
	{
		int* pval = (int*)dlist_pop_back(pdlst);
		if (pval)
		{
			printf("%d\t", *pval);
		}
	}	printf("\n");

	// push front, pop front.
	for (int i = 0; i < size; i++)
	{
		*(pitems + i) = 100 + i;
		dlist_push_front(pdlst, pitems + i);
	}
	for (int i = 0; i < size + stackoverflow_times; i++)
	{
		int* pval = (int*)dlist_pop_front(pdlst);
		if (pval)
		{
			printf("%d\t", *pval);
		}
	}	printf("\n");

	// 
	printf("%p\n", pdlst);
	printf("%p\n", pdlst->next);
	printf("%p\n", pdlst->prev);

	// destroy.
	dlist_destroy(pdlst);

	free(pitems);

}