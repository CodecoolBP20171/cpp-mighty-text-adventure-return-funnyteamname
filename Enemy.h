#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ENEMY_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ENEMY_H

#include <iostream>

class Enemy {
public:
    Enemy(const std::string &name, short attack, short defense, short health);
    std::string* getName();
    short getAttack() const;
    void setAttack(short attack);
    short getDefense() const;
    void setDefense(short defense);
    short* getHealth();
    void setHealth(short* health);


private:
    std::string name;
    short attack;
    short defense;
    short health;
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_ENEMY_H
