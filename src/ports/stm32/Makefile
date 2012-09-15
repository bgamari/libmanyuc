#!/usr/bin/make

STM_CHIP = stm32f4xx

ifeq ($(STM_CHIP),stm32f4xx)
	MCPU = cortex-m4
else
	MCPU = cortex-m3
endif

#  List of the objects files to be compiled/assembled
PORT_OBJECTS = startup_$(STM_CHIP).o port.o io.o serial.o syscalls.o \
	       adc.o pwm.o timers.o i2c.o dma.o
PORT_OBJECTS := $(addprefix $(ARCH_COMMON_DIR)/, $(PORT_OBJECTS))

LSCRIPT=$(ARCH_COMMON_DIR)/$(STM_CHIP).ld

DEBUG ?= -g
OPTIMIZATION ?= 0

#  Compiler Options - Add whatever's needed
CFLAGS := $(CFLAGS) -fno-common -mcpu=$(MCPU) -mthumb -I./ -I$(ARCH_DIR) -I$(ARCH_COMMON_DIR) $(INCLUDES) -O$(OPTIMIZATION) $(DEBUG) 
LDFLAGS := $(LDFLAGS) -mcpu=$(MCPU) -mthumb -O$(OPTIMIZATION) -nostartfiles -Wl,-Map=$(PROJECT).map -T$(LSCRIPT)
ASFLAGS = $(LISTING) -mcpu=$(MCPU)

CPPFLAGS = $(CFLAGS)
CPPFLAGS += -fno-rtti -fno-exceptions

#  Compiler/Assembler/Linker Paths
CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
REMOVE = rm -f

