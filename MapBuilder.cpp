
#include <sstream>
#include "MapBuilder.h"

MapBuilder::MapBuilder(int mapWidth, int mapHeight) : mapWidth(mapWidth), mapHeight(mapHeight) {}

void MapBuilder::drawMap(vector<Zone> & zones, Zone * startZone, Zone * currentZone) {
    std::stringstream wanderedMap;

    for (int i = 0; i < mapHeight ; ++i) {

        for (int j = 0; j < mapWidth ; ++j) {
            for ( Zone zone : zones) {
                if (zone.getCoords() == make_pair(i,j) && zone.getZone(ActionType::NORTH) != nullptr && zone.isVisited()) {
                    wanderedMap << ROUTE_N_S;
                    break;
                }
                if (zone.getCoords() == make_pair(mapHeight-1, mapWidth-1)) {
                    wanderedMap << NO_ROUTE_N_S;
                }
            }
        }
        wanderedMap << "\n";

        for (int j = 0; j < mapWidth ; ++j) {
            for (Zone zone : zones) {
                if ( zone.getCoords() == make_pair(i,j) && zone.isVisited() ) {

                    if (zone.getZone(ActionType::WEST) != nullptr) {
                        wanderedMap << ROUTE_E_W;
                    } else {
                        wanderedMap << NO_ROUTE_E_W;
                    }

                    if (zone.getCoords() == startZone->getCoords()) wanderedMap << START_ZONE;
                    else if (zone.getCoords() == currentZone->getCoords()) wanderedMap << CURRENT_ZONE;
                    else wanderedMap << ZONE;

                    if (zone.getZone(ActionType::EAST) != nullptr) {
                        wanderedMap << ROUTE_E_W;
                    } else {
                        wanderedMap << NO_ROUTE_E_W;
                    }
                    break;
                }
                if (zone.getCoords() == make_pair( mapHeight-1, mapWidth-1)) wanderedMap << NO_ROUTE_N_S;
            }
        }
        wanderedMap << "\n";

        for (int j = 0; j < mapWidth ; ++j) {
            for ( Zone zone : zones) {
                if (zone.getCoords() == make_pair(i,j) && zone.getZone(ActionType::SOUTH) != nullptr && zone.isVisited()) {
                    wanderedMap << ROUTE_N_S;
                    break;
                }
                if (zone.getCoords() == make_pair(mapHeight-1, mapWidth-1)) {
                    wanderedMap << NO_ROUTE_N_S;
                }
            }
        }
        wanderedMap << "\n";
    }
    std::cout << wanderedMap.str();
}
