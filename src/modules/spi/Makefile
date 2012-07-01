#!/usr/bin/make

# Objects compiled for the general use of the library
MODULE_OBJECTS = 
MODULE_CPP_OBJECTS = 

# Include dirs
INCLUDES += -I $(MODULE_DIR)/include

# Add CPP objects if necessary
ifeq ($(LANGUAGE), CPP)
    MODULE_OBJECTS += $(CPP_OBJECTS)
    INCLUDES += -I $(MODULE_DIR)/include/cpp
endif

# Add path to objects
COMMON_OBJECTS += $(addprefix $(MODULE_DIR)/, $(MODULE_OBJECTS))

# Include the appropriate Makefile
ifneq "$(ARCH)" "" 
    MODULE_ARCH_DIR := $(shell dirname $(MODULE_DIR)/ports/$(ARCH))
    include $(MODULE_ARCH_DIR)/Makefile
endif


