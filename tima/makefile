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
PROJECT      = instruments
PROJECT_PATH = instruments
# Put here the board name: olimex, rpi
BOARD_NAME = rpi

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
DEFS =

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
CINCDIR += $(APP_PATH)/source4
CINCDIR += $(APP_PATH)/skin_client
CINCDIR += $(APP_PATH)/graphics

# End of include section
##############################################################################################

##############################################################################################
# Start of source section
#
SRC  =

# List C source files here
SRC += $(APP_PATH)/source4/main.c
SRC += $(APP_PATH)/source4/driving_data.c
SRC += $(APP_PATH)/source4/input_reader.c
SRC += $(APP_PATH)/source4/canbus_conns.c
SRC += $(APP_PATH)/source4/logging_data.c
SRC += $(APP_PATH)/source4/odometer_ctrl.c

SRC += $(APP_PATH)/graphics/gauges_lib.c
SRC += $(APP_PATH)/graphics/show_7segs_lib.c
SRC += $(APP_PATH)/graphics/warning_lights.c

SRC += $(APP_PATH)/skin_client/infocentre.c
SRC += $(APP_PATH)/skin_client/skin_standard.c
SRC += $(APP_PATH)/skin_client/skin_fuel.c
SRC += $(APP_PATH)/skin_client/skin_handbrake.c
SRC += $(APP_PATH)/skin_client/skin_infocentre.c
SRC += $(APP_PATH)/skin_client/skin_odometer.c
SRC += $(APP_PATH)/skin_client/skin_rpm.c
SRC += $(APP_PATH)/skin_client/skin_speed.c
SRC += $(APP_PATH)/skin_client/skin_temperature.c
SRC += $(APP_PATH)/skin_client/skin_warning.c
SRC += $(APP_PATH)/skin_client/skin_touchscreen.c


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
include $(DEFAULT_PATH)/make/make_rules.rules

# *** EOF ***

