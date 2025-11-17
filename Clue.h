#pragma once
#include "Entity.h"
#include "EntityVisitor.h"

/**
 * Clue entity that can be examined by the player for information
 */
class Clue : public Entity {
private:
    std::string fHiddenInfo;
    bool fIsExamined;

public:
    Clue(const std::string& aName, const std::string& aDescription, const std::string& aHiddenInfo)
        : Entity(aName, aDescription), fHiddenInfo(aHiddenInfo), fIsExamined(false) {}

    // Getter and setter methods
    const std::string& getHiddenInfo() const { return fHiddenInfo; }
    bool isExamined() const { return fIsExamined; }
    void examine() { fIsExamined = true; }

    // Accept method for Visitor pattern
    void accept(EntityVisitor& aVisitor) override {
        aVisitor.visitClue(*this);
    }
};
