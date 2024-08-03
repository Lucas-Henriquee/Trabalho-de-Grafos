# Compiler
CXX := g++

# Directories
SRC_DIR := source
INC_DIR := include
TEST_DIR := test
BUILD_DIR := build

# Files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(filter-out main.cpp, $(SRCS)))
MAIN_OBJ := $(BUILD_DIR)/main.o
DEPS := $(wildcard $(INC_DIR)/*.hpp)

# Test files
TEST_SRCS := $(TEST_DIR)/testGraphOperations.cpp
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))
TEST_TARGET := $(BUILD_DIR)/runTests

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -g -I$(INC_DIR)
LDFLAGS := -pthread

# OS-specific settings
ifeq ($(OS),Windows_NT)
    CXXFLAGS += -I/usr/include
    LDFLAGS += -L/usr/lib -lCatch2WithMain
else
    # Linux-specific flags
    CXXFLAGS += -I/usr/include
    LDFLAGS += -pthread -L/usr/lib -lCatch2WithMain
endif

# Output executables
TARGET := execGrupoX
TEST_TARGET := runTests

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $(OBJS) $(MAIN_OBJ) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.cpp $(DEPS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp $(DEPS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_TARGET): $(TEST_OBJS) $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) $(OBJS) -o $(TEST_TARGET) $(LDFLAGS)

test: $(TEST_TARGET)
	@./$(TEST_TARGET)

clean:
	@rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)
