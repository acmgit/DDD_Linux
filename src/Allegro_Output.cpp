#include "Allegro_Output.h"
#include <allegro/gfx.h>
#include <allegro/graphics.h>
#include <allegro/system.h>
#include <allegro/font.h>

#ifdef DEBUG
#include "Logfile.h"

#endif // DEBUG

Allegro_Output::Allegro_Output(int Width, int Height, int Scrdepth, bool Fullscreen)
{
    set_color_depth(Scrdepth);
    Screendepth = Scrdepth;

    int screenError;
    if(Fullscreen)
    {
        screenError = set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, Width, Height, 0, 0);

    }
    else
    {
        screenError = set_gfx_mode(GFX_AUTODETECT_WINDOWED, Width, Height, 0, 0);

    } // if Fullscreen

    if(screenError)
    {
#ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Fail to open Screen " << Width << "x" << Height << " Depth: " << Screendepth)
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

#ifdef DEBUG
    Log("Allegro_Output opened with Screen " << Screenwidth << " x " << Screenheight << " x " << Screendepth << ".")
#endif // DEBUG

} // Allegro_Output

Allegro_Output::~Allegro_Output()
{
    destroy_bitmap(VirtualScreen);
#ifdef DEBUG
    Log("Virtual Screen destroyed.")
#endif // DEBUG
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


void Allegro_Output::setFont(FONT *newFont)
{
    currFont = newFont;

} // setFont

void Allegro_Output::clearScreen(bool Virtual)
{
    if(Virtual)
    {
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