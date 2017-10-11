//
// Created by apha on 2017.10.09..
//

#include "Player.h"
#include <iostream>

Player::Player() {}

Player::Player(Zone *pPosition) : pPosition(pPosition) {
    health = MAX_HEALTH;
    invWeight = 0.00;

}

Enemy *Player::getNearbyEnemy(std::string * enemyName) {
    //return pPosition->getEnemy(std::string * enemyName);
}

void Player::changeHealth(short &damage) {
    health += damage;
}

void Player::moveTo(Zone* destination) {
    pPosition = destination;
    (*pPosition).setVisited(true);
}

Zone Player::getPosition() {
    return *pPosition;
}

Player::~Player() {
}

/*Level 1 task - some pointer needed & subclasses.
 *
 * void Player::pickup(Item itemToPickup) {
    if (itemToPickup.getWight() + invWeight <= INV_WEIGHT_LIMIT) {
        inventory.emplace_back(itemToPickup);
        invWeight += itemToPickup.getWeight();
    } else {
        std::cout << "You are too weak to carry this item. Try to drop something form your inventory or go to the gym." << std::end;

    }
}
*/