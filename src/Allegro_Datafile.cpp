#include "Allegro_Datafile.h"
#include <allegro/system.h>

#ifdef DEBUG
#include "Logfile.h"
#include <allegro/system.h>

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
