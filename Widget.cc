#include "Widget.hpp"
#include <iostream>

// Widget
Widget::Widget(sf::Vector2<size_t> &p) {
    _position = p;
    _isActive = true;
}

Widget::Widget(size_t x, size_t y) {
    sf::Vector2<size_t> p(x, y);
    _position = p;
    _isActive = true;
}

void Widget::Draw(rgb_matrix::Canvas* c) {
    std::cout << "draw" << std::endl;
}

// TimeClock - Should probably not allow default font :3
TimeClock::TimeClock() : Widget(0, 0) {
    _color = rgb_matrix::Color(255, 255, 255);
    SetSize(MEDIUM);
}

TimeClock::TimeClock(size_t x, size_t y) : Widget(x, y) {
    _color = rgb_matrix::Color(255, 255, 255);
    SetSize(MEDIUM);
}

TimeClock::TimeClock(size_t x, size_t y, rgb_matrix::Color& color) : Widget(x, y) {
    _color = color;
    SetSize(MEDIUM);
}

TimeClock::TimeClock(size_t x, size_t y, uint r, uint g, uint b) : Widget(x, y) {
    _color = rgb_matrix::Color(r, g, b);
    SetSize(MEDIUM);
}

void TimeClock::SetSize(Size s) {
    switch(s){
        case SMALL:
            _dateFont.LoadFont("fonts/5x7.bdf");
            _font.LoadFont("fonts/6x10.bdf");
            _letterSpacing = 0;
            _dateLetterSpacing = 0;
        break;
        
        case MEDIUM:
            _dateFont.LoadFont("fonts/6x9.bdf");
            _font.LoadFont("fonts/8x13.bdf");
            _letterSpacing = -1;
            _dateLetterSpacing = -1;
        break;

        case LARGE:

        break;
    }

    _clockSize = s;
}


std::string TimeClock::GetHourMinute() const{
    std::string str;
    time_t t = time(NULL);
    tm *tm_local = localtime(&t);
    int hour = tm_local->tm_hour;
    int minute = tm_local->tm_min;

    // Hour 
    if (hour > 12) {
        hour = hour % 12;
    }
    if (hour < 10) {
        str.append("0" + std::to_string(hour) + ":");
    }else{
        str.append(std::to_string(hour) + ":");
    }
    
    // Minute
    if (minute < 10) {
        str.append("0" + std::to_string(minute));
    }else {
        str.append(std::to_string(minute));
    }
    //std::cout << str.c_str() << std::endl;
    const char* cstr = str.c_str();
    return cstr;
}

std::string TimeClock::GetMonthDayYear() const{
    std::string str;
    time_t t = time(NULL);
    tm *tm_local = localtime(&t);

    int day = tm_local->tm_mday;
    int month = tm_local->tm_mon;

    if (day < 10) {
        str.append("0");
    }
    str.append(std::to_string(day) + "/");
    if (month < 10) {
        str.append("0");
    }
    str.append(std::to_string(month + 1));

    return str;
}

void TimeClock::Draw(rgb_matrix::Canvas* c) {
    int xOffset, yOffset;
    switch (_clockSize) {
        case SMALL:
            xOffset = 2;
            yOffset = 7;
            break;
        case MEDIUM:
            xOffset = 5;
            yOffset = 8;
            break;
        case LARGE:

            break;
    }
    rgb_matrix::DrawText(c, _font, GetPosition().x, GetPosition().y, _color, nullptr, GetHourMinute().c_str(),
        _letterSpacing);
    rgb_matrix::DrawText(c, _dateFont, GetPosition().x + xOffset, GetPosition().y + yOffset, _color, nullptr, GetMonthDayYear().c_str(),
        _dateLetterSpacing);
}