#!/usr/bin/make

#  List of the objects files to be compiled/assembled
MY_PORT_OBJECTS = startup_LPC17xx.o port.o io.o serial.o syscalls.o adc.o pwm.o timers.o i2c.o
PORT_OBJECTS += $(addprefix $(ARCH_COMMON_DIR)/, $(MY_PORT_OBJECTS))

# Linking script
LSCRIPT=$(ARCH_COMMON_DIR)/LPC17xx.ld

DEBUG ?= -g
OPTIMIZATION ?= 0
#LISTING = -ahls

#  Compiler Options
CFLAGS := $(CFLAGS) -fno-common -mcpu=cortex-m3 -mthumb -I./ -I$(ARCH_DIR) -I$(ARCH_COMMON_DIR) $(INCLUDES) -O$(OPTIMIZATION) $(DEBUG) 
LDFLAGS := $(LDFLAGS) -mcpu=cortex-m3 -mthumb -O$(OPTIMIZATION) -nostartfiles -Wl,-Map=$(PROJECT).map -T$(LSCRIPT) 
ASFLAGS = $(LISTING) -mcpu=cortex-m3

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

