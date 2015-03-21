#ifndef MAPINTERFACE_H
#define MAPINTERFACE_H

#include <string>
#include <vector>
#include <allegro/gfx.h>

#include "Battlemap.h"
#include "Worldmap.h"

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
            Battlemaptile,
            Treasuremaptile
        };

        Mapinterface(Allegro_Datafile *Data);
        ~Mapinterface();

        Tiledata get_Tile(Tiletyp Map, const int Column, const int Row);

        bool get_Battlemapstatus();                                         // is a Battlemap valid?

        /*
            Generates a Battlemap with the Typ like "Gras", "Dessert", "Swamp", etc. ...
        */
        void generate_Battlemap(const std::string &Battletyp);
        void destroy_Battlemap();                                           // deletes a generated Battlemap

    private:

    std::vector<std::string> currBattlemap;
    bool validBattlemap;                                                        // Ask, is there an Battlemap?

    /*
        Get a Tile of the Battlemap and fills the following Data:
        Tile.Sheet = Bitmap of the Tilesheet.

        It fills Tile.Sheet with a NULL, if there is no valid Battlemap generated.
        It fills Tile.Index with 0, if there is no valid Battlemap generated.

        Is a Batllemap there, then the Tiledata are filled with the Tilesheet and
        calls convert_Tile.
    */
    void get_BattlemapTile(Tiledata &Tile, const int Column, const int Row);

    /*
        Fills the Data of the Typ Tiledata with Informations of the found Tile.
        It fills Tiledata.Index with the Position in the Tilesheet.
        Tiledata    .walkable
                    .flyable
                    .shipable
    */
    void convert_Tile(Tiledata &Tile, const char TChar);

    Allegro_Datafile *currDatafile;
    Battlemap *currBattlemapclass;
    Worldmap *currWorldmapclass;

}; // Mapinterface

#endif // MAPINTERFACE_H
