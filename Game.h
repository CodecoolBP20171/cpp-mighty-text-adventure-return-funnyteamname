#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H

#include <vector>
#include "Area.hpp"
#include "Item.h"
#include "Enemy.h"
#include "Player.h"

using namespace std;

class Game {
public:
    void init();
    void run();
    enum class ActionType{
        INVALID_ENTRY, NORTH, SOUTH, EAST, WEST, ATTACK, EQUIP, UNEQUIP, DROP, USE
    };
    struct Command {
        ActionType action;
        vector<std::string> listOfObjects;
    };

private:
    // enum ActionType;
    vector<Area> areas; // areas has only non-changeable information
    vector<Item> items;
    vector<Enemy> enemies;

    void loadAreas();
    void loadItems();
    bool step();
    void parseInput(); //TODO:
                        // for movement: parse direction, check with the player's current Zone
                        // if direction is ok, then tell Player to move to the pointer that we get from
                        // the departure zone's corresponding direction
    ActionType parseAction(std::string* action);
    void handleCommand();
    bool isCommandValid();
    Command nextCommand;
    Player player;
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H
