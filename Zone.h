#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ZONE_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ZONE_H


#include "Item.h"
#include "vector"
#include "Enemy.h"
#include "Area.hpp"
#include "ActionType.h"
#include <utility>

enum Directions{NORTH, EAST, SOUTH, WEST, endMark};

class Zone {
public:
    Zone(Area *description, std::pair<int,int> coords);
    Enemy* getEnemy(std::string * enemy);
    Item* getItem(std::string*);
    Zone* getZone(ActionType);
    std::pair<int,int> getCoords();
    void setZone (Directions , Zone *);
    void show();
    void setVisited(bool);
    bool isVisited();
    void addToZoneInventory(Item*);
    void addEnemyToZone(Enemy*);
    void removeFromZoneInventory(std::string* itemName);

    const vector<Enemy *> &getEnemies() const;

    Item *getUnlockedBy() const;

    void setUnlockedBy(Item *unlockedBy);
    bool getIsDirectionOpen(ActionType direction) ;
    void setIsDirectionOpen(ActionType* direction, bool isOpen);

private:
    const std::string directionNames[4] = {"NORTH", "EAST", "SOUTH", "WEST"};
    std::pair<int,int> coords;
    void printMonsters();
    void printDirections();
    void printItems();
    Area* description;
    Zone* directions[4];
    bool isDirectionOpen[4] = {true, true, true, true};
    std::vector<Item*> inventory;
    bool visited;
    std::vector<Enemy*> enemies;
    Item* unlockedBy;
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ZONE_H
