#ifndef TOWNSMAP_CPP
#define TOWNSMAP_CPP

#include <allegro/system.h>

#include "Townsmap.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#ifdef DEBUG
#include "Logfile.h"
#endif // DEBUG

Townsmap::Townsmap(const std::string &Filename)
{
    load_Map(Filename);

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Townsmapclass opened.")
    #endif // DEBUG

} // Townsmap

Townsmap::~Townsmap()
{
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Townsmapclass closed.")
    #endif // DEBUG

} // ~Townsmap

void Townsmap::load_Map(const std::string &Mapname)
{
    std::ifstream File(Mapname.c_str());

    if(File.is_open())
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") <" << Mapname.c_str() << "> opened.")
        #endif // DEBUG

        Enter Entry;
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
                Entry.Name = Line;

                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Cityentry loaded:")
                Log("Keyname: " << Entry.Keyname.c_str())
                Log("Pos X: " << Entry.Pos_x)
                Log("Pos Y: " << Entry.Pos_y)
                Log("Name: " << Entry.Name.c_str())
                #endif // DEBUG

                Citys.push_back(Entry);             // Store the City in the Array

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
        Log("(" << ErrorLog.FILE_NOT_FOUND << ") Townmapfile <" << Mapname.c_str() << "> not found.")
        #endif // DEBUG

        allegro_message("Townsmapfile not found.");
        //allegro_exit();

    } // if File.open

} // load_Map

std::string Townsmap::find_Town(const int &Position_x, const int &Position_y)
{
    std::vector<Enter>::iterator Cityiterator;
    std::string Townname;

    Townname.clear();

    for(Cityiterator = Citys.begin(); Cityiterator != Citys.end(); ++Cityiterator)
    {
        if( ( (*Cityiterator).Pos_x == Position_x) && ( (*Cityiterator).Pos_y == Position_y) )
        {
            #ifdef DEBUG
            Log("Town <" << (*Cityiterator).Name.c_str() << "> found.")
            #endif // DEBUG

            Townname = (*Cityiterator).Name;

        } // if Pos_x && Pos_y

    } // for Cityiterator

    return Townname;
}
#endif
