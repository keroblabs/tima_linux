GCCPATH = /Volumes/xtools/armv8-rpi3-linux-gnueabihf/bin/armv8-rpi3-linux-gnueabihf-
TRGT    = /Volumes/xtools/armv8-rpi3-linux-gnueabihf/bin/armv8-rpi3-linux-gnueabihf-
LIBDIR  = /Volumes/xtools/armv8-rpi3-linux-gnueabihf/lib

BOARD_LDFLAGS += -pthread  -lwiringPi -L$(BOARD_APP_INCLUDE)/wiringPi

# List all default C defines here, like -D_DEBUG=1
DEFS += -D_USE_MULTITHREAD
#DEFS += -DUSE_SECTIONS
DEFS += -DARM4_ASM
DEFS += -DARM5_ASM
DEFS += -D_USE_LINUX
DEFS += -D_USE_RPI
DEFS += -D_USE_MULTITHREAD
DEFS += -DADC_TOTAL_INDEX=4

BOARD_CFLAGS  += -std=gnu99

# List all default ASM defines here, like -D_DEBUG=1
ADEFS += -D_USE_LINUX

LIBOUTPUT =  $(BOARD_APP_INCLUDE)
