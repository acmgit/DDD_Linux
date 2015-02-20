#include "Allegro_Output.h"
#include <allegro/gfx.h>
#include <allegro/graphics.h>

#ifdef DEBUG
#include "Logfile.h"

#endif // DEBUG
Allegro_Output::Allegro_Output(BITMAP *Source, BITMAP *Destination, int Width, int Height)
{

    Display = Destination;
    VirtualScreen = Source;
    Screenwidth = Width;
    Screenheight = Height;

#ifdef DEBUG
    Log("Allegro_Output geöffnet.")
#endif // DEBUG

} // Allegro_Output

Allegro_Output::~Allegro_Output()
{
    //dtor
} // ~Allegro_Output

void Allegro_Output::renderScreen()
{
    blit(VirtualScreen, Display, 0, 0, 0, 0, Screenwidth, Screenheight);
    clear_bitmap(VirtualScreen);

} // renderScreen

void Allegro_Output::writeOnScreen(void *Text)
{
    gfx_Text* currText = (gfx_Text*) Text;
    textout_ex(VirtualScreen, currText->Font, currText->Text.c_str(), currText->Pos_x, currText->Pos_y, currText->Foregroundcolor, currText->Backgroundcolor);

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
