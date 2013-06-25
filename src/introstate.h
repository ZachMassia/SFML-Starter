#pragma once

#include "gamestate.h"

#include <SFML/Graphics.hpp>
#include <memory>

class GameEngine;

class IntroState : public GameState
{
public:
    IntroState(GameEngine& engine, bool replace = true);

    void pause();
    void resume();

    void update(const sf::Time& dt);
    void draw();

private:
    void initTitleText();

    std::shared_ptr<sf::Font> font;
    sf::Text text;
};
