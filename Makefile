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

# Default Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -g -I$(INC_DIR)

# Linker flags
LDFLAGS := -lgtest -lgtest_main -lpthread

# OS-specific settings
ifeq ($(OS),Windows_NT)
    MKDIR_CMD = @if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM_DIR_CMD = @if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
    RM_TARGET_CMD = @if exist $(TARGET).exe del $(TARGET).exe
    RM_TEST_CMD = @if exist $(TEST_TARGET).exe del $(TEST_TARGET).exe
else
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
	$(CXX) $(CXXFLAGS) $(OBJS) $(MAIN_OBJ) -o $(TARGET)

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
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) $(OBJS) $(LDFLAGS) -o $(TEST_TARGET)

# Check for gtest library
check_gtest:
	@echo "Checking for gtest library..."
	@echo '#include <gtest/gtest.h>' > $(BUILD_DIR)/test_gtest.cpp
	@echo 'int main(int argc, char **argv) { ::testing::InitGoogleTest(&argc, argv); return 0; }' >> $(BUILD_DIR)/test_gtest.cpp
	@$(CXX) $(CXXFLAGS) $(BUILD_DIR)/test_gtest.cpp -o $(BUILD_DIR)/test_gtest $(LDFLAGS) > /dev/null 2>&1 || (echo "Error: gtest library is required but not found." && exit 1)
	@rm -f $(BUILD_DIR)/test_gtest $(BUILD_DIR)/test_gtest.cpp

test: $(TEST_TARGET) check_gtest
	@./$(TEST_TARGET)

clean:
	@$(RM_DIR_CMD)
	@$(RM_TARGET_CMD)
	@$(RM_TEST_CMD)