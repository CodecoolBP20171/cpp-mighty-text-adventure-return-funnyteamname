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
    if(health > MAX_HEALTH) {
        health = MAX_HEALTH;
    }
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

short Player::getHealth() {
    return health;
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
    if (inventory.armor != nullptr) std::cout << "Armor: " << *(inventory.armor->getName()) << std::endl;
    if (inventory.weapon != nullptr) std::cout << "Weapon: " << *(inventory.weapon->getName()) << std::endl;
    if (inventory.shield != nullptr) std::cout << "shield: " << *(inventory.shield->getName()) << std::endl;
    if (inventory.backpack.size() != 0) std::cout << "Backpack contents: ";
    for (int i = 0; i < inventory.backpack.size(); ++i) {
        if(nullptr != inventory.backpack[i]) std::cout << *(inventory.backpack[i]->getName());
        if ( i != inventory.backpack.size()-1 ) std::cout << ", ";
    }
    std::cout << std::endl;
}

void Player::changeInvWgt(double *wgtChange) {
    this->inventory.invWeight += *wgtChange;
}

bool Player::isWgtOk(std::string *itemName) {
    Item* itemToCheck = pPosition->getItem(itemName);
    return inventory.invWeight + *(itemToCheck->getWeight()) < INV_WEIGHT_LIMIT;
}

void Player::equip(std::string *itemName) {
    Item* itemToEquip = getItemFromInventory(itemName);
    std::string itemToUnequip;
    if(itemToEquip->getType() == ItemType::SHIELD) {
        if(nullptr != inventory.shield) {
            itemToUnequip = *inventory.shield->getName();
            itemToUnequip = switchToLowerCase(itemToUnequip);
            unequip(&itemToUnequip);
        }
        inventory.shield = itemToEquip;
        updateDefense(*itemToEquip->getDefense());
        removeFromBackpack(itemName);
    }
    if(itemToEquip->getType() == ItemType::WEAPON) {
        if(nullptr != inventory.weapon) {
            itemToUnequip = *inventory.weapon->getName();
            itemToUnequip = switchToLowerCase(itemToUnequip);
            unequip(&itemToUnequip);
        }
        inventory.weapon = itemToEquip;
        updateDamage(*itemToEquip->getAttack());
        removeFromBackpack(itemName);
    }
    if(itemToEquip->getType() == ItemType::ARMOR) {
        if(nullptr != inventory.armor) {
            itemToUnequip = *inventory.armor->getName();
            itemToUnequip = switchToLowerCase(itemToUnequip);
            unequip(&itemToUnequip);
        }
        inventory.armor = itemToEquip;
        updateDefense(*itemToEquip->getDefense());
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
    std::string existingItem;

    if(nullptr != inventory.armor) {
        existingItem = switchToLowerCase(*(inventory.armor->getName()));
        if(existingItem == *itemName) {
            return inventory.armor;
        }
    }

    if(nullptr != inventory.shield) {
        existingItem = switchToLowerCase(*inventory.shield->getName());
        if(existingItem == *itemName) {
            return inventory.shield;
        }
    }

    if(nullptr != inventory.weapon) {
        existingItem = switchToLowerCase(*(inventory.weapon->getName()));
        if(existingItem == *itemName) {
            return inventory.weapon;
        }
    }

    for(Item* item: inventory.backpack) {
        existingItem = switchToLowerCase(*(item->getName()));
        if(existingItem == *itemName) return item;
    }
    return nullptr;
}

void Player::removeFromBackpack(std::string *itemName) {
    for (int i = 0; i < inventory.backpack.size() ; ++i) {
        std::string existingItem = switchToLowerCase(*(inventory.backpack[i]->getName()));
        if(existingItem == *itemName) {
            inventory.backpack.erase(inventory.backpack.begin()+i);
        }
    }

}

void Player::unequip(std::string *itemName) {
    Item* itemToUnequip = getItemFromInventory(itemName);
    if(inventory.weapon == itemToUnequip) {
        updateDamage(*itemToUnequip->getAttack() * -1);
        inventory.backpack.push_back(itemToUnequip);
        inventory.weapon = nullptr;
    } else if(inventory.shield == itemToUnequip) {
        updateDefense(*itemToUnequip->getDefense() * -1);
        inventory.backpack.push_back(itemToUnequip);
        inventory.shield = nullptr;
    } else if(inventory.armor == itemToUnequip) {
        updateDefense(*itemToUnequip->getDefense() * -1);
        inventory.backpack.push_back(itemToUnequip);
        inventory.armor = nullptr;
    } else {
        std::cout << *itemName << " cannot be unequipped";
    }
}

bool Player::isItemUnequippable(std::string *itemName) {
    Item* itemToCheck = getItemFromInventory(itemName);
    if(nullptr != itemToCheck) {
        return inventory.shield == itemToCheck ||
            inventory.armor == itemToCheck ||
            inventory.weapon == itemToCheck;
    }
}

std::string Player::switchToLowerCase(std::string itemName) {
    std::string existingItem = itemName;
    for (int i = 0; i < itemName.length() ; ++i) {
        existingItem[i] = std::tolower(existingItem[i]);
    }
    return existingItem;


}

void Player::drop(std::string *itemName) {
    Item* itemToDrop = getItemFromInventory(itemName);
    if(inventory.armor == itemToDrop ||
       inventory.weapon == itemToDrop ||
       inventory.shield == itemToDrop){
        unequip(itemName);
    }
    pPosition->addToZoneInventory(itemToDrop);
    removeFromBackpack(itemName);

}

void Player::updateDamage(short weaponDamage) {
    damage += weaponDamage;
}

void Player::updateDefense(short itemDefense) {
    defense += itemDefense;
}

void Player::use(Item *itemToUse) {
        if(itemToUse->getUseEffect() == UseEffectType::NONE) {
            std::cout << "This item has no special uses." << std::endl;
        } else if(itemToUse->getUseEffect() == UseEffectType::HEAL) {
            short potionHealAmount = 20;
            changeHealth(potionHealAmount);
            std::cout << "Drinking it healed you to " << getHealth() << " health points." << std::endl;
            std::string itemName = switchToLowerCase(*itemToUse->getName());
            removeFromBackpack(&itemName);
        } else if(itemToUse->getUseEffect() == UseEffectType::OPEN_DOOR) {
            std::cout << "east: " << pPosition->getIsDirectionOpen(ActionType::EAST) << std::endl;
            if(pPosition->getUnlockedBy() == itemToUse) {
                ActionType dir = ActionType::EAST;
                pPosition->setIsDirectionOpen(&dir, true);
                std::cout << "The way east is now open..." << std::endl;
                std::cout << "east: " << pPosition->getIsDirectionOpen(ActionType::EAST) << std::endl;
            }
        }
}

short Player::getHealth() const {
    return health;
}

void Player::attack(Enemy *enemy) {
    short damageToDeal = (getDamage() - enemy->getDefense())*-1;
    enemy->setHealth(&damageToDeal);
    std::cout << "Your attack deals " << damageToDeal << " damage." << std::endl;
}

short Player::getDamage()  {
    return damage;
}

short Player::getDefense() const {
    return defense;
}

void Player::playerGetsAttacked() {
    short damageToTake;
    pPosition->getEnemies().empty();
    if (!pPosition->getEnemies().empty()) {
        std::cout << "Enemy attacks:: ";
        for(int j = 0; j < pPosition->getEnemies().size(); ++j) {
            damageToTake = (pPosition->getEnemies()[j]->getAttack() - getDefense())*-1;
            std::cout << *(pPosition->getEnemies()[j]->getName()) << " (hp: " << *(pPosition->getEnemies()[j]->getHealth()) << ") deals: ";
            std::cout << damageToTake << " damage." << std::endl;
            changeHealth(damageToTake);
        }
    }
}


