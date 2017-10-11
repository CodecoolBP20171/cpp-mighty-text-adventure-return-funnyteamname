#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ZONE_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ZONE_H


#include "Item.h"
#include "vector"
#include "Enemy.h"
#include "Area.hpp"

enum Directions{NORTH, EAST, SOUTH, WEST, endMark};

class Zone {
public:
    Zone(Area *description);

    Zone* getZone(char direction);
    void setZone (Directions , Zone *);
    void show();
    void setVisited(bool);

private:
    Area* description;
    Zone* directions[4];
    std::vector<Item> inventory;
    bool visited;
    std::vector<Enemy> enemies;
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ZONE_H
