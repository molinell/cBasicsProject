ifeq ($(shell which clang 2>/dev/null),)
	CC = gcc
	CXX = g++
else
	CC = clang
	CXX = clang++
endif

CFLAGS += -c -std=c99 -g -Wall
EXECNAME = main
BUILD_DIR = build
SRC_DIR = src

C_FILES = $(wildcard $(SRC_DIR)/*.c)
COBJECTS = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

ifeq ($(OS),Windows_NT)
	RM=del /f /q
	EXECUTABLE = $(BUILD_DIR)/$(EXECNAME).exe
else
	RM=rm -f
	EXECUTABLE = $(BUILD_DIR)/$(EXECNAME)
endif

.PHONY: all

all: main run

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

main: $(COBJECTS)
	@echo "Linking for executable" $(EXECUTABLE)
	$(CC) $(COBJECTS) $(LDFLAGS) -o $(EXECUTABLE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling" $<
	$(CC) $(CFLAGS) $< -o $@

clean:
	@echo "Cleaning" $(C_FILES)
	$(RM) $(BUILD_DIR)/*

run:
	@echo "Running \"$(EXECUTABLE)\""
	@./$(EXECUTABLE)

