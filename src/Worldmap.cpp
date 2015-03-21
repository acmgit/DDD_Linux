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
        Columns = Maprow.length();          // Len of the String is the Width of the Map

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

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Tile: " << Tile << " at Pos_x: " << Pos_x << " Pos_y: " << Pos_y)
    #endif // DEBUG

    return Tile;

} // get_Tile

int Worldmap::get_Columns()
{
    return Columns;

} // get_Columns

int Worldmap::get_Rows()
{
    return Rows;

} // get_Rows

#endif // WORLDMAP_CPP
