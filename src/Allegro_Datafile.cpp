#include "Allegro_Datafile.h"
#include <allegro/system.h>

#ifdef DEBUG
#include "Logfile.h"
#include <allegro/system.h>
#include <allegro/graphics.h>

#endif // DEBUG
#include <string>
#include <map>

Allegro_Datafile::Allegro_Datafile(const std::string File)
{

#ifdef DEBUG
    Log("Loading " << File.c_str() << ".")
#endif // DEBUG

    Data = load_datafile(File.c_str());
    if(!Data)
    {
        std::string DataError = "Could not load <";
        DataError = DataError + File;
        DataError = DataError + ">.";

#ifdef DEBUG
        Log("(" << ErrorLog.FILE_NOT_FOUND << ") " << DataError.c_str())
#endif // DEBUG

        allegro_message(DataError.c_str());
        allegro_exit();

    } // if !Pictures

    Filename = File;

    generateIndex();

} // Datafile

Allegro_Datafile::~Allegro_Datafile()
{
    unload_datafile(Data);

} // ~Datafile

const std::string Allegro_Datafile::getFilename()
{
    return Filename;

} // getFilename

DATAFILE* Allegro_Datafile::getDatafile()
{
    return Data;

}

void Allegro_Datafile::addIndex(Index newEntry)
{
    Dataindex.insert(std::pair<std::string, int>(newEntry.Name, newEntry.Number));

} // addIndex

void Allegro_Datafile::removeIndex(Index Entry)
{
    std::map<std::string, int>::iterator delEntry;
    delEntry = Dataindex.find(Entry.Name);

    if(delEntry != Dataindex.end())
    {
        //*delEntry.erase();
    } // if delEntry != end()

} // removeIndex

Allegro_Datafile::Index Allegro_Datafile::findIndex(std::string Keyname)
{
    std::map<std::string, int>::iterator Entry;
    Entry = Dataindex.find(Keyname);
    Index foundEntry;

    if(Entry != Dataindex.end())
    {
        foundEntry.Name = (*Entry).first;
        foundEntry.Number = (*Entry).second;

    } // if delEntry != end()

    return foundEntry;

} // findIndex

void Allegro_Datafile::generateIndex()
{
/* Index for the Sheets in DDD
    -------------------------------------------------
*/
    Index MyIndex;
    int Tilewidth = 32;

    MyIndex.Name = "SHE_Font";
    MyIndex.Number = 0;
    addIndex(MyIndex);

    MyIndex.Name = "SHE_Frame";
    MyIndex.Number = 1;
    addIndex(MyIndex);

    MyIndex.Name = "SHE_Hero";
    MyIndex.Number = 2;
    addIndex(MyIndex);

    MyIndex.Name = "SHE_Logo";
    MyIndex.Number = 3;
    addIndex(MyIndex);

    MyIndex.Name = "SHE_Towntiles";
    MyIndex.Number = 4;
    addIndex(MyIndex);

    MyIndex.Name = "SHE_Worldtiles";
    MyIndex.Number = 5;
    addIndex(MyIndex);

    MyIndex.Name = "SHE_Worldenemys";
    MyIndex.Number = 6;
    addIndex(MyIndex);

/*  Index of Colors in DDD
    -------------------------------------------------
*/
    MyIndex.Name = "COL_red";
    MyIndex.Number = makecol(255,  50,    50);
    addIndex(MyIndex);

    MyIndex.Name = "COL_orange";
    MyIndex.Number = makecol(255,  100,    0);
    addIndex(MyIndex);

    MyIndex.Name = "COL_blue";
    MyIndex.Number = makecol(50,   50,   255);
    addIndex(MyIndex);

    MyIndex.Name = "COL_purple";
    MyIndex.Number = makecol(255,  50,   255);
    addIndex(MyIndex);

    MyIndex.Name = "COL_green";
    MyIndex.Number = makecol(50,   255,   50);
    addIndex(MyIndex);

    MyIndex.Name = "COL_cyan";
    MyIndex.Number = makecol(50,   255,  255);
    addIndex(MyIndex);

    MyIndex.Name = "COL_yellow";
    MyIndex.Number = makecol(255,  255,   50);
    addIndex(MyIndex);

    MyIndex.Name = "COL_gold";
    MyIndex.Number = makecol(255,  200,   50);
    addIndex(MyIndex);

    MyIndex.Name = "COL_brown";
    MyIndex.Number = makecol(200,  100,    0);
    addIndex(MyIndex);

    MyIndex.Name = "COL_white";
    MyIndex.Number = makecol(250,  250,  250);
    addIndex(MyIndex);

    MyIndex.Name = "COL_lightgrey";
    MyIndex.Number = makecol(200,  200,  200);
    addIndex(MyIndex);

    MyIndex.Name = "COL_silver";
    MyIndex.Number = makecol(150,  150,  150);
    addIndex(MyIndex);

    MyIndex.Name = "COL_darkgrey";
    MyIndex.Number = makecol(100,  100,  100);
    addIndex(MyIndex);

    MyIndex.Name = "COL_black";
    MyIndex.Number = makecol(0,    0,    0);
    addIndex(MyIndex);

    MyIndex.Name = "COL_transparent";
    MyIndex.Number = -1;
    addIndex(MyIndex);

/*  Index of Enemytiles on the Worldenemyspritesheet
    -------------------------------------------------
*/
    // Goblin
    MyIndex.Name = "WEN_Goblin";
    MyIndex.Number = 0;
    addIndex(MyIndex);

    // Zombie
    MyIndex.Name = "WEN_Zombie";
    MyIndex.Number = Tilewidth;
    addIndex(MyIndex);

    // Räuber
    MyIndex.Name = "WEN_Bandit";
    MyIndex.Number = 2 * Tilewidth;
    addIndex(MyIndex);

    // Wassermann
    MyIndex.Name = "WEN_Aquarius";
    MyIndex.Number = 3 * Tilewidth;
    addIndex(MyIndex);

    // Sandviper
    MyIndex.Name = "WEN_Sandviper";
    MyIndex.Number = 4 * Tilewidth;
    addIndex(MyIndex);

    // Ork
    MyIndex.Name = "WEN_Orc";
    MyIndex.Number = 5 * Tilewidth;
    addIndex(MyIndex);

    // Skelett
    MyIndex.Name = "WEN_Skeleton";
    MyIndex.Number = 6 * Tilewidth;
    addIndex(MyIndex);

    // Pirat
    MyIndex.Name = "WEN_Pirate";
    MyIndex.Number = 7 * Tilewidth;
    addIndex(MyIndex);

    // Nesselbaum
    MyIndex.Name = "WEN_Hackberry";
    MyIndex.Number = 8 * Tilewidth;
    addIndex(MyIndex);

    // Wildpferd
    MyIndex.Name = "WEN_Wildhorse";
    MyIndex.Number = 9 * Tilewidth;
    addIndex(MyIndex);

    // Seepferd
    MyIndex.Name = "WEN_Seahorse";
    MyIndex.Number = 10 * Tilewidth;
    addIndex(MyIndex);

    // Ghul
    MyIndex.Name = "WEN_Ghoul";
    MyIndex.Number = 11 * Tilewidth;
    addIndex(MyIndex);

    // Waldschrat
    MyIndex.Name = "WEN_Forestdemon";
    MyIndex.Number = 12 * Tilewidth;
    addIndex(MyIndex);

    // Einhorn
    MyIndex.Name = "WEN_Wildunicorn";
    MyIndex.Number = 13 * Tilewidth;
    addIndex(MyIndex);

    // Oger
    MyIndex.Name = "WEN_Ogre";
    MyIndex.Number = 14 * Tilewidth;
    addIndex(MyIndex);

    // Auerochse
    MyIndex.Name = "WEN_Aurochs";
    MyIndex.Number = 15 * Tilewidth;
    addIndex(MyIndex);

    // Vampir
    MyIndex.Name = "WEN_Vampire";
    MyIndex.Number = 16 * Tilewidth;
    addIndex(MyIndex);

    // Troll (Brückentroll)
    MyIndex.Name = "WEN_Troll";
    MyIndex.Number = 17 * Tilewidth;
    addIndex(MyIndex);

    // Seeschlange
    MyIndex.Name = "WEN_Seaserpent";
    MyIndex.Number = 18 * Tilewidth;
    addIndex(MyIndex);

    // Riesenpython
    MyIndex.Name = "WEN_Giantpython";
    MyIndex.Number = 19 * Tilewidth;
    addIndex(MyIndex);

    // Werwolf
    MyIndex.Name = "WEN_Werewolf";
    MyIndex.Number = 20 * Tilewidth;
    addIndex(MyIndex);

    // Höhlenspinne
    MyIndex.Name = "WEN_Raftspider";
    MyIndex.Number = 21 * Tilewidth;
    addIndex(MyIndex);

    // Mumie
    MyIndex.Name = "WEN_Mummy";
    MyIndex.Number = 22 * Tilewidth;
    addIndex(MyIndex);

    // Riesenkrake
    MyIndex.Name = "WEN_Giantoctopus";
    MyIndex.Number = 23 * Tilewidth;
    addIndex(MyIndex);

    // Höhlenschrat
    MyIndex.Name = "WEN_Cavedemon";
    MyIndex.Number = 24 * Tilewidth;
    addIndex(MyIndex);

    // Feuerechse
    MyIndex.Name = "WEN_Firelizard";
    MyIndex.Number = 25 * Tilewidth;
    addIndex(MyIndex);

    // Zweihaupt
    MyIndex.Name = "WEN_Doublehead";
    MyIndex.Number = 26 * Tilewidth;
    addIndex(MyIndex);

    // Zauberer
    MyIndex.Name = "WEN_Wizard";
    MyIndex.Number = 27 * Tilewidth;
    addIndex(MyIndex);

    // Dämon
    MyIndex.Name = "WEN_Demon";
    MyIndex.Number = 28 * Tilewidth;
    addIndex(MyIndex);

    // Speihkobra
    MyIndex.Name = "WEN_Spittincobra";
    MyIndex.Number = 29 * Tilewidth;
    addIndex(MyIndex);

    // Höhlenspinne
    MyIndex.Name = "WEN_Scaffoldwebspider";
    MyIndex.Number = 30 * Tilewidth;
    addIndex(MyIndex);

    // Riesenaffe
    MyIndex.Name = "WEN_Giantape";
    MyIndex.Number = 31 * Tilewidth;
    addIndex(MyIndex);

    // Jungdrache
    MyIndex.Name = "WEN_Youngdragon";
    MyIndex.Number = 32 * Tilewidth;
    addIndex(MyIndex);

    // Zyklop
    MyIndex.Name = "WEN_Cyclops";
    MyIndex.Number = 33 * Tilewidth;
    addIndex(MyIndex);

    // Balrog
    MyIndex.Name = "WEN_Balrog";
    MyIndex.Number = 34 * Tilewidth;
    addIndex(MyIndex);

    // Hydra
    MyIndex.Name = "WEN_Hydra";
    MyIndex.Number = 35 * Tilewidth;
    addIndex(MyIndex);

    // Riese
    MyIndex.Name = "WEN_Giant";
    MyIndex.Number = 36 * Tilewidth;
    addIndex(MyIndex);

    // Drache
    MyIndex.Name = "WEN_Wilddragon";
    MyIndex.Number = 37 * Tilewidth;
    addIndex(MyIndex);

    // Totes Monster
    MyIndex.Name = "WEN_Deadenemy";
    MyIndex.Number = 38 * Tilewidth;
    addIndex(MyIndex);

/*  Index of Herotiles on the Herospritesheet
    -------------------------------------------------
*/

    // Held nur mit Einhandwaffe
    MyIndex.Name = "HER_Sword";
    MyIndex.Number = 0;
    addIndex(MyIndex);

    // Held mit Einhandwaffe und Schild
    MyIndex.Name = "HER_Shield";
    MyIndex.Number = Tilewidth;
    addIndex(MyIndex);

    // Held nur mit Einhandwaffe (vergiftet)
    MyIndex.Name = "HER_Sword_poisoned";
    MyIndex.Number = 2 * Tilewidth;
    addIndex(MyIndex);

    // Held mit Einhandwaffe und Schild (vergiftet)
    MyIndex.Name = "HER_Shield_poisoned";
    MyIndex.Number = 3 * Tilewidth;
    addIndex(MyIndex);

    // Held auf Pferd
    MyIndex.Name = "HER_on_Horse";
    MyIndex.Number = 4 * Tilewidth;
    addIndex(MyIndex);

    // Held auf Einhorn
    MyIndex.Name = "HER_on_Unicorn";
    MyIndex.Number = 5 * Tilewidth;
    addIndex(MyIndex);

    // Held auf Schiff
    MyIndex.Name = "HER_on_Ship";
    MyIndex.Number = 6 * Tilewidth;
    addIndex(MyIndex);

    // Held auf Feuerechse
    MyIndex.Name = "HER_on_Dragon";
    MyIndex.Number = 7 * Tilewidth;
    addIndex(MyIndex);

    // Held tot
    MyIndex.Name = "HER_dead";
    MyIndex.Number = 8 * Tilewidth;
    addIndex(MyIndex);

/*  Index of Towntiles on the Townsheet
    -------------------------------------------------
*/
    MyIndex.Name = "TWN_Secretcave";
    MyIndex.Number = 0;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Druidshack";
    MyIndex.Number = Tilewidth;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Ackbah";
    MyIndex.Number = 2 * Tilewidth;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Worthal";
    MyIndex.Number = 3 * Tilewidth;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Trisdisk";
    MyIndex.Number = 4 * Tilewidth;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Gaht";
    MyIndex.Number = 5 * Tilewidth;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Mubrak";
    MyIndex.Number = 6 * Tilewidth;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Muspel";
    MyIndex.Number = 7 * Tilewidth;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Madraskan";
    MyIndex.Number = 8 * Tilewidth;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Royalpalace";
    MyIndex.Number = 9 * Tilewidth;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Blacktower";
    MyIndex.Number = 10 * Tilewidth;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Whitetower";
    MyIndex.Number = 11 * Tilewidth;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Fulgarpalace";
    MyIndex.Number = 12 * Tilewidth;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Dragoncave";
    MyIndex.Number = 13 * Tilewidth;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Swampdungeon";
    MyIndex.Number = 14 * Tilewidth;
    addIndex(MyIndex);

    MyIndex.Name = "TWN_Crystaldungeon";
    MyIndex.Number = 15 * Tilewidth;
    addIndex(MyIndex);

/*  Index of Worldtiles on the Worldtilesheet
    -------------------------------------------------
*/

    // Meer
    MyIndex.Name = "WTI_Sea";
    MyIndex.Number = 0;
    addIndex(MyIndex);

    // Fluss, seichtes Meer
    MyIndex.Name = "WTI_River";
    MyIndex.Number = Tilewidth;
    addIndex(MyIndex);

    // Wald
    MyIndex.Name = "WTI_Forest";
    MyIndex.Number = 2 * Tilewidth;
    addIndex(MyIndex);

    // Gestrüpp
    MyIndex.Name = "WTI_Shrubbery";
    MyIndex.Number = 3 * Tilewidth;
    addIndex(MyIndex);

    // Grasland
    MyIndex.Name = "WTI_Gras";
    MyIndex.Number = 4 * Tilewidth;
    addIndex(MyIndex);

    // Wüste
    MyIndex.Name = "WTI_Dessert";
    MyIndex.Number = 5 * Tilewidth;
    addIndex(MyIndex);

    // Sumpf
    MyIndex.Name = "WTI_Swamp";
    MyIndex.Number = 6 * Tilewidth;
    addIndex(MyIndex);

    // Berge
    MyIndex.Name = "WTI_Mountain";
    MyIndex.Number = 7 * Tilewidth;
    addIndex(MyIndex);

    // Geröll
    MyIndex.Name = "WTI_Boulders";
    MyIndex.Number = 8 * Tilewidth;
    addIndex(MyIndex);

    // Lava
    MyIndex.Name = "WTI_Lava";
    MyIndex.Number = 9 * Tilewidth;
    addIndex(MyIndex);

    // Brücke horizontal
    MyIndex.Name = "WTI_Bridge_horizontal";
    MyIndex.Number = 10 * Tilewidth;
    addIndex(MyIndex);

    // Brücke vertikal
    MyIndex.Name = "WTI_Bridge_vertical";
    MyIndex.Number = 11 * Tilewidth;
    addIndex(MyIndex);

    // Nebel des Krieges
    MyIndex.Name = "WTI_Fog";
    MyIndex.Number = 12 * Tilewidth;
    addIndex(MyIndex);
/*
    -------------------------------------------------
*/

} // generateIndex
