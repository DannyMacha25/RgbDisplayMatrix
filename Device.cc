
#include "Device.hpp"

Device::Device() {
    
}

bool Device::AddWidget(Widget* w) {
    _widgets.push_back(w);
    return true;
}

void Device::Display(rgb_matrix::Canvas* c) {
    for (Widget *w : _widgets) {
        w->Draw(c);
    }
}