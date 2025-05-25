#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "config.h"
#include "input_box.h"
#include "buttons.h"
#include "card_deck.h"
#include "header.h"
#include "logic.h"
#include "player.h"
#include "dealer.h"
#include "timer.h"
#include "card_effect.h"
#include "game_stats.h"
#include "sound_manager.h"
#include "volume_slider.h"
#include "vegas_lights.h"
using namespace std;

class Engine
{
private:
    // SFML window instance
    sf::RenderWindow m_window;

    // Game components
    InputBox m_input_box;
    CardDeck m_card_deck;
    Buttons m_buttons;
    Button m_restart;
    Header m_header;
    Header m_bet_board;
    Player m_player;
    Dealer m_dealer;
    // For demo purposes
    Timer* m_heap_timer;  // timer on heap
    Timer m_stack_timer;  // timer on stack
    sf::Text m_timer_text;
    GameStats m_stats;

    // Game state
    bool m_entered_bet;
    int m_bet;
    bool m_end;
    vector<Card> m_player_cards;
    vector<Card> m_dealer_cards;

    // Initialization
    void _Init();

    // Event processing
    void _UpdateButtonsEvent(sf::Event& event);
    void _UpdateBetEvent();
    void _UpdateEndGameEvent(sf::Event& event);

    // Rendering
    void _DrawEndGame();

    // Game logic
    void _SetCardPosHelper();
    void _WinLogicHelper(int player_points, int dealer_points);

    //background
    sf::Sprite m_background_sprite;

    //audio
    SoundManager m_sound_manager;
    VolumeSlider m_volume_slider;

    sf::Clock m_lights_clock;

public:
    // Constructor / Destructor
    Engine();
    ~Engine();

    // Main engine loop functions
    void Input();
    void Run();
    void Display();
};

#endif
