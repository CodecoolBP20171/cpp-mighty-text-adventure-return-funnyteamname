
#include <sstream>
#include "MapBuilder.h"

MapBuilder::MapBuilder(int mapWidth, int mapHeight) : mapWidth(mapWidth), mapHeight(mapHeight) {}

bool MapBuilder::isLastZone(Zone * zone) {
    return zone->getCoords() == make_pair( mapHeight-1, mapWidth-1);
}

void MapBuilder::drawNSConnectionLines(int i, ActionType dir) {
    for (int j = 0; j < mapWidth ; ++j) {
        for ( Zone zone : *zones) {
            if (zone.getCoords() == make_pair(i,j) && zone.getZone(dir) != nullptr && zone.isVisited()) {
                wanderedMap << ROUTE_N_S;
                break;
            }
            if (isLastZone(&zone)) {
                wanderedMap << BLANK_SPACE;
            }
        }
    }
    wanderedMap << "\n";
}

void MapBuilder::drawEWConnection(Zone * zone, ActionType dir) {
    if (zone->getZone(dir) != nullptr) {
        wanderedMap << ROUTE_E_W;
    } else {
        wanderedMap << NO_ROUTE_E_W;
    }
}

void MapBuilder::drawZone(Zone * zone, Zone * startZone, Zone * currentZone) {
    if (zone->getCoords() == startZone->getCoords()) wanderedMap << START_ZONE;
    else if (zone->getCoords() == currentZone->getCoords()) wanderedMap << CURRENT_ZONE;
    else wanderedMap << ZONE;
}

void MapBuilder::drawMap(vector<Zone> & zonesList, Zone * startZone, Zone * currentZone) {
    zones = & zonesList;
    wanderedMap.str();
    wanderedMap << "\nMarauder's Map\n";

    for (int i = 0; i < mapHeight ; ++i) {

        drawNSConnectionLines(i,ActionType::NORTH);

        for (int j = 0; j < mapWidth ; ++j) {
            for (Zone zone : *zones) {
                if ( zone.getCoords() == make_pair(i,j) && zone.isVisited() ) {
                    drawEWConnection ( &zone, ActionType::WEST );
                    drawZone ( &zone, startZone, currentZone );
                    drawEWConnection ( &zone, ActionType::EAST );
                    break;
                }
                if (isLastZone(&zone)) wanderedMap << BLANK_SPACE;
            }
        }
        wanderedMap << "\n";

        drawNSConnectionLines(i,ActionType::SOUTH);
    }
    std::cout << wanderedMap.str();
}
