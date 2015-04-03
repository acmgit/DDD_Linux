#ifndef TREASUREMAP_CPP
#define TREASUREMAP_CPP

#include "Treasuremap.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <allegro/system.h>

#ifdef DEBUG
#include "Logfile.h"
#endif // DEBUG

Treasuremap::Treasuremap(const std::string &Filename)
{

    load_Map(Filename);

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Treasuremapclass opened.")
    #endif // DEBUG


} // Treasuermap

Treasuremap::~Treasuremap()
{
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Treasuremapclass closed.")
    #endif // DEBUG

} // ~Treasuermap

void Treasuremap::load_Map(const std::string &Mapname)
{
    std::ifstream File(Mapname.c_str());

    if(File.is_open())
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") <" << Mapname.c_str() << "> opened.")
        #endif // DEBUG

        Treasure Entry;
        std::string Line;

        while(File.good())
        {
            std::getline(File, Line);

            if((Line.find("[") != Line.npos) && (Line.find("]") != Line.npos))
            {

                Entry.Keyname = Line;

                // get Pos_x
                std::getline(File, Line);
                int Val;

                // convert String to Int
                std::stringstream Valstring;
                Valstring << Line;
                Valstring >> Val;
                Valstring.clear();              // prepare for the next Value

                Entry.Pos_x = Val;


                // get Pos_y
                std::getline(File, Line);

                // convert String to Int
                Valstring << Line;
                Valstring >> Val;
                Valstring.clear();             // prepare for the next Value

                Entry.Pos_y = Val;

                // get Name
                std::getline(File, Line);
                Entry.Treasurename = Line;

                // get Availabitlity
                std::getline(File, Line);

                // convert String to Int
                Valstring << Line;
                Valstring >> Val;
                Valstring.clear();

                Entry.available = Val;

                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Treasurentry loaded:")
                Log("Keyname: " << Entry.Keyname.c_str())
                Log("Pos X: " << Entry.Pos_x)
                Log("Pos Y: " << Entry.Pos_y)
                Log("Name: " << Entry.Treasurename.c_str())
                Log("available: " << Entry.available)
                #endif // DEBUG

                Secret.push_back(Entry);             // Store the City in the Array

            } // if Line.find

        } // while File.good

        File.close();
        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") <" << Mapname.c_str() << "> closed.")
        #endif // DEBUG
    }
    else
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.FILE_NOT_FOUND << ") Treasuremapfile <" << Mapname.c_str() << "> not found.")
        #endif // DEBUG

        allegro_message("Treasuremapfile not found.");
        //allegro_exit();

    } // if File.open

} // load_Map

std::string Treasuremap::find_Secret(const int &Position_x, const int &Position_y)
{

    #ifdef DEBUG
    Log("Searching at Pos_x: " << Position_x << " Pos_y: " << Position_y)
    #endif // DEBUG

    std::vector<Treasure>::iterator Treasureiterator;
    std::string Treasurename;

    Treasurename.clear();

    for(Treasureiterator = Secret.begin(); Treasureiterator != Secret.end(); ++Treasureiterator)
    {
        if( ( (*Treasureiterator).Pos_x == Position_x) && ( (*Treasureiterator).Pos_y == Position_y) )
        {
            #ifdef DEBUG
            Log("Treasure <" << (*Treasureiterator).Treasurename.c_str() << "> found.")
            #endif // DEBUG

            if( (*Treasureiterator).available > 0)
            {
                (*Treasureiterator).available = 0;
                Treasurename = (*Treasureiterator).Treasurename;

            }
            else
            {
                if( (*Treasureiterator).available < 0)
                {
                    Treasurename = (*Treasureiterator).Treasurename;

                } // if available < 0 (infinity)

            } // if available > 0

        } // if Pos_x && Pos_y

    } // for Treasureiterator

    return Treasurename;

} // find_Secret()

#endif // TREASUREMAP_CPP
