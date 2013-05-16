#include "introstate.h"

#include <memory>
#include <iostream>

#include "playstate.h"
#include "gameengine.h"

IntroState::IntroState(GameEngine &engine, bool replace)
    : GameState("intro", engine, replace)
{
    // Escape key should quit
    actionSystem.connect("escape_key", [&] (GameEngine::actionContext c) {
        engine.quit();
    });

    // Spacebar should build playstate
    actionSystem.connect("space_key", [&] (GameEngine::actionContext c) {
        _next = engine.build<PlayState>(true);
    });

    std::cout << "Entered introstate" << std::endl;
}

void IntroState::pause()
{

}

void IntroState::resume()
{

}

void IntroState::update(const sf::Time &dt)
{

}

void IntroState::draw()
{
    engine.screen.clear();
    engine.screen.display();
}
