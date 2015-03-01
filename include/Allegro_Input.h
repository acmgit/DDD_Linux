#ifndef ALLEGRO_INPUT_H
#define ALLEGRO_INPUT_H

#include "Inputinterface.h"
#include "Clock.h"

class Allegro_Input: public Inputinterface
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

    void setMiliSeconds(const int &Miliseconds);
    void setSeconds(const int &Seconds);
    bool wait();

    protected:

    private:
    void needPoll();

    bool isMousePositionvalid;
    MousePosition lastMousePosition;

    Clock *inputClock;

}; // class Allegro_Input

#endif // ALLEGRO_INPUT_H
