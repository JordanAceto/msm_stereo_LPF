
TARGET = executable

CPP_STD = -std=c++17

BSP_DIR         = ./BSP/
LIB_DIR         = ./lib/
SRC_DIR         = ./src/
THIRD_PARTY_DIR = ./third_party/
CMSIS_DEV_DIR   = $(THIRD_PARTY_DIR)CMSIS/Device/
CMSIS_INC_DIR   = $(THIRD_PARTY_DIR)CMSIS/Include/
BIN_DIR         = ./bin/

LD_SCRIPT = $(THIRD_PARTY_DIR)STM32L031F4Px_FLASH.ld

CPU = -mcpu=cortex-m0plus
MCU = $(CPU) -mthumb

TOOLCHAIN   = arm-none-eabi
COMPILER    = $(TOOLCHAIN)-g++
OBJECT_COPY = $(TOOLCHAIN)-objcopy
OBJECT_DUMP = $(TOOLCHAIN)-objdump
OBJECT_SIZE = $(TOOLCHAIN)-size

OPTIONS += $(MCU)
OPTIONS += $(CPP_STD)
OPTIONS += -O3
OPTIONS += -Wall -Wextra -Wpedantic -Wshadow -Wconversion
OPTIONS += -mlittle-endian
OPTIONS += -fdata-sections
OPTIONS += -ffunction-sections
OPTIONS += -fno-strict-aliasing
OPTIONS += --specs=nosys.specs
OPTIONS += -nostdlib
OPTIONS += -fno-exceptions
OPTIONS += -fno-unwind-tables
OPTIONS += -fno-rtti
OPTIONS += -flto

ASM_FLAGS += -c
ASM_FLAGS += -x
ASM_FLAGS += assembler-with-cpp
ASM_FLAGS += $(OPTIONS)

CPP_FLAGS += -c
CPP_FLAGS += $(OPTIONS)
CPP_FLAGS += $(CPP_STD)
CPP_FLAGS += -I$(BSP_DIR)
CPP_FLAGS += -I$(LIB_DIR)
CPP_FLAGS += -I$(SRC_DIR)
CPP_FLAGS += -I$(CMSIS_DEV_DIR)
CPP_FLAGS += -I$(CMSIS_INC_DIR)

L_FLAGS += $(MCU)
L_FLAGS += -specs=nano.specs
L_FLAGS += -mthumb
L_FLAGS += -T./$(LD_SCRIPT)
L_FLAGS += -lc -lm -lnosys
L_FLAGS += -flto
L_FLAGS += -Wl,--gc-sections
L_FLAGS += -Wl,--print-memory-usage

OBJ_COPY_FLAGS += -S
OBJ_COPY_FLAGS += -O
OBJ_COPY_FLAGS += binary

CPP_OBJECT_FILES := $(patsubst $(BSP_DIR)%.cpp,$(BIN_DIR)%.o,$(wildcard $(BSP_DIR)*.cpp))
CPP_OBJECT_FILES += $(patsubst $(LIB_DIR)%.cpp,$(BIN_DIR)%.o,$(wildcard $(LIB_DIR)*.cpp))
CPP_OBJECT_FILES += $(patsubst $(SRC_DIR)%.cpp,$(BIN_DIR)%.o,$(wildcard $(SRC_DIR)*.cpp))
ASM_OBJECT_FILES := $(patsubst $(THIRD_PARTY_DIR)%.s,$(BIN_DIR)%.o,$(wildcard $(THIRD_PARTY_DIR)*.s))

# build the application
all: $(CPP_OBJECT_FILES) $(BIN_DIR)
	make $(BIN_DIR)$(TARGET).bin

$(CPP_OBJECT_FILES): | $(BIN_DIR)

$(BIN_DIR)%.o: $(BSP_DIR)%.cpp
	$(COMPILER) $(CPP_FLAGS) $< -o $@

$(BIN_DIR)%.o: $(LIB_DIR)%.cpp
	$(COMPILER) $(CPP_FLAGS) $< -o $@

$(BIN_DIR)%.o: $(SRC_DIR)%.cpp
	$(COMPILER) $(CPP_FLAGS) $< -o $@

$(BIN_DIR)%.o: $(THIRD_PARTY_DIR)%.s
	$(COMPILER) $(ASM_FLAGS) $< -o $@

# make the elf file
$(BIN_DIR)$(TARGET).elf: $(CPP_OBJECT_FILES) $(ASM_OBJECT_FILES)
	$(COMPILER) $^ $(L_FLAGS) -o $@

# make the binary file and show the size in the terminal
$(BIN_DIR)$(TARGET).bin: $(BIN_DIR)$(TARGET).elf
	$(OBJECT_COPY) $(OBJ_COPY_FLAGS) $< $@
	$(OBJECT_DUMP) -D $< > $(BIN_DIR)$(TARGET).list

# flash the mcu
write: $(BIN_DIR)$(TARGET).bin
	st-flash --connect-under-reset --hot-plug write $(BIN_DIR)$(TARGET).bin 0x08000000

# if ./bin/ does not exist, create the directory
$(BIN_DIR):
	mkdir $@

clean:
	rm -f $(BIN_DIR)*.o
	rm -f $(BIN_DIR)*.out
	rm -f $(BIN_DIR)*.elf
	rm -f $(BIN_DIR)*.bin
	rm -f $(BIN_DIR)*.list
