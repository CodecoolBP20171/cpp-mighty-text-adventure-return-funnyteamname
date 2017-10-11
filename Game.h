#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H

#include <vector>
#include "Area.hpp"
#include "Zone.h"
#include "Player.h"

using namespace std;

class Game {
public:
    Game();
    void init();
    void run();

private:
    vector<Area> areas; // areas has only non-changeable information
    vector<Zone> zones;
    Zone *startZone, *endZone;
    Player player;

    void loadAreas();
    void loadZones();
    void loadItems();
    void linkZones();
    void linkTwo(Directions, int , int );
    bool step();
    void parseInput(); //TODO:
                        // for movement: parse direction, check with the player's current Zone
                        // if direction is ok, then tell Player to move to the pointer that we get from
                        // the departure zone's corresponding direction
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H
