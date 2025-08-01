SRC_DIR := src
BIN_DIR := bin
BUILD_DIR := build

TARGET := $(BIN_DIR)/vcc
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CC := gcc
CFLAGS := -Wall -Wextra

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(BUILD_DIR):
	mkdir -p $@

.PHONY: all clean run

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) .vcc

run: $(TARGET)
	./$(TARGET) init

