#include "random.h"

////////////////////////////////////////////////////////////////////////////////////////////////

#define RAND_DEFAULT_PARAM1     15874
#define RAND_DEFAULT_PARAM2     48547
#define RAND_DEFAULT_SEED       5698744213654

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

void rand_init( random_t * data, int64_t seed, uint32_t max_value )
{
    data->param1    = RAND_DEFAULT_PARAM1;
    data->param2    = RAND_DEFAULT_PARAM2;
    data->seed      = seed;
    data->max_value = max_value;
}

uint32_t rand_get_next( random_t * data )
{
    uint32_t * seed_32 = ( uint32_t * )( &data->seed );

    seed_32[0] = data->param1 * (seed_32[0] & 65535) + (seed_32[0] >> 16);
    seed_32[1] = data->param2 * (seed_32[1] & 65535) + (seed_32[1] >> 16);

    return( ( seed_32[0] << 16 ) + ( seed_32[1] & 0x0FFFF ) ) % data->max_value;
}

