#include "menustate.h"

#include <memory>
#include <iostream>

#include "gameengine.h"

MenuState::MenuState(GameEngine &engine, bool replace)
    : GameState("menu", engine, replace)
{
    // Escape should return to last state
    actionSystem.connect("escape_key", [&] (GameEngine::actionContext c) {
        engine.lastState();
    });

    std::cout << "Entered menu" << std::endl;
}

void MenuState::pause()
{

}

void MenuState::resume()
{

}

void MenuState::update(const sf::Time &dt)
{

}

void MenuState::draw()
{
    engine.screen.clear();
    engine.screen.display();
}
