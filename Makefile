CXX := x86_64-w64-mingw32-g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -Iinclude

SRC := $(shell find src -name '*.cpp')
OBJ := $(SRC:src/%.cpp=build/%.o)
TARGET := build/keywatch.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build
