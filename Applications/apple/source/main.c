//
//  main.c
//  AppleEmulator
//
//  Created by Marcio Cherobim on 07/04/2014.
//  Copyright (c) 2014 Marcio Cherobim. All rights reserved.
//

#include "types.h"
#include "keyboard_drv.h"
#include "socket_dma.h"
#include "board.h"
#include "apl_emulator.h"
#include "commands.h"
#include "cmd_default.h"
#include "cmd_brkpoint.h"

#if defined _USE_MACOS_SDL
int _fe_main( void )
#else
int main( void )
#endif
{
    board_data_t * p_board;
    
    p_board = apl_emulator_init();
    
    console_init();
    commands_add_default();
    commands_add_breakpoint();
    
    console_listen_telnet( 2555 );
    
    socket_dma_init( p_board );

    while( p_board->is_running == TRUE )
    {
        console_process();
        socket_dma_process();
        board_execute();
        graphics_process();
    }

    return 0;
}

