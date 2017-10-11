#include <iostream>
#include <cstring>
#include "Game.h"
#include <algorithm>
#include "vector"
#include "Player.h"
#include "ActionType.h"
#include <time.h>


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

void Game::loadItems() {
    Item swordWooden(3.0,
                     "Wooden sword",
                     "A near-useless unremarkable wooden sword. Mostly useful for training and not much else",
                     ItemType::WEAPON, 2, 0);
    items.emplace_back(swordWooden);

    Item steelSword(8.0,
                    "Fine Steel sword",
                    "A sharp steel sword of excellent craftsmanship.",
                    ItemType::WEAPON, 8, 0);
    items.emplace_back(steelSword);

    Item chainArmor(10.0,
                    "Chainmail armor",
                    "Mediocre armor, capable of providing some protection in battle at the cost of some added weight",
                    ItemType::ARMOR, 0, 10);
    items.emplace_back(chainArmor);

    Item kiteShield(15.0,
                    "Large Kite Shield",
                    "An old large sturdy wooden kite shield. The front is covered in flecks of blue paint. It has a wooden handle in the back and leather straps hold the arm in place",
                    ItemType::SHIELD, 0, 20);
    items.emplace_back(kiteShield);

    Item potionPalinka(1.0,
                       "Magical Pálinka of Forgetfulness",
                       "Magical potion brewed with ancient wisdom, legend has it, that it makes the imbiber see the world differently...",
                       ItemType::CONSUMABLE, 0, 0);
    items.emplace_back(potionPalinka);

    Item brassKey(0.3,
                  "Brass Key",
                  "An ornate brass key designed to unlock a rough, clumsy lock. A gate perhaps?",
                  ItemType::KEY, 0, 0);
    items.emplace_back(brassKey);
}

void Game::init()
{
    loadAreas();
    loadZones();
    linkZones();
    loadItems();
    randomizeItemLocations();
    player.setPosition(startZone);
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
        player.getPosition()->show();
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
    // std::cout << "entry was valid\n";
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
    if(nextCommand.action == ActionType::INVALID_ENTRY) {
        std::cout << "Invalid command. Type \"help\" to get further information on the available commands." << std::endl;
      return false;
    }
    if(nextCommand.action == ActionType::ATTACK && nextCommand.listOfObjects.size() != 1) return false;
    if(nextCommand.action == ActionType::EQUIP && nextCommand.listOfObjects.empty()) return false;
    if(nextCommand.action == ActionType::UNEQUIP && nextCommand.listOfObjects.empty()) return false;
    if(nextCommand.action == ActionType::DROP && nextCommand.listOfObjects.empty()) return false;
    if(nextCommand.action == ActionType::USE && nextCommand.listOfObjects.size() != 1) return false;

    return isCommandADirection() && nextCommand.listOfObjects.empty() && isDirectionValid(nextCommand.action);
}

void Game::handleCommand() {

    switch (nextCommand.action) {
        case ActionType::ATTACK:
            std::cout << "player attacks: " << nextCommand.listOfObjects[0] << std::endl;
            // player.attack(player.getNearbyEnemy(&nextCommand.listOfObjects[0]));
            break;
        case ActionType::USE:
            std::cout << "player uses: " << nextCommand.listOfObjects[0] << std::endl;
            // player.use(player.getItemFromInventory(&nextCommand.listOfObjects[0]));
            break;
        case ActionType::DROP:
            std::cout << "player drops: " << std::endl;
            for (int i = 0; i < nextCommand.listOfObjects.size() ; ++i) {
                std::cout << "object: " << nextCommand.listOfObjects[i] << std::endl;
                // player.drop(player.getItemFromInventory(&nextCommand.listOfObjects[i]));
            }
            break;
        case ActionType::EQUIP:
            std::cout << "player equips: " << std::endl;
            for (int j = 0; j < nextCommand.listOfObjects.size() ; ++j) {
                std::cout << "object: " << nextCommand.listOfObjects[j] << std::endl;
                //player.equip(player.getItemFromInventory(&nextCommand.listOfObjects[j]));
            }
            break;
        case ActionType::UNEQUIP:
            std::cout << "player unequips: " << std::endl;
            for (int k = 0; k < nextCommand.listOfObjects.size() ; ++k) {
                std::cout << "object: " << nextCommand.listOfObjects[k] << std::endl;
                //player.unequip(player.getItemFromInventory(&nextCommand.listOfObjects[k]));
            }
            break;
        case ActionType::NORTH:
            std::cout << "player goes north... " << std::endl;
            player.moveTo(ActionType::NORTH);
            break;
        case ActionType::EAST:
            std::cout << "player goes east... " << std::endl;
            player.moveTo(ActionType::EAST);
            break;
        case ActionType::SOUTH:
            std::cout << "player goes south... " << std::endl;
            player.moveTo(ActionType::SOUTH);
            break;
        case ActionType::WEST:
            std::cout << "player goes west... " << std::endl;
            player.moveTo(ActionType::WEST);
            break;
    }
}

bool Game::isCommandADirection() {
    return (nextCommand.action == ActionType::NORTH ||
            nextCommand.action == ActionType::EAST ||
            nextCommand.action == ActionType::SOUTH ||
            nextCommand.action == ActionType::WEST );
}

bool Game::isDirectionValid(ActionType direction) {
    std::string dirAsStr;
    switch (direction) {
        case ActionType::NORTH: dirAsStr = "North"; break;
        case ActionType::EAST: dirAsStr = "East"; break;
        case ActionType::SOUTH: dirAsStr = "South"; break;
        case ActionType::WEST: dirAsStr = "West"; break;
    }
    if(nullptr == player.getPosition()->getZone(direction)) {
        std::cout << "You cannot go " << dirAsStr << " from here..." << std::endl;
        return false;
    }
    return true;

}

void Game::randomizeItemLocations() {
    for (int i = 0; i < items.size(); ++i) {
        srand(time(NULL));
        int randomIndex = rand() % (zones.size()-1);
        zones[randomIndex].addToZoneInventory(&items[i]);
    }
}



