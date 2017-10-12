//
// Created by apha on 2017.10.09..
//

#include "Enemy.h"

std::string* Enemy::getName() {
    return &this->name;
}

short Enemy::getAttack() const {
    return attack;
}

void Enemy::setAttack(short attack) {
    Enemy::attack = attack;
}

short Enemy::getDefense() const {
    return defense;
}

void Enemy::setDefense(short defense) {
    Enemy::defense = defense;
}

Enemy::Enemy(const std::string &name, short attack, short defense, short health) : name(name), attack(attack),
                                                                                   defense(defense), health(health) {}

short* Enemy::getHealth() {
    return &health;
}

void Enemy::setHealth(short* damage) {
    Enemy::health += *damage;
}
