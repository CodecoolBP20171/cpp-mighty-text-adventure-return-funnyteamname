#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ITEM_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ITEM_H

#include "iostream"

class Item {
public:


private:
    double weight;
    std::string name;
    std::string description;
    bool equippable;
    bool consumable;
    enum type;
    short attack;
    short defense;
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ITEM_H
