#ifndef MAPINTERFACE_CPP
#define MAPINTERFACE_CPP

#include <allegro/system.h>
#include <allegro/gfx.h>
#include <vector>
#include <string>

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

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Mapinterface opened.")
    #endif // DEBUG

} // Mapinterface

Mapinterface::~Mapinterface()
{

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
            currMap.Sheet = nullptr;
            currMap.Index = 0;
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
        Tile.walkable = false;
        Tile.shipable = false;
        Tile.flyable = false;
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

void Mapinterface::convert_Tile(Tiledata &Tile, const char TChar)
{

    switch(TChar)
    {
    case 'g':
        {
            Tile.Index = currDatafile->find_Index("[WTI_Gras]").Number;
            Tile.walkable = true;
            Tile.flyable = true;
            Tile.shipable = false;
            break;
        } // Case 'G'

    case 'w':
        {
            Tile.Index = currDatafile->find_Index("[WTI_Shrubbery]").Number;
            Tile.walkable = true;
            Tile.flyable = true;
            Tile.shipable = false;
            break;

        } // Case 'S'

    case 'W':
        {
            Tile.Index = currDatafile->find_Index("[WTI_Forest]").Number;
            Tile.walkable = true;
            Tile.flyable = true;
            Tile.shipable = false;
            break;

        } // Case 'F'

    case 'n':
        {
            Tile.Index = currDatafile->find_Index("[WTI_Boulders]").Number;
            Tile.walkable = true;
            Tile.flyable = true;
            Tile.shipable = false;
            break;

        } // case 'B'

    case 'B':
        {
            Tile.Index = currDatafile->find_Index("[WTI_Mountain]").Number;
            Tile.walkable = false;
            Tile.flyable = true;
            Tile.shipable = false;
            break;

        } // case 'M'

    case 'x':
        {
            Tile.Index = currDatafile->find_Index("[WTI_Dessert]").Number;
            Tile.walkable = true;
            Tile.flyable = true;
            Tile.shipable = false;
            break;

        } // case 'D'

    case 'm':
        {
            Tile.Index = currDatafile->find_Index("[WTI_Swamp]").Number;
            Tile.walkable = true;
            Tile.flyable = true;
            Tile.shipable = false;
            break;

        } // case 'm'

    case 's':
        {
            Tile.Index = currDatafile->find_Index("[WTI_River]").Number;
            Tile.walkable = false;
            Tile.flyable = true;
            Tile.shipable = false;
            break;

        } // case 'w'

    case 'S':
        {
            Tile.Index = currDatafile->find_Index("[WTI_Sea]").Number;
            Tile.walkable = false;
            Tile.shipable = true;
            Tile.flyable = true;
            break;

        } // case 'W'

    case 'l':
        {
            Tile.Index = currDatafile->find_Index("[WTI_Lava]").Number;
            Tile.walkable = false;
            Tile.shipable = false;
            Tile.flyable = true;
            break;

        } // case 'l'

    case 'b':
        {
            Tile.Index = currDatafile->find_Index("[WTI_Bridge_horizontal]").Number;
            Tile.walkable = true;
            Tile.shipable = false;
            Tile.flyable = true;
            break;
        }

    case '#':
        {
            Tile.Index = currDatafile->find_Index("[WTI_Bridge_vertical]").Number;
            Tile.walkable = true;
            Tile.shipable = false;
            Tile.flyable = true;
            break;
        }

    default: // Unknown Tile
        {
            Tile.Index = currDatafile->find_Index("[WTI_Fog]").Number;
            Tile.walkable = false;
            Tile.shipable = false;
            Tile.flyable = false;
            break;

        } // default

    } // switch TChar

} // convert_Tile

void Mapinterface::convert_WorldmapCoords(int &Pos_x, int &Pos_y)
{
    currWorldmapclass->check_Coord(Pos_x, Pos_y);

} // convert_WorldmapCoords

#endif // MAPINTERFACE_CPP
