PROJECT_NAME = tik-tac-toe
CC = gcc
CFLAGS = -g -Wall
SRC_DIR = src
BUILD_DIR = build
ASSETS_DIR = imgs

SOURCES = $(wildcard $(SRC_DIR)/*.c)
TARGET = $(BUILD_DIR)/$(PROJECT_NAME)

all: $(BUILD_DIR) $(ASSETS_DIR) $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

$(ASSETS_DIR): $(BUILD_DIR)
	cp -r $(SRC_DIR)/$(ASSETS_DIR)/* $(BUILD_DIR)/$(ASSETS_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/$(ASSETS_DIR)

clean:
	rm -rf $(BUILD_DIR)
