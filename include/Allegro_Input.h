#ifndef ALLEGRO_INPUT_H
#define ALLEGRO_INPUT_H

#include "Inputinterface.h"
#include "Clock.h"

class Allegro_Input: public Inputinterface, public Clock
{
    public:
        Allegro_Input();
        ~Allegro_Input();

    // Keyboard
    bool readKey();
    bool readKey(int Seconds);

    Key getKey();

    // Mouse
    bool hasMousemoved();
    MousePosition getMousePosition();
    MouseButtonStatus getMouseButton();

    protected:

    private:
    void needPoll();

    bool isMousePositionvalid;
    MousePosition lastMousePosition;

}; // class Allegro_Input

#endif // ALLEGRO_INPUT_H
