#ifndef ALLEGRO_INPUT_CPP
#define ALLEGRO_INPUT_CPP

#include "Allegro_Input.h"
#include <iostream>
#include <allegro.h>

Allegro_Input::Allegro_Input()
{
    install_keyboard();
    install_mouse();
    install_timer();
    isMousePositionvalid = false;

    enable_hardware_cursor();
    show_os_cursor(MOUSE_CURSOR_ARROW);

} // Allegro_Input

Allegro_Input::~Allegro_Input()
{
    //dtor
    remove_keyboard();
    remove_mouse();

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

    std::cout << "Es steht die Taste " << currentKey.Key << " im Tastaturpuffer." << std::endl;
    std::cout << "Mit dem Scancode " << currentKey.Scancode << "." << std::endl;

    return currentKey;

} // getKey

bool Allegro_Input::readKey()
{
    if(keypressed())
    {
        std::cout << "Es wurde eine Taste gedrückt ..." << std::endl;
        return true;

    } // if keypressed()

    return false;

} // readKey

bool Allegro_Input::hasMousemoved()
{
    needPoll();
    if(isMousePositionvalid == false)                                                       // has lastMousePosition a value?
    {
        isMousePositionvalid = true;                                                        // no,
        lastMousePosition = getMousePosition();                                             // write the Value to lastMousePosition

        std::cout << "Die Maus hat ihre Position nicht verändert ..." << std::endl;
        return false;                                                                       // false, cause we don't know about an move of the mouse

    } // if isMousePositionvalid

    MousePosition currentMousePosition = getMousePosition();
    if((currentMousePosition.mouse_x == lastMousePosition.mouse_x) && (currentMousePosition.mouse_y == lastMousePosition.mouse_y))
    {
        std::cout << "Die Maus hat ihre Position nicht verändert ..." << std::endl;
        return false;

    }
    else
    {
        lastMousePosition.mouse_x = currentMousePosition.mouse_x;                           // Update the new Mouseposition
        lastMousePosition.mouse_y = currentMousePosition.mouse_y;
        std::cout << "Die Maus hat ihre Position verändert ..." << std::endl;
        return true;

    } // if MyMousePosition.mouse_x && MyMousePosition.mouse_y

} // hasMousemoved

Allegro_Input::MouseButtonStatus Allegro_Input::getMouseButton()
{
    needPoll();

    Allegro_Input::MouseButtonStatus currentMouseButtonStatus;

    currentMouseButtonStatus.mouse_left = mouse_b & 1;
    currentMouseButtonStatus.mouse_right = mouse_b & 2;

    if(currentMouseButtonStatus.mouse_left)
    {
        std::cout << "Die linke Maustaste ist gedrückt ..." << std::endl;

    }
    else
    {
        std::cout << "Die linke Maustaste ist nicht gedrückt ..." << std::endl;

    } // if currentMouseButtonStatus.mouse_left

    if(currentMouseButtonStatus.mouse_right)
    {
        std::cout << "Die rechte Maustaste ist gedrückt ..." << std::endl;

    }
    else
    {
        std::cout << "Die rechte Maustaste ist nicht gedrückt ..." << std::endl;

    } // if currentMousePosition.mouse_right

    return currentMouseButtonStatus;

} // getMouseButton

Allegro_Input::MousePosition Allegro_Input::getMousePosition()
{
    needPoll();

    Allegro_Input::MousePosition currentMousePosition;

    currentMousePosition.mouse_x = mouse_pos >> 16;
    currentMousePosition.mouse_y = mouse_pos & 0x0000ffff;

    std::cout << "Die Maus steht an Position X = " << currentMousePosition.mouse_x << " und Position Y = " << currentMousePosition.mouse_y << " ..." << std::endl;

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
