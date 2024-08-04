# Compiler
CXX := g++

# Directories
SRC_DIR := source
INC_DIR := include
BUILD_DIR := build

# Files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(filter-out main.cpp, $(SRCS)))
MAIN_OBJ := $(BUILD_DIR)/main.o
DEPS := $(wildcard $(INC_DIR)/*.hpp)

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -g -I$(INC_DIR)
LDFLAGS := -pthread

# OS-specific settings
ifeq ($(OS),Windows_NT)
    CXXFLAGS += -I/usr/include
    LDFLAGS += -L/usr/lib
    MKDIR_CMD = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM_CMD = if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
    RM_EXEC_CMD = if exist $(TARGET).exe del $(TARGET).exe
else
    # Linux-specific flags
    CXXFLAGS += -I/usr/include
    LDFLAGS += -pthread -L/usr/lib
    MKDIR_CMD = mkdir -p $(BUILD_DIR)
    RM_CMD = rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)
    RM_EXEC_CMD = rm -f $(TARGET)
endif

# Output executables
TARGET := execGrupoX

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $(OBJS) $(MAIN_OBJ) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM_CMD)
	@$(RM_EXEC_CMD)
