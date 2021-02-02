#include "system.h"

#ifdef _USE_FRONTEND
int _fe_main( void )
#else
int main( void )
#endif
{
    system_Startup();
    return 0;
}

