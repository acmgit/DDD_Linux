#ifndef BATTLEMAP_CPP
#define BATTLEMAP_CPP

#include "Battlemap.h"

#include <string>
#include <sys/time.h>
#include <allegro/system.h>

#ifdef DEBUG
#include "Logfile.h"
#endif // DEBUG

#include "Allegro_Datafile.h"

Battlemap::Battlemap(Allegro_Datafile *Datafile)
{
    if(!Datafile)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.WRONG_FUNCTION << ") No Datafile for Battlemapgenerator given.")
        #endif // DEBUG

        allegro_message("No Datafile for Battlemapgenerator given ...");
        allegro_exit();
    }

    Data = Datafile;

    // Initalise the Randomseed
    gettimeofday(&currTime, 0);
    lastRandom = currTime.tv_usec;

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Battlemapgenerator opened.")
    #endif // DEBUG

} // Battlemap()

Battlemap::~Battlemap()
{
    Data = nullptr;

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Battlemapgenerator closed.")
    #endif // DEBUG

} // ~Battlemap()

std::string Battlemap::getBattlerow(const std::string Typo, const int Columns)
{
    std::string Typ = "[BAT_" + Typo;
    std::string Row;

/*
#ifdef DEBUG
    Log("Battlemap generates a Line of " << Typ.c_str() << "_...] with " << Columns << " Columns.")
#endif // DEBUG
*/
    Battledata Seed;

    Seed.Gras = Data->findIndex(Typ + "_Gras]").Number;
    Seed.Shrubbery = Data->findIndex(Typ + "_Shrubbery]").Number;
    Seed.Forest = Data->findIndex(Typ + "_Forest]").Number;
    Seed.Boulder = Data->findIndex(Typ + "_Boulder]").Number;
    Seed.Mountain = Data->findIndex(Typ + "_Mountain]").Number;
    Seed.Sea = Data->findIndex(Typ + "_Sea]").Number;
    Seed.River = Data->findIndex(Typ + "_River]").Number;
    Seed.Dessert = Data->findIndex(Typ + "_Dessert]").Number;
    Seed.Swamp = Data->findIndex(Typ + "_Swamp]").Number;
    Seed.Lava = Data->findIndex(Typ + "_Lava]").Number;

/*
#ifdef DEBUG
    Log("% of Gras = " << Seed.Gras << "%.")
    Log("% of Shrubbery = " << Seed.Shrubbery << "%.")
    Log("% of Forest = " << Seed.Forest << "%.")
    Log("% of Boulder = " << Seed.Boulder << "%.")
    Log("% of Mountain = " << Seed.Mountain << "%.")
    Log("% of Sea = " << Seed.Sea << "%.")
    Log("% of River = " << Seed.River << "%.")
    Log("% of Dessert = " << Seed.Dessert << "%.")
    Log("% of Swamp = " << Seed.Swamp << "%.")
    Log("% of Lava = " << Seed.Lava << "%.")
#endif // DEBUG
*/
    int genTile;

    for(int Column = 0; Column < Columns; ++Column)
    {
        genTile = generateRandom(0, 101);
/*
        #ifdef DEBUG
        Log("Random = " << genTile)
        #endif // DEBUG
*/
        int maxPercent = Seed.Gras;
        int minPercent = 0;

        if(isTile(genTile, minPercent, maxPercent))             // is Gras
        {
            Row = Row + "G";

        }
        else
        {
            minPercent = Seed.Gras;
            maxPercent = maxPercent + Seed.Shrubbery;
            if(isTile(genTile, minPercent, maxPercent))         // is Shrubbery
            {
                Row = Row + "S";

            }
            else
            {
                minPercent = minPercent + Seed.Shrubbery;
                maxPercent = maxPercent + Seed.Shrubbery;
                if(isTile(genTile, minPercent, maxPercent))     // is Forest
                {
                    Row = Row + "F";

                }
                else
                {
                    minPercent = minPercent + Seed.Boulder;
                    maxPercent = maxPercent + Seed.Boulder;
                    if(isTile(genTile, minPercent, maxPercent)) // is Boulder
                    {
                        Row = Row + "B";

                    }
                    else
                    {
                        minPercent = minPercent + Seed.Mountain;
                        maxPercent = maxPercent + Seed.Mountain;
                        if(isTile(genTile, minPercent, maxPercent)) // is Mountain
                        {
                            Row = Row + "M";

                        }
                        else
                        {
                           minPercent = minPercent + Seed.Dessert;
                           maxPercent = maxPercent + Seed.Dessert;
                           if(isTile(genTile, minPercent, maxPercent))  // is Dessert
                           {
                               Row = Row + "D";

                           }
                           else
                           {
                               minPercent = minPercent + Seed.Swamp;
                               maxPercent = maxPercent + Seed.Swamp;
                               if(isTile(genTile, minPercent, maxPercent))  // is Swamp
                               {
                                   Row = Row + "m";

                               }
                               else
                               {
                                   minPercent = minPercent + Seed.River;
                                   maxPercent = maxPercent + Seed.River;
                                   if(isTile(genTile, minPercent, maxPercent))  // is River
                                   {
                                       Row = Row + "w";

                                   }
                                   else
                                   {
                                       minPercent = minPercent + Seed.Sea;
                                       maxPercent = maxPercent + Seed.Sea;
                                       if(isTile(genTile, minPercent, maxPercent)) // is Sea
                                       {
                                           Row = Row + "W";

                                       }
                                       else
                                       {
                                           minPercent = minPercent + Seed.Lava;
                                           maxPercent = maxPercent + Seed.Lava;
                                           if(isTile(genTile, minPercent, maxPercent))  // is Lava
                                           {
                                               Row = Row + "l";

                                           }
                                           else
                                           {
                                               Row = Row + "x";                         // Unknown Tile;

                                           } // is Lava

                                       } // is Sea

                                   } // is River

                               } // is Swamp

                           } // is Dessert

                        } // is Mountain

                    } // is Boulder

                } // if Forest

            } // if Shrubbery

        } // if Gras

    } // For Column
/*
    #ifdef DEBUG
    Log("Value = " << Seed.Boulder + Seed.Dessert + Seed.Forest + Seed.Gras + Seed.Lava + Seed.Mountain + Seed.River + Seed.Sea + Seed.Shrubbery + Seed.Swamp << "%.")
    Log("Row = " << Row.c_str())
    #endif // DEBUG
*/
    return Row;
} // getBattlerow(Typo, Columns)

bool Battlemap::isTile(int Value, int Min, int Max)
{
    if((Value >= Min) && (Value < Max))
    {
        return true;
    }

    return false;

} // isTile

int Battlemap::generateRandom(const int Low, const int High)
{
    gettimeofday(&currTime, 0);

    int thisRandom = (currTime.tv_sec * lastRandom + Low) % High;
    lastRandom = thisRandom;
    return thisRandom;

} // generateRandom

#endif // BATTLEMAP_CPP
