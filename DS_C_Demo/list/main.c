#include "list-app.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print(node_ptr_t n)
{
	if (!n)
	{
		return;
	}

	printf("%d\t", n->data);
}

int my_cmp(dat_t one, dat_t two)
{
	return one - two;
}

int my_atoi(const char* str, int* pval)
{
	*pval = 0;

	while (*str)
	{
		if (*str < '0' || *str > '9')
		{
			break;
		}

		*pval *= 10;
		*pval += (*str - '0');

		++str;
	}

	if (*str)
	{
		return -1;
	}

	return 0;
}

int main(int argn, char* argv[])
{
	if (argn != 2)
	{
		printf("bad parameters\n");
		return 1;
	}

	srand(time(NULL));

	int list_nm;
	if ( my_atoi(argv[1], &list_nm) != 0 )
	{
		printf("please input value \n");
		return 1;
	}

	printf("argv[1] = %d\n", list_nm);

	int k = -1;

	node_ptr_t head = list_create(k);

	k++;

	while (k < list_nm)
	{
		int val = rand() % 100;
		// list_insert(head, val);
		list_insert_sort(head, val, my_cmp);
		++k;
	}

	list_traverse(head, print);
	list_reverse(head);
	printf("\nAfter reverse: \n");
	list_traverse(head, print);

	list_destroy(&head);

	printf("\nany key pressed to exit ... \n");

	getchar();

	return 0;
}