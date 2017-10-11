//
// Created by apha on 2017.10.09..
//

#include "Player.h"
#include <iostream>

Player::Player() {}

Player::Player(Zone *pPosition) : pPosition(pPosition) {
    health = MAX_HEALTH;
    inventory.invWeight = 0.00;

}

Enemy *Player::getNearbyEnemy(std::string * enemyName) {
    //return pPosition->getEnemy(std::string * enemyName);
}

void Player::changeHealth(short &damage) {
    health += damage;
}

void Player::setPosition(Zone * newPosition) {
    pPosition = newPosition;
}

void Player::moveTo(ActionType destination) {
    pPosition = pPosition -> getZone(destination);
    (*pPosition).setVisited(true);
}

Zone* Player::getPosition() {
    return pPosition;
}

Player::~Player() {
}

void Player::pickup(std::string *item) {
    Item* itemToAdd = pPosition->getItem(item);

    inventory.backpack.push_back(itemToAdd);
    changeInvWgt(itemToAdd->getWeight());
    pPosition->removeFromZoneInventory(item);
}

void Player::displayInventory() {
    if (inventory.armor != nullptr) std::cout << "Armor: " << (inventory.armor->getName()) << std::endl;
    if (inventory.weapon != nullptr) std::cout << "Weapon: " << (inventory.weapon->getName()) << std::endl;
    if (inventory.shield != nullptr) std::cout << "shield: " << (inventory.shield->getName()) << std::endl;
    for (int i = 0; i < inventory.backpack.size(); ++i) {
        std::cout << "backpack: " << *(inventory.backpack[i]->getName()) << std::endl;
    }
}

void Player::changeInvWgt(double *wgtChange) {
    std::cout << "changing inv wgt" << *wgtChange << std::endl;
    this->inventory.invWeight += *wgtChange;
}

bool Player::isWgtOk(std::string *itemName) {
    Item* itemToCheck = pPosition->getItem(itemName);
    std::cout << "wgt: " << inventory.invWeight << std::endl;
    return inventory.invWeight + *(itemToCheck->getWeight()) < INV_WEIGHT_LIMIT;
}

void Player::equip(std::string *itemName) {
    Item* itemToEquip = getItemFromInventory(itemName);
    if(itemToEquip->getType() == ItemType::SHIELD) {
        if(nullptr != inventory.shield) {
            unequip(inventory.shield->getName());
        }
        inventory.shield = itemToEquip;
        removeFromBackpack(itemName);
    }
    if(itemToEquip->getType() == ItemType::WEAPON) {
        if(nullptr != inventory.weapon) {
            unequip(inventory.weapon->getName());
        }
        inventory.weapon = itemToEquip;
        removeFromBackpack(itemName);
    }
    if(itemToEquip->getType() == ItemType::ARMOR) {
        if(nullptr != inventory.armor) {
            unequip(inventory.armor->getName());
        }
        inventory.armor = itemToEquip;
        removeFromBackpack(itemName);
    }
}

bool Player::isItemEquippable(std::string *itemName) {
    if(getItemFromInventory(itemName) != nullptr) {
        if(getItemFromInventory(itemName)->getType() == ItemType::ARMOR ||
            getItemFromInventory(itemName)->getType() == ItemType::WEAPON ||
            getItemFromInventory(itemName)->getType() == ItemType::SHIELD){
            return true;
        }
    }
    return false;
}

Item *Player::getItemFromInventory(std::string *itemName) {

    for(Item* item: inventory.backpack) {
        std::string existingItem = *(item->getName());
        for (int i = 0; i < existingItem.length(); ++i) {
            existingItem[i] = std::tolower(existingItem[i]);
        }
        if(existingItem == *itemName) {
            return item;
        }
    }
    return nullptr;
}

void Player::removeFromBackpack(std::string *itemName) {
    for (int i = 0; i < inventory.backpack.size() ; ++i) {
        std::string existingItem = *(inventory.backpack[i]->getName());
        for (int i = 0; i < existingItem.length(); ++i) {
            existingItem[i] = std::tolower(existingItem[i]);
        }
        if(existingItem == *itemName) {
            inventory.backpack.erase(inventory.backpack.begin()+i);
        }
    }

}

void Player::unequip(std::string *itemName) {

}




/*Level 1 task - some pointer needed & subclasses.
 *
 * void Player::pickup(Item itemToPickup) {
    if (itemToPickup.getWight() + invWeight <= INV_WEIGHT_LIMIT) {
        inventory.emplace_back(itemToPickup);
        invWeight += itemToPickup.getWeight();
    } else {
        std::cout << or go to the gym." << std::end;

    }
}
*/