##############################################################################################
#
# On command line:
#
# make all = Create project
#
# make clean = Clean project files.
#
# To rebuild project do "make clean" and "make all".
#
#
##############################################################################################

##############################################################################################
# Start of main variables
#

# Define project name here
PROJECT      = apple
PROJECT_PATH = apple
# Put here the board name: olimex, rpi
BOARD_NAME = rpi
USERNAME = pi
TARGET_NAME = 192.168.1.190
#TARGET_NAME = 10.0.0.3

# Tima OS paths
DEFAULT_PATH = ../../..

include $(DEFAULT_PATH)/make/make_initial.rules

#
# End of main variables
##############################################################################################

##############################################################################################
# Start of define section
#

# List all default C defines here, like -D_DEBUG=1
DEFS += -D_USE_SCREEN_WIDTH=1280
DEFS += -D_USE_SCREEN_HEIGHT=800

# List all default ASM defines here, like -D_DEBUG=1
ADEFS +=

#
# End of define section
##############################################################################################

##############################################################################################
# Start of include section
#

# List all default directories to look for include files here
CINCDIR += $(APP_PATH)/debugger
CINCDIR += $(APP_PATH)/emulator_core
CINCDIR += $(APP_PATH)/source
CINCDIR += $(APP_PATH)/xa_embedded

# End of include section
##############################################################################################

##############################################################################################
# Start of source section
#
SRC  =

# List C source files here
SRC += $(APP_PATH)/source/main.c
SRC += $(APP_PATH)/source/apl_emulator.c
SRC += $(APP_PATH)/source/extension.c
SRC += $(APP_PATH)/source/socket_dma.c

SRC += $(APP_PATH)/emulator_core/board.c
SRC += $(APP_PATH)/emulator_core/clock_card.c
SRC += $(APP_PATH)/emulator_core/cpu.c
SRC += $(APP_PATH)/emulator_core/debug.c
SRC += $(APP_PATH)/emulator_core/disc_drive.c
SRC += $(APP_PATH)/emulator_core/hard_drive.c
SRC += $(APP_PATH)/emulator_core/io_addr.c
SRC += $(APP_PATH)/emulator_core/keyboard.c
SRC += $(APP_PATH)/emulator_core/led_frame.c
SRC += $(APP_PATH)/emulator_core/mouse.c
SRC += $(APP_PATH)/emulator_core/paddles.c
SRC += $(APP_PATH)/emulator_core/printer.c
SRC += $(APP_PATH)/emulator_core/ram_ctrl.c
SRC += $(APP_PATH)/emulator_core/serial.c
SRC += $(APP_PATH)/emulator_core/sw_switch.c
SRC += $(APP_PATH)/emulator_core/video.c

SRC += $(APP_PATH)/xa_embedded/asm_embedded.c
SRC += $(APP_PATH)/xa_embedded/xa.c
SRC += $(APP_PATH)/xa_embedded/xaa.c
SRC += $(APP_PATH)/xa_embedded/xacharset.c
SRC += $(APP_PATH)/xa_embedded/xal.c
SRC += $(APP_PATH)/xa_embedded/xao.c
SRC += $(APP_PATH)/xa_embedded/xap.c
SRC += $(APP_PATH)/xa_embedded/xar.c
SRC += $(APP_PATH)/xa_embedded/xar2.c
SRC += $(APP_PATH)/xa_embedded/xat.c
SRC += $(APP_PATH)/xa_embedded/xau.c

SRC += $(APP_PATH)/debugger/cmd_brkpoint.c
SRC += $(APP_PATH)/debugger/cmd_default.c
SRC += $(APP_PATH)/debugger/commands.c

# List ASM source files here
ASRC  =

#
# End of source section
##############################################################################################

##############################################################################################
# Start of Modules section
#

#include $(DEFAULT_PATH)/make/make_console.rules
#include $(DEFAULT_PATH)/make/make_filesys.rules
#include $(DEFAULT_PATH)/make/make_speex.rules
#include $(DEFAULT_PATH)/make/make_graphics.rules
#include $(DEFAULT_PATH)/make/make_framework.rules
#include $(DEFAULT_PATH)/make/make_interface.rules
#include $(DEFAULT_PATH)/make/make_libc.rules
#include $(DEFAULT_PATH)/make/make_system_linux.rules

#include $(DEFAULT_PATH)/Boards/imx233/make/make_imx233.rules


#
# End of Modules section
##############################################################################################

##############################################################################################
# Start of additional modules
#

##include $(DEFAULT_PATH)/make/make_4Ddisplay.rules


#
# End of source section
##############################################################################################


# this is always the last include
include $(DEFAULT_PATH)/make/make_rules.rules

# *** EOF ***

