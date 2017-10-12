//
// Created by apha on 2017.10.09..
//

#include "Zone.h"
#include <iostream>


Zone::Zone(Area *description, std::pair<int, int> coords) : description(description), coords(coords) {
    visited = false;
    for (int i = 0; i < 4; ++i ) {
        directions[i] = nullptr;
    };
}

Enemy* Zone::getEnemy(std::string *enemy) {
    return nullptr;
}

void Zone::setVisited(bool isItVisited) {
    visited = isItVisited;
}

void Zone::setZone(Directions direction, Zone * zoneToConnect) {
    directions[direction] = zoneToConnect;
}

Zone* Zone::getZone(ActionType direction) {
    Directions dir;
    switch (direction) {
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
            return nullptr;
        }
    }
    return directions[dir];
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
        std::cout << "You can see in this room the following stuffs: ";
        for(int i = 0; i < inventory.size(); ++i) {
            std::cout << inventory[i]->getName();
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
    printDirections();
    printItems();
}

bool Zone::isVisited() {
    return visited;
}