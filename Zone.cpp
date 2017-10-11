//
// Created by apha on 2017.10.09..
//

#include "Zone.h"
#include <iostream>


Zone::Zone(Area *description) : description(description) {
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

Zone* Zone::getZone(char direction) {
    Directions dir;
    switch (direction) {
        case 'n' : {
            dir = NORTH;
            break;
        }
        case 'e' : {
            dir = EAST;
            break;
        }
        case 's' : {
            dir = SOUTH;
            break;
        }
        case 'w' : {
            dir = WEST;
            break;
        }
        default: {
            std::cout<<"cant return valid direction for: " << direction << std::endl;
            return nullptr;
        }
    }
    return directions[dir];
}

void Zone::show() {
    const string *room = (*description).getDescription();
    std::cout << *room << std::endl;
}