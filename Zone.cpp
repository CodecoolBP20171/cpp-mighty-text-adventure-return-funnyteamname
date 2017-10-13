//
// Created by apha on 2017.10.09..
//

#include "Zone.h"


Zone::Zone(Area *description, std::pair<int, int> coords) : description(description), coords(coords) {
    visited = false;
    for (int i = 0; i < 4; ++i ) {
        directions[i] = nullptr;
    };
}

Enemy* Zone::getEnemy(std::string *enemyName) {
    for(Enemy* enemy: enemies) {
        std::string existingItem = *(enemy->getName());
        for (int i = 0; i < existingItem.length(); ++i) {
            existingItem[i] = std::tolower(existingItem[i]);
        }
        if(existingItem == *enemyName) {
            return enemy;
        }
    }
    return nullptr;
}

void Zone::setVisited(bool isItVisited) {
    visited = isItVisited;
}

void Zone::setZone(Directions direction, Zone * zoneToConnect) {
    directions[direction] = zoneToConnect;
}

Zone* Zone::getZone(ActionType direction) {
    return directions[getDirIndex(&direction)];
}

void Zone::printDirections() {
    std::cout << "From here routes are leading to the ";
    int validDirections = 0;

    for (auto &direction : directions) {
        if (direction != nullptr) ++validDirections;
    }

    for (int i = 0; i < 4; ++i) {
        if (directions[i] != nullptr) {
            std::cout << directionNames[i];
            switch (validDirections) {
                case 1 : std::cout << std::endl;
                    break;
                case 2 : std::cout << " and ";
                    break;
                default: std::cout << ", ";
            }
            --validDirections;
        }
    }
}

void Zone::printItems() {
    if ( !inventory.empty() ) {
        std::cout << "You can see in this room the following items: ";
        for(int i = 0; i < inventory.size(); ++i) {
            std::cout << *(inventory[i]->getName());
            if ( i != inventory.size()-1 ) std::cout << ", ";
            else std::cout << std::endl;
        }
    }
}

std::pair<int,int> Zone::getCoords() {
    return coords;
}

void Zone::show() {
    const string *room = (*description).getDescription();
    std::cout << *room << std::endl;
    // monsters to attack
    printMonsters();
    printDirections();
    printItems();
}

bool Zone::isVisited() {
    return visited;
}

void Zone::addToZoneInventory(Item * itemToAdd) {
    this->inventory.emplace_back(itemToAdd);
}

Item *Zone::getItem(std::string * itemName) {
    for(Item* item: inventory) {
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

void Zone::removeFromZoneInventory(std::string *itemName) {
    for (int i = 0; i < inventory.size() ; ++i) {
        std::string existingItem = *(inventory[i]->getName());
        for (int i = 0; i < existingItem.length(); ++i) {
            existingItem[i] = std::tolower(existingItem[i]);
        }
        if(existingItem == *itemName) {
            inventory.erase(inventory.begin()+i);
        }
    }
}

Item *Zone::getUnlockedBy() const {
    return unlockedBy;
}

void Zone::setUnlockedBy(Item *unlockedBy) {
    Zone::unlockedBy = unlockedBy;
}

bool Zone::getIsDirectionOpen(ActionType direction) {
    return isDirectionOpen[getDirIndex(&direction)];
}

void Zone::setIsDirectionOpen(ActionType *direction, bool isOpen) {
    isDirectionOpen[getDirIndex(direction)] = isOpen;
}

void Zone::addEnemyToZone(Enemy * enemy) {
    this->enemies.emplace_back(enemy);
}

void Zone::printMonsters() {
    if ( !enemies.empty() ) {
        std::cout << "Enemy sighted: ";
        for(int j = 0; j < enemies.size(); ++j) {
            std::cout << *(enemies[j]->getName()) << " (hp: " << *(enemies[j]->getHealth()) << ")";
            if ( j != enemies.size()-1 ) std::cout << ", ";
            else std::cout << std::endl;
        }
    }
}

const vector<Enemy *> &Zone::getEnemies() const {
    return enemies;
}

void Zone::removeEnemyFromZone(Enemy *enemy) {
    for (int i = 0; i < enemies.size(); ++i) {
        if(enemies[i] == enemy){
            enemies.erase(enemies.begin()+i);
        }
    }
}

void Zone::removeDeadEnemies() {
    for(int j = 0; j < enemies.size(); ++j) {
        if( *(enemies[j]->getHealth()) <= 0) {
            std::cout << *(enemies[j]->getName()) << " dies." << std::endl;
            removeEnemyFromZone(enemies[j]);
        }
    }
}

int Zone::getDirIndex(ActionType *direction) {
    Directions dir;
    switch (*direction) {
        case ActionType::NORTH : {
            dir = NORTH;
            break;
        }
        case ActionType::EAST : {
            dir = EAST;
            break;
        }
        case ActionType::SOUTH : {
            dir = SOUTH;
            break;
        }
        case ActionType::WEST : {
            dir = WEST;
            break;
        }
        default: {
            std::cout<<"cant return valid direction" << std::endl;
        }
    }
    return static_cast<int>(dir);
}




