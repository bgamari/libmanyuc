#!/usr/bin/make

# If no LIB_BASE dir defined, define it as .
LIB_BASE ?= .

# Include user configuration
include $(LIB_BASE)/config.mk

# Port object must be defined here as empty
# Then added in the modules and ports
PORT_OBJECTS := 

# Objects compiled for the general use of the library
COMMON_OBJECTS := io.o hash.o swtimer.o
CPP_OBJECTS := cpp/pin.o cpp/bus.o

INCLUDES := -I $(LIB_BASE)/include
INCLUDES_CPP := -I $(LIB_BASE)/include/cpp

# Select objects and project compiler according to the language
ifeq ($(LANGUAGE), CPP)
    PCC = $(CXX)
    INCLUDES += $(INCLUDES_CPP)
    COMMON_OBJECTS += $(CPP_OBJECTS)
else
    PCC = $(CC)
endif

# Add path to objects
COMMON_OBJECTS := $(addprefix $(LIB_BASE)/, $(COMMON_OBJECTS))

# List of objects in assembler
ASSEMBLER_OBJECTS := $(OBJECTS:.o=.s)

# Add modules
MODULE_DIRS := $(LIB_BASE)/modules/spi $(LIB_BASE)/modules/accelerometer
MODULE_FILES := $(foreach MODULE_DIR,$(MODULE_DIRS),$(MODULE_DIR)/Makefile)
include $(MODULE_FILES)

# Include the appropriate Makefile
ARCH_DIR := $(LIB_BASE)/ports/$(ARCH)
ifneq "$(ARCH)" "" 
include $(ARCH_DIR)/Makefile
endif

#########################################################################

all: $(PROJECT).hex $(PROJECT).bin

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary -j .text -j .data $(PROJECT).elf $(PROJECT).bin

$(PROJECT).hex: $(PROJECT).elf
	$(OBJCOPY) -R .stack -O ihex $(PROJECT).elf $(PROJECT).hex

$(PROJECT).elf: $(PORT_OBJECTS) $(COMMON_OBJECTS) $(OBJECTS)
	$(PCC) $(LDFLAGS) $(OBJECTS) $(PORT_OBJECTS) $(COMMON_OBJECTS) -o $(PROJECT).elf

stats: $(PROJECT).elf
	$(SIZE) $(PROJECT).elf

assembler: $(ASSEMBLER_OBJECTS)

clean:
	$(REMOVE) $(OBJECTS)
	$(REMOVE) $(ASSEMBLER_OBJECTS)
	$(REMOVE) $(PORT_OBJECTS)
	$(REMOVE) $(COMMON_OBJECTS)
	$(REMOVE) $(PROJECT).hex
	$(REMOVE) $(PROJECT).elf
	$(REMOVE) $(PROJECT).map
	$(REMOVE) $(PROJECT).bin
	$(REMOVE) *.lst

#########################################################################
#  Default rules to compile .c and .cpp file to .o
#  assemble .s files to .o
#  .c or .cpp files to .s

.c.o :
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

.cpp.o :
	$(CXX) $(CPPFLAGS) -c $< -o $(<:.cpp=.o)

.s.o :
	#$(AS) $(ASFLAGS) -o $(notdir $@) $< > $(notdir $(basename $@)).lst
	$(AS) $(ASFLAGS) -o $@ $< > $(basename $@).lst

.c.s :
	$(CC) $(CFLAGS) $< -S 

.cpp.s :
	$(CXX) $(CPPFLAGS) $< -S 

#########################################################################

indent:
	astyle --indent-classes --indent-cases --indent-preprocessor \
		--pad-oper --pad-header --unpad-paren --convert-tabs \
		--keep-one-line-statements --indent=spaces=4 --brackets=attach \
		--align-pointer=name --mode=c --lineend=linux --suffix=none \
		--recursive '*.c' --recursive '*.cpp' \
		--recursive '../demo/*.c' --recursive '../demo/*.cpp' 
	astyle --pad-oper --pad-header --unpad-paren --convert-tabs \
		--indent=spaces=4 --align-pointer=name --mode=c --lineend=linux \
		--suffix=none --brackets=break --recursive '*.h' --recursive '../demo/*.h'

.PHONY: indent
