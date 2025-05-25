#include "config.h"
#include <cassert>

// Global instance
Config config = Config();

Config::Config()
{
    this->_SetTexture();
    this->_SetFont();
}

Config::~Config() {}

shared_ptr<sf::Texture> Config::_GetTexture(string key)
{
    if (this->m_texture_map.find(key) != this->m_texture_map.end()) {
        return this->m_texture_map[key];
    }
    return nullptr;
}

shared_ptr<sf::Font> Config::_GetFont(int key)
{
    if (this->m_font_map.find(key) != this->m_font_map.end()) {
        return this->m_font_map[key];
    }
    return nullptr;
}

sf::Texture& Config::GetTexture(string index)
{
    shared_ptr<sf::Texture> texture = this->_GetTexture(index);
    assert(texture != nullptr && "Attempted to access a non-existent texture.");
    return *texture;
}

sf::Font& Config::GetFont(int index)
{
    shared_ptr<sf::Font> font = this->_GetFont(index);
    assert(font != nullptr && "Attempted to access a non-existent font.");
    return *font;

}

void Config::_SetTexture()
{
    for (int i = 0; i < 13; ++i)
    {
        string temp = "";

        switch (i)
        {
        case 0: temp += "ace"; break;
        case 10: temp += "jack"; break;
        case 11: temp += "queen"; break;
        case 12: temp += "king"; break;
        default: temp += to_string(i + 1); break;
        }

        string club_path = PATH + temp + CLUBS;
        auto club_ptr = make_shared<sf::Texture>();
        club_ptr->loadFromFile(club_path);
        this->m_texture_map["c" + to_string(i + 1)] = club_ptr;

        string diamond_path = PATH + temp + DIAMONDS;
        auto diamond_ptr = make_shared<sf::Texture>();
        diamond_ptr->loadFromFile(diamond_path);
        this->m_texture_map["d" + to_string(i + 1)] = diamond_ptr;

        string heart_path = PATH + temp + HEARTS;
        auto heart_ptr = make_shared<sf::Texture>();
        heart_ptr->loadFromFile(heart_path);
        this->m_texture_map["h" + to_string(i + 1)] = heart_ptr;

        string spade_path = PATH + temp + SPADES;
        auto spade_ptr = make_shared<sf::Texture>();
        spade_ptr->loadFromFile(spade_path);
        this->m_texture_map["s" + to_string(i + 1)] = spade_ptr;
    }

    string bet = "1";
    for (int i = 0; i < 4; ++i)
    {
        string temp = PATH + bet + PNG;
        auto ptr = make_shared<sf::Texture>();
        ptr->loadFromFile(temp);
        this->m_texture_map[bet] = ptr;
        bet += "0";
    }

    this->_LoadTextureHelper();
}

void Config::_SetFont()
{
    auto font = make_shared<sf::Font>();
    font->loadFromFile("assets/arial.ttf");
    this->m_font_map[ARIAL] = font;
}

void Config::DrawConstants(sf::RenderWindow& window, bool exclude)
{
    sf::Font font = this->GetFont(ARIAL);
    sf::Text bet_input_title;
    bet_input_title.setFont(font);
    bet_input_title.setString("Enter your bet\n(Press Enter)\nUP to start");
    bet_input_title.setCharacterSize(20);
    bet_input_title.setPosition({ 1150, 325 });
    bet_input_title.setFillColor(sf::Color::Red);
    window.draw(bet_input_title);

    vector<sf::Sprite> bet_sprites;
    string bet = "1";
    for (int i = 0; i < 4; ++i)
    {
        sf::Sprite sprite(this->GetTexture(bet));
        sprite.setPosition({ 1225, float(10 + 60 * i) });
        bet_sprites.push_back(sprite);
        bet += "0";
    }

    sf::Sprite max_bet(this->GetTexture("max"));
    max_bet.setPosition({ 1225, 250 });
    bet_sprites.push_back(max_bet);

    if (exclude)
    {
        sf::Sprite back(this->GetTexture("back"));
        back.setPosition({ 670, 25 });
        bet_sprites.push_back(back);
    }

    for (auto& sprite : bet_sprites)
    {
        window.draw(sprite);
    }
}

void Config::_LoadTextureHelper()
{
    auto p = make_shared<sf::Texture>();
    p->loadFromFile("assets/max.png");
    this->m_texture_map["max"] = p;

    p = make_shared<sf::Texture>();
    p->loadFromFile("assets/cardBack.png");
    this->m_texture_map["back"] = p;

    p = make_shared<sf::Texture>();
    p->loadFromFile("assets/lose.png");
    this->m_texture_map["lose"] = p;

    p = make_shared<sf::Texture>();
    p->loadFromFile("assets/win.png");
    this->m_texture_map["win"] = p;

    auto bg_ptr = std::make_shared<sf::Texture>();
    bg_ptr->loadFromFile("assets/background.jpg");
    this->m_texture_map["background"] = bg_ptr;

}
