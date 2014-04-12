#include "../include/util.h"

int gDataVer = 1;

int get_data_ver()
{
    gDataVer++;

    return gDataVer;
}
