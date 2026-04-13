# Compiler and Linker
CC = gcc

# Compiler Flags
# -Wall: enable all warnings
# -Iinclude: look for header files in the include/ directory
CFLAGS = -Wall -Iinclude

# Linker Flags
# -lgpiod: link the GPIO library
# -lm: link the math library (required if you use sqrt or floats)
LDFLAGS = -lgpiod -lm

# Directories
SRC_DIR = src
DRV_DIR = drivers
OBJ_DIR = obj

# Source files
SRCS = $(SRC_DIR)/main.c \
       $(DRV_DIR)/adxl.c \
       $(DRV_DIR)/DS3231.c \
       $(DRV_DIR)/i2c_master.c

# Object files (transform .c paths to obj/.o paths)
OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/adxl.o \
       $(OBJ_DIR)/DS3231.o \
       $(OBJ_DIR)/i2c_master.o

# Target executable
TARGET = firmware_app

# Default rule: build the target
all: $(OBJ_DIR) $(TARGET)

# Rule to create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Linking stage: Combine all .o files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compilation stage: Build object files from .c files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(DRV_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule: Remove objects and executable
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean