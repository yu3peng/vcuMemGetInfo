#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum {

  CUDA_SUCCESS = 0

} CUresult;

#define MiB 1048576
/* 
CUresult cuMemGetInfo ( size_t* free, size_t* total )
{
    *total = 100 * MiB;
    *free = 10 * MiB;

    return CUDA_SUCCESS;
}
*/

CUresult cuMemGetInfo_v2 ( size_t* free, size_t* total )
{
    if ( NULL != getenv( "GPU_MEMORY" ) )
    {
        *free = atoi( getenv( "GPU_MEMORY" ) ) * MiB;
    }
    else
    {
        *free = 300 * MiB;
    }
  
    *total = *free * 2;

    return CUDA_SUCCESS;
}
