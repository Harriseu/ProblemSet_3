#pragma once
#include "Room.h"
#include <memory>
#include <vector>

/**
 * Dungeon class - manages the tree structure of rooms
 * The root room is the entrance to the dungeon
 */
class Dungeon {
private:
    Room* fRoot;  // Root node of the tree (entrance)
    std::vector<std::unique_ptr<Room>> fRooms;  // All rooms in the dungeon

public:
    Dungeon() : fRoot(nullptr) {}

    // Create and add a room to the dungeon
    Room* createRoom(const std::string& aName, const std::string& aDescription) {
        auto room = std::make_unique<Room>(aName, aDescription);
        Room* roomPtr = room.get();
        fRooms.push_back(std::move(room));
        return roomPtr;
    }

    // Set the entrance (root) of the dungeon
    void setEntrance(Room* aRoom) {
        fRoot = aRoom;
    }

    // Get the entrance room
    Room* getEntrance() const {
        return fRoot;
    }

    // Get total number of rooms
    size_t getRoomCount() const {
        return fRooms.size();
    }

    // Display dungeon statistics
    void displayInfo() const {
        std::cout << "\n=== Dungeon Information ===" << std::endl;
        std::cout << "Total Rooms: " << fRooms.size() << std::endl;
        std::cout << "Entrance: " << (fRoot ? fRoot->getName() : "Not set") << std::endl;
        std::cout << "==========================" << std::endl;
    }
};
