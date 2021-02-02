#include "crc.h"

////////////////////////////////////////////////////////////////////////////////////////////////

/* Make the table for a fast CRC. */
void crc_init( crc_data_t * data, uint32_t poly, uint32_t init_val )
{
    uint32_t c, n, k;

	for (n = 0; n < 256; n++) 
	{
        c = n;

        for (k = 0; k < 8; k++) 
		{
            if (c & 1) 
			{
                c = poly ^ (c >> 1);
            } 
			else 
			{
                c = c >> 1;
            }
        }

        data->table[n] = c;
    }

	data->crc_init = init_val;
}

uint32_t crc_calculate( crc_data_t * data, uint8_t * buffer, uint32_t size )
{
	uint32_t count;
	uint32_t crc = data->crc_init;
	
	for( count = 0; count < size; count++ )
	{
		crc = ( crc >> 8 ) ^ data->table[ ( crc & 0x0FF ) ^ buffer[count] ];
	}
	
	return crc;	
}

