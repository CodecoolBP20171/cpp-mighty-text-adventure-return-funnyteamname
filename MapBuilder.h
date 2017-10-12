#ifndef MIGHTY_TEXT_ADVENTURE_MAPBUILDER_H
#define MIGHTY_TEXT_ADVENTURE_MAPBUILDER_H

#include <iostream>
#include <vector>
#include <sstream>
#include "Zone.h"

class MapBuilder {
private:
    const std::string BLANK_SPACE = "     ";
    const std::string ROUTE_N_S =    "  |  ";
    const std::string NO_ROUTE_E_W = " ";
    const std::string ROUTE_E_W =    "-";
    const std::string ZONE =         "( )";
    const std::string START_ZONE =   "(S)";
    const std::string CURRENT_ZONE = "(X)";

    int mapWidth;
    int mapHeight;

    vector<Zone> * zones;
    std::stringstream wanderedMap;

    void drawNSConnectionLines(int, ActionType);
    void drawEWConnection(Zone*, ActionType);
    void drawZone(Zone*, Zone*, Zone*);
    bool isLastZone(Zone*);

public:
    MapBuilder(int, int);

    void setMapSize(int, int);
    void drawMap(vector<Zone> &, Zone* , Zone*);

};


#endif //MIGHTY_TEXT_ADVENTURE_MAPBUILDER_H
