SRC += $(BOARD_PATH)/olimex/lcd_driver.c
SRC += $(BOARD_PATH)/olimex/ms_timer.c
SRC += $(BOARD_PATH)/olimex/spi_driver.c
SRC += $(BOARD_PATH)/olimex/gpio_driver.c
SRC += $(BOARD_PATH)/olimex/mcp3208_driver.c
SRC += $(BOARD_PATH)/olimex/serial_driver.c
SRC += $(BOARD_PATH)/olimex/keyboard_drv.c

DEFS += -D_USE_OLIMEX

GCCPATH = arm-linux-gnueabihf-
TRGT    = arm-linux-gnueabihf-
