//
// Created by apha on 2017.10.09..
//

#include "Item.h"

std::string* Item::getName() {
    return &this->name;
}

double* Item::getWeight() {
    return &this->weight;
}

std::string &Item::getDescription() {
    return description;
}

short* Item::getAttack() {
    return &attack;
}

short* Item::getDefense() {
    return &defense;
}

void Item::setWeight(double weight) {
    Item::weight = weight;
}

void Item::setName(const std::string &name) {
    Item::name = name;
}

void Item::setDescription(const std::string &description) {
    Item::description = description;
}

void Item::setAttack(short attack) {
    Item::attack = attack;
}

void Item::setDefense(short defense) {
    Item::defense = defense;
}

void Item::setType(ItemType type) {
    this->type = type;
}

Item::Item() {}

Item::Item(double weight, const std::string &name, const std::string &description, ItemType type, short attack,
           short defense) : weight(weight), name(name), description(description), type(type), attack(attack),
                            defense(defense) {}
