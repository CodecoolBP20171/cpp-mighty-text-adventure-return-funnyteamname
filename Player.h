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
    void equip(std::string* itemName);
    void unequip(std::string* itemName);
    void drop(Item* itemToDrop);
    void changeHealth(short &damage);
    void use(Item* itemToUse);
    void pickup(std::string * item);
    void setPosition(Zone*);
    Enemy * getNearbyEnemy(std::string * enemyName);
    Item * getItemFromInventory(std::string * itemName);
    Zone* getPosition();
    void displayInventory();
    void changeInvWgt(double* wgtChange);
    bool isWgtOk(std::string* itemName);
    bool isItemEquippable(std::string* itemName);
    void removeFromBackpack(std::string * itemName);

    virtual ~Player();

    struct Inventory {
        double invWeight = 0;
        Item* armor = nullptr;
        Item* weapon = nullptr;
        Item* shield = nullptr;
        vector<Item*> backpack;
    };

private:
    const int MAX_HEALTH = 100;
    const double INV_WEIGHT_LIMIT = 30.00;

    Inventory inventory;
    Zone* pPosition;
    short health;
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_PLAYER_H
