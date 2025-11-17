# COS30008 Problem Set 3 - Dungeon Crawler Game
## Temple of the Ancients

---

## TASK 1: Game Environment & Class Diagram

### Game Description

**Temple of the Ancients** is a text-based dungeon crawler game that demonstrates the use of Tree data structures and the Visitor design pattern.

**Story:**
The player takes on the role of an adventurer exploring an ancient temple in search of the legendary Crystal of Power. The temple is filled with dangerous monsters, valuable treasures, and mysterious clues that guide the player toward their goal.

**Core Features:**
- **Game Loop**: Interactive text-based interface where players can explore rooms, interact with entities, and manage their character
- **Player Entity**: The main character with health, attack power, inventory, and score tracking
- **Entity System**: Three types of entities that populate the dungeon:
  - **Monsters**: Hostile creatures that can be fought (Giant Spider, Skeleton Warrior, Shadow Beast)
  - **Items**: Treasures and useful objects that can be collected (Health Potion, Golden Amulet, Silver Coins, Crystal of Power)
  - **Clues**: Informational objects that reveal hints when examined (Stone Tablet, Ancient Shield, Dusty Journal)

**Game Mechanics:**
1. Players navigate through interconnected rooms forming a tree structure
2. Each room contains entities that can be interacted with
3. Players use different actions (Attack, Collect, Examine) based on entity types
4. Combat system where monsters fight back
5. Score tracking based on defeated enemies, collected items, and discovered clues
6. Victory condition: Reach the Inner Sanctum and collect the Crystal of Power

### Class Diagram

The class diagram (ClassDiagram.puml) shows the complete object-oriented design:

**Key Design Elements:**

1. **Entity Hierarchy** (Inheritance)
   - Abstract base class `Entity`
   - Three concrete subclasses: `Monster`, `Item`, `Clue`
   - Each entity has unique attributes and behaviors

2. **Visitor Pattern** (Behavioral Design Pattern)
   - Abstract `EntityVisitor` interface
   - Three concrete visitors: `AttackAction`, `CollectAction`, `ExamineAction`
   - Allows actions to be performed on entities without modifying entity classes
   - Demonstrates double dispatch mechanism

3. **Tree Structure** (Data Structure)
   - `Room` class represents nodes in the tree
   - Rooms contain entities and connect to other rooms
   - `Dungeon` class manages the entire tree structure
   - Root node represents the entrance

4. **Game Controller**
   - `Player` class manages player state
   - Main game loop handles user interaction
   - Integration of all components

---

## TASK 2: Room Layout Tree Diagram

### Dungeon Structure

The dungeon is organized as a tree with 6 rooms:

```
Temple Entrance (ROOT)
└── Main Hall
    ├── Guard Chamber (Leaf)
    ├── Treasure Vault (Leaf)
    └── Secret Passage
        └── Inner Sanctum (Leaf/Goal)
```

**Room Details:**

1. **Temple Entrance** (Root Node)
   - Entities: Stone Tablet [Clue]
   - Connections: 1 (Main Hall)
   - Purpose: Starting point, provides initial hint

2. **Main Hall** (Internal Node)
   - Entities: Giant Spider [Monster], Health Potion [Item]
   - Connections: 3 (Guard Chamber, Treasure Vault, Secret Passage)
   - Purpose: Central hub with multiple paths

3. **Guard Chamber** (Leaf Node)
   - Entities: Skeleton Warrior [Monster], Ancient Shield [Clue]
   - Connections: 0
   - Purpose: Combat challenge with clue about secret passage

4. **Treasure Vault** (Leaf Node)
   - Entities: Golden Amulet [Item], Silver Coins [Item]
   - Connections: 0
   - Purpose: Reward room with valuable items

5. **Secret Passage** (Internal Node)
   - Entities: Dusty Journal [Clue], Shadow Beast [Monster]
   - Connections: 1 (Inner Sanctum)
   - Purpose: Hidden path to the goal

6. **Inner Sanctum** (Leaf Node/Goal)
   - Entities: Crystal of Power [Item]
   - Connections: 0
   - Purpose: Final destination with the ultimate prize

See `DungeonTree_Simple.txt` for detailed ASCII diagram.
See `DungeonTreeDiagram.puml` for PlantUML visualization.

---

## TASK 3: Dungeon Implementation

### A) Room Node Class (Room.h)

```cpp
class Room {
private:
    std::string fName;
    std::string fDescription;
    std::vector<std::shared_ptr<Entity>> fEntities;
    std::vector<Room*> fConnectedRooms;  // Child nodes
    std::vector<std::string> fDoorNames;  // Edge labels
public:
    // Methods to add entities, connect rooms, and navigate
};
```

**Key Features:**
- Stores room name and description for atmosphere
- Contains a collection of entities present in the room
- Maintains connections to other rooms (tree edges)
- Provides methods to describe room contents and navigate

### B) Dungeon Tree Manager (Dungeon.h)

```cpp
class Dungeon {
private:
    Room* fRoot;  // Root node (entrance)
    std::vector<std::unique_ptr<Room>> fRooms;  // All rooms
public:
    Room* createRoom(const std::string& aName, const std::string& aDescription);
    void setEntrance(Room* aRoom);
    Room* getEntrance() const;
};
```

**Key Features:**
- Manages the tree structure with a root pointer
- Creates and owns all room nodes
- Provides access to the entrance (root)
- Uses smart pointers for memory management

### C) Dungeon Exploration Test

The main.cpp file demonstrates:
- Building the complete dungeon tree
- Player navigation through room connections
- Interactive exploration via game loop
- Room descriptions and entity interactions

**Test Output Shows:**
1. Successfully created 6-room dungeon
2. Player can move between connected rooms
3. Room contents properly displayed
4. Navigation limited to available doors (tree edges)
5. Dead-end rooms (leaves) properly identified

---

## TASK 4: Visitor Pattern Implementation

### Visitor Pattern Design

The Visitor pattern separates algorithms (actions) from the objects (entities) they operate on.

**Abstract Visitor Interface (EntityVisitor.h):**
```cpp
class EntityVisitor {
public:
    virtual void visitMonster(Monster& aMonster) = 0;
    virtual void visitItem(Item& aItem) = 0;
    virtual void visitClue(Clue& aClue) = 0;
};
```

**Concrete Visitors (PlayerActions.h):**

1. **AttackAction**
   - Appropriate for: Monsters
   - Effect: Deals damage, monster counterattacks if alive
   - Inappropriate for: Items (suggests collecting), Clues (suggests examining)

2. **CollectAction**
   - Appropriate for: Items
   - Effect: Adds to inventory, increases score
   - Inappropriate for: Monsters (suggests attacking), Clues (suggests examining)

3. **ExamineAction**
   - Appropriate for: All entity types
   - Effect on Monsters: Shows stats and status
   - Effect on Items: Shows value and collection status
   - Effect on Clues: Reveals hidden information, awards points

**Entity Accept Method:**
```cpp
void Monster::accept(EntityVisitor& aVisitor) override {
    aVisitor.visitMonster(*this);  // Double dispatch
}
```

### Working Demonstration

The test output shows:
- ✓ Examine action on Stone Tablet reveals hidden clue (+25 points)
- ✓ Attack action on Giant Spider: deals damage, monster fights back
- ✓ Examine action on Health Potion shows item details
- ✓ Incorrect action usage provides helpful feedback
- ✓ Attack on Skeleton Warrior demonstrates combat system
- ✓ Visitor pattern correctly routes actions to appropriate methods

---

## Reflection Summary

### Problems Encountered and Solutions

1. **Problem**: Managing entity lifetime in rooms
   - **Solution**: Used shared_ptr for entities to allow safe access across different scopes
   - **Reference**: C++ Smart Pointers documentation

2. **Problem**: Forward declaration circular dependencies between Entity and EntityVisitor
   - **Solution**: Separated declarations into header files with forward declarations
   - **Reference**: Week 9 Lab Tutorial on Visitor pattern structure

3. **Problem**: Ensuring proper tree navigation without back edges
   - **Solution**: Used one-way pointers from parent to children only
   - **Reference**: Tree data structure principles from lectures

### Experience with Tree ADT and Visitor Pattern

**Tree ADT:**
- **Learning Curve**: Moderate - The concept was straightforward, but implementing navigation required careful thought
- **Practicality**: Very practical for representing hierarchical dungeon layouts
- **Challenges**: Ensuring no cyclic references and handling leaf nodes properly
- **Other Uses**: Could be used for skill trees, dialogue systems, file systems, organizational hierarchies

**Visitor Pattern:**
- **Learning Curve**: Challenging initially - Understanding double dispatch took time
- **Practicality**: Excellent for adding new actions without modifying entity classes
- **Challenges**: Setting up the interface and ensuring all visitor methods are implemented
- **Benefits**: Makes code extensible - can add new actions (e.g., TradeAction, HealAction) without changing entities
- **Other Uses**: Compilers (AST traversal), document processors, game AI behavior systems

**Overall Assessment:**
The combination of Tree structure and Visitor pattern created a clean, maintainable design. The Tree naturally represents spatial relationships, while the Visitor allows flexible interaction mechanics. This architecture would scale well for larger games with more rooms and action types.

---

## File Structure

```
ProblemSet_3/
├── Entity.h              - Abstract entity base class
├── Monster.h             - Monster entity implementation
├── Item.h                - Item entity implementation
├── Clue.h                - Clue entity implementation
├── Player.h              - Player character class
├── EntityVisitor.h       - Abstract visitor interface
├── PlayerActions.h       - Concrete visitor implementations
├── Room.h                - Room node class (Tree node)
├── Dungeon.h             - Dungeon tree manager
├── main.cpp              - Game loop and dungeon builder
├── Makefile              - Build configuration
├── ClassDiagram.puml     - UML class diagram (Task 1)
├── DungeonTreeDiagram.puml - Tree diagram (Task 2)
├── DungeonTree_Simple.txt  - ASCII tree diagram (Task 2)
└── PROJECT_DOCUMENTATION.md - This file
```

## Compilation and Execution

```bash
# Compile
make

# Run
./dungeon_crawler

# Clean
make clean
```

---

## Design Patterns Used

1. **Visitor Pattern** - Separates actions from entities
2. **Strategy Pattern** - Different visitor strategies for different actions
3. **Composite Pattern** - Room contains entities (composition)
4. **Factory Pattern** - Dungeon creates and manages rooms

## Data Structures Used

1. **Tree** - Dungeon room hierarchy
2. **Vector** - Entity collections, inventory
3. **Smart Pointers** - Memory management (unique_ptr, shared_ptr)

---

*End of Documentation*
