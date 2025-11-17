#pragma once
#include <string>
#include <vector>

/**
 * Player class represents the player character in the game
 */
class Player {
private:
    std::string fName;
    int fHealth;
    int fMaxHealth;
    int fAttackPower;
    std::vector<std::string> fInventory;
    int fScore;

public:
    Player(const std::string& aName, int aHealth = 100, int aAttackPower = 20)
        : fName(aName), fHealth(aHealth), fMaxHealth(aHealth),
          fAttackPower(aAttackPower), fScore(0) {}

    // Getter methods
    const std::string& getName() const { return fName; }
    int getHealth() const { return fHealth; }
    int getMaxHealth() const { return fMaxHealth; }
    int getAttackPower() const { return fAttackPower; }
    int getScore() const { return fScore; }
    const std::vector<std::string>& getInventory() const { return fInventory; }

    // Action methods
    void takeDamage(int aDamage) {
        fHealth -= aDamage;
        if (fHealth < 0) fHealth = 0;
    }

    void heal(int aAmount) {
        fHealth += aAmount;
        if (fHealth > fMaxHealth) fHealth = fMaxHealth;
    }

    void addToInventory(const std::string& aItem) {
        fInventory.push_back(aItem);
    }

    void addScore(int aPoints) {
        fScore += aPoints;
    }

    bool isAlive() const {
        return fHealth > 0;
    }

    void displayStatus() const {
        std::cout << "\n=== Player Status ===" << std::endl;
        std::cout << "Name: " << fName << std::endl;
        std::cout << "Health: " << fHealth << "/" << fMaxHealth << std::endl;
        std::cout << "Attack Power: " << fAttackPower << std::endl;
        std::cout << "Score: " << fScore << std::endl;
        std::cout << "Inventory: ";
        if (fInventory.empty()) {
            std::cout << "Empty" << std::endl;
        } else {
            std::cout << std::endl;
            for (const auto& item : fInventory) {
                std::cout << "  - " << item << std::endl;
            }
        }
        std::cout << "===================" << std::endl;
    }
};
