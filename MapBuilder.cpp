
#include <sstream>
#include "MapBuilder.h"

MapBuilder::MapBuilder(int mapWidth, int mapHeight) : mapWidth(mapWidth), mapHeight(mapHeight) {}

void MapBuilder::drawMap(vector<Zone> & zones, Zone *& startZone) {
    std::stringstream wanderedMap;
    for (int i = 0; i < mapHeight ; ++i) {
        for (int j = 0; j < mapWidth ; ++j) {
            for ( Zone zone : zones) {
                if (zone.getZone(ActionType::NORTH) != nullptr)
            }
        }
        for (int j = 0; j < mapWidth ; ++j) {

        }
        for (int j = 0; j < mapWidth ; ++j) {

        }
    }

}
