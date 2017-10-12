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
    Enemy* getEnemy(std::string*);
    Item* getItem(std::string*);
    Zone* getZone(ActionType);
    void setZone (Directions , Zone *);
    void show();
    void setVisited(bool);
    void addToZoneInventory(Item*);
    void removeFromZoneInventory(std::string* itemName);

    Item *getUnlockedBy() const;

    void setUnlockedBy(Item *unlockedBy);
    bool getIsDirectionOpen(ActionType direction) ;
    void setIsDirectionOpen(ActionType* direction, bool isOpen);

private:
    Area* description;
    Zone* directions[4];
    bool isDirectionOpen[4] = {true, true, true, true};
    std::vector<Item*> inventory;
    bool visited;
    std::vector<Enemy> enemies;
    Item* unlockedBy;
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ZONE_H
