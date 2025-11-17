#pragma once

// Forward declarations
class Monster;
class Item;
class Clue;

/**
 * Abstract Visitor interface for performing actions on entities
 * This is the Visitor pattern implementation
 */
class EntityVisitor {
public:
    virtual ~EntityVisitor() = default;

    // Visit methods for each entity type
    virtual void visitMonster(Monster& aMonster) = 0;
    virtual void visitItem(Item& aItem) = 0;
    virtual void visitClue(Clue& aClue) = 0;
};
