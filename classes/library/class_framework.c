#include "types.h"

int create_instance_class( void * list[], int size, int max )
{
    for( int i = 0; i < max; i++ )
    {
        if( list[i] == NULL )
        {
            list[i] = MMALLOC( size );
            if( list[i] != NULL )
            {
                memset( list[i], 0x00, size );
                return i;
            }
            else
            {
                return -1;
            }
        }
    }
    
    return -1;
}
