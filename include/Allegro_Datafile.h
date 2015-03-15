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

        Allegro_Datafile(const std::string &Datafile, const std::string &DatafileIndex, const std::string &Configfile);
        ~Allegro_Datafile();

        DATAFILE* get_Datafile();
        const std::string get_Filename();

        void add_Index(Index newEntry);
        Index find_Index(const std::string &Keyname);
        void remove_Index(Index Entry);

        BITMAP* get_Bitmap(const std::string &Bitmapname);
        FONT* get_Font(const std::string &Fontname);
        PALETTE* get_Palette(const std::string &Palettename);

        int strtoint(std::string Value);
        std::string inttostr(int Value);

    private:

        void load_Index(std::string Indexfile);

        std::string Filename;
        DATAFILE* Data;

        std::map<std::string, int> Dataindex;

        int Tilewidth;
        int Tileheight;


};

#endif // DATAFILE_H
