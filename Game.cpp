#include <iostream>
#include <cstring>
#include "Game.h"
#include <algorithm>
#include "vector"
#include "Player.h"
#include "ActionType.h"


void Game::init()
{
    loadAreas();
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
        parseInput();
        handleCommand();
        std::cout << "end of game loop \n";
    }
}

bool Game::step()
{
    return false;
}

void Game::parseInput() {
    std::string input;
    std::string word = "";
    do{
        Game::nextCommand.action = ActionType::INVALID_ENTRY;
        Game::nextCommand.listOfObjects.clear();
        std::cout << "Please input action: " << std::endl;
        getline(cin, input);
        int length = strlen(input.c_str());
        for (int i = 0; i <= length; ++i) {
            if(!isspace(input[i]) && i < length) {
                std::tolower(input[i]);
                word += std::tolower(input[i]);
            } else if((i == length) || (isspace(input[i])) && word != "") {
                if(nextCommand.action == ActionType::INVALID_ENTRY) {
                    nextCommand.action = parseAction(&word);
                } else {
                    nextCommand.listOfObjects.push_back(word);
                }
                word = "";
            }
        }
    } while(!isCommandValid());
    std::cout << "entry was valid\n";
    std::cout << "action: " << static_cast<int>(nextCommand.action) << endl;
    for(auto& object: nextCommand.listOfObjects){
        std::cout << "object: " << object << std::endl;
    }
}

ActionType Game::parseAction(std::string *word) {
    if(*word == "n" || *word == "north") return ActionType::NORTH;
    if(*word == "e" || *word == "east") return ActionType::EAST;
    if(*word == "s" || *word == "south") return ActionType::SOUTH;
    if(*word == "w" || *word == "west") return ActionType::WEST;
    if(*word == "a" || *word == "attack") return ActionType::ATTACK;
    if(*word == "eq" || *word == "equip") return ActionType::EQUIP;
    if(*word == "unequip") return ActionType::UNEQUIP;
    if(*word == "drop") return ActionType::DROP;
    if(*word == "use") return ActionType::USE;
    return ActionType::INVALID_ENTRY;
}

bool Game::isCommandValid() {
    // TODO will need a function to check if the objects to interact with are valid!
    if(nextCommand.action == ActionType::INVALID_ENTRY) return false;
    if(nextCommand.action == ActionType::ATTACK && nextCommand.listOfObjects.size() != 1) return false;
    if(nextCommand.action == ActionType::EQUIP && nextCommand.listOfObjects.empty()) return false;
    if(nextCommand.action == ActionType::UNEQUIP && nextCommand.listOfObjects.empty()) return false;
    if(nextCommand.action == ActionType::DROP && nextCommand.listOfObjects.empty()) return false;
    if(nextCommand.action == ActionType::USE && nextCommand.listOfObjects.size() != 1) return false;
    return !((nextCommand.action == ActionType::NORTH ||
              nextCommand.action == ActionType::EAST ||
              nextCommand.action == ActionType::SOUTH ||
              nextCommand.action == ActionType::WEST) &&
             !nextCommand.listOfObjects.empty());
}

void Game::handleCommand() {

    switch (nextCommand.action) {
        case ActionType::ATTACK:
            player.attack(player.getNearbyEnemy(&nextCommand.listOfObjects[0]));
            break;
        case ActionType::USE:
            player.use(player.getItemFromInventory(&nextCommand.listOfObjects[0]));
            break;
        case ActionType::DROP:
            for (int i = 0; i < nextCommand.listOfObjects.size() ; ++i) {
                player.drop(player.getItemFromInventory(&nextCommand.listOfObjects[i]));
            }
            break;
        case ActionType::EQUIP:
            for (int j = 0; j < nextCommand.listOfObjects.size() ; ++j) {
                player.equip(player.getItemFromInventory(&nextCommand.listOfObjects[j]));
            }
            break;
        case ActionType::UNEQUIP:
            for (int k = 0; k < nextCommand.listOfObjects.size() ; ++k) {
                player.unequip(player.getItemFromInventory(&nextCommand.listOfObjects[k]));
            }
            break;
        case ActionType::NORTH:
            player.moveTo(ActionType::NORTH);
            break;
        case ActionType::EAST:
            player.moveTo(ActionType::EAST);
            break;
        case ActionType::SOUTH:
            player.moveTo(ActionType::SOUTH);
            break;
        case ActionType::WEST:
            player.moveTo(ActionType::WEST);
            break;
    }
}


