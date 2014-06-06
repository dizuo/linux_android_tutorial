
// 输入paragraph中文本，单词缓存设为50，采用lru淘汰缓存相。

#include "lru-cache-app.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lru_cache_test();

int main(int argn, char* argv[])
{

	printf("any key pressed to exit...\n");
	getchar();

    return 0;
}

#define MAX_lEN (100)

typedef struct Item
{
	char word[MAX_lEN];
} Item_t;

unsigned int DJB_hash(char* buffer, int len)
{
    unsigned int hash = 5381;
    int i = 0;
    
    while (i < len)
    {
        hash += (hash << 5) + buffer[i++];
    }
    
    return (hash & 0x7FFFFFFF);
}

int item_key(void* ptr)
{
	if (!ptr)
	{
		return 0;
	}

	Item_t* pitem = (Item_t*)ptr;
    
    return DJB_hash(pitem->word, strlen(pitem->word));
}

int item_cmp(void* pleft, void* pright)
{
	if (!pleft || !pright)
	{
		return -1;
	}
    
    Item_t* p1 = (Item_t*)pleft;
    Item_t* p2 = (Item_t*)pright;

	return strcmp(p1->word, p2->word);
}

void lru_cache_test()
{
	lru_cache_nd_pt phead = lru_cache_create(123, item_key, item_cmp);

	

}


