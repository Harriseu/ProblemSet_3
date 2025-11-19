#pragma once
#include "Entity.h"
#include "EntityVisitor.h"

/**
 * Item entity that can be collected by the player
 */
class Item : public Entity {
private:
    int fValue;
    bool fIsCollected;

public:
    Item(const std::string& aName, const std::string& aDescription, int aValue)
        : Entity(aName, aDescription), fValue(aValue), fIsCollected(false) {}

    // Getter and setter methods
    int getValue() const { return fValue; }
    bool isCollected() const { return fIsCollected; }
    void collect() { fIsCollected = true; }

    // Accept method for Visitor pattern
    void accept(EntityVisitor& aVisitor) override {
        aVisitor.visitItem(*this);
    }
};
