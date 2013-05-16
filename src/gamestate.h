#pragma once

#include <memory>
#include <string>

#include <SFML/System/Time.hpp>
#include <Thor/Input.hpp>

#include "gameengine.h"

class GameState
{
public:
    GameState(const std::string& id, GameEngine& _engine, bool replace = true)
        : stateID(id), engine(_engine), replacing(replace) {}

    virtual ~GameState() {}

    virtual void pause()  = 0;
    virtual void resume() = 0;

    virtual void update(const sf::Time& dt) = 0;
    virtual void draw()   = 0;

    std::unique_ptr<GameState> next()
    {
        return std::move(_next);
    }

    bool isReplacing()
    {
        return replacing;
    }

    // Each state will use it's own callback system to avoid previously connected actions from
    // interfering with the current state.
    thor::ActionMap<std::string>::CallbackSystem actionSystem;

    const std::string stateID;

protected:
    bool replacing;
    std::unique_ptr<GameState> _next;

    GameEngine& engine;
};
