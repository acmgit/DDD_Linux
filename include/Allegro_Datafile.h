#ifndef DATAFILE_H
#define DATAFILE_H

#include <string>
#include <map>

#include "Datafileinterface.h"

#include <allegro/datafile.h>
#include <allegro/gfx.h>
#include <allegro/font.h>
#include <allegro/graphics.h>
#include <sstream>
#include <iostream>

class Allegro_Datafile: public Datafileinterface
{
    public:
        struct Index
        {
            std::string Name;
            int Number;
        };

        struct Colorfont
        {
            FONT *Font;
            PALETTE *Palette;
        };

        Allegro_Datafile(const std::string Datafile, const std::string DatafileIndex, const std::string Configfile);
        ~Allegro_Datafile();

        DATAFILE* getDatafile();
        const std::string getFilename();

        void addIndex(Index newEntry);
        Index findIndex(const std::string Keyname);
        void removeIndex(Index Entry);

        BITMAP* getBitmap(const std::string Bitmapname);
        FONT* getFont(const std::string Fontname);
        PALETTE* getPalette(const std::string Palettename);

        int strtoint(std::string Value);
        std::string inttostr(int Value);

    private:

        void loadIndex(std::string Indexfile);

        std::string Filename;
        DATAFILE* Data;

        std::map<std::string, int> Dataindex;

        int Tilewidth;
        int Tileheight;


};

#endif // DATAFILE_H
