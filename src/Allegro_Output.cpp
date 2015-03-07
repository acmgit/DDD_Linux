#ifndef ALLEGRO_OUTPUT_CPP
#define ALLEGRO_OUTPUT_CPP

#include "Allegro_Output.h"
#include "Console.h"
#include "Statuswindow.h"

#include <allegro/gfx.h>
#include <allegro/graphics.h>
#include <allegro/system.h>
#include <allegro/font.h>

#ifdef DEBUG
#include "Logfile.h"

#endif // DEBUG

Allegro_Output::Allegro_Output(const screenData &Data)
{
    set_color_depth(Data.screenDepth);
    Screendepth = Data.screenDepth;

    int screenError;
    if(Data.Fullscreen)
    {
        screenError = set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, Data.screenWidth, Data.screenHeight, 0, 0);

    }
    else
    {
        screenError = set_gfx_mode(GFX_AUTODETECT_WINDOWED, Data.screenWidth, Data.screenHeight, 0, 0);

    } // if Fullscreen

    if(screenError)
    {
#ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Fail to open Screen " << Data.screenWidth << "x" << Data.screenHeight << " Depth: " << Data.screenDepth)
#endif // DEBUG

        allegro_message(allegro_error);
        allegro_exit();

    } // if screenError

    Display = screen;
    Screenheight = SCREEN_H;
    Screenwidth = SCREEN_W;
    currFont = font;

    VirtualScreen = create_bitmap(Screenwidth, Screenheight);
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

    destroy_bitmap(VirtualScreen);

} // ~Allegro_Output

void Allegro_Output::renderScreen()
{
    blit(VirtualScreen, Display, 0, 0, 0, 0, Screenwidth, Screenheight);
    //clear_bitmap(VirtualScreen);

} // renderScreen

void Allegro_Output::writeOnScreen(void *Text)
{
#ifdef DEBUG
    Log("(" << ErrorLog.WRONG_FUNCTION << ") Attention, void* called")
#endif // DEBUG
    writeOnScreen((gfx_Text*) Text);

} // writeOnScreen(void*)

void Allegro_Output::writeOnScreen(gfx_Text *Text)
{
    if(Text->toConvert)
    {
        textout_ex(VirtualScreen, currFont, convertText(Text->Text).c_str(), Text->Pos_x, Text->Pos_y, Text->Foregroundcolor, Text->Backgroundcolor);

    }
    else
    {
        textout_ex(VirtualScreen, currFont, Text->Text.c_str(), Text->Pos_x, Text->Pos_y, Text->Foregroundcolor, Text->Backgroundcolor);

    } // if Textconvert

} // writeOnScreen(gfx_Text *Text)

void Allegro_Output::writeOnConsole(const int FCol, const int BCol, const std::string CText, const bool nextLine)
{

    Console::ConsoleText toConsole;

    toConsole.Foreground = FCol;
    toConsole.Background = BCol;
    toConsole.CText = convertText(CText);

    outputConsole->writeOnConsole(toConsole, nextLine);

} // writeOnConsole

void Allegro_Output::renderObject(void *Object)
{

#ifdef DEBUG
    Log("(" << ErrorLog.WRONG_FUNCTION << ") Attention, void* called")
#endif // DEBUG

    renderObject((gfx_Object*) Object);

} // drawObject(void *Object)

void Allegro_Output::renderObject(gfx_Object *Object)
{
    if(Object->transparency)
    {
        masked_blit(Object->Sheet, VirtualScreen, Object->Sheetpos_x, Object->Sheetpos_y, Object->Destinationpos_x, Object->Destinationpos_y, Object->Width, Object->Height);

    }
    else
    {
        blit(Object->Sheet, VirtualScreen, Object->Sheetpos_x, Object->Sheetpos_y, Object->Destinationpos_x, Object->Destinationpos_y, Object->Width, Object->Height);

    } // if transparency

} // drawObject(gfx_Object *Object)

void Allegro_Output::renderTile(const tileData Tile)
{
    int currColumn = Tile.Column;
    int currRow = Tile.Row;

    outputPlayfield->drawTile(Tile.Sheet, Tile.Sheetpos_x, Tile.Sheetpos_y, currColumn, currRow, Tile.transparency);

}

void Allegro_Output::setFont(FONT *newFont)
{
    currFont = newFont;

} // setFont(FONT)

void Allegro_Output::setPalette(PALETTE *newPalette)
{
    set_palette((const RGB*) newPalette);

} // setPalette(PALETTE)

void Allegro_Output::clearScreen(bool Virtual)
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

std::string Allegro_Output::convertText(std::string Text)
{
    replace_all(Text, "ä", "{");
    replace_all(Text, "ö", "|");
    replace_all(Text, "ü", "}");
    replace_all(Text, "Ä", "<");
    replace_all(Text, "Ö", "=");
    replace_all(Text, "Ü", ">");

    return Text;

} // convertText

int Allegro_Output::getScreenHeight()
{
    return Screenheight;

} // getScreenHeight

int Allegro_Output::getScreenWidth()
{
    return Screenwidth;

} // getScreenHeight

int Allegro_Output::getScreenDepth()
{
    return Screendepth;

} // getScreenDepth

void Allegro_Output::setConsole(const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &Rows)
{
    if(!outputConsole)
    {

        outputConsole = new Console(VirtualScreen, currFont, Pos_x, Pos_y, TextHeight, Rows);
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
        outputConsole->resetConsole(VirtualScreen, currFont, Pos_x, Pos_y, TextHeight, Rows);

    } // if !outputConsole)

} // setConsole

void Allegro_Output::setStatuswindow(const int &Pos_x, const int &Pos_y, const int &TextHeight, const int &Rows)
{
    if(!outputStatus)
    {
        outputStatus = new Statuswindow(VirtualScreen, currFont, Pos_x, Pos_y, TextHeight, Rows);
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
        outputStatus->resetStatuswindow(VirtualScreen, currFont, Pos_x, Pos_y, TextHeight, Rows);

    } // if !outputStatus

} // setStatuswindow

void Allegro_Output::setPlayfieldwindow(const int &Pos_x, const int &Pos_y, const int &Tilewidth, const int &Tileheight, const int &Tilecolumns, const int &Tilerows)
{
    if(!outputPlayfield)
    {
        outputPlayfield = new Playfield(VirtualScreen, Pos_x, Pos_y, Tilewidth, Tileheight, Tilecolumns, Tilerows);
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
void Allegro_Output::addStatusLine(const int &Row, const int &Tab, const int &FCol, const int &BCol, const std::string &SText)
{
    Statuswindow::StatusText addText;

    addText.Row = Row;
    addText.Tab = Tab;
    addText.Foreground = FCol;
    addText.Background = BCol;
    addText.Text = convertText(SText);

    outputStatus->addRow(addText);

} // addStatusLine

void Allegro_Output::writeStatus()
{
    outputStatus->writeStatus();

} //writeStatus

#endif // ALLEGRO_OUTPUT_CPP
