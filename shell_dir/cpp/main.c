#include "test.h"
#include "share.h"

#include <stdio.h>

int main()
{
    test();
    share();    

    printf("any key to exit...\n");
    getchar();
    return 0;    
}
