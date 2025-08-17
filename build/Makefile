CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I../include

SRC_DIR := ../src
INC_DIR := ../include
BUILD_DIR := .

SRCS := $(SRC_DIR)/main.cpp
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

TARGET := $(BUILD_DIR)/app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/Vector.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)

.PHONY: all clean
