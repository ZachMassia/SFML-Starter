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

    initTitleText();
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
    engine.screen.draw(text);
    engine.screen.display();
}

void IntroState::initTitleText()
{
    font = engine.assets.acquire(engine.fontKeys.get("Ubuntu-R"));
    text.setFont(*font.get());

    text.setString("SNAKE!");
    text.setCharacterSize(engine.screen.getSize().y * 0.25f);
    text.setStyle(sf::Text::Bold);

    text.setPosition(engine.screen.getSize().x / 2 - text.getGlobalBounds().width / 2,
                     engine.screen.getSize().y * 0.35f);
}
