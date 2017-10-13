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
    Zone* getZone(ActionType);
    std::pair<int,int> getCoords();
    void show();

    //Zone settings
    void setZone (Directions , Zone *);
    void setVisited(bool);
    bool isVisited();
    Item *getUnlockedBy() const;
    void setUnlockedBy(Item *unlockedBy);
    bool getIsDirectionOpen(ActionType direction) ;
    void setIsDirectionOpen(ActionType* direction, bool isOpen);

    //Items
    void addToZoneInventory(Item*);
    void removeFromZoneInventory(std::string* itemName);
    Item* getItem(std::string*);

    //Enemies
    void addEnemyToZone(Enemy*);
    void removeDeadEnemies();
    const vector<Enemy *> &getEnemies() const;
    void removeEnemyFromZone(Enemy* enemy);
    Enemy* getEnemy(std::string * enemy);



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
    int getDirIndex(ActionType* direction);
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ZONE_H
