#pragma once

#include "gamestate.h"

#include <SFML/Graphics.hpp>
#include <memory>

#include "snake.h"

class GameEngine;

class PlayState : public GameState
{
public:
    PlayState(GameEngine& engine, bool replace = true);

    void pause();
    void resume();

    void update(const sf::Time &dt);
    void draw();

private:
    Snake snake;
};
