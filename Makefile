# Compiler
CXX := g++

# Directories
SRC_DIR := source
INC_DIR := include
BUILD_DIR := build
TEST_DIR := test

# Source and header files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(filter-out main.cpp, $(SRCS)))
MAIN_OBJ := $(BUILD_DIR)/main.o
DEPS := $(wildcard $(INC_DIR)/*.hpp)

# Test files
TEST_SRCS := $(TEST_DIR)/testGraph.cpp $(TEST_DIR)/testDirected.cpp $(TEST_DIR)/testUndirected.cpp 
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))
TEST_TARGET := runTests

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -g -I$(INC_DIR)

# OS-specific settings
ifeq ($(OS),Windows_NT)
    # Windows-specific settings using vcpkg
    CXXFLAGS += -I$(VCPKG_ROOT)/installed/x64-windows/include
    LDFLAGS += -L$(VCPKG_ROOT)/installed/x64-windows/lib -lCatch2Main -lCatch2
    MKDIR_CMD = @if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM_DIR_CMD = @if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
    RM_TARGET_CMD = @if exist $(TARGET).exe del $(TARGET).exe
    RM_TEST_CMD = @if exist $(TEST_TARGET).exe del $(TEST_TARGET).exe
else
    # Unix-specific flags
    CXXFLAGS += -I/usr/include/catch2
    LDFLAGS += -pthread -lCatch2Main -lCatch2
    MKDIR_CMD = @mkdir -p $(BUILD_DIR)
    RM_DIR_CMD = @rm -rf $(BUILD_DIR)
    RM_TARGET_CMD = @rm -f $(TARGET)
    RM_TEST_CMD = @rm -f $(TEST_TARGET)
endif

# Ensure Catch2 is installed (Unix only)
ifeq ($(OS),Windows_NT)
    # No special Catch2 installation check for Windows, assuming vcpkg handles it
else
    # Unix-specific Catch2 check
    $(BUILD_DIR)/.catch2_installed:
	@if [ ! -f /usr/include/catch2/catch.hpp ]; then echo "Catch2 not found, please install it using your package manager."; exit 1; fi
	@touch $(BUILD_DIR)/.catch2_installed
endif
$(TEST_DIR)/testGraph.cpp
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

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp $(DEPS) $(BUILD_DIR)/.catch2_installed
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_TARGET): $(TEST_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) $(OBJS) -o $(TEST_TARGET) $(LDFLAGS)

test: $(TEST_TARGET)
	@./$(TEST_TARGET)

clean:
	@$(RM_DIR_CMD)
	@$(RM_TARGET_CMD)
	@$(RM_TEST_CMD)
