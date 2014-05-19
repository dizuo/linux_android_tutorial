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
    
    int* ptr = (int*)n->data;

	printf("%d\t", *ptr);
}

int my_cmp(dat_t one, dat_t two)
{
    int* p1 = (int*)one;
    int* p2 = (int*)two;
    
	return *p1 - *p2;
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

void list_test(int num);

int main(int argn, char* argv[])
{
	if (argn != 2)
	{
		printf("bad parameters\n");
		return 1;
	}
    
    int list_nm;
	if ( my_atoi(argv[1], &list_nm) != 0 )
	{
		printf("please input value \n");
		return 1;
	}
    
    list_test(list_nm);

	printf("\nany key pressed to exit ... \n");

	getchar();

	return 0;
}

void list_test(int list_nm)
{
    srand(time(NULL));
    
	printf("argv[1] = %d\n", list_nm);
    
	node_ptr_t head = NULL;
    
    int* buffer = (int*)malloc(sizeof(int) * list_nm);
    
	int k = 0;
    
	while (k < list_nm)
	{
		buffer[k] = rand() % 100;
		list_insert_sort(&head, buffer + k, my_cmp);
		++k;
	}
    
	list_traverse(&head, print);
	list_reverse(&head);
	printf("\nAfter reverse: \n");
	list_traverse(&head, print);
    
    // list erase.
    for (int k = 0; k < 100; k++)
    {
        int val = rand() % 100;
        
        if (list_erase_node(&head, &val, my_cmp) == 0)
        {
            printf("\nerase [%d]\n", val);
            list_traverse(&head, print);
            printf("\n");
        }
    }
    
	list_destroy(&head);
    free(buffer);
    
    //
    {
        int val = 3;
        list_insert(&head, &val);
        list_traverse(&head, print);
        printf("\n");
        
        int val1 = 30;
        list_insert(&head, &val1);
        list_reverse(&head);
        list_traverse(&head, print);
        printf("\n");
        
        list_destroy(&head);
    }
    
}