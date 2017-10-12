#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ITEM_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ITEM_H

#include "iostream"
#include "ItemType.h"
#include "UseEffectType.h"

class Item {
public:
    Item();

    Item(double weight, const std::string &name, const std::string &description, ItemType type, short attack,
         short defense, UseEffectType useEffect);

    std::string* getName();
    double* getWeight();
    std::string &getDescription();
    short* getAttack();
    short* getDefense();
    ItemType getType();
    UseEffectType getUseEffect() const;

    void setWeight(double weight);
    void setName(const std::string &name);
    void setDescription(const std::string &description);
    void setAttack(short attack);
    void setDefense(short defense);
    void setType(ItemType);

private:
    double weight;
    std::string name;
    std::string description;
    ItemType type;
    short attack;
    short defense;
    UseEffectType useEffect;
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ITEM_H
