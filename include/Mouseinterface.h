#ifndef MOUSEINTERFACE_H
#define MOUSEINTERFACE_H


class Mouseinterface
{
    public:
        struct MousePosition
        {
            int mouse_x;
            int mouse_y;
        }; // MousePosition

        struct MouseButtonStatus
        {
            bool mouse_left;
            bool mouse_right;
            bool mouse_middle;
        }; // MouseButtonStatus

        virtual MousePosition getMousePosition() = 0;
        virtual MouseButtonStatus getMouseButton() = 0;

}; // class Mouseinterface

#endif // MOUSEINTERFACE_H
