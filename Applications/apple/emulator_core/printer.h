#ifndef _PRINTER_H__
#define _PRINTER_H__

//////////////////////////////////////////////////////////////////////////////////////

#include "datatypes.h"

//////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////

void printer_new_paper( void );
void printer_remove_paper( void );
void printer_insert( uint8_t slot );
void printer_init( void * p_board );

//////////////////////////////////////////////////////////////////////////////////////

#endif // _PRINTER_H__