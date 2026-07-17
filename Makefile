CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude
LDFLAGS = -luser32 -lpsapi

TARGET = keywatch
SOURCES = src/main.cpp src/app/keylogger.cpp src/input/key_to_string.cpp \
          src/input/modifiers.cpp src/output/logger.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

debug: CXXFLAGS += -g -DDEBUG
debug: clean all
