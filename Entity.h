#pragma once
#include <string>

// Forward declaration for Visitor pattern
class EntityVisitor;

/**
 * Abstract base class for all game entities
 * Uses the Visitor pattern to allow different actions to be performed on entities
 */
class Entity {
protected:
    std::string fName;
    std::string fDescription;

public:
    Entity(const std::string& aName, const std::string& aDescription)
        : fName(aName), fDescription(aDescription) {}

    virtual ~Entity() = default;

    // Getter methods
    const std::string& getName() const { return fName; }
    const std::string& getDescription() const { return fDescription; }

    // Accept method for Visitor pattern
    virtual void accept(EntityVisitor& aVisitor) = 0;
};
