CC = gcc
CFLAGS = -g -O2
TARGET = cshell

BUILD_DIR = build
BIN_DIR = bin

SOURCES = repl.c 
OBJECTS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SOURCES))

all: $(BIN_DIR)/$(TARGET)
	$(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

 
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
