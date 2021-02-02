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

BOARD_PATH = $(DEFAULT_PATH)/Boards/Nucleo_446

# hardware paths
CMSIS_ST_PATH =  $(BOARD_PATH)/CMSIS/Device/ST/STM32F4xx/Include
CMSIS_PATH =     $(BOARD_PATH)/CMSIS/Include
STDPERIPH_PATH = $(BOARD_PATH)/STM32F4xx_StdPeriph_Driver

GCCPATH = /Users/marciocherobim/Tools/gcc-4_7-2013q3/arm-none-eabi
TRGT    = /Users/marciocherobim/Tools/gcc-4_7-2013q3/bin/arm-none-eabi-
LIBDIR  = /Users/marciocherobim/Tools/gcc-4_7-2013q3/arm-none-eabi/lib/thumb
STLINKP = /Users/marciocherobim/Tools/stlink/bin/

LD		= $(TRGT)gcc
CC      = $(TRGT)gcc
CP      = $(TRGT)objcopy
AS      = $(TRGT)gcc -x assembler-with-cpp
SIZE    = $(TRGT)size
OBJCOPY = $(TRGT)objcopy
OBJDUMP = $(TRGT)objdump
BIN     = $(CP) -O ihex
MAKE    = make
CP      = cp
FLASHER = $(STLINKP)st-flash

# Select the cpu
BOARD_CFLAGS += -mcpu=cortex-m4 -mthumb -mthumb-interwork 
BOARD_CFLAGS += -std=gnu99 
BOARD_CFLAGS += -fsigned-char -mlittle-endian

# link information
LDDEF = $(BOARD_PATH)/library/STM32F446RETx_FLASH.ld

# additional link commands
BOARD_LDFLAGS += 
BOARD_LDFLAGS += -Wl,--cref,--gc-sections
BOARD_LDFLAGS += -Wl,-static
BOARD_LDFLAGS += -nostartfiles

FLASHER_PARAM = --reset write
FLASHER_ADDR  = 0x8000000

BOARD_LDFLAGS += 
BOARD_LDFLAGS += -Wl,-T -Xlinker $(LDDEF)
#
# End of main variables
##############################################################################################

##############################################################################################
# Start of define section
#

# hardware dependent defs
DEFS += -DSTM32F446xx
DEFS += -DUSE_STDPERIPH_DRIVER
DEFS += -DUSE_ST_TYPES
DEFS += -DUSE_SECTIONS
DEFS += -DUSE_SERIAL_PRINTF
DEFS += -DADC_TOTAL_INDEX=4
DEFS += -DUSE_LOCAL_TYPES
#
# End of define section
##############################################################################################

##############################################################################################
# Start of include section
#

# List all default directories to look for include files here
CINCDIR += $(CMSIS_ST_PATH)
CINCDIR += $(CMSIS_PATH)
CINCDIR += $(STDPERIPH_PATH)/Inc
CINCDIR += $(BOARD_PATH)
CINCDIR += $(BOARD_PATH)/library
CINCDIR += $(BOARD_PATH)/drivers

# End of include section
##############################################################################################

##############################################################################################
# Start of source section
#

# List C source files for hardware library
SRC += $(STDPERIPH_PATH)/Src/misc.c
SRC += $(STDPERIPH_PATH)/Src/stm32f4xx_rcc.c
SRC += $(STDPERIPH_PATH)/Src/stm32f4xx_gpio.c
SRC += $(STDPERIPH_PATH)/Src/stm32f4xx_usart.c
SRC += $(STDPERIPH_PATH)/Src/stm32f4xx_dma.c
SRC += $(STDPERIPH_PATH)/Src/stm32f4xx_spi.c
SRC += $(STDPERIPH_PATH)/Src/stm32f4xx_adc.c
SRC += $(STDPERIPH_PATH)/Src/stm32f4xx_syscfg.c
SRC += $(STDPERIPH_PATH)/Src/stm32f4xx_exti.c

# # List C source files for board specific
SRC += $(BOARD_PATH)/drivers/ms_timer.c
SRC += $(BOARD_PATH)/drivers/gpio_driver.c
SRC += $(BOARD_PATH)/drivers/serial_driver.c

SRC += $(BOARD_PATH)/library/system_stm32f446.c
SRC += $(BOARD_PATH)/library/cpu_driver.c

#SRC += $(BOARD_PATH)/library/adc.c
#SRC += $(BOARD_PATH)/library/ms_timer.c
#SRC += $(BOARD_PATH)/library/usart_driver.c
#SRC += $(BOARD_PATH)/library/gpio_driver.c
#SRC += $(BOARD_PATH)/library/spi_driver.c
#SRC += $(BOARD_PATH)/library/counter_driver.c
#SRC += $(BOARD_PATH)/library/socket_library.c

# List ASM source files here
ASRC += $(BOARD_PATH)/library/startup_stm32f446xx.s

#
# End of application section
##############################################################################################

