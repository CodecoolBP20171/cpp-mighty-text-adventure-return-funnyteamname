#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ZONE_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ZONE_H


#include "Item.h"
#include "vector"
#include "Enemy.h"
#include "Area.hpp"
#include "ActionType.h"

enum Directions{NORTH, EAST, SOUTH, WEST, endMark};

class Zone {
public:
    Zone(Area *description);
    Enemy* getEnemy(std::string * enemy);
    Zone* getZone(ActionType);
    void setZone (Directions , Zone *);
    void show();
    void setVisited(bool);

private:
    const std::string directionNames[4] = {"NORTH", "EAST", "SOUTH", "WEST"};
    void printMonsters();
    void printDirections();
    void printItems();
    Area* description;
    Zone* directions[4];
    std::vector<Item *> inventory;
    bool visited;
    std::vector<Enemy> enemies;
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ZONE_H
