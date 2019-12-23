#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include "cuMemGetInfo.h"

#define MiB 1048576

CUresult cuMemGetInfo ( size_t* free, size_t* total )
{
    *total = 100 * MiB;
    *free = 10 * MiB;

    return CUDA_SUCCESS;
}

CUresult cuMemGetInfo_v2 ( size_t* free, size_t* total )
{
    *total = 200 * MiB;
    *free = 20 * MiB;

    return CUDA_SUCCESS;
}
