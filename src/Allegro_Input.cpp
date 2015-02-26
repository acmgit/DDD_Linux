#ifndef ALLEGRO_INPUT_CPP
#define ALLEGRO_INPUT_CPP

#include "Allegro_Input.h"

#include <iostream>
#include <allegro.h>

#ifdef DEBUG

#include "Logfile.h"

#endif // DEBUG

Allegro_Input::Allegro_Input()
{
    install_keyboard();
    install_mouse();
    install_timer();
    isMousePositionvalid = false;

    enable_hardware_cursor();
    show_os_cursor(MOUSE_CURSOR_ARROW);
#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Allegro_Input opened.")
#endif

} // Allegro_Input

Allegro_Input::~Allegro_Input()
{
    //dtor
    remove_keyboard();
    remove_mouse();

#ifdef DEBUG
    Log("(" << ErrorLog.ALLOK << ") Allegro_Input closed.")
#endif // DEBUG

} // ~Allegro_Input

Allegro_Input::Key Allegro_Input::getKey()
{
    int currentAllegroKey;
    currentAllegroKey = readkey();                                                          // Attention, this is the readkey-Function from Allegro

    Allegro_Input::Key currentKey;
    currentKey.Key = (char) currentAllegroKey;
    currentKey.Scancode = currentAllegroKey >> 8;
    currentKey.Strg = false;
    currentKey.Alt = false;
    currentKey.Shift = false;

    return currentKey;

} // getKey

bool Allegro_Input::readKey()
{
    if(keypressed())
    {
        return true;

    } // if keypressed()

    return false;

} // readKey

bool Allegro_Input::readKey(const int Seconds)
{
    setSeconds(Seconds);

    while(!wait())
    {
        if(readKey())
        {
            return true;

        } // if readKey

    } // while wait

    return false;

} // readKey(Seconds)

bool Allegro_Input::hasMousemoved()
{
    needPoll();
    if(isMousePositionvalid == false)                                                       // has lastMousePosition a value?
    {
        isMousePositionvalid = true;                                                        // no,
        lastMousePosition = getMousePosition();                                             // write the Value to lastMousePosition

        return false;                                                                       // false, cause we don't know about an move of the mouse

    } // if isMousePositionvalid

    MousePosition currentMousePosition = getMousePosition();
    if((currentMousePosition.mouse_x == lastMousePosition.mouse_x) && (currentMousePosition.mouse_y == lastMousePosition.mouse_y))
    {
        return false;

    }
    else
    {
        lastMousePosition.mouse_x = currentMousePosition.mouse_x;                           // Update the new Mouseposition
        lastMousePosition.mouse_y = currentMousePosition.mouse_y;
        return true;

    } // if MyMousePosition.mouse_x && MyMousePosition.mouse_y

} // hasMousemoved

Allegro_Input::MouseButtonStatus Allegro_Input::getMouseButton()
{
    needPoll();

    Allegro_Input::MouseButtonStatus currentMouseButtonStatus;

    currentMouseButtonStatus.mouse_left = mouse_b & 1;
    currentMouseButtonStatus.mouse_right = mouse_b & 2;

    return currentMouseButtonStatus;

} // getMouseButton

Allegro_Input::MousePosition Allegro_Input::getMousePosition()
{
    needPoll();

    Allegro_Input::MousePosition currentMousePosition;

    currentMousePosition.mouse_x = mouse_pos >> 16;
    currentMousePosition.mouse_y = mouse_pos & 0x0000ffff;

    return currentMousePosition;
} // getMousePosition

void Allegro_Input::needPoll()
{
    if(mouse_needs_poll())
    {
        poll_mouse();

    } // if mouse_needs_poll

    if(keyboard_needs_poll())
    {
        poll_keyboard();

    } // if keyboard_needs_poll

} // needPoll
#endif // ALLEGRO_INPUT_CPP
