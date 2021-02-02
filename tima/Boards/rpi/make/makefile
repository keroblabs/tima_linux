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

# Put here the board name: olimex, rpi
BOARD_NAME   = rpi

# Tima OS paths
DEFAULT_PATH = ../../..

include $(DEFAULT_PATH)/make/make_initial.rules

#
# End of main variables
##############################################################################################

##############################################################################################
# Start of define section
#


#
# End of define section
##############################################################################################

##############################################################################################
# Start of include section
#

# List all default directories to look for include files here
CINCDIR += $(BOARD_PATH)/library
CINCDIR += $(BOARD_PATH)/wiringPi

# End of include section
##############################################################################################

##############################################################################################
# Start of source section
#

# Compiler definitions
GCCPATH = /Volumes/xtools/armv8-rpi3-linux-gnueabihf/bin/armv8-rpi3-linux-gnueabihf-
TRGT    = /Volumes/xtools/armv8-rpi3-linux-gnueabihf/bin/armv8-rpi3-linux-gnueabihf-
LIBDIR  = /Volumes/xtools/armv8-rpi3-linux-gnueabihf/lib

# List C source files here
SRC += $(BOARD_PATH)/library/mcp3202_driver.c
SRC += $(BOARD_PATH)/library/spi_driver.c
SRC += $(BOARD_PATH)/library/ms_timer.c
SRC += $(BOARD_PATH)/library/lcd_driver.c
SRC += $(BOARD_PATH)/library/touch.c
SRC += $(BOARD_PATH)/library/serial_driver.c
SRC += $(BOARD_PATH)/library/gpio_driver.c
SRC += $(BOARD_PATH)/library/spawn_lib.c
SRC += $(BOARD_PATH)/library/canbus.c
SRC += $(BOARD_PATH)/library/video.c

# List ASM source files here

#
# End of source section
##############################################################################################

##############################################################################################
# Start of Modules section
#

#include $(DEFAULT_PATH)/make/make_console.rules
#include $(DEFAULT_PATH)/make/make_filesys.rules
#include $(DEFAULT_PATH)/make/make_speex.rules
include $(DEFAULT_PATH)/make/make_graphics.rules
include $(DEFAULT_PATH)/make/make_framework.rules
#include $(DEFAULT_PATH)/make/make_interface.rules
include $(DEFAULT_PATH)/make/make_libc.rules
include $(DEFAULT_PATH)/make/make_system_linux.rules

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
include $(DEFAULT_PATH)/make/make_lib_rules.rules

# *** EOF ***

