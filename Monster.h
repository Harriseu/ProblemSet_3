#pragma once
#include "Entity.h"
#include "EntityVisitor.h"

/**
 * Monster entity that can be fought by the player
 */
class Monster : public Entity {
private:
    int fHealth;
    int fDamage;
    bool fIsAlive;

public:
    Monster(const std::string& aName, const std::string& aDescription, int aHealth, int aDamage)
        : Entity(aName, aDescription), fHealth(aHealth), fDamage(aDamage), fIsAlive(true) {}

    // Getter and setter methods
    int getHealth() const { return fHealth; }
    int getDamage() const { return fDamage; }
    bool isAlive() const { return fIsAlive; }

    void takeDamage(int aDamage) {
        fHealth -= aDamage;
        if (fHealth <= 0) {
            fHealth = 0;
            fIsAlive = false;
        }
    }

    // Accept method for Visitor pattern
    void accept(EntityVisitor& aVisitor) override {
        aVisitor.visitMonster(*this);
    }
};
