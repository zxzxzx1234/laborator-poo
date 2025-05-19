#ifndef CONFIG_H
#define CONFIG_H

#include "system.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>

using namespace std;

class Config
{
private:
    // Maps texture name to loaded texture (shared for reuse)
    unordered_map<string, shared_ptr<sf::Texture>> m_texture_map;

    // Maps font identifier to loaded font
    unordered_map<int, shared_ptr<sf::Font>> m_font_map;

    // Load a font into the font map
    shared_ptr<sf::Font> _GetFont(int key);

    // Load a texture into the texture map
    shared_ptr<sf::Texture> _GetTexture(string key);

    // Load all textures at once
    void _SetTexture();

    // Load all fonts at once
    void _SetFont();

    // Helper function for texture loading
    void _LoadTextureHelper();

public:
    // Constructor
    Config();

    // Destructor
    ~Config();

    // Draw debugging constants (optional)
    void DrawConstants(sf::RenderWindow& window, bool exclude = true);

    // Retrieve a texture by string key
    sf::Texture& GetTexture(string index);

    // Retrieve a font by integer ID
    sf::Font& GetFont(int index);
};

// Global config instance (singleton-style)
extern Config config;

#endif
