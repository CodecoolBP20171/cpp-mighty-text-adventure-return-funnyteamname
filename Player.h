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
    virtual ~Player();

    //Actions
    void attack(Enemy * enemy);
    void moveTo(ActionType direction);
    void equip(std::string* itemName);
    void unequip(std::string* itemName);
    void drop(std::string* itemName);
    void pickup(std::string * item);
    void use(Item* itemToUse);

    //Items
    Item * getItemFromInventory(std::string * itemName);
    void displayInventory();
    void changeInvWgt(double* wgtChange);
    bool isWgtOk(std::string* itemName);
    bool isItemEquippable(std::string* itemName);
    bool isItemUnequippable(std::string* itemName);
    void removeFromBackpack(std::string * itemName);
    void updateDamage(short weaponDamage);
    void updateDefense(short itemDefense);

    void changeHealth(short &damage);
    void setPosition(Zone*);
    Zone* getPosition();
    std::string switchToLowerCase(std::string itemName);
    short getHealth();
    short getDamage();
    short getDefense() const;
    void playerGetsAttacked();


    struct Inventory {
        double invWeight = 0;
        Item* armor = nullptr;
        Item* weapon = nullptr;
        Item* shield = nullptr;
        vector<Item*> backpack;
    };

private:
    const short MAX_HEALTH = 100;
    const double INV_WEIGHT_LIMIT = 30.00;

    short damage = 20;
    short defense = 20;
    Inventory inventory;
    Zone* pPosition;
    short health = MAX_HEALTH;
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_PLAYER_H
