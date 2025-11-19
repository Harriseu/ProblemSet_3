#pragma once
#include "EntityVisitor.h"
#include "Monster.h"
#include "Item.h"
#include "Clue.h"
#include "Player.h"
#include <iostream>

/**
 * Concrete Visitor: Attack Action
 * Allows player to attack monsters
 */
class AttackAction : public EntityVisitor {
private:
    Player& fPlayer;

public:
    AttackAction(Player& aPlayer) : fPlayer(aPlayer) {}

    void visitMonster(Monster& aMonster) override {
        if (!aMonster.isAlive()) {
            std::cout << "The " << aMonster.getName() << " is already dead." << std::endl;
            return;
        }

        std::cout << "\n" << fPlayer.getName() << " attacks the " << aMonster.getName() << "!" << std::endl;
        aMonster.takeDamage(fPlayer.getAttackPower());
        std::cout << "You deal " << fPlayer.getAttackPower() << " damage!" << std::endl;

        if (!aMonster.isAlive()) {
            std::cout << "The " << aMonster.getName() << " has been defeated!" << std::endl;
            fPlayer.addScore(50);
            std::cout << "+50 points!" << std::endl;
        } else {
            std::cout << "The " << aMonster.getName() << " has " << aMonster.getHealth()
                     << " health remaining." << std::endl;
            std::cout << "\nThe " << aMonster.getName() << " strikes back!" << std::endl;
            fPlayer.takeDamage(aMonster.getDamage());
            std::cout << "You take " << aMonster.getDamage() << " damage! Health: "
                     << fPlayer.getHealth() << "/" << fPlayer.getMaxHealth() << std::endl;
        }
    }

    void visitItem(Item& aItem) override {
        std::cout << "You can't attack the " << aItem.getName() << "! Try collecting it instead." << std::endl;
    }

    void visitClue(Clue& aClue) override {
        std::cout << "You can't attack the " << aClue.getName() << "! Try examining it instead." << std::endl;
    }
};

/**
 * Concrete Visitor: Collect Action
 * Allows player to collect items
 */
class CollectAction : public EntityVisitor {
private:
    Player& fPlayer;

public:
    CollectAction(Player& aPlayer) : fPlayer(aPlayer) {}

    void visitMonster(Monster& aMonster) override {
        std::cout << "You can't collect the " << aMonster.getName() << "! Try attacking it instead." << std::endl;
    }

    void visitItem(Item& aItem) override {
        if (aItem.isCollected()) {
            std::cout << "You have already collected the " << aItem.getName() << "." << std::endl;
            return;
        }

        std::cout << "\nYou collect the " << aItem.getName() << "!" << std::endl;
        std::cout << aItem.getDescription() << std::endl;
        aItem.collect();
        fPlayer.addToInventory(aItem.getName());
        fPlayer.addScore(aItem.getValue());
        std::cout << "+" << aItem.getValue() << " points!" << std::endl;
    }

    void visitClue(Clue& aClue) override {
        std::cout << "You can't collect the " << aClue.getName() << "! Try examining it instead." << std::endl;
    }
};

/**
 * Concrete Visitor: Examine Action
 * Allows player to examine clues and get information
 */
class ExamineAction : public EntityVisitor {
private:
    Player& fPlayer;

public:
    ExamineAction(Player& aPlayer) : fPlayer(aPlayer) {}

    void visitMonster(Monster& aMonster) override {
        std::cout << "\nYou examine the " << aMonster.getName() << ":" << std::endl;
        std::cout << aMonster.getDescription() << std::endl;
        if (aMonster.isAlive()) {
            std::cout << "Health: " << aMonster.getHealth() << std::endl;
            std::cout << "Damage: " << aMonster.getDamage() << std::endl;
            std::cout << "Status: Hostile and ready to attack!" << std::endl;
        } else {
            std::cout << "Status: Defeated" << std::endl;
        }
    }

    void visitItem(Item& aItem) override {
        std::cout << "\nYou examine the " << aItem.getName() << ":" << std::endl;
        std::cout << aItem.getDescription() << std::endl;
        std::cout << "Value: " << aItem.getValue() << " points" << std::endl;
        if (aItem.isCollected()) {
            std::cout << "Status: Already collected" << std::endl;
        } else {
            std::cout << "Status: Available to collect" << std::endl;
        }
    }

    void visitClue(Clue& aClue) override {
        std::cout << "\nYou examine the " << aClue.getName() << ":" << std::endl;
        std::cout << aClue.getDescription() << std::endl;

        if (!aClue.isExamined()) {
            std::cout << "\n*** Hidden Information Revealed: ***" << std::endl;
            std::cout << aClue.getHiddenInfo() << std::endl;
            aClue.examine();
            fPlayer.addScore(25);
            std::cout << "+25 points for discovering a clue!" << std::endl;
        } else {
            std::cout << "\nPreviously discovered: " << aClue.getHiddenInfo() << std::endl;
        }
    }
};
