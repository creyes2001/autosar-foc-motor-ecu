#====================Directories===================================
STM_STARTUP_DIR = Platform
STM_INCLUDE_DIR = Cmsis
LDSCRIPT = $(STM_STARTUP_DIR)/STM32F446RETx_FLASH.ld
 
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

INCLUDE_DIRS = $(STM_INCLUDE_DIR)\
 
#=====================TOOLCHAIN=================================
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

#=====================Files======================================
TARGET  = foc
 
SOURCES = main.c
          
 
ASM_SRCS = $(STM_STARTUP_DIR)/startup_stm32f446xx.s\
		   $(STM_STARTUP_DIR)/system_stm32g4xx.c

vpath %.c . \

C_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SOURCES)))
ASM_OBJS = $(patsubst %.s,$(OBJ_DIR)/%.o,$(notdir $(ASM_SRCS)))
OBJECTS = $(C_OBJS) $(ASM_OBJS)


#=====================Flags==================================
MCU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
WFLAGS = -Wall -Wextra  -Wshadow
CFLAGS = $(MCU) -O0 -g3 -ggdb $(WFLAGS) -DSTM32G431xx $(addprefix -I,$(INCLUDE_DIRS    ))
LDFLAGS = $(MCU) -T $(LDSCRIPT) --specs=nosys.specs --specs=nano.specs
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,--print-memory-usage

#Tell Make where to find .c and .s source files
VPATH = src:$(STM_STARTUP_DIR)

all: $(BUILD_DIR)/$(TARGET).elf $(BIN_DIR)/$(TARGET).bin

#Binary
$(BIN_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary $< $@

##Link
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC)  $(LDFLAGS) $^ -o $@

##Compile c
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^

#Assemble
$(OBJ_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(MCU) -c $< -o $@


size:
	$(SIZE) $(BUILD_DIR)/$(TARGET).elf

flash: $(BIN_DIR)/$(TARGET).bin
	openocd -f interface/stlink.cfg -f target/stm32g4x.cfg \
      -c "program $(BIN_DIR)/$(TARGET).bin 0x08000000 verify reset exit"


clean:
	rm -rf $(BUILD_DIR)

