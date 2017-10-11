#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_PLAYER_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_PLAYER_H


#include "Zone.h"
#include "Item.h"
#include "Enemy.h"
#include "vector"
#include "map"
#include "ActionType.h"

class Player {
public:
    void attack(Enemy * enemy);
    void moveTo(ActionType direction);
    void equip(Item* itemToEquip );
    void unequip(Item* itemToUnequip);
    void drop(Item* itemToDrop);
    void changeHealth(short &damage);
    void use(Item* itemToUse);
    void pickup(Item itemToPickup);
    Enemy * getNearbyEnemy(std::string * enemyName);
    Item * getItemFromInventory(std::string * itemName);
private:
    std::vector<Item> inventory;
    // std::map<enum type, Item> equipped;
    Zone* pPosition;
    short health;
    double invWeightLimit;
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_PLAYER_H
