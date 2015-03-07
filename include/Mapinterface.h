#ifndef MAPINTERFACE_H
#define MAPINTERFACE_H

#include <string>
#include <vector>
#include <allegro/gfx.h>

#include "Battlemap.h"
#include "Allegro_Datafile.h"

class Mapinterface
{
    public:

        struct Tiledata
        {
            BITMAP *Sheet;
            int Index;
            bool walkable;
            bool shipable;
            bool flyable;
        };

        enum Tiletyp
        {
            Worldmaptile = 1,
            Townmaptile,
            Battlemaptile
        };

        Mapinterface(Allegro_Datafile *Data);
        ~Mapinterface();

        Tiledata getTile(Tiletyp Map, const int Column, const int Row);

        bool getBattlemapstatus();
        void generateBattlemap(const std::string Battletyp);
        void destroyBattlemap();

    private:

    std::vector<std::string> currBattlemap;
    bool validBattlemap;
    void getBattlemapTile(Tiledata &Tile, const int Column, const int Row);

    Allegro_Datafile *currDatafile;
    Battlemap *currBattlemapclass;
};

#endif // MAPINTERFACE_H
