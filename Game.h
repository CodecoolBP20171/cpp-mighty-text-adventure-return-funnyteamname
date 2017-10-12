#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H

#include <vector>
#include "Area.hpp"
#include "Item.h"
#include "Enemy.h"
#include "Player.h"
#include "ActionType.h"
#include "Zone.h"
#include "Player.h"

using namespace std;

class Game {
public:
    void init();
    void run();
    struct Command {
        ActionType action;
        std::string object;
    };

private:
    vector<Area> areas;
    vector<Item> items;
    vector<Enemy> enemies;
    vector<Zone> zones;
    Zone *startZone, *endZone;
    Player player;

    void loadAreas();
    void loadZones();
    void loadItems();
    void randomizeItemLocations();
    void linkZones();
    void linkTwo(Directions, int , int );
    bool isGameOn();
    void parseInput();
    ActionType parseAction(std::string* action);
    void handleCommand();
    bool isCommandValid();
    bool isCommandADirection();
    bool isDirectionValid(ActionType);
    bool isItemPickupable(std::string* itemName);
    void displayHelp(std::string* command);
    Command nextCommand;
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H
