#include "playstate.h"

#include <memory>
#include <iostream>
#include <sstream>

#include <cstdlib>
#include <ctime>
#include <cmath>

#include "introstate.h"
#include "menustate.h"
#include "gameengine.h"

PlayState::PlayState(GameEngine& engine, bool replace) :
    GameState("play", engine, replace),
    cellSize(engine.screen.getSize().x / 20),
    snake(engine.screen.getSize(), cellSize)
{
    // Seed the RNG using current time
    std::srand(std::time(0));

    //snake.snakeDiesOnEdgeCollision = false;

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

    initApples();
    initScoreText();
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
        std::cout << "SNAKE DEAD @ X: " << snake.getHeadPosition().x << " Y: "
                  << snake.getHeadPosition().y << std::endl;
        std::cout << getScore() << std::endl;
        _next = engine.build<IntroState>(true);
    }

    updateScoreText();

    // Check collisions
    sf::FloatRect snakeRect = snake.getHeadRect();
    for (auto& apple : apples) {
        if (snakeRect.intersects(apple.sprite.getGlobalBounds())) {
            apple.alive = false;
            snake.grow();
        }
    }

    // Spawn new apple
    if (clock.getElapsedTime() - lastAppleSpawn > sf::seconds(2.5f)) {
        spawnApple();
    }

}

void PlayState::draw()
{
    engine.screen.clear();

    engine.screen.draw(snake);
    for (auto& apple : apples) {
        if (apple.alive) {
            engine.screen.draw(apple.sprite);
        }
    }
    engine.screen.draw(scoreText);

    engine.screen.display();
}

void PlayState::initApples()
{
    for (auto& apple: apples) {
        apple.alive = false;
        apple.sprite.setFillColor(sf::Color::Green);
        apple.sprite.setOutlineColor(sf::Color::White);
        apple.sprite.setOutlineThickness(-1.0f);
        apple.sprite.setSize(sf::Vector2f(cellSize, cellSize));
    }
}

void PlayState::spawnApple()
{
    // Get first dead apple
    Apple* apple;
    for (auto& a: apples) {
        if (!a.alive) {
            apple = &a;
            break;
        }
    }

    // Make sure we're not dealing with a nullptr
    if (nullptr == apple) {
        return;
    }

    apple->alive = true;

    // Return a random Vector2f
    auto getNewPos = [&] () {
        float x = std::fmod(std::rand(),
                            engine.screen.getSize().x - apple->sprite.getGlobalBounds().width);
        float y = std::fmod(std::rand(),
                            engine.screen.getSize().y - apple->sprite.getGlobalBounds().height);

        return sf::Vector2f(x, y);
    };

    // Make sure apple does not spawn on snake
    do {
        apple->sprite.setPosition(getNewPos());
    } while (snake.rectIntersectsSnake(apple->sprite.getGlobalBounds()));

    lastAppleSpawn = clock.getElapsedTime();
}

std::string PlayState::getScore()
{
    std::stringstream score;
    score << "SCORE: " << snake.length() * 10;
    return score.str();
}

void PlayState::initScoreText()
{
    scoreFont = engine.assets.acquire(engine.fontKeys.get("Ubuntu-R"));
    scoreText.setFont(*scoreFont.get());

    scoreText.setString(getScore());
    scoreText.setCharacterSize(engine.screen.getSize().y * 0.04);
    scoreText.setStyle(sf::Text::Bold);

    scoreText.setPosition(engine.screen.getSize().x * 0.05f,
                          engine.screen.getSize().y * 0.05f);
}

void PlayState::updateScoreText()
{
    scoreText.setString(getScore());
}
