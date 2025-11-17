#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Entity.h"

/**
 * Room class - represents a node in the dungeon tree
 * Each room can contain multiple entities and connect to other rooms (children)
 */
class Room {
private:
    std::string fName;
    std::string fDescription;
    std::vector<std::shared_ptr<Entity>> fEntities;
    std::vector<Room*> fConnectedRooms;  // Child nodes in the tree
    std::vector<std::string> fDoorNames;  // Names for each door/edge

public:
    Room(const std::string& aName, const std::string& aDescription)
        : fName(aName), fDescription(aDescription) {}

    // Getter methods
    const std::string& getName() const { return fName; }
    const std::string& getDescription() const { return fDescription; }
    const std::vector<std::shared_ptr<Entity>>& getEntities() const { return fEntities; }
    const std::vector<Room*>& getConnectedRooms() const { return fConnectedRooms; }
    const std::vector<std::string>& getDoorNames() const { return fDoorNames; }

    // Add an entity to this room
    void addEntity(std::shared_ptr<Entity> aEntity) {
        fEntities.push_back(aEntity);
    }

    // Connect this room to another room (add child node)
    void connectRoom(Room* aRoom, const std::string& aDoorName) {
        fConnectedRooms.push_back(aRoom);
        fDoorNames.push_back(aDoorName);
    }

    // Display room information
    void describe() const {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  " << fName << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << fDescription << std::endl;

        if (!fEntities.empty()) {
            std::cout << "\nYou see the following:" << std::endl;
            for (size_t i = 0; i < fEntities.size(); ++i) {
                std::cout << "  " << (i + 1) << ". " << fEntities[i]->getName()
                         << " - " << fEntities[i]->getDescription() << std::endl;
            }
        } else {
            std::cout << "\nThe room appears empty." << std::endl;
        }

        if (!fConnectedRooms.empty()) {
            std::cout << "\nDoors/Exits:" << std::endl;
            for (size_t i = 0; i < fDoorNames.size(); ++i) {
                std::cout << "  " << (i + 1) << ". " << fDoorNames[i] << std::endl;
            }
        } else {
            std::cout << "\nThere are no visible exits. This might be the final room!" << std::endl;
        }
        std::cout << "========================================" << std::endl;
    }

    // Get entity by index
    std::shared_ptr<Entity> getEntity(size_t aIndex) {
        if (aIndex < fEntities.size()) {
            return fEntities[aIndex];
        }
        return nullptr;
    }

    // Get connected room by index
    Room* getConnectedRoom(size_t aIndex) {
        if (aIndex < fConnectedRooms.size()) {
            return fConnectedRooms[aIndex];
        }
        return nullptr;
    }
};
