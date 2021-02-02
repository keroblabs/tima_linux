BOARD_PATH = $(DEFAULT_PATH)/Boards/rpi

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

DEFS += -D_USE_RPI -D_USE_LINUX -D_USE_MULTITHREAD -std=gnu99

DEFS += -DUSE_SECTIONS
DEFS += -DARM4_ASM
DEFS += -DARM5_ASM
DEFS += -D_USE_LINUX
DEFS += -D_USE_RPI
DEFS += -D_USE_MULTITHREAD

DEFS += -DADC_TOTAL_INDEX=4

ADEFS += -D_USE_LINUX

BOARD_CFLAGS += -std=gnu99

BOARD_LDFLAGS += -pthread  -lwiringPi -L$(BOARD_PATH)/wiringPi

CINCDIR += $(BOARD_PATH)/wiringPi

##ARCH_NAME = -march=armv7

#GCCPATH = ~/raspbian-toolchain-gcc-4.7.2-linux32/bin/arm-raspbian-linux-gnueabi-
#TRGT    = ~/raspbian-toolchain-gcc-4.7.2-linux32/bin/arm-raspbian-linux-gnueabi-

GCCPATH = /Volumes/xtools/armv8-rpi3-linux-gnueabihf/bin/armv8-rpi3-linux-gnueabihf-
TRGT    = /Volumes/xtools/armv8-rpi3-linux-gnueabihf/bin/armv8-rpi3-linux-gnueabihf-
LIBDIR  = /Volumes/xtools/armv8-rpi3-linux-gnueabihf/lib
