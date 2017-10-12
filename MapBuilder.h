#ifndef MIGHTY_TEXT_ADVENTURE_MAPBUILDER_H
#define MIGHTY_TEXT_ADVENTURE_MAPBUILDER_H

#include <iostream>
#include "Zone.h"

class MapBuilder {
private:
    static const std::string NO_ROUTE_N_S = "     ";
    static const std::string ROUTE_N_S =    "  |  ";
    static const std::string NO_ROUTE_E_W = " ";
    static const std::string ROUTE_E_W =    "-";
    static const std::string ZONE =         "( )";
    static const std::string START_ZONE =   "(S)";
    static const std::string CURRENT_ZONE = "(X)";

    int mapWidth;
    int mapHeight;

public:
    MapBuilder(int, int);
    void setMapSize(int, int);
    void drawMap(vector<Zone> &, Zone*& );
    
};


#endif //MIGHTY_TEXT_ADVENTURE_MAPBUILDER_H
