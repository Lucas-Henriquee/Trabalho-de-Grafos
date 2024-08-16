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
    RM_CMD = @if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR) && if exist $(TARGET).exe del $(TARGET).exe && if exist $(TEST_TARGET).exe del $(TEST_TARGET).exe
    TEST_CMD = $(CXX) $(CXXFLAGS) $(BUILD_DIR)\test_gtest.cpp -o $(BUILD_DIR)\test_gtest $(LDFLAGS)
else
    MKDIR_CMD = @mkdir -p $(BUILD_DIR)
    RM_CMD = @rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)
    TEST_CMD = $(CXX) $(CXXFLAGS) $(BUILD_DIR)/test_gtest.cpp -o $(BUILD_DIR)/test_gtest $(LDFLAGS)
endif

# Output executables
TARGET := execGrupoX

.PHONY: all clean test check_gtest

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $(OBJS) $(MAIN_OBJ) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp $(DEPS) check_gtest
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_TARGET): $(TEST_OBJS) $(OBJS) check_gtest
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) $(OBJS) $(LDFLAGS) -o $(TEST_TARGET)

# Check if gtest library is installed
check_gtest:
ifeq ($(OS),Windows_NT)
	@echo Checking if gtest is installed...
	@where gtest.lib >nul 2>&1 && \
		echo Google Test is installed. Compiling and running tests... || \
		(echo Google Test is not installed. Please install it manually and rerun make test. && exit 1)
else
	@echo Checking for gtest library...
	@dpkg -l | grep -q libgtest-dev && \
		echo "Google Test is installed. Compiling and running tests..." || \
		(echo -n "Google Test is not installed. Would you like to install it now? (y/n): " && \
		read -r answer && \
		if [ "$$answer" = "y" ]; then \
			echo "Installing Google Test..."; \
			sudo apt-get update && sudo apt-get install -y googletest libgtest-dev; \
			echo "Google Test installed successfully. Please run 'make test' again."; \
			exit 1; \
		else \
			echo "Google Test is required to run tests. Please install it manually and run 'make test' again."; \
			exit 1; \
		fi)
endif

test: $(TEST_TARGET)
ifeq ($(OS),Windows_NT)
	@$(BUILD_DIR)\$(TEST_TARGET).exe
else
	@./$(TEST_TARGET)
endif

clean:
	@$(RM_CMD)
