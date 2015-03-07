#ifndef SCREENINTERFACE_H
#define SCREENINTERFACE_H

class Screeninterface
{
    public:
        virtual ~Screeninterface() {};

        virtual void renderScreen() = 0;                                    // renders the whole Screen
        virtual void writeOnScreen(void *Text) = 0;
        virtual void renderObject(void *Object) = 0;

    protected:

}; // Screeninterface

#endif // SCREENINTERFACE_H
