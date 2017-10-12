#include <iostream>
#include <cstring>
#include "Game.h"
#include <algorithm>
#include <utility>
#include "vector"
#include "Player.h"
#include "ActionType.h"
#include <time.h>
#include "MapBuilder.h"


void Game::loadZones() {
    // nothing serious, just for testing
    std::pair<int,int> coordinates[7] = {std::make_pair(0,0),
                                         std::make_pair(0,1),
                                         std::make_pair(0,2),
                                         std::make_pair(1,1),
                                         std::make_pair(1,2),
                                         std::make_pair(0,3),
                                         std::make_pair(1,3)};
    for(int i = 0; i < 7; ++i) {
        zones.emplace_back( Zone( &areas.at(i), coordinates[i] ) );
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
    linkTwo(SOUTH,2,4);

}

void Game::loadItems() {
    Item swordWooden(3.0,
                     "Wooden sword",
                     "A near-useless unremarkable wooden sword. Mostly useful for training and not much else",
                     ItemType::WEAPON, 2, 0, UseEffectType::NONE);
    items.emplace_back(swordWooden);

    Item steelSword(8.0,
                    "Fine Steel sword",
                    "A sharp steel sword of excellent craftsmanship.",
                    ItemType::WEAPON, 8, 0, UseEffectType::NONE);
    items.emplace_back(steelSword);

    Item chainArmor(10.0,
                    "Chainmail armor",
                    "Mediocre armor, capable of providing some protection in battle at the cost of some added weight",
                    ItemType::ARMOR, 0, 10, UseEffectType::NONE);
    items.emplace_back(chainArmor);

    Item kiteShield(15.0,
                    "Large Kite Shield",
                    "An old large sturdy wooden kite shield. The front is covered in flecks of blue paint. It has a wooden handle in the back and leather straps hold the arm in place",
                    ItemType::SHIELD, 0, 20, UseEffectType::NONE);
    items.emplace_back(kiteShield);

    Item potionPalinka(1.0,
                       "Healing potion",
                       "Magical potion brewed with ancient wisdom, legend has it, it heals the imbiber but not past their maximum health",
                       ItemType::CONSUMABLE, 0, 0, UseEffectType::HEAL);
    items.emplace_back(potionPalinka);

    Item brassKey(0.3,
                  "Brass Key",
                  "An ornate brass key designed to unlock a rough, clumsy lock. A gate perhaps?",
                  ItemType::KEY, 0, 0, UseEffectType::OPEN_DOOR);
    items.emplace_back(brassKey);
}

void Game::loadEnemies() {
    Enemy orc("Orc warrior", 20, 10, 50);
    enemies.emplace_back(orc);

    Enemy troll("Cave troll", 30, 5, 120);
    enemies.emplace_back(troll);
}

void Game::init()
{
    loadAreas();
    loadZones();
    linkZones();
    loadItems();
    loadEnemies();
    randomizeItemLocations();

    startZone->setVisited(true);
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
    ActionType direction = ActionType::EAST;
    zones[4].setIsDirectionOpen(&direction, false);
    zones[4].setUnlockedBy(&items[5]);
    zones[1].addEnemyToZone(&enemies[0]);
    zones[4].addEnemyToZone(&enemies[1]);
    MapBuilder levelMap(4,2);
    while(!Game::isGameOn()){
        levelMap.drawMap(zones, startZone, player.getPosition() );
        player.getPosition()->show();
        player.displayInventory();
        parseInput();
        handleCommand();
        player.playerGetsAttacked();
    }
}

bool Game::isGameOn()
{
    if(player.getPosition() == endZone) {
        std::cout << "Congratulations! You managed to escape!" << std::endl;
        return true;
    } else if(player.getHealth() < 0) {
        std::cout << "Game over, you failed to survive the dungeon." << std::endl;
        return true;
    }
    return false;
}

void Game::parseInput() {
    std::string input;
    std::string word = "";
    do{
        Game::nextCommand.action = ActionType::INVALID_ENTRY;
        Game::nextCommand.object = "";
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
                    if(nextCommand.object != ""){
                        nextCommand.object += " ";
                    }
                    nextCommand.object += word;
                }
                word = "";
            }
        }
    } while(!isCommandValid());
}

ActionType Game::parseAction(std::string *word) {
    if(*word == "n" || *word == "north") return ActionType::NORTH;
    if(*word == "e" || *word == "east") return ActionType::EAST;
    if(*word == "s" || *word == "south") return ActionType::SOUTH;
    if(*word == "w" || *word == "west") return ActionType::WEST;
    if(*word == "a" || *word == "attack") return ActionType::ATTACK;
    if(*word == "eq" || *word == "equip") return ActionType::EQUIP;
    if(*word == "p" || *word == "pickup") return ActionType::PICKUP;
    if(*word == "unequip") return ActionType::UNEQUIP;
    if(*word == "drop") return ActionType::DROP;
    if(*word == "use") return ActionType::USE;
    if(*word == "help") return ActionType::HELP;
    return ActionType::INVALID_ENTRY;
}

bool Game::isCommandValid() {
    if(nextCommand.action == ActionType::INVALID_ENTRY) {
        std::cout << "Invalid command. Type \"help\" to get further information on the available commands." << std::endl;
      return false;
    }
    if(nextCommand.action == ActionType::ATTACK) {
        if(nextCommand.object != "" && nullptr == player.getPosition()->getEnemy(&nextCommand.object)){
            std::cout << "No enemy with that name found." << std::endl;
            return false;
        } else if (nextCommand.object == "") {
            std::cout << "No target specified." << std::endl;
            return false;
        };
        return true;
    }

    if(nextCommand.action == ActionType::EQUIP) {
        if(nullptr == player.getItemFromInventory(&nextCommand.object)){
            std::cout << nextCommand.object << " doesn't exist in your inventory." << std::endl;
            return false;
        }
        if(nullptr != player.getItemFromInventory(&nextCommand.object) && !player.isItemEquippable(&nextCommand.object)){
            std::cout << nextCommand.object << " is not equippable." << std::endl;
            return false;
        }
        return true;
    }

    if(nextCommand.action == ActionType::PICKUP) {
        if(!isItemPickupable(&nextCommand.object)) {
            std::cout << "No item called: \"" << nextCommand.object << "\" is nearby." << std::endl;
            return false;
        }
        if (!player.isWgtOk(&nextCommand.object)) {
            std::cout << "Picking up the " << nextCommand.object << " would make you encumbered." << std::endl;
            return false;
        }
        return true;
    }

    if(nextCommand.action == ActionType::UNEQUIP) {
        if(nullptr == player.getItemFromInventory(&nextCommand.object)) {
            std::cout << "You do not have " << nextCommand.object << " in your inventory." << std::endl;
            return false;
        }
        if(nullptr != player.getItemFromInventory(&nextCommand.object) && !player.isItemUnequippable(&nextCommand.object)) {
            std::cout << "Cannot unequip " << nextCommand.object << ", because it is not equipped." << std::endl;
            return false;
        }
        return true;
    }
    if(nextCommand.action == ActionType::DROP){
        if(nextCommand.object != ""  && nullptr == player.getItemFromInventory(&nextCommand.object)) {
            std::cout << "You do not have " << nextCommand.object << " in your inventory." << std::endl;
            return false;
        } else if(nextCommand.object == "") {
            std::cout << "Specify an item to drop." << std::endl;
            return false;
        }
        return true;
    }
    if(nextCommand.action == ActionType::USE) {
        if(nullptr == player.getItemFromInventory(&nextCommand.object)){
            std::cout << "No valid item specified for command" << std::endl;
            return false;
        }
        return true;
    }
    if(nextCommand.action == ActionType::HELP) return true;
    return isCommandADirection() && nextCommand.object.empty() && isDirectionValid(nextCommand.action);
}

void Game::handleCommand() {

    switch (nextCommand.action) {
        case ActionType::HELP:
            displayHelp(&nextCommand.object);
            break;
        case ActionType::ATTACK:
            std::cout << "You attack the " << nextCommand.object << std::endl;
            player.attack(player.getPosition()->getEnemy(&nextCommand.object));
            break;
        case ActionType::USE:
            std::cout << "You use the " << nextCommand.object << std::endl;
            player.use(player.getItemFromInventory(&nextCommand.object));
            break;
        case ActionType::PICKUP:
            std::cout << "You pick up the " << nextCommand.object << std::endl;
            player.pickup(&nextCommand.object);
            break;
        case ActionType::DROP:
            std::cout << "You drop the " << nextCommand.object << std::endl;
            player.drop(&nextCommand.object);
            break;
        case ActionType::EQUIP:
            std::cout << "You equips the " << nextCommand.object << std::endl;
            player.equip(&nextCommand.object);
            break;
        case ActionType::UNEQUIP:
            std::cout << "You unequips the " << nextCommand.object << std::endl;
            player.unequip(&nextCommand.object);
            break;
        case ActionType::NORTH:
            std::cout << "You go north... " << std::endl;
            player.moveTo(ActionType::NORTH);
            break;
        case ActionType::EAST:
            std::cout << "You go east... " << std::endl;
            player.moveTo(ActionType::EAST);
            break;
        case ActionType::SOUTH:
            std::cout << "You go south... " << std::endl;
            player.moveTo(ActionType::SOUTH);
            break;
        case ActionType::WEST:
            std::cout << "You go west... " << std::endl;
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
    if(!player.getPosition()->getIsDirectionOpen(direction)) {
        std::cout << "east: " << player.getPosition()->getIsDirectionOpen(ActionType::EAST) << std::endl;
        std::cout << "The way heading " << dirAsStr << " is closed by a large gate." << std::endl;
        return false;
    }
    return true;

}

void Game::randomizeItemLocations() {
    srand(time(NULL));
    for (int i = 0; i < items.size(); ++i) {
        int randomIndex = rand() % (zones.size()-1);
        zones[0].addToZoneInventory(&items[i]); // everything is put in the 1st zone now!
    }
}

bool Game::isItemPickupable(std::string *itemName) {
    return nullptr != player.getPosition()->getItem(itemName);
}

void Game::displayHelp(std::string* command) {
    if(nullptr == command || *command == "") {
        std::cout << "Use the letters or full word (non case sensitive) of the four cardinal directions to move around the level.\n";
        std::cout << "The following commands can interact with the world: attack, pickup, equip, drop, unequip, use.\n";
        std::cout << "You can get specific help appropriate for each command by typing \"help commandname\".\n";
    } else if (*command == "attack") {
        std::cout << "Specify the name of the enemy to attack it.\n";
    } else if (*command == "pickup"){
        std::cout << "Specify the name of the item to pick up if its weight won't make you over encumbered.\n";
    } else if(*command == "equip") {
        std::cout << "Specify the name of the item to equip. If you already have another item equipped in the target slot\n";
        std::cout << "then that item will be unequipped and placed in your backpack first.\n";
    } else if(*command == "drop") {
        std::cout << "Specify item to drop. If the item that you try to drop is equipped, it will be unequipped first\n";
        std::cout << "then placed on the ground.\n";
    } else if(*command == "unequip") {
        std::cout << "Specify item to unequip it. It will be removed from the corresponding slot and placed in your backpack.\n";
    } else if(*command == "use") {
        std::cout << "Specify item to use. Consumables are removed from your inventory afterwards.";
    } else {
        std::cout << "Invalid command specified after help.";
    }
}




