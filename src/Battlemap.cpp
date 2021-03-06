#ifndef BATTLEMAP_CPP
#define BATTLEMAP_CPP

#include "Battlemap.h"

#include <string>
#include <time.h>
#include <allegro/system.h>
#include <stdio.h>
#include <stdlib.h>

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
    time(&btime);
    srand((unsigned int) btime);
/*
    gettimeofday(&currTime, 0);
    lastRandom = currTime.tv_usec;
*/
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

std::string Battlemap::get_Battlerow(const std::string &Typo, const int Columns)
{
    std::string Typ = "[BAT_" + Typo;
    std::string Row;

/*
#ifdef DEBUG
    Log("Battlemap generates a Line of " << Typ.c_str() << "_...] with " << Columns << " Columns.")
#endif // DEBUG
*/
    Battledata Seed;

    Seed.Gras = Data->find_Index(Typ + "_Gras]").Number;
    Seed.Shrubbery = Data->find_Index(Typ + "_Shrubbery]").Number;
    Seed.Forest = Data->find_Index(Typ + "_Forest]").Number;
    Seed.Boulder = Data->find_Index(Typ + "_Boulder]").Number;
    Seed.Mountain = Data->find_Index(Typ + "_Mountain]").Number;
    Seed.Sea = Data->find_Index(Typ + "_Sea]").Number;
    Seed.River = Data->find_Index(Typ + "_River]").Number;
    Seed.Dessert = Data->find_Index(Typ + "_Dessert]").Number;
    Seed.Swamp = Data->find_Index(Typ + "_Swamp]").Number;
    Seed.Lava = Data->find_Index(Typ + "_Lava]").Number;

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
        genTile = generate_Random(0, 100);
/*
        #ifdef DEBUG
        Log("Random = " << genTile)
        #endif // DEBUG
*/
        int minPercent = 0;
        int maxPercent = Seed.Gras;

        if(isTile(genTile, minPercent, maxPercent))             // is Gras
        {
            Row = Row + "g";

        }
        else
        {
            minPercent = maxPercent;
            maxPercent = minPercent + Seed.Shrubbery;
            if(isTile(genTile, minPercent, maxPercent))         // is Shrubbery
            {
                Row = Row + "w";
            }
            else
            {
                minPercent = maxPercent;
                maxPercent = minPercent + Seed.Forest;
                if(isTile(genTile, minPercent, maxPercent))     // is Forest
                {
                    Row = Row + "W";

                }
                else
                {
                    minPercent = maxPercent;
                    maxPercent = minPercent + Seed.Boulder;
                    if(isTile(genTile, minPercent, maxPercent)) // is Boulder
                    {
                        Row = Row + "n";

                    }
                    else
                    {
                        minPercent = maxPercent;
                        maxPercent = minPercent + Seed.Mountain;
                        if(isTile(genTile, minPercent, maxPercent)) // is Mountain
                        {
                            Row = Row + "B";

                        }
                        else
                        {
                           minPercent = maxPercent;
                           maxPercent = minPercent + Seed.Dessert;
                           if(isTile(genTile, minPercent, maxPercent))  // is Dessert
                           {
                               Row = Row + "x";

                           }
                           else
                           {
                               minPercent = maxPercent;
                               maxPercent = minPercent + Seed.Swamp;
                               if(isTile(genTile, minPercent, maxPercent))  // is Swamp
                               {
                                   Row = Row + "m";

                               }
                               else
                               {
                                   minPercent = maxPercent;
                                   maxPercent = minPercent + Seed.River;
                                   if(isTile(genTile, minPercent, maxPercent))  // is River
                                   {
                                       Row = Row + "s";

                                   }
                                   else
                                   {
                                       minPercent = maxPercent;
                                       maxPercent = minPercent + Seed.Sea;
                                       if(isTile(genTile, minPercent, maxPercent)) // is Sea
                                       {
                                           Row = Row + "S";

                                       }
                                       else
                                       {
                                           minPercent = maxPercent;
                                           maxPercent = minPercent + Seed.Lava;
                                           if(isTile(genTile, minPercent, maxPercent))  // is Lava
                                           {
                                               Row = Row + "l";

                                           }
                                           else
                                           {
                                               Row = Row + "X";                         // Unknown Tile;

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

} // get_Battlerow(Typo, Columns)

bool Battlemap::isTile(int Value, int Min, int Max)
{
/*
    #ifdef DEBUG
    Log("Tile: " << Value << " Min: " << Min << " Max: " << Max)
    #endif // DEBUG
*/
    if((Value >= Min) && (Value <= Max))
    {
        return true;
    }

    return false;

} // isTile

int Battlemap::generate_Random(const int Low, const int High)
{

    return rand() % High + Low;


} // generate_Random

#endif // BATTLEMAP_CPP
