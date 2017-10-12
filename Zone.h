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
    Zone* getZone(ActionType);
    std::pair<int,int> getCoords();
    void setZone (Directions , Zone *);
    void show();
    void setVisited(bool);
    bool isVisited();

private:
    const std::string directionNames[4] = {"NORTH", "EAST", "SOUTH", "WEST"};
    std::pair<int,int> coords;
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
