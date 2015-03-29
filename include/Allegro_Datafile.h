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
        struct Index                        // Entry of an Index
        {
            std::string Name;
            int Number;
        };

        struct Colorfont                    // Entry of a Colorfont
        {
            FONT *Font;
            PALETTE *Palette;
        };

        Allegro_Datafile(const std::string &Datafile, const std::string &DatafileIndex, const std::string &Configfile);
        ~Allegro_Datafile();

        DATAFILE* get_Datafile();
        const std::string get_Filename();

        // Indexcommands
        void add_Index(Index newEntry);                                 // Build an Indexentry
        Index find_Index(const std::string &Keyname);                   // Find an Indexentry
        void remove_Index(Index Entry);                                 // delete an Indexentry

        // Special Commands
        BITMAP* get_Bitmap(const std::string &Bitmapname);
        FONT* get_Font(const std::string &Fontname);
        PALETTE* get_Palette(const std::string &Palettename);
        int get_Color(std::string Text);

        template <class X>
        void strtoval(std::string Value, X &Val);

        template <class X>
        std::string valtostr(X &Value);

    private:

        void load_Index(std::string Indexfile);

        std::string Filename;
        DATAFILE* Data;

        std::map<std::string, int> Dataindex;

        int Tilewidth;
        int Tileheight;


};

template <class X>
void Allegro_Datafile::strtoval(std::string Number, X &Val)
{
    X Num;
    std::stringstream Str;
    Str << Number;
    Str >> Num;

    Val = Num;

} // strtoint

template <class X>
std::string Allegro_Datafile::valtostr(X &Value)
{
    std::ostringstream Str;
    Str << Value;

    return Str.str();

} // inttostr
#endif // DATAFILE_H
