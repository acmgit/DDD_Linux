#ifndef MAPINTERFACE_CPP
#define MAPINTERFACE_CPP

#include <allegro/system.h>
#include <allegro/gfx.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Mapinterface.h"
#include "Battlemap.h"
#include "Allegro_Datafile.h"

#ifdef DEBUG
#include "Logfile.h"
#endif // DEBUG

Mapinterface::Mapinterface(Allegro_Datafile *Data)
{
    currDatafile = Data;

    currBattlemapclass = new Battlemap(currDatafile);
    if(!currBattlemapclass)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't open Battlemapclass.")
        #endif // DEBUG
        allegro_message("Couldn't open Battlemapclass.");
        allegro_exit();

    } // if !currBattlemap

    validBattlemap = false;

    currWorldmapclass = new Worldmap("data/DDD_Map.txt");
    if(!currWorldmapclass)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't open Worldmapclass.")
        #endif // DEBUG

        allegro_message("Couldn't open Worldmapclass.");
        allegro_exit();

    } // if !currWorldmapclass

    currTownsclass = new Townsmap("data/DDD_Towns.idx");

    if(!currTownsclass)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't open Townsmapclass.")
        #endif // DEBUG

        allegro_message("Couldn't open Townsmapclass.");
        allegro_exit();

    } // if !currWorldmapclass

    currTreasures = new Treasuremap("data/DDD_Treasures.idx");

    if(!currTreasures)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Couldn't open Treasuremapclass.")
        #endif // DEBUG

        allegro_message("Couldn't open Treasuremapclass.");
        allegro_exit();

    } // if !currWorldmapclass

    load_Tiles("data/DDD_Tiledata.txt");

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Mapinterface opened.")
    #endif // DEBUG

} // Mapinterface

Mapinterface::~Mapinterface()
{

    if(currTreasures)
    {
        delete currTreasures;
        currTreasures = nullptr;

    } // if currTreasures

    if(currTownsclass)
    {
        delete currTownsclass;
        currTownsclass = nullptr;

    } // if currTownsclass

    if(currWorldmapclass)
    {
        delete currWorldmapclass;
        currWorldmapclass = nullptr;

    } // if currWorldmapclass

    if(currBattlemapclass)
    {
        delete currBattlemapclass;
        currBattlemapclass = nullptr;

    } // if currBattlemap

    destroy_Battlemap();

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Mapinterface closed.")
    #endif // DEBUG
} // ~Mapinterface

Mapinterface::Tiledata Mapinterface::get_Tile(Tiletyp Map, const int Column, const int Row)
{
    Tiledata currMap;

    switch(Map)
    {
        case Tiletyp::Battlemaptile:
        {
            get_BattlemapTile(currMap, Column, Row);
            break;

        } // case Battlemaptile

        case Tiletyp::Townmaptile:
        {
            get_TownTile(currMap, Column, Row);
            break;

        } // case Townmaptile

        case Tiletyp::Worldmaptile:
        {
            get_WorldmapTile(currMap, Column, Row);
            break;

        } // case Worldmaptile

        case Tiletyp::Treasuremaptile:
        {
            currMap.Sheet = nullptr;
            currMap.Index = 0;
            break;

        } // case Treasuremaptile

        default:
        {
            currMap.Sheet = nullptr;
            currMap.Index = 0;
            break;

        } // default

    } // switch Map

    return currMap;

} // get_Tile

void Mapinterface::generate_Battlemap(const std::string &Battletyp)
{
    int Rows = currDatafile->find_Index("[INI_Playfieldrows]").Number;
    int Columns = currDatafile->find_Index("[INI_Playfieldcolumns]").Number;
    std::string Battlerow;

    for(int Row = 0; Row < Rows; ++Row)
    {
        Battlerow = currBattlemapclass->get_Battlerow(Battletyp, Columns);
        currBattlemap.push_back(Battlerow);

    } // for Row

    validBattlemap = true;

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Battlemap generated.")
    #endif // DEBUG

} // generate_Battlemap

void Mapinterface::destroy_Battlemap()
{
    if(validBattlemap)
    {
        currBattlemap.clear();
        validBattlemap = false;

        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") Battlemap destroyed.")
        #endif // DEBUG

    } // if validBattlemap

} // destroy_Battlemap

bool Mapinterface::get_Battlemapstatus()
{
    return validBattlemap;

} // get_Battlemapstatus

void Mapinterface::get_BattlemapTile(Tiledata &Tile, const int Column, const int Row)
{
    if(!validBattlemap)
    {
        Tile.Sheet = nullptr;               // No Battlemap generated
        Tile.Index = 0;
        //Tile.walkable = false;
        //Tile.shipable = false;
        //Tile.flyable = false;
        #ifdef DEBUG
        Log("(" << ErrorLog.ILLEGAL_ACCESS << ") No Battlemap generated.")
        #endif // DEBUG

    } // if !validBattlemap
    else
    {
        Tile.Sheet = currDatafile->get_Bitmap("[SHE_Worldtile]");

        std::string cRow = currBattlemap.at(Row);
        char cColumn = (char) cRow.at(Column);

        convert_Tile(Tile, cColumn);
    } // if else !validBattlemap

} // get_BattlemapTile

void Mapinterface::get_WorldmapTile(Tiledata &Tile, const int Column, const int Row)
{
    int curr_Column = Column;
    int curr_Row = Row;
    convert_WorldmapCoords(curr_Column, curr_Row);

    Tile.Sheet = currDatafile->get_Bitmap("[SHE_Worldtile]");
    char cTile = currWorldmapclass->get_Tile(curr_Column, curr_Row);

    convert_Tile(Tile, cTile);

} // get_WorldmapTile

void Mapinterface::get_TownTile(Tiledata &Tile, const int Column, const int Row)
{
    int curr_Column = Column;
    int curr_Row = Row;
    convert_WorldmapCoords(curr_Column, curr_Row);

    Tile.Sheet = currDatafile->get_Bitmap("[SHE_Towntile]");
    std::string Town = currTownsclass->find_Town(curr_Column, curr_Row);

    Town = "[TWN_" + Town + "]";
    Tile.Index = currDatafile->find_Index(Town).Number;
    //Tile.flyable = true;
    //Tile.shipable = false;
    //Tile.walkable = true;

} // get_Towntile

void Mapinterface::convert_Tile(Tiledata &Tile, const char TChar)
{

    std::map<char, Tilecheck>::iterator Entry;

    Entry = Tiles.find(TChar);

    if(Entry != Tiles.end())
    {
        Tile.Index = currDatafile->find_Index((*Entry).second.Keyname).Number;

    }
    else
    {
        // Unknown Tile
        Tile.Index = currDatafile->find_Index("[WTI_Fog]").Number;

    } // if(Entry)

} // convert_Tile

void Mapinterface::convert_WorldmapCoords(int &Pos_x, int &Pos_y)
{
    currWorldmapclass->check_Coord(Pos_x, Pos_y);

} // convert_WorldmapCoords

std::string Mapinterface::check_Town(const int Column, const int Row)
{
    int curr_Column = Column;
    int curr_Row = Row;
    convert_WorldmapCoords(curr_Column, curr_Row);

    return currTownsclass->find_Town(curr_Column, curr_Row);

} // get_Town

std::string Mapinterface::find_Treasure(const int Column, const int Row)
{
    int curr_Column = Column;
    int curr_Row = Row;
    convert_WorldmapCoords(curr_Column, curr_Row);

    return currTreasures->find_Secret(curr_Column, curr_Row);

} // find_Treasure

void Mapinterface::load_Tiles(std::string Filename)
{
    std::ifstream File(Filename.c_str());

    if(File.is_open())
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") <" << Filename.c_str() << "> opened.")
        #endif // DEBUG

        Tilecheck Entry;
        std::string Line;

        while(File.good())
        {
            std::getline(File, Line);

            if((Line.find("[") != Line.npos) && (Line.find("]") != Line.npos))
            {
                // get Keyname
                Entry.Keyname = Line;

                // get Char
                std::getline(File, Line);

                Entry.Rawtile = (char) Line.at(0);

                // get walkable
                std::getline(File, Line);
                Entry.walkable = convert_Bool(Line);

                // get shipable
                std::getline(File, Line);
                Entry.shipable = convert_Bool(Line);


                // get flyable
                std::getline(File, Line);
                Entry.flyable = convert_Bool(Line);

                // get poison
                std::getline(File, Line);
                Entry.poison = convert_Bool(Line);

                // get danger
                std::getline(File, Line);
                Entry.danger = convert_Bool(Line);

                // get secret
                std::getline(File, Line);
                Entry.secret = convert_Bool(Line);

                #ifdef DEBUG
                Log("(" << ErrorLog.ALLOK << ") Tileentry loaded:")
                Log("Keyname: " << Entry.Keyname.c_str())
                Log("Rawtile: " << Entry.Rawtile)
                Log("walkable: " << Entry.walkable)
                Log("shipable: " << Entry.shipable)
                Log("flyable: " << Entry.flyable)
                Log("poison: " << Entry.poison)
                Log("danger: " << Entry.danger)
                Log("secret: " << Entry.secret)
                #endif // DEBUG

                // Stores the Entry
                Tiles.insert(std::pair<char, Tilecheck>(Entry.Rawtile, Entry));

            } // if Line.find

        } // while File.good

        File.close();
        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") <" << Filename.c_str() << "> closed.")
        #endif // DEBUG
    }
    else
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.FILE_NOT_FOUND << ") Tiledatafile <" << Filename.c_str() << "> not found.")
        #endif // DEBUG

        allegro_message("Tiledatafile not found.");
        //allegro_exit();

    } // if File.open

} // load_Tiles

bool Mapinterface::convert_Bool(std::string &Valuestring)
{

    int Val;
    std::stringstream Valstring;

    // convert String to Int
    Valstring << Valuestring;
    Valstring >> Val;

    if(Val > 0)
    {
        return true;

    }
    else
    {
        return false;

    } // if Val

} // convertBool

Mapinterface::Tilecheck Mapinterface::get_Tilecheck(Tiletyp Map, const int &Pos_x, const int &Pos_y)
{
    Tilecheck currTile;

    currTile.Keyname = "[WTI_Fog]";
    currTile.walkable = false;
    currTile.shipable = false;
    currTile.flyable = false;
    currTile.danger = false;
    currTile.poison = false;
    currTile.secret = false;

    int curr_Pos_x = Pos_x;
    int curr_Pos_y = Pos_y;
    char Chartile;
    std::map<char, Tilecheck>::iterator Entry;

    switch(Map)
    {
        case(Worldmaptile):
        {
            convert_WorldmapCoords(curr_Pos_x, curr_Pos_y);
            Chartile = currWorldmapclass->get_Tile(curr_Pos_x, curr_Pos_y);
            Entry = Tiles.find(Chartile);
            if(Entry != Tiles.end())
            {
                currTile.Keyname = (*Entry).second.Keyname;
                currTile.Rawtile = (*Entry).second.Rawtile;
                currTile.walkable = (*Entry).second.walkable;
                currTile.shipable = (*Entry).second.shipable;
                currTile.flyable = (*Entry).second.flyable;
                currTile.poison = (*Entry).second.poison;
                currTile.danger = (*Entry).second.danger;
                currTile.secret = (*Entry).second.secret;

            } // if(Entry != end)

            break;

        } // case Worldmaptile

        case(Battlemaptile):
        {
            break;

        } // case Battlemaptile

        case(Townmaptile):
        {
            break;

        } // case Townmaptile

        default:
        {
            break;
        } // case default

    } // switch(Map)

    return currTile;

} // get_Tilecheck
#endif // MAPINTERFACE_CPP
