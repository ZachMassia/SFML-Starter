#pragma once

#include "gamestate.h"

#include <SFML/Graphics.hpp>

class GameEngine;

class MenuState : public GameState
{
public:
    MenuState(GameEngine& engine, bool replace = true);

    void pause();
    void resume();

    void update(const sf::Time &dt);
    void draw();

private:

};
