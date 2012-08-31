#!/usr/bin/make

#  List of the objects files to be compiled/assembled
PORT_OBJECTS = startup_STM32F4xx.o io.o serial.o syscalls.o adc.o pwm.o timers.o i2c.o
PORT_OBJECTS := $(addprefix $(ARCH_COMMON_DIR)/, $(PORT_OBJECTS))

LSCRIPT=$(ARCH_COMMON_DIR)/stm32f4.ld

DEBUG ?= -g
OPTIMIZATION ?= 0

#  Compiler Options - Add whatever's needed
CFLAGS := $(CFLAGS) -fno-common -mcpu=cortex-m3 -mthumb -I./ -I$(ARCH_DIR) -I$(ARCH_COMMON_DIR) $(INCLUDES) -O$(OPTIMIZATION) $(DEBUG) 
LDFLAGS := $(LDFLAGS) -mcpu=cortex-m3 -mthumb -O$(OPTIMIZATION) -nostartfiles -Wl,-Map=$(PROJECT).map -T$(LSCRIPT) 
ASFLAGS = $(LISTING) -mcpu=cortex-m3

CPPFLAGS = $(CFLAGS)
CPPFLAGS += -fno-rtti -fno-exceptions

#  Compiler/Assembler/Linker Paths
CC = 
CXX =
AS =
LD =
OBJCOPY = 
SIZE = 
REMOVE = 

