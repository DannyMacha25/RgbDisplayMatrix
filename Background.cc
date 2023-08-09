#include "Background.hpp"
#include <SFML/Graphics.hpp>
 

Background::Background(std::vector<sf::Image> &f){
    _numFrames = f.size();
    _frames = f;
    _currentFrame = 0;
}

const sf::Image& Background::step(){
    sf::Image& toReturn = _frames[_currentFrame];
    _currentFrame++;
    if(_currentFrame == _numFrames - 1){
        _currentFrame = 0;
    }

    return toReturn;
}
