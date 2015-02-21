#ifndef DATAFILE_H
#define DATAFILE_H

#include <string>
#include <map>

#include "Datafileinterface.h"
#include <allegro/datafile.h>

class Allegro_Datafile: public Datafileinterface
{
    public:
        struct Index
        {
            std::string Name;
            int Number;
        };

        Allegro_Datafile(const std::string File);
        ~Allegro_Datafile();

        DATAFILE* getDatafile();
        const std::string getFilename();

        void addIndex(Index newEntry);
        Index findIndex(std::string Keyname);
        void removeIndex(Index Entry);

    private:

    std::string Filename;
    DATAFILE* Data;

    std::map<std::string, int> Dataindex;
};

#endif // DATAFILE_H
