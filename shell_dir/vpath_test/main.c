#include <stdio.h>

#include "./header/global.h"
#include "./util/include/util.h"

int main()
{
    test();
    
    int dataVer = get_data_ver();
    printf("ver1 = %d\n", dataVer);
    dataVer = get_data_ver();
    printf("ver2 = %d\n", dataVer);

    printf("any press to exit...\n");
    getchar();

    return 0;
}
