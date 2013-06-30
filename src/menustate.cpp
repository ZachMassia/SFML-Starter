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

    font = engine.assets.acquire(engine.fontKeys.get("Ubuntu-R"));
    text.setFont(*font.get());

    text.setString("Press escape to continue playing");
    text.setCharacterSize(engine.screen.getSize().y * 0.065);

    text.setPosition(engine.screen.getSize().x / 2 - text.getGlobalBounds().width / 2,
                     engine.screen.getSize().y * 0.275);
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
    engine.screen.draw(text);
    engine.screen.display();
}
