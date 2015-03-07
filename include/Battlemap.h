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

        std::string getBattlerow(const std::string Typo, const int Columns);

    private:

        int generateRandom(const int Low, const int High);
        bool isTile(int Value, int Min, int Max);

    Allegro_Datafile *Data;
    timeval currTime;
    int lastRandom;

}; // Battlemap

#endif // BATTLEMAP_H
