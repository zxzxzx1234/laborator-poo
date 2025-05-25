#include "engine.h"
#include <iostream>
#include "card_effect.h"
#include "game_logger.h"

using namespace std;
// Constructor: initializes window and game components
Engine::Engine()
{
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Black Jack");
    m_window.setKeyRepeatEnabled(true);
    _Init();
}

// Destructor
Engine::~Engine() {}

// Handles input events (keyboard, mouse, text)
void Engine::Input()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        m_volume_slider.HandleEvent(m_window, event);
       m_sound_manager.SetVolume(m_volume_slider.GetVolume());


        _UpdateButtonsEvent(event);
        _UpdateEndGameEvent(event);

        if (event.type == sf::Event::Closed)
        {
            cout << "User Quit" << endl;
            m_window.close();
            break;
        }

        if (event.type == sf::Event::TextEntered)
        {
            m_input_box.TypedOn(event);
            break;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !m_entered_bet)
        {
            _UpdateBetEvent();
            break;
        }
    }
}

// Updates the display (main draw loop)
void Engine::Display()
{
    m_window.draw(m_background_sprite); // background


    if (m_end)
    {
        _DrawEndGame();
        return;
    }

    m_header.DrawTo(m_window);
    m_bet_board.DrawTo(m_window);
    m_input_box.DrawTo(m_window);

    if (m_entered_bet)
        m_buttons.DrawButtons(m_window);

    _SetCardPosHelper();
    config.DrawConstants(m_window, m_entered_bet);
    std::string time_text = "Elapsed: " + std::to_string(m_stack_timer.ElapsedMilliseconds()) + " seconds";
    m_timer_text.setString(time_text);
    m_timer_text.setFillColor(sf::Color::Yellow);
    m_timer_text.setPosition({ 10, 10 });
    m_window.draw(m_timer_text);
    std::vector<IGameObject*> game_objects;
    m_header.DrawTo(m_window, sf::Color(255, 215, 0)); 
    m_volume_slider.DrawTo(m_window);
    float t = m_lights_clock.getElapsedTime().asSeconds();
    VegasLights::Update(t);
    VegasLights::Draw(m_window);

}

// Main game loop
void Engine::Run()
{
    sf::Font arial = config.GetFont(ARIAL);
    m_input_box.SetFont(arial);
    m_input_box.SetLimit(true, CHAR_LIMIT);
    m_header.SetFont(arial);
    m_bet_board.SetFont(arial);
    m_restart.SetFont(arial);

    m_timer_text.setFont(arial);
    m_timer_text.setCharacterSize(16);
    m_timer_text.setFillColor(sf::Color::White);
    m_timer_text.setPosition({ 10, 10 });  // top-left corner

    m_restart.SetPosition({ 300, 500 });

    while (m_window.isOpen())
    {
        m_input_box.UpdateInputBox();
        Input();
        m_window.clear(sf::Color(0, 102, 0));
        Display();
        if (m_stack_timer.ElapsedMilliseconds() > 10000) {
            std::cout << "[STACK TIMER] Round running for 10+ sec!" << std::endl;
        }
        if (m_heap_timer->ElapsedMilliseconds() > 15000) {
            std::cout << "[HEAP TIMER] Total elapsed > 15 sec!" << std::endl;
        }

        m_window.display();
    }
    delete m_heap_timer;

}
// Initializes all game components and state variables
void Engine::_Init()
{
    m_entered_bet = false;
    m_end = false;
    m_bet = 0;

    m_player_cards = std::vector<Card>();
    m_dealer_cards = std::vector<Card>();

    m_buttons = Buttons();
    m_restart = Button("Play Again", { 200, 50 }, 25, sf::Color::White, sf::Color::Red);
    m_header = Header(WELCOME_MESSAGE, HEADER_SIZE, HEADER_POS, HEADER_FONT_SIZE, sf::Color(0, 102, 0), sf::Color::Red);
    m_bet_board = Header("$" + to_string(m_player.GetBet()), BET_BOARD_SIZE, BET_BOARD_POS, INPUT_BOX_FONT_SIZE, sf::Color(0, 102, 0), sf::Color(255, 215, 0));

    m_input_box = InputBox(INPUT_BOX_FONT_SIZE, INPUT_BOX_SIZE, INPUT_BOX_POS, sf::Color::Red, sf::Color::White, false);
    m_card_deck = CardDeck();
    m_player = Player();
    m_dealer = Dealer();
    m_heap_timer = new Timer();   // timer on heap
    m_stack_timer = Timer();      // timer on stack
    m_background_sprite.setTexture(config.GetTexture("background"));

    m_sound_manager.PlayBackground();
    VegasLights::Init();

}

// Parses bet from input box, updates player's cards and bet
void Engine::_UpdateBetEvent()
{
    StrToIntParser parser(m_input_box.GetText());
    int bet = parser.ToInt();
    if (bet == -1) return;

    int original_bet = m_player.GetBet();
    if (bet > original_bet) return;


    m_player_cards.clear();
    m_dealer_cards.clear();
    m_entered_bet = true;

    for (int i = 0; i < 2; ++i)
    {
        m_player_cards.push_back(m_card_deck.DrawCard());
        m_dealer_cards.push_back(m_card_deck.DrawCard());
    }

    m_bet = bet;
    m_player.SetBet(m_bet, true);
    m_bet_board.SetHeader("$" + to_string(m_player.GetBet()));
    cout << "Bet: " << bet << endl;


}

// Handles button events: HIT, STAND, ANOTHER_GAME
void Engine::_UpdateButtonsEvent(sf::Event& event)
{
    if (!m_entered_bet) return;

    int action = m_buttons.UpdateButtons(m_window, event);

    if (action == HIT && m_player_cards.size() < MAX_CARDS)
    {
        m_sound_manager.PlayHit();
        std::cout << "hit" << std::endl;
        GameLogger logger("Gameplay");
        logger.Log("Player chose HIT.");

        Card c = m_card_deck.DrawCard();
        c.StartFlip();
        m_player_cards.push_back(c);


       
        if (!m_player_cards.empty()) {
            BurnEffect effect;
            effect.Apply(m_player_cards[0]);
            std::cout << "BurnEffect applied to first card." << std::endl;
        }

        return;
    }



    if (action == STAND)
    {
        m_sound_manager.PlayStand();
        cout << "stand" << endl;
        GameLogger logger("Gameplay");
        logger.Log("Player chose STAND.");

        int player_points = m_player.CalculatePoints(m_player_cards);
        int dealer_points = m_dealer.CalculatePoints(m_dealer_cards);

        dealer_points = m_dealer.DrawCardAI(m_dealer_cards, m_card_deck);

        for (int i = 2; i < m_dealer_cards.size(); ++i)
            m_dealer_cards[i].DrawTo(m_window); 



        cout << "player points: " << player_points << endl;
        cout << "dealer points: " << dealer_points << endl;

        m_entered_bet = false;
        _WinLogicHelper(player_points, dealer_points);
    }

    if (action == ANOTHER_GAME)
    {
        m_player_cards.clear();
        m_dealer_cards.clear();
        m_player.SetBet(m_bet, false);
        m_bet_board.SetHeader("$" + to_string(m_player.GetBet()));
        m_entered_bet = false;
        m_header.SetHeader(WELCOME_MESSAGE);
    }
}

// Updates game state if the user wins/loses the entire bet
void Engine::_UpdateEndGameEvent(sf::Event& event)
{
    bool hovering = m_restart.IsMouseOver(m_window);
    if (hovering && m_end) m_restart.SetBackColor(sf::Color::Yellow);
    if (!hovering && m_end) m_restart.SetBackColor(sf::Color::White);

    if (hovering && m_end && event.type == sf::Event::MouseButtonPressed)
    {
        cout << "Restart" << endl;
        m_end = false;
        m_player.Reset();
        m_player.SetBet(2500, false);
        m_bet_board.SetHeader("$" + to_string(m_player.GetBet()));
        m_header.SetHeader(WELCOME_MESSAGE);
        m_player_cards.clear();
        m_dealer_cards.clear();
    }
}

// Draws the end-game message (win or lose) and restart button
void Engine::_DrawEndGame()
{
    if (m_player.GetBet() == 0)
    {
        sf::Sprite lose(config.GetTexture("lose"));
        lose.setPosition({ 175, 75 });
        m_window.draw(lose);
        m_restart.DrawTo(m_window);
        return;
    }

    if (m_player.GetBet() >= 10000)
    {
        sf::Sprite win(config.GetTexture("win"));
        win.setPosition({ 175, 75 });
        m_window.draw(win);
        m_restart.DrawTo(m_window);
        return;
    }
}

// Applies win/lose/tie logic and updates state and bet accordingly
void Engine::_WinLogicHelper(int player_points, int dealer_points)
{
    Logic logic;
    int win_code = logic.CheckUserWin(player_points, dealer_points);

    if (win_code == WIN)
    {
        m_sound_manager.PlayWin();
        m_header.SetHeader(WIN_MESSAGE);
        m_player.SetBet(2 * m_bet, false);
        std::ostringstream ss;
        ss << m_player.GetBet();
        m_bet_board.SetHeader(ss.str());
        m_stats.wins++;
        std::cout << m_stats << std::endl;
        if (m_player.GetBet() >= 10000) m_end = true;
        return;
    }

    if (win_code == TIE)
    {
        m_header.SetHeader(TIE_MESSAGE);
        m_player.SetBet(m_bet, false);
        std::ostringstream ss;
        ss << m_player.GetBet();
        m_bet_board.SetHeader(ss.str());
        m_stats.ties++; 
        std::cout << m_stats << std::endl;
        return;
    }

    if (win_code == LOSE)
    {
        m_sound_manager.PlayLose();
        m_header.SetHeader(LOSE_MESSAGE);
        std::ostringstream ss;
        ss << m_player.GetBet();
        m_bet_board.SetHeader(ss.str());
        m_stats.losses++;
        std::cout << m_stats << std::endl;
        if (m_player.GetBet() == 0) m_end = true;
        return;
    }
}


// Positions and draws player and dealer cards on screen
void Engine::_SetCardPosHelper()
{
    for (size_t i = 0; i < m_player_cards.size(); ++i)
    {
        if (!m_player_cards[i].IsAnimating())
            m_player_cards[i].AnimateTo({ float(850 - 180 * i), 375 });
        m_player_cards[i].UpdateAnimation();
        m_player_cards[i].UpdateFlip();

        m_player_cards[i].DrawTo(m_window);
    }

    for (size_t i = 0; i < m_dealer_cards.size(); ++i)
    {
        if (!m_dealer_cards[i].IsAnimating())
            m_dealer_cards[i].AnimateTo({ float(850 - 180 * i), 25 });
        m_dealer_cards[i].UpdateAnimation();
        m_dealer_cards[i].UpdateFlip();
        m_dealer_cards[i].DrawTo(m_window);
    }
}

