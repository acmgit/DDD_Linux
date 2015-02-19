#ifndef ALLEGRO_INPUT_H
#define ALLEGRO_INPUT_H

#include "Inputinterface.h"

class Allegro_Input: public Inputinterface
{
    public:
        Allegro_Input();
        ~Allegro_Input();

    // Keyboard
    bool readKey();
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
