#ifndef BOARDS_MACOS_SDL_SDL_INTERNAL_H_
#define BOARDS_MACOS_SDL_SDL_INTERNAL_H_

////////////////////////////////////////////////////////////////////

#include "types.h"

#ifdef WIN32
#include <SDL.h>
#include <Windows.h>
#include <conio.h>
#elif defined __MACH__
#include <SDL2/SDL.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#endif

#include <pthread.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////////

#define MAX_INSTANCES           10
#define MAX_RAM_DATA            2048
#define SDL_INTERNAL_DELEGATE   1

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

#endif /* BOARDS_MACOS_SDL_SDL_INTERNAL_H_ */
