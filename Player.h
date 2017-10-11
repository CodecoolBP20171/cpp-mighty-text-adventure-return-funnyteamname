#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_PLAYER_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_PLAYER_H


#include "Zone.h"
#include "Item.h"
#include "Enemy.h"
#include "vector"
#include "ActionType.h"

class Player {
public:
    Player(Zone *pPosition);
    Player();
    void attack(Enemy * enemy);
    void moveTo(ActionType direction);
    void equip(Item* itemToEquip );
    void unequip(Item* itemToUnequip);
    void drop(Item* itemToDrop);
    void changeHealth(short &damage);
    void use(Item* itemToUse);
    void pickup(Item itemToPickup);
    void setPosition(Zone*);
    Enemy * getNearbyEnemy(std::string * enemyName);
    Item * getItemFromInventory(std::string * itemName);
    Zone* getPosition();

    virtual ~Player();

private:
    const int MAX_HEALTH = 100;
    const double INV_WEIGHT_LIMIT = 50.00;

    std::vector<Item> inventory;
    Zone* pPosition;
    short health;
    double invWeight;
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_PLAYER_H
