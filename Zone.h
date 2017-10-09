#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ZONE_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ZONE_H


#include "Item.h"
#include "vector"
#include "Enemy.h"
#include "Area.hpp"

class Zone {
public:
    void setDescription(Area* area);
    Zone* getDirection(char direction);
private:
    Area* description;
    Zone* north;
    Zone* east;
    Zone* south;
    Zone* west;
    std::vector<Item> Inventory;
    bool visited;
    std::vector<Enemy> enemies;
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ZONE_H
