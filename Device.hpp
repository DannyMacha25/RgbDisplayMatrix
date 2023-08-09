#ifndef DEVICE
#define DEVICE

#include "graphics.h"
#include "led-matrix.h"
#include "Widget.hpp"
#include <iostream>
#include <SFML/System.hpp>

const int MAX_WIDGETS = 3;

class Device{
    public:
        Device();

        bool AddWidget(Widget *w); // Can't add if full
        bool RemoveWidget(Widget *w); // Can't remove if not there

        void Display(rgb_matrix::Canvas* c);
    private:
        std::vector<Widget*> _widgets;
};

#endif