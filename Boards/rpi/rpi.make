#BOARD_PATH = $(DEFAULT_PATH)/Boards/rpi

GCCPATH = /Volumes/xtools/armv8-rpi3-linux-gnueabihf/bin/armv8-rpi3-linux-gnueabihf-
TRGT    = /Volumes/xtools/armv8-rpi3-linux-gnueabihf/bin/armv8-rpi3-linux-gnueabihf-
LIBDIR  = /Volumes/xtools/armv8-rpi3-linux-gnueabihf/lib

# List all default C defines here, like -D_DEBUG=1
#DEFS += -DUSE_SECTIONS
DEFS += -DTIMA_LINUX
DEFS += -DARM4_ASM
DEFS += -DARM5_ASM
DEFS += -D_USE_LINUX
DEFS += -D_USE_RPI
DEFS += -D_USE_MULTITHREAD
DEFS += -DADC_TOTAL_INDEX=4

ADEFS += -D_USE_LINUX

BOARD_CFLAGS  += -std=gnu99
BOARD_LDFLAGS += -pthread  -lwiringPi -L$(BOARD_APP_INCLUDE)/wiringPi