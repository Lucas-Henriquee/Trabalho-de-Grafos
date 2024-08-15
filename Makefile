# Compiler
CXX := g++

# Directories
SRC_DIR := source
INC_DIR := include
BUILD_DIR := build
TEST_DIR := test

# Files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(filter-out main.cpp, $(SRCS)))
MAIN_OBJ := $(BUILD_DIR)/main.o
DEPS := $(wildcard $(INC_DIR)/*.hpp)

# Test files
TEST_SRCS := $(TEST_DIR)/testDirected.cpp $(TEST_DIR)/testUndirected.cpp $(TEST_DIR)/testGraph.cpp
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))
TEST_TARGET := runTests

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -g -I$(INC_DIR)
LDFLAGS := -pthread

# OS-specific settings
ifeq ($(OS),Windows_NT)
    CXXFLAGS += -I/usr/include
    LDFLAGS += -L/usr/lib
    MKDIR_CMD = @if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM_DIR_CMD = @if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
    RM_TARGET_CMD = @if exist $(TARGET).exe del $(TARGET).exe
    RM_TEST_CMD = @if exist $(TEST_TARGET).exe del $(TEST_TARGET).exe
else
    # Linux-specific flags
    CXXFLAGS += -I/usr/include
    LDFLAGS += -pthread -L/usr/lib
    MKDIR_CMD = @mkdir -p $(BUILD_DIR)
    RM_DIR_CMD = @rm -rf $(BUILD_DIR)
    RM_TARGET_CMD = @rm -f $(TARGET)
    RM_TEST_CMD = @rm -f $(TEST_TARGET)
endif

# Output executables
TARGET := execGrupoX

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $(OBJS) $(MAIN_OBJ) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_TARGET): $(TEST_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) $(OBJS) -o $(TEST_TARGET) $(LDFLAGS) -lCatch2WithMain

test: $(TEST_TARGET)
	@./$(TEST_TARGET)

clean:
	@$(RM_DIR_CMD)
	@$(RM_TARGET_CMD)
	@$(RM_TEST_CMD)
