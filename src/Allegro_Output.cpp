#ifndef ALLEGRO_OUTPUT_CPP
#define ALLEGRO_OUTPUT_CPP

#include "Allegro_Output.h"
#include "Console.h"
#include "Statuswindow.h"
#include "DDD_Screen.h"

#include <allegro/gfx.h>
#include <allegro/graphics.h>
#include <allegro/system.h>
#include <allegro/font.h>

#ifdef DEBUG
#include "Logfile.h"

#endif // DEBUG

Allegro_Output::Allegro_Output(const screenData &Data)
{
    Screendepth = Data.screenDepth;

    outputScreen = new DDD_Screen(Data.screenWidth, Data.screenHeight, Data.screenDepth, Data.Fullscreen);

    if(!outputScreen)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Fail to open the Screenclass.")
        #endif // DEBUG
        allegro_message("Fail to open Screenclass.");
        allegro_exit();
    }


    Display = screen;
    Screenheight = SCREEN_H;
    Screenwidth = SCREEN_W;
    currFont = font;

    VirtualScreen = outputScreen->open_VirtualScreen(Screenwidth, Screenheight);

    if(!VirtualScreen)
    {
#ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Fail to open virtual Screen with " << Screenheight << " x " << Screenwidth << " x " << Screendepth << ".")
#endif // DEBUG

        allegro_message("Konnte keinen Speicher für Bildschrim reservieren.");
        allegro_exit();
    } // if !VirtualScreen

    outputConsole = nullptr;
    outputStatus = nullptr;
    outputPlayfield = nullptr;

    outputSound = new Soundinterface("snd/sound.dat", "snd/sound.idx");
    if(!outputSound)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Fail to open Soundinterfaceclass.")
        #endif // DEBUG

        allegro_message("Fail to open Soundinterfaceclass.");

    } // if !outputSound

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Allegro_Output opened.")
#endif // DEBUG

} // Allegro_Output(screenData)

Allegro_Output::~Allegro_Output()
{
    if(outputConsole)
    {

        delete outputConsole;
        outputConsole = nullptr;
    }
    else
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Consolewindow wasn't open.")
        #endif // DEBUG

    } //if outputConsole


    if(outputStatus)
    {

        delete outputStatus;
        outputStatus = nullptr;
    }
    else
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Statuswindow wasn't open.")
        #endif // DEBUG

    } //if outputConsole

    if(outputPlayfield)
    {
        delete outputPlayfield;
        outputPlayfield = nullptr;

    }
    else
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Playfieldwindow wasn't open.")
        #endif // DEBUG

    } // if outputPlayfield

    outputScreen->close_VirtualScreen(VirtualScreen);

    if(outputScreen)
    {
        delete outputScreen;
        outputScreen = nullptr;

    } // if outputScreen

    if(outputSound)
    {
        delete outputSound;
        outputSound = nullptr;

    } // if outputSound

    #ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Allegro_Output closed.")
    #endif // DEBUG

} // ~Allegro_Output

void Allegro_Output::render_Screen()
{
    outputScreen->render_Screen(VirtualScreen);

    //blit(VirtualScreen, Display, 0, 0, 0, 0, Screenwidth, Screenheight);
    //clear_bitmap(VirtualScreen);

} // render_Screen

void Allegro_Output::write_OnScreen(gfx_Text *Text)
{

    if(Text->toConvert)
    {
        outputScreen->write_Text(VirtualScreen, currFont,
                                convert_Text(Text->Text),
                                Text->Pos_x, Text->Pos_y,
                                Text->Foregroundcolor, Text->Backgroundcolor);

    }
    else
    {
        outputScreen->write_Text(VirtualScreen, currFont,
                                Text->Text,
                                Text->Pos_x, Text->Pos_y,
                                Text->Foregroundcolor, Text->Backgroundcolor);

    } // if Textconvert

} // write_OnScreen(gfx_Text *Text)

void Allegro_Output::write_OnConsole(const int FCol, const int BCol, const std::string &CText, const bool nextLine)
{

    Console::ConsoleText toConsole;

    toConsole.Foreground = FCol;
    toConsole.Background = BCol;
    toConsole.CText = convert_Text(CText);

    outputConsole->write_OnConsole(toConsole, nextLine);

} // write_OnConsole

void Allegro_Output::render_Object(gfx_Object *Object)
{
    outputScreen->render_Object( Object->Sheet, VirtualScreen,
                                Object->Sheetpos_x, Object->Sheetpos_y,
                                Object->Destinationpos_x, Object->Destinationpos_y,
                                Object->Width, Object->Height, Object->transparency);

} // render_Object(gfx_Object *Object)

void Allegro_Output::render_Tile(const tileData &Tile)
{
    int currColumn = Tile.Column;
    int currRow = Tile.Row;

    outputPlayfield->draw_Tile(Tile.Sheet, VirtualScreen, Tile.Sheetpos_x, Tile.Sheetpos_y, currColumn, currRow, Tile.transparency);

} // render_Tile

void Allegro_Output::set_Font(FONT *newFont)
{
    currFont = newFont;

} // setFont(FONT)

void Allegro_Output::set_Palette(PALETTE *newPalette)
{
    set_palette((const RGB*) newPalette);

} // setPalette(PALETTE)

void Allegro_Output::clear_Screen(bool Virtual)
{
    if(Virtual)
    {
        #ifdef DEBUG
        Log("(" << ErrorLog.ALLOK << ") ---===< CLEAR VIRTUAL SCREEN >===---")
        #endif // DEBUG
        clear_bitmap(VirtualScreen);

    }
    else
    {
        clear_bitmap(Display);

    } // if Virtual

} // clearScreen

void Allegro_Output::replace_all(std::string &text,const std::string &fnd,const std::string &rep)
{
    size_t pos = text.find(fnd);
    while(pos != std::string::npos)
    {
        text.replace(pos, fnd.length(), rep);
        pos = text.find(fnd, pos+rep.length());

    } // while(pos)

} // replace_all

std::string Allegro_Output::convert_Text(std::string Text)
{
    replace_all(Text, "ä", "{");
    replace_all(Text, "ö", "|");
    replace_all(Text, "ü", "}");
    replace_all(Text, "Ä", "<");
    replace_all(Text, "Ö", "=");
    replace_all(Text, "Ü", ">");

    return Text;

} // convertText

int Allegro_Output::get_ScreenHeight()
{
    return Screenheight;

} // getScreenHeight

int Allegro_Output::get_ScreenWidth()
{
    return Screenwidth;

} // getScreenHeight

int Allegro_Output::get_ScreenDepth()
{
    return Screendepth;

} // getScreenDepth

void Allegro_Output::set_Console(const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &Rows)
{
    if(!outputConsole)
    {

        outputConsole = new Console(outputScreen, currFont, VirtualScreen, Pos_x, Pos_y, TextHeight, Rows);
        if(!outputConsole)
        {
            #ifdef DEBUG
            Log("(" << ErrorLog.MEMORY_FAILURE << ") Fail to open the Consoleclass.")
            #endif // DEBUG

            allegro_message("Konnte keinen Speicher für die Konsole reservieren.");
            allegro_exit();

        } //if outputConsole

    }
    else
    {
        outputConsole->reset_Console(outputScreen, currFont, Pos_x, Pos_y, TextHeight, Rows);

    } // if !outputConsole)

} // setConsole

void Allegro_Output::set_Statuswindow(const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &Rows)
{
    if(!outputStatus)
    {
        outputStatus = new Statuswindow(outputScreen, VirtualScreen, currFont, Pos_x, Pos_y, TextHeight, Rows);
        if(!outputStatus)
        {
            #ifdef DEBUG
            Log("(" << ErrorLog.MEMORY_FAILURE << ") Fail to open the Statuswindowclass.")
            #endif // DEBUG

            allegro_message("Konnte keinen Speicher für das Statusfenster reservieren.");
            allegro_exit();

        } // if !outputStatus


    }
    else
    {
        outputStatus->reset_Statuswindow(VirtualScreen, currFont, Pos_x, Pos_y, TextHeight, Rows);

    } // if !outputStatus

} // setStatuswindow

void Allegro_Output::set_Playfieldwindow(const int &Pos_x, const int &Pos_y, const int &Tilewidth, const int &Tileheight, const int &Tilecolumns, const int &Tilerows)
{
    if(!outputPlayfield)
    {
        outputPlayfield = new Playfield(outputScreen, Pos_x, Pos_y, Tilewidth, Tileheight, Tilecolumns, Tilerows);
        if(!outputPlayfield)
        {
            #ifdef DEBUG
            Log("(" << ErrorLog.MEMORY_FAILURE << ") Fail to open the Playfieldwindowclass.")
            #endif // DEBUG

            allegro_message("Konnte keinen Speicher für das Spielfeld reservieren.");
            allegro_exit();

        } // if !outputPlayfield

    }
    else
    {

    } // if !outputPlayfield
}

void Allegro_Output::add_StatusLine(const int &Row, const int &Tab, const int &FCol, const int &BCol, const std::string &SText)
{
    Statuswindow::StatusText addText;

    addText.Row = Row;
    addText.Tab = Tab;
    addText.Foreground = FCol;
    addText.Background = BCol;
    addText.Text = convert_Text(SText);

    outputStatus->add_Row(addText);

} // addStatusLine

void Allegro_Output::write_Status()
{
    outputStatus->write_Status();

} //write_Status

BITMAP *Allegro_Output::get_VirtualScreen()
{
    return VirtualScreen;

} // getVirtualScreen();

void Allegro_Output::set_Faderpause(const int Pause)
{
    outputScreen->set_Faderpause(Pause);

} // setFaderpause

void Allegro_Output::screen_FadeIn(const int Speed, BITMAP *to_Fadein)
{
    outputScreen->fade_In(Speed, to_Fadein);

} // screen_FadeIn

void Allegro_Output::screen_FadeOut(const int Speed, BITMAP *to_Fadeout)
{
    outputScreen->fade_Out(Speed, to_Fadeout);

} // screen_FadeOut

void Allegro_Output::play_Music(const std::string Filename, const float &Volume)
{
    if(outputSound)
    {
            outputSound->stream_Music(Filename, Volume);
    } // if outputSound

} // play_Music

void Allegro_Output::play_Sound(std::string Filename)
{
    if(outputSound)
    {
        outputSound->play_Sound(Filename);

    } // if outputSound

} // play_Sound

void Allegro_Output::set_Volume(const float &Volume, const bool &increment)
{
    outputSound->set_Globalvolume(Volume, increment);

} // set_Volume

void Allegro_Output::play_Music()
{
    outputSound->play_Music();

} // play_Music

void Allegro_Output::stop_Music()
{
    outputSound->stop_Music();

} // stop_Music

void Allegro_Output::pause_Music()
{
    outputSound->pause_Music();

} // pause_Music

#endif // ALLEGRO_OUTPUT_CPP
