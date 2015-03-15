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
    bool read_Key();
    bool read_Key(int Seconds);
    Key get_Key();

    // Mouse
    bool hasMousemoved();
    MousePosition get_MousePosition();
    MouseButtonStatus get_MouseButton();

    void set_MilliSeconds(const int &Milliseconds);
    void set_Seconds(const int &Seconds);
    bool wait();

    protected:

    private:
    void needPoll();

    bool isMousePositionvalid;
    MousePosition lastMousePosition;

    Clock *inputClock;

}; // class Allegro_Input

#endif // ALLEGRO_INPUT_H
