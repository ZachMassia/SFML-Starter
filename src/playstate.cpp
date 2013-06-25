#include "playstate.h"

#include <memory>
#include <iostream>

#include "introstate.h"
#include "menustate.h"
#include "gameengine.h"

PlayState::PlayState(GameEngine& engine, bool replace) :
    GameState("play", engine, replace),
    snake(engine.screen.getSize(), engine.screen.getSize().x / 17.5)
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

    actionSystem.connect("up_key_once", [&] (GameEngine::actionContext c) {
        snake.direction = Snake::UP;
    });

    actionSystem.connect("down_key_once", [&] (GameEngine::actionContext c) {
        snake.direction = Snake::DOWN;
    });

    actionSystem.connect("left_key_once", [&] (GameEngine::actionContext c) {
        snake.direction = Snake::LEFT;
    });

    actionSystem.connect("right_key_once", [&] (GameEngine::actionContext c) {
        snake.direction = Snake::RIGHT;
    });

    // Debug actions
    engine.actionMap["plus"] = thor::Action(sf::Keyboard::Equal, thor::Action::PressOnce);
    actionSystem.connect("plus", [&] (GameEngine::actionContext c) {
        snake.grow();
    });
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
    snake.update(dt);

    if (snake.isDead()) {
        _next = engine.build<IntroState>(true);
    }
}

void PlayState::draw()
{
    engine.screen.clear();
    engine.screen.draw(snake);
    engine.screen.display();
}
