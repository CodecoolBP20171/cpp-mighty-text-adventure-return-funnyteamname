#include <iostream>
#include "Game.h"

void Game::loadZones() {
    // nothing serious, just for testing
    for(int i = 0; i < 7; ++i) {
        zones.emplace_back( Zone( &areas.at(i) ) );
    }
    startZone = & zones.at(0);
    endZone = & zones.at(6);
}
void Game::linkTwo(Directions dir1, int zone1, int zone2) {
    Directions dir2 = static_cast<Directions >((dir1 + endMark/2)%endMark); //looking up opposite direction
    zones[zone1].setZone(dir1, &zones[zone2]);
    zones[zone2].setZone(dir2, &zones[zone1]);
}

void Game::linkZones() {
    // nothing serious, just for testing
    /*
     * Start -- 1 -- 2 -- 5
     *          |    |
     *          3 -- 4 -- 6(end)
     *                          */
    linkTwo(EAST,0,1);
    linkTwo(EAST,1,2);
    linkTwo(EAST,2,5);
    linkTwo(EAST,3,4);
    linkTwo(EAST,4,6);
    linkTwo(SOUTH,1,3);
    linkTwo(SOUTH,1,3);

}

void Game::init()
{
    loadAreas();
    loadZones();
    linkZones();

    player = Player(startZone);
}

void Game::loadAreas()
{
    areas.emplace_back("start room");
    areas.emplace_back("room 1");
    areas.emplace_back("room 2");
    areas.emplace_back("room 3");
    areas.emplace_back("room 4");
    areas.emplace_back("room 5");
    areas.emplace_back("room 6");
}

void Game::run()
{
    while(!step()){
        // for testing
        player.getPosition().show();
    }
}

bool Game::step()
{
    return true;
}
