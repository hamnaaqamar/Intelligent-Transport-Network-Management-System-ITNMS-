# Makefile for Intelligent Transport Network Management System (ITNMS)
# CS221 Semester Project

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = itnms
SOURCES = main.cpp Graph.cpp Queue.cpp Stack.cpp HashTable.cpp BST.cpp Heap.cpp SearchSort.cpp Analytics.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = Graph.h Queue.h Stack.h HashTable.h BST.h Heap.h SearchSort.h Analytics.h

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Build successful! Run ./$(TARGET) to start the program."

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete."

# Run the program
run: $(TARGET)
	./$(TARGET)

# Rebuild everything
rebuild: clean all

.PHONY: all clean run rebuild

