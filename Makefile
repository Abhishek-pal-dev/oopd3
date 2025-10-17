# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Source files
SRCS = main.cpp Student.cpp StudentDatabase.cpp Trie.cpp
OBJS = $(SRCS:.cpp=.o)

# Executable name
BIN = main

# Default target
all: $(BIN)

# Link object files
$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(BIN)

.PHONY: all clean
