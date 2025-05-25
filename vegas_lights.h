#ifndef VEGAS_LIGHTS_H
#define VEGAS_LIGHTS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

namespace VegasLights {

    struct Light {
        sf::CircleShape shape;
        float base_radius;
        float phase;
    };

    std::vector<Light>& GetLights();

    void Init();
    void Update(float time);
    void Draw(sf::RenderWindow& window);
}

#endif
