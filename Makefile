CC = gcc
CFLAGS = -Wall -I./include
TARGET = cpu_scheduler
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Create bin and obj directories if they don't exist
$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR))

# Default target
all: $(BIN_DIR)/$(TARGET)

# Link object files to create the executable
$(BIN_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/$(TARGET)

# Run the program
run: all
	./$(BIN_DIR)/$(TARGET)

# Phony targets
.PHONY: all clean run
