#pragma once

#include "gamestate.h"

#include <SFML/Graphics.hpp>

class GameEngine;

class PlayState : public GameState
{
public:
    PlayState(GameEngine& engine, bool replace = true);

    void pause();
    void resume();

    void update();
    void draw();

private:

};
