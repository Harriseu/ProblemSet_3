# Makefile for Problem Set 3 - Dungeon Crawler

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET = dungeon_crawler

# Source files
SOURCES = main.cpp
HEADERS = Entity.h Monster.h Item.h Clue.h Player.h EntityVisitor.h PlayerActions.h Room.h Dungeon.h

# Build target
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Clean build files
clean:
	rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
