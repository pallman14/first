# Set the C++ compiler
# CXX = clang++  # Change this to clang++ if you want to use Clang
CXX = g++   # Uncomment this line to use g++

# Compiler flags
CXXFLAGS = -Wall -g -std=c++17

# Executable name
TARGET = first

# Source files
SRCS = main.cpp grammar.cpp non_terminal.cpp terminal.cpp production.cpp

# Header files
HEADERS = grammar.h non_terminal.h terminal.h production.h

# Object files (generated from source files)
OBJS = $(SRCS:.cpp=.o)

# Default target to build the executable
all: $(TARGET)

# Rule to build the executable by linking object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files from .cpp source files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets to avoid conflicts with files named 'clean' or 'all'
.PHONY: all clean

