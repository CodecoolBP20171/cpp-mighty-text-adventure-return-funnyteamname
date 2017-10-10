#include <iostream>
#include <cstring>
#include "Game.h"
#include <algorithm>
#include "vector"
#include "Player.h"


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
                    std::string toAdd;
                    toAdd = word;
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

void Game::handleCommand() {
    if(nextCommand.action == ActionType::ATTACK) {
        std::string * pEnemyName = &nextCommand.listOfObjects[1];
        player.attack(player.getNearbyEnemy(pEnemyName));
    }
}

bool Game::isCommandValid() {
    // TODO will need a function to check if the objects to interact with are valid!
    if(nextCommand.action == ActionType::INVALID_ENTRY) return false;
    if(nextCommand.action == ActionType::ATTACK && nextCommand.listOfObjects.size() != 1) return false;
    if(nextCommand.action == ActionType::EQUIP && nextCommand.listOfObjects.size() == 0) return false;
    if(nextCommand.action == ActionType::UNEQUIP && nextCommand.listOfObjects.size() == 0) return false;
    if(nextCommand.action == ActionType::DROP && nextCommand.listOfObjects.size() == 0) return false;
    if(nextCommand.action == ActionType::USE && nextCommand.listOfObjects.size() != 1) return false;
    return !((nextCommand.action == ActionType::NORTH ||
              nextCommand.action == ActionType::EAST ||
              nextCommand.action == ActionType::SOUTH ||
              nextCommand.action == ActionType::WEST) &&
              nextCommand.listOfObjects.size() != 0);
}

Game::ActionType Game::parseAction(std::string *word) {
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
