#include "one_api.h"

typedef struct hmodule_t
{
	int (*open)(int* ptr);
} hmodule_t;

int hello_open(int* ptr)
{	
	return 0;
}

static struct hmodule_t hmodule_t_mothods = {
	open : hello_open
};
