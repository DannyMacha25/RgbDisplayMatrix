
#ifndef WIDGET
#define WIDGET

#include "graphics.h"
#include "led-matrix.h"
#include "nlohmann/json.hpp"
#include <ctime>
#include <SFML/System.hpp>

using json = nlohmann::json;
// Needs copy constructors and stuff
enum Size{
    SMALL,
    MEDIUM,
    LARGE
};

enum WidgetID{
    NONE,
    TIMECLOCK
};

class Widget {
    public:
        Widget(sf::Vector2<size_t> &p);
        Widget(size_t x, size_t y);

        void ToggleActive(){_isActive = !_isActive;}
        void SetPosition(sf::Vector2<size_t> &p) {_position = p;}
        void SetPosition(size_t x, size_t y) {_position.x = x; _position.y = y;}
        sf::Vector2<size_t>& GetPosition() {return _position;}
        virtual void Draw(rgb_matrix::Canvas* c);
        virtual void InitializeWidgetFromJson(json j, int index);
    private:
        sf::Vector2<size_t> _position; // Top left corner - Text doesn bottom left
        bool _isActive;
};

class TimeClock: public Widget {
    public:
        TimeClock();
        TimeClock(size_t x, size_t y);
        TimeClock(size_t x, size_t y, rgb_matrix::Color& color);
        TimeClock(size_t x, size_t y, uint r, uint g, uint b);

        std::string GetHourMinute() const;
        std::string GetMonthDayYear() const;

        void SetSize(Size s);
        void Draw(rgb_matrix::Canvas* c) override;
        void InitializeWidgetFromJson(json j, int index) override;
    private:
        rgb_matrix::Color _color;
        rgb_matrix::Font _font, _dateFont;
        Size _clockSize = MEDIUM;
        int _letterSpacing = 0, _dateLetterSpacing = 0;
};

#endif