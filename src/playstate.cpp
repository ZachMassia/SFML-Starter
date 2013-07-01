#include "playstate.h"

#include <memory>
#include <iostream>

#include "menustate.h"
#include "gameengine.h"

PlayState::PlayState(GameEngine& engine, bool replace) :
    GameState("play", engine, replace)
{
    // Escape key should quit
    actionSystem.connect("escape_key", [&] (GameEngine::actionContext c) {
        engine.quit();
    });

    // M key should enter menu
    engine.actionMap["m_key"] = thor::Action(sf::Keyboard::M);
    actionSystem.connect("m_key", [&] (GameEngine::actionContext c) {
        _next = engine.build<MenuState>(false);
    });

    std::cout << "Playstate built" << std::endl;
}

void PlayState::pause()
{
}

void PlayState::resume()
{
    std::cout << "Resume playstate" << std::endl;
}

void PlayState::update(const sf::Time &dt)
{

}

void PlayState::draw()
{
    engine.screen.clear();
    engine.screen.display();
}
