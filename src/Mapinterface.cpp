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

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Mapinterface closed.")
    #endif // DEBUG
} // ~Mapinterface

Mapinterface::Tiledata Mapinterface::getTile(Tiletyp Map, const int Column, const int Row)
{
    Tiledata currMap;

    switch(Map)
    {
        case Tiletyp::Battlemaptile:
        {
            getBattlemapTile(currMap, Column, Row);
            break;

        } // case Battlemaptile

        case Tiletyp::Townmaptile:
        {

            break;

        } // case Townmaptile

        case Tiletyp::Worldmaptile:
        {

            break;

        } // case Worldmaptile

        default:
        {

            break;

        } // default

    } // switch Map

    return currMap;

} // getTile

void Mapinterface::generateBattlemap(const std::string Battletyp)
{
    int Rows = currDatafile->findIndex("[INI_Playfieldrows]").Number;
    int Columns = currDatafile->findIndex("[INI_Playfieldcolumns]").Number;
    std::string Battlerow;

    for(int Row = 0; Row < Rows; ++Row)
    {
        Battlerow = currBattlemapclass->getBattlerow(Battletyp, Columns);
        currBattlemap.push_back(Battlerow);

    } // for Row

    validBattlemap = true;
} // generateBattlemap

void Mapinterface::destroyBattlemap()
{
    currBattlemap.clear();
    validBattlemap = false;

} // destroyBattlemap

bool Mapinterface::getBattlemapstatus()
{
    return validBattlemap;

} // getBattlemapstatus

void Mapinterface::getBattlemapTile(Tiledata &Tile, const int Column, const int Row)
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

    } // if !validbattlemap

    Tile.Sheet = currDatafile->getBitmap("[SHE_Worldtile]");

    std::string cRow = currBattlemap.at(Row);
    char cColumn = (char) cRow.at(Column);

    switch(cColumn)
    {
    case 'G':
        {
            Tile.Index = currDatafile->findIndex("[WTI_Gras]").Number;
            Tile.walkable = true;
            Tile.flyable = true;
            Tile.shipable = false;
            break;
        } // Case 'G'

    case 'S':
        {
            Tile.Index = currDatafile->findIndex("[WTI_Shrubbery]").Number;
            Tile.walkable = true;
            Tile.flyable = true;
            Tile.shipable = false;
            break;

        } // Case 'S'

    case 'F':
        {
            Tile.Index = currDatafile->findIndex("[WTI_Forest]").Number;
            Tile.walkable = true;
            Tile.flyable = true;
            Tile.shipable = false;
            break;

        } // Case 'F'

    case 'B':
        {
            Tile.Index = currDatafile->findIndex("[WTI_Boulder]").Number;
            Tile.walkable = true;
            Tile.flyable = true;
            Tile.shipable = false;
            break;

        } // case 'B'

    case 'M':
        {
            Tile.Index = currDatafile->findIndex("[WTI_Mountain]").Number;
            Tile.walkable = false;
            Tile.flyable = true;
            Tile.shipable = false;
            break;

        } // case 'M'

    case 'D':
        {
            Tile.Index = currDatafile->findIndex("[WTI_Dessert]").Number;
            Tile.walkable = true;
            Tile.flyable = true;
            Tile.shipable = false;
            break;

        } // case 'D'

    case 'm':
        {
            Tile.Index = currDatafile->findIndex("[WTI_Swamp]").Number;
            Tile.walkable = true;
            Tile.flyable = true;
            Tile.shipable = false;
            break;

        } // case 'm'

    case 'w':
        {
            Tile.Index = currDatafile->findIndex("[WTI_River]").Number;
            Tile.walkable = false;
            Tile.flyable = true;
            Tile.shipable = false;
            break;

        } // case 'w'

    case 'W':
        {
            Tile.Index = currDatafile->findIndex("[WTI_Sea]").Number;
            Tile.walkable = false;
            Tile.shipable = true;
            Tile.flyable = true;
            break;

        } // case 'W'

    case 'l':
        {
            Tile.Index = currDatafile->findIndex("[WTI_Lava]").Number;
            Tile.walkable = false;
            Tile.shipable = false;
            Tile.flyable = true;
            break;

        } // case 'l'

    default: // Unknown Tile
        {
            Tile.Index = -1;
            Tile.walkable = false;
            Tile.shipable = false;
            Tile.flyable = false;
            break;

        } // default

    } // switch cColumn

} // getBattlemapTile
#endif // MAPINTERFACE_CPP
