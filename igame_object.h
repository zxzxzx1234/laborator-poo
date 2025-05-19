#ifndef IGAME_OBJECT_H
#define IGAME_OBJECT_H

#include <SFML/Graphics.hpp>

class IGameObject {
public:
    virtual void DrawTo(sf::RenderWindow& window) = 0;
    virtual ~IGameObject() = default;
};

#endif
