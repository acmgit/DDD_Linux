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

    Screenwidth = Width;
    Screenheight = Height;

    set_color_depth(Scrdepth);

    int screenError;
    if(Fullscreen)
    {
        screenError = set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, Width, Height, 0, 0);

    }
    else
    {
        screenError = set_gfx_mode(GFX_AUTODETECT_WINDOWED, Screenwidth, Screenheight, 0, 0);

    } // if Fullscreen

    if(screenError)
    {
#ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Fail to open Screen " << Screenwidth << "x" << Screenheight << " Depth: " << Screendepth)
#endif // DEBUG

        allegro_message(allegro_error);
        allegro_exit();

    } // if screenError

    Display = screen;

    VirtualScreen = create_bitmap(SCREEN_W, SCREEN_H);
    if(!VirtualScreen)
    {
#ifdef DEBUG
        Log("(" << ErrorLog.MEMORY_FAILURE << ") Fail to open virtual Screen.")
#endif // DEBUG

        //exit_on_error("Konnte keinen Speicher für Bildschrim reservieren.");
        allegro_message("Konnte keinen Speicher für Bildschrim reservieren.");
        allegro_exit();
    } // if !VirtualScreen

    currFont = font;
#ifdef DEBUG
    Log("Allegro_Output geöffnet.")
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
    gfx_Text* currText = (gfx_Text*) Text;

    if(currText->toConvert)
    {
        textout_ex(VirtualScreen, currFont, convertText(currText->Text).c_str(), currText->Pos_x, currText->Pos_y, currText->Foregroundcolor, currText->Backgroundcolor);

    }
    else
    {
        textout_ex(VirtualScreen, currFont, currText->Text.c_str(), currText->Pos_x, currText->Pos_y, currText->Foregroundcolor, currText->Backgroundcolor);

    } // if toConvert


} // writeOnScreen

void Allegro_Output::renderObject(void *Object)
{
    gfx_Object* currObject = (gfx_Object*) Object;
    if(currObject->transparency)
    {
        masked_blit(currObject->Source, VirtualScreen, currObject->Sourcepos_x, currObject->Sourcepos_y, currObject->Destinationpos_x, currObject->Destinationpos_y, currObject->Width, currObject->Height);

    }
    else
    {
        blit(currObject->Source, VirtualScreen, currObject->Sourcepos_x, currObject->Sourcepos_y, currObject->Destinationpos_x, currObject->Destinationpos_y, currObject->Width, currObject->Height);

    } // if transparency

} // drawObject()

void Allegro_Output::setFont(FONT *newFont)
{
    currFont = newFont;
}
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
