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
PROJECT      = carputer
PROJECT_PATH = carputer
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
DEFS +=

# List all default ASM defines here, like -D_DEBUG=1
ADEFS +=

#
# End of define section
##############################################################################################

##############################################################################################
# Start of include section
#

# List all default directories to look for include files here
CINCDIR += $(APP_PATH)/source
CINCDIR += $(APP_PATH)/minimp3

# End of include section
##############################################################################################

##############################################################################################
# Start of source section
#
SRC  =

# List C source files here
SRC += $(APP_PATH)/source/main.c


# List ASM source files here
ASRC  =

#
# End of source section
##############################################################################################

# this is always the last include
include $(DEFAULT_PATH)/make/make_rules.rules

# *** EOF ***

