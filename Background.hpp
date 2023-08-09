#include "led-matrix.h"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Background{
    public:
        Background (std::vector<sf::Image> & f);
        const sf::Image& step();
    private:
        size_t _numFrames;
        size_t _currentFrame;
        std::vector<sf::Image> _frames;
};