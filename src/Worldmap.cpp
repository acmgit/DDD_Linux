#ifndef WORLDMAP_CPP
#define WORLDMAP_CPP

#include <string>
#include <iostream>
#include <fstream>

#include <allegro/system.h>

#include "Worldmap.h"

#ifdef DEBUG
#include "Logfile.h"
#endif // DEBUG

Worldmap::Worldmap(const std::string &Worldmapname)
{
    read_Map(Worldmapname);

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Worldmapclass opened.")
    #endif // DEBUG

} // Worldmap()

Worldmap::~Worldmap()
{
    Map.clear();

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Worldmapclass closed.")
    #endif // DEBUG

} // ~Worldmap()

void Worldmap::read_Map(const std::string &Mapname)
{

    #ifdef DEBUG
    Log("Open Worldmapfile: " << Mapname.c_str())
    #endif // DEBUG

    int Row = 0;

    std::ifstream File(Mapname);
    std::string Maprow;

    if(File.is_open())
    {
        while(File.good())
        {
            std::getline(File, Maprow);
            Map.push_back(Maprow);
            ++Row;
        } // while File.good

        Rows = Row - 1;                     // we begin to count at 0
        Columns = Maprow.length() - 1;      // Len of the String is the Width of the Map

        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") Worldmapfile readed: Rows = " << Rows << " Columns = " << Columns)
        #endif // DEBUG

        File.close();

    }
    else
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.FILE_NOT_FOUND << ") Couldn't open File: " << Mapname.c_str())
        #endif // DEBUG

        Rows = 0;
        Columns = 0;
        allegro_message("Couldn't open Worldmapfile.");

    } // if File.is_open


} // read_Map

char Worldmap::get_Tile(const int Pos_x, const int Pos_y)
{
    char Tile;
    if((Pos_x < 0) || (Pos_x > Columns))
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.ILLEGAL_ACCESS << ") Illegal Worldtile at Pos_x: " << Pos_x)
        #endif // DEBUG

        Tile = ' ';
        return Tile;

    } // if Pos_x

    if((Pos_y < 0) || (Pos_y > Rows))
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.ILLEGAL_ACCESS << ") Illegal Worldtile at Pos_y: " << Pos_y)
        #endif // DEBUG

        Tile = ' ';
        return Tile;

    } // if Pos_y

    Tile = Map.at(Pos_y).at(Pos_x);

    /*
    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Tile: " << Tile << " at Pos_x: " << Pos_x << " Pos_y: " << Pos_y)
    #endif // DEBUG
    */

    return Tile;

} // get_Tile

void Worldmap::check_Coord(int &Pos_x, int &Pos_y)
{
    if(Pos_x < 0)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") Convert Pos_x from: " << Pos_x << " to " << (Columns + (Pos_x + 1)) << ".")
        #endif // DEBUG

        Pos_x = Columns + (Pos_x + 1);

    } // if Pos_x < 0

    if(Pos_x > Columns)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") Convert Pos_x from: " << Pos_x << " to " << ((Pos_x - 1) - Columns) << ".")
        #endif // DEBUG

        Pos_x = (Pos_x - 1) - Columns;

    } // if Pos_x > Columns

    if(Pos_y < 0)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") Convert Pos_y from: " << Pos_y << " to " << (Rows + (Pos_y + 1)) << ".")
        #endif // DEBUG

        Pos_y = Rows + (Pos_y + 1);

    } // if Pos_y < 0

    if(Pos_y > Rows)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") Convert Pos_y from: " << Pos_y << " to " << ((Pos_y - 1) - Rows) << ".")
        #endif // DEBUG

        Pos_y = (Pos_y - 1) - Rows;

    } // if Pos_y > Columns

} // check_Coord

int Worldmap::get_Columns()
{
    return Columns;

} // get_Columns

int Worldmap::get_Rows()
{
    return Rows;

} // get_Rows

#endif // WORLDMAP_CPP
