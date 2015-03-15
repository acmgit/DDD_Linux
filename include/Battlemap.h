#ifndef BATTLEMAP_H
#define BATTLEMAP_H

#include <string>
#include <sys/time.h>

#include "Allegro_Datafile.h"

class Battlemap
{
    public:
        struct Battledata
        {
            int Gras;
            int Shrubbery;
            int Forest;
            int Boulder;
            int Mountain;
            int Swamp;
            int River;
            int Sea;
            int Lava;
            int Dessert;
        }; // struct Battledata

        Battlemap(Allegro_Datafile *Datafile);
        ~Battlemap();
        /*
            generate's a Row for the Battlemap, Typo is a string for an special Tile
            This string has the simple Name of the Tile like, Gras, Dessert, Swamp, etc. ...
            They Data's can found in Allegro_Datafile::find_Index("BAT_" + Typo)
            Now the Row will generated with the Data of this Table.
            The Table has an Entry of Battledata and the Entry's are only Numbers of Percent's
            like Gras = 20, Swamp = 10, Dessert = 0 etc. ...
            This Numbers now: Gras = 20%, Swamp = 10%, no Dessert etc. ...
            The Sum of the Table is 100%. If there are more as 100%, the Tiles will not generated.
            If there are lower as 100%, then unknown Tiles will be generated.
        */
        std::string get_Battlerow(const std::string Typo, const int Columns);

    private:

        int generate_Random(const int Low, const int High);
        bool isTile(int Value, int Min, int Max);

    Allegro_Datafile *Data;
    time_t btime;

/*
    int lastRandom;
*/
}; // Battlemap

#endif // BATTLEMAP_H
