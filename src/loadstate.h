#pragma once

#include "gamestate.h"

#include <SFML/Graphics.hpp>

class GameEngine;

class LoadState : public GameState
{
public:
    LoadState(GameEngine& engine, bool replace = true);

    void pause();
    void resume();

    void update(const sf::Time &dt);
    void draw();

private:
    void cacheAllAssets();
};
