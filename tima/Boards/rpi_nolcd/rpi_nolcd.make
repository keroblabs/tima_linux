SRC += $(BOARD_PATH)/rpi/ms_timer.c
#SRC += $(BOARD_PATH)/rpi/lcd_driver.c
#SRC += $(BOARD_PATH)/rpi/touch.c

DEFS += -D_USE_RPI

##ARCH_NAME = -march=armv7

GCCPATH = ~/raspbian-toolchain-gcc-4.7.2-linux32/bin/arm-raspbian-linux-gnueabi-
TRGT    = ~/raspbian-toolchain-gcc-4.7.2-linux32/bin/arm-raspbian-linux-gnueabi-