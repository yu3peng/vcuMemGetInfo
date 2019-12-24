#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef enum {

  CUDA_SUCCESS = 0

} CUresult;

#define MiB 1048576

/* 
CUresult cuMemGetInfo ( size_t* free, size_t* total )
{
}
*/

CUresult cuMemGetInfo_v2 ( size_t* free, size_t* total )
{
    printf(" Hacking GPU MEMORY from GPU_MEMORY env.\n");
 
    if ( NULL != getenv( "GPU_MEMORY" ) )
    {
        *free = atoi( getenv( "GPU_MEMORY" ) ) * MiB;
        printf(" GPU_MEMORY env is %s MiB.\n", getenv( "GPU_MEMORY" ) );
    }
    else
    {
        *free = 300 * MiB;
        printf(" Default GPU_MEMORY env is 300 MiB.\n");
    }
  
    *total = *free * 2;

    return CUDA_SUCCESS;
}
