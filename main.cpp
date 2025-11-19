#include <iostream>
#include <memory>
#include <limits>
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Clue.h"
#include "Room.h"
#include "Dungeon.h"
#include "PlayerActions.h"

/**
 * COS30008 Problem Set 3 - Dungeon Crawler Game
 *
 * This is a simple text-based dungeon crawler that demonstrates:
 * - Tree data structure (Room nodes connected via edges)
 * - Visitor pattern (Player actions on entities)
 * - Object-oriented design with inheritance
 *
 * Game Description:
 * The player explores an ancient temple dungeon searching for the legendary
 * Crystal of Power. Along the way, they must defeat monsters, collect treasures,
 * and examine clues to progress through interconnected rooms organized as a tree.
 */

// Function to build the dungeon with all rooms and entities
Dungeon buildDungeon() {
    Dungeon dungeon;

    // Create rooms (nodes in the tree)
    Room* entrance = dungeon.createRoom("Temple Entrance",
        "A grand stone archway marks the entrance to an ancient temple. "
        "Torch light flickers on the walls.");

    Room* mainHall = dungeon.createRoom("Main Hall",
        "A vast hall with tall pillars reaching into darkness above. "
        "Ancient murals depict forgotten rituals.");

    Room* leftChamber = dungeon.createRoom("Guard Chamber",
        "A chamber that once housed temple guards. "
        "Old weapons and armor lie scattered about.");

    Room* rightChamber = dungeon.createRoom("Treasure Vault",
        "A small vault with ornate decorations and empty pedestals. "
        "Something valuable might still remain here.");

    Room* secretPassage = dungeon.createRoom("Secret Passage",
        "A narrow, dusty passage hidden behind a false wall. "
        "Few have walked this path.");

    Room* innerSanctum = dungeon.createRoom("Inner Sanctum",
        "The heart of the temple. A pedestal in the center holds "
        "the Crystal of Power, glowing with ancient magic!");

    // Add entities to rooms

    // Entrance room entities
    entrance->addEntity(std::make_shared<Clue>("Stone Tablet",
        "An ancient stone tablet with carved inscriptions.",
        "The inscription reads: 'Only the brave shall claim the crystal. "
        "Beware the guardian in the chamber of guards.'"));

    // Main Hall entities
    mainHall->addEntity(std::make_shared<Monster>("Giant Spider",
        "A massive spider with gleaming red eyes.",
        40, 15));

    mainHall->addEntity(std::make_shared<Item>("Health Potion",
        "A shimmering red potion that restores vitality.",
        30));

    // Left Chamber (Guard Chamber) entities
    leftChamber->addEntity(std::make_shared<Monster>("Skeleton Warrior",
        "An undead warrior wielding a rusty sword.",
        60, 20));

    leftChamber->addEntity(std::make_shared<Clue>("Ancient Shield",
        "A shield bearing the temple's emblem.",
        "The emblem hints at a secret passage behind the eastern wall of the main hall."));

    // Right Chamber (Treasure Vault) entities
    rightChamber->addEntity(std::make_shared<Item>("Golden Amulet",
        "A beautiful amulet encrusted with gems.",
        100));

    rightChamber->addEntity(std::make_shared<Item>("Silver Coins",
        "A pouch of ancient silver coins.",
        50));

    // Secret Passage entities
    secretPassage->addEntity(std::make_shared<Clue>("Dusty Journal",
        "A journal left by a previous adventurer.",
        "The final entry: 'I found the way to the sanctum, but I'm too weak to continue. "
        "The crystal lies ahead...'"));

    secretPassage->addEntity(std::make_shared<Monster>("Shadow Beast",
        "A creature made of living darkness.",
        50, 18));

    // Inner Sanctum entities
    innerSanctum->addEntity(std::make_shared<Item>("Crystal of Power",
        "The legendary Crystal of Power, radiating mystical energy!",
        500));

    // Build the tree structure by connecting rooms
    // Entrance connects to Main Hall
    entrance->connectRoom(mainHall, "North Door - Main Hall");

    // Main Hall connects to three rooms
    mainHall->connectRoom(leftChamber, "West Door - Guard Chamber");
    mainHall->connectRoom(rightChamber, "East Door - Treasure Vault");
    mainHall->connectRoom(secretPassage, "Hidden Door - Secret Passage (requires examination)");

    // Secret Passage connects to Inner Sanctum
    secretPassage->connectRoom(innerSanctum, "Ancient Door - Inner Sanctum");

    // Set entrance as root of the tree
    dungeon.setEntrance(entrance);

    return dungeon;
}

// Function to handle player interaction with entities in current room
void interactWithRoom(Room* currentRoom, Player& player) {
    const auto& entities = currentRoom->getEntities();

    if (entities.empty()) {
        std::cout << "\nThere's nothing to interact with in this room." << std::endl;
        return;
    }

    std::cout << "\nWhat would you like to interact with?" << std::endl;
    for (size_t i = 0; i < entities.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << entities[i]->getName() << std::endl;
    }
    std::cout << "  0. Cancel" << std::endl;

    int choice;
    std::cout << "Enter choice: ";
    std::cin >> choice;

    if (choice == 0 || choice > static_cast<int>(entities.size())) {
        return;
    }

    auto entity = currentRoom->getEntity(choice - 1);
    if (!entity) {
        std::cout << "Invalid selection." << std::endl;
        return;
    }

    // Choose action
    std::cout << "\nWhat action do you want to perform?" << std::endl;
    std::cout << "  1. Attack" << std::endl;
    std::cout << "  2. Collect" << std::endl;
    std::cout << "  3. Examine" << std::endl;
    std::cout << "  0. Cancel" << std::endl;

    int action;
    std::cout << "Enter choice: ";
    std::cin >> action;

    // Apply visitor pattern based on action
    switch (action) {
        case 1: {
            AttackAction attack(player);
            entity->accept(attack);
            break;
        }
        case 2: {
            CollectAction collect(player);
            entity->accept(collect);
            break;
        }
        case 3: {
            ExamineAction examine(player);
            entity->accept(examine);
            break;
        }
        default:
            std::cout << "No action performed." << std::endl;
    }
}

// Main game loop
void gameLoop(Dungeon& dungeon, Player& player) {
    Room* currentRoom = dungeon.getEntrance();
    bool gameRunning = true;

    std::cout << "\n╔════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║     WELCOME TO THE TEMPLE OF THE ANCIENTS!        ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\nYour quest: Find the legendary Crystal of Power!" << std::endl;
    std::cout << "Navigate through rooms, defeat monsters, collect treasures," << std::endl;
    std::cout << "and examine clues to guide your journey." << std::endl;

    while (gameRunning && player.isAlive()) {
        // Display current room
        currentRoom->describe();

        // Show menu
        std::cout << "\n=== Actions ===" << std::endl;
        std::cout << "1. Interact with entities" << std::endl;
        std::cout << "2. Move to another room" << std::endl;
        std::cout << "3. View player status" << std::endl;
        std::cout << "4. Quit game" << std::endl;
        std::cout << "===============" << std::endl;

        int choice;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        // Clear input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                interactWithRoom(currentRoom, player);
                break;

            case 2: {
                const auto& connectedRooms = currentRoom->getConnectedRooms();
                if (connectedRooms.empty()) {
                    std::cout << "\nThere are no exits from this room!" << std::endl;
                    break;
                }

                std::cout << "\nWhere would you like to go?" << std::endl;
                const auto& doorNames = currentRoom->getDoorNames();
                for (size_t i = 0; i < doorNames.size(); ++i) {
                    std::cout << "  " << (i + 1) << ". " << doorNames[i] << std::endl;
                }
                std::cout << "  0. Stay here" << std::endl;

                int roomChoice;
                std::cout << "Enter choice: ";
                std::cin >> roomChoice;

                if (roomChoice > 0 && roomChoice <= static_cast<int>(connectedRooms.size())) {
                    currentRoom = currentRoom->getConnectedRoom(roomChoice - 1);
                    std::cout << "\nYou move through the door..." << std::endl;
                }
                break;
            }

            case 3:
                player.displayStatus();
                break;

            case 4:
                std::cout << "\nThanks for playing!" << std::endl;
                gameRunning = false;
                break;

            default:
                std::cout << "\nInvalid choice. Try again." << std::endl;
        }
    }

    if (!player.isAlive()) {
        std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
        std::cout << "║          GAME OVER                     ║" << std::endl;
        std::cout << "║   You have been defeated...            ║" << std::endl;
        std::cout << "╚════════════════════════════════════════╝" << std::endl;
    }

    std::cout << "\nFinal Score: " << player.getScore() << std::endl;
}

int main() {
    // Build the dungeon
    Dungeon dungeon = buildDungeon();

    // Create player
    Player player("Adventurer", 100, 25);

    // Display dungeon info
    dungeon.displayInfo();

    // Start game loop
    gameLoop(dungeon, player);

    return 0;
}
