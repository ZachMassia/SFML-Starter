#pragma once

#include "gamestate.h"

#include <SFML/Graphics.hpp>

class GameEngine;

class IntroState : public GameState
{
public:
    IntroState(GameEngine& engine, bool replace = true);

    void pause();
    void resume();

    void update();
    void draw();

private:

};
