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
PROJECT = home_control

# Put here the board name: olimex, rpi
BOARD_NAME = rpi_nolcd

# Tima OS paths
DEFAULT_PATH = ../../..

# SCP parameters, when applicable
USERNAME    = pi
TARGET_NAME = 192.168.1.200
TARGET_PATH = ~/$(PROJECT)

include $(DEFAULT_PATH)/make/make_initial.rules

APP_PATH = $(DEFAULT_PATH)/Applications/$(PROJECT)

#
# End of main variables
##############################################################################################

##############################################################################################
# Start of define section
#

# List all default C defines here, like -D_DEBUG=1
DEFS = -DMAKE_RPI

# List all default ASM defines here, like -D_DEBUG=1
ADEFS =

# List all default ASM defines here, like -D_DEBUG=1
ADEFS =

#
# End of define section
##############################################################################################

##############################################################################################
# Start of include section
#

# List all default directories to look for include files here
CINCDIR =
CINCDIR += $(APP_PATH)/source2
CINCDIR += $(APP_PATH)/library

# End of include section
##############################################################################################

##############################################################################################
# Start of source section
#
SRC  =

# List C source files here
SRC += $(APP_PATH)/source2/main.c
SRC += $(APP_PATH)/source2/build_page.c

SRC += $(APP_PATH)/library/driver_ctrl.c
SRC += $(APP_PATH)/library/sensor_ctrl.c
SRC += $(APP_PATH)/library/schedule_ctrl.c
SRC += $(APP_PATH)/library/background.c
SRC += $(APP_PATH)/library/net_comms.c
SRC += $(APP_PATH)/library/settings.c

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
include $(DEFAULT_PATH)/make/make_framework.rules
#include $(DEFAULT_PATH)/make/make_interface.rules
include $(DEFAULT_PATH)/make/make_libc.rules
#include $(DEFAULT_PATH)/make/make_system.rules

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

