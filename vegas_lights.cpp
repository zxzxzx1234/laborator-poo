#include "vegas_lights.h"

namespace VegasLights {

    std::vector<Light>& GetLights() {
        static std::vector<Light> lights;
        return lights;
    }

    void Init() {
        auto& lights = GetLights();
        lights.clear();

        float base_y = 700.f; 
        float spacing = 180.f; 
        float start_x = 150.f;

        for (int i = 0; i < 4; ++i) {
            Light l;
            l.base_radius = 35 + i * 5;
            l.phase = i * 1.57f;
            l.shape.setRadius(l.base_radius);
            l.shape.setFillColor(sf::Color(255, 255, 0, 80)); 
            l.shape.setOrigin(l.base_radius, l.base_radius);
            l.shape.setPosition(start_x + i * spacing, base_y);  
            lights.push_back(l);
        }
    }


    void Update(float time) {
        auto& lights = GetLights();
        for (auto& l : lights) {
            float pulse = std::sin(time + l.phase) * 5.f;
            l.shape.setRadius(l.base_radius + pulse);
            l.shape.setOrigin(l.shape.getRadius(), l.shape.getRadius());
        }
    }

    void Draw(sf::RenderWindow& window) {
        auto& lights = GetLights();
        for (auto& l : lights)
            window.draw(l.shape);
    }
}
